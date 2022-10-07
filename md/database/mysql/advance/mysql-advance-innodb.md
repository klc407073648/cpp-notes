# MySQL进阶 - InnoDB引擎

[[toc]]

# 逻辑存储结构

见存储引擎章节内容：存储引擎

# 架构

MySQL5.5 版本开始，默认使用InnoDB存储引擎，它擅长事务处理，具有崩溃恢复特性，在日常开发中使用非常广泛。下面是InnoDB架构图，左侧为内存结构，右侧为磁盘结构。

![](/_images/database/mysql/advance/InnoDB架构图.png)

## 内存结构

在左侧的内存结构中，主要分为这么四大块儿： Buffer Pool、Change Buffer、Adaptive Hash Index、Log Buffer。

![](/_images/database/mysql/advance/内存结构.png)

1). Buffer Pool

> InnoDB存储引擎基于磁盘文件存储，访问物理硬盘和在内存中进行访问，速度相差很大，为了尽可能弥补这两者之间的I/O效率的差值，就需要把经常使用的数据加载到缓冲池中，避免每次访问都进行磁盘I/O。

在InnoDB的缓冲池中不仅缓存了索引页和数据页，还包含了undo页、插入缓存、自适应哈希索引以及InnoDB的锁信息等等。

缓冲池 Buffer Pool，是主内存中的一个区域，里面可以缓存磁盘上经常操作的真实数据，在执行增删改查操作时，**先操作缓冲池中的数据**（若缓冲池没有数据，则从磁盘加载并缓存），然后**再以一定频率刷新到磁盘**，从而减少磁盘IO，加快处理速度。

缓冲池以Page页为单位，底层采用链表数据结构管理Page。根据状态，将Page分为三种类型：

* free page：空闲page，未被使用。
* clean page：被使用page，数据没有被修改过。
* dirty page：脏页，被使用page，数据被修改过，也中数据与磁盘的数据产生了不一致。

在专用服务器上，通常将多达80％的物理内存分配给缓冲池 。参数设置： 
`show variables like 'innodb_buffer_pool_size';`

2). Change Buffer

Change Buffer，更改缓冲区（针对于**非唯一二级索引页**），在执行DML语句时，如果这些数据Page没有在Buffer Pool中，不会直接操作磁盘，而会将数据变更存在更改缓冲区 Change Buffer
中，在未来数据被读取时，再将数据合并恢复到Buffer Pool中，再将合并后的数据刷新到磁盘中。

Change Buffer的意义是什么呢?

![](/_images/database/mysql/advance/change_buffer.png)

先来看一幅图，这个是二级索引的结构图：与聚集索引不同，二级索引通常是非唯一的，并且以相对随机的顺序插入二级索引。同样，删除和更新可能会影响**索引树中不相邻的二级索引页，如果每一次都操作磁盘，会造成大量的磁盘IO**。有了ChangeBuffer之后，**可以在缓冲池中进行合并处理，减少磁盘IO**。


3). Adaptive Hash Index

自适应hash索引，用于优化对Buffer Pool数据的查询。MySQL的innoDB引擎中虽然没有直接支持hash索引，但是给我们提供了一个功能就是这个自适应hash索引。因为前面我们讲到过，hash索引在
进行等值匹配时，一般性能是要高于B+树的，因为hash索引一般只需要一次IO即可，而B+树，可能需要几次匹配，所以hash索引的效率要高，但是hash索引又不适合做范围查询、模糊匹配等。

InnoDB存储引擎会监控对表上各索引页的查询，如果观察到在特定的条件下hash索引可以提升速度，则建立hash索引，称之为自适应hash索引。

**自适应哈希索引，无需人工干预，是系统根据情况自动完成。**

参数： adaptive_hash_index

```sql
mysql> show variables like '%adaptive_hash_index%';
+----------------------------------+-------+
| Variable_name                    | Value |
+----------------------------------+-------+
| innodb_adaptive_hash_index       | ON    |
| innodb_adaptive_hash_index_parts | 8     |
+----------------------------------+-------+
```
4). Log Buffer

Log Buffer：日志缓冲区，用来保存要写入到磁盘中的log日志数据（redo log 、undo log），默认大小为 16MB，日志缓冲区的日志会定期刷新到磁盘中。如果需要更新、插入或删除许多行的事务，增加日志缓冲区的大小可以节省磁盘 I/O。

参数:

* innodb_log_buffer_size：缓冲区大小
* innodb_flush_log_at_trx_commit：日志刷新到磁盘时机，取值主要包含以下三个：
    * 1: 日志在每次事务提交时写入并刷新到磁盘，默认值。
    * 0: 每秒将日志写入并刷新到磁盘一次。
    * 2: 日志在每次事务提交后写入，并每秒刷新到磁盘一次。

## 磁盘结构

InnoDB体系结构的右边部分，也就是磁盘结构：

![](/_images/database/mysql/advance/磁盘结构.png)

1). System Tablespace

系统表空间是更改缓冲区的存储区域。如果表是在系统表空间而不是每个表文件或通用表空间中创建的，它也可能包含表和索引数据。(在MySQL5.x版本中还包含InnoDB数据字典、undolog等)
参数：innodb_data_file_path
系统表空间，默认的文件名叫 ibdata1。

2). File-Per-Table Tablespaces

如果开启了innodb_file_per_table开关 ，则每个表的文件表空间包含单个InnoDB表的数据和索引 ，并存储在文件系统上的单个数据文件中。

开关参数：innodb_file_per_table ，该参数默认开启。

test 数据库下的表空间文件：

```bash
bash-4.4# cd ./test/
bash-4.4# ls -al
total 264
drwxr-x--- 2 mysql mysql   4096 Sep 24 12:14 .
drwxrwxrwt 8 mysql mysql   4096 Sep 25 03:27 ..
-rw-r----- 1 mysql mysql 114688 Sep 24 11:58 course.ibd
-rw-r----- 1 mysql mysql 147456 Sep 24 13:13 stu.ibd
```
3). General Tablespaces

通用表空间，需要通过 CREATE TABLESPACE 语法创建通用表空间，在创建表时，可以指定该表空间。
A. 创建表空间
`CREATE TABLESPACE ts_name ADD DATAFILE 'file_name' ENGINE = engine_name;`
B. 创建表时指定表空间
`CREATE TABLE xxx ... TABLESPACE ts_name`

示例：
```sql
mysql> CREATE TABLESPACE ts_test ADD DATAFILE 'my_ts_test.ibd' ENGINE = innodb;
Query OK, 0 rows affected (0.08 sec)

mysql> use test
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A

Database changed
mysql> CREATE TABLE test_tb(id int,name varchar(10)) ENGINE = innodb TABLESPACE ts_test;
Query OK, 0 rows affected (0.05 sec)

```

4). Undo Tablespaces

> 撤销表空间，MySQL实例在初始化时会自动创建两个默认的undo表空间（初始大小16M），用于存储undo log日志。

5). Temporary Tablespaces

InnoDB 使用会话临时表空间和全局临时表空间。存储用户创建的临时表等数据。

6). Doublewrite Buffer Files

双写缓冲区，innoDB引擎将数据页从Buffer Pool刷新到磁盘前，先将数据页写入双写缓冲区文件中，便于系统异常时恢复数据。

```
ib_16384_0.dblwr
ib_16384_1.dblwr
```

7). Redo Log

重做日志，是用来实现事务的持久性。该日志文件由两部分组成：重做日志缓冲（redo log buffer）以及重做日志文件（redo log）,前者是在内存中，后者在磁盘中。当事务提交之后会把所有修改信息都会存到该日志中, 用于在刷新脏页到磁盘时,发生错误时, 进行数据恢复使用。以循环方式写入重做日志文件，涉及两个文件：

```
ib_logfile0
ib_logfile1
```

前面介绍了InnoDB的内存结构，以及磁盘结构，那么内存中所更新的数据，又是如何到磁盘中的呢？ ———— 此时，就涉及到一组后台线程，接下来，就来介绍一些InnoDB中涉及到的后台线程。

![](/_images/database/mysql/advance/后台处理线程.png)

## 后台线程

![](/_images/database/mysql/advance/后台线程.png)

在InnoDB的后台线程中，分为4类，分别是：Master Thread 、IO Thread、Purge Thread、Page Cleaner Thread。

1). Master Thread

核心后台线程，负责调度其他线程，还负责将缓冲池中的数据异步刷新到磁盘中, 保持数据的一致性，还包括脏页的刷新、合并插入缓存、undo页的回收 。

2). IO Thread

在InnoDB存储引擎中大量使用了AIO(异步IO请求)来处理IO请求, 这样可以极大地提高数据库的性能，而IOThread主要负责这些IO请求的回调。

| 线程类型                           | 默认个数   | 职责                                     |
| ----------------------------- | ---------- | ---------------------------------------- |
| Read thread                     | 4     | 负责读操作                                 |
| Write thread                    | 4     | 负责写操作                                 |
| Log thread                   | 1     | 负责将日志缓冲区刷新到磁盘                  |
| Insert buffer thread                | 1 |     负责将写缓冲区内容刷新到磁盘           |


通过以下的这条指令，查看到InnoDB的状态信息，其中就包含IO Thread信息。

```sql
mysql> show engine innodb status \G;
....
--------
FILE I/O
--------
I/O thread 0 state: waiting for completed aio requests (insert buffer thread)
I/O thread 1 state: waiting for completed aio requests (log thread)
I/O thread 2 state: waiting for completed aio requests (read thread)
I/O thread 3 state: waiting for completed aio requests (read thread)
I/O thread 4 state: waiting for completed aio requests (read thread)
I/O thread 5 state: waiting for completed aio requests (read thread)
I/O thread 6 state: waiting for completed aio requests (write thread)
I/O thread 7 state: waiting for completed aio requests (write thread)
I/O thread 8 state: waiting for completed aio requests (write thread)
I/O thread 9 state: waiting for completed aio requests (write thread)
Pending normal aio reads: [0, 0, 0, 0] , aio writes: [0, 0, 0, 0] ,   ## 0表示未在工作态
```

3). Purge Thread

主要用于回收事务已经提交了的undo log，在事务提交之后，undo log可能不用了，就用它来回收。

4). Page Cleaner Thread

协助 Master Thread 刷新脏页到磁盘的线程，它可以减轻 Master Thread 的工作压力，减少阻塞。

# 事务原理

## 事务基础

> 事务 是一组操作的集合，它是一个不可分割的工作单位，事务会把所有的操作作为一个整体一起向系统提交或撤销操作请求，即这些操作要么同时成功，要么同时失败。

**特性**

* 原子性（Atomicity）：事务是不可分割的最小操作单元，要么全部成功，要么全部失败。
* 一致性（Consistency）：事务完成时，必须使所有的数据都保持一致状态。
* 隔离性（Isolation）：数据库系统提供的隔离机制，保证事务在不受外部并发操作影响的独立环境下运行。
* 持久性（Durability）：事务一旦提交或回滚，它对数据库中的数据的改变就是永久的。

那实际上，研究事务的原理，就是研究MySQL的InnoDB引擎是如何保证事务的这四大特性的。

而对于这四大特性，实际上分为两个部分。 

![](/_images/database/mysql/advance/事务原理.png)

其中的原子性、一致性、持久化，实际上是由InnoDB中的两份日志来保证的，一份是redo log日志，一份是undo log日志。 

而持久性是通过数据库的锁，加上MVCC来保证的。

在讲解事务原理的时候，主要就是来研究一下redolog，undolog以及MVCC。

## redo log

重做日志，记录的是事务提交时数据页的物理修改，是用来实现事务的持久性。

该日志文件由两部分组成：重做日志缓冲（redo log buffer）以及重做日志文件（redo log file）,前者是在内存中，后者在磁盘中。当事务提交之后会把所有修改信息都存到该日志文件中, 用于在刷新脏页到磁盘, 发生错误时, 进行数据恢复使用。

如果没有redolog，可能会存在什么问题的？ 

在InnoDB引擎中的内存结构中，主要的内存区域就是缓冲池，在缓冲池中缓存了很多的数据页。 当在一个事务中，执行多个增删改的操作时，InnoDB引擎会先操作缓冲池中的数据，如果缓冲区没有对应的数据，会通过后台线程将磁盘中的数据加载出来，存放在缓冲区中，然后将缓冲池中的数据修改，修改后的数据页我们称为脏页。 而脏页则会在一定的时机，通过后台线程刷新到磁盘中，从而保证缓冲区与磁盘的数据一致。 而缓冲区的脏页数据并不是实时刷新的，而是一段时间之后将缓冲区的数据刷新到磁盘中，假如刷新到磁盘的过程出错了，而提示给用户事务提交成功，而数据却没有持久化下来，这就出现问题了，没有保证事务的持久性。

![](/_images/database/mysql/advance/redo_log_1.png)

那么，如何解决上述的问题呢？ 在InnoDB中提供了一份日志 redo log，接下来我们再来分析一下，通过redolog如何解决这个问题。

![](/_images/database/mysql/advance/redo_log_2.png)

有了redolog之后，当对缓冲区的数据进行增删改之后，会首先将操作的数据页的变化，记录在redo log buffer中。在事务提交时，会将redo log buffer中的数据刷新到redo log磁盘文件中。过一段时间之后，如果刷新缓冲区的脏页到磁盘时，发生错误，此时就可以借助于redo log进行数据恢复，这样就保证了事务的持久性。 而如果脏页成功刷新到磁盘 或 或者涉及到的数据已经落盘，此时redolog就没有作用了，就可以删除了，所以存在的两个redolog文件是循环写的。

那为什么每一次提交事务，要刷新redo log 到磁盘中呢，而不是直接将buffer pool中的脏页刷新到磁盘呢 ?

因为在业务操作中，我们操作数据一般都是随机读写磁盘的，而不是顺序读写磁盘。 而redo log在往磁盘文件中写入数据，**由于是日志文件，所以都是顺序写的。顺序写的效率，要远大于随机写**。 这种先写日志的方式，称之为 WAL（Write-Ahead Logging）。

## undo log

> 回滚日志，用于记录数据被修改前的信息, 作用包含两个: 提供回滚(保证事务的原子性) 和MVCC(多版本并发控制) 。

undo log和redo log记录物理日志不一样，它是逻辑日志。可以认为当delete一条记录时，undo log中会记录一条对应的insert记录，反之亦然，当update一条记录时，它记录一条对应相反的update记录。当执行rollback时，就可以从undo log中的逻辑记录读取到相应的内容并进行回滚。

undo log销毁：undo log在事务执行时产生，事务提交时，并不会立即删除undo log，因为这些日志可能还用于MVCC。

undo log存储：undo log采用段的方式进行管理和记录，存放在前面介绍的 rollback segment回滚段中，内部包含1024个undo log segment。

# MVCC

## 基本概念

**当前读**

读取的是记录的最新版本，读取时还要保证其他并发事务不能修改当前记录，会对读取的记录进行加锁。对于我们日常的操作，如：select ... lock in share mode(共享锁)，select ...for update、update、insert、delete(排他锁)都是一种当前读。

测试：在测试中我们可以看到，即使是在默认的RR隔离级别下，事务A中依然可以读取到事务B最新提交的内容，因为在查询语句后面加上了 lock in share mode 共享锁，此时是当前读操作。当然，当我们加排他锁的时候，也是当前读操作。

![](/_images/database/mysql/advance/当时读.png)

**快照读**

简单的select（不加锁）就是快照读，快照读，**读取的是记录数据的可见版本，有可能是历史数据，不加锁，是非阻塞读**。

* Read Committed：每次select，都生成一个快照读。
* Repeatable Read：开启事务后第一个select语句才是快照读的地方。
* Serializable：快照读会退化为当前读。

测试:

![](/_images/database/mysql/advance/快照读.png)

在测试中,我们看到即使事务B提交了数据,事务A中也查询不到。 原因就是因为普通的select是快照读，而在当前默认的RR隔离级别下，开启事务后第一个select语句才是快照读的地方，后面执行相同的select语句都是从快照中获取数据，可能不是当前的最新数据，这样也就保证了可重复读。

**MVCC**

全称 Multi-Version Concurrency Control，多版本并发控制。指维护一个数据的多个版本，使得读写操作没有冲突，快照读为MySQL实现MVCC提供了一个非阻塞读功能。MVCC的具体实现，还需要依赖于数据库记录中的三个隐式字段、undo log日志、readView。

## 隐藏字段 

### 介绍

![](/_images/database/mysql/advance/隐藏字段示例.png)

当我们创建了上面的这张表，我们在查看表结构的时候，就可以显式的看到这三个字段。 实际上除了这三个字段以外，InnoDB还会自动的给我们添加三个隐藏字段及其含义分别是：

| 隐藏字段 | 含义 | 
| --------------------- | ----------- | 
| DB_TRX_ID           | 最近修改事务ID，记录插入这条记录或最后一次修改该记录的事务ID。        | 
| DB_ROLL_PTR           | 回滚指针，指向这条记录的上一个版本，用于配合undo log，指向上一个版本。        | 
| DB_ROW_ID           | 隐藏主键，如果表结构没有指定主键，将会生成该隐藏字段。        | 

而上述的前两个字段是肯定会添加的， 是否添加最后一个字段DB_ROW_ID，得看当前表有没有主键，如果有主键，则不会添加该隐藏字段。

### 测试

1. 查看有主键的表 stu进入服务器中的 /var/lib/mysql/itcast/ , 查看stu的表结构信息, 通过如下指令:
`ibd2sdi stu.ibd`

查看到的表结构信息中，有一栏 columns，在其中我们会看到处理我们建表时指定的字段以外，还有额外的两个字段 分别是：DB_TRX_ID 、 DB_ROLL_PTR ，因为该表有主键，所以没有DB_ROW_ID隐藏字段。

2. 查看没有主键的表 employee

建表语句：
`create table employee (id int , name varchar(10))`

此时，我们再通过以下指令来查看表结构及其其中的字段信息：
`ibd2sdi employee.ibd`

查看到的表结构信息中，有一栏 columns，在其中我们会看到处理我们建表时指定的字段以外，还有额外的三个字段 分别是：DB_TRX_ID 、 DB_ROLL_PTR 、DB_ROW_ID，因为employee表是没有指定主键的。


## undolog

回滚日志，在insert、update、delete的时候产生的便于数据回滚的日志。当insert的时候，产生的undo log日志只在回滚时需要，在事务提交后，可被立即删除。而update、delete的时候，产生的undo log日志不仅在回滚时需要，在快照读时也需要，不会立即被删除。

### 版本链

有一张表原始数据为：

![](/_images/database/mysql/advance/版本链.png)

* DB_TRX_ID : 代表最近修改事务ID，记录插入这条记录或最后一次修改该记录的事务ID，是自增的。
* DB_ROLL_PTR ： 由于这条数据是才插入的，没有被更新过，所以该字段值为null。

然后，有四个并发事务同时在访问这张表。

A. 第一步

![](/_images/database/mysql/advance/版本链_1.png)

当事务2执行第一条修改语句时，会记录undo log日志，记录数据变更之前的样子; 然后更新记录，并且记录本次操作的事务ID，回滚指针，回滚指针用来指定如果发生回滚，回滚到哪一个版本。

![](/_images/database/mysql/advance/回滚指针_1.png)

B.第二步

![](/_images/database/mysql/advance/版本链_2.png)

当事务3执行第一条修改语句时，也会记录undo log日志，记录数据变更之前的样子; 然后更新记录，并且记录本次操作的事务ID，回滚指针，回滚指针用来指定如果发生回滚，回滚到哪一个版本。

![](/_images/database/mysql/advance/回滚指针_2.png)

C. 第三步

![](/_images/database/mysql/advance/版本链_3.png)

当事务4执行第一条修改语句时，也会记录undo log日志，记录数据变更之前的样子; 然后更新记录，并且记录本次操作的事务ID，回滚指针，回滚指针用来指定如果发生回滚，回滚到哪一个版本。

![](/_images/database/mysql/advance/回滚指针_3.png)

最终我们发现，不同事务或相同事务对同一条记录进行修改，会导致该记录的undolog生成一条记录版本链表，链表的头部是最新的旧记录，链表尾部是最早的旧记录。

### readview

ReadView（读视图）是 快照读 SQL执行时MVCC提取数据的依据，记录并维护系统当前活跃的事务（未提交的）id。

ReadView中包含了四个核心字段：

| 隐藏字段 | 含义 | 
| --------------------- | ----------- | 
| m_ids | 当前活跃的事务ID集合 | 
| min_trx_id | 最小活跃事务ID | 
| max_trx_id | 预分配事务ID，当前最大事务ID+1（因为事务ID是自增的） | 
| creator_trx_id | ReadView创建者的事务ID | 

而在readview中就规定了版本链数据的访问规则：

* trx_id 代表当前undolog版本链对应事务ID。

| 条件 | 是否可以访问 | 说明| 
| -------- | ----- |  ----- | 
| trx_id == creator_trx_id|可以访问该版本 | 成立，说明数据是当前这个事务更改的。| 
| trx_id < min_trx_id |可以访问该版本 | 成立，说明数据已经提交了。| 
| trx_id > max_trx_id|不可以访问该版本 | 成立，说明该事务是在ReadView生成后才开启。| 
| min_trx_id <= trx_id <= max_trx_id|如果trx_id不在m_ids中，是可以访问该版本的 | 成立，说明数据已经提交。| 

不同的隔离级别，生成ReadView的时机不同：

* READ COMMITTED ：在事务中每一次执行快照读时生成ReadView。
* REPEATABLE READ：仅在事务中第一次执行快照读时生成ReadView，后续复用该ReadView。

## 原理分析

###  RC隔离级别

RC隔离级别下，在事务中每一次执行快照读时生成ReadView。我们就来分析事务5中，两次快照读读取数据，是如何获取数据的?

在事务5中，查询了两次id为30的记录，由于隔离级别为Read Committed，所以每一次进行快照读都会生成一个ReadView，那么两次生成的ReadView如下。

![](/_images/database/mysql/advance/RC_1.png)

那么这两次快照读在获取数据时，就需要根据所生成的ReadView以及ReadView的版本链访问规则，到undolog版本链中匹配数据，最终决定此次快照读返回的数据。

A. 先来看第一次快照读具体的读取过程：

![](/_images/database/mysql/advance/RC_2.png)

在进行匹配时，会从undo log的版本链，从上到下进行挨个匹配：

1. 先匹配 DB_ROLL_PTR=0x00003 这条记录，这条记录对应的trx_id为4，也就是将4带入右侧的匹配规则中。 ①不满足 ②不满足 ③不满足 ④也不满足 ，都不满足，则继续匹配undo log版本链的下一条。

2. 再匹配第二条 ，这条 DB_ROLL_PTR=0x00002 记录对应的trx_id为3，也就是将3带入右侧的匹配规则中。①不满足 ②不满足 ③不满足 ④也
不满足 ，都不满足，则继续匹配undo log版本链的下一条。

3. 再匹配第三条 ，这条记录 DB_ROLL_PTR=0x00001 对应的trx_id为2，也就是将2带入右侧的匹配规则中。①不满足 ②满足 终止匹配，此次快照
读，返回的数据就是版本链中记录的这条数据。

B. 再来看第二次快照读具体的读取过程:

![](/_images/database/mysql/advance/RC_3.png)

在进行匹配时，会从undo log的版本链，从上到下进行挨个匹配：

1. 先匹配 这条记录，这条记录 DB_ROLL_PTR=0x00003 对应的trx_id为4，也就是将4带入右侧的匹配规则中。 ①不满足 ②不满足 ③不满足 ④也不满足 ，都不满足，则继续匹配undo log版本链的下一条。

2. 再匹配第二条 ，这条记录 DB_ROLL_PTR=0x00002 对应的trx_id为3，也就是将3带入右侧的匹配规则中。①不满足 ②满足 。终止匹配，此次
快照读，返回的数据就是版本链中记录的这条数据。

### RR隔离级别

RR隔离级别下，仅在事务中第一次执行快照读时生成ReadView，后续复用该ReadView。 而RR 是可重复读，在一个事务中，执行两次相同的select语句，查询到的结果是一样的。

那MySQL是如何做到可重复读的呢? 我们简单分析一下就知道了

![](/_images/database/mysql/advance/RR_1.png)

我们看到，在RR隔离级别下，只是在事务中第一次快照读时生成ReadView，后续都是复用该ReadView，那么既然ReadView都一样， ReadView的版本链匹配规则也一样， 那么最终快照读返回的结果也是一样的。

所以呢，MVCC的实现原理就是通过 InnoDB表的隐藏字段、UndoLog 版本链、ReadView来实现的。而MVCC + 锁，则实现了事务的隔离性。 而一致性则是由redolog 与 undolog保证。

![](/_images/database/mysql/advance/MVCC实现原理.png)