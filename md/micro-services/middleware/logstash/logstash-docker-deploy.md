# Logstash - docker部署

[[toc]]

# 内存

注意Logstash的版本，需要与Elasticsearch, Kibana版本统一，这里是下载7.2.0版本的镜像

**1.下载镜像**

```
docker pull logstash:7.2.0
```

**2.获取原始的配置信息**

```
[root@iZuf61kbf845xt6tz10abgZ logstash]# docker run -d  -p 5044:5044 --name logstash docker.io/logstash:7.2.0
9fba0cd4d460b6023975e0fd059d3e3e8b67f0745f516a694a48876d2263d051
[root@iZuf61kbf845xt6tz10abgZ logstash]# docker cp logstash:/usr/share/logstash/config  ./tmp/
[root@iZuf61kbf845xt6tz10abgZ logstash]# docker cp logstash:/usr/share/logstash/pipeline  ./tmp/
```

**3.修改配置文件logstash.conf**：

配置文件目录结构：

```
[root@iZuf61kbf845xt6tz10abgZ test]# tree
.
├── build_logstash.sh
├── config
│   ├── jvm.options
│   ├── logstash.conf
│   ├── logstash.yml
│   └── pipelines.yml
├── data
│   └── test.log
├── docker-compose.yml
└── pipeline
    └── gitkeep
```

logstash.conf文件内容：

```
input {
	file{
		path => "/usr/share/logstash/data/test.log"
		codec => json
		start_position => "beginning"
	}
}
output {
	stdout {
        codec => rubydebug
    }
}
```

**4.执行启动脚本build_logstash.sh**

主要完成文件赋权和docker容器启动：

```
#/bin/bash

chmod 777 -R ./pipeline/
chmod 777 -R ./data/
chmod 777 -R ./config/

docker-compose up -d
```

**5.启动容器，并向test.log输入信息**

```
[root@iZuf61kbf845xt6tz10abgZ test]# cd /home/logstash/test/data/
[root@iZuf61kbf845xt6tz10abgZ data]# echo "hello world" >> test.log
[root@iZuf61kbf845xt6tz10abgZ data]# echo "logstash use test" >> test.log
```

**6.另外启动一个窗口查看打印信息**

```
docker logs -f --tail=200 stibel_logstash

/base_formatter.rb:31: warning: constant ::Fixnum is deprecated
{
          "path" => "/usr/share/logstash/data/test.log",
       "message" => "hello world",
      "@version" => "1",
    "@timestamp" => 2022-04-05T06:55:07.791Z,
          "host" => "6dc97085cbff",
          "tags" => [
        [0] "_jsonparsefailure"
    ]
}

[DEBUG] 2022-04-05 06:55:53.946 [[main]<file] sincedbcollection - writing sincedb (delta since last write = 46)
{
          "path" => "/usr/share/logstash/data/test.log",
       "message" => "logstash use test",
      "@version" => "1",
    "@timestamp" => 2022-04-05T06:55:53.938Z,
          "host" => "6dc97085cbff",
          "tags" => [
        [0] "_jsonparsefailure"
    ]
}
```

