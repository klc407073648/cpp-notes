# SQL语言 - 使用技巧

> 别名、去重、条件查询、排序、分页查询和分组查询

[[toc]]

# 概述

本章主要介绍以下几类内容：

* as(别名)
* distinct(去重)
* 排序(asc,desc)
* where条件查询
* 分页查询
* 分组查询
​
# as关键字

> 在使用SQL语句显示结果的时候，往往在屏幕显示的字段名并不具备良好的可读性，此时可以使用 as 给字段起一个别名。

**使用 as 给字段起别名**

```sql
mysql> select id as 序号, name as 名字 from teacher;
+------+-------+
| 序号 | 名字  |
+------+-------+
|    1 | Helen |
|    2 | Jason |
+------+-------+
2 rows in set
```

**可以通过 as 给表起别名**

```sql
-- 如果是单表查询 可以省略表名
select id, name from student;

-- 表名.字段名
select students.id,students.name from student;

-- 可以通过 as 给表起别名 
select s.id,s.name from student as s;


mysql> select s.id,s.name from student as s;
+----+-------+
| id | name  |
+----+-------+
|  1 | Jason |
|  4 | Steve |
+----+-------+
2 rows in set
```

说明: 在这里给表起别名看起来并没有什么意义,然而并不是这样的。在后期学习**自连接**的时候，必须要对表起别名。

# distinct关键字

> distinct可以去除重复数据行。

```sql
select distinct 列1,... from 表名;

例： 查询班级中学生的性别
select name, id from student;

-- 看到了很多重复数据 想要对其中重复数据行进行去重操作可以使用 distinct
select distinct name, id from student;


mysql> select name,sex from student;
+-------+-----+
| name  | sex |
+-------+-----+
| Jason | 男  |
| Steve | 男  |
| Jason | 男  |
| Steve | 男  |
+-------+-----+
4 rows in set

mysql> select distinct name,sex from student;
+-------+-----+
| name  | sex |
+-------+-----+
| Jason | 男  |
| Steve | 男  |
+-------+-----+
2 rows in set
```

# 排序

排序查询语法：

```sql
select * from 表名 order by 列1 asc|desc [,列2 asc|desc,...]
```

语法说明:

1. 先按照列1进行排序，如果列1的值相同时，则按照 列2 排序，以此类推
2. asc从小到大排列，即升序
3. desc从大到小排序，即降序
4. 默认按照列值从小到大排列（即asc关键字）

```sql
以id降序:
mysql> select * from student order by id desc;
+------+-------+-----+-------+
| id   | name  | age | sex   |
+------+-------+-----+-------+
| 1005 | Bob   |  26 | man   |
| 1004 | Hanna |  25 | woman |
| 1003 | Steve |  27 | man   |
| 1002 | Helen |  25 | woman |
| 1001 | Jason |  25 | man   |
+------+-------+-----+-------+
5 rows in set

以age,id降序:
mysql> select * from student order by age desc,id desc;
+------+-------+-----+-------+
| id   | name  | age | sex   |
+------+-------+-----+-------+
| 1003 | Steve |  27 | man   |
| 1005 | Bob   |  26 | man   |
| 1004 | Hanna |  25 | woman |
| 1002 | Helen |  25 | woman |
| 1001 | Jason |  25 | man   |
+------+-------+-----+-------+
5 rows in set
```

# where条件查询

where语句支持的运算符:

1. 比较运算符，>,<,>=,<=,!=
2. 逻辑运算符, and,or,not
3. 模糊查询，like是模糊查询关键字，%表示任意多个任意字符，_表示一个任意字符
4. 范围查询，between .. and .. 表示在一个连续的范围内查询，in 表示在一个非连续的范围内查询
5. 空判断，判断为空使用: is null，判断非空使用: is not null

```sql
mysql> use mytestdata;
Database changed
mysql> select * from student;
+------+-------+-----+-------+
| id   | name  | age | sex   |
+------+-------+-----+-------+
| 1001 | Jason |  25 | man   |
| 1002 | Helen |  25 | woman |
| 1003 | Steve |  27 | man   |
| 1004 | Hanna |  25 | woman |
| 1005 | Bob   |  26 | man   |
+------+-------+-----+-------+
5 rows in set

mysql> select * from student where sex='man';
+------+-------+-----+-----+
| id   | name  | age | sex |
+------+-------+-----+-----+
| 1001 | Jason |  25 | man |
| 1003 | Steve |  27 | man |
| 1005 | Bob   |  26 | man |
+------+-------+-----+-----+
3 rows in set

mysql> select * from student where age between 26 and 27;
+------+-------+-----+-----+
| id   | name  | age | sex |
+------+-------+-----+-----+
| 1003 | Steve |  27 | man |
| 1005 | Bob   |  26 | man |
+------+-------+-----+-----+
2 rows in set

mysql> select * from student where id >1004;
+------+------+-----+-----+
| id   | name | age | sex |
+------+------+-----+-----+
| 1005 | Bob  |  26 | man |
+------+------+-----+-----+
1 row in set

mysql> select * from student where name like 'H%';
+------+-------+-----+-------+
| id   | name  | age | sex   |
+------+-------+-----+-------+
| 1002 | Helen |  25 | woman |
| 1004 | Hanna |  25 | woman |
+------+-------+-----+-------+
2 rows in set

mysql> select * from student where name like 'H_';
Empty set
mysql> select * from student where id >1003 and age>=26;
+------+------+-----+-----+
| id   | name | age | sex |
+------+------+-----+-----+
| 1005 | Bob  |  26 | man |
+------+------+-----+-----+
1 row in set
mysql> select * from student where id is null;
Empty set
```

# 分页查询

> 当我们在天猫购物，浏览商品列表时，由于商品数据过多，一个页面无法完全展示，需要一页一页的进行显示，这就是分页查询。

## 分页查询的语法

```sql
select * from 表名 limit start,count
```

说明:

1. limit是分页查询关键字
2. start表示开始行索引，默认是0
3. count表示查询条数

查询前3条男生信息：

```sql
mysql> select * from student where sex='man' limit 0,3; 
（或简写select * from student where sex='man' limit 3;）
+------+-------+-----+-----+
| id   | name  | age | sex |
+------+-------+-----+-----+
| 1001 | Jason |  25 | man |
| 1003 | Steve |  27 | man |
| 1005 | Bob   |  26 | man |
+------+-------+-----+-----+
3 rows in set
```

## 分页查询案例

已知每页显示m条数据，求第n页显示的数据

提示: 关键是求每页的开始行索引

查询学生表，获取第n页数据的SQL语句:

```sql
select * from student limit (n-1)*m,m
```

# 分组查询

> 分组查询就是将查询结果按照指定字段进行分组，字段中数据相等的分为一组。

分组查询基本的语法格式如下：

```
GROUP BY 列名 [HAVING 条件表达式] [WITH ROLLUP]
```

说明:

* 列名: 是指按照指定字段的值进行分组。
* HAVING 条件表达式: 用来过滤分组后的数据。
* WITH ROLLUP：在所有记录的最后加上一条记录，显示select查询时聚合函数的统计和计算结果

## group by的使用

group by可用于单个字段分组，也可用于多个字段分组。

```sql
-- 根据sex字段来分组
mysql> select sex from student group by sex;
+-------+
| sex   |
+-------+
| man   |
| woman |
+-------+
2 rows in set

-- 根据name和sex字段进行分组
mysql> select name,sex from student group by name,
sex;
+-------+-------+
| name  | sex   |
+-------+-------+
| Bob   | man   |
| Hanna | woman |
| Helen | woman |
| Jason | man   |
| John  | man   |
| Steve | man   |
+-------+-------+
6 rows in set
```

## group by + group_concat()的使用

> group_concat(字段名): 统计每个分组指定字段的信息集合，每个信息之间使用逗号进行分割。

```sql
-- 根据sex字段进行分组， 查询sex字段和分组的name字段信息
mysql> select sex,group_concat(name) from student
 group by sex;
+-------+----------------------+
| sex   | group_concat(name)   |
+-------+----------------------+
| man   | Jason,Steve,Bob,John |
| woman | Helen,Hanna          |
+-------+----------------------+
2 rows in set
```

## group by + 聚合函数的使用

```sql
-- 统计不同性别的人的平均年龄
mysql> select sex,avg(age) from student group by sex;
+-------+----------+
| sex   | avg(age) |
+-------+----------+
| man   | 26.0000  |
| woman | 25.0000  |
+-------+----------+
2 rows in set

-- 统计不同性别的人的个数
mysql> select sex,count(*) from student group by sex;
+-------+----------+
| sex   | count(*) |
+-------+----------+
| man   |        4 |
| woman |        2 |
+-------+----------+
2 rows in set
```

## group by + having的使用

> having作用和where类似都是过滤数据的，**但having是过滤分组数据的，只能用于group by**。

```sql
-- 根据sex字段进行分组，统计分组条数大于2的
mysql> select sex,count(*) from student group by sex having count(*)>2;
+-----+----------+
| sex | count(*) |
+-----+----------+
| man |        4 |
+-----+----------+
1 row in set
```

## group by + with rollup的使用

> with rollup的作用是：在最后记录后面新增一行，显示select查询时聚合函数的统计和计算结果。

```sql
-- 根据sex字段进行分组，汇总总人数
mysql> select sex,count(*) from student group by sex with rollup;
+-------+----------+
| sex   | count(*) |
+-------+----------+
| man   |        4 |
| woman |        2 |
| NULL  |        6 |
+-------+----------+
3 rows in set

-- 根据sex字段进行分组，汇总所有人的年龄
mysql> select sex,group_concat(age) from student group by sex with rollup;
+-------+-------------------+
| sex   | group_concat(age) |
+-------+-------------------+
| man   | 25,27,26          |
| woman | 25,25             |
| NULL  | 25,27,26,25,25    |
+-------+-------------------+
3 rows in set
```

# 小结

* as 关键字可以给表中字段 或者 表名起别名
* distinct 关键字可以去除重复数据行。
* group by 根据指定的一个或者多个字段对数据进行分组
* group_concat(字段名)函数是统计每个分组指定字段的信息集合
* 聚合函数在和 group by 结合使用时, 聚合函数统计和计算的是每个分组的数据
* having 是对分组数据进行条件过滤
* with rollup在最后记录后面新增一行，显示select查询时聚合函数的统计和计算结果
