# ElasticSearch应用 - 使用

## ES的几种调用方式

### restful api调用(http请求）

GET请求：http://localhost:9200/

curl可以模拟发送请求：curl -X GET "localhost:9200/?pretty"

ES的启动端口

1. 9200：给外部用户（客户端）调用的端口
2. 9300：给ES集群内部通信的（外部无法使用）

### kibana devtools

自由地对ES进行操作（本质也是restful api)，不建议生产环境使用

### 客户端调用

支持 Java, JavaScript, Ruby, Go, .NET, PHP, Python等多种客户端的调用。

* [Elasticsearch Clients](https://www.elastic.co/guide/en/elasticsearch/client/index.html)

## 使用方法

基础的增删改查，已有

### EQL查询

事件查询语言（EQL）是一种用于基于事件的时间序列数据（如日志、度量和跟踪）的查询语言。

* [EQL查询](https://www.elastic.co/guide/en/elasticsearch/reference/7.17/eql.html)

EQL的优势

* EQL可以让你表达事件之间的关系。
* EQL的学习曲线很低。
* EQL是为安全用例而设计的。

```
GET /my-data-stream/_eql/search
{
  "query": """
    process where process.name == "regsvr32.exe"
  """
}
```

返回

EQL查询结果：

<<< @/md/database/es/src/eql.json

### SQL查询

学习成本低，与原来的数据库查询语言一致。

* [EQL查询](https://www.elastic.co/guide/en/elasticsearch/reference/7.17/sql-getting-started.html)

```
POST /_sql?format=txt
{
  "query": "SELECT * FROM library WHERE release_date < '2000-01-01'"
}
```

结果

```
    author     |     name      |  page_count   | release_date
---------------+---------------+---------------+------------------------
Dan Simmons    |Hyperion       |482            |1989-05-26T00:00:00.000Z
Frank Herbert  |Dune           |604            |1965-06-01T00:00:00.000Z
```

### Painless Scripting language

编程式取值，更灵活，但是学习成本高

### Mapping

可以理解为数据库的表结构，有哪些字段、字段类型。(没有指定字段类型，自动生成；也可以手动指定字段类型)

ES支持动态mapping, 表结构可以动态改变，而不像MySQL一样必须手动建表，没有的字段就不能插入。

* [Mapping](https://www.elastic.co/guide/en/elasticsearch/reference/7.17/sql-getting-started.html)

显示创建mapping:

```
GET user/_mapping

PUT /user
{
  "mappings": {
    "properties": {
      "age":    { "type": "integer" },  
      "email":  { "type": "keyword"  }, 
      "name":   { "type": "text"  }     
    }
  }
}
```

## 分词器

指定了分词的规则。

* [分词器](https://www.elastic.co/guide/en/elasticsearch/reference/7.17/analysis-analyzers.html)

* Standard Analyzer 标准分词器
    * 根据Unicode文本分割算法的定义，将文本划分为单词边界上的术语。它删除了大多数标点符号，降低了术语的小写，并支持删除停止词。

* Simple Analyzer 简单分词器
    * 每当遇到不是字母的字符时，简单分析器就会将文本划分为多个术语。它将文本全部转换成小写。

* Whitespace Analyzer 空格分词器
    * 每当遇到任何空白字符时，空白分析器都会将文本划分为多个术语。它没有小写的转换。

* Stop Analyzer 停止分词器
    * 与简单分析器类似，但也支持删除停止词。

* Keyword Analyzer 关键字分词器
    * 是一个“noop”分析器，它接受给定的任何文本，并输出与单个术语完全相同的文本。

* Pattern Analyzer 模式分词器
    * 使用正则表达式将文本拆分为术语。它支持小写和停止字。

* Language Analyzers 语言分词器
    * Elasticsearch提供了许多特定于语言的分析器，如英语或法语或中文（ik,pinyin）。

* Fingerprint Analyzer 指纹分词器
    * 是一种专业的分析仪，可以创建可用于重复检测的指纹。

### DSL

* [bool查询](https://www.elastic.co/guide/en/elasticsearch/reference/7.17/query-dsl-bool-query.html)
* [查询过滤](https://www.elastic.co/guide/en/elasticsearch/reference/7.17/query-filter-context.html)

**写DSL查询语句时，先测试原生DSL，再翻译成客户端语言**

DSL搜索条件：

<<< @/md/database/es/src/dsl.json

java代码：

<<< @/md/database/es/src/dsl.java

动静分离设计：先模糊筛选静态数据，查出数据后，再根据查到的内容id去数据库查找到**动态数据**。类似MySQL的聚簇索引，二次查找的原理
