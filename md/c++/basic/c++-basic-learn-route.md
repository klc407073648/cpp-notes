# C++ 基础 - 学习路线

[[toc]]

## C++ 介绍
 
C++ 是一种 <font color='red'>**面向对象的、通用的、静态类型**</font>的编程语言，它是 C 语言的一种扩展。

C++ 语言支持多种编程范式，包括<font color='red'>**面向过程、面向对象、函数式、泛型和元编程形式**</font>的多重泛型编程语言等，因此具有很高的灵活性和可扩展性。

具体含义：
::: details
* **面向过程**: 关注处理过程，“确定你需要的过程并采用你能找到的最好的算法”。
* **面向对象**: 关注问题中的事物，根据问题“确定你需要哪些类，为每个类提供完整的一组操作，利用继承明确表示共性。”。
* **函数式编程**: 将计算机运算看作是数学中函数的运算，避免了状态以及变量的概念。
* **泛型编程**: 利用模板，将原本特定于某个类型的算法或类当中的信息抽取出来作为模板参数，支持开发一般化可重复使用的算法。
* **元编程**: 编写某类计算机程序，该计算机程序以数据的形式编写或操纵其他程序。
:::

C++ 相对于其他高级语言（比如 Java）来说，更加底层，因此具有**高性能、可移植、可重用**等优点，被广泛应用于系统开发、嵌入式系统、服务端开发、游戏开发、图形学、音视频处理、金融分析等领域。

C++ 标准语法的发展也是非常快的，目前最新标准都到C++20了。

可以参见: [C++20特性](/md/c++/features/c20/c++-features-c20.md)

## 就业方向选择

### 服务端开发

即常说的后端开发了。C++ 语言在高性能服务器开发、大数据处理、金融领域等都有广泛应用。对于用户/并发量非常高的系统（比如，抖音、微信、天猫），通常会选择更高性能的 C++ 框架来开发。服务端开发工程师除了要学习后端都要学习的通用知识（比如：设计模式、数据库、缓存），还需要更熟悉网络编程（抓包分析）、并发编程、内存管理等技术。

::: details
* 熟练掌握C/C++/Java/Go/Python/PHP等至少一门服务端编程语言；
* 深刻理解计算机原理，有良好的数据结构和算法基础；
* TCP/UDP网络协议及相关编程、进程间通讯编程； ———— 计算机网络知识
* 熟悉Mysql 、Redis、MQ等常用开源组件，了解原理(校招)；
    *有数据库使用调优经验；
    * 掌握缓存、消息队列的技术原理，有实际项目经验；.
    *熟悉mysql等关系型数据库、redis等非关系型数据库、kafka等消息系统，并了解相关的设计原理(社招)
* 有大型分布式系统设计或开发经验优先； (加分项)
* 分布式系统设计与开发、负载均衡技术，系统容灾设计，高可用系统等知识  (加分项)
:::

### 系统开发

高性能的 C++ 无疑是系统开发的不二选择！系统开发工程师负责设计和实现操作系统、驱动程序、嵌入式系统、网络协议栈等**系统级**软件，从事这个岗位必须熟练掌握 C++ 的常用语法、各种数据结构、算法、多线程编程、Linux 操作系统等技术。

### 客户端开发

一般是指开发用户看到的界面。C++ 语言在桌面应用程序、移动应用程序和游戏开发中有着广泛应用。C++ 客户端开发工程师和前端开发有着相似的学习
要求，都需要掌握 GUI 编程、布局知识、跨平台开发技术。现在主流的开发软件是 Qt。

::: details
* 有linux+QT项目开发经验优先，能够独立解决项目的编译.调试等基本问题；；
* 熟练Qt应用程序图形界面开发，熟悉掌握Qt库各控件使用及架构，能独立完成单个项目；
* 能熟练运用VS，Qt进行跨平台软件开发，熟悉设计模式；
:::

### 嵌入式开发

因为C++ 的高性能，它被广泛应用于网络设备、汽车电子、智能家居、医疗设备等产品。嵌入式开发工程师，经常需要和硬件打交道，例如单片机、ARM32、各种传感器、蓝牙、wifi模块等，需要掌握一定的电路设计能力，且需要具备C/C++ 系统级编程以及操作系统知识。此外，还需要了解嵌入式开发平台和相关工具等。

::: details
* 熟悉x86，arm架构以及stm32等单片机；
* 熟悉Linux内核和驱动开发，熟练掌握stm32等裸机开发；
* 熟悉TCP/IP、UDP、I2C、SPI、CAN、485、232等通信协议和开发；
* 掌握设计PCB硬件电路设计和绘制，具备电路焊接、电气硬件维护、部署、整合能力；
:::

### 游戏开发

C++ 语言是游戏开发的主语言之一（另一个是 C#），当下很火的虚幻引擎的主语言就是 C++！对于游戏开发工程师，最重要的是**热爱游戏**！然后游戏开发也分界面和后台开发，前者需要熟悉游戏引擎、图形渲染、物理引擎、游戏专项技术等技术，后者和服务端开发的要求差不多，都要学好网络编程、并发编程。

::: details
* 在图形学、网络同步、UI框架、Gameplay、工具链等某个游戏相关领域有一定深入的了解和积累；
* 熟悉Unity，UE4等至少一种3D引擎，熟练掌握UE4优先；
* 熟悉UE或Unity引擎，具备扎实的数学和算法基础；
* 熟悉游戏前沿技术，熟悉图形学，熟悉常用的GPU调试工具和方法；
* 熟悉卡通渲染、有RPG/ACT游戏开发经验者优先。
* 掌握引擎动画系统，具有高表现的技能动画、Locomotion等开发能力；
* 熟悉常用的游戏AI技术（例如行为树，HFSM等），能够针对项目需求设计个体、群体AI的技术方案；
* 在框架设计、渲染、动画, 网络同步, 物理、游戏AI等其中某一技术领域有丰富的经验； 
* 丰富的3D游戏引擎实践经验, 了解其关键技术实现原理, 并有实际的二次开发维护经验；
:::

### 音视频处理

考虑到 C++ 的高性能，它在音视频编解码、视频渲染等领域有着非常广泛的应用！音视频处理工程师除了 C++ 基础知识外，还需要熟悉**音视频格式、编解码技术、图形学**等相关技术。

::: details
* 熟悉Android平台开发技术或对Android平台的音视频相关技术有一定程度的了解
* 熟悉常见的音视频标准和协议：h.264，H265，aac，opus，rtp，rtmp，flv等；
* 熟悉音视频相关技术包括FFmpeg/opengl等，熟悉服务端相关技术，对web音视频有一定的熟悉和了解；
* 熟悉音视频采集、编码、渲染：Linux，Windows，Android，IOS；
* 了解FFmpeg/OpenGL/MediaCodec的使用或有相关实际应用开发经验的优先
:::

### 图像处理

和音视频处理类似，都属于 C++ 计算类工作。图像处理工程师需要**熟悉图像处理算法、计算机视觉**等，掌握各种 C++ 的图像处理库和相关算法。图像处理和音视频处理这方面的工作细分内容可能比较多，而且这类工作对数学会有一定要求，有些公司可能把它们定义为 “算法工程师”，常用的开源图像库如OpenCV。

::: details
* 熟悉手机端图像算法的开发，熟悉OpenGL ES，熟悉OpenCV。
* 支持短视频、图像等方向的研发工作
* 负责特效渲染、人像美化能力的规划和建设
:::

### SDK开发

C++ 也适用于开发各种 SDK（软件开发工具包）。SDK 开发工程师需要熟悉C++ 的语言特性、SDK / API 的设计和接口开发、掌握软件开发原则和设计模式，要能够设计出易用、高性能、可靠的 SDK 接口，提供给其他开发者使用。国内这方面的岗位没那么多，很多时候合并到后端（服务端）开发了。

::: details
* 有渲染、导航、诱导播报领域知识经验者佳 有跨平台开发或适配的经验，有移动端（Android）开发经验佳，有车载系统开发经验佳；
:::

### 总结

从上面这些岗位，我们会发现，虽然都是学 C++，但不同方向的工程师需要侧重掌握的技能和专业知识也是有区别的。但是如果你还没确定选什么具体的方
向，不妨先掌握它们都要求的通用技能，即能够熟练使用 C++ 语法来编程。

# 语言选择 ———— C++ or Java

C++ 和 Java 都是非常优秀的主流编程语言，编程语言和技术没有绝对的优劣之分，<font color='red'>**只不过在不同的场景下，有更优的选择。**</font>

语言只是工具，编程思想才是核心。不过，选择好的工具也是至关重要的，“好的抓手才能带来更大的赋能”。

* C++: 如果操作系统底层、嵌入式、图像处理、音视频处理、游戏开发等方向感兴趣，建议选择 C++；
* Java: 如果更喜欢开发应用系统、思考和实现业务逻辑，就选择 Java。

除此之外，后台开发需要掌握一定的通用知识，比如数据库、缓存、消息队列、各类中间件、网络编程、Linux命令、Git、计算机基础知识等。

# C++ 学习路线

以服务端开发为例，大致分为以下几个阶段：
1. C++ 基础语法
    * 基础阶段可以看一下[C++教程](https://www.runoob.com/cplusplus/cpp-tutorial.html)
2. C++ 进阶(使用)
3. 计算机基础知识
4. 软件开发通用学习
5. 后台开发相关知识
6. C++ 实战项目
7. C++ 求职面试

# 知识点

## 知识点

基础知识点1：

![](/_images/c++/basic/基础知识点1.png)

基础知识点2：

![](/_images/c++/basic/基础知识点2.png)

## C++ 进阶

上个阶段主要通过看视频来快速入门 C++ 基础编程语法；而这个阶段要做的是巩固基础、学习更多 C++ 的特性、甚至是底层原理，建议大家通过阅读经
典书籍的方式来学习。

### C++ 基础及进阶语法书籍：

* [C++ Primer Plus] ———— 巩固基础
* [Effective C++]  —————— 提高认知，常用技巧
* [More Effective C++]
* [深度探索C++对象模型]  —————— 了解对象模型，构造、析构等函数语义内容
* [STL 源码剖析] ———— 常用数据结构、实现、算法等内容
* [Linux多线程服务端编程——使用muduo C++ 网络库] ————  多线程
* [深入理解计算机系统]  ————  计算机知识概览
* [UNIX网络编程]           ————  网络编程

### 架构类

* [从零开始学架构]
* [大型网站技术架构——核心原理与案例分析]
* [数据密集型应用系统设计]
* [重构改善既有代码的设计]

### 进阶知识图

![](/_images/c++/basic/进阶知识点.png)

# 编程四大件

* [数据结构与算法](/md/programming/data-structure/data-structure-overview.md)
* [计算机网络](/md/programming/network/network-physical.md)
* [操作系统](/md/programming/system/system-overview.md)
* [设计模式](/md/programming/designpattern/designpattern-overview.md)

# 软件开发通用

企业项目研发流程:

* [技术选型 - 如何写一个自己的项目](/md/method/tech/tech-per-prj.md)
* Git & GitHub 
* Linux 系统 <https://www.code-nav.cn/post/1640586295529324545>
* 设计模式 <https://www.code-nav.cn/post/1640588392073150465>
* 软件工程 <https://www.code-nav.cn/post/1640648711119892481>

数据库、Redis、Nginx、消息队列都是通用的。只不过不同编程语言的后端开发用到的具体的开发框架、编程语法会有差别。

比如 Java 的主流开发框架有 Spring Boot、Netty 等，而 C++ 主流开发框架有 Boost、gRPC、crow 等。

# 后端开发通用

这部分知识点几乎适用于所有后端方向的同学（比如 Java、Go、Python等），比如数据库、Redis、Nginx、消息队列都是通用的。只不过不同编程语
言的后端开发用到的具体的开发框架、编程语法会有差别，比如 Java 的主流开发框架有 <font color='red'>**Spring Boot、Netty**</font> 等，而 C++ 主流开发框架有 <font color='red'>**Boost、gRPC、crow**</font> 等。

## 开发框架

* ORM 框架: 操作数据库
    * [ODB](https://www.codesynthesis.com/products/odb/)

* Web 开发框架: 编写 HTTP 接口，可用于应用的后端
    * [Drogon](https://github.com/drogonframework/drogon)
    * [Pistache](https://github.com/pistacheio/pistache)

* RPC 框架: 作用是远程调用其他的服务，可用于实现分布式、微服务架构。
    * [gRPC](https://github.com/grpc/grpc)

* 网络编程库: 让使用者更关注业务逻辑，而不需要关心底层socket通信相关细节。
    * [muduo](https://github.com/chenshuo/muduo)

其他框架: 可以从这个库中按需学习：
    * [awesome-cpp](https://github.com/fffaraz/awesome-cpp)

## 包管理工具

作用是帮你管理复杂的 C++ 项目依赖包。建议学习 conan：

* [conan](https://github.com/conan-io/conan)

# C++ 项目实战

* 工具库
    * [手写简易 STL](https://github.com/Alinshans/MyTinySTL)
    * [简单 JSON 库](https://github.com/dropbox/json11)
    * [简单堆内存分配器](https://github.com/CCareaga/heap_allocator)
    * [XML 解析库](https://github.com/leethomason/tinyxml2)

* 数据库
    * [SQLite](https://github.com/sqlite/sqlite)
    * [KV 存储引擎 LevelDB](https://github.com/google/leveldb)

* 开发框架
    * [网络编程库 muduo](https://github.com/chenshuo/muduo)
    * [超轻量 web 框架 oatpp](https://github.com/oatpp/oatpp)
    * [微信 RPC 框架 phxrpc](https://github.com/Tencent/phxrpc)

* 服务器
    * [轻量级 Web 服务器学习](https://github.com/qinguoyi/TinyWebServer)
    * [超轻量型 Http Server - Tinyhttpd](https://github.com/EZLippi/Tinyhttpd)
    * [高性能 web 服务器项目](https://github.com/linyacool/WebServer)

* 分布式系统
    * [MIT6.824 中文教程](https://mit-public-courses-cntranslatio.gitbook.io/mit6-824/)

# 自学资源

* [⭐ GitHub C++ 专区](https://github.com/topics/cpp)
* [⭐ GitHub C++ 内容合集](https://github.com/fffaraz/awesome-cpp)
* [掘金 C++ 专区](https://juejin.cn/tag/C++)
* 大厂技术博客
* [美团技术团队](https://tech.meituan.com/)
* [阿里技术团队](https://102.alibaba.com/tech/list/)
* [有赞技术团队](https://tech.youzan.com/tag/back-end/)
* [知名 C++ 大佬陈硕的博客](https://blog.csdn.net/solstice/) 
* [C++ 编程技巧](https://abseil.io/tips/) 
* [C++ 之父的一些问答](https://www.stroustrup.com/bsfaqcn.html) 
