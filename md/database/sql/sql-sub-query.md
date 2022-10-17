
# SQL语言 - 子查询

> SQL语句中嵌套SELECT语句，称谓嵌套查询，又称子查询。

[[toc]]

## 概述

语法：
`SELECT * FROM t1 WHERE column1 = ( SELECT column1 FROM t2);`
**子查询外部的语句可以是 INSERT / UPDATE / DELETE / SELECT 的任何一个**

根据子查询结果可以分为：

- 标量子查询（子查询结果为单个值）
- 列子查询（子查询结果为一列）
- 行子查询（子查询结果为一行）
- 表子查询（子查询结果为多行多列）

根据子查询位置可分为：

- WHERE 之后
- FROM 之后
- SELECT 之后

## 标量子查询

子查询返回的结果是单个值（数字、字符串、日期等）。
常用操作符：- < > > >= < <=

例子：

```mysql
-- 查询 "销售部" 所有员工信息
select id from dept where name = '销售部';
-- 根据销售部部门ID，查询员工信息
select * from emp where dept_id = 4;
-- 合并（子查询）
select * from emp where dept_id = (select id from dept where name = '销售部');

-- 查询在 "方东白" 入职之后的员工信息
select entrydate from emp where name = '方东白';
-- 根据入职日期查询之后入职的员工信息
select * from emp where entrydate > '2009-02-12';
-- 合并（子查询）
select * from emp where entrydate > (select entrydate from emp where name = '方东白');
```

查询结果:

<<< @/md/database/sql/sub_query/标量子查询.sql

## 列子查询

子查询返回的结果是一列（可以是多行），这种子查询称为列子查询。

常用操作符：

| 操作符  | 描述  |
| ------------ | ------------ |
| IN  | 在指定的集合范围内，多选一  |
| NOT IN  | 不在指定的集合范围内  |
| ANY  | 子查询返回列表中，有任意一个满足即可  |
| SOME  | 与ANY等同，使用SOME的地方都可以使用ANY  |
| ALL  | 子查询返回列表的所有值都必须满足  |

例子：

```mysql
-- 查询销售部和市场部的所有员工信息
select * from emp where dept_id in (select id from dept where name = '销售部' or name = '市场部');
-- 查询比财务部所有人工资都高的员工信息
select * from emp where salary > all ( select salary from emp where dept_id = (select id from dept where name = '财务部'));
-- 查询比研发部任意一人工资高的员工信息
select * from emp where salary > any ( select salary from emp where dept_id = (select id from dept where name = '研发部') );
```

查询结果:

<<< @/md/database/sql/sub_query/列子查询.sql

## 行子查询

> 子查询返回的结果是一行（可以是多列），这种子查询称为行子查询。

常用操作符：=, <, >, IN, NOT IN

例子：

```mysql
-- 查询与 "张无忌" 的薪资及直属领导相同的员工信息 ;
select * from emp where (salary,managerid) = (select salary, managerid from emp where name = '张无忌');
```

查询结果:

<<< @/md/database/sql/sub_query/行子查询.sql

## 表子查询

返回的结果是多行多列
常用操作符：IN

例子：

```mysql
-- 查询与 "鹿杖客" , "宋远桥" 的职位和薪资相同的员工信息
select * from emp where (job,salary) in ( select job, salary from emp where name = '鹿杖客' or name = '宋远桥' );
-- 查询入职日期是 "2006-01-01" 之后的员工信息 , 及其部门信息
select e.*, d.* from (select * from emp where entrydate > '2006-01-01') e left join dept d on e.dept_id = d.id ;
```

查询结果:

<<< @/md/database/sql/sub_query/表子查询.sql