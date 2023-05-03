# ElasticSearch数据 - 存储

> 主要介绍elasticsearch的数据存储功能，包括索引库操作和文档操作。

[[toc]]

# 参考资料

* [安装elasticsearch](./安装elasticsearch.md)
* [elasticsearch官网](https://www.elastic.co/guide/index.html)

# 安装elasticsearch

主要步骤:

1. docker load -i  加载 es 和 kibana的镜像；
2. docker run + 配置参数，依次启动es和kibana；
3. 在kibana提供的DevTools界面，编写DSL来操作elasticsearch；
4. 安装ik分词器、配置扩展词词典、以及再次测试验证。

## 分词器

分词器的作用：
	- 创建倒排索引时对文档分词
	- 用户搜索时，对输入的内容分词

处理中文分词，一般会使用IK分词器。https://github.com/medcl/elasticsearch-analysis-ik

ik分词器包含两种模式：
 - ik_smart：最少切分，粗粒度
 - ik_max_word：最细切分，细粒度

示例：输入“小黑子”

* ik_smart拆分结果："小"，"黑子"
* ik_max_word拆分结果："小黑"、"黑子"

而且会有打分机制，根据分词的匹配程度score字段。

**ik分词器-拓展词库**

![ik分词器-拓展词库](/_images/database/es/elasticsearch/ik分词器-拓展词库.png)

**ik分词器-停用词库**

![ik分词器-停用词库](/_images/database/es/elasticsearch/ik分词器-停用词库.png)

#  索引库操作

索引库就类似数据库表，mapping映射就类似表的结构。我们要向es中存储数据，必须先创建“库”和“表”。

## mapping映射属性

mapping是对索引库中文档的约束，常见的mapping属性包括：

- type：字段数据类型，常见的简单类型有：
  - 字符串：text（可分词的文本）、keyword（精确值，例如：品牌、国家、ip地址）
  - 数值：long、integer、short、byte、double、float、
  - 布尔：boolean
  - 日期：date
  - 对象：object
- index：是否创建索引，默认为true
- analyzer：使用哪种分词器
- properties：该字段的子字段

例如下面的json文档：

```json
{
    "age": 21,
    "weight": 52.1,
    "isMarried": false,
    "info": "黑马程序员Java讲师",
    "email": "zy@itcast.cn",
    "score": [99.1, 99.5, 98.9],
    "name": {
        "firstName": "云",
        "lastName": "赵"
    }
}
```

对应的每个字段映射（mapping）：

- age：类型为 integer；参与搜索，因此需要index为true；无需分词器
- weight：类型为float；参与搜索，因此需要index为true；无需分词器
- isMarried：类型为boolean；参与搜索，因此需要index为true；无需分词器
- info：类型为字符串，需要分词，因此是text；参与搜索，因此需要index为true；分词器可以用ik_smart
- email：类型为字符串，但是不需要分词，因此是keyword；不参与搜索，因此需要index为false；无需分词器
- score：虽然是数组，但是我们只看元素的类型，类型为float；参与搜索，因此需要index为true；无需分词器
- name：类型为object，需要定义多个子属性
  - name.firstName；类型为字符串，但是不需要分词，因此是keyword；参与搜索，因此需要index为true；无需分词器
  - name.lastName；类型为字符串，但是不需要分词，因此是keyword；参与搜索，因此需要index为true；无需分词器

注意: **mapping约束中，keyword:表明不需要分词;index为false为不参加搜索，能够加快搜索速度。**

## 索引库操作

- 创建索引库：PUT /索引库名
- 查询索引库：GET /索引库名
- 删除索引库：DELETE /索引库名
- 添加字段：PUT /索引库名/_mapping

```json
#创建索引库
PUT /student
{
  "mappings": {
    "properties": {
      "name":{
        "type": "keyword"
      },
      "age":{
        "type": "integer"
      },
      "school":{
        "type": "text", 
        "analyzer": "ik_smart"
      }
    }
  }
}

#查看索引库
GET /student

#删除索引库
DELETE /student

#更新索引库
PUT /student/_mapping
{
  "properties":{
    "id":{
      "type":"integer"
    }
  }
}
```

# 文档操作

文档操作包括以下几种:

- 创建文档：POST /{索引库名}/_doc/文档id   { json文档 }
- 查询文档：GET /{索引库名}/_doc/文档id
- 删除文档：DELETE /{索引库名}/_doc/文档id
- 修改文档：
  - 全量修改：PUT /{索引库名}/_doc/文档id { json文档 }
  - 增量修改：POST /{索引库名}/_update/文档id { "doc": {字段}}
```json
#新增文档
POST /student/_doc/1
{
  "age": "25",
  "id": "1001",
  "name": "Jason",
  "school": "南京理工大学"
}

POST /student/_doc/2
{
  "age": "24",
  "id": "0005",
  "name": "Hellen",
  "school": "东南大学"
}

POST /student/_doc/3
{
  "age": "27",
  "id": "1011",
  "name": "Steven",
  "school": "南京大学"
}

#查询文档
GET /student/_doc/1

GET /student/_doc/2

GET /student/_doc/3

#修改文档
#增量修改
POST /student/_update/1
{
  "doc":{
  "id": "1003"
  }
}

#全量修改
PUT /student/_doc/1
{
  "age": "25",
  "id": "1007",
  "name": "Bob",
  "school": "南京理工大学"
}

#删除文档
DELETE /student/_doc/3
```

## 文档操作-动态映射

当我们向ES中插入文档时，如果文档中字段没有对应的mapping，ES会帮助我们字段设置mapping，规则如下：

![文档操作-动态映射](/_images/database/es/elasticsearch/文档操作-动态映射.png)

```
#动态映射
PUT /student/_doc/1
{
  "age": "25",
  "id": "1007",
  "name": "Bob",
  "school": "南京理工大学",
  "city":"南京",
  "sex": "male"
}

#查看索引库,会发现默认帮我们新增了city和sex的mapping约束
GET /student
"student" : {
    "aliases" : { },
    "mappings" : {
      "properties" : {
        "age" : {
          "type" : "integer"
        },
        "city" : {
          "type" : "text",
          "fields" : {
            "keyword" : {
              "type" : "keyword",
              "ignore_above" : 256
            }
          }
        },
        "id" : {
          "type" : "integer"
        },
        "name" : {
          "type" : "keyword"
        },
        "school" : {
          "type" : "text",
          "analyzer" : "ik_smart"
        },
        "sex" : {
          "type" : "text",
          "fields" : {
            "keyword" : {
              "type" : "keyword",
              "ignore_above" : 256
            }
          }
        }
      }
    }
```


# RestClient操作索引库学习

ES官方提供了各种不同语言的客户端，用来操作ES。这些客户端的本质就是组装DSL语句，通过http请求发送给ES。官方文档地址：https://www.elastic.co/guide/en/elasticsearch/client/index.html

其中的Java Rest Client又包括两种：

- Java Low Level Rest Client
- Java High Level Rest Client

![RestClient](/_images/database/es/elasticsearch/RestClient.png)


## 数据库导入

以hotel.sql的数据为例：

数据结构如下：

```sql
CREATE TABLE `tb_hotel` (
  `id` bigint(20) NOT NULL COMMENT '酒店id',
  `name` varchar(255) NOT NULL COMMENT '酒店名称；例：7天酒店',
  `address` varchar(255) NOT NULL COMMENT '酒店地址；例：航头路',
  `price` int(10) NOT NULL COMMENT '酒店价格；例：329',
  `score` int(2) NOT NULL COMMENT '酒店评分；例：45，就是4.5分',
  `brand` varchar(32) NOT NULL COMMENT '酒店品牌；例：如家',
  `city` varchar(32) NOT NULL COMMENT '所在城市；例：上海',
  `star_name` varchar(16) DEFAULT NULL COMMENT '酒店星级，从低到高分别是：1星到5星，1钻到5钻',
  `business` varchar(255) DEFAULT NULL COMMENT '商圈；例：虹桥',
  `latitude` varchar(32) NOT NULL COMMENT '纬度；例：31.2497',
  `longitude` varchar(32) NOT NULL COMMENT '经度；例：120.3925',
  `pic` varchar(255) DEFAULT NULL COMMENT '酒店图片；例:/img/1.jpg',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

## mapping映射分析

创建索引库，最关键的是mapping映射，而mapping映射要考虑的信息包括：

- 字段名
- 字段数据类型
- 是否参与搜索
- 是否需要分词
- 如果分词，分词器是什么？

其中：

- 字段名、字段数据类型，可以参考数据表结构的名称和类型
- 是否参与搜索要分析业务来判断，例如图片地址，就无需参与搜索
- 是否分词呢要看内容，内容如果是一个整体就无需分词，反之则要分词
- 分词器，我们可以统一使用ik_max_word



来看下酒店数据的索引库结构:

```json
PUT /hotel
{
  "mappings": {
    "properties": {
      "id": {
        "type": "keyword"
      },
      "name":{
        "type": "text",
        "analyzer": "ik_max_word",
        "copy_to": "all"
      },
      "address":{
        "type": "keyword",
        "index": false
      },
      "price":{
        "type": "integer"
      },
      "score":{
        "type": "integer"
      },
      "brand":{
        "type": "keyword",
        "copy_to": "all"
      },
      "city":{
        "type": "keyword",
        "copy_to": "all"
      },
      "starName":{
        "type": "keyword"
      },
      "business":{
        "type": "keyword"
      },
      "location":{
        "type": "geo_point"
      },
      "pic":{
        "type": "keyword",
        "index": false
      },
      "all":{
        "type": "text",
        "analyzer": "ik_max_word"
      }
    }
  }
}
```



几个特殊字段说明：

- location：地理坐标，里面包含精度、纬度
- all：一个组合字段，其目的是将多字段的值 利用copy_to合并，提供给用户搜索
