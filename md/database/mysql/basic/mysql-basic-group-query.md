# MySQL - 聚合函数和分组查询

[[toc]]

# 聚合函数

> 聚合函数又叫组函数，通常是对表中的数据进行统计和计算，一般结合分组(group by)来使用，用于统计和计算分组数据。

常用的聚合函数:

```
count(col): 表示求指定列的总行数
max(col): 表示求指定列的最大值
min(col): 表示求指定列的最小值
sum(col): 表示求指定列的和
avg(col): 表示求指定列的平均值
```

## 求总行数

```sql
-- 返回非NULL数据的总行数.
mysql> select count(age) from student; 
+------------+
| count(age) |
+------------+
|          5 |
+------------+
1 row in set

-- 返回总行数，包含null值记录;
mysql> select count(*) from student;
+----------+
| count(*) |
+----------+
|        6 |
+----------+
1 row in set
```

## 求最大值

```sql
-- 查询男生的编号最大值
mysql> select max(id) from student where sex = 'man';
+---------+
| max(id) |
+---------+
|    1005 |
+---------+
1 row in set
```

## 求最小值

```sql
-- 查询学生最小编号
mysql> select min(id) from student;
+---------+
| min(id) |
+---------+
|    1001 |
+---------+
1 row in set
```

## 求和

```sql
-- 查询男生的总年龄
mysql> select sum(age) from student where sex = 'man';
+----------+
| sum(age) |
+----------+
| 78       |
+----------+
1 row in set

-- 平均年龄
mysql> select sum(age) / count(*) from student where sex = 'man';
+---------------------+
| sum(age) / count(*) |
+---------------------+
| 19.5000             |
+---------------------+
1 row in set
```

## 求平均值

```sql
-- 求男生的平均年龄, 聚合函数不统计null值，平均身高年龄
mysql> select avg(age) from student where sex = 'man';
+----------+
| avg(age) |
+----------+
| 26.0000  |
+----------+
1 row in set

-- 求男生的平均年龄, 包含年龄是null的
mysql> select avg(ifnull(age,20)) from student where sex = 'man';
+---------------------+
| avg(ifnull(age,20)) |
+---------------------+
| 24.5000             |
+---------------------+
1 row in set
```

说明：ifnull函数: 表示判断指定字段的值是否为null，如果为空使用自己提供的值。

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

group_concat(字段名): 统计每个分组指定字段的信息集合，每个信息之间使用逗号进行分割。

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

having作用和where类似都是过滤数据的，**但having是过滤分组数据的，只能用于group by**。

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

with rollup的作用是：在最后记录后面新增一行，显示select查询时聚合函数的统计和计算结果。

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

## 小结

* group by 根据指定的一个或者多个字段对数据进行分组
* group_concat(字段名)函数是统计每个分组指定字段的信息集合
* 聚合函数在和 group by 结合使用时, 聚合函数统计和计算的是每个分组的数据
* having 是对分组数据进行条件过滤
* with rollup在最后记录后面新增一行，显示select查询时聚合函数的统计和计算结果
​