# MySQL进阶 - 管理工具

[[toc]]

# 系统数据库

Mysql数据库安装完成后，自带了一下四个数据库，具体作用如下：数据库 含义

| 数据库 | 含义 | 
| --------------------- | ----------- | 
| mysql | 存储MySQL服务器正常运行所需要的各种信息 （时区、主从、用户、权限等） | 
| information_schema | 提供了访问数据库元数据的各种表和视图，包含数据库、表、字段类型及访问权限等 | 
| performance_schema | 为MySQL服务器运行时状态提供了一个底层监控功能，主要用于收集数据库服务器性能参数 | 
| sys | 包含了一系列方便 DBA 和开发人员利用 performance_schema性能数据库进行性能调优和诊断的视图 | 

# 常用工具

## mysql

该mysql不是指mysql服务，而是指mysql的客户端工具。

```sql
语法 ：
    mysql [options] [database]
选项 ：
    -u, --user=name #指定用户名
    -p, --password[=name] #指定密码
    -h, --host=name #指定服务器IP或域名
    -P, --port=port #指定连接端口
    -e, --execute=name #执行SQL语句并退出
```

-e选项可以在MySQL客户端执行SQL语句，而不用连接到MySQL数据库再执行，对于一些批处理脚本，这种方式尤其方便。

示例：

```sql
[root@VM-16-6-centos mysql]# mysql -uroot -p456789 db01 -e "select * from stu";
mysql: [Warning] Using a password on the command line interface can be insecure.
+----+-------+-----+
| id | name  | age |
+----+-------+-----+
|  1 | tom   |   1 |
|  3 | cat   |   3 |
|  8 | rose  |   8 |
| 11 | jetty |  11 |
| 19 | lily  |  19 |
| 25 | luci  |  25 |
+----+-------+-----+

```

## mysqladmin

mysqladmin 是一个执行管理操作的客户端程序。可以用它来检查服务器的配置和当前状态、创建并删除数据库等。

```sql
通过帮助文档查看选项：
    * mysqladmin --help

语法:
mysqladmin [options] command ...
选项:
    -u, --user=name #指定用户名
    -p, --password[=name] #指定密码
    -h, --host=name #指定服务器IP或域名
    -P, --port=port #指定连接端口
```


示例：

```sql
-- 查看版本信息
[root@VM-16-6-centos mysql]# mysqladmin -uroot -p456789 version
mysqladmin: [Warning] Using a password on the command line interface can be insecure.
mysqladmin  Ver 8.0.26 for Linux on x86_64 (MySQL Community Server - GPL)
Copyright (c) 2000, 2021, Oracle and/or its affiliates.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Server version          8.0.26
Protocol version        10
Connection              Localhost via UNIX socket
UNIX socket             /var/lib/mysql/mysql.sock
Uptime:                 17 min 9 sec

Threads: 7  Questions: 65  Slow queries: 0  Opens: 235  Flush tables: 3  Open tables: 154  Queries per second avg: 0.063

-- 查看服务器状态
[root@VM-16-6-centos mysql]# mysqladmin -uroot -p456789 status
mysqladmin: [Warning] Using a password on the command line interface can be insecure.
Uptime: 1085  Threads: 7  Questions: 67  Slow queries: 0  Opens: 235  Flush tables: 3  Open tables: 154  Queries per second avg: 0.061

```

## mysqlbinlog

由于服务器生成的二进制日志文件以二进制格式保存，所以如果想要检查这些文本的文本格式，就会使用到mysqlbinlog 日志管理工具。

```sql
语法 ：
    mysqlbinlog [options] log-files1 log-files2 ...
选项 ：
    -d, --database=name 指定数据库名称，只列出指定的数据库相关操作。
    -o, --offset=# 忽略掉日志中的前n行命令。
    -r,--result-file=name 将输出的文本格式日志输出到指定文件。
    -s, --short-form 显示简单格式， 省略掉一些信息。
    --start-datatime=date1 --stop-datetime=date2 指定日期间隔内的所有日志。
    --start-position=pos1 --stop-position=pos2 指定位置间隔内的所有日志。
```

示例：

```sql
-- A. 查看 binlog.000008这个二进制文件中的数据信息
[root@VM-16-6-centos mysql]# mysqlbinlog  binlog.000002
# The proper term is pseudo_replica_mode, but we use this compatibility alias
# to make the statement usable on server versions 8.0.24 and older.
/*!50530 SET @@SESSION.PSEUDO_SLAVE_MODE=1*/;
/*!50003 SET @OLD_COMPLETION_TYPE=@@COMPLETION_TYPE,COMPLETION_TYPE=0*/;

-- B. 可以加上一个参数 -s 来显示简单格式
[root@VM-16-6-centos mysql]# mysqlbinlog  binlog.000002
# The proper term is pseudo_replica_mode, but we use this compatibility alias
# to make the statement usable on server versions 8.0.24 and older.
/*!50530 SET @@SESSION.PSEUDO_SLAVE_MODE=1*/;
/*!50003 SET @OLD_COMPLETION_TYPE=@@COMPLETION_TYPE,COMPLETION_TYPE=0*/;
```

## mysqlshow

mysqlshow 客户端对象查找工具，用来很快地查找存在哪些数据库、数据库中的表、表中的列或者索引。

```sql
语法 ：
    mysqlshow [options] [db_name [table_name [col_name]]]
选项 ：
    --count 显示数据库及表的统计信息（数据库，表 均可以不指定）
    -i 显示指定数据库或者指定表的状态信息
```

示例：

```sql
-- A. 查询每个数据库的表的数量及表中记录的数量
[root@VM-16-6-centos mysql]# mysqlshow -uroot -p456789 --count
mysqlshow: [Warning] Using a password on the command line interface can be insecure.
+--------------------+--------+--------------+
|     Databases      | Tables |  Total Rows  |
+--------------------+--------+--------------+
| db01               |      5 |           44 |
| information_schema |     79 |        26372 |
| mysql              |     37 |         3879 |
| performance_schema |    110 |       245812 |
| sys                |    101 |         5012 |
+--------------------+--------+--------------+
5 rows in set.


-- B. 查看数据库db01的统计信息
[root@VM-16-6-centos mysql]# mysqlshow -uroot -p456789 db01 --count
mysqlshow: [Warning] Using a password on the command line interface can be insecure.
Database: db01
+----------------+----------+------------+
|     Tables     | Columns  | Total Rows |
+----------------+----------+------------+
| course         |        2 |          4 |
| stu            |        3 |          6 |
| student        |        3 |          4 |
| student_course |        3 |          6 |
| tb_user        |        9 |         24 |
+----------------+----------+------------+
5 rows in set.

-- C. 查询db01库中course表的详细情况
[root@VM-16-6-centos mysql]# mysqlshow -uroot -p456789 db01 course --count
mysqlshow: [Warning] Using a password on the command line interface can be insecure.
Database: db01  Table: course  Rows: 4
+-------+-------------+-----------------+------+-----+---------+----------------+---------------------------------+--------------+
| Field | Type        | Collation       | Null | Key | Default | Extra          | Privileges                      | Comment      |
+-------+-------------+-----------------+------+-----+---------+----------------+---------------------------------+--------------+
| id    | int         |                 | NO   | PRI |         | auto_increment | select,insert,update,references | 主键ID     |
| name  | varchar(10) | utf8_general_ci | YES  |     |         |                | select,insert,update,references | 课程名称 |
+-------+-------------+-----------------+------+-----+---------+----------------+---------------------------------+--------------+

-- D. 查看数据库db01中的course表的id字段的信息
[root@VM-16-6-centos mysql]# mysqlshow -uroot -p456789 db01 course id --count
mysqlshow: [Warning] Using a password on the command line interface can be insecure.
Database: db01  Table: course  Rows: 4  Wildcard: id
+-------+------+-----------+------+-----+---------+----------------+---------------------------------+----------+
| Field | Type | Collation | Null | Key | Default | Extra          | Privileges                      | Comment  |
+-------+------+-----------+------+-----+---------+----------------+---------------------------------+----------+
| id    | int  |           | NO   | PRI |         | auto_increment | select,insert,update,references | 主键ID |
+-------+------+-----------+------+-----+---------+----------------+---------------------------------+----------+

```

## mysqldump

mysqldump 客户端工具用来备份数据库或在不同数据库之间进行数据迁移。备份内容包含创建表，及插入表的SQL语句。

```sql
语法 ：
mysqldump [options] db_name [tables]
mysqldump [options] --database/-B db1 [db2 db3...]
mysqldump [options] --all-databases/-A
连接选项 ：
    -u, --user=name 指定用户名
    -p, --password[=name] 指定密码
    -h, --host=name 指定服务器ip或域名
    -P, --port=# 指定连接端口
输出选项：
    --add-drop-database 在每个数据库创建语句前加上 drop database 语句
    --add-drop-table 在每个表创建语句前加上 drop table 语句 , 默认开启 ; 不开启 (--skip-add-drop-table)
    -n, --no-create-db 不包含数据库的创建语句
    -t, --no-create-info 不包含数据表的创建语句
    -d --no-data 不包含数据
    -T, --tab=name 自动生成两个文件：一个.sql文件，创建表结构的语句；一个.txt文件，数据文件

```

示例：

```sql
-- A. 备份db01数据库
mysqldump -uroot -p456789 db01 > db01.sql

-- B. 备份db01数据库中的表数据，不备份表结构(-t)
mysqldump -uroot -p456789 -t db01 > db01.sql


-- C. 将db01数据库的表的表结构与数据分开备份(-T)
[root@VM-16-6-centos mysql]# mysqldump -uroot -p456789 -T /var/lib/mysql-files/ db01 stu
mysqldump: [Warning] Using a password on the command line interface can be insecure.
[root@VM-16-6-centos mysql]# cd /var/lib/mysql-files/
[root@VM-16-6-centos mysql-files]# ls -al
total 16
drwxr-x---   2 mysql mysql 4096 Oct  3 21:21 .
drwxr-xr-x. 37 root  root  4096 Oct  3 09:50 ..
-rw-r--r--   1 root  root  1446 Oct  3 21:21 stu.sql
-rw-r-----   1 mysql mysql   59 Oct  3 21:21 stu.txt

```

## mysqlimport/source

### mysqlimport

mysqlimport 是客户端数据导入工具，用来导入mysqldump 加 -T 参数后导出的文本文件。

语法 ：
    
    mysqlimport [options] db_name textfile1 [textfile2...]

```
## 清空表数据后，mysqlimport数据文件txt
[root@VM-16-6-centos mysql-files]# mysqlimport -uroot -p456789 db01 /var/lib/mysql-files/stu.txt
mysqlimport: [Warning] Using a password on the command line interface can be insecure.
db01.stu: Records: 6  Deleted: 0  Skipped: 0  Warnings: 0
```

### source

如果需要导入sql文件,可以使用mysql中的source 指令 :

```bash
[root@VM-16-6-centos mysql-files]# mysql -u root -p456789
mysql> source /var/lib/mysql-files/stu.sql;
Query OK, 0 rows affected (0.00 sec)
```