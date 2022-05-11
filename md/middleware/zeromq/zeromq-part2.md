
# 第二章 ZeroMQ进阶
第一章我们简单试用了ZMQ的若干通信模式：请求-应答模式、发布-订阅模式、管道模式。这一章我们将学习更多在实际开发中会使用到的东西：

本章涉及的内容有：

* 零的哲学
* 套接字API
* 使用套接字构建拓扑结构
* 使用套接字传递数据
* 单播传输
* ZMQ不只是数据传输
* I/O线程
* 核心消息模式
* 消息的使用方法
* 处理多个套接字
* 多帧消息
* 中间件和装置
* 发布-订阅代理服务
* 请求-应答代理
* 内置装置
* ZMQ多线程编程
* 瞬时套接字和持久套接字
---

## 零的哲学

一开始ZMQ代表零中间件、零延迟，同时，它又有了新的含义：零管理、零成本、零浪费。总的来说，零表示最小、最简，这是贯穿于该项目的哲理。我们致力于减少复杂程度，提高易用性。

## 套接字API

ZMQ提供了一套类似于BSD套接字的API，但将很多消息处理机制的细节隐藏了起来，你会逐渐适应这种变化，并乐于用它进行编程。套接字事实上是用于网络编程的标准接口，ZMQ之所那么吸引人眼球，原因之一就是它是建立在标准套接字API之上。因此，ZMQ的套接字操作非常容易理解，其生命周期主要包含四个部分：

* 创建和销毁套接字：zmq_socket(), zmq_close()
* 配置和读取套接字选项：zmq_setsockopt(), zmq_getsockopt()
* 为套接字建立连接：zmq_bind(), zmq_connect()
* 发送和接收消息：zmq_send(), zmq_recv()

实际使用了，利用C++版本的封装的函数库，只需包含#include "zhelpers.hpp"。
* 创建和销毁套接字：使用zmq::socket_t来创建一个socket对象
* 配置和读取套接字选项：subscriber.setsockopt(),subscriber.getsockopt()
* 为套接字建立连接：subscriber.connect(), publisher.bind()
* 发送和接收消息：s_send(), s_recv()

```
zmq::socket_t subscriber(context, ZMQ_SUB);
subscriber.connect("tcp://localhost:5561");
subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

zmq::socket_t publisher(context, ZMQ_PUB);
publisher.bind("tcp://*:5561");
```

## 使用套接字构建拓扑结构


在连接两个节点时，其中一个需要使用zmq_bind()，另一个则使用zmq_connect()。通常来讲，使用zmq_bind()连接的节点称之为服务端，它有着一个较为固定的网络地址；使用zmq_connect()连接的节点称为客户端，其地址不固定。我们会有这样的说法：绑定套接字至端点；连接套接字至端点。端点指的是某个广为周知网络地址。

ZMQ连接和传统的TCP连接是有区别的，主要有：

* 使用多种协议，inproc（进程内）、ipc（进程间）、tcp、pgm（广播）、epgm；
* **当客户端使用zmq_connect()时连接就已经建立了，并不要求该端点已有某个服务使用zmq_bind()进行了绑定；**
* **连接是异步的，并由一组消息队列做缓冲；**
* 连接会表现出某种消息模式，这是由创建连接的套接字类型决定的；
* 一个套接字可以有**多个输入和输出连接**；
* ZMQ没有提供类似zmq_accept()的函数，因为当套接字绑定至端点时它就自动开始接受连接了；
* 应用程序无法直接和这些连接打交道，因为它们是被封装在ZMQ底层的。

在很多架构中都使用了类似于C/S的架构。服务端组件式比较稳定的，而客户端组件则较为动态，来去自如。所以说，服务端地址对客户端而言往往是可见的，反之则不然。这样一来，架构中应该将哪些组件作为服务端（使用zmq_bind()），哪些作为客户端（使用zmq_connect()），就很明显了。同时，这需要和你使用的套接字类型相联系起来，我们下文会详细讲述。

让我们试想一下，如果先打开了客户端，后打开服务端，会发生什么？传统网络连接中，我们打开客户端时一定会收到系统的报错信息，但ZMQ让我们能够自由地启动架构中的组件。**当客户端使用zmq_connect()连接至某个端点时，它就已经能够使用该套接字发送消息了。如果这时，服务端启动起来了，并使用zmq_bind()绑定至该端点，ZMQ将自动开始转发消息。**

服务端节点可以仅使用一个套接字就能绑定至多个端点。也就是说，它能够使用不同的协议来建立连接：

```
zmq_bind (socket, "tcp://*:5555");
zmq_bind (socket, "tcp://*:9999");
zmq_bind (socket, "ipc://myserver.ipc");
```
当然，你不能多次绑定至同一端点，这样是会报错的。

每当有客户端节点使用zmq_connect()连接至上述某个端点时，服务端就会自动创建连接。ZMQ没有对连接数量进行限制。此外，**客户端节点也可以使用一个套接字同时建立多个连接**。

大多数情况下，哪个节点充当服务端，哪个作为客户端，是网络架构层面的内容，而非消息流问题。不过也有一些特殊情况（如失去连接后的消息重发），同一种套接字使用绑定和连接是会有一些不同的行为的。

所以说，当我们在设计架构时，应该遵循“服务端是稳定的，客户端是灵活的“原则，这样就不太会出错。

**套接字是有类型的，套接字类型定义了套接字的行为，它在发送和接收消息时的规则等。**你可以将不同种类的套接字进行连接，如PUB-SUB组合，这种组合称之为发布-订阅模式，其他组合也会有相应的模式名称，我们会在下文详述。

正是因为套接字可以使用不同的方式进行连接，才构成了ZMQ最基本的消息队列系统。我们还可以在此基础之上建立更为复杂的装置、路由机制等，下文会详述。**总的来说，ZMQ为你提供了一套组件，供你在网络架构中拼装和使用。** 


## 使用套接字传递数据

发送和接收消息使用的是zmq_send()和zmq_recv()这两个函数。虽然函数名称看起来很直白，但由于ZMQ的I/O模式和传统的TCP协议有很大不同，因此还是需要花点时间去理解的。

![1](/_images/middleware/zeromq/chapter2_1.png)

让我们看一看**TCP套接字和ZMQ套接字之间在传输数据方面的区别:**

* **ZMQ套接字传输的是消息，而不是字节（TCP）或帧（UDP）。** 消息指的是一段指定长度的二进制数据块，我们下文会讲到消息，这种设计是为了性能优化而考虑的，所以可能会比较难以理解。
* ZMQ套接字在**后台进行I/O操作，也就是说无论是接收还是发送消息，它都会先传送到一个本地的缓冲队列，** 这个内存队列的大小是可以配置的。
* ZMQ套接字可以和多个套接字进行连接（如果套接字类型允许的话）。TCP协议只能进行点对点的连接，而ZMQ则可以进行一对多（类似于无线广播）、多对多（类似于邮局）、多对一（类似于信箱），当然也包括一对一的情况。
* ZMQ套接字可以发送消息给多个端点（扇出模型），或从多个端点中接收消息（扇入模型）

![2](/_images/middleware/zeromq/chapter2_2.png)

所以，向套接字写入一个消息时可能会将消息发送给很多节点，相应的，套接字又会从所有已建立的连接中接收消息。zmq_recv()方法使用了公平队列的算法来决定接收哪个连接的消息。

调用zmq_send()方法时其实并没有真正将消息发送给套接字连接。消息会在一个内存队列中保存下来，并由后台的I/O线程异步地进行发送。如果不出意外情况，这一行为是非阻塞的。所以说，即便zmq_send()有返回值，并不能代表消息已经发送。当你在用zmq_msg_init_data()初始化消息后，你不能重用或是释放这条消息，否则ZMQ的I/O线程会认为它在传输垃圾数据。这对初学者来讲是一个常犯的错误，下文我们会讲述如何正确地处理消息。

## 单播传输

ZMQ提供了一组单播传输协议（inporc, ipc, tcp），和两个广播协议（epgm, pgm）。

一般而言我们会使用**tcp**作为传输协议，这种TCP连接是可以脱机运作的，它灵活、便携、且足够快速。为什么称之为脱机，是因为ZMQ中的TCP连接不需要该端点已经有某个服务进行了绑定，客户端和服务端可以随时进行连接和绑定，这对应用程序而言都是透明的。

<font color="red">**进程间协议**</font>，即**ipc**，和tcp的行为差不多，但已从网络传输中抽象出来，不需要指定IP地址或者域名。这种协议很多时候会很方便，本指南中的很多示例都会使用这种协议。ZMQ中的ipc协议同样可以是脱机的，但有一个缺点——无法在Windows操作系统上运作，这一点也许会在未来的ZMQ版本中修复。我们一般会在端点名称的末尾附上**.ipc的扩展名上**，在UNIX系统上，使用ipc协议还需要注意权限问题。你还需要保证所有的程序都能够找到这个ipc端点。

进程内协议，即**inproc**，可以在同一个进程的不同线程之间进行消息传输，它比ipc或tcp要快得多。这种协议有一个要求，必须先绑定到端点，才能建立连接，即先启动服务端线程，绑定至端点，后启动客户端线程，连接至端点。

## ZMQ不只是数据传输

ZMQ不只是一个数据传输的工具，而是在现有通信协议之上建立起来的新架构。它的数据帧和现有的协议并不兼容，如下面是一个HTTP请求和ZMQ请求的对比，同样使用的是TCP/IPC协议：

![3](/_images/middleware/zeromq/chapter2_3.png)

HTTP请求使用CR-LF（换行符）作为信息帧的间隔，而ZMQ则使用指定长度来定义帧：

![4](/_images/middleware/zeromq/chapter2_4.png)

所以说，你的确是可以用ZMQ来写一个类似于HTTP协议的东西，但是这并不是HTTP。

不过，如果有人问我如何更好地使用ZMQ建立一个新的服务，我会给出一个不错的答案，那就是：你可以自行设计一种通信协议，用ZMQ进行连接，使用不同的语言提供服务和扩展，可以在本地，亦可通过远程传输。赛德•肖的[Mongrel2](http://www.mongrel2.org)网络服务的架构就是一个很好的示例。

## I/O线程

我们提过ZMQ是通过后台的I/O线程进行消息传输的。**一个I/O线程已经足以处理多个套接字的数据传输要求**，当然，那些极端的应用程序除外。这也就是我们在创建上下文时传入的1所代表的意思：

```c++
zmq::context_t context(1);
```

**ZMQ应用程序和传统应用程序的区别之一就是你不需要为每个套接字都创建一个连接。单个ZMQ套接字可以处理所有的发送和接收任务。**如，当你需要向一千个订阅者发布消息时，使用一个套接字就可以了；当你需要向二十个服务进程分发任务时，使用一个套接字就可以了；当你需要从一千个网页应用程序中获取数据时，也是使用一个套接字就可以了。

这一特性可能会颠覆网络应用程序的编写步骤，传统应用程序每个进程或线程会有一个远程连接，它又只能处理一个套接字。ZMQ让你打破这种结构，使用一个线程来完成所有工作，更易于扩展。

## 核心消息模式
ZMQ的核心消息模式有：

* **请求-应答模式** 将一组服务端和一组客户端相连，用于远程过程调用或任务分发。
* **发布-订阅模式** 将一组发布者和一组订阅者相连，用于数据分发。
* **管道模式** 使用扇入或扇出的形式组装多个节点，可以产生多个步骤或循环，用于构建并行处理架构。
* **排他对接模式** 将两个套接字一对一地连接起来。

zmq_socket()函数的说明页中有对所有消息模式的说明，比较清楚，因此值得研读几次。([参考使用手册](http://api.zeromq.org))我们会介绍每种消息模式的内容和应用场景。

以下是合法的套接字连接-绑定对（一端绑定、一端连接即可）：

* PUB - SUB
* REQ - REP
* REQ - ROUTER
* DEALER - REP
* DEALER - ROUTER
* DEALER - DEALER
* ROUTER - ROUTER
* PUSH - PULL
* PAIR - PAIR

## 消息的使用方法

ZMQ的传输单位是消息，即一个二进制块。**你可以使用任意的序列化工具，如谷歌的Protocal Buffers、XDR、JSON等，将内容转化成ZMQ消息。**不过这种转化工具最好是便捷和快速的，这个请自己衡量。

在内存中，ZMQ消息由zmq_msg_t结构表示（每种语言有特定的表示）。在C语言中使用ZMQ消息时需要注意以下几点：

* 你需要创建和传递zmq_msg_t对象，而不是一组数据块；
* 读取消息时，先用zmq_msg_init()初始化一个空消息，再将其传递给zmq_recv()函数；
* 写入消息时，先用zmq_msg_init_size()来创建消息（同时也已初始化了一块内存区域），然后用memcpy()函数将信息拷贝到该对象中，最后传给zmq_send()函数；
* 释放消息（并不是销毁）时，使用zmq_msg_close()函数，它会将对消息对象的引用删除，最终由ZMQ将消息销毁；
* 获取消息内容时需使用zmq_msg_data()函数；若想知道消息的长度，可以使用zmq_msg_size()函数；
* 至于zmq_msg_move()、zmq_msg_copy()、zmq_msg_init_data()函数，在充分理解手册中的说明之前，建议不好贸然使用。

以下是一段处理消息的典型代码，如果之前的代码你有看的话，那应该会感到熟悉。这段代码其实是从zhelpers.h文件中抽出的：

```c
//  从套接字中获取ZMQ字符串，并转换为C语言字符串
static char *
s_recv (void *socket) {
    zmq_msg_t message;
    zmq_msg_init (&message);
    zmq_recv (socket, &message, 0);
    int size = zmq_msg_size (&message);
    char *string = malloc (size + 1);
    memcpy (string, zmq_msg_data (&message), size);
    zmq_msg_close (&message);
    string [size] = 0;
    return (string);
}

//  将C语言字符串转换为ZMQ字符串，并发送给套接字
static int
s_send (void *socket, char *string) {
    int rc;
    zmq_msg_t message;
    zmq_msg_init_size (&message, strlen (string));
    memcpy (zmq_msg_data (&message), string, strlen (string));
    rc = zmq_send (socket, &message, 0);
    assert (!rc);
    zmq_msg_close (&message);
    return (rc);
}
```

同理，C++的对应处理函数来自zhelpers.hpp
```c++
static std::string
s_recv (zmq::socket_t & socket) {

    zmq::message_t message;
    socket.recv(&message);

    return std::string(static_cast<char*>(message.data()), message.size());
}

static bool
s_send (zmq::socket_t & socket, const std::string & string) {

    zmq::message_t message(string.size());
    memcpy(message.data(), string.data(), string.size());

    bool rc = socket.send(message);
    return (rc);
}
```

你可以对以上代码进行扩展，让其支持发送和接受任一长度的数据。

**需要注意的是，当你将一个消息对象传递给zmq_send()函数后，该对象的长度就会被清零，因此你无法发送同一个消息对象两次，也无法获得已发送消息的内容。**

如果你想发送同一个消息对象两次，就需要在发送第一次前新建一个对象，使用zmq_msg_copy()函数进行拷贝。这个函数不会拷贝消息内容，只是拷贝引用。然后你就可以再次发送这个消息了（或者任意多次，只要进行了足够的拷贝）。当消息最后一个引用被释放时，消息对象就会被销毁。

ZMQ支持多帧消息，即在一条消息中保存多个消息帧。关于消息，还有一些需要注意的地方：

* ZMQ的消息是作为一个整体来收发的，你不会只收到消息的一部分；
* ZMQ不会立即发送消息，而是有一定的延迟；
* 你可以**发送0字节长度的消息，作为一种信号；** 
* 消息必须能够在内存中保存，如果你想发送文件或超长的消息，就需要将他们切割成小块，在独立的消息中进行发送；
* 必须使用zmq_msg_close()函数来关闭消息，但在一些会在变量超出作用域时自动释放消息对象的语言中除外(C++的message_t对象)。

## 处理多个套接字

在之前的示例中，主程序的循环体内会做以下几件事：

1. 等待套接字的消息；
2. 处理消息；
3. 返回第一步。

如果我们想要读取多个套接字中的消息呢？最简单的方法是将套接字连接到多个端点上，让ZMQ使用公平队列的机制来接受消息。如果不同端点上的套接字类型是一致的，那可以使用这种方法。但是，如果一个套接字的类型是PULL，另一个是PUB怎么办？如果现在开始混用套接字类型，那将来就没有可靠性可言了。

正确的方法应该是使用zmq_poll()函数。更好的方法是将zmq_poll()包装成一个框架，编写一个事件驱动的反应器，但这个就比较复杂了，我们这里暂不讨论。

我们先不使用zmq_poll()，而用NOBLOCK（非阻塞）的方式来实现从多个套接字读取消息的功能。下面将气象信息服务和并行处理这两个示例结合起来：

**msreader: Multiple socket reader**
```c++
//
//  Reading from multiple sockets in C++
//  This version uses a simple recv loop
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include "zhelpers.hpp"


int main (int argc, char *argv[])
{
    //  Prepare our context and sockets
    zmq::context_t context(1);

    //  Connect to task ventilator
    zmq::socket_t receiver(context, ZMQ_PULL);
    receiver.connect("tcp://localhost:5557");

    //  Connect to weather server
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "10001 ", 6);

    //  Process messages from both sockets
    //  We prioritize traffic from the task ventilator
    while (1) {
    	
        //  Process any waiting tasks
        bool rc;
        do {
        	zmq::message_t task;
            if ((rc = receiver.recv(&task, ZMQ_NOBLOCK)) == true) {
                //  process task
            }
        } while(rc == true);
        
        //  Process any waiting weather updates
        do {
            zmq::message_t update;
            if ((rc = subscriber.recv(&update, ZMQ_NOBLOCK)) == true) {
                //  process weather update

            }
        } while(rc == true);
        
        //  No activity, so sleep for 1 msec
        s_sleep(1);
    }
    return 0;
}
```

你可以做一个改进，轮流处理消息，正如ZMQ内部做的公平队列机制一样。下面，让我们看看如何用zmq_poll()来实现同样的功能：

**mspoller: Multiple socket poller**

```c++
//
//  Reading from multiple sockets in C++
//  This version uses zmq_poll()
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include "zhelpers.hpp"


int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    //  Connect to task ventilator
    zmq::socket_t receiver(context, ZMQ_PULL);
    receiver.connect("tcp://localhost:5557");

    //  Connect to weather server
    zmq::socket_t subscriber(context, ZMQ_SUB);
	subscriber.connect("tcp://localhost:5556");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "10001 ", 6);

    //  Initialize poll set
    //  初始化轮询对象
    zmq::pollitem_t items [] = {
        { receiver, 0, ZMQ_POLLIN, 0 },
        { subscriber, 0, ZMQ_POLLIN, 0 }
    };
    //  Process messages from both sockets
    while (1) {
        zmq::message_t message;
        zmq::poll (&items [0], 2, -1);
        
        if (items [0].revents & ZMQ_POLLIN) {
            receiver.recv(&message);
            //  Process task
        }
        if (items [1].revents & ZMQ_POLLIN) {
            subscriber.recv(&message);
            //  Process weather update
        }
    }
    return 0;
}
```

## 多帧消息

ZMQ消息可以包含多个帧，这在实际应用中非常常见，特别是那些有关“信封”的应用，我们下文会谈到。我们这一节要讲的是如何正确地收发多帧消息。

多帧消息的每一帧都是一个zmq_msg结构，也就是说，当你在收发含有五个帧的消息时，你需要处理五个zmq_msg结构。你可以将这些帧放入一个数据结构中，或者直接一个个地处理它们。

下面的代码演示如何发送多帧消息：

```c++
s_sendmore(publisher, "music");
        
s_send(publisher, "<Rain>");

```

然后我们看看如何接收并处理这些消息，**这段代码对单帧消息和多帧消息都适用：**

```c++
 while (1) 
 {
    zmq::message_t message;
    int64_t more;
    size_t more_size = sizeof (more);

    //  Process all parts of the message
    frontend.recv(&message);
    frontend.getsockopt( ZMQ_RCVMORE, &more, &more_size);
    backend.send(message, more? ZMQ_SNDMORE: 0);
    if (!more)
        break;      //  Last message part
}
```

关于多帧消息，你需要了解的还有：

* 在发送多帧消息时，只有当最后一帧提交发送了，整个消息才会被发送；
* 如果使用了zmq_poll()函数，当收到了消息的第一帧时，其它帧其实也已经收到了；
* 多帧消息是整体传输的，不会只收到一部分；
* 多帧消息的每一帧都是一个zmq_msg结构；
* 无论你是否检查套接字的ZMQ_RCVMORE选项，你都会收到所有的消息；
* 发送时，ZMQ会将开始的消息帧缓存在内存中，直到收到最后一帧才会发送；
* 我们无法在发送了一部分消息后取消发送，只能关闭该套接字。

## 中间件和装置

当网络组件的数量较少时，所有节点都知道其它节点的存在。但随着节点数量的增加，这种结构的成本也会上升。因此，我们需要将这些组件拆分成更小的模块，使用一个中间件来连接它们。

这种结构在现实世界中是非常常见的，我们的社会和经济体系中充满了中间件的机制，用以降低复杂度，压缩构建大型网络的成本。中间件也会被称为批发商、分包商、管理者等等。

ZMQ网络也是一样，如果规模不断增长，就一定会需要中间件。ZMQ中，我们称其为“装置”。在构建ZMQ软件的初期，我们会画出几个节点，然后将它们连接起来，不使用中间件：

![5](/_images/middleware/zeromq/chapter2_6.png)

随后，我们对这个结构不断地进行扩充，将装置放到特定的位置，进一步增加节点数量：

![6](/_images/middleware/zeromq/chapter2_7.png)

ZMQ装置没有具体的设计规则，但一般会有**一组“前端”端点和一组“后端”端点。**装置是无状态的，因此可以被广泛地部署在网络中。你可以在进程中启动一个线程来运行装置，或者直接在一个进程中运行装置。ZMQ内部也提供了基本的装置实现可供使用。

ZMQ装置可以用作路由和寻址、提供服务、队列调度、以及其他你所能想到的事情。不同的消息模式需要用到不同类型的装置来构建网络。如，请求-应答模式中可以使用队列装置、抽象服务；发布-订阅模式中则可使用流装置、主题装置等。

ZMQ装置比起其他中间件的优势在于，你可以将它放在网络中任何一个地方，完成任何你想要的事情。

## 发布-订阅代理服务

我们经常会需要将发布-订阅模式扩充到不同类型的网络中。比如说，有一组订阅者是在外网上的，我们想用广播的方式发布消息给内网的订阅者，而用TCP协议发送给外网订阅者。

我们要做的就是写一个简单的代理服务装置，在发布者和外网订阅者之间搭起桥梁。这个装置有两个端点，一端连接内网上的发布者，另一端连接到外网上。它会从发布者处接收订阅的消息，并转发给外网上的订阅者们。

**wuproxy: Weather update proxy**

```c++
//
//  Weather proxy device C++
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//

#include "zhelpers.hpp"

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    //  This is where the weather server sits
    zmq::socket_t frontend(context, ZMQ_SUB);
    frontend.connect("tcp://192.168.55.210:5556");

    //  This is our public endpoint for subscribers
    zmq::socket_t backend (context, ZMQ_PUB);
    backend.bind("tcp://10.1.1.0:8100");

    //  Subscribe on everything
    frontend.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    //  Shunt messages out to our own subscribers
    while (1) {
        while (1) {
            zmq::message_t message;
            int64_t more;
            size_t more_size = sizeof (more);

            //  Process all parts of the message
            frontend.recv(&message);
            frontend.getsockopt( ZMQ_RCVMORE, &more, &more_size);
            backend.send(message, more? ZMQ_SNDMORE: 0);
            if (!more)
                break;      //  Last message part
        }
    }
    return 0;
}
```

我们称这个装置为代理，因为它既是订阅者，又是发布者。这就意味着，添加该装置时不需要更改其他程序的代码，只需让外网订阅者知道新的网络地址即可。

![7](/_images/middleware/zeromq/chapter2_8.png)

可以注意到，这段程序能够正确处理多帧消息，会将它完整的转发给订阅者。如果我们在发送时不指定ZMQ_SNDMORE选项，那么下游节点收到的消息就可能是破损的。编写装置时应该要保证能够正确地处理多帧消息，否则会造成消息的丢失。

## 请求-应答代理

我们需要有一个模块位于客户端和服务端之间，将所有的知识都汇聚到这个网络拓扑结构中。理想状态下，我们可以任意地增减客户端或是服务端，不需要更改任何组件的配置。

下面就让我们编写这样一个组件。**这个代理会绑定到两个端点，前端端点供客户端连接，后端端点供服务端连接。**它会使用zmq_poll()来轮询这两个套接字，接收消息并进行转发。装置中不会有队列的存在，因为ZMQ已经自动在套接字中完成了。

在使用REQ和REP套接字时，其请求-应答的会话是严格同步。客户端发送请求，服务端接收请求并发送应答，由客户端接收。如果客户端或服务端中的一个发生问题（如连续两次发送请求），程序就会报错。

但是，我们的代理装置必须要是非阻塞式的，虽然可以使用zmq_poll()同时处理两个套接字，但这里显然不能使用REP和REQ套接字。

幸运的是，我们有DEALER和ROUTER套接字可以胜任这项工作，进行非阻塞的消息收发。DEALER过去被称为XREQ，ROUTER被称为XREP，但新的代码中应尽量使用DEALER/ROUTER这种名称。在第三章中你会看到如何用DEALER和ROUTER套接字构建不同类型的请求-应答模式。

下面就让我们看看DEALER和ROUTER套接字是怎样在装置中工作的。

下方的简图描述了一个请求-应答模式，REQ和ROUTER通信，DEALER再和REP通信。ROUTER和DEALER之间我们则需要进行消息转发：

![8](/_images/middleware/zeromq/chapter2_10.png)

请求-应答代理会将两个套接字分别绑定到前端和后端，供客户端和服务端套接字连接。在使用该装置之前，还需要对客户端和服务端的代码进行调整。

**rrclient: Request-reply client**
```c++
//   Request-reply client in C++
//   Connects REQ socket to tcp://localhost:5559
//   Sends "Hello" to server, expects "World" back
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>


#include "zhelpers.hpp"
 
int main (int argc, char *argv[])
{
    zmq::context_t context(1);

	zmq::socket_t requester(context, ZMQ_REQ);
	requester.connect("tcp://localhost:5559");
 
	for( int request = 0 ; request < 10 ; request++) {
		
		s_send (requester, "Hello");
        std::string string = s_recv (requester);
		
		std::cout << "Received reply " << request 
				<< " [" << string << "]" << std::endl;
	}
}
```

**rrserver: Request-reply service**
```c++
//
//   Request-reply service in C++
//   Connects REP socket to tcp://localhost:5560
//   Expects "Hello" from client, replies with "World"
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>


#include "zhelpers.hpp"
 
int main (int argc, char *argv[])
{
    zmq::context_t context(1);

	zmq::socket_t responder(context, ZMQ_REP);
	responder.connect("tcp://localhost:5560");
 
	while(1)
	{
		//  Wait for next request from client
		std::string string = s_recv (responder);
		
		std::cout << "Received request: " << string << std::endl;
		
		// Do some 'work'
        sleep (1);
        
        //  Send reply back to client
		s_send (responder, "World");
		
	}
}

```

**rrbroker: Request-reply broker**
```c++
//
//  Simple request-reply broker in C++
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>


#include "zhelpers.hpp"


int main (int argc, char *argv[])
{
    //  Prepare our context and sockets
    zmq::context_t context(1);
    zmq::socket_t frontend (context, ZMQ_ROUTER);
    zmq::socket_t backend (context, ZMQ_DEALER);

    frontend.bind("tcp://*:5559");
    backend.bind("tcp://*:5560");

    //  Initialize poll set
    zmq::pollitem_t items [] = {
        { frontend, 0, ZMQ_POLLIN, 0 },
        { backend,  0, ZMQ_POLLIN, 0 }
    };
    
    //  Switch messages between sockets
    while (1) {
        zmq::message_t message;
        int64_t more;           //  Multipart detection

        zmq::poll (&items [0], 2, -1);
        
        if (items [0].revents & ZMQ_POLLIN) {
            while (1) {
                //  Process all parts of the message
                // 通过判断more是否为0,来判断是否为最后一帧消息
                frontend.recv(&message);
                size_t more_size = sizeof (more);
                frontend.getsockopt(ZMQ_RCVMORE, &more, &more_size);
                backend.send(message, more? ZMQ_SNDMORE: 0);
                
                if (!more)
                    break;      //  Last message part
            }
        }
        if (items [1].revents & ZMQ_POLLIN) {
            while (1) {
                //  Process all parts of the message
                backend.recv(&message);
                size_t more_size = sizeof (more);
                backend.getsockopt(ZMQ_RCVMORE, &more, &more_size);
                frontend.send(message, more? ZMQ_SNDMORE: 0);
                if (!more)
                    break;      //  Last message part
            }
        }
    }
    return 0;
}

```

**使用请求-应答代理可以让你的C/S网络结构更易于扩展：**客户端不知道服务端的存在，服务端不知道客户端的存在。网络中唯一稳定的组件是中间的代理装置：

![9](/_images/middleware/zeromq/chapter2_11.png)

## 内置装置

ZMQ提供了一些内置的装置，不过大多数人需要自己手动编写这些装置。内置装置有：
<font color="red">
* QUEUE，可用作请求-应答代理；
* FORWARDER，可用作发布-订阅代理服务；
* STREAMER，可用作管道模式代理。
</font>

可以使用zmq_device()来启动一个装置，需要传递两个套接字给它：

```c++
zmq_device(ZMQ_QUEUE, frontend, backend);
```

**启动了QUEUE队列就如同在网络中加入了一个请求-应答代理(即上述rrbroker中while(1)的循环内容可以由zmq_device(ZMQ_QUEUE, frontend, backend)来替代)**，只需为其创建已绑定或连接的套接字即可。下面这段代码是使用内置装置的情形：

**msgqueue: Message queue broker**

```c++
//
//  Simple message queuing broker in C++
//  Same as request-reply broker but using QUEUE device
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>


#include "zhelpers.hpp"

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    //  Socket facing clients
    zmq::socket_t frontend (context, ZMQ_ROUTER);
    frontend.bind("tcp://*:5559");

    //  Socket facing services
    zmq::socket_t backend (context, ZMQ_DEALER);
    zmq_bind (backend, "tcp://*:5560");

    //  Start built-in device
    zmq_device (ZMQ_QUEUE, frontend, backend);
    return 0;
}

```
内置装置会恰当地处理错误，而我们手工实现的代理并没有加入错误处理机制。所以说，当你能够在程序中使用内置装置的时候就尽量用吧。

## ZMQ多线程编程

如何用ZMQ进行多线程编程，以下是一些规则：

* 不要在不同的线程之间访问同一份数据，如果要用到传统编程中的互斥机制，那就有违ZMQ的思想了。唯一的例外是ZMQ上下文对象，它是线程安全的。
* 必须为进程创建ZMQ上下文，并将其传递给所有你需要使用inproc协议进行通信的线程；
* 你可以将线程作为单独的任务来对待，使用自己的上下文，但是这些线程之间就不能使用inproc协议进行通信了。这样做的好处是可以在日后方便地将程序拆分为不同的进程来运行。
* 不要在不同的线程之间传递套接字对象，这些对象不是线程安全的。从技术上来说，你是可以这样做的，但是会用到互斥和锁的机制，这会让你的应用程序变得缓慢和脆弱。唯一合理的情形是，在某些语言的ZMQ类库内部，需要使用垃圾回收机制，这时可能会进行套接字对象的传递。

以下是多线程版的Hello World服务：

**mtserver: Multithreaded service**
```c++
/*
    Multithreaded Hello World server in C++
*/

#include <pthread.h>
#include <unistd.h>
#include <cassert>
#include <string>
#include <iostream>
#include <zmq.hpp>
#include "zhelpers.hpp"

void *worker_routine(void *arg)
{
    zmq::context_t *context = (zmq::context_t *)arg;

    zmq::socket_t socket(*context, ZMQ_REP);
    socket.connect("inproc://workers");

    while (true)
    { 
        //  Wait for next request from client
        std::string recvStr;
        recvStr = s_recv(socket);
        std::cout << "server pthread_id: "<<pthread_self()<<" Received request: [" << recvStr << "]" << std::endl;

        //  Do some 'work'
        sleep(1);

        //  Send reply back to client
        std::string sendStr = "server pthread_id: "+ std::to_string(pthread_self())+" send [I'm server Hello.]";
        std::cout << sendStr << std::endl;
        s_send(socket, sendStr);
    }
    return (NULL);
}

int main()
{
    //  Prepare our context and sockets
    zmq::context_t context(1);
    zmq::socket_t clients(context, ZMQ_ROUTER);
    clients.bind("tcp://*:5555");
    zmq::socket_t workers(context, ZMQ_DEALER);
    workers.bind("inproc://workers");

    //  Launch pool of worker threads
    for (int thread_nbr = 0; thread_nbr != 5; thread_nbr++)
    {
        pthread_t worker;
        pthread_create(&worker, NULL, worker_routine, (void *)&context);
    }
    //  Connect work threads to client threads via a queue
    zmq_device(ZMQ_QUEUE, clients, workers);
    return 0;
}
```

所有的代码应该都已经很熟悉了：

* 服务端启动一组worker线程，每个worker创建一个REP套接字，并处理收到的请求。worker线程就像是一个单线程的服务，唯一的区别是使用了inproc而非tcp协议，以及绑定-连接的方向调换了。
* 服务端创建ROUTER套接字用以和client通信，因此提供了一个TCP协议的外部接口。
* 服务端创建DEALER套接字用以和worker通信，使用了内部接口（inproc）。
* 服务端启动了QUEUE内部装置，连接两个端点上的套接字。QUEUE装置会将收到的请求分发给连接上的worker，并将应答路由给请求方。

需要注意的是，在某些编程语言中，创建线程并不是特别方便，POSIX提供的类库是pthreads，但Windows中就需要使用不同的API了。我们会在第三章中讲述如何包装一个多线程编程的API。

示例中的“工作”仅仅是1秒钟的停留，我们可以在worker中进行任意的操作，包括与其他节点进行通信。消息的流向是这样的：REQ-ROUTER-queue-DEALER-REP。

![10](/_images/middleware/zeromq/chapter2_12.png)

## 瞬时套接字和持久套接字

在传统网络编程中，套接字是一个API对象，它们的生命周期不会长过程序的生命周期。但仔细打量一下套接字，它会占用一项特定的资源——缓存，这时ZMQ的开发者可能会问：是否有办法在程序崩溃时让这些套接字缓存得以保留，稍后能够恢复？

这种特性应该会非常有用，虽然不能应对所有的危险，但至少可以挽回一部分损失，特别是多发布-订阅模式来说。让我们来讨论一下。

这里有两个套接字正在欢快地传送着气象信息：如果接收方（SUB、PULL、REQ）指定了套接字标识，当它们断开网络时，发送方（PUB、PUSH、REP）会为它们缓存信息，直至达到阈值（HWM）。这里发送方不需要有套接字标识。需要注意，ZMQ的套接字缓存对程序员来说是不可见的，正如TCP缓存一样。

到目前为止，我们使用的套接字都是瞬时套接字。要将瞬时套接字转化为持久套接字，需要为其设定一个套接字标识。所有的ZMQ套接字都会有一个标识，不过是由ZMQ自动生成的UUID。在ZMQ内部，两个套接字相连时会先交换各自的标识。如果发生对方没有ID，则会自行生成一个用以标识对方。但套接字也可以告知对方自己的标识，那当它们第二次连接时，就能知道对方的身份：

下面这行代码就可以为套接字设置标识，从而建立了一个持久的套接字：

```c++
subscriber.setsockopt(ZMQ_IDENTITY, "Hello", 5);
```

关于套接字标识还有几点说明：

* 如果要为套接字设置标识，必须在连接或绑定至端点之前设置；
* 接收方会选择使用套接字标识，正如cookie在HTTP网页应用中的性质，是由服务器去选择要使用哪个cookie的；
* 套接字标识是二进制字符串；以字节0开头的套接字标识为ZMQ保留标识；
* 不用为多个套接字指定相同的标识，若套接字使用的标识已被占用，它将无法连接至其他套接字；
* 不要使用随机的套接字标识，这样会生成很多持久化套接字，最终让节点崩溃；
* 如果你想获取对方套接字的标识，只有ROUTER套接字会帮你自动完成这件事，使用其他套接字类型时，需要将标识作为消息的一帧发送过来；
* 说了以上这些，使用持久化套接字其实并不明智，因为它会让发送者越来越混乱，让架构变得脆弱。如果我们能重新设计ZMQ，很可能会去掉这种显式声明套接字标识的功能。

其他信息可以查看zmq_setsockopt()函数的ZMQ_IDENTITY一节。注意，该方法只能获取程序中套接字的标识，而不能获得对方套接字的标识。
