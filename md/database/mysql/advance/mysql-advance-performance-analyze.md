# MySQL进阶 - SQL性能分析

[[toc]]

## 概述

> MySQL 客户端连接成功后，通过 show [session|global] status 命令可以提供服务器状态信息。通过如下指令，可以查看当前数据库的INSERT、UPDATE、DELETE、SELECT的访问频次：

```mysql
-- session 是查看当前会话 ;
-- global 是查询全局数据 ;
SHOW GLOBAL STATUS LIKE 'Com_______';
```

查询结果：

```mysql
mysql> SHOW GLOBAL STATUS LIKE 'Com_______';
+---------------+-------+
| Variable_name | Value |
+---------------+-------+
| Com_binlog    | 0     |
| Com_commit    | 0     |
| Com_delete    | 0     |
| Com_insert    | 50    |
| Com_repair    | 0     |
| Com_revoke    | 0     |
| Com_select    | 8     |
| Com_signal    | 0     |
| Com_update    | 0     |
| Com_xa_end    | 0     |
+---------------+-------+
10 rows in set (0.00 sec)
```

通过上述指令，我们可以查看到**当前数据库到底是以查询为主，还是以增删改为主**，从而为数据库优化提供参考依据。 如果是以增删改为主，我们可以考虑不对其进行索引的优化。 如果是以查询为主，那么就要考虑对数据库的索引进行优化了。

假如数据库是以查询为主，又该如何定位针对于那些查询语句进行优化呢？ 次数我们可以借助于慢查询日志。

接下来，我们就来介绍一下MySQL中的慢查询日志。

## 慢查询日志

> 慢查询日志记录了所有执行时间超过指定参数（long_query_time，单位：秒，默认10秒）的所有SQL语句的日志。

MySQL的慢查询日志默认没有开启，需要在MySQL的配置文件（/etc/my.cnf）中配置如下信息：

```mysql
# 开启慢查询日志开关
slow_query_log=1
# 设置慢查询日志的时间为2秒，SQL语句执行时间超过2秒，就会视为慢查询，记录慢查询日志
long_query_time=2
```

更改后记得重启MySQL服务，日志文件位置：/var/lib/mysql/localhost-slow.log

或者采用命令方式设置：

<<< @/md/database/mysql/src/slow_query设置.txt

查看慢查询日志开关状态：
`show variables like 'slow_query_log';`

### 测试

A. 执行如下SQL语句 ：

```
mysql> select count(*) from tb_user;
+----------+
| count(*) |
+----------+
|       24 |
+----------+
1 row in set (0.00 sec)

mysql> select count(*) from big_data;
+----------+
| count(*) |
+----------+
| 10000001 |
+----------+
1 row in set (2.78 sec)
```

B. 检查慢查询日志 ：

最终我们发现，在慢查询日志中，只会记录执行时间超多我们预设时间（2s）的SQL，执行较快的SQL是不会记录的。

```
root@1a11b56b97f7:/# tail -f /var/lib/mysql/1a11b56b97f7-slow.log
# Time: 2022-09-10T05:48:27.412308Z
# User@Host: root[root] @ localhost []  Id:    30
# Query_time: 2.781475  Lock_time: 0.000132 Rows_sent: 1  Rows_examined: 10000001
SET timestamp=1662788907;
select count(*) from big_data;
```

那这样，通过慢查询日志，就可以定位出执行效率比较低的SQL，从而有针对性的进行优化。

## profile

> show profile 能在做SQL优化时帮我们了解时间都耗费在哪里。

通过 have_profiling 参数，能看到当前 MySQL 是否支持 profile 操作：
`SELECT @@have_profiling;`
profiling 默认关闭，可以通过set语句在session/global级别开启 profiling：
`SET profiling = 1;`

**查看指令的执行耗时**：

查看所有语句的耗时：
`show profiles;`
查看指定query_id的SQL语句各个阶段的耗时：
`show profile for query query_id;`
查看指定query_id的SQL语句CPU的使用情况
`show profile cpu for query query_id;`

### 测试

操作示例:

<<< @/md/database/mysql/src/profile测试内容.txt

## explain

> EXPLAIN 或者 DESC 命令获取 MySQL 如何执行 SELECT 语句的信息，包括在 SELECT 语句执行过程中表如何连接和连接的顺序。

语法：

```
# 直接在select语句之前加上关键字 explain / desc
EXPLAIN SELECT 字段列表 FROM 表名 HWERE 条件;
```

```
mysql> explain select * from tb_user where id = 1;
+----+-------------+---------+------------+-------+---------------+---------+---------+-------+------+----------+-------+
| id | select_type | table   | partitions | type  | possible_keys | key     | key_len | ref   | rows | filtered | Extra |
+----+-------------+---------+------------+-------+---------------+---------+---------+-------+------+----------+-------+
|  1 | SIMPLE      | tb_user | NULL       | const | PRIMARY       | PRIMARY | 4       | const |    1 |   100.00 | NULL  |
+----+-------------+---------+------------+-------+---------------+---------+---------+-------+------+----------+-------+
1 row in set, 1 warning (0.00 sec)
```

EXPLAIN 各字段含义：

- id：select 查询的序列号，表示查询中执行 select 子句或者操作表的顺序（id相同，执行顺序从上到下；id不同，值越大越先执行）
- select_type：表示 SELECT 的类型，常见取值有 SIMPLE（简单表，即不适用表连接或者子查询）、PRIMARY（主查询，即外层的查询）、UNION（UNION中的第二个或者后面的查询语句）、SUBQUERY（SELECT/WHERE之后包含了子查询）等
- type：表示连接类型，性能由好到差的连接类型为 NULL、system、const、eq_ref、ref、range、index、all
- possible_key：可能应用在这张表上的索引，一个或多个
- Key：实际使用的索引，如果为 NULL，则没有使用索引
- Key_len：表示索引中使用的字节数，该值为索引字段最大可能长度，并非实际使用长度，在不损失精确性的前提下，长度越短越好
- rows：MySQL认为必须要执行的行数，在InnoDB引擎的表中，是一个估计值，可能并不总是准确的
- filtered：表示返回结果的行数占需读取行数的百分比，filtered的值越大越好