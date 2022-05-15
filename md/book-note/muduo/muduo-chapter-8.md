# Connector剖析

[[toc]]

​# Connector剖析

Connector负责主动发起连接，不负责创建socket，只负责连接的建立，外部调用Connector::start就可以发起连接，Connector具有重连的功能和停止连接的功能，连接成功建立后返回到TcpClient。

与Acceptor 相比少了一个 acceptSocket_ 成员，因为Connector 是创建一个新的sockfd 并connect 它，创建过程如下：Connector::start()-->Connector::startInLoop()-->void Connector::connect()。

```cpp
void Connector::connect()
{
  int sockfd = sockets::createNonblockingOrDie(serverAddr_.family()); // 创建非阻塞套接字
  int ret = sockets::connect(sockfd, serverAddr_.getSockAddr());
  int savedErrno = (ret == 0) ? 0 : errno;
  switch (savedErrno)
  {
    case 0:
    case EINPROGRESS:    // 非阻塞套接字，未连接成功返回码是EINPROGRESS表示正在连接
    case EINTR:
    case EISCONN:        // 连接成功
      connecting(sockfd); 
      break;
    ...
  }
}
```

再看Connector::connecting():

```cpp
void Connector::connecting(int sockfd)
{
  setState(kConnecting);
  assert(!channel_);
  channel_.reset(new Channel(loop_, sockfd));// Channel与sockfd关联
  // 设置可写回调函数，这时候如果socket没有错误，sockfd就处于可写状态
  channel_->setWriteCallback(
      std::bind(&Connector::handleWrite, this)); // FIXME: unsafe
  // 设置错误回调函数
  channel_->setErrorCallback(
      std::bind(&Connector::handleError, this)); // FIXME: unsafe

  // channel_->tie(shared_from_this()); is not working,
  // as channel_ is not managed by shared_ptr
  channel_->enableWriting();    // 让Poller关注可写事件
}
```

现在connnect(sockfd) 没有出错，sockfd 就处于可写状态（内核缓冲区不为满），而且poller 关注了可写事件，触发调用Connector::handleWrite()。

```cpp
void Connector::handleWrite()
{
    LOG_TRACE <<  "Connector::handleWrite " << state_;

     if (state_ == kConnecting)
    {
         int sockfd = removeAndResetChannel();    // 从poller中移除关注，并将channel置空
         // socket可写并不意味着连接一定建立成功
         // 还需要用getsockopt(sockfd, SOL_SOCKET, SO_ERROR, ...)再次确认一下。
         int err = sockets::getSocketError(sockfd);
        ......
         else     // 连接成功
        {
            setState(kConnected);
             if (connect_)
            {
                newConnectionCallback_(sockfd);      // 回调
            }

        }
    }
}
```

在handleWrite()里面需要removeAndResetChannel()，因此此时连接建立，故不用再关注channel的可写事件，最终会执行 channel_.reset();  即把channel析构了。此外函数需要返回sockfd, 让TcpConnection来接管。

连接成功后调用newConnectionCallback_(sockfd)，调用预先设置的回调函数。实际上 Connector 一般也不单独使用，作为TcpClient 的成员，但TcpClient 与 TcpServer 不同的是，它只有一个TcpConnection 成员。

```cpp
TcpServer: 
typedef std::map<string, TcpConnectionPtr> ConnectionMap;
std::unique_ptr<Acceptor> acceptor_; // avoid revealing Acceptor
ConnectionMap connections_;

TcpClient:
ConnectorPtr connector_; 
TcpConnectionPtr connection_ GUARDED_BY(mutex_);
```

即**一个TcpClient 对应一个TcpConnection 和一个 Connector；而一个TcpServer 对应一个TcpConnection 列表 和 一个 Acceptor**。

测试程序：

```cpp
///home/muduo/muduo_recipes/recipes/reactor/s11/test12.cc
#include "Connector.h"
#include "EventLoop.h"

#include <stdio.h>

muduo::EventLoop* g_loop;

void connectCallback(int sockfd)
{
  printf("connected.\n");
  g_loop->quit();
}

int main(int argc, char* argv[])
{
  muduo::EventLoop loop;
  g_loop = &loop;
  muduo::InetAddress addr("127.0.0.1", 9981);
  muduo::ConnectorPtr connector(new muduo::Connector(&loop, addr));
  connector->setNewConnectionCallback(connectCallback);
  connector->start();

  loop.loop();
}
```

执行结果：

```bash
服务端：
[root@192 s04]# ./test7
main(): pid = 2294
newConnection(): accepted a new connection from 127.0.0.1:43836

客户端：
[root@192 s11]# ./test12
20201201 23:23:51.688777Z  2295 DEBUG Connector ctor[0x822360] - Connector.cc:31
connected.
20201201 23:23:51.689096Z  2295 DEBUG ~Connector dtor[0x822360] - Connector.cc:36
```
