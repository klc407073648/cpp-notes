# muduo - EventLoopThread和EventLoopThreadPool剖析

[[toc]]

​# EventLoopThread

EventLoopThread是事件循环线程，包含一个Thread对象和一个EventLoop对象。在构造函数中，把EventLoopThread::threadFunc 注册到Thread对象中，在EventLoopThread::startLoop()函数中进行回调。

EventLoopThread的工作流程为：

1. 在主线程创建EventLoopThread对象。
2. 主线程调用EventLoopThread.start()，启动EventLoopThread中的线程（称为IO线程），而且主线程要等待IO线程创建完毕EventLoop对象。 
3. IO线程调用threadFunc创建EventLoop对象。通知主线程已经创建完毕。 
4. 主线程返回创建的EventLoop对象。

EventLoopThread类分析：

类定义如下：

```cpp
class EventLoopThread : noncopyable
{
 public:
  typedef std::function<void(EventLoop*)> ThreadInitCallback;

  EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),
                  const string& name = string());
  ~EventLoopThread();
  EventLoop* startLoop();

 private:
  void threadFunc();

  EventLoop* loop_ GUARDED_BY(mutex_);
  bool exiting_;
  Thread thread_;
  MutexLock mutex_;
  Condition cond_ GUARDED_BY(mutex_);
  ThreadInitCallback callback_;
};
```

成员函数： 

```cpp
/******************************************************************** 
Description : 这个类专门创建一个线程用于执行Reactor的事件循环，当然
这只是一个辅助类，没有说一定要使用它，可以根据自己的情况进行选择，
你也可以不创建线程去执行事件循环，而在主线程中执行事件循环，
一切根据自己的需要。
*********************************************************************/

//构造函数
EventLoopThread::EventLoopThread(const ThreadInitCallback& cb,
                                 const string& name)
  : loop_(NULL),
    exiting_(false),
    thread_(std::bind(&EventLoopThread::threadFunc, this), name),
    mutex_(),
    cond_(mutex_),
    callback_(cb)
{
}

//析构函数
EventLoopThread::~EventLoopThread()
{
  exiting_ = true;
  if (loop_ != NULL)
  {
    loop_->quit();
    thread_.join();
  }
}

// 启动一个EventLoop线程
EventLoop* EventLoopThread::startLoop()
{
  assert(!thread_.started());
  // 当前线程启动，调用threadFunc()
  thread_.start();
  EventLoop* loop = NULL;
  {
    MutexLockGuard lock(mutex_);
    while (loop_ == NULL)
    {
      // 等待创建好当前IO线程
      cond_.wait();
    }
    loop = loop_;
  }
  return loop;
}

void EventLoopThread::threadFunc()
{
  EventLoop loop;
  // 如果有初始化函数，就先调用初始化函数
  if (callback_)
  {
    callback_(&loop);
  }
  {
    MutexLockGuard lock(mutex_);
    // loop_指针指向了一个栈上的对象，threadFunc函数退出之后。这个指针就失效了
    // threadFunc函数退出，就意味着线程退出了，EventLoopThread对象也就没有存在的价值了。
    // 因而不会有什么大的问题
    loop_ = &loop;
    // 通知startLoop线程已经启动完毕
    cond_.notify();
  }
  // 事件循环,直到EventLoopThread析构。此后不再使用loop_访问EventLoop了。
  loop.loop();
  MutexLockGuard lock(mutex_);
  loop_ = NULL;
}
```

测试程序：

```cpp
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

void runInThread()
{
  printf("runInThread(): pid = %d, tid = %d\n",
         getpid(), CurrentThread::tid());
}

int main()
{
  printf("main(): pid = %d, tid = %d\n",
         getpid(), CurrentThread::tid());

  EventLoopThread loopThread;
  EventLoop* loop = loopThread.startLoop();
  // 异步调用runInThread，即将runInThread加入到loop对象所在IO线程，让该IO线程运行
  loop->runInLoop(runInThread);
  sleep(1);
  // runAfter内部也调用了runInLoop。所以这里也是异步调用
  loop->runAfter(2, runInThread);
  sleep(3);
  loop->quit();

  printf("exit main().\n");
}
```

执行结果：

```bash
[root@192 EventLoopThread]# g++ runInLoopThreadTest.cpp -o runInLoopThreadTest -I /home/muduo/muduo-master -L/home/muduo/build/release-cpp11/lib/  -lmuduo_net  -lmuduo_base -lpthread
[root@192 EventLoopThread]# ./runInLoopThreadTest
main(): pid = 2399, tid = 2399
runInThread(): pid = 2399, tid = 2400
runInThread(): pid = 2399, tid = 2400
exit main().
[root@192 EventLoopThread]#
```

对于上述调用程序进行分析：

主线程调用 loop->runInLoop(runInThread); 因为主线程（不是IO线程）调用runInLoop。 故进一步调用queueInLoop() 将runInThread 加入到队列，然后wakeup() IO线程。IO线程在doPendingFunctors() 中取loop->runAfter() 要唤醒一下，此时仅仅是运行runAfter() 加入了一个2s的定时器, 2s超时。timerfd_ 可读，先handleRead()一下然后运行回调函数runInThread()。

那为什么exit main() 之后wakeupFd_ 还会有可读事件呢？那是由于EventLoopThead 栈上对象析构，在析构函数内 loop_ ->quit(), 因为不是在IO线程调用quit()，故也须要唤醒一下。IO线程才干从poll 返回，这样再次循环推断 while (!quit_) 就能退出IO线程。

# EventLoopThreadPool

muduo的线程模型：

![线程模型](/_images/book-note/muduo/线程模型.JPG)

muduo的思想是EventLoop + thread pool。为了更方便使用，将EventLoopThread做了封装。main reactor能够创建sub reactor，并发一些任务分发到sub reactor中去。EventLoopThreadPool的思想比较简单，用一个main reactor创建EventLoopThreadPool。在EventLoopThreadPool中将EventLoop和Thread绑定，能够返回EventLoop对象来使用EventLoopThreadPool中的Thread。

EventLoopThreadPool 是一个线程池，只不过该线程池有一点特殊，该线程池中的每一个线程都要执行EventLoop进行文件描述符的监听。**此时一个线程用于管理分配线程池中的EventLoop,如果线程池为空，主线程的EventLoop用于监听所有的文件描述符。**

## EventLoopThreadPool类分析：

类定义如下：

```cpp
class EventLoopThreadPool : noncopyable
{
 public:
  typedef std::function<void(EventLoop*)> ThreadInitCallback;

  EventLoopThreadPool(EventLoop* baseLoop, const string& nameArg);
  ~EventLoopThreadPool();
  void setThreadNum(int numThreads) { numThreads_ = numThreads; }
  void start(const ThreadInitCallback& cb = ThreadInitCallback());

  // valid after calling start()
  /// round-robin
  EventLoop* getNextLoop();

  /// with the same hash code, it will always return the same EventLoop
  EventLoop* getLoopForHash(size_t hashCode);

  std::vector<EventLoop*> getAllLoops();

  bool started() const
  { return started_; }

  const string& name() const
  { return name_; }

 private:

  EventLoop* baseLoop_;    //线程池类用于服务端，baseLoop_用于接收新连接，线程池用于处理这些新连接的IO操作。与Acceptor所属EventLoop同样
  string name_;
  bool started_;          //开始标志
  int numThreads_;        // 线程数
  int next_;              // 新连接到来。所选择的EventLoop对象下标
  std::vector<std::unique_ptr<EventLoopThread>> threads_;    // IO线程列表
  std::vector<EventLoop*> loops_;       // EventLoop列表
};
```

成员函数分析：

### 构造与析构

```cpp
EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, const string& nameArg)
  : baseLoop_(baseLoop),
    name_(nameArg),
    started_(false),
    numThreads_(0),
    next_(0)
{
}

EventLoopThreadPool::~EventLoopThreadPool()
{
  // Don't delete loop, it's stack variable
}
```

### 开启线程池 

```cpp
void EventLoopThreadPool::start(const ThreadInitCallback& cb)
{
  assert(!started_);
  baseLoop_->assertInLoopThread();

  started_ = true;

  //创建numThreads_个事件循环器，numThreads_通过setThreadNum函数进行设置
  //一般调用时先setThreadNum()，然后start().
  // void setThreadNum(int numThreads) { numThreads_ = numThreads; } 设置线程数量
  // void start(const ThreadInitCallback& cb = ThreadInitCallback()); 设置初始回调函数
  for (int i = 0; i < numThreads_; ++i)
  {
    char buf[name_.size() + 32];
    snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
    ////创建一个EventLoopThread 对象
    EventLoopThread* t = new EventLoopThread(cb, buf);
    threads_.push_back(std::unique_ptr<EventLoopThread>(t));
    //事件循环器开始执行，如果此时需要监听的文件描述符的数量小于线程个数
	//其余的线程会进入睡眠状态
    loops_.push_back(t->startLoop());
  }
  //线程池的个数为0，则主线程开始监听套接字
  if (numThreads_ == 0 && cb)
  {
    cb(baseLoop_);
  }
}
```

### getNextLoop 采用轮询的方式分配EventLoop

```cpp
//循环获取下一个线程池的loop，保证各IO线程上执行的IO操作基本负载均衡
EventLoop* EventLoopThreadPool::getNextLoop()
{
  baseLoop_->assertInLoopThread();
  assert(started_);
  EventLoop* loop = baseLoop_;

  //如果线程池为空，返回主线程的EventLoop
  if (!loops_.empty())
  {
    // round-robin
    loop = loops_[next_];
    ++next_;
    //循环获取，如果next_的值大于了loops_.size(), 从第一个开始获取
    if (implicit_cast<size_t>(next_) >= loops_.size())
    {
      next_ = 0;
    }
  }
  return loop;
}
```

### getLoopForHash采用hash方式分配EventLoop

```cpp
EventLoop* EventLoopThreadPool::getLoopForHash(size_t hashCode)
{
  baseLoop_->assertInLoopThread();
  EventLoop* loop = baseLoop_;

  if (!loops_.empty())
  {
    loop = loops_[hashCode % loops_.size()];////hash 的方式获取EventLoop 事件循环器
  }
  return loop;
}
```

### getAllLoops 返回所有的EventLoop 

```cpp
std::vector<EventLoop*> EventLoopThreadPool::getAllLoops()
{
  baseLoop_->assertInLoopThread();
  assert(started_);

  //如果线程池为空
  if (loops_.empty())
  {
    //将主线程的EventLoop 返回
    return std::vector<EventLoop*>(1, baseLoop_);
  }
  else
  {
    //否则，返回线程池中的EventLoop 
    return loops_;
  }
}
```

实际使用过程中，EventLoopThreadPool是嵌入TcpServer作为类的一个成员来使用：

```cpp
TcpServer::TcpServer(EventLoop* loop,
                     const InetAddress& listenAddr,
                     const string& nameArg,
                     Option option)
  : loop_(CHECK_NOTNULL(loop)),
    ipPort_(listenAddr.toIpPort()),
    name_(nameArg),
    acceptor_(new Acceptor(loop, listenAddr, option == kReusePort)),
    threadPool_(new EventLoopThreadPool(loop, name_)), //创建线程池
    connectionCallback_(defaultConnectionCallback),
    messageCallback_(defaultMessageCallback),
    nextConnId_(1)
{
  acceptor_->setNewConnectionCallback(
      std::bind(&TcpServer::newConnection, this, _1, _2));
}

void TcpServer::setThreadNum(int numThreads)
{
  assert(0 <= numThreads);
  threadPool_->setThreadNum(numThreads);//设置线程数量
}

void TcpServer::setThreadNum(int numThreads)
{
  assert(0 <= numThreads);
  threadPool_->setThreadNum(numThreads);
}

void TcpServer::start()
{
  if (started_.getAndSet(1) == 0)
  {
    threadPool_->start(threadInitCallback_);//线程池启动

    assert(!acceptor_->listening());
    loop_->runInLoop(
        std::bind(&Acceptor::listen, get_pointer(acceptor_)));
  }
}

void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr)
{
  loop_->assertInLoopThread();
  EventLoop* ioLoop = threadPool_->getNextLoop();//获取下一个Loop，进行使用
  ......
}
```