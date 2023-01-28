-- <20210720074148>
-- -----------------------------------------------------
-- Database student
-- -----------------------------------------------------
create database `student` default character set utf8 collate utf8_general_ci;
 
use student;
 
-- -----------------------------------------------------
-- Table `student`.`student`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `student`;

CREATE TABLE `student` (
  `id` int(11) NOT NULL,
  `name` varchar(30) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `sex` enum('man','woman') DEFAULT NULL,
  `class` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
);
 