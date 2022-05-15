# TcpClient剖析

[[toc]]

​# TcpClient

muduo用TcpClient发起连接，TcpClient有一个Connector连接器，TcpClient使用Connector发起连接, 连接建立成功后, 用socket创建TcpConnection来管理连接, 每个TcpClient class只管理一个TcpConnecction，连接建立成功后设置相应的回调函数。很显然，TcpClient用来管理客户端连接，真正连接交给Connector。

调用过程如下：TcpClient::connect()——>Connector::start()——>Connector::startInLoop——>Connector::connect()——>Connector::connecting()::

```cpp
void Connector::connect()
{
  int sockfd = sockets::createNonblockingOrDie(serverAddr_.family());
  int ret = sockets::connect(sockfd, serverAddr_.getSockAddr());
  int savedErrno = (ret == 0) ? 0 : errno;
  switch (savedErrno)
  {
    case 0:
    case EINPROGRESS:
    case EINTR:
    case EISCONN:
      connecting(sockfd);
 ...
}

void Connector::connecting()设置写回调函数且监听writable事件
```

TcpClient的特点：

1. TcpClient具备TcpConnection断开之后重新连接的功能，加上Connector具备反复尝试连接的功能，因此客户端和服务器的启动顺序无关紧要。可以先启动客户端，一旦服务器启动，半分钟之内即可恢复连接(由Connector::kMaxRetryDelayMs常数控制)；再客户端运行期间服务器可以重启，客户端也会自动重连。
2. 连接断开后初次重试的延迟时间是随机的，比方说服务器崩溃，它所有的客户端连接同时断开，然后0.5s之后同时再次发起连接，这样既可能造成SYN丢包，也可能给服务器带来短期大负载，影响其服务质量。因此每个TcpClient应该等待一段随机的时间(0.5~2s)，再重试，避免拥塞。
3. 发起连接的时候如果发生TCP SYN丢包，那么系统默认的重试间隔是3s，这期间不会返回错误码，而且这个间隔似乎不容易修改。如果需要缩短间隔，可以再用一个定时器，在0.5s或1s之后发起另一个链接。如果有需求的话，这个功能可以做到Connector中。

TcpClient中的成员变量有：

```cpp
EventLoop* loop_;
ConnectorPtr connector_; //用于主动发起连接
const string name_;

ConnectionCallback connectionCallback_; //连接建立回调函数
MessageCallback messageCallback_;       //消息到来回调函数
WriteCompleteCallback writeCompleteCallback_;//数据发送完毕回调函数

bool retry_;   // 重连，是指连接建立成功之后又断开的时候是否重连，通过enableRetry()设置
bool connect_; // atomic
int nextConnId_; //name_+nextConnId_用于标识一个连接
mutable MutexLock mutex_;

//connector_连接成功以后，得到一个TcpConnectionPtr
TcpConnectionPtr connection_;
```

其中，重要的成员变量是connector_(用于发起连接)、connection_(当连接成功建立后，创建TcpConnection对象用于通信)。

下面来介绍TcpClient的成员函数：

## 构造函数

```cpp
TcpClient::TcpClient(EventLoop* loop,
                     const InetAddress& serverAddr,
                     const string& nameArg)
  : loop_(CHECK_NOTNULL(loop)),
    connector_(new Connector(loop, serverAddr)),
    name_(nameArg),
    connectionCallback_(defaultConnectionCallback),
    messageCallback_(defaultMessageCallback),
    retry_(false),
    connect_(true),
    nextConnId_(1)
{
  //设置连接成功后的回调函数
  connector_->setNewConnectionCallback(
      std::bind(&TcpClient::newConnection, this, _1));
  // FIXME setConnectFailedCallback
  LOG_INFO << "TcpClient::TcpClient[" << name_
           << "] - connector " << get_pointer(connector_);
}
```

连接成功后，就会调用TcpClient::newConnection()函数 ：

```cpp
void TcpClient::newConnection(int sockfd)
{
  loop_->assertInLoopThread();
  InetAddress peerAddr(sockets::getPeerAddr(sockfd));
  char buf[32];
  snprintf(buf, sizeof buf, ":%s#%d", peerAddr.toIpPort().c_str(), nextConnId_);
  ++nextConnId_;
  string connName = name_ + buf;

  InetAddress localAddr(sockets::getLocalAddr(sockfd));
  //创建一个堆上局部TcpConnection对象，并用TcpClient的智能指针connection_保存起来
  TcpConnectionPtr conn(new TcpConnection(loop_,
                                          connName,
                                          sockfd,
                                          localAddr,
                                          peerAddr));
  //设置各种回调函数
  conn->setConnectionCallback(connectionCallback_); //连接建立
  conn->setMessageCallback(messageCallback_); //可读
  conn->setWriteCompleteCallback(writeCompleteCallback_);//可写
  conn->setCloseCallback( 
      std::bind(&TcpClient::removeConnection, this, _1)); // FIXME: unsafe
  {
    MutexLockGuard lock(mutex_);
    connection_ = conn;
  }
  //使用conn->connectEstablished()内部会关注可读事件
  conn->connectEstablished();
}
TcpConnection::connectEstablished()，连接成功后监听readable事件。

void TcpConnection::connectEstablished()
{
  loop_->assertInLoopThread();   //断言处于loop线程
  assert(state_ == kConnecting);   //断言处于未连接状态
  setState(kConnected);   //将状态设置为已连接
 
  channel_->tie(shared_from_this());   //将自身这个TcpConnection对象提升，由于是智能指针，所以不能直接用this
  //shared_from_this()之后引用计数+1，为3，但是shared_from_this()是临时对象，析构后又会减一，
  //而tie是weak_ptr并不会改变引用计数，所以该函数执行完之后引用计数不会更改
  
  channel_->enableReading();   //一旦连接成功就关注它的可读事件，加入到Poller中关注
  
  //回调之前设置的函数：conn->setConnectionCallback(connectionCallback_)
  connectionCallback_(shared_from_this());
}
```

下面是连接断开的函数：

```cpp
void TcpClient::removeConnection(const TcpConnectionPtr& conn)
{
  loop_->assertInLoopThread();
  assert(loop_ == conn->getLoop());
 
  {
    MutexLockGuard lock(mutex_);
    assert(connection_ == conn);
    connection_.reset();   //重置
  }
 
  //I/O线程中销毁
  loop_->queueInLoop(boost::bind(&TcpConnection::connectDestroyed, conn));
  if (retry_ && connect_)  //是否发起重连
  {
    LOG_INFO << "TcpClient::connect[" << name_ << "] - Reconnecting to "
             << connector_->serverAddress().toIpPort();
    //这里的重连是连接成功后断开的重连，所以实际上是重启
    connector_->restart();
  }
}
```

测试程序：

```cpp
/*
/home/muduo/muduo_recipes/recipes/reactor/s05/test8
/home/muduo/muduo_recipes/recipes/reactor/s12/test12
*/

#include "EventLoop.h"
#include "InetAddress.h"
#include "TcpClient.h"

#include "logging/Logging.h"

#include <boost/bind.hpp>

#include <utility>

#include <stdio.h>
#include <unistd.h>

std::string message = "Hello\n";

void onConnection(const muduo::TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    printf("onConnection(): new connection [%s] from %s\n",
           conn->name().c_str(),
           conn->peerAddress().toHostPort().c_str());
    conn->send(message);
  }
  else
  {
    printf("onConnection(): connection [%s] is down\n",
           conn->name().c_str());
  }
}

void onMessage(const muduo::TcpConnectionPtr& conn,
               muduo::Buffer* buf,
               muduo::Timestamp receiveTime)
{
  printf("onMessage(): received %zd bytes from connection [%s] at %s\n",
         buf->readableBytes(),
         conn->name().c_str(),
         receiveTime.toFormattedString().c_str());

  printf("onMessage(): [%s]\n", buf->retrieveAsString().c_str());
}

int main()
{
  muduo::EventLoop loop;
  muduo::InetAddress serverAddr("localhost", 9981);
  muduo::TcpClient client(&loop, serverAddr);

  client.setConnectionCallback(onConnection);
  client.setMessageCallback(onMessage);
  client.enableRetry();
  client.connect();
  loop.loop();
}
```

执行结果：

```bash
服务端：
[root@192 s05]# ./test8
main(): pid = 2527
20201202 23:25:27.680955Z  2527 INFO  TcpServer::newConnection [0.0.0.0:9981] - new connection [0.0.0.0:9981#1] from 127.0.0.1:50308 - TcpServer.cc:58
20201202 23:25:27.681025Z  2527 DEBUG TcpConnection TcpConnection::ctor[0.0.0.0:9981#1] at 0x117d4e0 fd=6 - TcpConnection.cc:35
onConnection(): new connection [0.0.0.0:9981#1] from 127.0.0.1:50308
onMessage(): received 6 bytes [Hello
] from connection [0.0.0.0:9981#1]


客户端：
[root@192 s12]# ./test13
20201202 23:25:27.680600Z  2528 ERROR sockets::fromHostPort - SocketsOps.cc:175
20201202 23:25:27.680761Z  2528 DEBUG Connector ctor[0x1c13430] - Connector.cc:31
20201202 23:25:27.680768Z  2528 INFO  TcpClient::TcpClient[0x7ffe384449e0] - connector 0x1c13430 - TcpClient.cc:62
20201202 23:25:27.680772Z  2528 INFO  TcpClient::connect[0x7ffe384449e0] - connecting to 0.0.0.0:9981 - TcpClient.cc:93
20201202 23:25:27.680943Z  2528 DEBUG TcpConnection TcpConnection::ctor[:127.0.0.1:9981#1] at 0x1c13d50 fd=5 - TcpConnection.cc:36
onConnection(): new connection [:127.0.0.1:9981#1] from 127.0.0.1:9981
20201202 23:26:35.887238Z  2528 INFO  TcpClient::connect[0x7ffe384449e0] - Reconnecting to 0.0.0.0:9981 - TcpClient.cc:162
onConnection(): connection [:127.0.0.1:9981#1] is down
20201202 23:26:35.887433Z  2528 DEBUG ~TcpConnection TcpConnection::dtor[:127.0.0.1:9981#1] at 0x1c13d50 fd=5 - TcpConnection.cc:50
20201202 23:26:35.887477Z  2528 WARN  Channel::handle_event() POLLHUP - Channel.cc:50
20201202 23:26:35.887482Z  2528 ERROR Connector::handleError - Connector.cc:188
20201202 23:26:35.887494Z  2528 INFO  Connector::retry - Retry connecting to 0.0.0.0:9981 in 500 milliseconds.  - Connector.cc:203
```
​