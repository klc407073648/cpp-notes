# 协议 - SNMP协议

> 简单网络管理协议,用于监控连接到网络上设备的运行情况。

[[toc]]

# 参考资料

* [什么是SNMP？](https://info.support.huawei.com/info-finder/encyclopedia/zh/SNMP.html)

::: danger 
TODO,待补充实践内容 
https://blog.csdn.net/cj1314528/article/details/123171978
https://blog.csdn.net/my_angle2016/article/details/124348744

配置snmp服务端，然后客户端能访问到服务端状态；
后续再去编写程序服务端侧，能够上报状态到NMS
:::

# 概念

> 简单网络管理协议(Simple Network Management Protocol--SNMP）的原来名字叫做简单网关监控协议（Simple Gateway Monitoring Protocol-SGMP）。

SNMP是广泛应用于TCP/IP网络的网络管理标准协议，该协议**能够支持网络管理系统，用以监测连接到网络上的设备是否有任何引起管理上关注的情况**。SNMP采用轮询机制，提供最基本的功能集，适合小型、快速、低价格的环境使用，而且SNMP以用户数据报协议（UDP）报文为承载，因而受到绝大多数设备的支持，同时保证管理信息在任意两点传送，便于管理员在网络上的任何节点检索信息，进行故障排查。

## 为什么需要SNMP？

随着网络技术的飞速发展，在网络不断普及的同时也给网络管理带来了一些问题：

* 网络设备数量成几何级数增加，使得网络管理员对设备的管理变得越来越困难；同时，网络作为一个复杂的分布式系统，其覆盖地域不断扩大，也使得对这些设备进行实时监控和故障排查变得极为困难。
* 网络设备种类多种多样，不同设备厂商提供的管理接口（如命令行接口）各不相同，这使得网络管理变得愈发复杂。

在这种背景下，SNMP应运而生，通过“利用网络管理网络”的方式：

* 网络管理员可以利用SNMP平台在网络上的任意节点完成信息查询、信息修改和故障排查等工作，工作效率得以提高。
* 屏蔽了设备间的物理差异，SNMP仅提供最基本的功能集，使得管理任务与被管理设备的物理特性、网络类型相互独立，因而可以实现对不同设备的统一管理，管理成本低。
* 设计简单、运行代价低，SNMP采用“尽可能简单”的设计思想，其在设备上添加的软件/硬件、报文的种类和报文的格式都力求简单，因而运行SNMP给设备造成的影响和代价都被最小化。

## SNMP的基本组件

SNMP基本组件包括网络管理系统NMS（Network Management System）、代理进程（Agent）、被管对象（Managed Object）和管理信息库MIB（Management Information Base）。如图所示他们共同构成SNMP的管理模型，在SNMP的体系结构中都起着至关重要的作用。

![](/_images/method/protocol/snmp/SNMP管理模型.png)

### NMS

NMS在网络中扮演管理者角色，是一个采用SNMP协议对网络设备进行管理/监视的系统，运行在NMS服务器上。

* NMS可以向设备上的Agent发出请求，查询或修改一个或多个具体的参数值。
* NMS可以接收设备上的Agent主动发送的Trap信息，以获知被管理设备当前的状态。

### Agent

Agent是被管理设备中的一个代理进程，用于维护被管理设备的信息数据并响应来自NMS的请求，把管理数据汇报给发送请求的NMS。

* Agent接收到NMS的请求信息后，通过MIB表完成相应指令后，并把操作结果响应给NMS。
* 当设备发生故障或者其它事件时，设备会通过Agent主动发送信息给NMS，向NMS报告设备当前的状态变化。

### Managed Object

Managed Object指被管理对象。每一个设备可能包含多个被管理对象，被管理对象可以是设备中的某个硬件，也可以是在硬件、软件（如路由选择协议）上配置的参数集合。

### MIB

MIB是一个数据库，指明了被管理设备所维护的变量，是能够被Agent查询和设置的信息。MIB在数据库中定义了被管理设备的一系列属性：对象的名称、对象的状态、对象的访问权限和对象的数据类型等。通过MIB，可以完成以下功能：

* Agent通过查询MIB，可以获知设备当前的状态信息。
* Agent通过修改MIB，可以设置设备的状态参数。

SNMP的MIB采用树型结构，它的根在最上面，根没有名字。如下图所示的是MIB的一部分，它又称为对象命名树。**每个对象标识符OID（object identifier）对应于树中的一个管理对象**，该树的每个分支都有一个数字和一个名称，并且每个点都以从该树的顶部到该点的完整路径命名，如system的OID为1.3.6.1.2.1.1，interfaces的OID为1.3.6.1.2.1.2。

![](/_images/method/protocol/snmp/OID树结构.png)

## SNMP版本

SNMP有三种版本：SNMPv1，SNMPv2c和SNMPv3。

1. SNMPv1：SNMP的第一个版本，它提供了一种监控和管理计算机网络的系统方法，它基于团体名认证，安全性较差，且返回报文的错误码也较少。它在RFC 1155和RFC 1157中定义。
2. SNMPv2c：第二个版本SNMPv2c引入了GetBulk和Inform操作，支持更多的标准错误码信息，支持更多的数据类型。它在RFC 1901，RFC 1905和RFC 1906中定义。
3. SNMPv3：鉴于SNMPv2c在安全性方面没有得到改善，IETF颁布了SNMPv3版本，提供了基于USM（User Security Module）的认证加密和基于VACM（View-based Access Control Model）的访问控制，是迄今为止最安全的版本。SNMPv3在RFC 1905，RFC 1906，RFC 2571，RFC 2572，RFC 2574和RFC 2575中定义。

## SNMP端口

SNMP端口是SNMP通信端点，SNMP消息传输通过UDP进行，通常使用UDP端口号161/162。有时也使用传输层安全性（TLS）或数据报传输层安全性（DTLS）协议，端口使用情况如下表所示。

表1-1 SNMP端口使用介绍

![](/_images/method/protocol/snmp/SNMP端口使用介绍.png)

## SNMP如何工作？

一旦网络中启动SNMP协议，NMS作为整个网络的网管中心，会对设备进行管理。每个被管理设备都包含驻留在设备上的Agent、多个被管对象和MIB，NMS通过与运行在被管理设备上的Agent交互，由Agent通过对设备端的MIB的操作，完成NMS的指令。

SNMP的工作原理是**将协议数据单元（也称为SNMP GET请求）发送到响应SNMP的网络设备。用户通过网络监控工具可以跟踪所有通信过程，并从SNMP获取数据**。

SNMP规定了几个操作类型来完成各组件之间的信息交换，如下表所示：

表1-2 SNMP操作类型

![](/_images/method/protocol/snmp/SNMP操作类型.png)

### SNMP Traps

SNMP Traps是指**SNMP Agent主动将设备产生的告警或事件上报给NMS，以便网络管理员及时了解设备当前运行的状态**。

SNMP Agent上报SNMP Traps有两种方式：Trap和Inform。

Trap和Inform的区别在于，SNMP Agent通过Inform向NMS发送告警或事件后，NMS需要回复InformResponse进行确认。

**Trap操作工作原理**

Trap不属于NMS对被管理设备的基本操作，它是**被管理设备的自发行为**。**当被管理设备达到告警的触发条件时，会通过SNMP Agent向NMS发送Trap消息，告知设备侧出现的异常情况，便于网络管理人员及时处理**。例如，被管理设备热启动后，SNMP Agent会向NMS发送warmStart的Trap。

这种Trap信息是受限制的。只有在设备端的模块达到模块预定义的告警触发条件时，SNMP Agent才会向管理进程报告。这种方法的好处是仅在严重事件发生时才发送Trap信息，减少报文交互产生的流量。

**Inform操作工作原理**

Inform操作也是被管理设备向NMS主动发送告警。与Trap告警不同的是，被管理设备发送Inform告警后，需要NMS进行接收确认。如果被管理设备没有收到确认信息则：

* 将告警或事件暂时保存在Inform缓存中。
* 重复发送该告警或事件，直到NMS确认收到该告警或者发送次数达到最大重传次数。
* 被管设备上会生成相应的告警或事件日志。

## SNMP的应用

网管可以通过SNMP协议管理设备，如下图所示，管理员要对整个网络的设备进行配置和管理，这些设备分布较为分散，管理员到现场进行设备配置是不现实的。当这些网络设备来自不同的厂商，而每个厂商都提供一套独立的管理接口（比如使用不同的命令行），将使得批量配置网络设备的工作量巨大。因此，在这种情况下，如果采用传统的人工方式，将会带来成本高、效率低的弊端，此时网络管理员可以利用SNMP远程管理和配置其下属设备，并对这些设备进行实时监控。

![](/_images/method/protocol/snmp/网管通过SNMP协议管理设备示意图.png)

在组网中配置SNMP协议，首先需要在管理端配置SNMP管理程序NMS，同时在被管理设备端配置SNMP的Agent。

通过SNMP协议：

* NMS可以通过Agent在任何时候及时地获得设备的状态信息，实现远端控制被管理设备。
* Agent可以及时地向NMS报告设备的当前状态信息。
