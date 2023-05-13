# muduo - 设计与实现

[[toc]]

# Reactor 介绍

Reactor模式用 **非阻塞IO + poll(epoll)函数来处理并发**，程序的基本结构是一个事件循环，以事件驱动和事件回调的方式实现业务逻辑。可参考《基于I/O复用的Reactor模式》。

```cpp
while(!done)
{
    int retval  = poll(fds,nfds,timeout)
    if(retval < 0)
        处理错误，回调用户的error handler
    else{
        处理到期的timers,回调用户的timer handler
        if(retval > 0){
            处理IO事件，毁掉用户的IO event handler
        }
    }
}
```

# 单线程Reactor实现

muduo的Reactor**核心主要由 EventLoop、Channel、Poller、TimerQueue这几个类完成**。代码里面各种回调函数的处理逻辑，使得看起来不直观。另外，这几个类的生命周期也值得注意，容易理不清楚。根据muduo的**中心思想one loop per thread ，每个线程只有一个EventLoop对象**。同时，每个Channel对象也只属于一个EventLoop，因此每个Channel对象只属于某一个IO线程。每个Channel对象只负责一个文件描述符（fd）的IO事件分发，但它并不拥有这个fd，也不会在析构的时候关闭fd。Channel的生命周期也由owner class负责管理。

## EventLoop类

EventLoop类是核心，大多数类都会包含一个EventLoop*的成员，因为所有的事件都会在EventLoop::loop()中通过Channel分发。先来看一下这个loop循环:

```cpp
void EventLoop::loop()
{
  assert(!looping_);
  assertInLoopThread();
  looping_ = true;
  quit_ = false;  // FIXME: what if someone calls quit() before loop() ?
  LOG_TRACE << "EventLoop " << this << " start looping";

  while (!quit_)
  {
    activeChannels_.clear();
    pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);
    ++iteration_;
    if (Logger::logLevel() <= Logger::TRACE)
    {
      printActiveChannels();
    }
    // TODO sort channel by priority
    eventHandling_ = true;
    for (Channel* channel : activeChannels_)
    {
      currentActiveChannel_ = channel;
      currentActiveChannel_->handleEvent(pollReturnTime_);
    }
    currentActiveChannel_ = NULL;
    eventHandling_ = false;
    doPendingFunctors();
  }

  LOG_TRACE << "EventLoop " << this << " stop looping";
  looping_ = false;
}
```

主要处理逻辑：调用poll函数获取activeChannels_，然后遍历activeChannels_，调用handleEvent 处理对应的事件（handleEvent 是 Channel 类的成员函数，它会根据事件的类型去调用不同的 Callback）。

## Channel 类

Channel类比较简单，负责IO事件分发，每一个Channel对象都对应了一个fd，它的核心成员如下：

```cpp
EventLoop* loop_;
const int  fd_;
int        events_;
int        revents_; // it's the received event types of epoll or poll
int        index_; // used by Poller.

ReadEventCallback readCallback_;
EventCallback writeCallback_;
EventCallback closeCallback_;
EventCallback errorCallback_;
```

Channel会在 handleEvent 函数中将不同的IO事件分发为不同的回调函数，例如readCallback_，writeCallback_。index_是 poller 类中 pollfds_数组的下标。events_和 revents_对应了 struct pollfd 结构中的成员，events_是关心的IO事件，由用户设置；revents_是目前活动的事件，由EventLoop/Poller设置。

Channel::update()会**调用EventLoop::updateChannel()，后者会转而调用Poller::updateChannel()，其函数会对pollfds_作添加或更新处理**。

### poll简述

poll的使用方法与select相似，轮询多个文件描述符，有读写时设置相应的状态位，poll相比select优在没有最大文件描述符数量的限制。

```cpp
# include <poll.h>
int poll ( struct pollfd * fds, unsigned int nfds, int timeout);
 
struct pollfd {
int fd;         /* 文件描述符 */
short events;         /* 等待的事件 */
short revents;       /* 实际发生了的事件 */
} ; 
```

每一个pollfd结构体指定了一个被监视的文件描述符，poll函数可以传递多个结构体，表示poll()监视多个文件描述符。每个结构体的events域是监视该文件描述符的事件掩码，由用户来设置这个域。revents域是文件描述符的操作结果事件掩码，内核在调用返回时设置这个域。events域中请求的任何事件都可能在revents域中返回。

poll函数的事件标志符值如下：

| 常量       | 说明                     |
| ---------- | ------------------------ |
| POLLIN     | 普通或优先级带数据可读   |
| POLLRDNORM | 普通数据可读             |
| POLLRDBAND | 优先级带数据可读         |
| POLLPRI    | 高优先级数据可读         |
| POLLOUT    | 普通数据可写             |
| POLLWRNORM | 普通数据可写             |
| POLLWRBAND | 优先级带数据可写         |
| POLLERR    | 发生错误                 |
| POLLHUP    | 发生挂起                 |
| POLLNVAL   | 描述字不是一个打开的文件 |

## Poller类

Poller类在这里是poll函数的封装（在muduo源码里面是抽象基类，支持poll和epoll），Poller 的职责也很简单，负责IO multiplexing，一个 EventLoop 有一个 Poller，Poller的生命周期和 EventLoop一样长。它有两个核心的数据成员：

```cpp
typedef std::vector<struct pollfd> PollFdList;
typedef std::map<int, Channel*> ChannelMap;  // fd to Channel
PollFdList pollfds_;
ChannelMap channels_;
```

ChannelMap是fd到Channel类的映射，PollFdList保存了每一个fd所关心的事件，用作参数传递到poll函数中，Channel类里面的index_即是这里的下标。Poller类有下面四个函数：

```cpp
Timestamp poll(int timeoutMs, ChannelList* activeChannels);
void updateChannel(Channel* channel);
void removeChannel(Channel* channel);
private:
void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;
updateChannel主要功能是负责维护和更新pollfds_数组，removeChannel负责从pollfds_移除指定channel对应的fd。

poll函数是对::poll的封装,获取当前活动的IO事件，然后填充调用方传入的activeChannels。其中主要逻辑：poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);//pollfds_传入传出参数，有读写时设置相应的状态位。

Timestamp PollPoller::poll(int timeoutMs, ChannelList* activeChannels)
{
  // XXX pollfds_ shouldn't change
  int numEvents = ::poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);//pollfds_传入传出参数，有读写时设置相应的状态位
  int savedErrno = errno;
  Timestamp now(Timestamp::now());
  if (numEvents > 0)
  {
    LOG_TRACE << numEvents << " events happened";
    fillActiveChannels(numEvents, activeChannels);
  }
  else if (numEvents == 0)
  {
    LOG_TRACE << " nothing happened";
  }
  else
  {
    if (savedErrno != EINTR)
    {
      errno = savedErrno;
      LOG_SYSERR << "PollPoller::poll()";
    }
  }
  return now;
}
```

fillActiveChannels 函数遍历pollfds_，找出有活动事件的fd（pollfds_中fd对应的revents已经在poll函数中置位了），把它对应的Channel添加到 activeChannels（vector<Channel*>）这个结构中，返回给用户。 

```cpp
void PollPoller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const
{
  for (PollFdList::const_iterator pfd = pollfds_.begin();
      pfd != pollfds_.end() && numEvents > 0; ++pfd)
  {
    if (pfd->revents > 0)
    {
      --numEvents;
      ChannelMap::const_iterator ch = channels_.find(pfd->fd);
      assert(ch != channels_.end());
      Channel* channel = ch->second;
      assert(channel->fd() == pfd->fd);
      channel->set_revents(pfd->revents);
      // pfd->revents = 0;
      activeChannels->push_back(channel);
    }
  }
}
```

综上所述，EventLoop:loop()中调用Poller::poll()获取当前的活动事件的Channel列表，然后依次调用每个Channel的handleEvent函数进行处理，总体的处理时序图如下：

![Reactor时序图](/_images/book-note/muduo/Reactor时序图.JPG)
