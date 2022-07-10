# 微服务 - 分布式搜索

> 本节主要介绍微服务架构中分布式搜索的实例。

[[toc]]

# 初识elasticsearch

## elasticsearch的作用

elasticsearch(ES)是一款非常强大的开源搜索引擎，具备非常多强大功能，可以帮助我们从海量数据中快速找到需要的内容

例如：

- 在GitHub搜索代码

  ![github搜索](/_images/micro-services/frame/分布式搜索/github搜索.png)

- 在电商网站搜索商品

  ![电商搜索](/_images/micro-services/frame/分布式搜索/电商搜索.png)

- 在百度搜索答案

  ![百度搜索](/_images/micro-services/frame/分布式搜索/百度搜索.png)

## ELK技术栈

elasticsearch结合kibana、Logstash、Beats，也就是elastic stack（ELK）。被广泛应用在日志数据分析、实时监控等领域。
而elasticsearch是elastic stack的核心，负责存储、搜索、分析数据。

* Kibana
	* 数据可视化
* elasticsearch
	* 存储、搜索、分析数据
* Logstash、Beats
	* 数据抓取

![ELK技术栈](/_images/micro-services/frame/分布式搜索/ELK技术栈.png)


# elasticsearch的发展

## elasticsearch和lucene

elasticsearch底层是基于**lucene**来实现的。

**Lucene**是一个Java语言的搜索引擎类库，是Apache公司的顶级项目，由DougCutting于1999年研发。官网地址：https://lucene.apache.org/ 。

![Lucene](/_images/micro-services/frame/分布式搜索/Lucene.png)


**elasticsearch**的发展历史：

- 2004年Shay Banon基于Lucene开发了Compass
- 2010年Shay Banon 重写了Compass，取名为Elasticsearch。

![elasticsearch](/_images/micro-services/frame/分布式搜索/elasticsearch.png)

## 为什么不是其他搜索技术？

目前比较知名的搜索引擎技术排名：

![searchRank](/_images/micro-services/frame/分布式搜索/searchRank.png)

虽然在早期，Apache Solr是最主要的搜索引擎技术，但随着发展elasticsearch已经渐渐超越了Solr，独占鳌头：


## 总结

什么是elasticsearch？

- 一个开源的分布式搜索引擎，可以用来实现搜索、日志统计、分析、系统监控等功能

什么是elastic stack（ELK）？

- 是以elasticsearch为核心的技术栈，包括beats、Logstash、kibana、elasticsearch

什么是Lucene？

- 是Apache的开源搜索引擎类库，提供了搜索引擎的核心API

# 索引

## 正向索引

倒排索引的概念是基于MySQL这样的正向索引而言的。
那么什么是正向索引呢？例如给下表（tb_goods）中的id创建索引：

![正向索引](/_images/micro-services/frame/分布式搜索/正向索引.png)

如果是根据id查询，那么直接走索引，查询速度非常快。但如果是基于title做模糊查询，只能是逐行扫描数据，流程如下：

1. 用户搜索数据，条件是title符合`"%手机%"`
2. 逐行获取数据，比如id为1的数据
3. 判断数据中的title是否符合用户搜索条件
4. 如果符合则放入结果集，不符合则丢弃。回到步骤1

逐行扫描，也就是全表扫描，随着数据量增加，其查询效率也会越来越低。当数据量达到数百万时，就是一场灾难。

## 倒排索引

倒排索引中有两个非常重要的概念：

- 文档（`Document`）：用来搜索的数据，其中的每一条数据就是一个文档。例如一个网页、一个商品信息
- 词条（`Term`）：对文档数据或用户搜索数据，**利用某种算法分词**，得到的具备含义的词语就是词条。例如：我是中国人，就可以分为：我、是、中国人、中国、国人这样的几个词条

**创建倒排索引**是对正向索引的一种特殊处理，流程如下：

1. 将每一个文档的数据利用算法分词，得到一个个词条
2. 创建表，每行数据包括词条、词条所在文档id、位置等信息
3. 因为词条唯一性，可以给词条创建索引，例如hash表结构索引

如图：

![倒排索引](/_images/micro-services/frame/分布式搜索/倒排索引.png)

倒排索引的**搜索流程**如下（以搜索"华为手机"为例）：

1. 用户输入条件`"华为手机"`进行搜索。
2. 对用户输入内容**分词**，得到词条：`华为`、`手机`。
3. 拿着词条在倒排索引中查找，可以得到包含词条的文档id：1、2、3。
4. 拿着文档id到正向索引中查找具体文档。

如图：

![倒排索引的搜索过程](/_images/micro-services/frame/分布式搜索/倒排索引的搜索过程.png)

虽然要先查询倒排索引，再查询正向索引，但是无论是词条、还是文档id都建立了索引，查询速度非常快！无需全表扫描。

## 正向和倒排

那么为什么一个叫做正向索引，一个叫做倒排索引呢？

- **正向索引**是最传统的，根据id索引的方式。但根据词条查询时，必须先逐条获取每个文档，然后判断文档中是否包含所需要的词条，是**根据文档找词条的过程**。

- 而**倒排索引**则相反，是先找到用户要搜索的词条，根据词条得到保护词条的文档的id，然后根据id获取文档。是**根据词条找文档的过程**。

是不是恰好反过来了？那么两者方式的优缺点是什么呢？

**正向索引**：

- 优点：
  - 可以给多个字段创建索引
  - 根据索引字段搜索、排序速度非常快
- 缺点：
  - 根据非索引字段，或者索引字段中的部分词条查找时，只能全表扫描。

**倒排索引**：

- 优点：
  - 根据词条搜索、模糊搜索时，速度非常快
- 缺点：
  - 只能给词条创建索引，而不是字段
  - 无法根据字段做排序

#es的一些概念

elasticsearch中有很多独有的概念，与mysql中略有差别，但也有相似之处。

## 文档和字段

elasticsearch是面向**文档（Document）**存储的，可以是数据库中的一条商品数据，一个订单信息。文档数据会被序列化为json格式后存储在elasticsearch中：

![文档数据json格式化](/_images/micro-services/frame/分布式搜索/文档数据json格式化.png)

而Json文档中往往包含很多的**字段（Field）**，类似于数据库中的列。

## 索引和映射

**索引（Index）**，就是相同类型的文档的集合。

例如：

- 所有用户文档，就可以组织在一起，称为用户的索引；
- 所有商品的文档，可以组织在一起，称为商品的索引；
- 所有订单的文档，可以组织在一起，称为订单的索引；

![索引举例](/_images/micro-services/frame/分布式搜索/索引举例.png)

因此，我们可以把索引当做是数据库中的表。

数据库的表会有约束信息，用来定义表的结构、字段的名称、类型等信息。因此，索引库中就有**映射（mapping）**，是索引中文档的字段约束信息，类似表的结构约束。

## mysql与elasticsearch

我们统一的把mysql与elasticsearch的概念做一下对比：

| **MySQL** | **Elasticsearch** | 							           **说明**                                     |
| --------- | ----------------- | ----------------------------------------------------------------------------------|
| Table     | Index             | 索引(index)，就是文档的集合，类似数据库的表(table)                                |
| Row       | Document          | 文档（Document），就是一条条的数据，类似数据库中的行（Row），文档都是JSON格式     |
| Column    | Field             | 字段（Field），就是JSON文档中的字段，类似数据库中的列（Column）                   |
| Schema    | Mapping           | Mapping（映射）是索引中文档的约束，例如字段类型约束。类似数据库的表结构（Schema） |
| SQL       | DSL               | DSL是elasticsearch提供的JSON风格的请求语句，用来操作elasticsearch，实现CRUD       |

是不是说，我们学习了elasticsearch就不再需要mysql了呢？并不是如此，两者各自有自己的擅长支出：

- Mysql：擅长事务类型操作，可以确保数据的安全和一致性
- Elasticsearch：擅长海量数据的搜索、分析、计算

因此在企业中，往往是两者结合使用：

- 对安全性要求较高的写操作，使用mysql实现
- 对查询性能要求较高的搜索需求，使用elasticsearch实现
- 两者再基于某种方式，实现数据的同步，保证一致性

![mysql与elasticsearch同步](/_images/micro-services/frame/分布式搜索/mysql与elasticsearch同步.png)