# elasticsearch与mysql之间的数据同步

> 主要介绍elasticsearch与mysql之间的数据同步。

[[toc]]

# 参考资料

* [MySQL Binlog 介绍](https://blog.csdn.net/wwwdc1012/article/details/88373440)

# 数据同步

elasticsearch中的酒店数据来自于mysql数据库，因此mysql数据发生改变时，elasticsearch也必须跟着改变，这个就是elasticsearch与mysql之间的**数据同步**。

在微服务中，负责酒店管理（操作mysql ）的业务与负责酒店搜索（操作elasticsearch ）的业务可能在两个不同的微服务上，数据同步该如何实现呢？

## 思路分析

常见的数据同步方案有三种：

- 同步调用
- 异步通知
- 监听binlog

MySQL中一般有以下几种日志：

| 日志类型              | 写入日志的信息                                               |
| --------------------- | ------------------------------------------------------------ |
| 错误日志              | 记录在启动，运行或停止mysqld时遇到的问题                     |
| 通用查询日志          | 记录建立的客户端连接和执行的语句                             |
| 二进制日志            | 记录更改数据的语句                                           |
| 中继日志              | 从复制主服务器接收的数据更改                                 |
| 慢查询日志            | 记录所有执行时间超过 long_query_time 秒的所有查询或不使用索引的查询 |
| DDL日志（元数据日志） | 元数据操作由DDL语句执行                                      |

### 3.1.1.同步调用

方案一：同步调用

![同步调用](/_images/database/es/ES与数据库数据同步/同步调用.png)

基本步骤如下：

- hotel-demo对外提供接口，用来修改elasticsearch中的数据
- 酒店管理服务在完成数据库操作后，直接调用hotel-demo提供的接口，

### 异步通知

方案二：异步通知

![异步通知](/_images/database/es/ES与数据库数据同步/异步通知.png)

流程如下：

- hotel-admin对mysql数据库数据完成增、删、改后，发送MQ消息
- hotel-demo监听MQ，接收到消息后完成elasticsearch数据修改

### 监听binlog

方案三：监听binlog

![监听binlog](/_images/database/es/ES与数据库数据同步/监听binlog.png)

流程如下：

- 给mysql开启binlog功能
- mysql完成增、删、改操作都会记录在binlog中
- hotel-demo基于canal监听binlog变化，实时更新elasticsearch中的内容

### 选择

方式一：同步调用

- 优点：实现简单，粗暴
- 缺点：业务耦合度高

方式二：异步通知

- 优点：低耦合，实现难度一般
- 缺点：依赖mq的可靠性

方式三：监听binlog

- 优点：完全解除服务间耦合
- 缺点：开启binlog增加数据库负担、实现复杂度高

## 实现数据同步

思路：利用课前资料提供的hotel-admin项目作为酒店管理的微服务。当酒店数据发生增、删、改时，要求对elasticsearch中数据也要完成相同操作。

步骤：

- 导入课前资料提供的hotel-admin项目，启动并测试酒店数据的CRUD

- 声明exchange、queue、RoutingKey

- 在hotel-admin中的增、删、改业务中完成消息发送

- 在hotel-demo中完成消息监听，并更新elasticsearch中数据

- 启动并测试数据同步功能
