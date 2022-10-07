# 如何写一个自己的项目

[[toc]]

> 做着玩和真正上线有很大的区别

# 项目流程

需求流程图:

![需求流程图](/_images/method/tech/需求流程图.png)

大致步骤如下：

**需求分析** => **设计（概要设计、详细设计）**=> **技术选型** => 初始化 / 引入需要的技术 => 写 Demo => 写代码（实现业务逻辑） => 测试（单元测试、系统测试）=> 代码提交 / 代码评审 => 部署 => 发布上线

研发流程图：

![研发流程图](/_images/method/tech/研发流程图.png)

# 个人需求分析

## 项目创作原因

1. 挖掘需求：自己遇到的问题，看别人的项目并且找出别人项目的缺点 

验证需求是否有价值：能解决别人的问题，**能否解决通用的问题**（对内 - 对自己、对外 - 对其他用户）

### 项目价值

1. 对别人的价值
2. 兴趣
3. 引流
4. 做项目出视频、分享
5. **巩固所学知识**

### 与其他同类型项目对比

例如，做博客系统

竞品：

- A ：vuepress
- B : Docisify等工具
- C : CSDN,博客园等平台

A + B + C 进行融合，取长补短、精简化

**为什么市面上轮子多？**

1. 每个产品都有优点、优缺点，面向的需求不一样
2. 不同的公司有各自擅长的领域，语言体系，为了内部能统一使用，会开源一些项目供内外部使用

## 需求篇

1. 千万不要一上来就大而全，要先把核心功能 **快速上线和验证**，得到用户反馈
2. 再进行下一步操作。
3. **不要闷头开发，需要得到反馈，至少是让同事或朋友体验使用中的不足。**
4. **敏捷开发，小步快跑，慢慢加功能。**

重点：**分析项目核心功能**

扩展：**后期扩展功能考虑**

## 技术选型

### 问题

需要回答以下几个问题：

1. 什么是技术选型?

   * 需要确定用哪些技术来完成项目的开发和维护。

2. 技术选型选什么?

   * 用哪类技术?比如编程语言，开发框架、数据库
   * 具体用什么技术?比如编程语言用 C++还是 Java?开发框架用 Spring 还是Vert.x?
   * 技术用哪个版本?比如 Vue 2 还是 Vue 3? Java 8 还是 Java 11?

3. 为什么要做技术选型?

   * 为了更好地开发和维护项目(提高效率,节约成本,提升体验)。

4. 怎么做好技术选型?

**先有的选：**

* 分析一下完成这个需求要用到哪些类别的技术?
   * 例如做一个网盘系统，需要选择开发语言，前端/后端开发框架、文件存储系统等。
   * 从百度、Google、GitHub、掘金等各个平台搜索各类技术，比如搜索:主流的文件存储系统。然后把搜到的所有技术以清单的形式记录在一个文档里。建议大家先尽可能多地搜索同类技术，不要只盯着某个技术不放。
* 有了可选项之后，可以从 **主观和客观** 两个视角去分析技术。

主观分析：
   * 通过官方文档了解技术作用、优缺点、适用场景等
   * 业务适用性。数据库的选择，消息队列的设计
   * 现有条件：团队技术栈，公司所能提供的资源，提高云主机的CPU核数和硬盘容量

客观分析：
   * 选择知名度高、有大厂背书、持续维护、活跃度高的、开源的、生态好的技术
      * 例如，业内普遍使用的Spring Cloud微服务框架、Vue和React前端框架等

### 后续分析

需要综合考虑成本、项目量级、所使用技术的生态等。

- 项目的量级（用户数、使用频率）

- 成本

  - 价格 （所需云主机的数量）
  - **人力成本** ：围绕着人来，团队对技术的熟悉程度；团队内要有一个问题解决者、领导者

- **生态**

  * 如何判断：去网上搜 github 的 star 数**（开源）**、业内的认可、文章
    - Spring /Spring boot
    - Vue、React
    - gRpc

  * 看作者（看公司）：google，apple，tencent

  * 稳定性

- **目的**：学习


如果是独立开发，考虑自己的技术栈即可。如果是团队协作，需要考虑大家都会的技术栈。


### 常用的技术框架

**前端**：三件套 + React + 组件库 Ant Design + Umi + Ant Design Pro（现成的管理系统）

| 技术       | 说明                  | 官网                           |
| ---------- | --------------------- | ------------------------------ |
| Vue        | 前端框架              | https://vuejs.org/             |
| Vue-router | 路由框架              | https://router.vuejs.org/      |
| Vuex       | 全局状态管理框架      | https://vuex.vuejs.org/        |
| Element    | 前端UI框架            | https://element.eleme.io/      |
| Axios      | 前端HTTP框架          | https://github.com/axios/axios |
| v-charts   | 基于Echarts的图表框架 | https://v-charts.js.org/       |

**后端**：

- java
   - spring（依赖注入框架，帮助你管理 Java 对象，集成一些其他的内容）
   - springmvc（web 框架，提供接口访问、restful接口等能力）
   - mybatis（Java 操作数据库的框架，持久层框架，对 jdbc 的封装）
   - mybatis-plus（对 mybatis 的增强，不用写 sql 也能实现增删改查）
   - springboot（**快速启动** / 快速集成项目。不用自己管理 spring 配置，不用自己整合各种框架）
   - junit 单元测试库
- c++
   - poco: 是一个开源的C++类库的集合,它主要提供简单的、快速的网络和可移植应用程序的C++开发
   - Boost：大量通用C++库的集合。
   - libev：功能齐全，高性能的时间循环，轻微地仿效libevent，但是不再像libevent一样有局限性，也修复了它的一些bug。
   - protobuf：协议缓冲，谷歌的数据交换格式。
- mysql 数据库

**部署**：服务器 / 容器（平台）

| 技术                   | 说明                 | 官网                                                 |
| ---------------------- | -------------------- | ---------------------------------------------------- |
| Spring Cloud           | 微服务框架           | https://spring.io/projects/spring-cloud              |
| Spring Cloud Alibaba   | 微服务框架           | https://github.com/alibaba/spring-cloud-alibaba      |
| Spring Boot            | 容器+MVC框架         | https://spring.io/projects/spring-boot               |
| Spring Security Oauth2 | 认证和授权框架       | https://spring.io/projects/spring-security-oauth     |
| MyBatis                | ORM框架              | http://www.mybatis.org/mybatis-3/zh/index.html       |
| MyBatisGenerator       | 数据层代码生成       | http://www.mybatis.org/generator/index.html          |
| PageHelper             | MyBatis物理分页插件  | http://git.oschina.net/free/Mybatis_PageHelper       |
| Knife4j                | 文档生产工具         | https://github.com/xiaoymin/swagger-bootstrap-ui     |
| Elasticsearch          | 搜索引擎             | https://github.com/elastic/elasticsearch             |
| RabbitMq               | 消息队列             | https://www.rabbitmq.com/                            |
| Redis                  | 分布式缓存           | https://redis.io/                                    |
| MongoDb                | NoSql数据库          | https://www.mongodb.com/                             |
| Docker                 | 应用容器引擎         | https://www.docker.com/                              |
| Druid                  | 数据库连接池         | https://github.com/alibaba/druid                     |
| OSS                    | 对象存储             | https://github.com/aliyun/aliyun-oss-java-sdk        |
| MinIO                  | 对象存储             | https://github.com/minio/minio                       |
| JWT                    | JWT登录支持          | https://github.com/jwtk/jjwt                         |
| LogStash               | 日志收集             | https://github.com/logstash/logstash-logback-encoder |
| Lombok                 | 简化对象封装工具     | https://github.com/rzwitserloot/lombok               |
| Seata                  | 全局事务管理框架     | https://github.com/seata/seata                       |
| Portainer              | 可视化Docker容器管理 | https://github.com/portainer/portainer               |
| Jenkins                | 自动化部署工具       | https://github.com/jenkinsci/jenkins                 |
| Kubernetes             | 应用容器管理平台     | https://kubernetes.io/                               |


## 设计篇

* 数据库设计
   * 设计用户表，订单表，商品表
* 提高性能
   * 消息队列 RabbitMq
   * 分布式缓存 Redis
* 提高搜索效率
   * Elasticsearch
* 考虑数据同步

### ES 和 MySQL 怎么同步（保证一致性）？

强一致性：

1. 事务双写：插入数据时两个库里都必须插入成功，才算成功，有任何一个失败就回滚（写入性能低）

稍强一致性：

1. 监听 binlog：mySQL 在插入数据成功后，会写入 binlog 日志，我们只开一个程序（线程）需要监听 binlog 的变化，如果发现有插入，就也插入到 es（canal 技术）

弱一致性：

1. 定时同步：每分钟读取 MySQL 中近 5 分钟内新增的数据，然后写入 ES（根据 id 判断已写入）

定时检测和补偿程序：每天 / 每小时去对比两个库，如果发现不一致，自动以数据库为主，或者发送告警，人工处理。

## 团队开发篇


1. 招募志同道合的伙伴一同开发

2. 要有一个协作文档 / 平台

   * 通过excel定制和分配任务
   * github平台，提交各自任务的代码

2. 日常沟通：了解各自工作情况、代码编写信息

3. 团队管理：

   1. 需要有负责人，统筹开发周期，测试验证，产品上线等工作
   2. 日常代码提交需要 CodeReview
   3. 构建Jenkins等自动化工具辅助开发

## 技术源码篇

1. 前端

2. 后端

3. 其他服务

## 项目上线篇

1. 建议选择 Docker/K8s 方式部署，弹性伸缩很方便。

2. 测试验证

3. 开源前：写好 README.md 项目介绍文档，参考知名项目的文档仿写，可以复制别人的 README 改写

   > 小图标网站：https://shields.io/

## 运营篇

1. 产品的持续维护，功能迭代更新

2. 收集用户反馈

3. 给网站添加统计分析功能（比如百度统计），查看用户访问数、**用户来源**

## 推广篇

* 推广给志同道合的同事、朋友或者自媒体上推广
