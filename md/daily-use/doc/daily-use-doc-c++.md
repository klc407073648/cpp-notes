# 日常使用 - C++常用资源

[[toc]]

# 经典网站

## C++ 专题资源

* ⭐ GitHub C++ 专区：https://github.com/topics/cpp
* ⭐ GitHub C++ 内容合集：https://github.com/fffaraz/awesome-cpp
* 掘金 C++ 专区：https://juejin.cn/tag/C++

## Fluent C++：

> 这个博客涵盖了与 C++ 编程相关的广泛主题，包括高级特性、最佳实践和性能优化。
* 官网：[https://www.fluentcpp.com/](https://www.fluentcpp.com/)

## C++ Insights  ⭐调试必备 

> 用编译器的眼睛看你的源代码。

* 官网：[https://cppinsights.io/](https://cppinsights.io/)

## Bartek's Coding Blog

> 这个博客涵盖了各种 C++ 编程主题，包括内存管理、模板和算法。

## Meeting C++ Blog

> 这个博客提供有关 C++ 编程语言及其社区的新闻、教程和更新。

* 官网：[https://www.meetingcpp.com/](https://www.meetingcpp.com/)

## C++ Truths

> 这个博客提供了关于各种 C++ 编程概念的深入讨论和解释，包括模板、移动语义和 Lambda 表达式。

## 云风的 BLOG

* 官网：[https://blog.codingnow.com/](https://blog.codingnow.com/)

## cplusplus

> 一个学习 C++ 的优秀网站，除了提供相应的教程之外，还有一个很棒的论坛。和其它网站相比，它的价值更多体现在参考上，因为里面解释了许多编程概念，如果对某个特定的东西感到困惑，那么这些概念将会很有帮助。

* 官网：[http://www.cplusplus.com/](http://www.cplusplus.com/)

## cppreference

> cppreference 即 C++ 参考手册，这个网站始终是我的首选，因为它非常简洁，可读性也很强，不但更新及时（已经到 C++20 了），还提供了很好的示例。

* 官网：[https://en.cppreference.com/w/](https://en.cppreference.com/w/)


# C++ 常用库整合

> 关于 C++ 框架、库和资源的一些汇总列表，内容包括：标准库、Web应用框架、人工智能、数据库、图片处理、机器学习、日志、代码分析等。

* 官网：[https://www.cnblogs.com/skyus/articles/8524408.html](https://www.cnblogs.com/skyus/articles/8524408.html)

# 框架

## C++通用框架和库

* [Boost](https://github.com/boostorg) ：大量通用C++库的集合。
* [QT](https://contribute.qt-project.org/) ：跨平台的应用程序和用户界面框架

## 异步事件循环

* [Boost.Asio](https://think-async.com/Asio/) ：用于网络和底层I/O编程的跨平台的C++库。
* [libev](http://libev.schmorp.de/) ：功能齐全，高性能的时间循环，轻微地仿效libevent，但是不再像libevent一样有局限性，也修复了它的一些bug。
* [libevent](https://libevent.org/) ：事件通知库。
* [libuv](https://github.com/libuv/libuv) ：跨平台异步I/O
 
## 数据库

> 数据库，SQL服务器，ODBC驱动程序和工具

* [Hiredis](https://github.com/redis/hiredis)： 用于Redis数据库的很简单的C客户端库
* [LevelDB](https://github.com/google/leveldb)： 快速键值存储库
* [MySQL++](https://tangentsoft.com/mysqlpp/wiki)：封装了MySql的C API的C++ 包装器
 
## 调试

> 调试库， 内存和资源泄露检测，单元测试

* [CppUnit](https://www.freedesktop.org/wiki/Software/cppunit/)：由JUnit移植过来的C++测试框架
* [CTest](https://cmake.org/cmake/help/v2.8.8/ctest.html)：CMake测试驱动程序
* [googletest](http://code.google.com/p/googletest/)：谷歌C++测试框架
 
## 图像处理

* [OpenCV](http://opencv.org/) ： 开源计算机视觉类库

## Jason

* [jsoncpp](https://github.com/open-source-parsers/jsoncpp) ： C/C++的Jason解析生成器

## 日志

* [Log4cpp](http://log4cpp.sourceforge.net/) ：一系列C++类库，灵活添加日志到文件，系统日志，IDSA和其他地方。

## 网络

* [Muduo](https://github.com/chenshuo/muduo) ：用于Linux多线程服务器的C++非阻塞网络库
* [POCO](https://github.com/pocoproject)：用于构建网络和基于互联网应用程序的C++类库，可以运行在桌面，服务器，移动和嵌入式系统。
* [WebSocket++](https://github.com/zaphoyd/websocketpp) ：基于C++/Boost Aiso的websocket 客户端/服务器库
* [ZeroMQ](https://zeromq.org/) ：高速，模块化的异步通信库
 
## 脚本

* [Lua](http://www.lua.org/) ：用于配置文件和基本应用程序脚本的小型快速脚本引擎。
* [luacxx](https://github.com/dafrito/luacxx)：用于创建Lua绑定的C++ 11 API

## 序列化

* [protobuf](http://code.google.com/p/protobuf/) ：协议缓冲，谷歌的数据交换格式。
* [Thrift](https://thrift.apache.org/) ：高效的跨语言IPC/RPC，用于C++，Java，Python，PHP，C#和其它多种语言中，最初由Twitter开发。

## Web应用框架

* [Drogon](https://github.com/drogonframework/drogon): Drogon是一个基于C++14/17的Http应用框架，使用Drogon可以方便的使用C++构
 
## XML

* [TinyXML](https://sourceforge.net/projects/tinyxml/) ：简单小型的C++XML解析器，可以很容易地集成到其它项目中。
* [TinyXML2](https://github.com/leethomason/tinyxml2)：简单快速的C++CML解析器，可以很容易集成到其它项目中。

## 编译器

> C/C++编译器列表

* [Clang](https://clang.llvm.org/) :由苹果公司开发的
* [GCC](https://gcc.gnu.org/)：GNU编译器集合

## 在线编译器

> 在线C/C++编译器列表

* [Compiler Explorer](https://gcc.godbolt.org/)：交互式编译器，可以进行汇编输出
* [Ideone](https://ideone.com/) ：一个在线编译器和调试工具，允许你在线编译源代码并执行，支持60多种编程语言。
 
## 调试器

> C/C++调试器列表

* [GDB](https://www.sourceware.org/gdb/) ：GNU调试器
* [Valgrind](https://valgrind.org/)：内存调试，内存泄露检测，性能分析工具。
 

## 集成开发环境（IDE）

> C/C++集成开发环境列表

* [CLion](https://www.jetbrains.com/clion/)：来自JetBrains的跨平台的C/C++的集成开发环境
* [Microsoft Visual Studio](https://visualstudio.microsoft.com/zh-hans/) ：适用于 Windows 上 .NET 和 C++ 开发人员的最佳综合 IDE。 完整打包了一系列丰富的工具和功能，可提升和增强软件开发的每个阶段。
* [Qt Creator](https://contribute.qt-project.org/)：跨平台的C++，Javascript和QML集成开发环境，也是Qt SDK的一部分。
* [Visual Studio Code](https://visualstudio.microsoft.com/zh-hans/) ：开源、免费、轻量的代码编辑器，可以通过安装插件增强功能，几乎支持任何语言代码的编写。
 
## 构建系统

* [CMake](https://cmake.org/) ：跨平台的免费开源软件用于管理软件使用独立编译的方法进行构建的过程。
* [CPM](https://github.com/iauns/cpm)：基于CMake和Git的C++包管理器
* [Scons](https://www.scons.org/) ：使用Python scipt 配置的软件构建工具
 
## 静态代码分析

> 提高质量，减少瑕疵的代码分析工具列表

* [Cppcheck](http://cppcheck.sourceforge.net/) ：静态C/C++代码分析工具
* [include-what-you-use](https://code.google.com/p/include-what-you-use/) ：使用clang进行代码分析的工具，可以#include在C和C++文件中。
* [OCLint](https://oclint.org/) ：用于C，C++和Objective-C的静态源代码分析工具，用于提高质量，减少瑕疵。