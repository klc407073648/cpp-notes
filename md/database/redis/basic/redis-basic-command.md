# Redis基础 - 命令

[[toc]]

# 概述

Redis为了方便我们学习，将操作不同数据类型的命令也做了分组，在官网 [https://redis.io/commands](https://redis.io/commands) 可以查看到不同的命令：

![](/_images/database/redis/basic/redis命令集合.png)

# Redis通用命令

通用指令是部分数据类型的，都可以使用的指令，常见的有：

* KEYS：查看符合模板的所有key
* DEL：删除一个指定的key
* EXISTS：判断key是否存在
* EXPIRE：给一个key设置有效期，有效期到期时该key会被自动删除
* TTL：查看一个KEY的剩余有效期

通过help [command] 可以查看一个命令的具体用法，例如：

![](/_images/database/redis/basic/redis_keys.png)

# String类型

String类型，也就是字符串类型，是Redis中最简单的存储类型。

其value是字符串，不过根据字符串的格式不同，又可以分为3类：

* string：普通字符串
* int：整数类型，可以做自增、自减操作
* float：浮点类型，可以做自增、自减操作

不管是哪种格式，底层都是字节数组形式存储，只不过是编码方式不同。字符串类型的最大空间不能超过512m

![](/_images/database/redis/basic/String类型.png)

## 单数据操作

```
添加/修改数据
set key value
获取数据
get key
删除数据
del key
```

## 多数据操作

```
添加/修改多个数据
mset key1 value1 key2 value2 …
获取多个数据
mget key1 key2 …
获取数据字符个数（字符串长度）
strlen key
追加信息到原始信息后部（如果原始信息存在就追加，否则新建）
append key value

mset相对于set操作能够节省数据发送返回所用时间，但是需要考虑数据量，如果过大可能影响性能，阻塞其他命令执行。
```

## 扩展操作

**应用场景1：**
大型企业级应用中，分表操作是基本操作，使用多张表存储同类型数据，但是对应的<font color='red'>**主键 id 必须保证统一性，不能重复。**</font> Oracle 数据库具有 sequence 设定，可以解决该问题，但是 MySQL数据库并不具有类似的机制，该如何解决？

**解决方案：**
设置数值数据增加指定范围的值

```
incr key
incrby key increment
incrbyfloat key increment
设置数值数据减少指定范围的值
decr key
decrby key increment
```

**应用场景2：**
“中国好声音”启动海选投票，只能通过微信投票，每个微信号每 4 小时只能投1票。电商商家开启热门商品推荐，热门商品不能一直处于热门期，每种商品热门期维持3天， 3天后自动取消热门。

新闻网站会出现热点新闻，热点新闻最大的特征是时效性，如何自动控制热点新闻的时效性。

**解决方案：**
设置数据具有指定的生命周期

```
setex key seconds value
psetex key milliseconds value
```

**应用场景3：**
主页高频访问信息显示控制，例如新浪微博大V主页显示粉丝数与微博数量。

![](/_images/database/redis/basic/String应用微博.png)

```
在redis中为大V用户设定用户信息，以用户主键和属性值作为key，后台设定定时刷新策略即可
eg: user:id:3506728370:fans → 12210947
eg: user:id:3506728370:blogs → 6164
eg: user:id:3506728370:focuss → 83

在redis中以json格式存储大V用户信息，定时刷新（也可以使用hash类型）
eg: user:id:3506728370 →
{"id":3506728370,"name":"中国新闻网","fans":12210862,"blogs":6164, "focus":83}

key 的设置约定
数据库中的热点数据key命名惯例
     表名  ：主键名 ： 主键值：     字段名
eg1：order ：id     ： 29437595    ：name
eg2：equip ：id     ： 390472345   ：type
eg3：news  ：id     ： 202004150   ：title
```

## 总结

1. redis用于控制数据库表主键id，为数据库表主键提供生成策略，保障数据库表的主键唯一性，此方案适用于所有数据库，且支持数据库集群。
2. redis 控制数据的生命周期，通过数据是否失效控制业务行为，适用于所有具有时效性限定控制的操作
3. redis应用于各种结构型和非结构型高热度数据访问加速

# Hash类型

针对于String类型，对象数据如果需要频繁更新就会显得笨重，例如

user:id:3506728370 →
{"id":3506728370,"name":"春晚","fans":12210862,"blogs":6164, "focus":83}

由此引入新的数据类型hash类型：

1. 新的存储需求：对一系列存储的数据进行编组，方便管理，典型应用存储对象信息
2. 需要的存储结构：一个存储空间保存多个键值对数据。

例如，购买用户的信息String类型和Hash类型的存储对比：

![](/_images/database/redis/basic/Hash类型.png)

## 单数据操作

```
添加/修改数据
hset key field value

获取数据
hget key field
hgetall key

删除数据
hdel key field1 [field2]

```

## 多数据操作

```
添加/修改多个数据
hmset key field1 value1 field2 value2 …
获取多个数据
hmget key field1 field2 …
获取哈希表中字段的数量
hlen key
获取哈希表中是否存在指定的字段
hexists key field
```

## 扩展操作

```
获取哈希表中所有的字段名或字段值
hkeys key
hvals key
置指定字段的数值数据增加指定范围的值
hincrby key field increment
hincrbyfloat key field increment

用于为哈希表中不存在的的字段赋值
hsetnx key field value
```

**应用场景4：**
电商平台的购物车设计与实现

![](/_images/database/redis/basic/Hash应用购物车.png)

**解决方案：**

```
以客户id作为key，每位客户创建一个hash存储结构存储对应的购物车信息
将商品编号作为field，购买数量作为value进行存储
添加商品：追加全新的field与value
浏览：遍历hash
更改数量：自增/自减，设置value值
删除商品：删除field
清空：删除key
```

**应用场景5：**
双11活动日，各类商家优惠券，例如100元，200元，300元。

![](/_images/database/redis/basic/Hash应用优惠券.png)

**解决方案*:**

```
以商家id作为key
将参与抢购的商品id作为field
将参与抢购的商品数量作为对应的value
抢购时使用降值的方式控制产品数量
```

## 总结

1. redis 应用于购物车数据存储设计
2. redis 应用于抢购，限购类、限量发放优惠卷、激活码等业务的数据存储设计

# List 类型

Redis中的List类型可以看做是一个双向链表结构。既可以支持正向检索和也可以支持反向检索。

特点：

1. 数据存储需求：存储多个数据，并对数据进入存储空间的顺序进行区分
2. 需要的存储结构：一个存储空间保存多个数据，且通过数据可以体现进入顺序
3. list类型：保存多个数据，底层使用双向链表存储结构实现

![](/_images/database/redis/basic/List类型.png)

## 基本操作

```
基本操作：
添加/修改数据
lpush key value1 [value2] ……
rpush key value1 [value2] ……

获取数据
lrange key start stop
lindex key index
llen key

获取并移除数据
lpop key
rpop key
```

## 扩展操作

```
规定时间内获取并移除数据
blpop key1 [key2] timeout
brpop key1 [key2] timeout
brpoplpush source destination timeout
```

**应用场景6：**
微信朋友圈点赞，要求按照点赞顺序显示点赞好友信息。如果取消点赞，移除对应好友信息

![](/_images/database/redis/basic/List应用朋友圈点赞.png)

**解决方案：**

```
移除指定数据
lrem key count value
```

**应用场景7：**
twitter、新浪微博、腾讯微博中个人用户的关注列表需要按照用户的关注顺序进行展示，粉丝列表需要将最
近关注的粉丝列在前面。
新闻、资讯类网站如何将最新的新闻或资讯按照发生的时间顺序展示？
企业运营过程中，系统将产生出大量的运营数据，如何保障多台服务器操作日志的统一顺序输出？ 

**解决方案**

```
依赖list的数据具有顺序的特征对信息进行管理
使用队列模型解决多路信息汇总合并的问题
使用栈模型解决最新消息的问题
```

## 总结

1. redis 应用于具有操作先后顺序的数据控制
2. redis 应用于最新消息展

# Set类型

1. 新的存储需求：存储大量的数据，在查询方面提供更高的效率
2. 需要的存储结构：能够保存大量的数据，高效的内部存储机制，便于查询
3. set类型：与hash存储结构完全相同，仅存储键，不存储值（ nil），并且值是不允许重复的。

## 基本操作

```
添加数据
sadd key member1 [member2]

获取全部数据
smembers key

删除数据
srem key member1 [member2]

判断集合中是否包含指定数据
scard key

获取集合数据总量
sismember key member
```

## 扩展操作

**应用场景8：**
每位用户首次使用今日头条、知乎、抖音等软件时会设置3项爱好的内容，但是后期为了增加用户的活跃度、兴趣点，必须让用户
对其他信息类别逐渐产生兴趣，增加客户留存度，如何实现？

![](/_images/database/redis/basic/Set应用知乎选择爱好.png)

**解决方案**

```
1.系统分析出各个分类的最新或最热点信息条目并组织成set集合
2.随机挑选其中部分信息
3.配合用户关注信息分类中的热点信息组织成展示的全信息集合

随机获取集合中指定数量的数据
srandmember key [count]
随机获取集合中的某个数据并将该数据移出集合
spop key [count]
```

**应用场景9：**
脉脉为了促进用户间的交流，保障业务成单率的提升，需要让每位用户拥有大量的好友，事实上职场新人不
具有更多的职场好友，如何快速为用户积累更多的好友？
新浪微博为了增加用户热度，提高用户留存性，需要微博用户在关注更多的人，以此获得更多的信息或热门
话题，如何提高用户关注他人的总量？
QQ新用户入网年龄越来越低，这些用户的朋友圈交际圈非常小，往往集中在一所学校甚至一个班级中，如何
帮助用户快速积累好友用户带来更多的活跃度？
微信公众号是微信信息流通的渠道之一，增加用户关注的公众号成为提高用户活跃度的一种方式，如何帮助
用户积累更多关注的公众号？
美团外卖为了提升成单量，必须帮助用户挖掘美食需求，如何推荐给用户最适合自己的美食？

**解决方案：**

```
求两个集合的交、并、差集
sinter key1 [key2]
sunion key1 [key2]
sdiff key1 [key2]

求两个集合的交、并、差集并存储到指定集合中
sinterstore destination key1 [key2]
sunionstore destination key1 [key2]
sdiffstore destination key1 [key2]

将指定数据从原始集合中移动到目标集合中
smove source destination member
```

**应用场景10：**
1.集团公司共具有12000名员工，内部OA系统中具有700多个角色，3000多个业务操作， 23000多种数据，每
位员工具有一个或多个角色，如何快速进行业务操作的权限校验？
2.公司对旗下新的网站做推广，统计网站的PV（访问量） ,UV（独立访客） ,IP（独立IP）。
PV：网站被访问次数，可通过刷新页面提高访问量
UV：网站被不同用户访问的次数，可通过cookie统计访问量，相同用户切换IP地址， UV不变
IP：网站被不同IP地址访问的总次数，可通过IP地址统计访问量，相同IP不同用户访问， IP不变

**解决方案:**

```
利用set集合的数据去重特征，记录各种访问数据
建立string类型数据，利用incr统计日访问量（ PV）
建立set模型，记录不同cookie数量（ UV）
建立set模型，记录不同IP数量（ IP）
```

## 总结

1. redis 应用于随机推荐类信息检索，例如热点歌单推荐，热点新闻推荐，热卖旅游线路，应用APP推荐，
   大V推荐等
2. redis 应用于同类信息的关联搜索，二度关联搜索，深度关联搜索
   显示共同关注（一度）
   显示共同好友（一度）
   由用户A出发，获取到好友用户B的好友信息列表（一度）
   由用户A出发，获取到好友用户B的购物清单列表（二度）
   由用户A出发，获取到好友用户B的游戏充值列表（二度）
3. redis 应用于同类型数据的快速去重

# sorted_set类型

sorted_set中的每一个元素都带有一个score属性，可以基于score属性对元素排序，底层的实现是一个跳表（SkipList）加 hash表。


1. 新的存储需求：数据排序有利于数据的有效展示，需要提供一种可以根据自身特征进行排序的方式
2. 需要的存储结构：新的存储模型，可以保存可排序的数据
3. sorted_set类型：在set的存储结构基础上添加可排序字段

## 基本操作

```
添加数据
zadd key score1 member1 [score2 member2]
获取全部数据
zrange key start stop [WITHSCORES]
zrevrange key start stop [WITHSCORES]
删除数据
zrem key member [member ...]
```

## 扩展操作

```
按条件获取数据
zrangebyscore key min max [WITHSCORES] [LIMIT]
zrevrangebyscore key max min [WITHSCORES]
条件删除数据
zremrangebyrank key start stop
zremrangebyscore key min max

获取集合数据总量
zcard key
zcount key min max

集合交、并操作
zinterstore destination numkeys key [key ...]
zunionstore destination numkeys key [key ...]
```

**应用场景10：**
票选广东十大杰出青年，各类综艺选秀海选投票
各类资源网站TOP10（电影，歌曲，文档，电商，游戏等）
QQ好友亲密度

![](/_images/database/redis/basic/sorted_set应用豆瓣电影排名.png)

**解决方案：**

```
为所有参与排名的资源建立排序依据

score值获取与修改
zrank key member
zrevrank key member

获取数据对应的索引（排名）,例如豆瓣电影打分
zscore key member
zincrby key increment member
```

**应用场景11：**
迅雷下载会员试用，腾讯视频VIP体验等。当VIP体验到期后，如何有效管理此类信息。

**解决方案：**

```
1.对于基于时间线限定的任务处理，将处理时间记录为score值，利用排序功能区分处理的先后顺序
2.记录下一个要处理的时间，当到期后处理对应任务，移除redis中的记录，并记录下一个要处理的时间
3.当新任务加入时，判定并更新当前下一个要处理的任务时间
4.为提升sorted_set的性能，通常将任务根据特征存储成若干个sorted_set。例如1小时内， 1天内，周内，
月内，季内，年度等，操作时逐级提升，将即将操作的若干个任务纳入到1小时内处理的队列中

获取当前系统时间
time
```

## 总结

1. redis 应用于计数器组合排序功能对应的排名
2. redis 应用于定时任务执行顺序管理或任务过期管理