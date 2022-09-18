-- A. 查询建表语句 --- 默认存储引擎: InnoDB
show create table time_zone;

CREATE TABLE `time_zone` (
  `Time_zone_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Use_leap_seconds` enum('Y','N') NOT NULL DEFAULT 'N',
  PRIMARY KEY (`Time_zone_id`)
) ENGINE=InnoDB AUTO_INCREMENT=1827 DEFAULT CHARSET=utf8 STATS_PERSISTENT=0 COMMENT='Time zones' |

-- 我们可以看到，创建表时，即使我们没有指定存储引擎，数据库也会自动选择默认的存储引擎。

-- B. 创建表 my_myisam , 并指定MyISAM存储引擎

create table my_myisam(
	id int,
	name varchar(10)
) engine = MyISAM ;

-- C. 创建表 my_memory , 指定Memory存储引擎

create table my_memory(
	id int,
	name varchar(10)
) engine = Memory ;
