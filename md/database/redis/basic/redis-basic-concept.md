# Redis基础 - 简介

> Redis (REmote DIctionary Server) 是用 C 语言开发的一个开源的<font color='red'>**高性能键值对（ key-value）数据库**</font>。它是一种NoSQL（Not-Only SQL，泛指非关系型的数据库），作为关系型数据库的补充。常用的NoSQL数据库：Redis,memcache,HBase,MongoDB。

[[toc]]

# 概述

## 基本概念

**数据存储格式**

redis 自身是一个 Map，其中所有的数据都是采用 key : value 的形式存储。数据类型指的是存储的数据的类型，也就是 value 部分的类型， **key 部分永远都是字符串**。

**应用场景**

基于海量用户和海量数据前提下的数据处理问题。一般热点信息（高频，波段性）可以使用redis来存储。（利用内存存储来减少磁盘IO次数；不存储关系，仅存储数据）

**特征**

1. 数据间没有必然的关联关系
2. 内部采用单线程机制进行工作。（最新版本支持多线程）
3. 高性能。官方提供测试数据， 50个并发执行100000 个请求,读的速度是110000 次/s,写的速度是81000次/s。
4. 多数据类型支持
5. 支持数据持久化，可以进行数据灾难恢复
6. 支持主从集群、分片集群
7. 支持多语言客户端

**数据类型**

Redis是一个key-value的数据库，key一般是String类型，不过value的类型多种多样：

![](/_images/database/redis/basic/redis数据结构.png)

## SQL和NoSQL

|    | SQL |  NoSQL | 
| -------- | ----------- | ----------- | 
| 数据结构 | 结构化(Structured) | 非结构化 | 
| 数据关联 | 关联的(Relational) | 无关联的 | 
| 查询方式 | SQL查询 | 非SQL | 
| 事务特性 | ACID | BASE| 
