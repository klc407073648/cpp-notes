# MySQL - 数据库连接查询

[[toc]]

# 连接查询的介绍

> 连接查询可以实现多个表的查询，当查询的字段数据来自不同的表就可以使用连接查询来完成。

连接查询可以分为:

1. 内连接查询
2. 左连接查询
3. 右连接查询
4. 自连接查询

## 内连接查询

> 查询两个表中符合条件的共有记录

内连接查询效果图:

![内连接查询](/_images/database/mysql/内连接查询.png)

内连接查询语法格式:

```sql
select 字段 from 表1 inner join 表2 on 表1.字段1 = 表2.字段2
```

说明:

* inner join 就是内连接查询关键字
* on 就是连接查询条件

例：使用内连接查询学生表与班级表

```sql
mysql> select * from student as s inner join course as c on s.class = c.cid;
+------+-------+-----+-------+-------+-----+---------+
| id   | name  | age | sex   | class | cid | cname   |
+------+-------+-----+-------+-------+-----+---------+
| 1001 | Jason |  25 | man   |     1 |   1 | Math    |
| 1002 | Helen |  25 | woman |     3 |   3 | Art     |
| 1003 | Steve |  27 | man   |     5 |   5 | Physics |
| 1004 | Hanna |  25 | woman |     1 |   1 | Math    |
| 1005 | Bob   |  26 | man   |     3 |   3 | Art     |
| 1006 | John  |  28 | man   |     7 |   7 | Biology |
+------+-------+-----+-------+-------+-----+---------+
6 rows in set
```

## 左连接查询

> 以左表为主根据条件查询右表数据，如果根据条件查询右表数据不存在使用null值填充。

左连接查询效果图:

![左连接查询](/_images/database/mysql/左连接查询.png)

左连接查询语法格式:

```sql
select 字段 from 表1 left join 表2 on 表1.字段1 = 表2.字段2
```

说明:

* left join 就是左连接查询关键字
* on 就是连接查询条件
* 表1 是左表
* 表2 是右表

例：使用左连接查询学生表与班级表

```sql
mysql> select * from student as s left join course as c on s.class = c.cid;
+------+-------+-----+-------+-------+------+---------+
| id   | name  | age | sex   | class | cid  | cname   |
+------+-------+-----+-------+-------+------+---------+
| 1001 | Jason |  25 | man   |     1 |    1 | Math    |
| 1002 | Helen |  25 | woman |     3 |    3 | Art     |
| 1003 | Steve |  27 | man   |     5 |    5 | Physics |
| 1004 | Hanna |  25 | woman |     1 |    1 | Math    |
| 1005 | Bob   |  26 | man   |     3 |    3 | Art     |
| 1006 | John  |  28 | man   |     7 |    7 | Biology |
| 1007 | Walln |  25 | woman |     8 | NULL | NULL    |
+------+-------+-----+-------+-------+------+---------+
7 rows in set
```

## 右连接查询

> 以右表为主根据条件查询左表数据，如果根据条件查询左表数据不存在使用null值填充

右连接查询效果图:

![右连接查询](/_images/database/mysql/右连接查询.png)

右连接查询语法格式:

```sql
select 字段 from 表1 right join 表2 on 表1.字段1 = 表2.字段2
```

说明:

* right join 就是右连接查询关键字
* on 就是连接查询条件
* 表1 是左表
* 表2 是右表

例：使用右连接查询学生表与班级表

```sql
mysql> select * from student as s right join course as c on s.class = c.cid;
+------+-------+------+-------+-------+-----+-----------+
| id   | name  | age  | sex   | class | cid | cname     |
+------+-------+------+-------+-------+-----+-----------+
| 1001 | Jason |   25 | man   |     1 |   1 | Math      |
| 1002 | Helen |   25 | woman |     3 |   3 | Art       |
| 1003 | Steve |   27 | man   |     5 |   5 | Physics   |
| 1004 | Hanna |   25 | woman |     1 |   1 | Math      |
| 1005 | Bob   |   26 | man   |     3 |   3 | Art       |
| 1006 | John  |   28 | man   |     7 |   7 | Biology   |
| NULL | NULL  | NULL | NULL  | NULL  |   2 | English   |
| NULL | NULL  | NULL | NULL  | NULL  |   4 | Music     |
| NULL | NULL  | NULL | NULL  | NULL  |   6 | Chemistry |
+------+-------+------+-------+-------+-----+-----------+
9 rows in set
```

## 自连接查询

> 左表和右表是同一个表，根据连接查询条件查询两个表中的数据。

区域表效果图

![区域表效果图](/_images/database/mysql/区域表效果图.png)

创建areas表:

```sql
create table areas(
    aid varchar(30) not null primary key, 
    title varchar(30), 
    pid varchar(30)
);
```

自连接查询的用法:

```sql
mysql> select city.* from areas as city inner join areas as province on city.pid = province.aid;
+-----+--------+-----+
| aid | title  | pid |
+-----+--------+-----+
| 3   | 杭州市 | 1   |
| 4   | 温州市 | 1   |
| 5   | 南京市 | 2   |
| 6   | 苏州市 | 2   |
+-----+--------+-----+
4 rows in set
```
​