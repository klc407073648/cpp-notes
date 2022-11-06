# 服务网格

> Service Mesh 是微服务时代的 TCP/IP 协议。

[[toc]]

# 参考资料

* [Service Mesh服务网格](https://zhuanlan.zhihu.com/p/61901608)
* [Service Mesh](https://philcalcado.com/2017/08/03/pattern_![](/_images/article/knowledge/service_mesh.html) 

# 概述

Service Mesh革命先驱、Buoyant公司CEO —— William Morgan，以及他对Service Mesh的定义和思考:

> A service mesh is a dedicated infrastructure layer for handling service-to-service communication. It’s responsible for the reliable delivery of requests through the complex topology of services that comprise a modern, cloud native application. In practice, the service mesh is typically implemented as an array of lightweight network proxies that are deployed alongside application code, without the application needing to be aware.

> Service Mesh 是一个基础设施层，用于处理服务间通信。云原生应用有着复杂的服务拓扑，Service Mesh 保证请求可以在这些拓扑中可靠地穿梭。在实际应用当中，Service Mesh 通常是由一系列轻量级的网络代理组成的，它们与应用程序部署在一起，但应用程序不需要知道它们的存在。

一言以蔽之：Service Mesh 是微服务时代的 TCP/IP 协议。

# 发展过程

Phil Calçado的文章[《Pattern: Service Mesh》](https://philcalcado.com/2017/08/03/pattern_![](/_images/article/knowledge/service_mesh.html)，详细的介绍了从开发者视角来看，服务开发模式和Service Mesh技术的演化过程。

1. 初期

两台电脑之间的通信

![](/_images/article/knowledge/service_mesh_1.png)

2. 原始通信时代

在实际情况中：

* 需要底层能够传输字节码和电子信号的物理层来完成通信。
* 在TCP协议出现之前，服务需要自己处理网络通信所面临的丢包、乱序、重试等一系列流控问题。
    
因此服务实现中，除了业务逻辑外，还夹杂着对网络传输问题的处理逻辑。

![](/_images/article/knowledge/service_mesh_2.png)

3. TCP时代

为了避免每个服务自己实现一套相似的网络传输处理逻辑。

TCP协议的出现解决了网络传输中通用的流量控制问题。将流控的问题下移，从服务的实现中抽离出来，成为操作系统网络层的一部分。

![](/_images/article/knowledge/service_mesh_3.png)

4. 第一代微服务

在TCP出现之后，机器之间的网络通信不再是一个难题，以GFS/BigTable/MapReduce为代表的分布式系统得以蓬勃发展。

此时，分布式系统又面临着很多新的问题，例如：

* 服务发现（Service Discovery）：解决“我想调用你，如何找到你”的问题。
* 服务熔断（Circuit Breaker）：缓解服务之间依赖的不可靠问题。
* 负载均衡（Load Balancing）：通过均匀分配流量，让请求处理更加及时。
* 安全通讯：包括协议加密（TLS）、身份认证（证书/签名）、访问鉴权（RBAC）等。

![](/_images/article/knowledge/service_mesh_4.png)


5. 第二代微服务

为了避免每个服务都需要自己实现一套分布式系统通信的语义功能。随着技术的发展，一些面向微服务架构的开发框架出现了，如Twitter的Finagle、Facebook的Proxygen以及Spring Cloud等等，这些框架实现了分布式系统通信需要的各种通用语义功能。

因此一定程度上屏蔽了这些通信细节，使得开发人员使用较少的框架代码就能开发出健壮的分布式系统。

![](/_images/article/knowledge/service_mesh_5.png)

6. 第一代Service Mesh

第二代微服务模式看似完美，但开发人员很快又发现，它也存在一些本质问题：

1. 虽然框架本身屏蔽了分布式系统通信的一些通用功能实现细节，但开发者却要花更多精力去掌握和管理复杂的框架本身，在实际应用中，去追踪和解决框架出现的问题也绝非易事；
2. 开发框架通常只支持一种或几种特定的语言，但是微服务的定义中一个重要的特性就是语言无关，但那些没有框架支持的语言编写的服务，很难融入面向微服务的架构体系，想因地制宜的用多种语言实现架构体系中的不同模块也很难做到；
3. 框架以lib库的形式和服务联编，复杂项目依赖时的库版本兼容问题非常棘手，同时，框架库的升级也无法对服务透明，服务会因为和业务无关的lib库升级而被迫升级；

因此以Linkerd，Envoy，NginxMesh为代表的代理模式（边车模式）应运而生，这就是第一代Service Mesh，它将分布式服务的通信抽象为单独一层，在这一层中实现负载均衡、服务发现、认证授权、监控追踪、流量控制等分布式系统所需要的功能，作为一个和服务对等的代理服务，和服务部署在一起，接管服务的流量，通过代理之间的通信间接完成服务之间的通信请求，这样上边所说的三个问题也迎刃而解。

![](/_images/article/knowledge/service_mesh_6.png)

从一个全局视角来看，就会得到如下部署图：

![](/_images/article/knowledge/service_mesh_7.png)

如果暂时略去服务，只看Service Mesh的单机组件组成的网络：

![](/_images/article/knowledge/service_mesh_8.png)

服务网格，即一个由若干服务代理所组成的错综复杂的网格。

7. 第二代Service Mesh

第一代Service Mesh由一系列独立运行的单机代理服务构成，为了提供统一的上层运维入口，演化出了集中式的控制面板，所有的单机代理组件通过和控制面板交互进行网络拓扑策略的更新和单机数据的汇报。这就是以Istio为代表的第二代Service Mesh。

![](/_images/article/knowledge/service_mesh_9.png)


只看单机代理组件(数据面板)和控制面板的Service Mesh全局部署视图如下：

![](/_images/article/knowledge/service_mesh_10.png)


# 总结

Service Mesh具有如下优点：

1. 屏蔽分布式系统通信的复杂性(负载均衡、服务发现、认证授权、监控追踪、流量控制等等)，服务只用关注业务逻辑；
2. 真正的语言无关，服务可以用任何语言编写，只需和Service Mesh通信即可；
3. 对应用透明，Service Mesh组件可以单独升级；

同时，Service Mesh目前也面临一些挑战：

1. Service Mesh组件以代理模式计算并转发请求，一定程度上会降低通信系统性能，并增加系统资源开销；
2. Service Mesh组件接管了网络流量，因此服务的整体稳定性依赖于Service Mesh，同时额外引入的大量Service Mesh服务实例的运维和管理也是一个挑战；


历史总是惊人的相似。为了解决端到端的字节码通信问题，TCP协议诞生，让多机通信变得简单可靠；微服务时代，Service Mesh应运而生，屏蔽了分布式系统的诸多复杂性，让开发者可以回归业务，聚焦真正的价值。