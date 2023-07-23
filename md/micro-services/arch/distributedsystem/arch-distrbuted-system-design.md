# 分布式系统 - 相关设计

[[toc]]

# 幂等性设计

* [幂等性设计](/md/micro-services/frame/frame-idempotent-design.md)

# 服务治理

## 服务注册与发现

* Zookeeper
* Eureka
* etcd
* Consul

![](/_images/micro-services/arch/distributedsystem/服务注册与发现.png)

## 服务熔断

在互联网系统中，当下游服务因访问压力过大而响应变慢或失败，上游服务为了保护系统整体的可用性，可以暂时切断对下游服务的调用。

# 常用框架

![](/_images/micro-services/arch/distributedsystem/常用框架.png)

## Dubbo

* [Dubbo](/md/micro-services/frame/frame-idempotent-design.md)

## SpringCloud

::: details
* 服务治理

  + 服务注册与发现

    - Netflix Eureka(保证AP)
    - Consul(保证CP)

* 服务网关 Zuul

  + 统一接入

    - 请求路由
    - 版本控制
    - 容错性
    - 服务埋点
    - 缓存
    - 负载均衡

  + 流量监控

    - 限流
    - 降级

  + 安全防护

    - 防止恶意攻击

			- IP黑白名单
			- 频率限制
			- 频次限制

    - 鉴权
    - 内外网隔离

  + 业务隔离
::: 

# 缓存

* Redis

# 提高架构稳定性

![](/_images/micro-services/arch/distributedsystem/提高架构稳定性.png)

# 提高架构性能

![](/_images/micro-services/arch/distributedsystem/提高架构性能.png)

# 通信方式

![](/_images/micro-services/arch/distributedsystem/通信方式.png)

* [通信方式](/md/micro-services/arch/distributedsystem/arch-distrbuted-system-communication-mode.md)

# 监控和调度

**应用整体监控**

![](/_images/micro-services/arch/distributedsystem/应用整体监控.png)

**资源服务调度**

![](/_images/micro-services/arch/distributedsystem/资源服务调度.png)

**状态数据调度**

![](/_images/micro-services/arch/distributedsystem/状态数据调度.png)

**流量调度**

![](/_images/micro-services/arch/distributedsystem/流量调度.png)