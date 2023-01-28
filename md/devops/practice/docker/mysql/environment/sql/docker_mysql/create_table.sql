-- <20210720073446>
-- -----------------------------------------------------
-- Database docker_mysql
-- -----------------------------------------------------
create database `docker_mysql` default character set utf8 collate utf8_general_ci;
 
use docker_mysql;
 
-- -----------------------------------------------------
-- Table `docker_mysql`.`user`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `user`;
 
CREATE TABLE `user` (
 `id` bigint(20) NOT NULL,
 `created_at` bigint(40) DEFAULT NULL,
 `last_modified` bigint(40) DEFAULT NULL,
 `email` varchar(255) DEFAULT NULL,
 `first_name` varchar(255) DEFAULT NULL,
 `last_name` varchar(255) DEFAULT NULL,
 `username` varchar(255) DEFAULT NULL,
 PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
 