-- 命令集中文待解决
-- ALTER TABLE `user` DEFAULT CHARACTER SET utf8;

-- -----------------------------------------------------
-- Database testuser
-- -----------------------------------------------------
use testuser;

-- 初始化数据
INSERT INTO `user` VALUES ('admin', 1, 'admin', 'https://636f-codenav-8grj8px727565176-1256524210.tcb.qcloud.la/img/logo.png', 0, '1a5914a939243dd0fa3556679abca904', '', 'admin@qq.com', 0, '2022-7-9 01:25:44', '2022-7-9 01:34:20', 0, 0, '1001', '[\"c++\",\"python\"]', 'I am admin');
INSERT INTO `user` VALUES ('testuser', 2, 'testuser', 'https://636f-codenav-8grj8px727565176-https://fastly.jsdelivr.net/npm/@vant/assets/weapp.svg', 0, '1a5914a939243dd0fa3556679abca904', '', 'testuser@qq.com', 0, '2022-7-9 01:26:46', '2022-7-9 01:34:21', 0, 0, '1002', '[\"c++\",\"python\"]', 'I am testuser');
INSERT INTO `user` VALUES ('klcadmin', 3, 'klcadmin', 'https://fastly.jsdelivr.net/npm/@vant/assets/github.svg', 1, '1a5914a939243dd0fa3556679abca904', '', 'klcadmin@qq.com', 0, '2022-7-9 01:27:06', '2022-7-9 01:34:22', 0, 1, '1003', '[\"c++\",\"python\"]', 'I am klcadmin');
INSERT INTO `user` VALUES ('testadmin', 4, 'testadmin', 'https://fastly.jsdelivr.net/npm/@vant/assets/logo.png', 1, '1a5914a939243dd0fa3556679abca904', '', 'testadmin@qq.com', 0, '2022-7-9 01:27:48', '2022-7-9 01:34:25', 0, 1, '1004', '[\"c++\",\"python\"]', 'I am testadmin');

