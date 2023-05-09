# ♥常用开发库知识体系详解♥

# 知识体系结构

下述常用类库的使用来自个人开源项目 [build_lib](https://github.com/klc407073648/build_lib)。

简单来说就是编译生成第三方库的头文件和so，进一步二次封装成个人库，便于统一使用。也可以参考介绍 [个人项目 - build_lib](md/project/person/build_lib/build_lib.md)

# 常用类库

* [常用开发库 - cppcheck](/md/develop/library/library-cppcheck.md)
    * cppcheck: Cppcheck是一种C/C++代码缺陷静态检查工具，不同于C/C++编译器及其它分析工具，Cppcheck只检查编译器检查不出来的bug，不检查语法错误。
    
* [常用开发库 - cppunit](/md/develop/library/library-cppunit.md)
    * cppunit: CppUnit 是个基于 LGPL 的开源项目，最初版本移植自 JUnit，是一个非常优秀的开源测试框架。CppUnit 和 JUnit 一样主要思想来源于极限编程(XProgramming)。主要功能就是对**单元测试**进行管理，并可进行自动化测试。

* [常用开发库 - drogon](/md/develop/library/library-drogon.md)
    * drogon: Drogon是一个基于C++14/17的Http应用框架，使用Drogon可以方便的使用C++构建各种类型的Web应用服务端程序。它是一个跨平台框架，它支持Linux，也支持macOS、FreeBSD，OpenBSD，HaikuOS，和Windows

* [常用开发库 - fastcgi](/md/develop/library/library-fastcgi.md)
    * fastcgi: 快速通用网关接口(Fast Common Gateway Interface, FastCGI)是通用网关接口(CGI)的改进，描述了客户端和服务器程序之间传输数据的一种标准。FastCGI致力于减少Web服务器与CGI程式之间互动的开销，从而使服务器可以同时处理更多的Web请求。与为每个请求创建一个新的进程不同，**FastCGI使用持续的进程来处理一连串的请求**。这些进程由FastCGI进程管理器管理，而不是web服务器。

* [常用开发库 - googletest](/md/develop/library/library-googletest.md)
    * googletest: Google Test 是由 Google 推出的 C++ 测试框架，具有稳定、跨平台、快速等特点，能够为 C++ 开发人员提供有效的单元测试和集成测试工具。

* [常用开发库 - hiredis](/md/develop/library/library-hiredis.md)
    * hiredis: Hiredis是Redis数据库的简约C客户端库。它是简约的，因为它只是增加了对协议的最小支持，但是同时它使用了一个高级别的printf-like API，所以对于习惯了printf风格的C编程用户来说，其非常容易使用，而且API中没有**明确的绑定每个Redis命令**。

* [常用开发库 - jsoncpp](/md/develop/library/library-jsoncpp.md)
    * jsoncpp: JsonCpp 是一个 C++ 库，允许操作 JSON 值，包括字符串之间的序列化和反序列化。它还可以在反序列化/序列化步骤中保留现有注释，使其成为存储用户输入文件的方便格式。

* [常用开发库 - log4cpp](/md/develop/library/library-log4cpp.md)
    * log4cpp: Log4cpp是一个开源的C++类库，它提供了C++程序中使用日志和跟踪调试的功能。

* [常用开发库 - poco](/md/develop/library/library-poco.md)
    * poco: POCO C++库是一组开源C++类库的集合，它们简化及加速了用C++来开发以网络功能为核心的可移植程序的过程。这些库，完美地与C++标准库结合到一起，并且填补了它所留下的那些空缺。它们具有模块化、高效的设计与实现，使得POCO C++库特别适合于进行嵌入式开发。

* [常用开发库 - protobuf](/md/develop/library/library-protobuf.md)
    * protobuf: Protocol Buffers 是一种轻便高效的结构化数据存储格式，可以用于**结构化数据串行化、或者说序列化**。它很适合做数据存储或RPC数据交换格式。可以用于即时通讯、数据存储等领域的语言无关、平台无关、可扩展的序列化结构数据格式。

* [常用开发库 - tinyxml](/md/develop/library/library-tinyxml.md)
    * tinyxml: TinyXML是一个C++的轻量级的XML解析库, 它基于文档对象模型(DOM)来进行解析。在解析时，一次性的将整个XML文档进行分析，并在内存中形成对应的树结构。同时，向用户提供一系列的接口来访问和编辑该树结构。

* [常用开发库 - yamlcpp](/md/develop/library/library-yamlcpp.md)
    * yamlcpp: yaml-cpp是用c++实现的用来解析和生成yaml文件。

* [常用开发库 - zeromq](/md/develop/library/library-zeromq.md)
    * zeromq: ZeroMQ是一种基于消息队列的多线程网络库，其对套接字类型、连接处理、帧、甚至路由的底层细节进行抽象，提供跨越多种传输协议的套接字。ZeroMQ是网络通信中新的一层，介于应用层和传输层之间（按照TCP/IP划分），其是一个可伸缩层，可并行运行，分散在分布式系统间。
