-- 用户基本信息表
create table tb_user(
    id int auto_increment primary key comment '主键ID',
    name varchar(10) comment '姓名',
    age int comment '年龄',
    gender char(1) comment '1: 男 , 2: 女',
    phone char(11) comment '手机号'
) comment '用户基本信息表';

insert into
    tb_user(id, name, age, gender, phone)
values
    (null, '黄渤', 45, '1', '18800001111'),
    (null, '冰冰', 35, '2', '18800002222'),
    (null, '码云', 55, '1', '18800008888'),
    (null, '李彦宏', 50, '1', '18800009999');

-- 用户教育信息表
create table tb_user_edu(
    id int auto_increment primary key comment '主键ID',
    degree varchar(20) comment '学历',
    major varchar(50) comment '专业',
    primaryschool varchar(50) comment '小学',
    middleschool varchar(50) comment '中学',
    university varchar(50) comment '大学',
    userid int unique comment '用户ID',
    constraint fk_userid foreign key (userid) references tb_user(id)
) comment '用户教育信息表';

insert into
    tb_user_edu(
        id,
        degree,
        major,
        primaryschool,
        middleschool,
        university,
        userid
    )
values
    (
        null,
        '本科',
        '舞蹈',
        '静安区第一小学',
        '静安区第一中学',
        '北京舞蹈学院',
        1
    ),
    (
        null,
        '硕士',
        '表演',
        '朝阳区第一小学',
        '朝阳区第一中学',
        '北京电影学院',
        2
    ),
    (
        null,
        '本科',
        '英语',
        '杭州市第一小学',
        '杭州市第一中学',
        '杭州师范大学',
        3
    ),
    (
        null,
        '本科',
        '应用数学',
        '阳泉第一小学',
        '阳泉区第一中学',
        '清华大学',
        4
    );