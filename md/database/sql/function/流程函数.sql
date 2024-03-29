-- A. if
-- 	select ifnull('Ok','Default');
-- B. ifnull
-- 	select ifnull('Ok','Default');
-- 	select ifnull('','Default');
-- 	select ifnull(null,'Default');
-- C. case when then else end
-- 	需求: 查询emp表的员工姓名和工作地址 (北京/上海 ----> 一线城市 , 其他 ----> 二线城市)
-- 	select name,( case workaddress when '北京' then '一线城市' when '上海' then '一线城市' else '二线城市' end ) as '工作地址' from emp;

mysql> select ifnull('Ok','Default');
+------------------------+
| ifnull('Ok','Default') |
+------------------------+
| Ok                     |
+------------------------+
1 row in set (0.00 sec)

mysql> select ifnull('Ok','Default');
+------------------------+
| ifnull('Ok','Default') |
+------------------------+
| Ok                     |
+------------------------+
1 row in set (0.00 sec)

mysql> select ifnull('','Default');
+----------------------+
| ifnull('','Default') |
+----------------------+
|                      |
+----------------------+
1 row in set (0.00 sec)

mysql> select ifnull(null,'Default');
+------------------------+
| ifnull(null,'Default') |
+------------------------+
| Default                |
+------------------------+
1 row in set (0.00 sec)

mysql> select name,( case workaddress when '北京' then '一线城市' when '上海' then '一线城市' else '二线城市' end ) as '工作地址' from emp;
+-----------+-------------+
| name      | 工作地址 |
+-----------+-------------+
| 柳岩    | 一线城市      |
| 张无忌  | 一线城市      |
| 韦一笑  | 一线城市      |
| 赵敏    | 一线城市      |
| 小昭    | 一线城市      |
| 杨逍    | 一线城市      |
| 范瑶    | 一线城市      |
| 黛绮丝  | 二线城市      |
| 范凉凉  | 一线城市      |
| 陈友谅  | 一线城市      |
| 张士诚  | 二线城市      |
| 常遇春  | 一线城市      |
| 张三丰  | 二线城市      |
| 灭绝    | 二线城市      |
| 胡青牛  | 二线城市      |
| 周芷若  | 一线城市      |
+-----------+-------------+


create table score(
id int comment 'ID',
name varchar(20) comment '姓名',
math int comment '数学',
english int comment '英语',
chinese int comment '语文'
) comment '学员成绩表';
insert into score(id, name, math, english, chinese) VALUES (1, 'Tom', 67, 88, 95
), (2, 'Rose' , 23, 66, 90),(3, 'Jack', 56, 98, 76);

select id, name,
(case when math >= 85 then '优秀' when math >=60 then '及格' else '不及格' end ) '数学',
(case when english >= 85 then '优秀' when english >=60 then '及格' else '不及格' end ) '英语',
(case when chinese >= 85 then '优秀' when chinese >=60 then '及格' else '不及格' end ) '语文' 
from score;

ID  姓名	数学	英语	语文
1	Tom		及格	优秀	优秀
2	Rose	不及格	及格	优秀
3	Jack	不及格	优秀	及格
