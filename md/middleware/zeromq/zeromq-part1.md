
# 第一章 ZeroMQ基础

> 本章介绍了ZeroMQ基础知识和基本模型的使用方法，涉及的内容有：

* 基础知识(ZMQ简介、学习内容、使用方法)
* 请求回应模型（Request-Reply）
* 发布订阅模型（Publish-Subscribe）
* 推拉模型（Push-Pull）
* 一对一结对模型（Exclusive-Pair）

---

[[toc]]

## 基础知识

### ZMQ简介

ZeroMQ（简称ZMQ）是一个基于消息队列的多线程网络库，其对套接字类型、连接处理、帧、甚至路由的底层细节进行抽象，提供跨越多种传输协议的套接字。ZMQ看起来像是一套嵌入式的网络链接库，但工作起来更像是一个并发式的框架。

ZeroMQ提供的套接字可以在多种协议中传输消息，如线程间、进程间、TCP、广播等。用户可以使用套接字构建多对多的连接模式，它将消息通信分成4种模型，分别是：

* 请求回应模型（Request-Reply）：将一组服务端和一组客户端相连，用于远程过程调用或任务分发。
* 发布订阅模型（Publish-Subscribe）：将一组发布者和一组订阅者相连，用于数据分发。
* 推拉模型（Push-Pull）：使用扇入或扇出的形式组装多个节点，可以产生多个步骤或循环，用于构建并行处理架构。
* 一对一结对模型（Exclusive-Pair）：将两个套接字一对一地连接起来。

ZMQ的快速足以胜任集群应用产品。它的异步I/O机制让你能够构建多核应用程序，完成异步消息处理任务。ZMQ有着多语言支持，并能在几乎所有的操作系统上运行。ZMQ是iMatix公司的产品，以LGPL开源协议发布。


ZMQ的主要特点有:
* 传统的网络，必须先启动服务器再启动客户端，要不然先启动客户端connect会报失败；
但是0mq允许我们任意的启动和停止各个部件。先启动客户端，再启动服务器也能正常工作。
* 使用ZeroMQ后，用户无需关心 拆包粘包、断线重连、心跳检测等问题。
* ZMQ会在**后台线程异步地处理I/O操作**，它使用一种不会死锁的数据结构来存储消息。
* 网络组件可以来去自如，ZMQ会负责自动重连，这就意味着你可以以任何顺序启动组件；用它创建的面向服务架构（SOA）中，服务端可以随意地加入或退出网络。
* ZMQ会在有必要的情况下自动将消息放入队列中保存，一旦建立了连接就开始发送。
* ZMQ有阈值（HWM）的机制，可以避免消息溢出。当队列已满，ZMQ会自动阻塞发送者，或丢弃部分消息，这些行为取决于你所使用的消息模式。
* ZMQ可以让你用不同的通信协议进行连接，如TCP、广播、进程内、进程间。改变通信协议时你不需要去修改代码。
* ZMQ会恰当地处理速度较慢的节点，会根据消息模式使用不同的策略。
* ZMQ提供了多种模式进行消息路由，如请求-应答模式、发布-订阅模式等。这些模式可以用来搭建网络拓扑结构。
* ZMQ中可以根据消息模式建立起一些中间装置（很小巧），可以用来降低网络的复杂程度。
* ZMQ会发送整个消息，使用消息帧的机制来传递。如果你发送了10KB大小的消息，你就会收到10KB大小的消息。
* ZMQ不强制使用某种消息格式，消息可以是0字节的，或是大到GB级的数据。当你表示这些消息时，可以选用诸如谷歌的protocol buffers，XDR等序列化产品。
* ZMQ能够智能地处理网络错误，有时它会进行重试，有时会告知你某项操作发生了错误。
* ZMQ甚至可以降低对环境的污染，因为节省了CPU时间意味着节省了电能。


### 学习内容

* [ZeroMQ教程中文版](https://gitee.com/solym/ZeroMQ-Guide-Zh)
* [ZeroMQ教程(examples)](https://github.com/booksbyus/zguide)
* [官方使用手册](http://api.zeromq.org)
* [ZeroMQ源码](https://github.com/zeromq/libzmq)
* [C++版0MQ](https://github.com/zeromq/cppzmq)


### 使用方法

下载libzmq和cppzmq的zip包，然后执行以下操作：
```
unzip libzmq-master.zip
cd ./libzmq-master/
mkdir build && cd build
cmake ..
sudo make -j4 install


cd /home/zeromq/
unzip cppzmq-master.zip

cd ./cppzmq-master/
mkdir build && cd build
cmake -DCPPZMQ_BUILD_TESTS=OFF ..
sudo make -j4 install
```

---
## 请求回应模型（Request-Reply）

让我们从简单的代码开始，一段传统的Hello World程序。我们会创建一个客户端和一个服务端，客户端发送Hello给服务端，服务端返回World。

备注:ZMQ不会关心发送消息的内容，只要知道它所包含的字节数。所以，程序员需要做一些工作，保证对方节点能够正确读取这些消息。因此，使用zhelpers.hpp，一个供C++语言使用的ZMQ功能函数库，封装了一些基础的函数例如s_send、s_recv等。

![1](/_images/middleware/zeromq/chapter1_1.png)

**hwclient: Hello World client** 
```cpp
//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include "zhelpers.hpp"

int main()
{
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 10; request_nbr++)
    {
        std::string sendStr = "Hello";
        s_send(socket, sendStr);
        std::cout << "client Send " << sendStr << " " << request_nbr << std::endl;

        //  Get the reply.
        std::string recvStr;
        recvStr = s_recv(socket);
        std::cout << "client Received " << recvStr << " " << request_nbr << std::endl;
    }
    return 0;
}
```
**hwserver.cpp: Hello World server**
```cpp
//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
#include "zhelpers.hpp"

int main()
{
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");

    int count=0;
    while (true)
    {
        std::string recvStr;
        recvStr = s_recv(socket);
        std::cout << "server Received " << recvStr << " " << count << std::endl;

        //  Do some 'work'
        sleep(1);

        //  Send reply back to client
        std::string sendStr = "World";
        s_send(socket, sendStr);
        std::cout << "server Send " << sendStr << " " << count << std::endl;
        count++;
    }
    return 0;
}

```
执行结果:
```
[root@192 zeromq]# ./hwclient
Connecting to hello world server...
client Send Hello 0
client Received World 0
client Send Hello 1
client Received World 1
client Send Hello 2
client Received World 2

[root@192 zeromq]# ./hwserver
server Received Hello 0
server Send World 0
server Received Hello 1
server Send World 1
server Received Hello 2
server Send World 2

```

---
## 发布订阅模型（Publish-Subscribe）

经典的消息模式是单向数据分发：服务端将更新事件发送给一组客户端。让我们看一个天气信息发布的例子，包括邮编、温度、相对湿度。我们生成这些随机信息，用来模拟气象站所做的那样。

![2](/_images/middleware/zeromq/chapter1_4.png)

**wuclient: Weather update client**
```cpp
//
//  Weather update client in C++
//  Connects SUB socket to tcp://localhost:5556
//  Collects weather updates and finds avg temp in zipcode
//
//  Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
#include <zmq.hpp>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{
    zmq::context_t context(1);

    //  Socket to talk to server
    std::cout << "Collecting updates from weather server...\n"
              << std::endl;
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556");

    //  Subscribe to zipcode, default is NYC, 10001
    const char *filter = (argc > 1) ? argv[1] : "10001 ";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));

    //  Process 100 updates
    int update_nbr;
    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 100; update_nbr++)
    {
        zmq::message_t update;
        int zipcode, temperature, relhumidity;

        subscriber.recv(&update);

        std::istringstream iss(static_cast<char *>(update.data()));
        iss >> zipcode >> temperature >> relhumidity;

        total_temp += temperature;
    }
    std::cout << "Average temperature for zipcode '" << filter
              << "' was " << (int)(total_temp / update_nbr) << "F"
              << std::endl;
    return 0;
}

```

**wuserver: Weather update server**
```cpp
//
//  Weather update server in C++
//  Binds PUB socket to tcp://*:5556
//  Publishes random weather updates
//
//  Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
#include <zmq.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

int main () {

    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.bind("tcp://*:5556");
    publisher.bind("ipc://weather.ipc");

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));
    while (1) {

        int zipcode, temperature, relhumidity;

        //  Get values that will fool the boss
        zipcode     = within (100000);
        temperature = within (215) - 80;
        relhumidity = within (50) + 10;

        //  Send message to all subscribers
        zmq::message_t message(20);
        snprintf ((char *) message.data(), 20 ,
        	"%05d %d %d", zipcode, temperature, relhumidity);
        publisher.send(message);

    }
    return 0;
}

```
执行结果:
```
[root@192 C++]# ./wuclient
Collecting updates from weather server...

Average temperature for zipcode '10001 ' was 20F

[root@192 C++]# ./wuserver

```
需要注意的是，在使用SUB套接字时，必须使用zmq_setsockopt()方法来设置订阅的内容。如果你不设置订阅内容，那将什么消息都收不到，新手很容易犯这个错误。订阅信息可以是任何字符串，可以设置多次。只要消息满足其中一条订阅信息，SUB套接字就会收到。订阅者可以选择不接收某类消息，也是通过zmq_setsockopt()方法实现的。

---
## 推拉模型（Push-Pull）

分布式处理
下面一个示例程序中，我们将使用ZMQ进行超级计算，也就是并行处理模型：

*任务分发器会生成大量可以并行计算的任务；
*有一组worker会处理这些任务；
*结果收集器会在末端接收所有worker的处理结果，进行汇总。
现实中，worker可能散落在不同的计算机中，利用GPU（图像处理单元）进行复杂计算。

![3](/_images/middleware/zeromq/chapter1_5.png)

下面是任务分发器的代码，它会生成100个任务，任务内容是让收到的worker延迟若干毫秒。

**taskvent: Parallel task ventilator**

```cpp
//
//  Task ventilator in C++
//  Binds PUSH socket to tcp://localhost:5557
//  Sends batch of tasks to workers via that socket
//
//  Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
#include <zmq.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

int main (int argc, char *argv[])
{
    zmq::context_t context (1);

    //  Socket to send messages on
    zmq::socket_t  sender(context, ZMQ_PUSH);
    sender.bind("tcp://*:5557");

    std::cout << "Press Enter when the workers are ready: " << std::endl;
    getchar ();
    std::cout << "Sending tasks to workers...\n" << std::endl;

    //  The first message is "0" and signals start of batch
    zmq::socket_t sink(context, ZMQ_PUSH);
    sink.connect("tcp://localhost:5558");
    zmq::message_t message(2);
    memcpy(message.data(), "0", 1);
    sink.send(message);

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));

    //  Send 100 tasks
    int task_nbr;
    int total_msec = 0;     //  Total expected cost in msecs
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        int workload;
        //  Random workload from 1 to 100msecs
        workload = within (100) + 1;
        total_msec += workload;

        message.rebuild(10);
        sprintf ((char *) message.data(), "%d", workload);
        sender.send(message);
    }
    std::cout << "Total expected cost: " << total_msec << " msec" << std::endl;
    sleep (1);              //  Give 0MQ time to deliver

    return 0;
}
```

下面是worker的代码，它接受信息并延迟指定的毫秒数，并发送执行完毕的信号:

**taskwork: Parallel task worker**

```cpp
//
//  Task worker in C++
//  Connects PULL socket to tcp://localhost:5557
//  Collects workloads from ventilator via that socket
//  Connects PUSH socket to tcp://localhost:5558
//  Sends results to sink via that socket
//
//  Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
#include "zhelpers.hpp"

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    //  Socket to receive messages on
    zmq::socket_t receiver(context, ZMQ_PULL);
    receiver.connect("tcp://localhost:5557");

    //  Socket to send messages to
    zmq::socket_t sender(context, ZMQ_PUSH);
    sender.connect("tcp://localhost:5558");

    //  Process tasks forever
    while (1) {

        zmq::message_t message;
        int workload;           //  Workload in msecs

        receiver.recv(&message);

        std::istringstream iss(static_cast<char*>(message.data()));
        iss >> workload;

        //  Do the work
        s_sleep(workload);

        //  Send results to sink
        message.rebuild();
        sender.send(message);

        //  Simple progress indicator for the viewer
		std::cout << "." << std::flush;
    }
    return 0;
}

```

下面是结果收集器的代码。它会收集100个处理结果，并计算总的执行时间，让我们由此判别任务是否是并行计算的。

**tasksink: Parallel task sink**

```cpp
//
//  Task sink in C++
//  Binds PULL socket to tcp://localhost:5558
//  Collects results from workers via that socket
//
//  Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>
//
#include <zmq.hpp>
#include <time.h>
#include <sys/time.h>
#include <iostream>

int main (int argc, char *argv[])
{
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t receiver(context,ZMQ_PULL);
	receiver.bind("tcp://*:5558");

    //  Wait for start of batch
    zmq::message_t message;
    receiver.recv(&message);

    //  Start our clock now
    struct timeval tstart;
    gettimeofday (&tstart, NULL);

    //  Process 100 confirmations
    int task_nbr;
    int total_msec = 0;     //  Total calculated cost in msecs
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {

        receiver.recv(&message);
        if ((task_nbr / 10) * 10 == task_nbr)
            std::cout << ":" << std::flush;
        else
            std::cout << "." << std::flush;
    }
    //  Calculate and report duration of batch
    struct timeval tend, tdiff;
    gettimeofday (&tend, NULL);

    if (tend.tv_usec < tstart.tv_usec) {
        tdiff.tv_sec = tend.tv_sec - tstart.tv_sec - 1;
        tdiff.tv_usec = 1000000 + tend.tv_usec - tstart.tv_usec;
    }
    else {
        tdiff.tv_sec = tend.tv_sec - tstart.tv_sec;
        tdiff.tv_usec = tend.tv_usec - tstart.tv_usec;
    }
    total_msec = tdiff.tv_sec * 1000 + tdiff.tv_usec / 1000;
    std::cout << "\nTotal elapsed time: " << total_msec << " msec\n" << std::endl;
    return 0;
}

```

一组任务的平均执行时间在5秒左右，以下是分别开始1个、2个、4个worker时的执行结果:
```
先启动./taskwork，然后启动./tasksink,./taskvent(点回车)

1 taskwork
Total elapsed time: 5227 msec
2 taskwork
Total elapsed time: 2572 msec

```
## 一对一结对模型（Exclusive-Pair）

当你刚开始使用ZMQ进行多线程编程时，你可能会问：要如何协调两个线程的工作呢？可能会想要使用sleep()这样的方法，或者使用诸如信号、互斥等机制。事实上，**你唯一要用的就是ZMQ本身**。回忆一下那个醉汉抢啤酒的例子吧。

下面的示例演示了三个线程之间需要如何进行同步：

![4](/_images/middleware/zeromq/chapter2_13.png)

我们使用PAIR套接字和inproc协议。

**mtrelay: Multithreaded relay in C**

```cpp
//
//  Multithreaded relay in C++
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>


#include "zhelpers.hpp"


//  Step 1 pushes one message to step 2

void *step1 (void *arg) {
	
	zmq::context_t * context = static_cast<zmq::context_t*>(arg);
	
	//  Signal downstream to step 2
	zmq::socket_t sender (*context, ZMQ_PAIR);
	sender.connect("inproc://step2");

	s_send (sender, "");

	return (NULL);
}

//  Step 2 relays the signal to step 3

void *step2 (void *arg) {

	zmq::context_t * context = static_cast<zmq::context_t*>(arg);
	
    //  Bind to inproc: endpoint, then start upstream thread
	zmq::socket_t receiver (*context, ZMQ_PAIR);
    receiver.bind("inproc://step2");

    pthread_t thread;
    pthread_create (&thread, NULL, step1, context);

    //  Wait for signal
    s_recv (receiver);

    //  Signal downstream to step 3
    zmq::socket_t sender (*context, ZMQ_PAIR);
    sender.connect("inproc://step3");
    s_send (sender, "");

    return (NULL);
}

//  Main program starts steps 1 and 2 and acts as step 3

int main () {
	
	zmq::context_t context(1);

    //  Bind to inproc: endpoint, then start upstream thread
    zmq::socket_t receiver (context, ZMQ_PAIR);
    receiver.bind("inproc://step3");

    pthread_t thread;
    pthread_create (&thread, NULL, step2, &context);

    //  Wait for signal
    s_recv (receiver);
    
    std::cout << "Test successful!" << std::endl;

    return 0;
}

```

这是一个ZMQ多线程编程的典型示例：

1. 两个线程通过inproc协议进行通信，**使用同一个上下文**；
2. 父线程创建一个套接字，绑定至inproc://端点，然后再启动子线程，将上下文对象传递给它；
3. 子线程创建第二个套接字，连接至inproc://端点，然后发送已就绪信号给父线程。

PAIR套接字建立的是一对一的连接，具有排他性,使用PAIR套接字进行线程间的协调是最合适的。
