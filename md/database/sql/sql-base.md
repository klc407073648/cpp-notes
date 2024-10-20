# SQL语言 - 语法基础

> 全称 Structured Query Language，结构化查询语言。操作关系型数据库的编程语言，定义了一套操作关系型数据库统一标准 。

[[toc]]

# 通用语法

在学习具体的SQL语句之前，先来了解一下SQL语言的同于语法。

1. SQL语句可以单行或多行书写，以分号结尾。
2. SQL语句可以使用空格/缩进来增强语句的可读性。
3. MySQL数据库的SQL语句不区分大小写，关键字建议使用大写。
4. 注释：
	* 单行注释：-- 注释内容 或 # 注释内容
	* 多行注释：/* 注释内容 */

# SQL分类

SQL语句，根据其功能，主要分为四类：DDL、DML、DQL、DCL

| 分 类 |            全称            |                                                         说明 |
| ----- | :------------------------: | -----------------------------------------------------------: |
| DDL   |  Data Definition Language  |           数据定义语言，用来定义数据库对象(<font color='red'>**数据库，表，字段)**</font> |
| DML   | Data Manipulation Language | 数据操作语言，用来对数据库<font color='red'>**表中的数据进行增删改**</font> |
| DQL   |    Data Query Language     |                     数据查询语言，用来查询数据库中表的记录 ⭐️ |
| DCL   |   Data Control Language    |       数据控制语言，用来创建数据库用户、控制数据库的访问权限 |

## DDL（数据定义语言）

> Data Definition Language，数据定义语言，用来定义数据库对象(数据库，表，字段) 。

### 数据库操作

```bash
查询所有数据库：
SHOW DATABASES;
查询当前数据库：
SELECT DATABASE();
创建数据库：
CREATE DATABASE [ IF NOT EXISTS ] 数据库名 [ DEFAULT CHARSET 字符集] [COLLATE 排序规则 ];
删除数据库：
DROP DATABASE [ IF EXISTS ] 数据库名;
使用数据库：
USE 数据库名;
```

**实际操作:**

<<< @/md/database/sql/base/DDL-数据库操作.sql

注意事项：

- UTF8字符集长度为3字节，有些符号占4字节，所以推荐用utf8mb4字符集

### 表操作

#### 表操作-查询

```
查询当前数据库所有表：
SHOW TABLES;
查询表结构：
DESC 表名;
查询指定表的建表语句：
SHOW CREATE TABLE 表名;
```

**实际操作:**

<<< @/md/database/sql/base/DDL-表操作-查询.sql

**创建表结构**：

```mysql
CREATE TABLE 表名(
	字段1 字段1类型 [COMMENT 字段1注释],
	字段2 字段2类型 [COMMENT 字段2注释],
	字段3 字段3类型 [COMMENT 字段3注释],
	...
	字段n 字段n类型 [COMMENT 字段n注释]
)[ COMMENT 表注释 ];
```

注意**：最后一个字段后面没有逗号**

#### 表操作-案例

设计一张员工信息表，要求如下：

1. 编号（纯数字）
2. 员工工号 (字符串类型，长度不超过10位)
3. 员工姓名（字符串类型，长度不超过10位）
4. 性别（男/女，存储一个汉字）
5. 年龄（正常人年龄，不可能存储负数）
6. 身份证号（二代身份证号均为18位，身份证中有X这样的字符）
7. 入职时间（取值年月日即可）

建表语句:

```mysql
create table emp(
	id int comment '编号',
	workno varchar(10) comment '工号',
	name varchar(10) comment '姓名',
	gender char(1) comment '性别',
	age tinyint unsigned comment '年龄',
	idcard char(18) comment '身份证号',
	entrydate date comment '入职时间'
) comment '员工表';
```

#### 表操作-修改

```
添加字段：
ALTER TABLE 表名 ADD 字段名 类型(长度) [COMMENT 注释] [约束];
例：ALTER TABLE emp ADD nickname varchar(20) COMMENT '昵称';

修改数据类型：
ALTER TABLE 表名 MODIFY 字段名 新数据类型(长度);
修改字段名和字段类型：
ALTER TABLE 表名 CHANGE 旧字段名 新字段名 类型(长度) [COMMENT 注释] [约束];
例：将emp表的nickname字段修改为username，类型为varchar(30)
ALTER TABLE emp CHANGE nickname username varchar(30) COMMENT '昵称';

删除字段：
ALTER TABLE 表名 DROP 字段名;

修改表名：
ALTER TABLE 表名 RENAME TO 新表名

删除表：
DROP TABLE [IF EXISTS] 表名;
删除表，并重新创建该表：
TRUNCATE TABLE 表名;
```

**实际操作**

1. 创建 emp 表
2. 添加字段: 为emp表增加一个新的字段”昵称”为nickname，类型为varchar(20)
3. 修改数据类型: nickname，类型为varchar(30)
4. 修改字段名和字段类型: 将emp表的nickname字段修改为username，类型为varchar(40)
5. 删除字段: 将emp表的字段username删除
6. 修改表名: 将emp表的表名修改为 employee

<<< @/md/database/sql/base/DDL-表操作-修改.sql

#### 表操作-删除

```
删除表
DROP TABLE [ IF EXISTS ] 表名;
删除指定表, 并重新创建表
TRUNCATE TABLE 表名;
```

**实际操作**

```
DROP TABLE IF EXISTS employee;
TRUNCATE TABLE employee;
```

## DML（数据操作语言）

> DML英文全称是Data Manipulation Language(数据操作语言)，用来对数据库中**表的数据记录进行增、删、改操作**。

* 添加数据（INSERT）
* 修改数据（UPDATE）
* 删除数据（DELETE）

### 添加数据

```
指定字段：
INSERT INTO 表名 (字段名1, 字段名2, ...) VALUES (值1, 值2, ...);
全部字段：
INSERT INTO 表名 VALUES (值1, 值2, ...);

批量添加数据：
INSERT INTO 表名 (字段名1, 字段名2, ...) VALUES (值1, 值2, ...), (值1, 值2, ...), (值1, 值2, ...);
INSERT INTO 表名 VALUES (值1, 值2, ...), (值1, 值2, ...), (值1, 值2, ...);
```

**实际操作**

<<< @/md/database/sql/base/DML-添加数据.sql

**注意事项**

- 插入数据时，指定的字段顺序需要与值的顺序是一一对应的。
- 字符串和日期类型数据应该包含在引号中
- 插入的数据大小应该在字段的规定范围内

### 更新数据

```
修改数据：
UPDATE 表名 SET 字段名1 = 值1, 字段名2 = 值2, ... [ WHERE 条件 ];
例：
UPDATE emp SET name = 'Jack' WHERE id = 1;
```

**实际操作**

<<< @/md/database/sql/base/DML-更新数据.sql

**注意事项**

- 修改语句的条件可以有，也可以没有，如果没有条件，则会修改整张表的所有数据。

### 删除数据

```
删除数据：
DELETE FROM 表名 [ WHERE 条件 ];
```

**实际操作**

<<< @/md/database/sql/base/DML-删除数据.sql

**注意事项**

* DELETE 语句的条件可以有，也可以没有，如果没有条件，则会删除整张表的所有数据。
* DELETE 语句不能删除某一个字段的值(可以使用UPDATE，将该字段值置为NULL即可)。

## DQL（数据查询语言）

> DQL英文全称是Data Query Language(数据查询语言)，数据查询语言，用来查询数据库中表的记录。

查询关键字: SELECT

在一个正常的业务系统中，查询操作的频次是要远高于增删改的，当我们去访问企业官网、电商网站，在这些网站中我们所看到的数据，实际都是需要从数据库中查询并展示的。而且在查询的过程中，可能还会涉及到条件、排序、分页等操作。

![](/_images/database/sql/base/京东商品界面.png)

数据源 `emp.sql` 为基础数据。

### 基本语法

```mysql
SELECT
	字段列表
FROM
	表名字段
WHERE
	条件列表
GROUP BY
	分组字段列表
HAVING
	分组后的条件列表
ORDER BY
	排序字段列表
LIMIT
	分页参数
```

可以将上述完整语法进行拆分，分为以下几个部分：

* 基本查询（不带任何条件）
* 条件查询（WHERE）
* 聚合函数（count、max、min、avg、sum）
* 分组查询（group by）
* 排序查询（order by）
* 分页查询（limit）

### 基础查询

```
查询多个字段：
SELECT 字段1, 字段2, 字段3, ... FROM 表名;
SELECT * FROM 表名;

设置别名：
SELECT 字段1 [ AS 别名1 ], 字段2 [ AS 别名2 ], 字段3 [ AS 别名3 ], ... FROM 表名;
SELECT 字段1 [ 别名1 ], 字段2 [ 别名2 ], 字段3 [ 别名3 ], ... FROM 表名;

去除重复记录：
SELECT DISTINCT 字段列表 FROM 表名;

转义：
SELECT * FROM 表名 WHERE name LIKE '/_张三' ESCAPE '/'
/ 之后的\_不作为通配符
```

**实际操作**

<<< @/md/database/sql/base/DQL-基础查询.sql

### 条件查询

语法：
SELECT 字段列表 FROM 表名 WHERE 条件列表;

条件：

| 比较运算符          | 功能                                        |
| ------------------- | ------------------------------------------- |
| >                   | 大于                                        |
| >=                  | 大于等于                                    |
| <                   | 小于                                        |
| <=                  | 小于等于                                    |
| =                   | 等于                                        |
| <> 或 !=            | 不等于                                      |
| BETWEEN ... AND ... | 在某个范围内（含最小、最大值）              |
| IN(...)             | 在in之后的列表中的值，多选一                |
| LIKE 占位符         | 模糊匹配（\_匹配单个字符，%匹配任意个字符） |
| IS NULL             | 是NULL                                      |

| 逻辑运算符         | 功能                         |
| ------------------ | ---------------------------- |
| AND 或 &&          | 并且（多个条件同时成立）     |
| OR 或 &#124;&#124; | 或者（多个条件任意一个成立） |
| NOT 或 !           | 非，不是                     |

**实际操作**

<<< @/md/database/sql/base/DQL-条件查询.sql

### 聚合查询（聚合函数）

> 将一列数据作为一个整体，进行纵向计算 。

常见聚合函数：

| 函数  | 功能     |
| ----- | -------- |
| count | 统计数量 |
| max   | 最大值   |
| min   | 最小值   |
| avg   | 平均值   |
| sum   | 求和     |

语法：

SELECT 聚合函数(字段列表) FROM 表名;

注意 : NULL值是不参与所有聚合函数运算的。

**案例**：

<<< @/md/database/sql/base/DQL-聚合函数案例.sql

### 分组查询

语法：

```mysql
SELECT 字段列表 FROM 表名 [ WHERE 条件 ] GROUP BY 分组字段名 [ HAVING 分组后的过滤条件 ];
```

where 和 having 的区别：

- 执行时机不同：where是分组之前进行过滤，不满足where条件不参与分组；having是分组后对结果进行过滤。
- 判断条件不同：where不能对聚合函数进行判断，而having可以。

例子：

<<< @/md/database/sql/base/DQL-分组查询.sql

**注意事项**

- 执行顺序：where > 聚合函数 > having
- 分组之后，查询的字段一般为聚合函数和分组字段，查询其他字段无任何意义
- 支持多字段分组, 具体语法为 : group by columnA,columnB

### 排序查询

> 排序在日常开发中是非常常见的一个操作，有升序排序，也有降序排序。例如，商品价格、销量排序等

语法：

```
SELECT 字段列表 FROM 表名 ORDER BY 字段1 排序方式1, 字段2 排序方式2;
```

排序方式：

- ASC: 升序（默认）
- DESC: 降序

注意事项：

- 如果是升序, 可以不指定排序方式ASC ;
- 如果是多字段排序，当第一个字段值相同时，才会根据第二个字段进行排序 ;

例子：

<<< @/md/database/sql/base/DQL-排序查询.sql

**注意事项**

如果是多字段排序，当第一个字段值相同时，才会根据第二个字段进行排序

### 分页查询

> 分页操作在业务系统开发时，也是非常常见的一个功能，我们在网站中看到的各种各样的分页条，后台都需要借助于数据库的分页操作。

语法：

```
SELECT 字段列表 FROM 表名 LIMIT 起始索引, 查询记录数;
```

注意事项:

* 起始索引从0开始，起始索引 = （查询页码 - 1）* 每页显示记录数。
* 分页查询是数据库的方言，不同的数据库有不同的实现，MySQL中是LIMIT。
* 如果查询的是第一页数据，起始索引可以省略，直接简写为 limit 10。

例子：

<<< @/md/database/sql/base/DQL-分页查询.sql


### 执行顺序

> DQL语句在执行时的执行顺序，也就是先执行那一部分，后执行那一部分

![](/_images/database/sql/base/执行顺序.png)

FROM -> WHERE -> GROUP BY -> HAVING > SELECT -> ORDER BY -> LIMIT

<<< @/md/database/sql/base/DQL-执行顺序.sql

## DCL

> DCL英文全称是Data Control Language(数据控制语言)，用来管理数据库用户、控制数据库的访问权限。

### 管理用户

查询用户：

```mysql
USE mysql;
SELECT * FROM user;
```

![](/_images/database/sql/base/mysql_user.png)
 
* Host代表当前用户访问的主机, 如果为localhost, 仅代表只能够在当前本机访问，是不可以
远程访问的。 
* User代表的是访问该数据库的用户名。在MySQL中需要通过Host和User来唯一标识一个用户。

```mysql
创建用户:
CREATE USER '用户名'@'主机名' IDENTIFIED BY '密码';

修改用户密码：
ALTER USER '用户名'@'主机名' IDENTIFIED WITH mysql_native_password BY '新密码';

删除用户：
DROP USER '用户名'@'主机名';
```

例子：

<<< @/md/database/sql/base/DCL-用户操作.sql

**注意事项**

- 主机名可以使用 % 通配

### 权限控制

常用权限：

| 权限                | 说明               |
| ------------------- | ------------------ |
| ALL, ALL PRIVILEGES | 所有权限           |
| SELECT              | 查询数据           |
| INSERT              | 插入数据           |
| UPDATE              | 修改数据           |
| DELETE              | 删除数据           |
| ALTER               | 修改表             |
| DROP                | 删除数据库/表/视图 |
| CREATE              | 创建数据库/表      |

更多权限请看[权限一览表](#权限一览表 "权限一览表")

```mysql
查询权限：
SHOW GRANTS FOR '用户名'@'主机名';

授予权限：
GRANT 权限列表 ON 数据库名.表名 TO '用户名'@'主机名';

撤销权限：
REVOKE 权限列表 ON 数据库名.表名 FROM '用户名'@'主机名';
```

例子：

<<< @/md/database/sql/base/DCL-权限操作.sql

**注意事项**

- 多个权限, 用逗号分隔
- 授权时，数据库名和表名可以用 * 进行通配，代表所有