
# ZeroMQ的经典例子
第一章我们简单试用了ZMQ的若干通信模式：请求-应答模式、发布-订阅模式、管道模式。这一章我们将学习更多在实际开发中会使用到的东西：

本章涉及的内容有：

* 节点协调
* 发布-订阅消息信封
* （半）持久订阅者和阈值（HWM）(阈值设置还未解决在例子中)
*  请求-应答模式下的消息代理(LRU路由)
*  请求-应答模式中使用套接字标识

---

## 节点协调

场景：气象信息模型的广播消息，考虑如何进行节点的协调，以保证客户端不会丢失最开始的那些消息。

下面是程序运行逻辑：
* 发布者知道预期的订阅者数量，这个数字可以任意指定；
* 发布者启动后会先等待所有订阅者进行连接，也就是节点协调。每个订阅者会使用另一个套接字来告知发布者自己已就绪；
* 当所有订阅者准备就绪后，发布者才开始发送消息。

这里我们会使用REQ-REP套接字来同步发布者和订阅者。具体代码参见syncpub.cpp和syncsub.cpp。

当REQ-REP请求完成时，我们仍无法保证SUB套接字已成功建立连接。除非使用inproc协议，否则对外连接的顺序是不一定的。因此，示例程序中使用了sleep(1)的方式来进行处理，随后再发送同步请求。

更可靠的模型可以是：

* 发布者打开PUB套接字，开始发送Hello消息（非数据）；
* 订阅者连接SUB套接字，当收到Hello消息后再使用REQ-REP套接字进行同步；
* 当发布者获得所有订阅者的同步消息后，才开始发送真正的数据。

## 发布-订阅消息信封

我们简单介绍了多帧消息，下面就来看看它的典型用法——消息信封。信封是指为消息注明来源地址，而不修改消息内容。

在发布-订阅模式中，信封包含了订阅信息，用以过滤掉不需要接收的消息。

如果你想要使用发布-订阅信封，就需要自行生成和设置。这个动作是可选的，我们在之前的示例中也没有使用到。在发布-订阅模式中使用信封可能会比较麻烦，但在现实应用中还是很有必要的，毕竟信封和消息的确是两块不想干的数据。具体代码参见psenvpub.cpp和psenvsub.cpp

**psenvsub: Pub-sub envelope publisher**

```c++

    while (1) {
        //  Write two messages, each with an envelope and content
        s_sendmore (publisher, "A");
        s_send (publisher, "We don't want to see this");
        s_sendmore (publisher, "B");
        s_send (publisher, "We would like to see this");
        sleep (1);
    }
}
```

**psenvsub: Pub-sub envelope subscriber**
```
    while (1) {
 
		//  Read envelope with address
		std::string address = s_recv (subscriber);
		//  Read message contents
		std::string contents = s_recv (subscriber);
		
        std::cout << "[" << address << "] " << contents << std::endl;
    }
```

## （半）持久订阅者和阈值（HWM）

所有的套接字类型都可以使用标识。如果你在使用PUB和SUB套接字，其中SUB套接字为自己声明了标识，那么，当SUB断开连接时，PUB会保留要发送给SUB的消息。

这种机制有好有坏。好的地方在于发布者会暂存这些消息，当订阅者重连后进行发送；不好的地方在于这样很容易让发布者因内存溢出而崩溃。

**如果你在使用持久化的SUB套接字（即为SUB设置了套接字标识），那么你必须设法避免消息在发布者队列中堆砌并溢出，应该使用阈值（HWM）来保护发布者套接字**。发布者的阈值会分别影响所有的订阅者。

我们可以运行一个示例来证明这一点，用第一章中的wuclient和wuserver具体，在wuclient中进行套接字连接前加入这一行：

```c++
    subscriber.setsockopt(ZMQ_IDENTITY, "Hello", 5);
```

具体代码参见durapub.cpp和durasub.cpp。

## 请求-应答模式下的消息代理

这一节我们将对如何使用ØMQ消息信封做一个回顾，并尝试编写一个通用的消息代理装置。我们会建立一个队列装置来连接多个client和worker，装置的路由算法可以由我们自己决定。这里我们选择最近最少使用算法，因为这和负载均衡一样比较实用。

首先让我们回顾一下经典的请求-应答模型，尝试用它建立一个不断增长的巨型服务网络。最基本的请求-应答模型是：

![11](/_images/middleware/zeromq/chapter3_11.png)

这个模型支持多个REP套接字，但如果我们想支持多个REQ套接字，就需要增加一个中间件，它通常是ROUTER和DEALER的结合体，简单将两个套接字之间的信息进行搬运，因此可以用现成的ZMQ_QUEUE装置来实现：

```
+--------+  +--------+  +--------+
| Client |  | Client |  | Client |
+--------+  +--------+  +--------+
|  REQ   |  |  REQ   |  |  REQ   |
+---+----+  +---+----+  +---+----+
    |           |           |
    +-----------+-----------+
                |
            +---+----+
            | ROUTER |
            +--------+
            | Device |
            +--------+
            | DEALER |
            +---+----+
                |
    +-----------+-----------+
    |           |           |
+---+----+  +---+----+  +---+----+
|  REP   |  |  REP   |  |  REP   |
+--------+  +--------+  +--------+
| Worker |  | Worker |  | Worker |
+--------+  +--------+  +--------+


Figure # - Stretched request-reply
```

这种结构的关键在于，ROUTER会将消息来自哪个REQ记录下来，生成一个信封。DEALER和REP套接字在传输消息的过程中不会丢弃或更改信封的内容，这样当消息返回给ROUTER时，它就知道应该发送给哪个REQ了。这个模型中的REP套接字是匿名的，并没有特定的地址，所以只能提供同一种服务。

上述结构中，对REP的路由我们使用了DEADER自带的负载均衡算法。但是，我们想用LRU算法来进行路由，这就要用到ROUTER-REQ模式：

![12](/_images/middleware/zeromq/chapter3_12.png)

这个ROUTER-ROUTER的LRU队列不能简单地在两个套接字间搬运消息，以下代码会比较复杂，不过在请求-应答模式中复用性很高。具体代码参见lruqueue.cpp。

这段程序有两个关键点：1、各个套接字是如何处理信封的；2、LRU算法。我们先来看信封的格式。

我们知道REQ套接字在发送消息时会向头部添加一个空帧，接收时又会自动移除。我们要做的就是在传输消息时满足REQ的要求，处理好空帧。另外还要注意，ROUTER会在所有收到的消息前添加消息来源的地址。

现在我们就将完整的请求-应答流程走一遍，我们将client套接字的标识设为“CLIENT”，worker的设为“WORKER”。以下是client发送的消息：

![13](/_images/middleware/zeromq/chapter3_13.png)

代理从ROUTER中获取到的消息格式如下：

![14](/_images/middleware/zeromq/chapter3_14.png)

代理会从LRU队列中获取一个空闲woker的地址，作为信封附加在消息之上，传送给ROUTER。注意要添加一个空帧。

![15](/_images/middleware/zeromq/chapter3_15.png)

REQ（worker）收到消息时，会将信封和空帧移去：

![16](/_images/middleware/zeromq/chapter3_16.png)

可以看到，worker收到的消息和client端ROUTER收到的消息是一致的。worker需要将该消息中的信封保存起来，只对消息内容做操作。

在返回的过程中：

* worker通过REQ传输给device消息\[client地址\]\[空帧\]\[应答内容\]；
* device从worker端的ROUTER中获取到\[worker地址\]\[空帧\]\[client地址\]\[空帧\]\[应答内容\]；
* device将worker地址保存起来，并发送\[client地址\]\[空帧\]\[应答内容\]给client端的ROUTER；
* client从REQ中获得到\[应答内容\]。

然后再看看LRU算法，它要求client和worker都使用REQ套接字，并正确的存储和返回消息信封，具体如下：

* 创建一组poll，不断地从backend（worker端的ROUTER）获取消息；只有当有空闲的worker时才从frontend（client端的ROUTER）获取消息；
 
* 循环执行poll
 
* 如果backend有消息，只有两种情况：1）READY消息（该worker已准备好，等待分配）；2）应答消息（需要转发给client）。两种情况下我们都会保存worker的地址，放入LRU队列中，如果有应答内容，则转发给相应的client。

* 如果frontend有消息，我们从LRU队列中取出下一个worker，将该请求发送给它。这就需要发送[worker地址][空帧][client地址][空帧][请求内容]到worker端的ROUTER。

我们可以对该算法进行扩展，如在worker启动时做一个自我测试，计算出自身的处理速度，并随READY消息发送给代理，这样代理在分配工作时就可以做相应的安排。

## 请求-应答模式中使用套接字标识

ROUTER是怎么标识消息的来源的？答案当然是套接字的标识。我们之前讲过，一个套接字可能是瞬时的，它所连接的套接字（如ROUTER）则会给它生成一个标识，与之相关联。一个套接字也可以显式地给自己定义一个标识，这样其他套接字就可以直接使用了。

这是一个瞬时的套接字，ROUTER会自动生成一个UUID来标识消息的来源。

![3](/_images/middleware/zeromq/chapter3_3.png)

这是一个持久的套接字，标识由消息来源自己指定。

![4](/_images/middleware/zeromq/chapter3_4.png)

下面让我们在实例中观察上述两种操作。下列程序会打印出ROUTER从两个REP套接字中获得的消息，其中一个没有指定标识，另一个指定了“Hello”作为标识。

**identity.cpp**

```c++
#include <zmq.hpp>
#include "zhelpers.hpp"

int main () {
    zmq::context_t context(1);

    zmq::socket_t sink(context, ZMQ_ROUTER);
    sink.bind( "inproc://example");

    //  First allow 0MQ to set the identity
    zmq::socket_t anonymous(context, ZMQ_REQ);
    anonymous.connect( "inproc://example");

    s_send (anonymous, "ROUTER uses a generated UUID");
    s_dump (sink);

    //  Then set the identity ourself
    zmq::socket_t identified (context, ZMQ_REQ);
    identified.setsockopt( ZMQ_IDENTITY, "Hello", 5);
    identified.connect( "inproc://example");

    s_send (identified, "ROUTER socket uses REQ's socket identity");
    s_dump (sink);

    return 0;
}
```

运行结果：

```
[root@192 C++]# ./identity
----------------------------------------
[005]006bffffff8b4567
[000]
[01c]ROUTER uses a generated UUID
----------------------------------------
[005]Hello
[000]
[028]ROUTER socket uses REQ's socket identity
```

## 客户端的可靠性设计（懒惰海盗模式）
基本的可靠队列（简单海盗模式）:
运行上述事例，启动多个worker，一个client，以及一个队列装置，顺序随意。你可以看到worker最终都会崩溃或死亡，client则多次重试并最终放弃。装置从来不会停止，你可以任意重启worker和client，这个模型可以和任意个worker、client交互。

执行结果：
```
[root@localhost zeromq]# ./spworker
I: (4BFA-5A56) worker ready
I: (4BFA-5A56) normal reply - I'm client Hello.
I: (4BFA-5A56) normal reply - I'm client Hello.
I: (4BFA-5A56) normal reply - I'm client Hello.
I: (4BFA-5A56) simulating a crash

[root@localhost zeromq]# ./spqueue

[root@localhost zeromq]# ./sp_client
Connecting to hello world server...
client Send I'm client Hello. 0
```
![3](/_images/middleware/zeromq/chapter4_1.png)

### 基本的可靠队列（简单海盗模式）

在第二种模式中，我们使用一个队列装置来扩展上述的“懒惰的海盗”模式，使客户端能够透明地和多个服务端通信。这里的服务端可以定义为worker。我们可以从最基础的模型开始，分阶段实施这个方案。

在所有的海盗模式中，worker是无状态的，或者说存在着一个我们所不知道的公共状态，如共享数据库。队列装置的存在意味着worker可以在client毫不知情的情况下随意进出。一个worker死亡后，会有另一个worker接替它的工作。这种拓扑结果非常简洁，但唯一的缺点是队列装置本身会难以维护，可能造成单点故障。

在第三章中，队列装置的基本算法是最近最少使用算法。那么，如果worker死亡或阻塞，我们需要做些什么？答案是很少很少。我们已经在client中加入了重试的机制，所以，使用基本的LRU队列就可以运作得很好了。这种做法也符合ZMQ的逻辑，所以我们可以通过在点对点交互中插入一个简单的队列装置来扩展它：

![2](/_images/middleware/zeromq/chapter4_2.png)

执行结果：
```
[root@localhost zeromq]# ./spworker
I: (4BFA-5A56) worker ready
I: (4BFA-5A56) normal reply - I'm client Hello.
I: (4BFA-5A56) normal reply - I'm client Hello.
I: (4BFA-5A56) normal reply - I'm client Hello.
I: (4BFA-5A56) simulating a crash

[root@localhost zeromq]# ./spqueue

[root@localhost zeromq]# ./sp_client
Connecting to hello world server...
client Send I'm client Hello. 0
```

## 健壮的可靠队列（偏执海盗模式）

“简单海盗队列”模式工作得非常好，主要是因为它只是两个现有模式的结合体。不过，它也有一些缺点：

* 该模式无法处理队列的崩溃或重启。client会进行重试，但worker不会重启。虽然ZMQ会自动重连worker的套接字，但对于新启动的队列装置来说，由于worker并没有发送“已就绪”的消息，所以它相当于是不存在的。为了解决这一问题，我们需要从队列发送心跳给worker，这样worker就能知道队列是否已经死亡。

* 队列没有检测worker是否已经死亡，所以当worker在处于空闲状态时死亡，队列装置只有在发送了某个请求之后才会将该worker从队列中移除。这时，client什么都不能做，只能等待。这不是一个致命的问题，但是依然是不够好的。所以，我们需要从worker发送心跳给队列装置，从而让队列得知worker什么时候消亡。

我们使用一个名为“偏执的海盗模式”来解决上述两个问题。

![3](/_images/middleware/zeromq/chapter4_3.png)
```
./ppqueue
./ppwork
I: (0D57-9062) worker heartbeat
I: (0D57-9062) worker heartbeat
I: (0D57-9062) worker heartbeat
I: (0D57-9062) worker heartbeat
I: (0D57-9062) worker heartbeat

然后启动./pp_lpclient 模拟失败：
[root@192 zeromq]# ./pp_lpclient
I: connecting to server...
W: no response from server, retrying...
I: connecting to server...
W: no response from server, retrying...
I: connecting to server...
E: server seems to be offline, abandoning

然后手动kill  ./ppqueue
ppwork就会一直不断调整时间去重连，最后还有问题：

W: (0D57-9062) heartbeat failure, can't reach queue
W: (0D57-9062) reconnecting in 1000 msec...
I: (D22E-44C5) worker ready
I: (D22E-44C5) worker heartbeat
I: (D22E-44C5) worker heartbeat
I: (D22E-44C5) worker heartbeat
W: (D22E-44C5) heartbeat failure, can't reach queue
W: (D22E-44C5) reconnecting in 2000 msec...
I: (C18A-C809) worker ready
I: (C18A-C809) worker heartbeat
I: (C18A-C809) worker heartbeat
I: (C18A-C809) worker heartbeat
W: (C18A-C809) heartbeat failure, can't reach queue
W: (C18A-C809) reconnecting in 4000 msec...

........
W: (04A7-5BB2) heartbeat failure, can't reach queue
W: (04A7-5BB2) reconnecting in 32000 msec...
I: (4972-9816) worker ready
I: (4972-9816) worker heartbeat
I: (4972-9816) worker heartbeat
I: (4972-9816) worker heartbeat
W: (4972-9816) heartbeat failure, can't reach queue
W: (4972-9816) reconnecting in 32000 msec...
I: (631F-3335) worker ready
I: (631F-3335) worker heartbeat
I: (631F-3335) worker heartbeat

现在改写了16000 msec 时即break ppwork
```

