CREATE TABLE `student` (
  `id` int(11) NOT NULL,
  `name` varchar(30) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `sex` enum('man','woman') DEFAULT NULL,
  `class` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
);

INSERT INTO `student` VALUES (1001, 'Jason', 25, 'man', 1);
INSERT INTO `student` VALUES (1002, 'Helen', 25, 'woman', 3);
INSERT INTO `student` VALUES (1003, 'Steve', 27, 'man', 5);
INSERT INTO `student` VALUES (1004, 'Hanna', 25, 'woman', 1);
INSERT INTO `student` VALUES (1005, 'Bob', 26, 'man', 3);
INSERT INTO `student` VALUES (1006, 'John', 28, 'man', 7);
INSERT INTO `student` VALUES (1007, 'Walln', 25, 'woman', 8);
