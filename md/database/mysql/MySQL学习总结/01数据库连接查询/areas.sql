create table areas(
    aid varchar(30) not null primary key, 
    title varchar(30), 
    pid varchar(30)
);


INSERT INTO `areas` VALUES ('1', '浙江省', 'null');
INSERT INTO `areas` VALUES ('2', '江苏省', 'null');
INSERT INTO `areas` VALUES ('3', '杭州市', '1');
INSERT INTO `areas` VALUES ('4', '温州市', '1');
INSERT INTO `areas` VALUES ('5', '南京市', '2');
INSERT INTO `areas` VALUES ('6', '苏州市', '2');
