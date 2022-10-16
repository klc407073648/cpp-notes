# MySQL实战 - MyCat使用

# MyCat概述

> MyCat是开源的、活跃的、基于Java语言编写的MySQL数据库中间件。可以像使用mysql一样来使用MyCat，对于开发人员来说根本感觉不到MyCat的存在。

开发人员只需要连接MyCat即可，而具体底层用到几台数据库，每一台数据库服务器里面存储了什么数据，都无需关心。 具体的分库分表的策略，只需要在MyCat中配置即可。

![](/_images/database/mysql/practice/MyCat.png)

优点：

* 性能可靠稳定
* 强大的技术团队
* 体系完善
* 社区活跃

## 下载及安装

下载地址：[http://dl.MyCat.org.cn/](http://dl.MyCat.org.cn/)

安装：

```
# 安装依赖的JDK
# 解压即可直接安装MyCat
tar -zxvf MyCat-server-1.6.7.3-release-20210913163959-linux.tar.gz -C /usr/local/
```

## 概念

在MyCat的整体结构中，分为两个部分：上面的逻辑结构、下面的物理结构。

![](/_images/database/mysql/practice/MyCat整体结构.png)

在MyCat的逻辑结构主要负责**逻辑库、逻辑表、分片规则、分片节点**等逻辑结构的处理，而具体的数据存储还是在物理结构，也就是数据库服务器中存储的。

# MyCat入门

## 配置文件

### schema.xml

schema.xml 作为MyCat中最重要的配置文件之一 , 涵盖了MyCat的逻辑库、逻辑表 、分片规则、分片节点及数据源的配置。

![](/_images/database/mysql/practice/schema配置文件.png)

重要的是三组标签：

* schema标签
* datanode标签
* datahost标签

### rule.xml

rule.xml中定义所有拆分表的规则, 在使用过程中可以灵活的使用分片算法, 或者对同一个分片算法使用不同的参数, 它让分片过程可配置化。主要包含两类标签：tableRule、Function

![](/_images/database/mysql/practice/rule配置文件.png)

### rule.xml

rule.xml中定义所有拆分表的规则, 在使用过程中可以灵活的使用分片算法, 或者对同一个分片算法使用不同的参数, 它让分片过程可配置化。主要包含两类标签：tableRule、Function

![](/_images/database/mysql/practice/rule配置文件.png)

### server.xml

server.xml配置文件包含了MyCat的系统配置信息，主要有两个重要的标签：system、user

![](/_images/database/mysql/practice/server配置文件.png)

备注：有些表应该声明为全局表，例如固定不变的省、市、区的名称

## 分片规则

* 范围分片
    * 根据指定的字段及其配置的范围与数据节点的对应情况，来决定该数据属于哪一个分片。
* 取模分片
    * 根据指定的字段值与节点数量进行求模运算，根据运算结果，来决定该数据属于哪一个分片。
* 一致性hash分片
    * 所谓一致性哈希，相同的哈希因子计算值总是被划分到相同的分区表中，不会因为分区节点的增加而改变原来数据的分区位置，有效的解决了分布式数据的拓容问题。
* 枚举分片
    * 通过在配置文件中配置可能的枚举值, 指定数据分布到不同数据节点上, 本规则适用于按照省份、性别、状态拆分数据等业务。
* 应用指定算法
    * 运行阶段由应用自主决定路由到那个分片, 直接根据字符子串（必须是数字）计算分片号。
* 固定分片hash算法
    * 该算法类似于十进制的求模运算，但是为二进制的操作，例如，取 id 的二进制低 10 位 与1111111111 进行位 & 运算，位与运算最小值为 0000000000，最大值为1111111111，转换为十进制，也就是位于0-1023之间。
* 字符串hash解析算法
    * 截取字符串中的指定位置的子字符串, 进行hash算法，算出分片。
* 按天分片算法
    * 按照日期及对应的时间周期来分片。
* 自然月分片
    * 使用场景为按照月份来分片, 每个自然月为一个分片。

# MyCat管理及监控

## MyCat原理

![](/_images/database/mysql/practice/MyCat原理.png)

在MyCat中，当执行一条SQL语句时，MyCat需要进行**SQL解析、分片分析、路由分析、读写分离分析**等操作，最终经过一系列的分析决定将当前的SQL语句到底路由到那几个(或哪一个)节点数据库，数据库将数据执行完毕后，如果有返回的结果，则将结果返回给MyCat，最终还需要在MyCat中进行**结果合并、聚合处理、排序处理、分页处理**等操作，最终再将结果返回给客户端。

而在MyCat的使用过程中，MyCat官方也提供了一个管理监控平台MyCat-Web（MyCat-eye）。MyCat-web 是 MyCat 可视化运维的管理和监控平台，弥补了 MyCat 在监控上的空白。帮 MyCat 分担统计任务和配置管理任务。MyCat-web 引入了 ZooKeeper 作为配置中心，可以管理多个节点。

MyCat-web 主要管理和监控 MyCat 的流量、连接、活动线程和内存等，具备 IP 白名单、邮件告警等模块，还可以统计 SQL 并分析慢 SQL 和高频 SQL 等。为优化 SQL 提供依据。

## MyCat管理

Mycat默认开通2个端口，可以在server.xml中进行修改。

* 8066 数据访问端口，即进行 DML 和 DDL 操作。
* 9066 数据库管理端口，即 mycat 服务管理控制功能，用于管理mycat的整个集群状态。

## 安装及使用

Mycat-eye运行过程中需要依赖zookeeper，需要首先安装Zookeeper，再去安装Mycat-web，且两者都是通过tar.gz源码方式安装。

![](/_images/database/mysql/practice/Mycat-eye使用界面.png)
