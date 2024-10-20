# 架构 - RPC框架

[[toc]]

# 参考资料

* [RPC原理及实现](https://www.jianshu.com/p/c113a9592044)
* [RPC（三）《Implementing Remote Procedure Calls》译文](https://www.jianshu.com/p/91be39f72c74)
* [wiki百科RPC](https://en.wikipedia.org/wiki/Remote_procedure_call)

::: danger
probuf实现，gRpc
:::

# wiki百科

## concept

> In distributed computing, a remote procedure call (RPC) is **when a computer program causes a procedure (subroutine) to execute in a different address space** (commonly on another computer on a shared network), which is coded as if it were a normal (local) procedure call, without the programmer explicitly coding the details for the remote interaction. That is, the programmer writes essentially the same code whether the subroutine is local to the executing program, or remote. This is a form of **client–server interaction (caller is client, executor is server)**, typically implemented via a **request–response message-passing system**. In the object-oriented programming paradigm, RPCs are represented by **remote method invocation** (RMI). The RPC model implies a level of location transparency, namely that calling procedures are largely the same whether they are local or remote, but usually, they are not identical, so local calls can be distinguished from remote calls. Remote calls are usually orders of magnitude slower and less reliable than local calls, so distinguishing them is important.

RPCs are **a form of inter-process communication (IPC)**, in that different processes have **different address spaces**: if on the same host machine, they have distinct virtual address spaces, even though the physical address space is the same; while if they are on different hosts, the physical address space is different. Many different (often incompatible) technologies have been used to implement the concept.

* 分布式计算中，远程过程调用时一个计算机程序触发一个子程序在不同的地址空间去执行
* 是一种客户端-服务器交互，通过请求-响应的消息传递机制。
* 在面对对象编程模型中，RPC表现为“远程方法调用”
* 作为一种进程间通信的方式，不同的进程有各自的地址空间

## Message passing

RPC is a request–response protocol. An RPC is initiated by the client, which sends a request message to a known remote server to execute a specified procedure with supplied parameters. The remote server sends a response to the client, and the application continues its process. While the server is processing the call, the client is blocked (it waits until the server has finished processing before resuming execution), unless the client sends an asynchronous request to the server, such as an XMLHttpRequest. There are many variations and subtleties in various implementations, resulting in a variety of different (incompatible) RPC protocols.

An important difference between remote procedure calls and local calls is that remote calls can fail because of unpredictable network problems. Also, callers generally must deal with such failures without knowing whether the remote procedure was actually invoked. Idempotent procedures (those that have no additional effects if called more than once) are easily handled, but enough difficulties remain that code to call remote procedures is often confined to carefully written low-level subsystems.

* 在各种实现中有许多变化和微妙之处，导致了各种不同的RPC协议。
* 远程过程调用和本地调用区别：远程调用存在不可预期的网络问题
* 需要保证幂等性

**Sequence of events**

1. The client calls the client stub. The call is a local procedure call, with parameters pushed on to the stack in the normal way.
2. The client stub packs the parameters into a message and makes a system call to send the message. Packing the parameters is called marshalling.
3. The client's local operating system sends the message from the client machine to the server machine.
4. The local operating system on the server machine passes the incoming packets to the server stub.
5. The server stub unpacks the parameters from the message. Unpacking the parameters is called unmarshalling.
6. Finally, the server stub calls the server procedure. The reply traces the same steps in the reverse direction.

A stub in distributed computing is a piece of code that converts parameters passed between client and server during a remote procedure call (RPC).

存根是分布式计算中的一段代码，用于转换远程过程调用（RPC）期间客户端和服务器之间传递的参数。

# 概述

> RPC(Remote Procedure Call)即远程过程调用，允许一台计算机调用另一台计算机上的程序得到结果，而代码中不需要做额外的编程，就像在本地调用一样。

## 角色

在RPC框架中主要有三个角色**：Provider、Consumer和Registry**。

节点角色说明：

* Server: 暴露服务的服务提供方。

* Client: 调用远程服务的服务消费方。

* Registry: 服务注册与发现的注册中心。

## 调用流程

![rpc基本流程图](/_images/project/opensource/buttonrpc/rpc基本流程图.png)

一次完整的RPC调用流程（同步调用，异步另说）如下：

1. 服务消费方（client）调用以本地调用方式调用服务；

2. client stub接收到调用后负责将方法、参数等组装成能够进行网络传输的消息体；

3. client stub找到服务地址，并将消息发送到服务端；

4. server stub收到消息后进行解码；

5. server stub根据解码结果调用本地的服务；

6. 本地服务执行并将结果返回给server stub；

7. server stub将返回结果打包成消息并发送至消费方；

8. client stub接收到消息，并进行解码；

9. 服务消费方得到最终结果。

RPC框架的目标就是要2~8这些步骤都封装起来，让用户对这些细节透明。

时序图如下：

![rpc时序图](/_images/project/opensource/buttonrpc/rpc时序图.png)

# 诞生背景

从单机走向分布式，产生了很多分布式的通信方法:

- 最古老也是最有效，并且永不过时的，**TCP/UDP的二进制传输**。事实上所有的通信方式归根结底都是TCP/UDP。（属于计算机网络的传输层，传输协议在计算机之间提供通信会话。传输协议的选择根据数据传输方式而定。传输控制协议TCP和用户数据报协议UDP）
- Web Service 
  - 基于 http + xml 的标准化 Web API  
- RestFul    (Representational State Transfer)
  - 回归简单化本源的Web API   http +json  ,提供一个网址返回 json 串 
- RPC  (Remote Procedure Call)
  - 远程过程调用

# RPC框架演进过程

从基础的架构一步步进行完善,从JAVA语言角度的示例：

- rpc01 客户端等待服务器端连接，客户端将数据通过二进制传给服务器端。服务器端收到数据后，在数据库进行查询，得到一个对象。然后将对象中的每个属性通过二进制传递给客户端。客户端读取每一个属性后，new为一个新的对象。(最原始的方法，很不灵活)

- rpc02 从客户端分离出一个stub类，作为代理，从而屏蔽一些网络细节。(缺点:在这个stub类里只能代理一个方法，并返回这一个类)

- rpc03 stub类通过动态代理返回了一个动态对象。这个对象所属的类实现了IUserService接口。在这个接口实在的方法屏蔽了一些网络的细节。(当换用不同的方法后，传输数据会有问题)

- rpc04 当换用不同的方法后，stub类拿到对应的方法名和参数类型(防止重载的情况)和参数，写给服务器端，服务器端通过反射的方式找到方法，然后调用相应的方法，返回给stub。(不足:只能支持同一个接口的很多方法，不能支持很多个接口的很多方法。stub返回值仍然是对象的每个属性)

- rpc05 在服务器的直接用writeobject方法把对象写出去(这个版本可以让IUserService随意的暴露和变换接口，客户端只能拿到一个接口)

- rpc06 stub中为class类型的对象。得到类的名字，方法的名字，方法的类型和具体参数传给服务器端。服务器端从服务注册表找到具体的类。实现类可以通过spring进行注入。然后通过具体实现类的对象，调用相应的方法。(能够生成更多类型的代理)


# 涉及的选型

1. 动态代理

   * 生成 client stub 和server stub

2. 序列化

   * 为了能够在网络上传输和接收C++对象，我们需要对它进行 **序列化 和 反序列化**。
   * 序列化：将C++对象转换成vector<char>的过程，也就是编码的过程；
   * 反序列化: 将vector<char>转换成C++对象的过程；

3. 服务注册

   * Redis
   * Zookeeper
   * Consul
   * Etcd
   * map键值对，函数名对应调用函数的内容：std::map<std::string, std::function<void(Serializer *, const char *, int)>> _handlers;

4. 网络通信  

   * TCP/IP
   * HTTP
   * Web Service
   * RestFul    
   * ZeroMQ，消息队列
