-- -----------------------------------------------------
-- Table `course`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `course` ;

CREATE TABLE IF NOT EXISTS `course` (
  `cou_id` INT NOT NULL ,
  `cou_name` VARCHAR(45) NULL ,
  `cou_score` CHAR(2) NULL ,
  `cou_info` TEXT NULL ,
  `cou_limit` INT NULL ,
  PRIMARY KEY (`cou_id`)  )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `department`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `department` ;

CREATE TABLE IF NOT EXISTS `department` (
  `dep_id` INT NOT NULL ,
  `dep_name` VARCHAR(45) NULL ,
  `dep_info` TEXT NULL ,
  PRIMARY KEY (`dep_id`)  )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `class`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `class` ;

CREATE TABLE IF NOT EXISTS `class` (
  `cls_id` INT NOT NULL ,
  `dep_id` INT NULL ,
  PRIMARY KEY (`cls_id`)  )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `student`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `student` ;

CREATE TABLE IF NOT EXISTS `student` (
  `stu_id` INT NOT NULL ,
  `stu_name` VARCHAR(45) NULL ,
  `stu_grade` CHAR(2) NULL ,
  `stu_sex` CHAR(2) NULL ,
  `cls_id` INT NULL ,
  `stu_hobby` VARCHAR(45) NULL ,
  `stu_birth` DATE NULL ,
  PRIMARY KEY (`stu_id`)  )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `choose_course`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `choose_course` ;

CREATE TABLE IF NOT EXISTS `choose_course` (
  `stu_id` INT NOT NULL ,
  `cou_id` INT NOT NULL ,
  `stu_cou_score` INT NULL ,
  PRIMARY KEY (`stu_id`, `cou_id`)  )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `techer`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `teacher` ;

CREATE TABLE IF NOT EXISTS `teacher` (
  `tec_id` INT NOT NULL ,
  `tec_name` VARCHAR(45) NULL ,
  `dep_id` INT NULL ,
  PRIMARY KEY (`tec_id`)  )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- ALTER Table FOREIGN KEY
-- -----------------------------------------------------
ALTER TABLE student ADD CONSTRAINT fk_student_class FOREIGN KEY (cls_id) REFERENCES class (cls_id);
ALTER TABLE teacher ADD CONSTRAINT fk_teacher_department FOREIGN KEY (dep_id) REFERENCES department (dep_id);
ALTER TABLE class ADD CONSTRAINT fk_classes_department FOREIGN KEY (dep_id) REFERENCES department (dep_id);
ALTER TABLE choose_course ADD CONSTRAINT fk_choose_course_course FOREIGN KEY (cou_id) REFERENCES course (cou_id);
ALTER TABLE choose_course ADD CONSTRAINT fk_choose_course_student FOREIGN KEY (stu_id) REFERENCES student (stu_id);
