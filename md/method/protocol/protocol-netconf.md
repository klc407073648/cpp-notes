# 协议 - NETCONF协议

> 为了弥补传统命令行和SNMP的缺陷，基于可扩展标记语言XML（Extensible Markup Language）的NETCONF协议应运而生

[[toc]]

# 参考资料

* [什么是NETCONF？](https://info.support.huawei.com/info-finder/encyclopedia/zh/NETCONF.html)

::: danger 
TODO,待补充实践内容 
:::

# 概念

网络配置协议NETCONF（Network Configuration Protocol）为网管和网络设备之间通信提供了一套协议，网管通过NETCONF协议对远端设备的配置进行下发、修改和删除等操作。网络设备提供了规范的应用程序编程接口API（Application Programming Interface），网管可以通过NETCONF使用这些API管理网络设备。

NETCONF是基于**可扩展标记语言XML（Extensible Markup Language）的网络配置和管理协议**，使用简单的基于RPC（Remote Procedure Call）机制实现客户端和服务器之间通信。**客户端可以是脚本或者网管上运行的一个应用程序。服务器是一个典型的网络设备。**

## 为什么需要NETCONF?

**云时代对网络的关键诉求之一是网络自动化，包括业务快速按需自动发放、自动化运维等**。传统的命令行和SNMP已经不适应云化网络的诉求。在网络自动化方面，NETCONF越来越受欢迎，并被广泛采用。

**传统命令行CLI和SNMP的缺陷**

1. 传统命令行是人机接口，配置过程复杂，厂商差异大，人工学习成本高。
    * 在NETCONF出现之前，CLI脚本编写是对网络进行自动配置更改的主要方法。但由于各厂商定义的CLI各不相同，用户需要针对各厂商分别学习和开发适配脚本。同时，频繁变更的命令结构和语法，使得CLI脚本维护困难、成本高昂。
    * 传统命令行输出内容是非结构化的，不可预测、容易变化，导致解析复杂，CLI脚本很难实现自动化解析。

2. SNMP配置效率低，不支持事务机制，更多被用来做**监控类协议**。
    * SNMP采用UDP传输协议，无法提供可靠的、有序的数据传输，缺乏有效的安全性。
    * SNMP缺乏配置事务提交机制，只能对一个一个对象单独配置，而不是面向一个业务。多个对象同时配置时，如果有些成功有些失败，会对网络造成未知影响。
    * SNMP只是单个设备的管理，不支持网络级的配置和多设备配置协同。

NETCONF应运而生

为了弥补传统命令行和SNMP的缺陷，基于可扩展标记语言XML（Extensible Markup Language）的NETCONF协议应运而生。其优点如下：

1. 采用分层的协议框架，更适用云化网络按需、自动化、大数据的诉求。
2. **以XML格式定义消息，运用RPC机制修改配置信息**，这样既能方便管理配置信息，又能满足来自不同制造商设备之间的互操作性。
3. **基于YANG模型对设备进行操作**，可减少由于人工配置错误引起的网络故障。
4. 提供了**认证、鉴权等安全机制，保证了消息传递的安全**。
5. 支持对数据的分类存储和迁移，支持分阶段提交和配置隔离。实现事务机制验证回滚。配置整体生效，可以缩短对网络业务的影响时间。
6. 定义了更丰富的操作接口，并支持基于能力集进行扩展。不同制造商设备可以定义自己的协议操作，以实现独特的管理功能。

## NETCONF是如何工作的？

NETCONF基本网络架构如下图所示，整套系统必须包含至少一个NMS（Network Management System）作为整个网络的网管中心，NMS运行在NMS服务器上，对设备进行管理。

![](/_images/method/protocol/netconf/NETCONF基本网络架构.png)

网络管理系统中的主要元素有：

* 客户端（Client），主要作用如下：
    * 利用NETCONF协议对网络设备进行系统管理。
    * 向NETCONF Server发送RPC请求，查询或修改一个或多个具体的参数值。
    * 接收NETCONF Server主动发送的告警和事件，以获知被管理设备的当前状态。
* 服务器（Server），主要用于维护被管理设备的信息数据并响应客户端的请求。
    * NETCONF Server收到Client的请求后会进行数据解析，然后给NETCONF Client返回响应。
    * 当设备发生故障或其他事件时，NETCONF Server利用Notification机制主动将设备的告警和事件通知给Client，向Client报告设备的当前状态变化。

### NETCONF基本会话建立过程

NETCONF协议使用RPC通信模式，NETCONF Client和Server之间使用RPC机制进行通信。Client必须和Server成功建立一个安全的、面向连接的会话才能进行通信。Client向Server发送一个RPC请求，Server处理完用户请求后，给Client发送一个回应消息。

![](/_images/method/protocol/netconf/NETCONF基本会话建立过程.png)

NETCONF会话建立和关闭的基本流程如下：

1. Client触发NETCONF会话建立，完成SSH连接建立，并进行认证与授权。
2. Client和Server完成NETCONF会话**建立和能力协商**。
3. Client发送一个或多个请求给Server，进行RPC交互（鉴权）。例如：
    * 修改并提交配置。
    * 查询配置数据或状态
    * 对设备进行维护操作。
4. Client关闭NETCONF会话。
5. SSH连接关闭。

## NETCONF的协议框架

NETCONF协议采用了分层结构。每层分别对协议的某一方面进行包装，并向上层提供相关服务。

分层结构使每层只关注协议的一个方面，实现起来更简单，同时使各层之间的依赖、内部实现的变更对其他层的影响降到最低。

![](/_images/method/protocol/netconf/NETCONF协议框架.png)

NETCONF协议划分为四层：由低到高分别为安全传输层、消息层、操作层和内容层。

1. 安全传输层
    * 提供了客户端和服务器之间的通信路径。NETCONF协议可以使用任何符合基本要求的传输层协议承载。
    * NETCONF传输层首选推荐SSH协议，XML信息通过SSH协议承载。

2. 消息层
    * 提供一种简易的不依赖于传输层，生成RPC和通知消息框架的通信协议。
    * 客户端把RPC请求封装在一个<rpc>元素内，发送给服务器；服务器把请求处理的结果封装在一个<rpc-reply>元素内，回应给客户端。

3. 操作层
    * 定义一组基本的操作，作为RPC的调用方法，可以使用XML编码的参数调用这些方法。

4. 内容层
    * 由管理数据内容的数据模型定义。目前主流的数据模型有Schema模型、YANG模型等。
    * Schema是为了描述XML文档而定义的一套规则。设备通过Schema文件向网管提供配置和管理设备的接口。Schema文件类似于SNMP的MIB文件。
    * YANG是专门为NETCONF协议设计的数据建模语言。客户端可以将RPC操作编译成XML格式的报文，XML遵循YANG模型约束进行客户端和服务器之间通信。

### NETCONF报文结构

一个完整的NETCONF YANG请求报文结构如下图所示。

![](/_images/method/protocol/netconf/NETCONF_YANG请求报文结构图.png)

XML作为NETCONF协议的编码格式，用文本文件表示复杂的层次化数据，即支持使用传统的文本编译工具，也支持使用XML专用的编辑工具读取、保存和操作配置数据。

更详细的报文字段含义可参见[NETCONF报文格式](https://support.huawei.com/hedex/hdx.do?docid=EDOC1100195096&tocURL=resources%2Fvrp_netconf_cfg1_0006.html&tocLibId=AZK0510V&tocLibVer=02&ui=1)。

### NETCONF通信模式

Client的RPC请求和Server的回应消息全部使用XML编码，XML编码的<rpc>和<rpc-reply>元素提供独立于传输层协议的请求和回应消息框架。如下为一些基本的RPC元素：

* <rpc>
    * <rpc>元素是用来封装NETCONF Client发送给NETCONF Server的请求。

* <rpc-reply>
    * <rpc-reply>元素用来封装<rpc>请求的应答消息，NETCONF Server给每个<rpc>操作回应一个使用<rpc-reply>元素封装的应答信息。

* <rpc-error>
    * NETCONF Server在处理<rpc>请求的过程中，如果发生任何错误或告警，则在<rpc-reply>元素内只封装<rpc-error>元素返回给NETCONF Client。

* <ok>
    * NETCONF Server在处理<rpc>请求的过程中，如果没有发生任何错误或告警，则在<rpc-reply>元素内封装一个<ok>元素返回给NETCONF Client。

### 配置数据库（Datastores）

所谓配置数据库是关于设备的一套完整的配置参数的集合。NETCONF定义了一个或多个配置数据库的存在，并允许对它们进行配置操作。

NETCONF基本模型中只存在<running/>配置数据库。 其他配置数据库可以由能力集定义，且只在宣称支持该能力集的设备上可用。

* <running/>：运行配置数据库，保存网络设备上当前处于活动状态的完整配置。
    * 在设备上只存在一个此类型的配置数据库，并且始终存在。

* <candidate/>：备用配置数据库，存放设备将要提交到<running/>的各项配置数据的集合。
    * 管理员可以在<candidate/>上进行操作，对<candidate/>的任何改变不会直接影响网络设备。可以通过<commit>指令将备用配置数据提交为设备运行数据。
    * 设备支持此数据库，必须支持NETCONF标准能力集中的Candidate Configuration能力。

* <startup/>：启动配置数据库，存放设备启动时所加载的配置数据，相当于已保存的配置文件。
    * 设备支持此数据库，必须支持NETCONF标准能力集中的Distinct Startup能力。

![](/_images/method/protocol/netconf/各数据库间可支持配置数据迁移.png)

## 什么是NETCONF的能力集？

### 能力集（Capabilities）

能力集是一组基于NETCONF协议实现的基础功能和扩展功能的集合。NETCONF能力集包括由IETF标准组织定义的标准能力集，以及由各设备制造商定义的各自的扩展能力集。设备可以通过能力集增加协议操作，扩展已有配置对象的操作范围。

NETCONF协议提供了定义能力集语法语义的规范，协议允许Client与Server交互各自支持的能力集，Client只能发送Server支持的能力集范围内的操作请求。

具体支持的能力集可以参见NETCONF支持哪些操作和能力？。

### NETCONF能力集交互过程

能力协商是在会话建立阶段，双方通过发送消息给对方来通告自己支持的能力。NETCONF会话一旦建立，Client和Server端会立即向对端发送Hello消息（含有本端支持的能力集列表<hello>元素），通告各自支持的能力集。这样双方就能利用协商后的能力实现特定的管理功能。

能力集协商结果，对于标准能力集（除Notification外），以Server支持的能力集为协商结果，对于扩展能力集，以双方支持的能力集交集为协商结果。

![](/_images/method/protocol/netconf/NETCONF能力交互示意图.png)

一般地，Client和Server经过如下的步骤来完成配置的获取和改变：

* Client和Server建立面向连接的传输协议的会话。
* 通过Hello消息协商彼此支持的功能（Capability），如都支持的NETCONF的最高级版本，从而避免解析时的歧义。
* Client向Server发送<rpc>的请求。
* Server接收并解析<rpc>请求，通过YANG数据模型的定义来验证RPC请求的合法性。
* Server执行<rpc>的请求，执行结果作为<rpc-reply>响应消息返回给Client。
* Client接收并解析响应消息。

### NETCONF支持哪些操作和能力？

NETCONF协议提供一组基本操作，管理设备的配置数据，以及查询设备的配置和状态信息。NETCONF协议还可以根据设备支持的能力集支持附加的操作。

#### NETCONF基本操作

NETCONF协议定义了基本能力base，基本能力定义了一系列操作，用于修改数据库配置、从数据库获取信息等。NETCONF基本能力定义的操作只是NETCONF必须实现的功能的最小集合，而不是功能的全集。

NETCONF支持的9个基本操作如下：

* <get-config>：用来查询全部或部分指定配置数据。可以通过<source>指定不同的配置数据库。
* <get>：用来查询配置数据和状态数据，只能从<running/>配置数据库中获取数据。
* <edit-config>：用来把配置数据加载到指定的目标配置数据库（<running/>或<candidate/>）。设备对<edit-config>中的操作进行鉴权，鉴权通过后，执行相应的修改。
* <copy-config>：用来将一个配置数据库的数据拷贝到另一个配置数据库。
* <delete-config>：用来删除一个配置数据库。其中，<running/>配置数据库不能被删除。
* <lock>：用来锁定指定的配置数据库，独占配置数据库的修改权，防止产生冲突。
* <unlock>：用来取消用户自己之前执行的<lock>操作，但不能取消其他用户的<lock>操作。
* <close-session>：用来正常关闭当前NETCONF会话。
* <kill-session>：用来强制关闭另一个NETCONF会话，只有管理员用户才有权限执行<kill-session>操作。

#### NETCONF标准能力集

除了基本操作能力，NETCONF协议还定义了一系列标准能力集。这些标准能力定义了一些新的操作，使NETCONF功能更加强大，并使其在容错性、可扩展性等方面得到加强，最终将有利于实现基于NETCONF的开放式网络管理体系结构，为设备厂商扩展功能提供有效的途径。

::: details
Writable-running能力
此能力指明设备支持对<running/>配置数据库的写能力，即设备支持对运行的配置进行<edit-config>和<copy-config>操作。

Candidate Configuration能力
此能力指明设备支持<candidate/>备用配置数据库。<candidate/>配置数据库中存放设备一套完整的配置数据。操作这些配置数据时，不会影响设备当前运行的配置数据。

Confirmed Commit能力
此能力指明设备支持协议操作<commit>携带参数<confirmed>和<confirm-timeout>，主要应用于对业务进行试运行、验证的场景中。

<confirmed>：将<candidate/>数据库中的配置数据提交，转化为设备当前运行的<running/>数据库中的配置。
<confirm-timeout>：<commit>操作确认超时时间，单位是秒，缺省值是600秒。
此能力仅在设备支持Candidate Configuration能力时有效。

Rollback on Error能力
此能力指明设备具备错误回滚能力。即支持在<edit-config>操作的<error-option>参数中携带“rollback-on-error”字段，如果在执行<edit-config>操作时出现错误并产生错误元素<rpc-error>，则服务器将停止处理<edit-config>操作，并将配置恢复至执行<edit-config>操作之前的状态。

此能力仅在设备支持Candidate Configuration能力时生效。

Distinct Startup能力
此能力指明设备具备独立启动的能力，即设备能够区分运行数据库<running/>和启动数据库<startup/>。

对<running/>数据库的配置操作不会自动同步到<startup/>数据库，必须执行一个从<running/>到<startup/>的操作（例如<copy-config>操作），才能把<running/>数据库中的数据更新到<startup/>数据库中。

Notification能力
此能力指明设备可以通过NETCONF协议的Notification能力向客户端上报告警和事件，以便客户端及时感知设备配置等的变更。

XPath能力
此能力指明设备具备在<filter>元素中使用XPath表达式作为查询条件的能力。<get>、<get-config>操作可通过XPath查询指定数据。

XPath是XML Path语言，使用路径表达式来为XML文档的各部分寻址，类似文件管理系统中的文件路径。

Validate能力
此能力指明设备具备配置顺序无关下发的能力，即在配置下发时只进行语法校验，不对配置顺序进行校验。在配置提交时进行语义校验，把下发的配置顺序调整正确后提交至<running/>。

URL能力
此能力指明设备具备对自定义路径下的文件进行编辑、拷贝操作的能力，目前支持<edit-config>和<copy-config>操作。支持对URL路径中的密码信息进行保护，支持配置数据导出时密码信息以密文方式输出。

Interleave能力
此能力指明设备支持NETCONF会话多功能重用。用户可在同一个NETCONF会话上同时对设备进行维护操作和告警、事件管理，提升管理效率。

With-defaults能力
此能力指明设备具备处理模型默认值的能力，<get>、<get-config>、<copy-config>操作中支持携带with-defaults参数。
:::

#### NETCONF扩展能力集

除了NETCONF定义的能力集，设备制造商也可以定义自己的能力集，以实现NETCONF定义以外的特色功能。
