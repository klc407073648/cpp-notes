# muduo - TCP网络库和核心类

[[toc]]

# 实现TCP网络库

在muduo中，Reactor事件处理框架如下所示，从poll返回到再次调用poll阻塞称为一次事件循环。不同于传统的Reactor，将timers 做成循环中单独的一步，muduo将 timers 和IO handlers 视为等同的。

![TCP网络库](/_images/book-note/muduo/TCP网络库.JPG)

# Acceptor

Acceptor class 用于 accept 新的TCP 连接， 并通过回调通知使用者。它是一个内部class ，供 Tcpserver 使用，且生命期由 Tcpserver控制。其定义如下：

```cpp
class Acceptor : noncopyable
{
 public:
  typedef std::function<void (int sockfd, const InetAddress&)> NewConnectionCallback;

  Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reuseport);
  ~Acceptor();

  void setNewConnectionCallback(const NewConnectionCallback& cb)
  { newConnectionCallback_ = cb; }

  void listen();

  bool listening() const { return listening_; }

 private:
  void handleRead();

  EventLoop* loop_;
  Socket acceptSocket_;   //用于进行监听的socket
  Channel acceptChannel_; //进行监听的channel
  NewConnectionCallback newConnectionCallback_; //建立连接时调用的回调函数
  bool listening_;    //是否在进行监听，一种状态表示
  int idleFd_;    //是一个空闲的描述符，它是在描述符耗尽的时候，用于接收连接的
};
```

Acceptor 中的acceptSocket_ 是listening socket，即server socket。acceptChannel 用于观察此socket 上的readable 事件，并且回调Acceptor::handleRead()，handleRead()会调用accept 函数来接受新连接，并且回调用户的callback。

muduo用Acceptor构造函数和Acceptor::listen()成员函数的执行，代替了传统TCP服务器的创建过程：即socket、bind、listen：

```cpp
Acceptor::Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reuseport)
  : loop_(loop),
    acceptSocket_(sockets::createNonblockingOrDie(listenAddr.family())),//socket()过程
    acceptChannel_(loop, acceptSocket_.fd()),
    listening_(false),
    idleFd_(::open("/dev/null", O_RDONLY | O_CLOEXEC))
{
  assert(idleFd_ >= 0);
  acceptSocket_.setReuseAddr(true);
  acceptSocket_.setReusePort(reuseport);
  acceptSocket_.bindAddress(listenAddr);//bind()过程
  acceptChannel_.setReadCallback(
      std::bind(&Acceptor::handleRead, this));
}

void Acceptor::listen()
{
  loop_->assertInLoopThread();
  listening_ = true;
  acceptSocket_.listen();//listen()过程
  acceptChannel_.enableReading();
}
```

handleRead()函数说明：

```cpp
void Acceptor::handleRead()
{
  loop_->assertInLoopThread();
  InetAddress peerAddr;
  //FIXME loop until no more
  int connfd = acceptSocket_.accept(&peerAddr);
  if (connfd >= 0)
  {
    // string hostport = peerAddr.toIpPort();
    // LOG_TRACE << "Accepts of " << hostport;
    if (newConnectionCallback_)
    {
      newConnectionCallback_(connfd, peerAddr);
    }
    else
    {
      sockets::close(connfd);
    }
  }
  else
  {
    LOG_SYSERR << "in Acceptor::handleRead";
    // Read the section named "The special problem of
    // accept()ing when you can't" in libev's doc.
    // By Marc Lehmann, author of libev.
    if (errno == EMFILE) // 文件描述符耗尽了
    {
      ::close(idleFd_);
      idleFd_ = ::accept(acceptSocket_.fd(), NULL, NULL);
      ::close(idleFd_);
      idleFd_ = ::open("/dev/null", O_RDONLY | O_CLOEXEC);
    }
  }
}
```

这里会出现几种情况，首先调用socket的accept系统函数，顺便将对端的struct sockaddr_in填充，然后返回得到新连接的文件描述符。

1. 如果返回值大于等于0，代表分配成功。那么调用回调函数，直接将已连接描述符和对端struct sockaddr_in peerAddr传进去。
2. 如果没有分配成功，那么这时候说明文件描述符耗尽了。muduo库里总是预留了一个文件描述符，也就是/dev/null，如果文件描述符耗尽，那么我们关闭这个文件描述符，那么就会有一个空闲的文件描述符空出来，这样我们去接受新连接，然后接收到以后，立马关掉这个连接，然后重新占用这个文件描述符。也算是一个小的trick吧。

测试程序：

```cpp
//https://github.com/chenshuo/recipes
// recipes/reactor/s04/test7.cc

#include "Acceptor.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "SocketsOps.h"
#include <stdio.h>

void newConnection(int sockfd, const muduo::InetAddress& peerAddr)
{
  printf("newConnection(): accepted a new connection from %s\n",
         peerAddr.toHostPort().c_str());
  ::write(sockfd, "How are you?\n", 13);
  muduo::sockets::close(sockfd);
}

int main()
{
  printf("main(): pid = %d\n", getpid());

  muduo::InetAddress listenAddr(9981);
  muduo::EventLoop loop;

  muduo::Acceptor acceptor(&loop, listenAddr);
  acceptor.setNewConnectionCallback(newConnection);
  acceptor.listen();

  loop.loop();
}

——————————————————————————————————————————————————————————
服务端：
[root@192 s04]# ./test7
main(): pid = 2249
newConnection(): accepted a new connection from 127.0.0.1:59734

客户端：
[root@192 ~]# nc 127.0.0.1 9981
How are you?
```

# TcpServer

TcpServer新建连接的过程如图所示，其中Channel::handleEvent()的触发条件是listening socket可读，表明有新连接到达。TcpServer会为新连接创建对应的TcpConnection对象：

![TcpServer新建连接](/_images/book-note/muduo/TcpServer新建连接.JPG)

TcpServer class 的功能是管理accept 获得的 TcpConnection 。TcpServer class 是供用户直接使用的，生命期由用户控制，用户需要设置好callback，再调用start() 即可。

TcpServer class 的内部使用 acceptor 来获得新连接的fd。TcpServer 持有目前存活的TcpConnection 的 shared_ptr ， 每个TcpConnection 对象有一个名字，这个名字是其所属的TcpServer 在创建 TcpConnection 对象时生成，名字是ConnectionMap 的 key，在新连接到来时，Acceptor 会回调newConnetion() ,后者会创建TcpConnection 对象，将它加入 ConnectionMap ，设置好callback，再调用TcpConnection-> connectEstablished() 。

整个过程如下：

1. TcpServer通过setConnectionCallback和setMessageCallback来获取用户提供的回调函数；
2. TcpServer在构造函数中，将TcpServer::newConnection设置为acceptor_在接收新连接时的回调函数；
3. 在TcpServer::newConnection函数中，完成TcpConnection的创建，并将用户设置的回调函数传递给它，且加入ConnectionMap中。

```cpp
TcpServer::TcpServer(EventLoop* loop,
                     const InetAddress& listenAddr,
                     const string& nameArg,
                     Option option)
  : loop_(CHECK_NOTNULL(loop)),
    ipPort_(listenAddr.toIpPort()),
    name_(nameArg),
    acceptor_(new Acceptor(loop, listenAddr, option == kReusePort)),
    threadPool_(new EventLoopThreadPool(loop, name_)),
    connectionCallback_(defaultConnectionCallback),
    messageCallback_(defaultMessageCallback),
    nextConnId_(1)
{
  acceptor_->setNewConnectionCallback(
      std::bind(&TcpServer::newConnection, this, _1, _2)); 
}

void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr)
{
  loop_->assertInLoopThread();
  EventLoop* ioLoop = threadPool_->getNextLoop();
  char buf[64];
  snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
  ++nextConnId_;
  string connName = name_ + buf;

  LOG_INFO << "TcpServer::newConnection [" << name_
           << "] - new connection [" << connName
           << "] from " << peerAddr.toIpPort();
  InetAddress localAddr(sockets::getLocalAddr(sockfd));
  // FIXME poll with zero timeout to double confirm the new connection
  // FIXME use make_shared if necessary
  TcpConnectionPtr conn(new TcpConnection(ioLoop,
                                          connName,
                                          sockfd,
                                          localAddr,
                                          peerAddr));
  connections_[connName] = conn;
  conn->setConnectionCallback(connectionCallback_);
  conn->setMessageCallback(messageCallback_);
  conn->setWriteCompleteCallback(writeCompleteCallback_);
  conn->setCloseCallback(
      std::bind(&TcpServer::removeConnection, this, _1)); // FIXME: unsafe
  ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));
}

void TcpConnection::connectEstablished()
{
  loop_->assertInLoopThread();
  assert(state_ == kConnecting);
  setState(kConnected);
  channel_->tie(shared_from_this());
  channel_->enableReading();

  connectionCallback_(shared_from_this());
}
```

# TcpConnection 

TcpConnection class 是muduo中最核心也是最复杂的class。TcpConnection class 是 唯一默认使用shared_ptr 来管理的class，也是唯一继承 enable_shared_from_this 的class，TcpConnection class 对象是短命对象，不同于 TcpServer 是长命对象。对于短命对象，其生命期的控制不一定完全被控制，例如：对方客户端断开了某个TCP socket ，其对应的服务端进程中的TcpConnection 对象（是一个堆对象）的生命也即将走到尽头。但是此时我们不能立刻 delete 这个对象，因为其他地方可能还持有其引用。用智能指针控制TcpConnection class 的生命期更安全。

TcpConnection 没有可以供用户直接调用的函数，TcpConnection class 有四个状态：kDisconnected, kConnecting, kConnected, kDisconnecting。TcpConnection class 使用channel 来获得socket 上的IO 事件，它自己处理writeable 事件，将 readable（接收数据） 事件通过messagecallbak 传给客户，TcpConnection class 拥有自己的Tcp socket, 析构函数中自动关闭这个socket。

TcpConnection class 表示的是**一次tcp连接，是不可再生的，一旦连接断开，这个对象就没用了**。TcpConnection class 也没有发起连接的功能，其中构造函数中的参数是已经建好连接的sockfd 。

TcpConnection 的状态图：

![TcpConnection的状态图](/_images/book-note/muduo/TcpConnection的状态图.JPG)

测试程序如下：

```cpp
#include "TcpServer.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include <stdio.h>

void onConnection(const muduo::TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    printf("onConnection(): new connection [%s] from %s\n",
           conn->name().c_str(),
           conn->peerAddress().toHostPort().c_str());
  }
  else
  {
    printf("onConnection(): connection [%s] is down\n",
           conn->name().c_str());
  }
}

void onMessage(const muduo::TcpConnectionPtr& conn,
               const char* data,
               ssize_t len)
{
  printf("onMessage(): received %zd bytes [%s] from connection [%s]\n",
         len, data,conn->name().c_str());
  
}

int main()
{
  printf("main(): pid = %d\n", getpid());

  muduo::InetAddress listenAddr(9981);
  muduo::EventLoop loop;

  muduo::TcpServer server(&loop, listenAddr);
  server.setConnectionCallback(onConnection);
  server.setMessageCallback(onMessage);
  server.start();

  loop.loop();
}
```

测试结果：

```bash
服务端：
[root@192 s05]# ./test8
main(): pid = 2488
20201129 23:43:48.207204Z  2488 INFO  TcpServer::newConnection [0.0.0.0:9981] - new connection [0.0.0.0:9981#1] from 127.0.0.1:53098 - TcpServer.cc:58
20201129 23:43:48.207274Z  2488 DEBUG TcpConnection TcpConnection::ctor[0.0.0.0:9981#1] at 0x13ac4e0 fd=6 - TcpConnection.cc:35
onConnection(): new connection [0.0.0.0:9981#1] from 127.0.0.1:53098
onMessage(): received 13 bytes [Hello World!
] from connection [0.0.0.0:9981#1]
20201129 23:44:11.412918Z  2488 INFO  TcpServer::newConnection [0.0.0.0:9981] - new connection [0.0.0.0:9981#2] from 127.0.0.1:53100 - TcpServer.cc:58
20201129 23:44:11.412935Z  2488 DEBUG TcpConnection TcpConnection::ctor[0.0.0.0:9981#2] at 0x13ace30 fd=7 - TcpConnection.cc:35
onConnection(): new connection [0.0.0.0:9981#2] from 127.0.0.1:53100
onMessage(): received 17 bytes [My name is Jason
] from connection [0.0.0.0:9981#2]

客户端1：
[root@192 ~]# nc 127.0.0.1 9981
Hello World!

客户端2：
[root@192 ~]# nc 127.0.0.1 9981
My name is Jason
```

## TcpConnection 断开连接

muduo服务器只有一种方法可以断开连接：被动关闭，即对方先关闭连接，本地read返回 0 ，触发关闭逻辑。处理过程：客户端断开TCP连接，这个事件会出发服务端 channel::handleRead() 调用，根据read() 返回0 调用closecallback() 函数来关闭连接。但是，在closecallback() 关闭连接的时候可能会析构channel 对象，这就造成了灾难。

解决方法：提供channel::tie(const boost::shared_ptr &) 函数，用来延长对象的生命期。并且muduo在Channel class中新增了CloseCallback事件的回调，并且断言（assert）在事件处理期间本Channel对象不会被析构。

```cpp
Channel::~Channel()
{
  assert(!eventHandling_);
  ......
}

void Channel::handleEvent(Timestamp receiveTime)
{
  std::shared_ptr<void> guard;
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

void Channel::handleEventWithGuard(Timestamp receiveTime)
{
  eventHandling_ = true;
  LOG_TRACE << reventsToString();
  if ((revents_ & POLLHUP) && !(revents_ & POLLIN))
  {
    if (logHup_)
    {
      LOG_WARN << "fd = " << fd_ << " Channel::handle_event() POLLHUP";
    }
    if (closeCallback_) closeCallback_();
  }
  ......
  eventHandling_ = false;
}
```

TcpConnection 断开连接函数调用流程如图所示：

![TcpConnection断开连接](/_images/book-note/muduo/TcpConnection断开连接.JPG)

TcpConnection新增了CloseCallback事件回调，供TcpServer和TcpClient使用，用于通知它们移除所持有的TcpConnectionPtr，这不是给普通用户使用的，普通用户继续使用ConnectionCallback。TcpConnection::handleRead会根据read的返回值分别调用messageCallback_、handleClose、handleError。

```cpp
void TcpConnection::handleRead(Timestamp receiveTime)
{
  loop_->assertInLoopThread();
  int savedErrno = 0;
  ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
  if (n > 0)
  {
    messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
  }
  else if (n == 0)
  {
    handleClose();
  }
  else
  {
    errno = savedErrno;
    LOG_SYSERR << "TcpConnection::handleRead";
    handleError();
  }
}
```

TcpConnection::handleClose的主要作用是调用closeCallback_，这个回调绑定到TcpServer::removeConnection，然后在removeConnection中先将TcpConnection 从 connections_Map 中删除，然后在 IO 事件循环线程中调用TcpConnection::connectDestroyed，它通知用户连接已断开。

最后，总结一下客户端主动断开连接时候的程序执行流程：

1. IO 事件循环class EventLoop::loop() 调用Poller::poll()，阻塞地关注套接字描述符上的事件；
2. 当客户端主动断开连接，导致系统调用::poll() 返回，处理活跃套接字对应的channel ；
3. Channel::handleEvent() , 对revents 中的事件进行分析，调用channel::closeCallback()；
4. Channel::closeCallback() 这个回调是与TcpConnection 中的handleClose() 关联的，在TcpConnection 的构造函数中进行的关联；handleClose回调函数中可能会析构channel 对象，因为channel对象的生命期由其owner class （Acceptor class） 来管理，而Acceptor class 的生命期由TcpServer 来管理，如果TcpServer 在removeConnection函数中析构了Acceptor ,那么channel对象也会被析构（程序在Channel::handleEvent() 中加入eventHandling_=true，且 Channel::~Channel()中assert(!eventHandling_) ，ASSERT ()是一个调试程序时经常使用的宏，在程序运行时它计算括号内的表达式，如果表达式为FALSE (0), 程序将报告错误，并终止执行。如果表达式不为0，则继续执行后面的语句。）；
5. TcpConnection::handleClose() 调用 TcpConnection::closeCallback_()，TcpConnection::closeCallback_() 与 TcpServer::removeConnection() 函数关联，在TcpServer 对象的构造函数中进行关联的。removeConnection() 最终实现将TcpConnection 从 connections_Map 中删除，且调用TcpConnection::connectDestroyed，它通知用户连接已断开；
​