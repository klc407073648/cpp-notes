# 架构设计原则 - 发展历程（六边形架构、洋葱架构、整洁架构、清晰架构）

[[toc]]

# 参考资料

* [DDD中常提到的应用架构总结（六边形、洋葱、整洁、清晰）](https://blog.csdn.net/luo15242208310/article/details/124708008)

# 架构发展
   
DDD应用架构设计时，接触到了不同的应用架构设计概念，如六边形架构、洋葱架构、整洁架构、清晰架构等，在本文中对这些架构进行了简单的介绍和总结。

这些架构随时间的演进可参见下图：

![架构发展](/_images/method/arch-principle/架构发展.png)

# EIC(Entity-Interface-Control) & EBI（Entity-Boundary-Interactor）

1992年由Ivar Jacobson提出EIC(Entity-Interface-Control) 架构，之后Robert C. Martin在一次关于整洁架构Clean Architecture的演讲中将其调整为EBI（Entity-Boundary-Interactor），即：

* Entity => Entity: 维持不变
* Interface => Boundary: 避免和编程语言中的interface相混淆
* Control => Interactor: 避免和MVC Controller相混淆

![EBI架构](/_images/method/arch-principle/EBI架构.png)

备注：参考上图EBI架构，图片中的矩形边数或边界数量为4，若将其修改为6边型，即可演进为2005年（13年后）提出的六边形架构，即可以将其视为六边形架构（端口、适配器架构）思想的前身。

EBI对象类型说明如下：

* Entity: 实体对象，包含数据、行为（避免贫血模型anaemic entities）
* Boundary(Interface): 系统与外界交互的边界，即对应bounday object，如controller实现（主动）、持久化实现（被动）、消息通知（被动）等。
* Interactor(Control): 所有不适合放在Entity和Boundary的行为都需要放在Interactor对象中，等价于DDD中的：
    * Application Services（who orchestrate(编排) use cases) - DDD架构中的应用服务层
    * Domain Services (who contain Domain behaviour but are not entities) - DDD架构中的领域服务层

类比MVC(Model View Controller)模式，

* 模型层Model即表示整个后端back-end，包括services、entities等
* 表现层Presentation即包含View层、Controller层
* View层、Controller层即为Boundary，
* Entity即为实体数据及其关联的行为操作（充血模型）
* Interactor（Application Services, Domain Services）即为表现层（View、Controller）和Entity的连接，
* 将MVC和EBI模式组合起来类似：View-Controller-Interactor-Entity

# 端口和适配器架构Ports & Adapters Architecture（又称六边形架构Hexagonal Architecture）

2005年，Alistair Cockburn提出了端口和适配器架构Ports & Adapters Architecture(又称六边形架构Hexagonal Architecture)。

![六边形架构](/_images/method/arch-principle/六边形架构.png)

端口和适配器架构中的相关概念：

* 工具Tools： 应用application使用的工具Tools(WebSerevr, Cli, DB, SearchEngine, MQ)

* 端口Port： 在application core层定义的工具交互规范（即定义 工具Tools如何使用application core的规范 或 工具Tools如何被application core使用的规范），对应编程语言的interface定义，且端口定义应该符合应用层逻辑（不可简单模仿或者直接使用底层工具的API）

* 适配器Adapter： 连接工具Tools(WebSerevr, Cli, DB, SearchEngine, MQ)和应用核心application core的代码单元
    * 适配器依赖port（调用port 或 实现port）和工具，但是application core仅依赖port。

* 主动适配器（Primary/Driving Adapters ） - 主动调用应用核心Application Core，触发应用执行某项活动
    * 主动适配器 -> 依赖端口 -> 注入端口实现，
    * 例如主动适配器Controller -> 依赖端口ServiceInterface -> 注入端口实现ServiceImpl

* 被动适配器（Secondary/Driven Adapters） - 被应用核心Application Core调用来执行动作，实现应用定义的端口
    * 端口 -->被动适配器实现端口逻辑-> 包装系统外部工具，
    * 例如端口RespositoryInterface -> 被动适配器Mysql实现MysqlRepositoryImpl -> 调用Mysql数据库

几边形不重要，可以N多边，重点是Port & Adapter思想，关于端口和适配器架构的优势：

* 核心业务在最中心（最重要），
* 核心业务依赖Port，Adapter依赖Port（主动） 或 Adapter为Port的具体实现（被动），
* 核心业务逻辑与实现细节（技术框架、底层存储、工具、传输通信机制等）相隔离，
* 保持核心业务逻辑的可重用性，
* 可通过（注入）不同Adapter实现来切换技术实现，避免技术框架、工具、供应商锁定，
* 且基于mock Port的形式更易于测试。

# 洋葱架构Onion Architecture

洋葱架构（Onion Architecture） 在2008年由Jeffrey Palermo提出。

![洋葱架构](/_images/method/arch-principle/洋葱架构.png)

洋葱架构 构建在Port & Adapter架构（又称六边形架构）之上，在Port & Adapter架构中仅提到2层：

1. 外层 - 表示传输（通信）机制和基础设施infrastructure
2. 内层 - 业务逻辑

而洋葱架构在DDD的基础上，将内层（业务逻辑层，Business Logic）进一步划分，最终为：

* Adapters，即六边形架构中的适配器Adapter层
    * User Interface、Infrastructure、Tests
* Application Core，应用核心层，也即原来的六边形架构中心的Business Logic层
    * Application Services - 应用服务册层
    * Domain Services - 领域服务层
    * Domain Model - 领域模型层

且明确了依赖方向：

* 外层依赖内层
* 内层不知道外层
* 且在不破坏依赖方向的前提下，外层亦可以直接调用任一内层（不一定是相邻接的2层），参考CQRS中Query实现（Application Services直接调用DAO）

# 整洁架构Clean Architecture

2012年Robert C. Martin (又名Uncle Bob) 提出了整洁架构Clean Architecture，整洁架构将EBI、六边形架构Hexagonal、洋葱架构Onoin等整合成一个可以实际落地的架构。

![Clean-Architecture-Cone](/_images/method/arch-principle/Clean-Architecture-Cone.png)

与洋葱架构相比，整洁架构调整如下：

* Application Services调整为Use Cases
* Domain Services, Domain Model调整为Entities

整洁架构并没有带来突破性的概念或模式，但是：

* 它发掘了某种程度上被遗忘了的概念、规则和模式；
* 它澄清了一些实用且重要的概念、规则和模式；
* 它告诉我们如何把所有的概念、规则和模式整合起来，形成一种构建复杂应用并保持可维护性的标准套路

# 清晰架构Explicit Architecture

2017年Herberto Graca在其软件架构编年史系列文章中提出清晰架构Explicit Architecture，即将DDD, Hexagonal, Onion, Clean, CQRS等进行融合后的架构。

![清晰架构](/_images/method/arch-principle/清晰架构.png)

* 最中心的红色多边形Application Core即表示业务逻辑实现，即应用核心
    * 红色多边形的边界即表示端口Port，即应用核心的入口/出口定义
    * Application Layer - 应用层，包括：
        * Application Services，业务用例的编排服务即及其interface定义，应用服务的作用通常如下：
            * 使用 Repostitory 查找一个或多个实体；
            * 让这些实体执行一些领域逻辑；
            * 再次使用 Repostitory 让这些实体持久化，有效地保存数据变化；
            * 触发应用事件（如发送邮件、调用第三方API、发送MQ消息等）。
        * CQRS命令/查询处理器
        * Event Listener事件监听器
        * Port端口定义，如ORM 接口Repostitory、搜索引擎接口、消息接口等等
    * Domain Layer - 领域层，这一层含了数据和操作数据的逻辑，它们只和领域本身有关，独立于调用这些逻辑的业务过程。它们完全独立，对应用层完全无感知。
        * Domain Services - 领域服务，封装涉及多实体（相同或不同实体类型）的领域逻辑，且领域服务间可以相互调用。
        * Domain Models - 领域模型，在架构的正中心，完全不依赖外部任何层次的领域模型。它包含了那些表示领域中某个概念的业务对象，如实体、值对象、枚举以及其它领域模型种用到的任何对象（如领域事件Domain Events，简单理解为MQ消息）。
* 红色多边形的外侧左半圆部分即为主/主动适配器（用户界面User Interface实现）
    * 如Spring MVC中的Controller实现
    * Command Query Bus 命令查询总线
* 红色多边形的外侧右半圆部分即次/被动适配器（基础设置Infrastructure实现）
    * 如数据持久化实现Mysql、短信通知实现、MQ通知、搜索引擎ES实现等
    * Event Bus 事件总线
* 依赖方向由外到内，且内层不知道外层（参见之前洋葱架构）

采用按组件分包Package By Component，即整合传统按层分包Package By Layer和按特性分包Package By Feature，组件Component可以理解为专属于特定一个领域内的业务逻辑服务和数据访问逻辑的组合，也可以理解为特定领域，如账单、用户、评论或帐号等。

A “component” in this sense is a combination of the business and data access logic related to a specific thing (e.g. domain concept, bounded context, etc).

在清晰架构中可以理解为：

* 先按照层次进行分包
    * 表现层Presentation
    * 业务核心层Application Core
    * 基础设施层Infrastructure）

* 之后每一层次再按照特性分包

![清晰架构分包](/_images/method/arch-principle/清晰架构分包.png)

> 清晰架构只是一份指南！

```
应用才是疆域，现实情况和具体用例才是运用这些知识的地方，它们才能勾勒出实际架构的轮廓！
我们需要理解所有这些模式，
但我们还时常需要思考和理解我们的应用需要什么，我们应该在追求解耦和内聚的道路上走多远。
这个决定可能受到许多因素的影响，
包括项目的功能需求，也包括构建应用的时间期限，应用寿命，开发团队的经验等等因素。
```

附国内大神翻译的清晰架构中文版：

![清晰架构高清中文](/_images/method/arch-principle/清晰架构高清中文.png)

# 整体发展过程

关于传统分层、六边形、洋葱、整洁、清晰架构的演进可参见下图：

![整体发展过程](/_images/method/arch-principle/整体发展过程.png)