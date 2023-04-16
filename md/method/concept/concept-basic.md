# 概念 -概述

[[toc]]

# 概念

* unix环境高级编程(Advanced programming in the unix environment,简称APUE)
* unix网络编程(UNIX Network Programming,简称UNP)

* IDL(接口描述语言)
    * 概念："IDL是Interface description language的缩写，指接口描述语言，是CORBA规范的一部分，是跨平台开发的基础。明用
    * 应用：对于跨语言调用业界一般选择使用IDL来描述接口定义，并来通过工具自动生成的**桩代码序列化、反序列码、解析RPC请求包**，grpc和thrift都是通过这种方式实现的多语言支持。
    
* Web应用防护系统（也称为：网站应用级入侵防御系统。英文：Web Application Firewall，简称： WAF）

* 物联网（英语：Internet of Things，缩写IoT）是互联网、传统电信网等信息承载体，让所有能行使独立功能的普通物体实现互联互通的网络。

* B2B(Business-to-business)：企业对企业，企业之间的商业交易，如制造商和批发商之间，或批发商和零售商之间。
* B2C(Business-to-consumer)：企业对消费者是直接向客户销售产品的商业模式，从而绕过任何第三方零售商、批发商或任何其他中间商。
* B2G(Business-to-government )：企业对政府（B2G），也称为企业对行政，是指作为供应商的企业部门和作为客户的政府机构之间的贸易,属于企业的政企业务。

* GPRS(General Packet Radio Services，通用分组无线业务)是一种新型的分组数据传输业务。

* 物联网是一个基于互联网、传统电信网等的信息承载体，它让所有能够被独立寻址的普通物理对象形成互联互通的网络。TODO补充

* SLA（Service-Level Agreement）服务等级协议，是指系统服务提供者（Provider）对客户（Customer）的一个可量化的服务承诺，常见于大型分布式系统中，用于衡量系统服务是否稳定健康的常见方法。

* Java

    * Servlet（Server Applet）是Java Servlet的简称，称为小服务程序或服务连接器，用Java编写的服务器端程序，具有独立于平台和协议的特性，主要功能在于交互式地浏览和生成数据，生成动态Web内容。
    狭义的Servlet是指Java语言实现的一个接口，广义的Servlet是指任何实现了这个Servlet接口的类，一般情况下，人们将Servlet理解为后者。Servlet运行于支持Java的应用服务器中。从原理上讲，Servlet可以响应任何类型的请求，但绝大多数情况下Servlet只用来扩展基于HTTP协议的Web服务器。

    * POJO(Plain Old Java Object),POJO是这样的一种“纯粹的”JavaBean，在它里面除了JavaBean规范的方法和属性没有别的东西，即private属性以及对这个属性方法的public的get和set方法。我们会发现这样的JavaBean很“单纯”，它只能装载数据，作为数据存储的载体，而不具有业务逻辑处理的能力。

* 前端

    * Axios，是一个基于promise [5]  的网络请求库，作用于node.js和浏览器中，它是 isomorphic 的(即同一套代码可以运行在浏览器和node.js中)。在服务端它使用原生node.js http模块, 而在客户端 (浏览端) 则使用XMLHttpRequest。
    
    * Ajax即Asynchronous Javascript And XML（异步JavaScript和XML）在 2005年被Jesse James Garrett提出的新术语，用来描述一种使用现有技术集合的‘新’方法，包括: HTML 或 XHTML, CSS, JavaScript, DOM, XML, XSLT, 以及最重要的XMLHttpRequest。 [3]  使用Ajax技术网页应用能够快速地将增量更新呈现在用户界面上，而不需要重载（刷新）整个页面，这使得程序能够更快地回应用户的操作

* [云网络](./concept-cloud-network.md)

* [脑裂(Split-brain)](./concept-split-brain.md)

# 临界区

在同步的程序设计中，临界区段（Critical section）指的是一个访问共用资源（例如：共用设备或是共用存储器）的程序片段，而这些共用资源又无法同时被多个线程访问的特性。

当有线程进入临界区段时，其他线程或是进程必须等待（例如：bounded waiting 等待法），有一些同步的机制必须在临界区段的进入点与离开点实现，以确保这些共用资源是被互斥或的使用，例如：semaphore。

访问共享资源的代码区叫做临界区，这里的共享资源可能被多个线程需要，但这些共享资源又不能被同时访问，因此临界区需要以某种互斥机制加以保护，以确保共享资源被互斥访问。linux下没有为临界区提供接口，可以理解成锁范围内的代码：

```cpp
xxx_lock()
//临界区
xxx_unlock()
```

# 墨菲定律

墨菲定律: 简单来说就是事情往往会向你所想到的不好的方向发展，只要有这个可能性。

西方的"墨菲定律"是这样说的: Anything that can go wrong will go wrong: "凡事只要有可能出错，那就一定会出错。"

根据"墨菲定律"可以得出4条结论：

1. 任何事都没有表面看起来那么简单；
2. 所有的事都会比你预计的时间长；
3. 会出错的事总会出错；
4. 如果你担心某种情况发生，那么它就更有可能发生。