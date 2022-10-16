# MySQL运维 - 日志分析

[[toc]]

## 错误日志

错误日志是 MySQL 中最重要的日志之一，它记录了当 mysqld 启动和停止时，以及服务器在运行过程中发生任何严重错误时的相关信息。当数据库出现任何故障导致无法正常使用时，建议首先查看此日志。

该日志是默认开启的，默认存放目录 /var/log/，默认的日志文件名为 mysqld.log 。查看日志位置：

```sql
mysql> show variables like "%log_error%";
+----------------------------+----------------------------------------+
| Variable_name              | Value                                  |
+----------------------------+----------------------------------------+
| binlog_error_action        | ABORT_SERVER                           |
| log_error                  | /var/log/mysqld.log                    |
| log_error_services         | log_filter_internal; log_sink_internal |
| log_error_suppression_list |                                        |
| log_error_verbosity        | 2                                      |
+----------------------------+----------------------------------------+
5 rows in set (0.00 sec)
```

测试错误日志：

```
# 1.修改 vi /var/lib/mysql/auto.cnf，把uuid删除一位

# 2. 重启mysql服务，systemctl restart mysqld

# 3. 实时查看错误日志内容： tail -f /var/log/mysqld.log ，报UUID无效

2022-10-06T02:40:28.799538Z 0 [ERROR] [MY-010073] [Server] The server_uuid stored in auto.cnf file is not a valid UUID.
2022-10-06T02:40:28.799640Z 0 [ERROR] [MY-010076] [Server] Initialization of the server's UUID failed because it could not be read from the auto.cnf file. If this is a new server, the initialization failed because it was not possible to generate a new UUID.
2022-10-06T02:40:28.799701Z 0 [ERROR] [MY-010119] [Server] Aborting

# 4. 修改回去后，重启mysql服务恢复正常
```

## 二进制日志

二进制日志（BINLOG）**记录了所有的 DDL（数据定义语言）语句和 DML（数据操纵语言）语句**，但不包括数据查询（SELECT、SHOW）语句。

作用：

1. 灾难时的数据恢复；
2. MySQL的主从复制。

在MySQL8版本中，默认二进制日志是开启着的，涉及到的参数如下：

```sql
mysql> show variables like '%log_bin%';
+---------------------------------+-----------------------------+
| Variable_name                   | Value                       |
+---------------------------------+-----------------------------+
| log_bin                         | ON                          |
| log_bin_basename                | /var/lib/mysql/binlog       |
| log_bin_index                   | /var/lib/mysql/binlog.index |
| log_bin_trust_function_creators | OFF                         |
| log_bin_use_v1_row_events       | OFF                         |
| sql_log_bin                     | ON                          |
+---------------------------------+-----------------------------+
6 rows in set (0.01 sec)
```

* log_bin_basename：当前数据库服务器的binlog日志的基础名称(前缀)，具体的binlog文件名需要再该basename的基础上加上编号(编号从000001开始)。
* log_bin_index：binlog的索引文件，里面记录了当前服务器关联的binlog文件有哪些

```
[root@VM-16-6-centos mysql]# ls -al |grep binlog
-rw-r-----   1 mysql mysql      179 Oct  3 09:50 binlog.000001
-rw-r-----   1 mysql mysql    16924 Oct  4 02:35 binlog.000002
-rw-r-----   1 mysql mysql      179 Oct  6 10:40 binlog.000003
-rw-r-----   1 mysql mysql      156 Oct  6 10:41 binlog.000004
-rw-r-----   1 mysql mysql       64 Oct  6 10:41 binlog.index

[root@VM-16-6-centos mysql]# cat binlog.index
./binlog.000001
./binlog.000002
./binlog.000003
./binlog.000004
```

### 格式

MySQL服务器中提供了多种格式来记录二进制日志，具体格式及特点如下：

| 日志格式 | 含义 | 
| --------------------- | ----------- | 
| STATEMENT | 基于SQL语句的日志记录，记录的是SQL语句，对数据进行修改的SQL都会记录在日志文件中。 | 
| ROW | 基于行的日志记录，记录的是每一行的数据变更。（默认） | 
| MIXED | 混合了STATEMENT和ROW两种格式，默认采用STATEMENT，在某些特殊情况下会自动切换为ROW进行记录。 | 


```sql
mysql> show variables like '%binlog_format%';
+---------------+-------+
| Variable_name | Value |
+---------------+-------+
| binlog_format | ROW   |
+---------------+-------+
1 row in set (0.00 sec)
```

如果我们需要配置二进制日志的格式，只需要在 /etc/my.cnf 中配置 binlog_format 参数即可。

<<< @/md/database/mysql/operation/src/binlog_row.sql

修改 binlog_format 为 STATEMENT，再次测试

```
1. vi /etc/my.cnf ,添加binlog_format=STATEMENT
2. 重启mysql服务
3. 执行更新操作

mysql> update score set math = math +1;
ERROR 2013 (HY000): Lost connection to MySQL server during query
No connection. Trying to reconnect...
Connection id:    8
Current database: db01

Query OK, 3 rows affected (0.03 sec)
Rows matched: 3  Changed: 3  Warnings: 0

mysql> update score set math = math +1 where id =1;
Query OK, 1 row affected (0.01 sec)
Rows matched: 1  Changed: 1  Warnings: 0

4. 修改 binlog_format后，binlog文件会从新的索引开始，且只会记录变更操作，不包含查询语句

[root@VM-16-6-centos mysql]# mysqlbinlog  binlog.000005

use `db01`/*!*/;
SET TIMESTAMP=1665025814/*!*/;
update score set math = math +1
SET TIMESTAMP=1665025894/*!*/;
update score set math = math +1 where id =1
```

### 查看

由于日志是以二进制方式存储的，不能直接读取，需要通过二进制日志查询工具 mysqlbinlog 来查看，具体语法：

```
mysqlbinlog [ 参数选项 ] logfilename
参数选项：
    -d 指定数据库名称，只列出指定的数据库相关操作。
    -o 忽略掉日志中的前n行命令。
    -v 将行事件(数据变更)重构为SQL语句
    -vv 将行事件(数据变更)重构为SQL语句，并输出注释信息
```

### 删除

对于比较繁忙的业务系统，每天生成的binlog数据巨大，如果长时间不清除，将会占用大量磁盘空间。可以通过以下几种方式清理日志：

| 日志格式 | 含义 | 
| --------------------- | ----------- | 
| reset master | 删除全部 binlog 日志，删除之后，日志编号，将从 binlog.000001重新开始 | 
| purge master logs to 'binlog.*' | 删除 * 编号之前的所有日志 | 
| purge master logs before 'yyyy-mm-dd hh24:mi:ss' | 删除日志为 "yyyy-mm-dd hh24:mi:ss" 之前产生的所有日志 | 

```sql
-- 删除 binlog.000002 之前的日志
mysql> purge master logs to 'binlog.000002';
Query OK, 0 rows affected (0.03 sec)

-- 删除 全部的binlog 日志
mysql> reset master;
Query OK, 0 rows affected (0.03 sec)

-- 未清理前
[root@VM-16-6-centos mysql]# ls -al |grep binlog
-rw-r-----   1 mysql mysql      179 Oct  3 09:50 binlog.000001
-rw-r-----   1 mysql mysql    16924 Oct  4 02:35 binlog.000002
-rw-r-----   1 mysql mysql      179 Oct  6 10:40 binlog.000003
-rw-r-----   1 mysql mysql     1304 Oct  6 11:09 binlog.000004
-rw-r-----   1 mysql mysql      804 Oct  6 11:11 binlog.000005
-rw-r-----   1 mysql mysql       80 Oct  6 11:09 binlog.index

-- 删除 binlog.000002 之前的日志
[root@VM-16-6-centos mysql]# ls -al |grep binlog
-rw-r-----   1 mysql mysql    16924 Oct  4 02:35 binlog.000002
-rw-r-----   1 mysql mysql      179 Oct  6 10:40 binlog.000003
-rw-r-----   1 mysql mysql     1304 Oct  6 11:09 binlog.000004
-rw-r-----   1 mysql mysql      804 Oct  6 11:11 binlog.000005
-rw-r-----   1 mysql mysql       64 Oct  6 11:19 binlog.index

-- 删除 全部的binlog 日志
[root@VM-16-6-centos mysql]# ls -al |grep binlog
-rw-r-----   1 mysql mysql      156 Oct  6 11:19 binlog.000001
-rw-r-----   1 mysql mysql       16 Oct  6 11:19 binlog.index

```

在mysql的配置文件中配置二进制日志的过期时间，设置了之后，二进制日志过期会自动删除(默认2592000秒，30天)。

```sql
mysql> show variables like '%binlog_expire_logs_seconds%';
+----------------------------+---------+
| Variable_name              | Value   |
+----------------------------+---------+
| binlog_expire_logs_seconds | 2592000 |
+----------------------------+---------+
1 row in set (0.01 sec)
```

## 查询日志

查询日志中记录了**客户端的所有操作语句**，而二进制日志不包含查询数据的SQL语句。默认情况下，查询日志是未开启的。

```sql
mysql> show variables like '%general%';
+------------------+-----------------------------------+
| Variable_name    | Value                             |
+------------------+-----------------------------------+
| general_log      | OFF                               |
| general_log_file | /var/lib/mysql/VM-16-6-centos.log |
+------------------+-----------------------------------+
2 rows in set (0.01 sec)
```

可以通过修改MySQL的配置文件 /etc/my.cnf 文件，开启查询日志：

```
#该选项用来开启查询日志 ， 可选值 ： 0 或者 1 ； 0 代表关闭， 1 代表开启
general_log=1
#设置日志的文件名 ， 如果没有指定， 默认的文件名为 host_name.log
general_log_file=mysql_query.log
```

开启了查询日志之后，在MySQL的数据存放目录，也就是 /var/lib/mysql/ 目录下就会出现mysql_query.log 文件。之后所有的客户端的增删改查操作都会记录在该日志文件之中，长时间运行后，该日志文件将会非常大。


```sql
mysql> update score set math = math +1;
Query OK, 3 rows affected (0.01 sec)
Rows matched: 3  Changed: 3  Warnings: 0

mysql> drop table stu;
Query OK, 0 rows affected (0.05 sec)


[root@VM-16-6-centos mysql]# tail -f mysql_query.log
/usr/sbin/mysqld, Version: 8.0.26 (MySQL Community Server - GPL). started with:
Tcp port: 3306  Unix socket: /var/lib/mysql/mysql.sock
Time                 Id Command    Argument
2022-10-06T03:30:13.041467Z         8 Connect   root@localhost on db01 using Socket
2022-10-06T03:30:13.042940Z         8 Query     show databases
2022-10-06T03:30:13.053659Z         8 Query     show tables
2022-10-06T03:30:13.057379Z         8 Field List        course
2022-10-06T03:30:13.067804Z         8 Field List        score
2022-10-06T03:30:13.069494Z         8 Field List        stu
2022-10-06T03:30:13.070706Z         8 Field List        student
2022-10-06T03:30:13.072610Z         8 Field List        student_course
2022-10-06T03:30:13.073246Z         8 Field List        tb_user
2022-10-06T03:30:13.074786Z         8 Query     select * from score
2022-10-06T03:31:16.157879Z         8 Query     update score set math = math +1
2022-10-06T03:31:53.716311Z         8 Query     drop table stu
```

## 慢查询日志

慢查询日志记录了所有执行时间超过参数 long_query_time 设置值并且扫描记录数不小于min_examined_row_limit 的所有的SQL语句的日志，默认未开启。long_query_time 默认为10 秒，最小为 0， 精度可以到微秒。

可以通过修改MySQL的配置文件 /etc/my.cnf 文件，开启慢查询日志：

```
#慢查询日志
slow_query_log=1
#执行时间参数
long_query_time=2
```

测试：

```sql
mysql> select count(*) from big_data;
+----------+
| count(*) |
+----------+
| 10000000 |
+----------+
1 row in set (2.78 sec)

[root@VM-16-6-centos mysql]# tail -f VM-16-6-centos-slow.log
# Time: 2022-09-10T05:48:27.412308Z
# User@Host: root[root] @ localhost []  Id:    30
# Query_time: 2.781475  Lock_time: 0.000132 Rows_sent: 1  Rows_examined: 10000000
SET timestamp=1662788907;
select count(*) from big_data;
```


默认情况下，不会记录管理语句，也不会记录不使用索引进行查找的查询。可以使用log_slow_admin_statements和 更改此行为 log_queries_not_using_indexes，如下所述。

上述所有的参数配置完成之后，都需要重新启动MySQL服务器才可以生效。

```
#记录执行较慢的管理语句
log_slow_admin_statements =1
#记录执行较慢的未使用索引的语句
log_queries_not_using_indexes = 1
```