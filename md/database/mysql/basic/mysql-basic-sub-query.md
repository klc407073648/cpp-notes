# MySQL - 数据库子查询

[[toc]]


# 子查询的介绍

> 在一个 select 语句中,嵌入了另外一个 select 语句, 那么**被嵌入的 select 语句称之为子查询语句**，外部那个select语句则称为主查询。

主查询和子查询的关系:

1. 子查询是嵌入到主查询中
2. 子查询是辅助主查询的,要么充当条件,要么充当数据源
3. 子查询是可以独立存在的语句,是一条完整的 select 语句

## 子查询的使用

例1. 查询大于平均年龄的学生:

```sql
mysql> select * from student where age > (select avg(age) from student);
+------+-------+-----+-----+-------+
| id   | name  | age | sex | class |
+------+-------+-----+-----+-------+
| 1003 | Steve |  27 | man |     5 |
| 1005 | Bob   |  26 | man |     3 |
| 1006 | John  |  28 | man |     7 |
+------+-------+-----+-----+-------+
3 rows in set
```

例2. 查询学生在班的所有班级名字:

```sql
mysql> select cname from course where cid in (select class from student where class is not null);
+---------+
| cname   |
+---------+
| Math    |
| Art     |
| Physics |
| Biology |
+---------+
4 rows in set
```

例3. 查找年龄最大,学号最大的学生:

```sql
mysql> select * from student where (age, id) =  (select max(age), max(id) from student);
Empty set
```

可能不存在，因为不同时满足两个条件

## 小结

子查询是一个完整的SQL语句，子查询被嵌入到一对小括号里面
​