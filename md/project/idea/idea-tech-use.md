# Idea - 常用技术

[[toc]]

# 技术组件

## 中间件

### 数据库中间件

* canal —— MySQL中间件
    * 阿里巴巴MySQL binlog **增量订阅&消费组件**，主要用途是基于MySQL数据库增量日志解析，提供增量数据订阅和消费。

* MyCat —— 分库分表中间件，前身是Cobar
    * MyCat数据库**分库分表中间件**，开发者可以像使用MySQL一样来使用MyCat，而无需关注底层用了几台数据库。

* Redis —— 缓存中间件
    * 键值对存储系统，可用作数据库、缓存、消息中间件

* Codis —— 分布式缓存中间件
    * 基于代理的高性能Redis集群方案，使用Go语言进行开发。

* Cobar —— 分布式服务中间件, MySQL高可用中间件
    * Cobar是分片数据库和表的代理,兼容MySQL protocal和MySQLSQL grama, 底层存储只支持MySQL,支持前台业务更简单,稳定,高效和安全。