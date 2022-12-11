# 技术概念

[[toc]]

# 概念

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



* 云网络  TODO
::: details
AI内智慧网络、云原生网络、确定性网络、算力网络、
分布式自治网络、空天地一体化网络。

The Serverless Framework (无服务器架构）允许你自动扩展、按执行付费、将事件驱动的功能部署到任何云。 

著名的CNCF（Cloud-Native Compute Foundation，云原生计算基金会）成立于2015年，由Google等大公司牵头，
目前有100多家企业成员，其目的是在容器、微服务及devops领域里、通过一系列的规范和标准帮助企业和组织、
在现代的云化环境中构建架构一致的应用。

云原生的三大特征是：容器化封装(docker)、动态和自动化管理(kubernetes)和面向微服务(明确服务间的依赖，互相解耦)。
此外，云原生强调自动化以提升能够开发效率和运维效率。

基于容器和Kubernetes的平台提供了云原生应用的标准发布和运行环境；基于容器的微服务架构定义了云原生
应用的标准架构。通过这些技术，为软件应用在架构、支撑服务和支持组件、基准平台上进行了标准化；
同时通过这些技术，解决了升级、扩容、稳定性、私有云/公有云/混合云统一基础架构等问题。

微服务架构的重要目标就是：快速发布，那么就需要在敏捷文化、自动化工具链上对流程提出了高要求。


CNCF对于网络架构的定义，可以看到Runtime这一层又可以分为资源管理、云原生网络、云原生存储。

云原生网络

容器网络VS传统网络
::: 

* [脑裂(Split-brain)](https://en.wikipedia.org/wiki/Split-brain_(computing))

::: details
wiki百科概念：

> Split-brain is a computer term, based on an analogy with the medical Split-brain syndrome. It indicates **data or availability inconsistencies** originating from the maintenance of **two separate data sets** with overlap in scope, either because of servers in a network design, or a failure condition based on servers not **communicating and synchronizing** their data to each other. This last case is also commonly referred to as a network partition.

> High-availability clusters usually use a heartbeat private network connection which is used to **monitor the health and status** of each node in the cluster. 

Approaches for dealing with split-brain：

1. The optimistic approaches simply let the partitioned nodes work as usual; this provides a greater level of availability, at the cost of sacrificing correctness. Once the problem has ended, automatic or manual reconciliation might be required in order to have the cluster in a consistent state. One current implementation for this approach is Hazelcast, which does automatic reconciliation of its key-value store.[3]

2. The pessimistic approaches sacrifice availability in exchange for consistency. Once a network partitioning has been detected, access to the sub-partitions is limited in order to guarantee consistency. A typical approach, as described by Coulouris et al.,[4] is to use a quorum-consensus approach. This allows the sub-partition with a majority of the votes to remain available, while the remaining sub-partitions should fall down to an auto-fencing mode. One current implementation for this approach is the one used by MongoDB replica sets.[5] And another such implementation is Galera replication for MariaDB and MySQL.[6]

3. Modern commercial general-purpose HA clusters typically use a combination of heartbeat network connections between cluster hosts, and quorum witness storage. The challenge with two-node clusters is that adding a witness device adds cost and complexity (even if implemented in the cloud), but without it, if heartbeat fails, cluster members cannot determine which should be active. In such clusters (without quorum), if a member fails, even if the members normally assign primary and secondary statuses to the hosts, there is at least a 50% probability that a 2-node HA cluster will totally fail until human intervention is provided, to prevent multiple members becoming active independently and either directly conflicting or corrupting data.

产生条件：

* 分区数据因通信或同步原因，产生双主或多主的场景。

解决方法：

1. 乐观的方法：
    * 以牺牲正确性为代价，让分区节点照常工作，即提供了更高级别的可用性。等到分区恢复后，可能需要自动或手动调节，以使集群处于一致状态。（Hazelcast就是采用该方法，它对其键值存储进行自动调节）
2. 悲观的方法：
    * 以牺牲可用性换取一致性。一旦检测到网络分区，就限制对子分区的访问，以保证一致性。可以采用投票选举方式(quorum-consensus approach)。这允许具有多数投票权的分区保持可用，而剩余的子分区应降至自动隔离模式(auto-fencing mode)。(MongoDB副本集使用;MariaDB和MySQL的Galera复制)

3. 现代商用HA集群：
    * 使用集群主机之间的心跳网络连接和仲裁见证存储。
    * 添加仲裁节点，增加额外成本和复杂性
    * 没有仲裁，当心跳网络中断，集群无法确定应该存活。
    
补充：

仲裁（Quorum）：法定数量，预先规定具有投票权的节点或见证（Witness）的数量；
::: 