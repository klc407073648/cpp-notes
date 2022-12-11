# 团队 - 陈皓《我做系统架构的一些原则》

[[toc]]

# 文章来源

* [我做系统架构的一些原则](https://coolshell.cn/articles/21672.html)

# 原则一：关注于真正的收益而不是技术本身

对于软件架构来说，我觉得第一重要的是架构的收益：

* 是否可以**降低技术门槛加快整个团队的开发流程**。
    * 能够加快整个团队的工程流程，快速发布，是软件工程一直在解决的问题，所以，系统架构需要能够进行并行开发，并行上线和并行运维，而不会让某个团队成为瓶颈点。
* 是否可以让整个系统可以运行的**更稳定**。
    * 要让整个系统可以运行的更为的稳定，提升整个系统的 SLA（Service-Level Agreement，服务等级协议），就需要对有计划和无计划的停机做相应的解决方案，保证服务的高可用，考虑HA集群。
* 是否可以**通过简化和自动化降低成本**。
    * 最高优化的成本是人力成本，人的成本除了慢和贵，还有**经常不断的 human error**。
    * 如果不能降低**人力成本**，反而需要更多的人，那么这个架构设计一定是失败的。
    * 除此之外，是**时间成本，资金成本**。

# 原则二：以应用服务和 API 为视角，而不是以资源和技术为视角

很多技术和组件已经分不清是 Dev 还是 Ops 的了，所以，需要合并 Dev和 Ops。整体规划，统一设计的方式，才能做到整体的提升。

为了做到整体的提升，需要所有的人都要有一个统一的视角和目标——**要站在服务和对外API的视角来看问题**，而不是技术和底层的角度。

# 原则三：选择最主流和成熟的技术

技术选型是一件很重要的事，**技术一旦选错，那会导致整个架构需要做调整**，而对架构的调整重来都不是一件简单的事。

* 当系统越来越复杂的时候，用户把他们的 PHP，Python, .NET，或 Node.js 的架构完全都迁移到 Java + Go 的架构上来的案例不断的发生。

核心要点：

* 尽可能的使用更为成熟更为**工业化的技术栈**，而不是自己熟悉的技术栈。 
    * 所谓工业化的技术栈，可以看看大多数公司使用的技术栈，例如Google,Alibaba,Tencent等
* 选择全球流行的技术，而不是中国流行的技术
* 尽可能的使用红利大的主流技术，而**不要自己发明轮子，更不要魔改**。
* 绝大多数情况下，如无非常特殊要求，选 Java基本是不会错的。
    * Spring 框架保障，代码很难写烂
    * Java 的社区成熟，需要的各种架构和技术都可以很容易获得以及使用

# 原则四：完备性会比性能更重要

架构原则：

* 使用最科学严谨的技术模型为主，并以不严谨的模型作为补充。
    * 永远使用**完备支持 ACID 的关系型数据库**，然后用 NoSQL 作补充。
* 性能上的东西，总是有很多解的。

# 原则五：制定并遵循服从标准、规范和最佳实践

需要注意的标准和规范：

* 服务间调用的协议标准和规范。
    * 包括 Restful API路径, HTTP 方法、状态码、标准头、自定义头等，返回数据 JSon Scheme等。
* 一些命名的标准和规范。
    * 用户 ID，服务名、标签名、状态名、**错误码**、消息、数据库等
* 日志和监控的规范。
    * **日志格式**，监控数据，采样要求，告警等
* 配置上的规范。
    * 操作系统配置、中间件配置，软件包等
* 中间件使用的规范。
    * 数据库，缓存、消息队列等
* 软件和开发库版本统一。
    * 整个组织架构内，软件或开发库的版本最好每年都升一次级，然后在各团队内统一。

重点：

* Restful API 的规范。
    * 参考[Microsoft](https://github.com/microsoft/api-guidelines)
    * 有一个标准和规范最大的好处就是监视可以很容易地做各种统计分析，控制系统可以很容易的做流量编排和调度。
* 服务调用链追踪。
    *参考[Google Dapper 这篇论文](https://research.google/pubs/pub36356/)
        * 其中最严格的实现是 Zipkin，这也是 Spring Cloud Sleuth 的底层实现。Zipkin 贴近 Google Dapper 论文的好处在于——无状态，快速地把 Span 发出来，不消耗服务应用侧的内存和 CPU。这意味着，**监控系统宁可自己死了也不能干扰实际应用**。
* 软件升级。
    * 定期进行软件版本的升级，保证各个服务依赖的软件版本的统一和一致，从而简化系统架构的复杂度。
    * 而且软件版本的升级，一般**伴随着新的特性的引入，能够提升效率和解决漏洞**。

# 原则六：重视架构扩展性和可运维性


很多技术人员或架构师在做架构设计时，只考虑当下，从来不考虑系统的未来扩展性和可运维性。

但是架构和软件不是写好就完事的，是需要不断修改不断维护的，80%的软件成本都是在维护上。所以，如何让架构有更好的扩展性，可以更容易地运维，这个是比较重要的。需要重点关注下面两个特性：

* 扩展性
    * 容易地加更多的功能，或是加入更多的系统。
    * 要求的是有标准规范且不耦合的业务架构
* 可运维
    * 可以对线上的系统做任意的变更。
    * 要求的则是可控的能力，也就是一组各式各样的控制系统。

* 通过服务编排架构来降低服务间的耦合。
    * 例如，使用 Broker，Gateway，Service Discovery 等中间件来降低服务间的依赖关系。

* 通过服务发现或服务网关来降低服务依赖所带来的运维复杂度。
    * 服务发现可以很好的降低相关依赖服务的运维复杂度，可以很轻松的上线或下线服务，或是进行服务伸缩。

* 一定要使用各种软件设计的原则。
    * 使用SOLID原则，IoC/DIP，SOA 或 Spring Cloud 等 架构的最佳实践，分布式系统架构的相关实践。
    * [微软件的 《Cloud Design Patterns》）](https://learn.microsoft.com/en-us/azure/architecture/patterns/)……等等


# 原则七：对控制逻辑进行全面收口

所有的程序都会有两种逻辑，一种是**业务逻辑**，一种是**控制逻辑**

* 业务逻辑就是完成业务的逻辑
* 控制逻辑是辅助
    * 例如，使用多线程，还是用分布式，是用数据库还是用文件，如何配置、部署，运维、监控，事务控制，服务发现，弹性伸缩，灰度发布，高并发，等等，等等
    * 控制逻辑的技术深度会通常会比业务逻辑要深一些，门槛也会要高一些。
    
所以，最好要专业的程序员来负责控制逻辑的开发，**统一规划统一管理，进行收口**。这其中包括：

* 流量收口。
    * 包括南北向和东西向的流量的调度，主要通过流量网关，开发框架 SDK或 Service Mesh 这样的技术。
* 服务治理收口。
    * 包括：服务发现、健康检查，配置管理、事务、事件、重试、熔断、限流等。主要通过开发框架 SDK – 如：Spring Cloud，或服务网格Service Mesh等技术。
* 监控数据收口。
    * 包括：日志、指标、调用链等。主要通过一些标准主流的探针，再加上后台的数据清洗和数据存储来完成，最好是使用无侵入式的技术。监控的数据必须统一在一个地方进行关联，这样才会产生信息。
* 资源调度有应用部署的收口。
    * 包括：计算、网络和存储的收口，主要是通过容器化的方案，如k8s来完成。
* 中间件的收口。
    * 包括：数据库，消息，缓存，服务发现，网关等。这类的收口方式一般要在企业内部统一建立一个共享的云化的中间件资源池。

这里的原则是：

* 要选择容易进行业务逻辑和控制逻辑分离的技术。
    * 关注 AOP 式的Spring 开发框架
* 要选择可以享受“前人种树，后人乘凉”的有技术红利的技术。
    * 例如：有庞大社区而且相互兼容的技术，如：Java, Docker,  Ansible，HTTP，Telegraf/Collectd……
* 中间件要使用可以 **支持HA集群 和 多租户** 的技术。主流中间件一般都会支持 HA 集群方式的。

# 原则八：不要迁就老旧系统的技术债务

很多公司都很非常大的技术债务，这些债务具体表现如下：

* 使用老旧的技术。
    * 比如，使用HTTP1.0，基于 socket的通讯协议，过时的模型等
* 不合理的设计。
    * 比如，在 gateway 中写大量的业务逻辑，单体架构，数据和业务逻辑深度耦合，错误的系统架构等
* 缺少配套设施。
    * 比如，**没有自动化测试，没有好的软件文档，没有质量好的代码**，没有标准和规范等


更进一步：

* 与其花大力气迁就技术债务，不如直接还技术债。是所谓的长痛不如短痛。
* 建设没有技术债的“新城区”，并通过“防腐层 ”的架构模型，不要让技术债侵入“新城区”。

# 原则九：不要依赖自己的经验，要依赖于数据和学习

在做技术决定的时候，**开始凭自己以往的经验，那么你就已经不可能再成长了**。

* **人都是不可能通过不断重复过去而进步的**，人的进步从来都是通过学习自己不知道的东西。
* 千万不要依赖于自己的经验做决定。
    * 做任何决定之前，要做调研，查找技术博客，文章，论文等 。
        * 看看各个公司，或是各个开源软件他们是怎么做的？然后，比较多种方案的 Pros/Cons(优/缺点)，最终形成自己的决定，这样，才可能做出一个更好的决定。

# 原则十：千万要小心 X – Y 问题，要追问原始需求

对于 X-Y 问题，是指用户为了解决 X问题，他觉得用 Y 可以解。于是问我 Y 怎么搞，结果搞到最后，发现原来要解决的 X 问题，这个时候最好的解决方案不是 Y，而是 Z。

追问原始需求，更能明白用户/客户的需要，才能给出自己判断得出的最好的方案，不能直接依赖用户给的选项做考虑。

# 原则十一：激进胜于保守，创新与实用并不冲突

积极拥抱会改变未来的新技术，如：Docker/Go。

进步永远来自于探索，探索是要付出代价的，但是收益更大。