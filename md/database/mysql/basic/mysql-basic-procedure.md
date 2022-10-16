# MySQL基础 - 存储过程

[[toc]]

# 存储过程

## 介绍

存储过程是事先经过编译并存储在数据库中的一段 SQL 语句的集合，调用存储过程可以简化应用开发人员的很多工作，减少数据在数据库和应用服务器之间的传输，对于提高数据处理的效率是有好处的。

存储过程思想上很简单，就是**数据库 SQL 语言层面的代码封装与重用**。

特点:

* 封装，复用
    * 可以把某一业务SQL封装在存储过程中，需要用到的时候直接调用即可。
* 可以接收参数，也可以返回数据 
    * 再存储过程中，可以传递参数，也可以接收返回值。
* 减少网络交互，效率提升 
    * 如果涉及到多条SQL，每执行一次都是一次网络传输。而如果封装在存储过程中，我们只需要网络交互一次可能就可以了。

## 基本语法

1). 创建

```sql
CREATE PROCEDURE 存储过程名称 ([ 参数列表 ])
BEGIN
    -- SQL语句
END ;
```

2). 调用

```sql
CALL 名称 ([ 参数 ]);
```

3). 查看

```sql
SELECT * FROM INFORMATION_SCHEMA.ROUTINES WHERE ROUTINE_SCHEMA = 'xxx'; -- 查询指定数据库的存储过程及状态信息
SHOW CREATE PROCEDURE 存储过程名称 ; -- 查询某个存储过程的定义
```

4). 删除

```sql
DROP PROCEDURE [ IF EXISTS ] 存储过程名称
```

注意:
    * 在命令行中，执行创建存储过程的SQL时，需要通过关键字 delimiter 指定SQL语句的结束符。

演示示例:

<<< @/md/database/mysql/basic/src/procedure_1.sql

## 变量

在MySQL中变量分为三种类型: 系统变量、用户定义变量、局部变量。

### 系统变量

系统变量 是MySQL服务器提供，不是用户定义的，属于服务器层面。分为全局变量（GLOBAL）、会话变量（SESSION）。

1). 查看系统变量

```sql
SHOW [ SESSION | GLOBAL ] VARIABLES ; -- 查看所有系统变量
SHOW [ SESSION | GLOBAL ] VARIABLES LIKE '......'; -- 可以通过LIKE模糊匹配方式查找变量
SELECT @@[SESSION | GLOBAL] 系统变量名; -- 查看指定变量的值
```

2). 设置系统变量

```sql
SET [ SESSION | GLOBAL ] 系统变量名 = 值 ;
SET @@[SESSION | GLOBAL] 系统变量名 = 值 ;
```
注意:
    * 如果没有指定SESSION/GLOBAL，默认是SESSION，会话变量。
        * mysql服务重新启动之后，所设置的全局参数会失效，要想不失效，可以在 /etc/my.cnf 中配置。
    * A. 全局变量(GLOBAL): 全局变量针对于所有的会话。
    * B. 会话变量(SESSION): 会话变量针对于单个会话，在另外一个会话窗口就不生效了。

演示示例:

<<< @/md/database/mysql/basic/src/procedure_2.sql

### 用户定义变量

用户定义变量 是用户根据需要自己定义的变量，用户变量不用提前声明，在用的时候直接用 "@变量名" 使用就可以。其作用域为当前连接。

1). 赋值

方式一:

```sql
SET @var_name = expr [, @var_name = expr] ... ;
SET @var_name := expr [, @var_name := expr] ... ;
```

赋值时，可以使用 = ，也可以使用 := 。

方式二:

```sql
SELECT @var_name := expr [, @var_name := expr] ... ;
SELECT 字段名 INTO @var_name FROM 表名;
```

2). 使用

`SELECT @var_name ;`

演示示例：

<<< @/md/database/mysql/basic/src/procedure_3.sql

### 局部变量

局部变量 是根据需要定义的在局部生效的变量，访问之前，需要DECLARE声明。可用作存储过程内的局部变量和输入参数，局部变量的范围是在其内声明的BEGIN ... END块。

1). 声明
`DECLARE 变量名 变量类型 [DEFAULT ... ];`

变量类型就是数据库字段类型：INT、BIGINT、CHAR、VARCHAR、DATE、TIME等。

2). 赋值

```sql
SET 变量名 = 值 ;
SET 变量名 := 值 ;
SELECT 字段名 INTO 变量名 FROM 表名 ... ;
```

演示示例:

<<< @/md/database/mysql/basic/src/procedure_4.sql

## if

1). 介绍

用于做条件判断，具体的语法结构为：

```sql
IF 条件1 THEN
.....
ELSEIF 条件2 THEN -- 可选
.....
ELSE -- 可选
.....
END IF;
```

在if条件判断的结构中，ELSE IF 结构可以有多个，也可以没有。 ELSE结构可以有，也可以没有。

2). 案例

<<< @/md/database/mysql/basic/src/procedure_if.sql

上述的需求我们虽然已经实现了，但是也存在一些问题，比如：score 分数我们是在存储过程中定义死的，而且最终计算出来的分数等级，我们也仅仅是最终查询展示出来而已。

那么我们能不能，把score分数动态的传递进来，计算出来的分数等级是否可以作为返回值返回呢？答案是肯定的，我们可以通过接下来所讲解的 参数 来解决上述的问题。

## 参数

1). 介绍

参数的类型，主要分为以下三种：IN、OUT、INOUT。 具体的含义如下：

|类型 |含义| 备注|
| -------- | ----- |  ----- | 
|IN |该类参数作为输入，也就是需要调用时传入值 |默认|
|OUT |该类参数作为输出，也就是该参数可以作为返回值||
|INOUT |既可以作为输入参数，也可以作为输出参数||

用法：
```sql
CREATE PROCEDURE 存储过程名称 ([ IN/OUT/INOUT 参数名 参数类型 ])
BEGIN
    -- SQL语句
END ;
```

2). 案例一

<<< @/md/database/mysql/basic/src/procedure_var_1.sql

3). 案例二

<<< @/md/database/mysql/basic/src/procedure_var_2.sql

## case

1). 介绍

case结构及作用，和我们在基础篇中所讲解的流程控制函数很类似。有两种语法格式：

语法1：

```sql
-- 含义： 当case_value的值为 when_value1时，执行statement_list1，当值为 when_value2时，执行statement_list2， 否则就执行statement_list
CASE case_value
    WHEN when_value1 THEN statement_list1
    [ WHEN when_value2 THEN statement_list2] ...
    [ ELSE statement_list ]
END CASE;
```

语法2：

```sql
-- 含义： 当条件search_condition1成立时，执行statement_list1，当条件search_condition2成立时，执行statement_list2， 否则就执行 statement_list
CASE
    WHEN search_condition1 THEN statement_list1
    [WHEN search_condition2 THEN statement_list2] ...
    [ELSE statement_list]
END CASE;
```

2). 案例

<<< @/md/database/mysql/basic/src/procedure_case.sql

注意：如果判定条件有多个，多个条件之间，可以使用 and 或 or 进行连接。

## while

1). 介绍

while 循环是有条件的循环控制语句。满足条件后，再执行循环体中的SQL语句。具体语法为：

```sql
-- 先判定条件，如果条件为true，则执行逻辑，否则，不执行逻辑
WHILE 条件 DO
    SQL逻辑...
END WHILE;
```

2). 案例

<<< @/md/database/mysql/basic/src/procedure_where.sql

## repeat

1). 介绍

repeat是有条件的循环控制语句, 当满足until声明的条件的时候，则退出循环 。具体语法为：

2). 案例

<<< @/md/database/mysql/basic/src/procedure_repeat.sql

## loop

1). 介绍

LOOP 实现简单的循环，如果不在SQL逻辑中增加退出循环的条件，可以用其来实现简单的死循环。

LOOP可以配合一下两个语句使用：

* LEAVE ：配合循环使用，退出循环。
* ITERATE：必须用在循环中，作用是跳过当前循环剩下的语句，直接进入下一次循环。

```sql
[begin_label:] LOOP
SQL逻辑...
END LOOP [end_label];

LEAVE label; -- 退出指定标记的循环体
ITERATE label; -- 直接进入下一次循环
```
 
上述语法中出现的 begin_label，end_label，label 指的都是我们所自定义的标记。

2). 案例

<<< @/md/database/mysql/basic/src/procedure_loop.sql

## 游标

### 介绍

游标（CURSOR）是用来存储查询结果集的数据类型 , 在存储过程和函数中可以使用游标对结果集进行循环的处理。游标的使用包括游标的声明、OPEN、FETCH 和 CLOSE，其语法分别如下。

A. 声明游标
`DECLARE 游标名称 CURSOR FOR 查询语句 ;`
B. 打开游标
`OPEN 游标名称;`
C. 获取游标记录
`FETCH 游标名称 INTO 变量 [, 变量 ] ;`
D. 关闭游标
`CLOSE 游标名称 ;`

2). 案例

<<< @/md/database/mysql/basic/src/procedure_cursor_1.sql

上述的存储过程，最终我们在调用的过程中，会报错，之所以报错是因为上面的while循环中，并没有退出条件。当游标的数据集获取完毕之后，再次获取数据，就会报错，从而终止了程序的执行。

但是此时，tb_user_pro表结构及其数据都已经插入成功了，我们可以直接刷新表结构，检查表结构中的数据。

上述的功能，虽然我们实现了，但是逻辑并不完善，而且程序执行完毕，获取不到数据，数据库还报错。 接下来，我们就需要来完成这个存储过程，并且解决这个问题。

要想解决这个问题，就需要通过MySQL中提供的 条件处理程序 Handler 来解决。

## 条件处理程序

1) 介绍

条件处理程序（Handler）可以用来定义在流程控制结构执行过程中遇到问题时相应的处理步骤。具体语法为：

```sql
DECLARE handler_action HANDLER FOR condition_value [, condition_value]
... statement ;

handler_action 的取值：
    CONTINUE: 继续执行当前程序
    EXIT: 终止执行当前程序

condition_value 的取值：
    SQLSTATE sqlstate_value: 状态码，如 02000

    SQLWARNING: 所有以01开头的SQLSTATE代码的简写
    NOT FOUND: 所有以02开头的SQLSTATE代码的简写
    SQLEXCEPTION: 所有没有被SQLWARNING 或 NOT FOUND捕获的SQLSTATE代码的简写
```
2). 案例

<<< @/md/database/mysql/basic/src/procedure_cursor_2.sql


具体的错误状态码，可以参考官方文档：
https://dev.mysql.com/doc/refman/8.0/en/declare-handler.html
https://dev.mysql.com/doc/mysql-errors/8.0/en/server-error-reference.html

# 存储函数

1). 介绍

存储函数是有返回值的存储过程，存储函数的参数只能是IN类型的。具体语法如下：

```sql
CREATE FUNCTION 存储函数名称 ([ 参数列表 ])
RETURNS type [characteristic ...]
BEGIN
    -- SQL语句
    RETURN ...;
END ;
```

characteristic说明：
    * DETERMINISTIC：相同的输入参数总是产生相同的结果
    * NO SQL ：不包含 SQL 语句。
    * READS SQL DATA：包含读取数据的语句，但不包含写入数据的语句。

2). 案例

<<< @/md/database/mysql/basic/src/store_fun.sql