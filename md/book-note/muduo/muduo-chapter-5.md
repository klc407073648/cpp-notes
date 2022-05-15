# EventLoop类剖析

[[toc]]

# 线程通信机制
通常一个进程（线程）通知另一个等待中的（线程），有以下几种方法：

1. pipe，使用fd[0] 为读端，fd[1]为写端，半双工。等待线程关注fd[0]的可读事件。
2. socketpair，也有一对文件描述符，可用于双向通信，全双工。
3. eventfd。**eventfd是一个比pipe更高效的线程间事件通知机制**:
    * 一方面:它比 pipe少用一个pipe descriptor，节省了资源；
    * 另一方面，eventfd的缓冲区管理简单，全部“buffer"只有定长8bytes，不像pipe那样可能有不定长的真正buffer。
4. condition。线程可以使用条件变量condition来实现消息通信。

muduo采用eventfd进行线程间通信，函数定义如下：

```cpp
#include <sys/eventfd.h>
 
int eventfd(unsigned int initval, int flags);
```

* 第一个参数是初始值，一般设置为0，后面是O_NONBLOCK、EFD_CLOEXEC之类的标志。

eventfd()创建了一个事件对象 (eventfd object)， 能在用户态用做事件wait/notify机制，通过内核去唤醒用户态的事件。内核会为这个对象维护一个64位的计数器(uint64_t)。并且使用第一个参数(initval)初始化这个计数器。调用这个函数就会返回一个新的文件描述符(event object)。这个描述符支持 read，write，以及有关epoll等操作。

# EventLoop类的剖析

EventLoop是整个muduo网络库的核心类，其重要性不言而喻，它的主要成员如下：

```cpp
typedef std::vector<Channel*> ChannelList;
 
bool looping_; /* atomic */    //loop循环标志
bool quit_; /* atomic and shared between threads, okay on x86, I guess. */   //是否退出标志
bool eventHandling_; /* atomic */     //是否在处理事件标志
bool callingPendingFunctors_; /* atomic */   //是否调用pendingFunctors标志
int64_t iteration_;       //迭代器，记录loop函数循环的次数
const pid_t threadId_;   //当前所属对象线程id
Timestamp pollReturnTime_;    //时间戳，poll返回的时间戳
boost::scoped_ptr<Poller> poller_;  //poller对象
boost::scoped_ptr<TimerQueue> timerQueue_;    //TimerQueue类型对象指针，构造函数中new
int wakeupFd_;     		//用于eventfd，线程间通信
// unlike in TimerQueue, which is an internal class,
// we don't expose Channel to client.
boost::scoped_ptr<Channel> wakeupChannel_;   //wakeupfd所对应的通道，该通道会纳入到poller来管理
boost::any context_;    //暂未剖析
 
// scratch variables
ChannelList activeChannels_;   //Poller返回的活动通道，vector<channel*>类型
Channel* currentActiveChannel_;   //当前正在处理的活动通道
 
MutexLock mutex_;
std::vector<Functor> pendingFunctors_; // GuardedBy mutex_ //本线程或其它线程使用queueInLoop添加的任务，可能是I/O计算任务
```

下面是它的构造函数：

```cpp
EventLoop::EventLoop()
  : looping_(false),  //表示还未循环
    quit_(false),
    eventHandling_(false),
    callingPendingFunctors_(false),
    iteration_(0),
    threadId_(CurrentThread::tid()),   //赋值真实id
    poller_(Poller::newDefaultPoller(this)),   //构造了一个实际的poller对象
    timerQueue_(new TimerQueue(this)),   //构造一个timerQueue指针，使用scope_ptr管理
    wakeupFd_(createEventfd()),   //创建eventfd作为线程间等待/通知机制
    wakeupChannel_(new Channel(this, wakeupFd_)),   //创建wakeupChannel通道，
    currentActiveChannel_(NULL)
{
  LOG_DEBUG << "EventLoop created " << this << " in thread " << threadId_;
  if (t_loopInThisThread)  //每个线程最多一个EventLoop对象，如果已经存在，使用LOG_FATAL终止abort它。
  {
    LOG_FATAL << "Another EventLoop " << t_loopInThisThread
              << " exists in this thread " << threadId_;
  }
  else
  {
    t_loopInThisThread = this; //this赋给线程局部数据指针，凭借这个这以保证per thread a EventLoop
  }
 
  //设定wakeupChannel的回调函数，即EventLoop自己的的handleRead函数
  wakeupChannel_->setReadCallback(
      boost::bind(&EventLoop::handleRead, this));
  // we are always reading the wakeupfd
  wakeupChannel_->enableReading();
}
```

构造函数中创建了一个wakeupFd以及wakeupChannel。之前我们说过Channel类的生命周期由TcpConnection，Acceptor类管理，唯有这个wakeupChannel类不同。这个类和EventLoop类是组合关系，是EventLoop中的对象，所以它的生命周期由EventLoop负责。实际上，它就是**EventLoop类中用来自己给自己通知的一个通道**，它利用同是类成员的wakeupFd_构造，负责提供线程间等待/通知机制。

下面来介绍EventLoop类的核心函数loop()函数：

```cpp
//事件循环，不能跨线程调用
//只能在创建该对象的线程中调用
void EventLoop::loop()
{
  assert(!looping_);
  assertInLoopThread();  //断言处于创建该对象的线程中
  looping_ = true;
  quit_ = false;  // FIXME: what if someone calls quit() before loop() ?
  LOG_TRACE << "EventLoop " << this << " start looping";
 
  while (!quit_)
  {
    activeChannels_.clear();  //首先清零
    pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);  //调用poll返回活动的通道，有可能是唤醒返回的
    ++iteration_; 
    if (Logger::logLevel() <= Logger::TRACE)
    {
      printActiveChannels();  //日志登记，日志打印
    }
    // TODO sort channel by priority
    eventHandling_ = true;  //true
    for (Channel* channel : activeChannels_)//遍历通道来进行处理
    {
      currentActiveChannel_ = channel;
      currentActiveChannel_->handleEvent(pollReturnTime_);
    }
    currentActiveChannel_ = NULL;   //处理完了赋空
    eventHandling_ = false;  //false
 //I/O线程设计比较灵活，通过下面这个设计也能够进行计算任务，否则当I/O不是很繁忙的时候，这个I/O线程就一直处于阻塞状态。
 //我们需要让它也能执行一些计算任务 
    doPendingFunctors();   //处理用户回调任务
  }
 
  LOG_TRACE << "EventLoop " << this << " stop looping";
  looping_ = false;
}

```

通过poller_->poll函数调用epoll_wait，等待事件发生，也就是activeChannels_返回。activeChannels_返回后，调用每个返回的Channel的handleEvent()函数依次处理发生的事件。对应的handleEvent函数实现如下：

```cpp
//处理所有发生的事件，如果活着，底层调用handleEventWithGuard
void Channel::handleEvent(Timestamp receiveTime) //事件到来调用handleEvent处理
{
  boost::shared_ptr<void> guard;
  if (tied_)
  {
    guard = tie_.lock();
    if (guard)
    {
      handleEventWithGuard(receiveTime);
    }
  }
  else
  {
    handleEventWithGuard(receiveTime);
  }
}
```

这里使用了shared_ptr保证线程安全，保证不会调用一个已经销毁了的对象。内部调用handleEventWithGuard()函数处理细节：

```cpp
//根据revents_判断对应事件类型，并处理所有发生的事件
//POLLIN、POLLNVAL、POLLOUT等为事件标志符
void Channel::handleEventWithGuard(Timestamp receiveTime)
{
  eventHandling_ = true;
  LOG_TRACE << reventsToString();
  if ((revents_ & POLLHUP) && !(revents_ & POLLIN))  //判断返回事件类型
  {
    if (logHup_)  //如果有POLLHUP事件，输出警告信息
    {
      LOG_WARN << "fd = " << fd_ << " Channel::handle_event() POLLHUP";
    }
    if (closeCallback_) closeCallback_(); //调用关闭回调函数
  }
 
  if (revents_ & POLLNVAL)  //不合法文件描述符，并没有终止，因为服务器程序要保证一天二十四小时工作。
  {
    LOG_WARN << "fd = " << fd_ << " Channel::handle_event() POLLNVAL";
  }
 
  if (revents_ & (POLLERR | POLLNVAL))
  {
    if (errorCallback_) errorCallback_();
  }
  if (revents_ & (POLLIN | POLLPRI | POLLRDHUP)) //POLLRDHUP是对端关闭连接事件，如shutdown等
  {
    if (readCallback_) readCallback_(receiveTime);
  }
  if (revents_ & POLLOUT)
  {
    if (writeCallback_) writeCallback_();
  }
  eventHandling_ = false;  //处理完了=false
}
```

handleEventWithGuard函数就是根据实际上发生的事件（revents_）的事件标志符，来执行相应回调函数的。这些函数我们在fd注册的时候同时注册过，现在事件发生了，就执行相应的回调就行了。至此，EventLoop完成了它的主要功能了。主要功能就是使用epoll等待事件，事件发生处理事件，然后回去再进行epoll_wait()就可以了，基本功能就是这样。

除此之外，EventLoop还具有额外的功能，就是loop()函数中最后一句的函数调用doPendingFunctors()。这个函数是为了让**I/O线程执行额外的计算任务的**，因为如果没有事件发生，I/O线程会一直处于I/O空闲状态，这个时候我们可以利用I/O线程来执行一些额外的任务。先说一下大概流程:

假设我们有这样的调用：loop->runInLoop(run)，说明想让IO线程执行一定的计算任务，此时若是在当前的IO线程，就马上就能执行run()；如果是其他线程调用的，那么就执行queueInLoop(run),将run异步添加到队列pendingFunctors_，当loop内处理完事件后，就执行doPendingFunctors()，也就执行到了run()；最后想要结束线程的话，执行quit。

因此，在看doPendingFunctors()函数之前先来看一下runInLoop()函数：

```cpp
//顾名思义，在I/O线程中调用某个函数，该函数可以跨线程调用
void EventLoop::runInLoop(const Functor& cb)
{
  if (isInLoopThread())//如果是在当前I/O线程中调用，就同步调用cb回调函数
  {
    cb();
  }
  else//否则在其他线程中调用，就异步将cb添加到任务队列当中，以便让EventLoop真实对应的I/O线程执行这个回调函数
  {
    queueInLoop(cb);
  }
}
```

下面是queueInLoop()函数的具体实现：

```cpp
//将任务添加到队列当中，队就是成员pendingFunctors_数组容器
void EventLoop::queueInLoop(const Functor& cb)
{
  {
  MutexLockGuard lock(mutex_);
  pendingFunctors_.push_back(cb);   //添加到任务队列当中
  }
  //如果当前调用queueInLoop调用不是I/O线程，那么唤醒该I/O线程，以便I/O线程及时处理。
  //或者调用的线程是当前I/O线程，并且此时调用pendingfunctor，需要唤醒
  //只有当前I/O线程的事件回调中调用queueInLoop才不需要唤醒
  if (!isInLoopThread() || callingPendingFunctors_)  
  {
    wakeup();
  }
}
```

加入要执行的事件到队列中后，我们当然希望I/O线程立刻执行该任务，所以立刻调用wakeup函数，唤醒I/O线程，具体实现是这样的：

```cpp
//唤醒EventLoop
void EventLoop::wakeup()    
{
  uint64_t one = 1;                                                           
  ssize_t n = sockets::write(wakeupFd_, &one, sizeof one);  //随便写点数据进去就唤醒了
  if (n != sizeof one)
  {
    LOG_ERROR << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
  }
}
```

wakeup函数调用了write，且文件描述符为wakeupFd_，我们就知道这是往我们之前的eventfd写一点数据，实现等待/通知机制，去触发该fd可读。且可以观察到EventLoop的构造函数，wakeupChannel_有设置对应的handleRead函数和enableReading函数。

```cpp
//设定wakeupChannel的回调函数，即EventLoop的handleRead函数
wakeupChannel_->setReadCallback(
      boost::bind(&EventLoop::handleRead, this));
// we are always reading the wakeupfd
wakeupChannel_->enableReading();

void enableReading() { events_ |= kReadEvent; update(); }   //或上事件，就是关注可读事件，注册到EventLoop，通过它注册到Poller中

void Channel::update()   //更新事件类型
{
  addedToLoop_ = true;
  loop_->updateChannel(this);  //调用loop的，loop再调用poll的注册pollfd
}
```

所以上述操作调用了write向eventfd写入几个字节后，EventLoop中poll会返回，然后开始进行事件处理，这次事件是wakeupFd产生的事件，loop()中这样执行：

```cpp
for (Channel* channel : activeChannels_)
{
    currentActiveChannel_ = channel;
    currentActiveChannel_->handleEvent(pollReturnTime_);
}
```

实际上handleEvent调用的就是构造函数中注册的EventLoop::headleRead函数：

```cpp
//实际上是wakeFd_的读回调函数
void EventLoop::handleRead()
{
  uint64_t one = 1;
  ssize_t n = sockets::read(wakeupFd_, &one, sizeof one);
  if (n != sizeof one)
  {
    LOG_ERROR << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
  }
}
```

我们看到它从wakeupFd读取了值之后并未处理，因为我们只是把wakeupFd（实际上是eventfd）作为等待/通知机制实现，这里是为了当我们向EventLoop的queue中也就是pendingFunctors_这个容器数组加入任务时，通过eventfd通知I/O线程从poll状态退出来执行I/O计算任务。

执行完eventfd的handleRead接下来就是loop()函数中处理任务函数了，就是最后一句doPendingFunctors()：

```cpp
// 1. 不是简单的在临界区内依次调用functor，而是把回调列表swap到functors中，这一方面减小了
//临界区的长度，意味着不会阻塞其他线程的queueInLoop()，另一方面也避免了死锁(因为Functor可能再次调用quueInLoop)
// 2. 由于doPendingFunctors()调用的Functor可能再次调用queueInLoop(cb)，这是queueInLoop()就必须wakeup(),否则新增的cb可能就不能及时调用了
// 3. muduo没有反复执行doPendingFunctors()直到pendingFunctors为空，这是有意的，否则I/O线程可能陷入死循环，无法处理I/O事件
void EventLoop::doPendingFunctors()
{
  std::vector<Functor> functors;
  callingPendingFunctors_ = true;
 
  //注意这里的临界区，这里使用了一个栈上变量functors和pendingFunctors交换
  {
  MutexLockGuard lock(mutex_);
  functors.swap(pendingFunctors_); //把它和空vector交换
  }
 
  //此处其它线程就可以往pendingFunctors添加任务
 
  //调用回调任务，这一部分不用临界区保护
  for (const Functor& functor : functors)
  {
    functor();
  }
  callingPendingFunctors_ = false;
}
```

它为了防止死锁与兼备高效性所采取的措施注释中已经解释过了，此刻I/O线程就可以顺利的执行这么些任务了。

# muduo跨线程函数调用

muduo库的跨线程函数主要是通过EventLoop类的成员函数runInLoop函数实现的，例子如下：

```cpp
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include <stdio.h>
using namespace muduo;
using namespace muduo::net;
 
void th_fn()
{
    printf("th_fn() : pid = %d, tid = %d\n", getpid(), CurrentThread::tid());
 
}
 
int main()
{
    printf("main(): pid = %d, tid = %d\n",
                    getpid(), CurrentThread::tid());    
    EventLoopThread loopThread; 
    EventLoop* loop = loopThread.startLoop();//创建了一个IO线程  并返回IO线程所对应的EventLoop对象的指针
    loop->runInLoop(th_fn);//跨线程调用函数th_fn
    sleep(1);
    loop->quit(); 
    printf("exit main().\n");
    return 0;
}
```

上述程序中，loopThread.startLoop函数执行完毕会创建一个IO线程，并返回IO线程所对应的EventLoop对象的指针，也就是loop指针指向的EventLoop并不在主线程中，我们在主线程执行loop->runInLoop(th_fn)怎么就能在loop指针指向的EventLoop所在的IO线程执行th_fn函数呢？

根据第二章节的描述，muduo库实现跨线程调用其实就是**通过向指定的IO线程的wakeupFd_上随便发点数据，让对应线程中loop()循环中之前阻塞监听的poll函数返回活跃通道，好让线程赶快执行回调函数。这样，回调函数执行完毕，其就可以调用doPendingFunctors函数执行我们之前添加的th_fn函数了。**也就是说，之前对应的线程可能没有活跃事件，所以一直阻塞，我们随便向wakeupFd_上发点数据就可以让poll返回了，然后赶快处理对应通道上注册的回调，其实处理指定的线程的回调函数并不是我们的目的，只是说，只有指定的线程执行完回调，我们期望的跨线程调用的函数才能被执行到。**wakeup的目的其实就是通知线程赶快执行我们跨线程调用的函数**，不然，其实以后只要该线程上有活跃事件，其实跨线程调用的函数还是会被执行的。也就是说，不通过wakeup方式，我们的跨线程调用的函数也会被执行，只是什么时候被执行就不好说了，只要线程检测到活跃事件才行。另外，为什么我们可以在**主线程中向loop指针指向的EventLoop对象的成员pendingFunctors_中添加数据呢?这都是因为我们在主线程有了指向该EventLoop对象的指针loop，通过loop指针，我们就可以修改它上面的数据。**

即loop->runInLoop(th_fn)——> loop->queueInLoop ——> loop->wakeup（loop->wakeup，所以这里的wakeupFd_和wakeupChannel_都是loop指针指向的EventLoop对象的成员，即IO线程的内容，非主线程）——>wakeup通过发送数据唤醒loop->loop()中的poll，执行对应的回调函数——>最终在doPendingFunctors里执行了th_fn函数。

我们最后来看一下上面程序的执行结果，可以看到执行main函数和th_fn函数的线程id是不同的，说明实现了跨线程调用。

```bash
[root@192 EventLoop]# g++ runInLoopTest.cpp -o runInLoopTest -I /home/muduo/muduo-master -L/home/muduo/build/release-cpp11/lib/  -lmuduo_net  -lmuduo_base -lpthread

[root@192 EventLoop]# ./runInLoopTest
main(): pid = 2326, tid = 2326
th_fn() : pid = 2326, tid = 2327
exit main().
```