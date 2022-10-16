# MySQL基础 - 视图

[[toc]]

# 视图

## 介绍

视图（View）是一种虚拟存在的表。视图中的数据并不在数据库中实际存在，行和列数据来自定义视图的查询中使用的表，并且是在使用视图时动态生成的。

通俗的讲，**视图只保存了查询的SQL逻辑，不保存查询结果**。所以我们在创建视图的时候，主要的工作就落在创建这条SQL查询语句上。

## 语法

1). 创建
`CREATE [OR REPLACE] VIEW 视图名称[(列名列表)] AS SELECT语句 [ WITH [CASCADED | LOCAL ] CHECK OPTION ]`

2). 查询

`查看创建视图语句：SHOW CREATE VIEW 视图名称;`
`查看视图数据：SELECT * FROM 视图名称 ...... ;`

3). 修改

```
方式一：CREATE [OR REPLACE] VIEW 视图名称[(列名列表)] AS SELECT语句 [ WITH [ CASCADED | LOCAL ] CHECK OPTION ]
方式二：ALTER VIEW 视图名称[(列名列表)] AS SELECT语句 [ WITH [ CASCADED | LOCAL ] CHECK OPTION ]
```

4). 删除
`DROP VIEW [IF EXISTS] 视图名称 [,视图名称] ...`

演示示例：

<<< @/md/database/mysql/basic/src/view_1.sql

上述我们演示了，视图应该如何创建、查询、修改、删除，那么我们能不能通过视图来插入、更新数据呢？ 接下来，做一个测试。

```sql
insert into stu_v_1 values(6,'Tom');
insert into stu_v_1 values(17,'Tom22');
```

执行上述的SQL，我们会发现，id为6和17的数据都是可以成功插入的。 但是我们执行查询，查询出来的数据，却没有id为17的记录。

![](/_images/database/mysql/basic/view_1.png)

因为我们在创建视图的时候，指定的条件为 id<=10, id为17的数据，是不符合条件的，所以没有查询出来，但是这条数据确实是已经成功的插入到了基表中。

如果我们定义视图时，如果指定了条件，然后我们在插入、修改、删除数据时，是否可以做到必须满足条件才能操作，否则不能够操作呢？ 答案是可以的，这就需要借助于视图的检查选项了。

## 检查选项

当使用WITH CHECK OPTION子句创建视图时，MySQL会通过视图检查正在更改的每个行，例如 插入，更新，删除，以使其符合视图的定义。 MySQL允许基于另一个视图创建视图，它还会检查依赖视图中的规则以保持一致性。为了确定检查的范围，mysql提供了两个选项： CASCADED 和 LOCAL
，默认值为 CASCADED 。
 
1). CASCADED

级联。

比如，v2视图是基于v1视图的，如果在v2视图创建的时候指定了检查选项为 cascaded，但是v1视图创建时未指定检查选项。 则在执行检查时，不仅会检查v2，还会级联检查v2的关联视图v1。

![](/_images/database/mysql/basic/检查选项_cascaded.png)

2). LOCAL

本地。

比如，v2视图是基于v1视图的，如果在v2视图创建的时候指定了检查选项为 local ，但是v1视图创建时未指定检查选项。 则在执行检查时，知会检查v2，不会检查v2的关联视图v1。

![](/_images/database/mysql/basic/检查选项_local.png)

## 视图的更新

要使视图可更新，视图中的行与基础表中的行之间必须存在一对一的关系。如果视图包含以下任何一项，则该视图不可更新：

A. 聚合函数或窗口函数（SUM()、 MIN()、 MAX()、 COUNT()等）
B. DISTINCT
C. GROUP BY
D. HAVING
E. UNION 或者 UNION ALL

示例演示:

```sql
create view stu_v_count as select count(*) from student;

-- 上述的视图中，就只有一个单行单列的数据，如果我们对这个视图进行更新或插入的，将会报错。
insert into stu_v_count values(10);

-- 报错
[SQL]insert into stu_v_count values(10);
[Err] 1471 - The target table stu_v_count of the INSERT is not insertable-into
```

##  视图作用

视图是在原有表或者视图的基础上重新定义的虚拟表，这可以从原有的表上选取对用户有用的信息，忽略次要信息，其作用类似于筛选。

1. 使操作简单化
    * 视图需要达到的目的就是所见即所需。视图不仅可以简化用户对数据的理解，也可以简化他们的操作。那些被经常使用的查询可以被定义为视图，从而使得用户不必为以后的操作每次指定全部的条件。
2. 增加数据的安全性
    * 通过视图，用户只能查询和修改指定的数据。指定数据之外的信息，用户根本接触不到。这样可以防止敏感信息被未授权的用户查看，增强机密信息的安全性。
3. 提高表的逻辑独立性
    * 视图可以屏蔽原有表结构变化带来的影响。例如原有表增加列和删除未被引用的列，对视图不会造成影响。同样，如果修改表中的某些列，可以使用修改视图来解决这些列带来的影响。

案例：

1). 为了保证数据库表的安全性，开发人员在操作tb_user表时，只能看到的用户的基本字段，屏蔽手机号和邮箱两个字段。
`create view tb_user_view as select id,name,profession,age,gender,status,createtime from tb_user;`

![](/_images/database/mysql/basic/tb_user_view.png)

2). 查询每个学生所选修的课程（三张表联查），这个功能在很多的业务中都有使用到，为了简化操作，定义一个视图。
`create view tb_stu_course_view as select s.name student_name , s.no student_no , c.name course_name from student s,student_course sc , course c where s.id = sc.studentid and sc.courseid = c.id;`

![](/_images/database/mysql/basic/tb_stu_course_view.png)