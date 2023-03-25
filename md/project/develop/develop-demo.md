# 项目开发 - C++开源项目推荐

> C++ 学习项目推荐。

[[toc]]

# TinyWebServer(9.8k+ star)  ———— Web服务器

Linux下C++轻量级Web服务器，助力初学者快速实践网络编程，搭建属于自己的服务器.

* 使用 **线程池 + 非阻塞socket + epoll(ET和LT均实现) + 事件处理(Reactor和模拟Proactor均实现)**的并发模型
* 使用**状态机**解析HTTP请求报文，支持解析GET和POST请求
* 访问服务器数据库实现web端用户注册、登录功能，可以请求服务器图片和视频文件
* 实现**同步/异步日志系统**，记录服务器运行状态
* 经Webbench压力测试可以实现**上万的并发连接数据**交换

* [传送门](https://github.com/qinguoyi/TinyWebServer)

# sylar(2.5k+ star) ———— 自封装的基础服务库，利用学习

C++高性能分布式服务器框架,webserver,websocket server,自定义tcp_server（包含日志模块，配置模块，线程模块，协程模块，协程调度模块，io协程调度模块，hook模块，socket模块，bytearray序列化，http模块，TcpServer模块，Websocket模块，Https模块等, Smtp邮件模块, MySQL, SQLite3, ORM,Redis,Zookeeper)

* [传送门](https://github.com/sylar-yin/sylar)

# TinyWebServer(9.8k+ star)  ———— Web服务器

Linux下C++轻量级Web服务器，助力初学者快速实践网络编程，搭建属于自己的服务器.

* 使用 **线程池 + 非阻塞socket + epoll(ET和LT均实现) + 事件处理(Reactor和模拟Proactor均实现)**的并发模型
* 使用**状态机**解析HTTP请求报文，支持解析GET和POST请求
* 访问服务器数据库实现web端用户注册、登录功能，可以请求服务器图片和视频文件
* 实现**同步/异步日志系统**，记录服务器运行状态
* 经Webbench压力测试可以实现**上万的并发连接数据**交换

* [传送门](https://github.com/qinguoyi/TinyWebServer)

# Poco 库 ———— 基础应用库

POCO C++库是强大的跨平台C++库,用于构建在桌面、服务器、移动、物联网和嵌入式系统上运行的基于网络和互联网的应用程序。

* [传送门](https://pocoproject.org/)

# Log4cpp 库  ———— 日志库

Log4cpp是一个开源的C++类库，它提供了在C++程序中使用日志和跟踪调试的功能。使用log4cpp，可以很便利地将日志或者跟踪调试信息写入字符流、内存字符串队列、文件、回滚文件、调试器、Windows日志、syslog和远程syslog服务器中。

* [传送门](https://sourceforge.net/projects/log4cpp/files/)

# Protobuf ———— 序列化

Google出品，protobuf一个具有高效的协议数据交换格式工具库(类似Json)，但相比于Json，Protobuf有更高的转化效率，时间效率和空间效率都是JSON的3-5倍。（现在的RPC基本都是用protobuf作为通讯数据格式。）

* [传送门](https://protobuf.dev/)

# gRPC ———— 远程过程调用

gRPC (gRPC Remote Procedure Calls) 是Google发起的一个开源远程过程调用 (Remote procedure call) 系统。该系统基于 HTTP/2 协议传输，使用Protocol Buffers 作为接口描述语言。

gRPC是可以在任何环境中运行的现代开源高性能远程过程调用（RPC）框架。它可以通过可插拔的支持来有效地连接数据中心内和跨数据中心的服务，以实现负载平衡，跟踪，运行状况检查和身份验证。它也适用于分布式计算的最后一英里，以将设备，移动应用程序和浏览器连接到后端服务。

* [传送门](https://grpc.io/)

# Webbench ———— 网站压测工具

Webbench是Radim Kolar在1997年写的一个在linux下使用的非常简单的网站压测工具。它使用fork()模拟多个客户端同时访问我们设定的URL，测试网站在压力下工作的性能，最多可以模拟3万个并发连接去测试网站的负载能力。非常适合用来学习网络编程，代码量也不大，适合初学者：

* [传送门](http://home.tiscali.cz/~cz210552/webbench.html)

# leveldb ———— KV数据库

这是一个基于LSM结构的KV存储，levldb常常被用作各类数据库、存储系统的存储引擎，估计在BAT都能找到它的使用。设计思想值得学习，LevelDB是一个持久化存储的KV系统，和Redis这种基于内存的KV系统不同，LevelDB不会像Redis一样大量使用内存，而是将大部分数据落到磁盘上。LevleDB在存储数据时，是根据记录的key值有序存储的，就是说相邻的key值在存储文件中是依次顺序存储的，而应用可以自定义key大小比较函数，LevleDB会按照用户定义的比较函数依序存储这些记录。

* [传送门](https://github.com/google/leveldb)

# muduo ———— KV数据库

muduo是陈硕大神个人开发的C++的TCP网络编程库。muduo基于Reactor模式实现。Reactor模式也是目前大多数Linux端高性能网络编程框架和网络应用所选择的主要架构，例如内存数据库Redis和Java的Netty库等。

* [传送门](https://github.com/chenshuo/muduo)

# Tinyhttpd ———— HTTP学习Demo

Tinyhttpd 是J. David Blackstone在1999年写的一个不到 500 行的超轻量型 Http Server，用来学习非常不错，可以帮助我们真正理解服务器程序的本质。

* [传送门](https://github.com/EZLippi/Tinyhttpd)