/*
Navicat MySQL Data Transfer

Source Server         : local_mysql
Source Server Version : 50626
Source Host           : localhost:3306
Source Database       : mytest

Target Server Type    : MYSQL
Target Server Version : 50626
File Encoding         : 65001

Date: 2020-10-25 08:42:37
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for student
-- ----------------------------
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student` (
  `id` int(11) NOT NULL,
  `name` varchar(30) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `sex` enum('man','woman') DEFAULT NULL,
  `class` int(10) DEFAULT NULL,
  `grade` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of student
-- ----------------------------
INSERT INTO `student` VALUES ('1001', 'Jason', '25', 'man', '1', '90');
INSERT INTO `student` VALUES ('1002', 'Helen', '25', 'woman', '3', '50');
INSERT INTO `student` VALUES ('1003', 'Steve', '27', 'man', '5', '85');
INSERT INTO `student` VALUES ('1004', 'Hanna', '25', 'woman', '1', '100');
INSERT INTO `student` VALUES ('1005', 'Bob', '26', 'man', '3', null);
INSERT INTO `student` VALUES ('1006', 'John', '28', 'man', '7', '70');
INSERT INTO `student` VALUES ('1007', 'Walln', '25', 'woman', '8', '60');

select id,if(grade>=60,'PASS','FAIL') as if_grade_pass from student;
select id,ifnull(grade,'NO GRADE') as if_grade_null from student;
select id,grade, case when grade>=90 then 'Great' when grade>=70 and grade<90 then 'Good' when grade>=60 and grade<70 then 'Okay' else 'FAIL' end level from student;

