-- 学生表
create table student(
    id int auto_increment primary key comment '主键ID',
    name varchar(10) comment '姓名',
    no varchar(10) comment '学号'
) comment '学生表';

insert into
    student
values
    (null, '黛绮丝', '2000100101'),
    (null, '谢逊', '2000100102'),
    (null, '殷天正', '2000100103'),
    (null, '韦一笑', '2000100104');

-- 课程表
create table course(
    id int auto_increment primary key comment '主键ID',
    name varchar(10) comment '课程名称'
) comment '课程表';

insert into
    course
values
    (null, 'Java'),
    (null, 'PHP'),
    (null, 'MySQL'),
    (null, 'Hadoop');

-- 学生课程中间表
create table student_course(
    id int auto_increment comment '主键' primary key,
    studentid int not null comment '学生ID',
    courseid int not null comment '课程ID',
    constraint fk_courseid foreign key (courseid) references course (id),
    constraint fk_studentid foreign key (studentid) references student (id)
) comment '学生课程中间表';

insert into
    student_course
values
    (null, 1, 1),
    (null, 1, 2),
    (null, 1, 3),
    (null, 2, 2),
    (null, 2, 3),
    (null, 3, 4);