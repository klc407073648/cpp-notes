# SQL语言 - 连接查询

[[toc]]

# 概述

连接查询包含以下几种类型：

* 连接查询
	* 内连接：相当于查询A、B交集部分数据
	* 外连接：
	* 左外连接：查询左表所有数据，以及两张表交集部分数据
	* 右外连接：查询右表所有数据，以及两张表交集部分数据
	* 自连接：当前表与自身的连接查询，自连接必须使用表别名

## 内连接查询

内连接查询的是两张表交集的部分

隐式内连接：
`SELECT 字段列表 FROM 表1, 表2 WHERE 条件 ...;`

显式内连接：
`SELECT 字段列表 FROM 表1 [ INNER ] JOIN 表2 ON 连接条件 ...;`

显式性能比隐式高

例子：

```mysql
-- 查询员工姓名，及关联的部门的名称
-- 隐式
select e.name,d.name from emp e , dept d where e.dept_id = d.id;
-- 显式
select e.name, d.name from emp e inner join dept d on e.dept_id = d.id;
```

<<< @/md/database/sql/con_query/内连接查询.sql

## 外连接查询

左外连接：
查询左表所有数据，以及两张表交集部分数据
`SELECT 字段列表 FROM 表1 LEFT [ OUTER ] JOIN 表2 ON 条件 ...;`
相当于查询表1的所有数据，包含表1和表2交集部分数据

右外连接：
查询右表所有数据，以及两张表交集部分数据
`SELECT 字段列表 FROM 表1 RIGHT [ OUTER ] JOIN 表2 ON 条件 ...;`

例子：

```mysql
-- 左
select e.*, d.name from emp as e left join dept as d on e.dept_id = d.id;
select d.name, e.* from dept d left join emp e on e.dept_id = d.id;  -- 这条语句与下面的语句效果一样,左右连接可以相互转换
-- 右
select d.name, e.* from emp as e right join dept as d on e.dept_id = d.id;
```

<<< @/md/database/sql/con_query/外连接查询.sql

左连接可以查询到没有dept的emp，右连接可以查询到没有emp的dept

## 自连接

### 自连接查询

自连接查询，顾名思义，就是自己连接自己，也就是把一张表连接查询多次。

语法：
`SELECT 字段列表 FROM 表A 别名A JOIN 表A 别名B ON 条件 ...;`

自连接查询，可以是内连接查询，也可以是外连接查询

例子：

```mysql
-- 查询员工及其所属领导的名字
select a.name , b.name from emp a , emp b where a.managerid = b.id;
-- 没有领导的也查询出来
select a.name '员工', b.name '领导' from emp a left join emp b on a.managerid =b.id;
```

<<< @/md/database/sql/con_query/自连接查询.sql

### 联合查询 union, union all

> 对于union查询，就是把多次查询的结果合并起来，形成一个新的查询结果集。

语法：

```mysql
SELECT 字段列表 FROM 表A ...
UNION [ALL]
SELECT 字段列表 FROM 表B ...
```

* 对于联合查询的多张表的列数必须保持一致，字段类型也需要保持一致。
* union all 会将全部的数据直接合并在一起，union 会对合并之后的数据去重。
* 联合查询比使用or效率高，不会使索引失效

```
-- 将薪资低于 5000 的员工 , 和 年龄大于 50 岁的员工全部查询出来.
select * from emp where salary < 5000
union all
select * from emp where age > 50;
-- union all查询出来的结果，仅仅进行简单的合并，并未去重。
select * from emp where salary < 5000
union
select * from emp where age > 50;
-- 等价于
select * from emp where salary < 5000 or age > 50;
```

<<< @/md/database/sql/con_query/联合查询.sql