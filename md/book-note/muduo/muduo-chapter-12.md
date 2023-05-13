# muduo - 消息广播服务

[[toc]]

> 本文介绍如何使用muduo实现一个简单的 topic-based 消息广播服务。消息广播服务其实是“聊天室”的一个简单扩展，不过聊天的不是人，而是分布式系统中的程序。

# 消息广播

在分布式系统中，除了常用的 end-to-end 通信，还有一对多的广播通信。本文讨论的是基于 TCP 协议的应用层广播。示意图如下：

![Hub](/_images/book-note/muduo/Hub.JPG)

上图中圆角矩形代表程序，"Hub"是一个服务程序，不是网络集线器，它起到类似集线器的作用，故而得名。**Publisher 和 Subscriper 通过 TCP 协议与 Hub 程序通信。Publisher 把消息发到某个 topic 上，Subscribers 订阅该 topic，然后就能收到消息**。即 publisher 借助 hub 把消息广播给了多个 subscribers。这种 **pub/sub 结构的好处在于可以增加多个 Subscriber 而不用修改 Publisher**，从而一定程度上实现了“解耦”（也可以看成分布式的 observer pattern）。

设计模式中的observer pattern的核心代码如下：

```cpp
class Subject
{
	public:
		virtual ~Subject();
		virtual void Attach(Observer* obv);
		virtual void Detach(Observer* obv);
		virtual void Notify();
		virtual void SetState(const State& st) = 0;
		virtual State GetState() = 0;
	
	protected:
		Subject();
		
	private:
	list<Observer* >* _obvs;
};

class Observer
{
	public:
		virtual ~Observer();
		virtual void Update(Subject* sub) = 0;
		virtual void PrintInfo() = 0;
		
	protected:
		Observer();
		State _st;
		
	private:
};
————————————————————————————————————————————————————————————————————
	Subject* sub = new ConcreteSubject();
	Observer* o1 = new ConcreteObserverA(sub);//构造和析构时，调用Attach、Detach
	Observer* o2 = new ConcreteObserverB(sub);
	
	sub->SetState("old");
	sub->Notify();        //调用(*it)->Update(this)，转调PrintInfo打印信息
	sub->SetState("new"); 
	sub->Notify();
————————————————————————————————————————————————————————————————————
[root@192 base_use]# ./Observer
ConcreteObserverB observer....old
ConcreteObserverA observer....old
ConcreteObserverB observer....new
ConcreteObserverA observer....new
```


应用层广播在分布式系统中用处很大，举例如下：

1. 体育比分转播。有 8 片比赛场地正在进行羽毛球比赛，每个场地的计分程序把当前比分发送到各自的 topic 上（第 1 号场地发送到 court1，第 2 号发送到 court2，以此类推）。需要用到比分的程序（赛场的大屏幕显示，网上比分转播等等）自己订阅感兴趣的 topic ，就能及时收到最新比分数据。由于本文实现的不是 100% 可靠广播，那么**消息应该是 snapshot，而不是 incremental**。（换句话说，消息的内容是“现在是几比几”，而不是“刚才谁得分”。）

2. 负载监控。**每台机器上运行一个监控程序，周期性地把本机当前负载（CPU、网络、磁盘、温度）publish 到以 hostname 命名的 topic 上**，这样需要用到这些数据的程序只要在 hub 订阅相应的 topic 就能获得数据，无需与多台机器直接打交道。沿着这个思路，分布式系统中的服务程序也可以把自己的当前负载发布到 hub 上，供 load balancer 和 monitor 取用。

moduo中的消息广播协议如下：

* sub <topic> /r/n
    * 该命令表示订阅 ，以后该 topic 有任何内容更新都会发给这个 tcp 连接。在 sub 的时候，hub 会把该 上最近的消息发给此 subscriber。

* unsub <topic> /r/n
    * 该命令表示退订 <topic>
* pub <topic>/r/n <content>/r/n
    * 往 <topic>发送消息，内容为<content>。所有订阅了此<topic> 的 subscribers 会收到同样的消息“pub <topic>/r/n <content>/r/n”
muduo的程序代码中将hub拆分成四个部分：

* hub 服务程序：负责一对多的消息分发。它会记住每个 client 订阅了哪些 topic，只把消息发给特定的订阅者。
* pubsub 公共库：为了方便编写使用 hub 服务的应用程序，编写公共的client library，用来和 hub 打交道。这个 * library 可以订阅 topic、退订 topic、往指定 topic 发布消息。
* sub 程序：订阅一个或多个 topic，然后等待 hub 的数据。
* pub 程序：向某个 topic 发布一条消息，消息内容由命令行参数指定。
一个程序可以既是 publisher 又是 subscriber，而且 pubsub 库只用一个 tcp 连接。

PubSubClient的类成员定义：

```cpp
class PubSubClient : muduo::noncopyable
{
 public:
  typedef std::function<void (PubSubClient*)> ConnectionCallback;
  typedef std::function<void (const string& topic,
                              const string& content,
                              muduo::Timestamp)> SubscribeCallback;

  PubSubClient(muduo::net::EventLoop* loop,
               const muduo::net::InetAddress& hubAddr,
               const string& name);
  void start();
  void stop();
  bool connected() const;

  void setConnectionCallback(const ConnectionCallback& cb)
  { connectionCallback_ = cb; }

  bool subscribe(const string& topic, const SubscribeCallback& cb);
  void unsubscribe(const string& topic);
  bool publish(const string& topic, const string& content);

 private:
  void onConnection(const muduo::net::TcpConnectionPtr& conn);
  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp receiveTime);
  bool send(const string& message);

  muduo::net::TcpClient client_;
  muduo::net::TcpConnectionPtr conn_;
  ConnectionCallback connectionCallback_;
  SubscribeCallback subscribeCallback_;
}
```

其中主要成员函数为subscribe，unsubscribe，publish，这三个函数主要封装message内容，然后通过TcpConnection的send函数发送消息：

```cpp
bool PubSubClient::subscribe(const string& topic, const SubscribeCallback& cb)
{
  string message = "sub " + topic + "\r\n";
  subscribeCallback_ = cb;
  return send(message);
}

void PubSubClient::unsubscribe(const string& topic)
{
  string message = "unsub " + topic + "\r\n";
  send(message);
}


bool PubSubClient::publish(const string& topic, const string& content)
{
  string message = "pub " + topic + "\r\n" + content + "\r\n";
  return send(message);
}

bool PubSubClient::send(const string& message)
{
  bool succeed = false;
  if (conn_ && conn_->connected())
  {
    conn_->send(message);
    succeed = true;
  }
  return succeed;
}
```

Hub的类成员定义：

```cpp
class PubSubServer : noncopyable
{
 public:
  PubSubServer(muduo::net::EventLoop* loop,
               const muduo::net::InetAddress& listenAddr)
    : loop_(loop),
      server_(loop, listenAddr, "PubSubServer")
  {
    server_.setConnectionCallback(
        std::bind(&PubSubServer::onConnection, this, _1));
    server_.setMessageCallback(
        std::bind(&PubSubServer::onMessage, this, _1, _2, _3));
    loop_->runEvery(1.0, std::bind(&PubSubServer::timePublish, this));
  }

  void start()
  {
    server_.start();
  }

 private:
  void onConnection(const TcpConnectionPtr& conn)
  {
    if (conn->connected())
    {
      conn->setContext(ConnectionSubscription());
    //typedef std::set<string> ConnectionSubscription;
    //每次有连接进来，初始化空的set
    }
    else
    {
      const ConnectionSubscription& connSub
        = boost::any_cast<const ConnectionSubscription&>(conn->getContext());
      // subtle: doUnsubscribe will erase *it, so increase before calling.
      for (ConnectionSubscription::const_iterator it = connSub.begin();
           it != connSub.end();)
      {
        doUnsubscribe(conn, *it++);
      }
    }
  }

  void onMessage(const TcpConnectionPtr& conn,
                 Buffer* buf,
                 Timestamp receiveTime)
  {
    ParseResult result = kSuccess;
    while (result == kSuccess)
    {
      string cmd;
      string topic;
      string content;
      result = parseMessage(buf, &cmd, &topic, &content);
      if (result == kSuccess)//解析buf的内容
      {
        if (cmd == "pub")
        {
          doPublish(conn->name(), topic, content, receiveTime);
        }
        else if (cmd == "sub")
        {
          LOG_INFO << conn->name() << " subscribes " << topic;
          doSubscribe(conn, topic);
        }
        else if (cmd == "unsub")
        {
          doUnsubscribe(conn, topic);
        }
        else
        {
          conn->shutdown();
          result = kError;
        }
      }
      else if (result == kError)
      {
        conn->shutdown();
      }
    }
  }

  void timePublish()
  {
    Timestamp now = Timestamp::now();
    doPublish("internal", "utc_time", now.toFormattedString(), now);
  }

  void doSubscribe(const TcpConnectionPtr& conn,
                   const string& topic)
  {
    ConnectionSubscription* connSub
      = boost::any_cast<ConnectionSubscription>(conn->getMutableContext());

    connSub->insert(topic);
    getTopic(topic).add(conn);
    //根据topic的名字，获取对应的Topic对象，然后将conn通过add函数加入audiences_
    //Topic的成员std::set<TcpConnectionPtr> audiences_;
  }

  void doUnsubscribe(const TcpConnectionPtr& conn,
                     const string& topic)
  {
    LOG_INFO << conn->name() << " unsubscribes " << topic;
    getTopic(topic).remove(conn);
    // topic could be the one to be destroyed, so don't use it after erasing.
    ConnectionSubscription* connSub
      = boost::any_cast<ConnectionSubscription>(conn->getMutableContext());
    connSub->erase(topic);
  }

  void doPublish(const string& source,
                 const string& topic,
                 const string& content,
                 Timestamp time)
  {
    getTopic(topic).publish(content, time);
  }

  Topic& getTopic(const string& topic)
  {
    std::map<string, Topic>::iterator it = topics_.find(topic);
    if (it == topics_.end())
    {
      it = topics_.insert(make_pair(topic, Topic(topic))).first;
    }
    return it->second;
  }

  EventLoop* loop_;
  TcpServer server_;
  std::map<string, Topic> topics_;
};
```

其中主要逻辑在onMessage函数里，通过parseMessage判断pub、sub、unsub，从而执行对应的处理逻辑doPublish、doSubscribe、doUnsubscribe。

消息广播服务与observer Pattern中相同的思想：

* observer Pattern ：Subject对象维持着一个Observer的list，每次sub通过SetState改变状态后，可以通过Notify函数去遍历list中所有的obvs，调用其Update方法，最终转调GetState获取状态，并且PrintInfo打印状态信息。

* 消息广播服务：其中Hub的作用类似Subject，通过PubSubServer维持着一个Topic的map<string, Topic>，且Topic成员中维持着std::set<TcpConnectionPtr> audiences_。即PubSubServer通过接收TcpConnection的消息（从sub或pub发送过来的），作对应的doPublish、doSubscribe操作。

消息交互过程如下，代码见muduo中examples/hub：

```bash
[root@192 bin]# ./hub 9980
20201207 23:45:23.648955Z  2306 INFO  TcpServer::newConnection [PubSubSerubSubServer-0.0.0.0:9980#1] from 127.0.0.1:33008 - TcpServer.cc:80
20201207 23:45:23.649658Z  2306 INFO  PubSubServer-0.0.0.0:9980#1 subscri
20201207 23:45:23.649669Z  2306 INFO  PubSubServer-0.0.0.0:9980#1 subscri
20201207 23:45:37.978798Z  2306 INFO  TcpServer::newConnection [PubSubSerubSubServer-0.0.0.0:9980#2] from 127.0.0.1:33010 - TcpServer.cc:80
20201207 23:45:37.978827Z  2306 INFO  PubSubServer-0.0.0.0:9980#2 subscri
20201207 23:47:12.095250Z  2306 INFO  TcpServer::newConnection [PubSubSerubSubServer-0.0.0.0:9980#3] from 127.0.0.1:33012 - TcpServer.cc:80
20201207 23:47:12.095828Z  2306 INFO  TcpServer::removeConnectionInLoop [on PubSubServer-0.0.0.0:9980#3 - TcpServer.cc:109
20201207 23:48:17.200370Z  2306 INFO  TcpServer::newConnection [PubSubSerubSubServer-0.0.0.0:9980#4] from 127.0.0.1:33014 - TcpServer.cc:80
20201207 23:48:17.200486Z  2306 INFO  TcpServer::removeConnectionInLoop [on PubSubServer-0.0.0.0:9980#4 - TcpServer.cc:109


[root@192 bin]# ./sub 127.0.0.1 9980 music book
Usage: ./sub hub_ip:port topic [topic ...]
[root@192 bin]# ./sub 127.0.0.1:9980 music book
20201207 23:45:23.648594Z  2319 INFO  TcpClient::TcpClient[root@192.168.2x1B705D0 - TcpClient.cc:69
20201207 23:45:23.648769Z  2319 INFO  TcpClient::connect[root@192.168.2.2 127.0.0.1:9980 - TcpClient.cc:107
music: Raining
book: Redis

[root@192 bin]# ./sub 127.0.0.1:9980 book
20201207 23:45:37.978528Z  2328 INFO  TcpClient::TcpClient[root@192.168.2x1C025A0 - TcpClient.cc:69
20201207 23:45:37.978610Z  2328 INFO  TcpClient::connect[root@192.168.2.2 127.0.0.1:9980 - TcpClient.cc:107
book: Redis

[root@192 bin]# ./pub 127.0.0.1:9980 music "Raining"
20201207 23:47:12.094796Z  2337 INFO  TcpClient::TcpClient[root@192.168.2x1951570 - TcpClient.cc:69
20201207 23:47:12.094949Z  2337 INFO  TcpClient::connect[root@192.168.2.2 127.0.0.1:9980 - TcpClient.cc:107
20201207 23:47:12.095980Z  2337 INFO  TcpClient::~TcpClient[root@192.168.0x1951570 - TcpClient.cc:75
[root@192 bin]# ./pub 127.0.0.1:9980 book "Redis"
20201207 23:48:17.200157Z  2349 INFO  TcpClient::TcpClient[root@192.168.2x1415570 - TcpClient.cc:69
20201207 23:48:17.200205Z  2349 INFO  TcpClient::connect[root@192.168.2.2 127.0.0.1:9980 - TcpClient.cc:107
20201207 23:48:17.200585Z  2349 INFO  TcpClient::~TcpClient[root@192.168.0x1415570 - TcpClient.cc:75
```
​