# Apollo - 设计

[[toc]]

# 总体设计

如下即是Apollo的基础模型：

1. 用户在配置中心对配置进行修改并发布

2. 配置中心通知Apollo客户端有配置更新

3. Apollo客户端从配置中心拉取最新的配置、更新本地配置并通知到应用

![basic-architecture](/_images/micro-services/middleware/apollo/basic-architecture.png)

## Apollo工作原理

下图是Apollo架构模块的概览

 ![架构图](/_images/micro-services/middleware/apollo/架构图.png)

上图简要描述了Apollo的总体设计，我们可以从下往上看：

* Config Service提供配置的读取、推送等功能，服务对象是Apollo客户端

* Admin Service提供配置的修改、发布等功能，服务对象是Apollo Portal（管理界面）

* Config Service和Admin Service都是多实例、无状态部署，所以需要将自己注册到Eureka中并保持心跳

* 在Eureka之上我们架了一层Meta Server用于封装Eureka的服务发现接口

* Client通过域名访问Meta Server获取Config Service服务列表（IP+Port），而后直接通过IP+Port访问服务，同时在Client侧会做load balance、错误重试

* Portal通过域名访问Meta Server获取Admin Service服务列表（IP+Port），而后直接通过IP+Port访问服务，同时在Portal侧会做load balance、错误重试

* 为了简化部署，我们实际上会把Config Service、Eureka和Meta Server三个逻辑角色部署在同一个JVM进程中

## 各模块概要介绍

### Config Service

* 提供配置的读取、推送等功能
* 服务于Apollo客户端

### Admin Service

* 提供配置的修改、发布等功能
* 服务于Apollo Portal（管理界面）

### Client

* 为应用获取配置，支持实时更新
* 通过Meta Server获取Config Service的服务列表
* 使用客户端软负载SLB方式调用Config Service

### Portal

* 配置管理界面
  通过Meta Server获取Admin Service的服务列表
* 使用客户端软负载SLB方式调用AdminService

### Eureka

* 用于服务发现和注册
* Config Service和Admin Service都是多实例、无状态部署，所以需要将自己注册到Eureka中并保持心跳
* 与Config Service住在一起部署

### Meta Server

* Client通过域名访问Meta Server获取Config Service服务列表（IP+Port）
* Portal通过域名访问Meta Server获取Admin Service服务列表（IP+Port）
* 在Eureka之上架了一层Meta Server用于封装Eureka的服务发现接口，Meta Server相当于一个Eureka Proxy
* 与Config Service住在一起部署

### NginxLB

* 通过与域名系统配合，完成以下功能
* 协助Portal访问MetaServer获取Admin Service服务列表
* 协助Client访问MetaServer获取Config Service服务列表
* 协助用户访问Portal进行配置管理

## 分步执行流程

1. Apollo启动后，Config/Admin Service会自动注册到Eureka服务注册中心，并定期发送保活心跳；
2. Apollo Client和Portal管理端通过配置的Meta Server的域名地址经由Software Load Balancer(软件负载均衡器)进行负载均衡后分配到某一个Meta Server；
3. Meta Server从Eureka获取Config Service和Admin Service的服务信息，相当于是一个Eureka Client；
4. Meta Server获取Config Service和Admin Service（IP+Port）失败后会进行重试；
5. 获取到正确的Config Service和Admin Service的服务信息后，Apollo Client通过Config Service为应用提供配置获取、实时更新等功能；Apollo Portal管理端通过Admin Service提供配置新增、修改、发布等功能。

# 服务端设计

在配置中心中，一个重要的功能就是配置发布后实时推送到客户端。下面我们简要看一下这块是怎么设计实现的。

![release-message-notification-design](/_images/micro-services/middleware/apollo/release-message-notification-design.png)

上图简要描述了配置发布的大致过程：

1. 用户在Portal操作配置发布

2. Portal调用Admin Service的接口操作发布

3. Admin Service发布配置后，发送ReleaseMessage给各个Config Service

4. Config Service收到ReleaseMessage后，通知对应的客户端

# 客户端设计

![client-architecture](/_images/micro-services/middleware/apollo/client-architecture.png)

上图简要描述了Apollo客户端的实现原理：

1. 客户端和服务端保持了一个长连接，从而能第一时间获得配置更新的推送。（通过Http Long Polling实现）

2. 客户端还会定时从Apollo配置中心服务端拉取应用的最新配置。

  * 这是一个fallback机制，为了防止推送机制失效导致配置不更新

  * 客户端定时拉取会上报本地版本，所以一般情况下，对于定时拉取的操作，服务端都会返回304 - Not Modified

  * 定时频率默认为每5分钟拉取一次，客户端也可以通过在运行时指定System Property: `apollo.refreshInterval`来覆盖，单位为分钟。

3. 客户端从Apollo配置中心服务端获取到应用的最新配置后，会保存在内存中

4. 客户端会把从服务端获取到的配置在本地文件系统缓存一份

  * 在遇到服务不可用，或网络不通的时候，依然能从本地恢复配置

5. 应用程序可以从Apollo客户端获取最新的配置、订阅配置更新通知
