/*
Navicat MySQL Data Transfer

Source Server         : local_mysql
Source Server Version : 50626
Source Host           : localhost:3306
Source Database       : mytest

Target Server Type    : MYSQL
Target Server Version : 50626
File Encoding         : 65001

Date: 2020-10-25 15:01:50
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for choose_course
-- ----------------------------
DROP TABLE IF EXISTS `choose_course`;
CREATE TABLE `choose_course` (
  `stu_id` int(11) NOT NULL,
  `cou_id` int(11) NOT NULL,
  `stu_cou_score` int(11) DEFAULT NULL,
  PRIMARY KEY (`stu_id`,`cou_id`),
  KEY `fk_choose_course_course` (`cou_id`),
  CONSTRAINT `fk_choose_course_course` FOREIGN KEY (`cou_id`) REFERENCES `course` (`cou_id`),
  CONSTRAINT `fk_choose_course_student` FOREIGN KEY (`stu_id`) REFERENCES `student` (`stu_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of choose_course
-- ----------------------------
INSERT INTO `choose_course` VALUES ('1001', '30010001', '80');
INSERT INTO `choose_course` VALUES ('1001', '30010002', '90');
INSERT INTO `choose_course` VALUES ('1002', '30050001', '70');
INSERT INTO `choose_course` VALUES ('1003', '30020001', '95');

-- ----------------------------
-- Table structure for class
-- ----------------------------
DROP TABLE IF EXISTS `class`;
CREATE TABLE `class` (
  `cls_id` int(11) NOT NULL,
  `dep_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`cls_id`),
  KEY `fk_classes_department` (`dep_id`),
  CONSTRAINT `fk_classes_department` FOREIGN KEY (`dep_id`) REFERENCES `department` (`dep_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of class
-- ----------------------------
INSERT INTO `class` VALUES ('2020001', '3001');
INSERT INTO `class` VALUES ('2020002', '3002');
INSERT INTO `class` VALUES ('2020003', '3003');
INSERT INTO `class` VALUES ('2020004', '3004');
INSERT INTO `class` VALUES ('2020005', '3005');
INSERT INTO `class` VALUES ('2020006', '3006');

-- ----------------------------
-- Table structure for course
-- ----------------------------
DROP TABLE IF EXISTS `course`;
CREATE TABLE `course` (
  `cou_id` int(11) NOT NULL,
  `cou_name` varchar(45) DEFAULT NULL,
  `cou_score` char(2) DEFAULT NULL,
  `cou_info` text,
  `cou_limit` int(11) DEFAULT NULL,
  PRIMARY KEY (`cou_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of course
-- ----------------------------
INSERT INTO `course` VALUES ('30010001', '?????????????????????', '3', '?????????????????????????????????', '50');
INSERT INTO `course` VALUES ('30010002', 'C++????????????', '5', 'C++?????????????????????', '80');
INSERT INTO `course` VALUES ('30020001', '?????????', '2', '??????????????????', '40');
INSERT INTO `course` VALUES ('30030001', '?????????????????????', '2', '??????????????????????????????????????????', '50');
INSERT INTO `course` VALUES ('30040001', '??????????????????', '4', '??????????????????????????????', '50');
INSERT INTO `course` VALUES ('30050001', '????????????', '3', '????????????????????????', '60');

-- ----------------------------
-- Table structure for department
-- ----------------------------
DROP TABLE IF EXISTS `department`;
CREATE TABLE `department` (
  `dep_id` int(11) NOT NULL,
  `dep_name` varchar(45) DEFAULT NULL,
  `dep_info` text,
  PRIMARY KEY (`dep_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of department
-- ----------------------------
INSERT INTO `department` VALUES ('3001', '???????????????', '?????????????????????');
INSERT INTO `department` VALUES ('3002', '????????????', '??????????????????');
INSERT INTO `department` VALUES ('3003', '????????????', '????????????????????????');
INSERT INTO `department` VALUES ('3004', '???????????????', '?????????????????????');
INSERT INTO `department` VALUES ('3005', '????????????', '????????????');
INSERT INTO `department` VALUES ('3006', '????????????', '?????????????????????');

-- ----------------------------
-- Table structure for student
-- ----------------------------
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student` (
  `stu_id` int(11) NOT NULL,
  `stu_name` varchar(45) DEFAULT NULL,
  `stu_grade` char(2) DEFAULT NULL,
  `stu_sex` char(2) DEFAULT NULL,
  `cls_id` int(11) DEFAULT NULL,
  `stu_hobby` varchar(45) DEFAULT NULL,
  `stu_birth` date DEFAULT NULL,
  PRIMARY KEY (`stu_id`),
  KEY `fk_student_class` (`cls_id`),
  CONSTRAINT `fk_student_class` FOREIGN KEY (`cls_id`) REFERENCES `class` (`cls_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of student
-- ----------------------------
INSERT INTO `student` VALUES ('1001', '??????', '??????', '???', '2020001', '??????', '2000-06-14');
INSERT INTO `student` VALUES ('1002', '??????', '??????', '???', '2020005', '??????', '2000-05-02');
INSERT INTO `student` VALUES ('1003', '??????', '??????', '???', '2020002', '??????', '2020-10-30');

-- ----------------------------
-- Table structure for teacher
-- ----------------------------
DROP TABLE IF EXISTS `teacher`;
CREATE TABLE `teacher` (
  `tec_id` int(11) NOT NULL,
  `tec_name` varchar(45) DEFAULT NULL,
  `dep_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`tec_id`),
  KEY `fk_teacher_department` (`dep_id`),
  CONSTRAINT `fk_teacher_department` FOREIGN KEY (`dep_id`) REFERENCES `department` (`dep_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of teacher
-- ----------------------------
INSERT INTO `teacher` VALUES ('20001', '??????', '3006');
INSERT INTO `teacher` VALUES ('20002', '??????', '3004');
INSERT INTO `teacher` VALUES ('20003', '??????', '3002');
INSERT INTO `teacher` VALUES ('20004', '?????????', '3001');
INSERT INTO `teacher` VALUES ('20005', '?????????', '3003');
