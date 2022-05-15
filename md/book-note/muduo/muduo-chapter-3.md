# 定时器与TimerQueue

[[toc]]

# muduo库时间函数的选择

* 计时:只使用 gettimeofday 来获取当前时间。gettimeofday 的分辨率 (resolution) 是 1 微秒，足以满足日常计时的需要。muduo::Timestamp 用一个 int64_t 来表示从 Epoch 到现在的微秒数，其范围可达上下 30 万年。

* 定时:只使用 timerfd_* 系列函数来处理定时。（timerfd_create / timerfd_gettime / timerfd_settime）timerfd_create 把时间变成了一个文件描述符，该“文件”在定时器超时的那一刻变得可读，这样就能很方便地融入到 select/poll 框架中，用统一的方式来处理 IO 事件和超时事件，这也正是 Reactor 模式的长处。

# Timer* 类的设计与实现

* TimerId非常简单，它被设计用来取消Timer的，它的结构很简单，只有一个Timer指针和其序列号。TimerQueue为其友元，可以操作其私有数据。

* Timer封装了定时器的一些参数，例如超时回调函数、超时时间、定时器是否重复、重复间隔时间、定时器的序列号。其函数大都是设置这些参数，run()用来调用回调函数，restart()用来重启定时器（如果设置为重复）。

* TimerQueue其实现时基于Set的。TimerQueue的封装是为了让未到期的时间Timer有序的排列起来，这样，能够根据当前时间找到已经到期的Timer也能高效的添加和删除Timer。内部有channel，和timerfd关联。添加新的Timer后，在超时后，timerfd可读，会处理channel事件，之后调用Timer的回调函数；在timerfd的事件处理后，还有检查一遍超时定时器，如果其属性为重复还有再次添加到定时器集合中。

这里涉及了3个类TimerId、Timer、TimerQueue要知道他们怎么与EventLoop结合起来，还是从一个示例开始。简单来说，TimerQueue是用来进行管理调度的，而Timer是真正的超时事件（该Class中封装了真正的超时回调）。

```cpp
void printTid()
{
  printf("pid = %d, tid = %d\n", getpid(), muduo::CurrentThread::tid());
  printf("now %s\n", muduo::Timestamp::now().toString().c_str());
}

void print(const char* msg)
{
  printf("msg %s %s\n", muduo::Timestamp::now().toString().c_str(), msg);
  if (++cnt == 20)
  {
    g_loop->quit();
  }
}

int main()
{
  printTid();
  muduo::EventLoop loop;
  g_loop = &loop;

  print("main");
  loop.runAfter(1, boost::bind(print, "once1"));
#if 1
  loop.runAfter(1.5, boost::bind(print, "once1.5"));
  loop.runAfter(2.5, boost::bind(print, "once2.5"));
  loop.runAfter(3.5, boost::bind(print, "once3.5"));
  loop.runEvery(2, boost::bind(print, "every2"));
  loop.runEvery(3, boost::bind(print, "every3"));
#endif
  loop.loop();
  print("main loop exits");
  sleep(1);
}
```

首先，是EventLoop类对象的初始化：

```cpp
EventLoop::EventLoop()
  : looping_(false),
    quit_(false),
    eventHandling_(false),
    callingPendingFunctors_(false),
    iteration_(0),
    threadId_(CurrentThread::tid()),
    poller_(Poller::newDefaultPoller(this)),
    timerQueue_(new TimerQueue(this)),
    wakeupFd_(createEventfd()),
    wakeupChannel_(new Channel(this, wakeupFd_)),
    currentActiveChannel_(NULL)
{
    ...
}
```

这里，我们看到在EventLoop的构造函数中对Poller和TimerQueue类型的成员进行初始化。然后，看TimerQueue的构造函数：

```cpp
TimerQueue::TimerQueue(EventLoop* loop)
  : loop_(loop),
    timerfd_(createTimerfd()), //timefd描述符
    timerfdChannel_(loop, timerfd_), //channel对象
    timers_(),    //保存Timer的关键结构
    callingExpiredTimers_(false)
{
  timerfdChannel_.setReadCallback(
      std::bind(&TimerQueue::handleRead, this));
  // we are always reading the timerfd, we disarm it with timerfd_settime.
  timerfdChannel_.enableReading();
}
```

将timefd和Channel关联起来，并绑定TimerQueue::handleRead作为描述符可读时的回调函数，而在TimerQueue::handleRead中又会去调用超时的Timer的回调。

```cpp
void TimerQueue::handleRead()
{
  loop_->assertInLoopThread();
  Timestamp now(Timestamp::now());
  readTimerfd(timerfd_, now);

  std::vector<Entry> expired = getExpired(now);//关键处理逻辑

  callingExpiredTimers_ = true;
  cancelingTimers_.clear();
  // safe to callback outside critical section
  for (const Entry& it : expired)
  {
    it.second->run(); //Timer的回调
  }
  callingExpiredTimers_ = false;

  reset(expired, now);
}
```

其中

```cpp
Timer(TimerCallback cb, Timestamp when, double interval)
    : callback_(std::move(cb)),
      expiration_(when),
      interval_(interval),
      repeat_(interval > 0.0),
      sequence_(s_numCreated_.incrementAndGet())
  { }

  void run() const
  {
    callback_();
  }
```

TimerQueue的关键处理函数getExpired的实现，它会从timers_中移除已到期的Timer，同时更新activeTimers_（主要在cancelInLoop中使用，取消活动的定时器），并通过vector返回超期的Timer。

```cpp
typedef std::pair<Timestamp, Timer*> Entry;
typedef std::set<Entry> TimerList;
typedef std::pair<Timer*, int64_t> ActiveTimer;
typedef std::set<ActiveTimer> ActiveTimerSet;
  
TimerList timers_;
ActiveTimerSet activeTimers_; // for cancel()
//TimerQueue的结构

std::vector<TimerQueue::Entry> TimerQueue::getExpired(Timestamp now)
{
  assert(timers_.size() == activeTimers_.size());
  std::vector<Entry> expired;
  Entry sentry(now, reinterpret_cast<Timer*>(UINTPTR_MAX));
  TimerList::iterator end = timers_.lower_bound(sentry);//返回第一个大于等于now的迭代器，小于now的都已经超时
  assert(end == timers_.end() || now < end->first);
  std::copy(timers_.begin(), end, back_inserter(expired));//[begin end)之间的元素追加到expired末尾
  timers_.erase(timers_.begin(), end);//删除超时定时器

  //for (const Entry& it : expired)
  for (std::vector<Entry>::iterator it = expired.begin();
      it != expired.end(); ++it)
  {
    ActiveTimer timer(it.second, it.second->sequence());
    size_t n = activeTimers_.erase(timer);//删除超时定时器,即同步timers_和activeTimers_
    assert(n == 1); (void)n;
  }

  assert(timers_.size() == activeTimers_.size());
  return expired;
}
```

构造函数帮我们做了很多事情，不过上述情况是假设TimerQueue中已经有一系列已经排好序列的时间事件了，现在要来看看怎么添加这些时间。对应EventLoop中的函数就是runAt、runAfter、runEvery，这三个函数其实底层调用的TimeQueue::addTimer函数，只是传参不同而已。addTimer函数只负责转发，addTimerInLoop完成修改定时器列表的工作。

```cpp
TimerId EventLoop::runAt(Timestamp time, TimerCallback cb)
{
  return timerQueue_->addTimer(std::move(cb), time, 0.0);
}

TimerId EventLoop::runAfter(double delay, TimerCallback cb)
{
  Timestamp time(addTime(Timestamp::now(), delay));
  return runAt(time, std::move(cb));
}

TimerId EventLoop::runEvery(double interval, TimerCallback cb)
{
  Timestamp time(addTime(Timestamp::now(), interval));
  return timerQueue_->addTimer(std::move(cb), time, interval);
}

TimerId TimerQueue::addTimer(TimerCallback cb,
                             Timestamp when,
                             double interval)
{
  Timer* timer = new Timer(std::move(cb), when, interval);
  loop_->runInLoop(
      std::bind(&TimerQueue::addTimerInLoop, this, timer));
  return TimerId(timer, timer->sequence());
}

void TimerQueue::addTimerInLoop(Timer* timer)
{
  loop_->assertInLoopThread();
  bool earliestChanged = insert(timer);

  if (earliestChanged)
  {
    resetTimerfd(timerfd_, timer->expiration());
  }
}
```

整个处理过程如下：

1. EventLoop的构造函数创建TimerQueue的对象，TimerQueue构造函数中创建timerfd，并通过timerfdChannel_绑定timerfd和loop，设置超时回调该回调将用来调用Timer的callback_。
2. EventLoop通过runAt、runAfter、runEvery添加Timer和设置Timer的回调，这三个函数是通过设置不同的参数去调用TimeQueue::addTimer。
3. 此时定时器已经启动，当发生超时事件时，timerfd可读，poll调用返回。
4. 通过activeChannl返回活跃事件（这里的活跃事件即为timerfd可读事件）
5. 在Channel::handleRead()回调中将执行在TimerQueue构造函数中绑定的TimerQueue::handleRead()。
6. TimerQueue::handleRead()又将获取所有超时的Timer并执行Timer中的回调。

TimerQueue回调用户代码onTime的时序图：

![​TimerQueue时序图](/_images/book-note/muduo/​TimerQueue时序图.JPG)