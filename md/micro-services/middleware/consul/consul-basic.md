# Consul - 简介

[[toc]]

## 概念

Consul是HashiCorp公司推出的开源工具，Consul由Go语言开发，部署起来非常容易，只需要极少的可执行程序和配置文件，具有绿色、轻量级的特点。

Consul是**<font color='red'>分布式的、高可用的、 可横向扩展</font>**的用于实现分布式系统的服务发现与配置。

## 特点

* 服务发现（Service Discovery）
  * Consul提供了通过DNS或者HTTP接口的方式来注册服务和发现服务。
  * 一些外部的服务通过Consul很容易的找到它所依赖的服务。
* 健康检查（Health Checking）
  * Consul的Client可以提供任意数量的健康检查，既可以与给定的服务相关联(“webserver是否返回200 OK”)，也可以与本地节点相关联(“内存利用率是否低于90%”)。
  * 操作员可以使用这些信息来<font color='red'>监视集群的健康状况</font>，服务发现组件可以使用这些信息将流量从不健康的主机路由出去。
* Key/Value存储
  * 应用程序可以根据自己的需要使用Consul提供的Key/Value存储。 
  * Consul提供了简单易用的HTTP接口，结合其他工具可以实现动态配置、功能标记、领袖选举等等功能。
* 安全服务通信
  * Consul可以为服务生成和分发TLS证书，以建立相互的TLS连接。
  * 可以使用<font color='red'> intentions 定义允许哪些服务进行通信</font>。可以使用 intentions 轻松管理服务隔离，而不是使用复杂的网络拓扑和静态防火墙规则。
  * 服务分割可以很容易地进行管理，其目的是可以实时更改的，而不是使用复杂的网络拓扑和静态防火墙规则。
* 多数据中心
  * Consul支持开箱即用的多数据中心. 这意味着用户不需要担心需要建立额外的抽象层让业务扩展到多个区域。

## Consul 角色

- CLIENT
  - CLIENT表示consul的就是客户端模式。<font color='red'>所有注册到当前节点的服务会被转发到SERVER，本身是不持久化这些信息。</font>
  - 作用是将 HTTP 和 DNS 接口请求转发给局域网内的服务端集群。


- SERVER
  - SERVER表示consul的服务端模式。功能和CLIENT都一样，唯一不同的是，它会把所有的信息持久化的本地，这样遇到故障，信息是可以被保留的。
  - 在局域网内与本地客户端通讯, 通过广域网与其它数据中心通讯。 
  - 每个数据中心的 Server 数量推荐为 3 个或是 5 个。


- SERVER-LEADER
  - 中间那个SERVER下面有LEADER的字眼。表明这个SERVER是它们的老大，它和其它SERVER不一样的一点是，它需要负责<font color='red'>同步注册的信息给其它的SERVER，同时也要负责各个节点的健康监测。</font>


## Consul 架构图

 <img src="/_images/micro-services/middleware/consul/架构图.png" alt="架构图" style="zoom: 25%;" />

如图所示，有两个数据中心，分别标记为“1”和“2”。Consul拥有对多个数据中心的一流支持，这是比较常见的情况。

在每个数据中心中，都有客户机和服务器。预计将有三到五台服务器。这在故障情况下的可用性和性能之间取得了平衡，因为随着添加更多的机器，一致性会逐渐变慢。但是，客户端的数量没有限制，可以很容易地扩展到数千或数万。

Consul 实现多个数据中心都依赖于gossip protocol协议。这样做有几个目的:首先，不需要使用服务器的地址来配置客户端;服务发现是自动完成的。其次，健康检查故障的工作不是放在服务器上，而是分布式的。这使得故障检测比单纯的心跳模式更具可伸缩性。为节点提供故障检测;如果无法访问代理，则节点可能经历了故障。

每个数据中心中的服务器都是一个筏对等集的一部分。这意味着它们一起工作来选举单个leader，一个被选中的服务器有额外的职责。领导负责处理所有的查询和事务。事务还必须作为协商一致协议的一部分复制到所有对等方。由于这个需求，当非leader服务器接收到RPC请求时，它会将其转发给集群leader。

## Consul的调用过程

 <img src="/_images/micro-services/middleware/consul/consul调用过程.png" alt="架构图" style="zoom: 100%;" />

1. 当 Producer 启动的时候，会向 Consul 发送一个 post 请求，告诉 Consul 自己的 IP 和 Port；

2. Consul 接收到 Producer 的注册后，每隔 10s（默认）会向 Producer 发送一个健康检查的请求，检验 Producer 是否健康；

3. 当 Consumer 发送 GET 方式请求 /api/address 到 Producer 时，会先从 Consul 中拿到一个存储服务 IP 和 Port 的临时表，从表中拿到 Producer 的 IP 和 Port 后再发送 GET 方式请求 /api/address；

4. 该临时表每隔 10s 会更新，<font color='red'>只包含有通过了健康检查的 Producer</font>。
   

## Consul的使用场景

Consul的应用场景包括服务发现、服务隔离、服务配置：

* 服务发现场景中consul作为注册中心，服务地址被注册到consul中以后，可以使用consul提供的dns、http接口查询，consul支持health check。
* 服务隔离场景中consul支持以服务为单位设置访问策略，能同时支持经典的平台和新兴的平台，支持tls证书分发，service-to-service加密。
* 服务配置场景中consul提供key-value数据存储功能，并且能将变动迅速地通知出去，借助Consul可以实现配置共享，需要读取配置的服务可以从Consul中读取到准确的配置信息。
* Consul可以帮助系统管理者更清晰的了解复杂系统内部的系统架构，运维人员可以将Consul看成一种监控软件，也可以看成一种资产（资源）管理系统。
