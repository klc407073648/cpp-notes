# MySQL - 存储引擎

[[toc]]

# 存储引擎概述

> 存储引擎是指表的类型，数据库的存储引擎决定了表在计算机中的存储方式。在MySQL中可以通过SHOW ENGINES来查询存储引擎的相关信息。

```sql
mysql> show engines;
+--------------------+---------+----------------------------------------------------------------+--------------+------+------------+
| Engine             | Support | Comment                                                        | Transactions | XA   | Savepoints |
+--------------------+---------+----------------------------------------------------------------+--------------+------+------------+
| FEDERATED          | NO      | Federated MySQL storage engine                                 | NULL         | NULL | NULL       |
| MRG_MYISAM         | YES     | Collection of identical MyISAM tables                          | NO           | NO   | NO         |
| MyISAM             | YES     | MyISAM storage engine                                          | NO           | NO   | NO         |
| BLACKHOLE          | YES     | /dev/null storage engine (anything you write to it disappears) | NO           | NO   | NO         |
| CSV                | YES     | CSV storage engine                                             | NO           | NO   | NO         |
| MEMORY             | YES     | Hash based, stored in memory, useful for temporary tables      | NO           | NO   | NO         |
| ARCHIVE            | YES     | Archive storage engine                                         | NO           | NO   | NO         |
| InnoDB             | DEFAULT | Supports transactions, row-level locking, and foreign keys     | YES          | YES  | YES        |
| PERFORMANCE_SCHEMA | YES     | Performance Schema                                             | NO           | NO   | NO         |
+--------------------+---------+----------------------------------------------------------------+--------------+------+------------+
9 rows in set
```

参数说明：Engine指存储引擎名称；Support表示MySQL是否支持该类型引擎；Comment指引擎的描述；Transactions指是否支持事务处理；XA表示是否分布式交易处理的XA规范；Savepoints指是否支持保存点，以便事务回滚到保存点。

# 存储引擎介绍

MySQL数据库最常用的三大存储引擎为**InnoDB, MyISAM, MEMORY**，其中默认的存储引擎是InnoDB。下面将详细介绍这三种存储引擎的特点。

## InnoDB存储引擎

InnoDB给MySQL的表**提供了事务、回滚、崩溃修复能力和多版本并发控制的事务安全**，是MySQL上第一个提供外键约束的表引擎。**支持自动增长列AUTO_INCREMENT，值不为空且唯一，规定自增列必须为主键**。支持外键FOREIGN KEY，外键所在的表为子表，外键依赖的表为父表，父表中被子表关联的字段必须为主键。InnoDB存储引擎中，创建的表的结构存储在.frm文件中，数据和索引存储在innodb_data_home_dir和innodb_data_file_path定义的表空间。

InnoDB存储引擎的优势在于提供了良好的事务处理、崩溃修复能力和并发控制，缺点是读写效率较差，占用的数据空间相对较大。使用场景：对事务的完整性要求较高，且要求实现并发控制，选择InnoDB有很大优势。 如果需要频繁进行更新、删除操作，也可以选择InnoDB存储引擎，该类引擎可以实现事务的提交和回滚。

## MyISAM存储引擎

基于ISAM发展的，MyISAM存储引擎的表存储为3个文件，文件的名字与表名相同，扩展名包括frm、MYD和MYI，frm扩展名的文件存储表结构，MYD扩展名文件存储数据MYData，MYI扩展名的文件存储索引。

MyISAM存储引擎的表支持3种不同的存储格式，包括静态型、动态型和压缩型。默认存储为静态型，字段固定长度；动态型包括变长字段，记录的长度不固定；压缩型需要使用myisampack工具创建，占用磁盘空间小。优势在于占用空间小，处理速度快。缺点是不支持事务的完整性和并发性。

MyISAM存储引擎的优势**在于插入数据快，空间和内存使用比较低，缺点是不支持事务的完整性和并行性**。使用场景：如果表主要用于插入新记录和读出记录，或者对应用的完整性、并发性要求很低，则可以选择MyISAM存储引擎。

## MEMORY存储引擎

MEMORY存储引擎使用其存储在内存中的内容创建表，数据也存放在内存中。每个基于MEMORY存储引擎的表实际对应一个磁盘文件，文件的文件名与表名相同，类型为frm类型。该文件中只存储表结构，数据存储在内存中。服务器需要有足够多的内存维持MEMORY存储引擎的表的使用。该存储引擎**默认使用哈希索引，速度比B型树索引快（随机查询快，范围查询不如B+树）**。

基于MEMORY存储引擎的表的生命周期很短，一般是一次性的。表的大小受限制，大小主要取决于max_rows和max_heap_table_size参数，max_rows在创建表时指定，max_heap_table_size默认大小为16MB，可以按需扩大。处理速度快，但数据易丢失，生命周期短。

MEMORY存储引擎的优势**在于处理速度非常快，缺点是数据易丢失，生命周期短**。使用场景：如果需要很快的读写速度，对数据安全性要求较低可以选择MEMORY存储引擎。对表的大小有要求。

# 存储引擎对比

1. 使用的索引类型不同：
    * InnoDB   B+树索引
    * MyISAM   B+树索引
    * MEMORY   Hash索引

2. 对应表在磁盘上法存储文件格式不同：

    test1,test2,test3分别对应InnoDB，MyISAM，MEMORY。

![存储引擎对比](/_images/database/mysql/存储引擎对比.png)

3.应用场景 ：
    * 事务处理和并发控制：InnoDB
    * 查询要求高：MyISAM
    * 需要创建临时表用于查询：MEMORY

​