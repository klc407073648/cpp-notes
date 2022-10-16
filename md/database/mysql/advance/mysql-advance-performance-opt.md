# MySQL进阶 - 性能优化

[[toc]]

# 插入数据

## insert

普通插入：

```sql
create table tb_test(
	id int comment'用户Id',
	name varchar(50) not null comment '用户名'
) COMMENT='用户测试表';

insert into tb_test values(1,'tom');
insert into tb_test values(2,'cat');
insert into tb_test values(3,'jerry');

```

如果我们需要一次性往数据库表中插入多条记录，可以从以下三个方面进行优化。

1. 采用批量插入（一次插入的数据不建议超过1000条）

`insert into tb_test values(1,'Tom'),(2,'Cat'),(3,'Jerry');`

2. 手动提交事务

```sql
start transaction;
insert into tb_test values(1,'Tom'),(2,'Cat'),(3,'Jerry');
insert into tb_test values(4,'Tom'),(5,'Cat'),(6,'Jerry');
insert into tb_test values(7,'Tom'),(8,'Cat'),(9,'Jerry');
commit;
```

3. 主键顺序插入

```
主键乱序插入 : 8 1 9 21 88 2 4 15 89 5 7 3
主键顺序插入 : 1 2 3 4 5 7 8 9 15 21 88 89
```

## 大批量插入数据

大批量插入：
如果一次性需要插入大批量数据，使用insert语句插入性能较低，此时可以使用MySQL数据库提供的load指令插入。

```mysql
# 客户端连接服务端时，加上参数 --local-infile（这一行在bash/cmd界面输入）
mysql --local-infile -u root -p
# 设置全局参数local_infile为1，开启从本地加载文件导入数据的开关
set global local_infile = 1;
select @@local_infile;
# 执行load指令将准备好的数据，加载到表结构中
load data local infile '/root/load_user_100w_sort.sql' into table tb_user fields terminated by ',' lines terminated by '\n' ;
```

# 主键优化

数据组织方式：在InnoDB存储引擎中，表数据都是根据主键顺序组织存放的，这种存储方式的表称为索引组织表（Index organized table, IOT）

![](/_images/database/mysql/advance/索引组织表.png)

行数据，都是存储在聚集索引的叶子节点上的。InnoDB的逻辑结构图：

![](/_images/database/mysql/advance/InnoDB逻辑存储结构.png)

在InnoDB引擎中，数据行是记录在逻辑结构 page 页中的，而每一个页的大小是固定的，默认16K。那也就意味着， 一个页中所存储的行也是有限的，如果插入的数据行row在该页存储不小，将会存储到下一个页中，页与页之间会通过指针连接。

## 页分裂

> 页可以为空，也可以填充一般，也可以填充100%，每个页包含了2-N行数据（如果一行数据过大，会行溢出），根据主键排列。

主键顺序插入:

![](/_images/database/mysql/advance/主键顺序插入效果.png)

主键乱序插入:

![](/_images/database/mysql/advance/主键乱序插入1.png)


![](/_images/database/mysql/advance/主键乱序插入2.png)


目前表中已有数据的索引结构(叶子节点)如下：

## 页合并

目前表中已有数据的索引结构(叶子节点)如下：

![](/_images/database/mysql/advance/页合并1.png)

当删除一行记录时，实际上记录并没有被物理删除，只是记录被标记（flaged）为删除并且它的空间变得允许被其他记录声明使用。

![](/_images/database/mysql/advance/页合并2.png)

当页中删除的记录到达 MERGE_THRESHOLD（默认为页的50%），InnoDB会开始寻找最靠近的页（前后）看看是否可以将这两个页合并以优化空间使用。

![](/_images/database/mysql/advance/页合并3.png)

> MERGE_THRESHOLD：合并页的阈值，可以自己设置，在创建表或创建索引时指定

## 索引设计原则

- 满足业务需求的情况下，尽量降低主键的长度
- 插入数据时，尽量选择顺序插入，选择使用 AUTO_INCREMENT 自增主键
- 尽量不要使用 UUID 做主键或者是其他的自然主键，如身份证号
- 业务操作时，避免对主键的修改

# order by优化

MySQL的排序，有两种方式：

1. Using filesort：通过表的索引或全表扫描，读取满足条件的数据行，然后在排序缓冲区 sort buffer 中完成排序操作，所有不是通过索引直接返回排序结果的排序都叫 FileSort 排序

2. Using index：通过有序索引顺序扫描直接返回有序数据，这种情况即为 using index，不需要额外排序，操作效率高。

对于以上的两种排序方式，Using index的性能高，而Using filesort的性能低，我们在优化排序操作时，尽量要优化为 Using index。

示例：

<<< @/md/database/mysql/advance/src/order_by.sql

注意事项：降序索引，MySQL版本可能要8.0以上

总结：

- 根据排序字段建立合适的索引，多字段排序时，也遵循最左前缀法则
- 尽量使用覆盖索引
- 多字段排序，一个升序一个降序，此时需要注意联合索引在创建时的规则（ASC/DESC）
- 如果不可避免出现filesort，大数据量排序时，可以适当增大排序缓冲区大小 sort_buffer_size（默认256k）

# group by优化

<<< @/md/database/mysql/advance/src/group_by.sql

- 在分组操作时，可以通过索引来提高效率
- 分组操作时，索引的使用也是满足最左前缀法则的

如索引为`idx_user_pro_age_stat`，则句式可以是`select ... where profession order by age`，这样也符合最左前缀法则

# limit优化

在数据量比较大时，如果进行limit分页查询，在查询时，越往后，分页查询效率越低。

一起来看看执行limit分页查询耗时对比：

<<< @/md/database/mysql/advance/src/limit.sql

通过测试发现越往后，分页查询效率越低，这就是分页查询的问题所在。

因为，当在进行分页查询时，如果执行 limit 2000000,10 ，此时需要MySQL排序前2000010 记录，仅仅返回 2000000 - 2000010 的记录，其他记录丢弃，查询排序的代价非常大 。

优化方案：一般分页查询时，通过创建覆盖索引能够比较好地提高性能，可以通过**覆盖索引加子查询形式进行优化**

例如：

<<< @/md/database/mysql/advance/src/limit_opt.sql

# count优化

在之前的测试中，我们发现，如果数据量很大，在执行count操作时，是非常耗时的。

* MyISAM 引擎把一个表的总行数存在了磁盘上，因此执行 count(*) 的时候会直接返回这个数，效率很高（前提是不适用where）；
* InnoDB 在执行 count(*) 时，需要把数据一行一行地从引擎里面读出来，然后累计计数。

要大幅度提升InnoDB表的count效率，主要的优化思路：自己计数，如创建key-value表存储在内存或硬盘，或者是用redis

**count的几种用法**

> count() 是一个聚合函数，对于返回的结果集，一行行地判断，如果 count 函数的参数不是NULL，累计值就加 1，否则不加，最后返回累计值。

用法：count（*）、count（主键）、count（字段）、count（数字）

各种用法的性能：

- count(主键)：InnoDB引擎会遍历整张表，把每行的主键id值都取出来，返回给服务层，服务层拿到主键后，直接按行进行累加（主键不可能为空）
- count(字段)：没有not null约束的话，InnoDB引擎会遍历整张表把每一行的字段值都取出来，返回给服务层，服务层判断是否为null，不为null，计数累加；有not null约束的话，InnoDB引擎会遍历整张表把每一行的字段值都取出来，返回给服务层，直接按行进行累加
- count(1)：InnoDB 引擎遍历整张表，但不取值。服务层对于返回的每一层，放一个数字 1 进去，直接按行进行累加
- count(*)：InnoDB 引擎并不会把全部字段取出来，而是专门做了优化，不取值，服务层直接按行进行累加

按效率排序：count(字段) < count(主键) < count(1) < count(*)，所以尽量使用 count(*)

# update优化（避免行锁升级为表锁）

> InnoDB 的行锁是针对索引加的锁，不是针对记录加的锁，并且该索引不能失效，否则会从行锁升级为表锁。

如以下两条语句：
`update course set name = 'javaEE' where id = 1;`，
这句由于id有主键索引，所以只会锁这一行；
`update course set name = 'SpringBoot' where name = 'PHP' ;`
这句由于name没有索引，所以会把整张表都锁住进行数据更新，解决方法是给name字段添加索引