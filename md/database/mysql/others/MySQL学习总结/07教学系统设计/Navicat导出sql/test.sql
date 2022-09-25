-- ----------------------------
-- 查找学生id为1001所选课程
-- ----------------------------
select cou_name from course where cou_id in (select cou_id from choose_course where stu_id=1001);

-- ----------------------------
-- 查找学生id为1001所在院系、课程、分数
-- ----------------------------
select a.dep_name,a.dep_info,b.cou_name,c.stu_cou_score,d.stu_name from department as a ,course as b ,
choose_course as c , student as d,class as e where d.stu_id=1002 and a.dep_id=e.dep_id and d.cls_id=e.cls_id and d.stu_id=c.stu_id and c.cou_id=b.cou_id;