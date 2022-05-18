# MySQL - 视图

[[toc]]

​
# 视图概述

> 视图是由数据库中的一个表或多个表导出的虚拟表，其作用是方便用户对数据的操作。

## 视图的概念

视图是一个虚拟表，其内容由查询定义。同真实的表一样，视图包含一系列带有名称的列和行数据。但是，**数据库中只存放了视图的定义，而并没有存放视图中的数据，这些数据存放在原来的表中**。使用视图查询数据时，数据库系统会从原来的表中取出对应的数据。因此，视图中的数据是依赖于原来的表中的数据的。一旦表中的数据发生改变，显示在视图中的数据也会发生改变。同样对视图的更新，会影响到原来表的数据。

视图是存储在数据库中的查询的SQL语句，它主要出于两种原因：**安全原因**，视图可以隐藏一些数据，例如，员工信息表，可以用视图只显示姓名、工龄、地址，而不显示社会保险号和工资数等；另一个原因是**可使复杂的查询易于理解和使用**。这个视图就像一个“窗口”，从中只能看到你想看的数据列。这意味着你可以在这个视图上使用SELECT *，而你看到的将是你在视图定义里给出的那些数据列。

## 视图的作用

视图是在原有表或者视图的基础上重新定义的虚拟表，这可以从原有的表上选取对用户有用的信息，忽略次要信息，其作用类似于筛选。视图的作用归纳为如下几点：

### 使操作简单化

视图需要达到的目的就是所见即所需。视图不仅可以简化用户对数据的理解，也可以简化他们的操作。那些被经常使用的查询可以被定义为视图，从而使得用户不必为以后的操作每次指定全部的条件。

### 增加数据的安全性

通过视图，用户只能查询和修改指定的数据。指定数据之外的信息，用户根本接触不到。这样可以防止敏感信息被未授权的用户查看，增强机密信息的安全性。

### 提高表的逻辑独立性

视图可以屏蔽原有表结构变化带来的影响。例如原有表增加列和删除未被引用的列，对视图不会造成影响。同样，如果修改表中的某些列，可以使用修改视图来解决这些列带来的影响。

# 视图的基本操作

## 创建视图

创建视图是指在已经存在的数据库表上建立视图。视图可以建立在一张表中，也可以建立在多张表中。

查看创建视图的权限

创建视图需要具有CREATE VIEW的权限。同时应该具有查询涉及的列的SELECT权限。可以使用SELECT语句来查询这些权限信息。查询语法如下：

```sql
SELECT Select_priv,Create_view_priv FROM mysql.user WHERE user='用户名';
```

参数说明：

1. Select_priv：属性表示用户是否具有SELECT权限，Y表示拥有SELECT权限，N表示没有。

2. Create_view_priv：属性表示用户是否具有CREATE VIEW权限；

3. mysql.user：表示MySQL数据库下面的user表。

4. 用户名：参数表示要查询是否拥有权限的用户，该参数需要用单引号引起来。

示例：查询MySQL中root用户是否具有创建视图的权限。

MySQL中，创建视图是通过CREATE VIEW语句实现的。其语法如下：

```sql
CREATE [OR REPLACE] [ALGORITHM={UNDEFINED|MERGE|TEMPTABLE}]
VIEW 视图名[(属性清单)]
AS SELECT语句
[WITH [CASCADED|LOCAL] CHECK OPTION];
```

参数说明：

1. ALGORITHM：可选项，表示视图选择的算法。

2. 视图名：表示要创建的视图名称。

3. 属性清单：可选项，指定视图中各个属性的名词，默认情况下与SELECT语句中的查询的属性相同。

4. SELECT语句：表示一个完整的查询语句，将查询记录导入视图中。

5. WITH CHECK OPTION：可选项，表示更新视图时要保证在该视图的权限范围之内。

例：创建视图。

```sql
CREATE  VIEW view_student AS SELECT id,name,class FROM student;
```

例：创建视图同时，指定属性清单。

```sql
CREATE VIEW view_student1(stu_id,stu_name,stu_class) AS SELECT id,name,class FROM student;

CREATE OR REPLACE VIEW view_student1(stu_id,stu_name,stu_class) AS SELECT id,name,class FROM student;
```

创建视图时需要注意以下几点：

1. 运行创建视图的语句需要用户具有创建视图（create view）的权限，若加了[or replace]时，还需要用户具有删除视图（drop view）的权限；

2. select语句不能包含from子句中的子查询；

3. select语句不能引用系统或用户变量；

4. select语句不能引用预处理语句参数；

5. 在存储子程序内，定义不能引用子程序参数或局部变量；

6. 在定义中引用的表或视图必须存在。但是，创建了视图后，能够舍弃定义引用的表或视图。要想检查视图定义是否存在这类问题，可使用check table语句；

7. 在定义中不能引用temporary表，不能创建temporary视图；

8. 在视图定义中命名的表必须已存在；

9. 不能将触发程序与视图关联在一起；

10. 在视图定义中允许使用order by，但是，如果从特定视图进行了选择，而该视图使用了具有自己order by的语句，它将被忽略。

## 修改视图

修改视图是指修改数据库中已存在的表的定义。当基本表的某些字段发生改变时，可以通过修改视图来保持视图和基本表之间一致。MySQL中通过CREATE OR REPLACE VIEW语句和ALTER VIEW语句来修改视图。

示例：修改视图

```sql
mysql> CREATE OR REPLACE 
VIEW view_student1(stu_id,stu_name,stu_class) AS SELECT id,name,class FROM student;
Query OK, 0 rows affected


mysql> select * from view_student1;
+--------+----------+-----------+
| stu_id | stu_name | stu_class |
+--------+----------+-----------+
|   1001 | Jason    |         1 |
|   1002 | Helen    |         3 |
|   1003 | Steve    |         5 |
|   1004 | Hanna    |         1 |
|   1005 | Bob      |         3 |
|   1006 | John     |         7 |
|   1007 | Walln    |         8 |
+--------+----------+-----------+
7 rows in set

mysql> ALTER VIEW view_student1 AS SELECT id,name,class FROM student where id  in (select id from student );
Query OK, 0 rows affected

mysql> select * from view_student1;
+------+-------+-------+
| id   | name  | class |
+------+-------+-------+
| 1001 | Jason |     1 |
| 1002 | Helen |     3 |
| 1003 | Steve |     5 |
| 1004 | Hanna |     1 |
| 1005 | Bob   |     3 |
| 1006 | John  |     7 |
| 1007 | Walln |     8 |
+------+-------+-------+
7 rows in set
```

说明：ALTER VIEW语句改变了视图的定义，该语句与CREATE OR REPLACE VIEW语句有着同样的限制，如果删除并重新创建一个视图，就必须重新为它分配权限。

## 删除视图

删除视图是指删除数据库中已存在的视图。删除视图时，只能删除视图的定义，不会删除数据。MySQL中，使用DROP VIEW语句来删除视图。但是，用户必须拥有DROP权限。

例：删除视图。

```sql
DROP VIEW IF EXISTS view_student;
```

## 查看视图

查看视图是指查看数据库中已存在的视图的定义。

例：查看视图。

```sql
mysql> describe view_student;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| id    | int(11)     | NO   |     | NULL    |       |
| name  | varchar(30) | YES  |     | NULL    |       |
| class | int(10)     | YES  |     | NULL    |       |
+-------+-------------+------+-----+---------+-------+
3 rows in set
```

# 视图练习

员工表和数据：

```sql
CREATE TABLE employee(  
        ID INT  PRIMARY KEY  AUTO_INCREMENT,  
        NAME CHAR(30) NOT NULL,  
        SEX  CHAR(2) NOT NULL,  
        AGE INT NOT NULL,  
        DEPARTMENT CHAR(10) NOT NULL,  
        SALARY  INT NOT NULL,  
        HOME CHAR(30),  
        MARRY CHAR(2) NOT NULL DEFAULT  '否',         
        HOBBY CHAR(30)  
 ); 
 
INSERT INTO employee(ID, NAME, SEX, AGE,DEPARTMENT, SALARY, HOME, MARRY, HOBBY) VALUES(NULL,'李红','女',20,'人事资源部','7000','浙江','否','网球');
INSERT INTO employee(ID, NAME, SEX, AGE,DEPARTMENT, SALARY, HOME, MARRY, HOBBY) VALUES(NULL,'姜文','女',21,'人事资源部','9000','北京','是','看书');
INSERT INTO employee(ID, NAME, SEX, AGE,DEPARTMENT, SALARY, HOME, MARRY, HOBBY) VALUES(NULL,'李楠','男',22,'产品研发部','8000','上海','否','音乐');
INSERT INTO employee(ID, NAME, SEX, AGE,DEPARTMENT, SALARY, HOME, MARRY, HOBBY) VALUES(NULL,'潇潇','女',23,'产品研发部','9000','重庆','否','游泳');
INSERT INTO employee(ID, NAME, SEX, AGE,DEPARTMENT, SALARY, HOME, MARRY, HOBBY) VALUES(NULL,'王亮','女',24,'产品研发部','9000','四川','是','足球');
INSERT INTO employee(ID, NAME, SEX, AGE,DEPARTMENT, SALARY, HOME, MARRY, HOBBY) VALUES(NULL,'程默','男',25,'业务销售部','8500','福建','否','游戏');
INSERT INTO employee(ID, NAME, SEX, AGE,DEPARTMENT, SALARY, HOME, MARRY, HOBBY) VALUES(NULL,'陆明','男',26,'业务销售部','10000','山西','否','篮球');
INSERT INTO employee(ID, NAME, SEX, AGE,DEPARTMENT, SALARY, HOME, MARRY, HOBBY) VALUES(NULL,'韩路','男',26,'业务销售部','15000','江苏','否','足球');
```

具体的表内容如下：

![员工表数据](/_images/database/mysql/员工表数据.png)

员工信息表和数据：

```sql
CREATE TABLE employee_detail(
	ID INT PRIMARY KEY,
	POS CHAR(10) NOT NULL,
	EXPERENCE CHAR(10) NOT NULL,
	CONSTRAINT `FK_ID` FOREIGN KEY(ID) REFERENCES employee(ID)
);

INSERT INTO employee_detail(ID,POS,EXPERENCE) VALUES(1,'人事管理','工作二年');
INSERT INTO employee_detail(ID,POS,EXPERENCE) VALUES(2,'人事招聘','工作二年');
INSERT INTO employee_detail(ID,POS,EXPERENCE) VALUES(3,'初级工程师','工作一年');
INSERT INTO employee_detail(ID,POS,EXPERENCE) VALUES(4,'中级工程师','工作二年');
INSERT INTO employee_detail(ID,POS,EXPERENCE) VALUES(5,'高级工程师','工作三年');
INSERT INTO employee_detail(ID,POS,EXPERENCE) VALUES(6,'销售代表','工作二年');
INSERT INTO employee_detail(ID,POS,EXPERENCE) VALUES(7,'销售经理','工作一年');
INSERT INTO employee_detail(ID,POS,EXPERENCE) VALUES(8,'销售总监','工作一年');
```

具体的表内容如下：

![员工信息表](/_images/database/mysql/员工信息表.png)

单表上创建视图:

```sql
CREATE VIEW V_VIEW1(ID, NAME, SEX, AGE,DEPARTMENT) AS SELECT ID, NAME, SEX, AGE,DEPARTMENT FROM employee;
```

显示结果

```sql
SELECT * FROM V_VIEW1;
```

![view1](/_images/database/mysql/view1.png)


多表上创建视图:

```sql
CREATE VIEW V_VIEW2(ID, NAME, SEX, AGE,DEPARTMENT,POS,EXPERENCE) AS SELECT a.ID, a.NAME, a.SEX, a.AGE,a.DEPARTMENT,b.POS,b.EXPERENCE FROM employee a,employee_detail b WHERE a.ID=b.ID;
```

显示结果

```sql
SELECT * FROM V_VIEW2;
```

![view2](/_images/database/mysql/view2.png)

修改视图中的数据，会影响原有表数据变化，例如：

```sql
UPDATE V_VIEW2 SET POS='高级工程师' WHERE NAME='李楠';
```

![update_view2](/_images/database/mysql/update_view2.png)

修改原始表中的数据，会影响视图的变化，例如：

```sql
INSERT INTO employee(ID, NAME, SEX, AGE,DEPARTMENT, SALARY, HOME, MARRY, HOBBY) VALUES(NULL,'韩寒','男',24,'产品研发部','8000','上海','否','音乐');
INSERT INTO employee_detail(ID,POS,EXPERENCE) VALUES(9,'初级工程师','工作一年');
```

![view3](/_images/database/mysql/view3.png)
​