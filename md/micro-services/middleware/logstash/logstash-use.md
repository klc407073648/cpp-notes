# Logstash - 实践

# 手动构建镜像

参考文档：

```
https://www.cnblogs.com/network-ren/p/12377162.html
https://www.cnblogs.com/caoweixiong/p/11791396.html
https://blog.csdn.net/weixin_43702146/article/details/120215807
https://elasticstack.blog.csdn.net/article/details/123730315
```

1. 启动构建容器

```
docker run -it -d --name logstash_test centos:centos7
57153ee028ea93303f9c14a313d2d7137828d0eab0ca355844ce19264266a331
```

2. 拷贝所需源文件

```
docker cp /home/logstash/logstash-7.1.0.tar.gz  logstash_test:/home
docker cp /home/logstash/jdk-8u221-linux-x64.tar.gz  logstash_test:/home
docker exec -it  logstash_test bash
```

3. 进入容器，设置jdk环境变量

```
docker exec -it  logstash_test bash

[root@57153ee028ea /]# cp /home/jdk-8u221-linux-x64.tar.gz  /usr/local/
[root@57153ee028ea /]# cd /usr/local/
[root@57153ee028ea local]# tar -zxvf jdk-8u221-linux-x64.tar.gz


echo 'export JAVA_HOME=/usr/local/jdk1.8.0_221' >> /etc/profile
echo 'export JRE_HOME=$JAVA_HOME/jre'	 >> /etc/profile
echo 'export CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar' >> /etc/profile
echo 'export PATH=$PATH:$JAVA_HOME/bin:$JRE_HOME/bin'	>> /etc/profile
source /etc/profile

[root@57153ee028ea local]# java -version
java version "1.8.0_221"
Java(TM) SE Runtime Environment (build 1.8.0_221-b11)
Java HotSpot(TM) 64-Bit Server VM (build 25.221-b11, mixed mode)
```

4. 使用logstash

```
[root@57153ee028ea home]# mkdir -p /home/logstash
[root@57153ee028ea home]# cd /home/logstash
[root@57153ee028ea logstash]# tar -zxvf logstash-7.1.0.tar.gz
[root@57153ee028ea logstash]# wget https://artifacts.elastic.co/downloads/logstash/logstash-7.1.0.tar.gz


[root@57153ee028ea logstash-7.1.0]# ./bin/logstash -e 'input { stdin { } } output { stdout {} }'
hello world

/home/logstash/logstash-7.1.0/vendor/bundle/jruby/2.5.0/gems/awesome_print-1.7.0/lib/awesome_print/formatters/base_formatter.rb:31: warning: constant ::Fixnum is deprecated
{
    "@timestamp" => 2022-04-05T23:29:09.146Z,
       "message" => "hello world",
      "@version" => "1",
          "host" => "57153ee028ea"
}
```

# 各种配置文件使用

## 输入

### 标准输入stdin

执行命令：

```
./bin/logstash -f stdin.conf
```

输出结果：

```
{
    "@timestamp" => 2022-04-05T23:29:09.146Z,
       "message" => "hello world",
      "@version" => "1",
          "host" => "57153ee028ea"
}
```

### file

执行命令：

```
./bin/logstash -f file.conf
```

输出结果：

```
{
          "host" => "935775b11580",
          "path" => "/home/logstash/log/mylog.log",
      "@version" => "1",
    "@timestamp" => 2022-04-08T12:48:47.875Z,
       "message" => "[2021-03-13 20:58:54:425 - ERROR](Register):mysql->getErrno(): 0 ,mysql->getErrStr(): "
}
{
          "host" => "935775b11580",
          "path" => "/home/logstash/log/mylog.log",
      "@version" => "1",
    "@timestamp" => 2022-04-08T12:48:47.875Z,
       "message" => "[2021-03-13 20:58:54:425 - DEBUG](Register):reg end"
}

```

### tcp

执行命令：

```
./bin/logstash -f tcp.conf
```

输出结果：

```
在另外一个窗口进入容器执行
[root@935775b11580 /]# echo "test tcp" >> olddata
[root@935775b11580 /]# yum install -y nc
[root@935775b11580 /]# nc 127.0.0.1 8888 < olddata

可以看到当前执行日志:
{
    "@timestamp" => 2022-04-07T13:59:58.370Z,
       "message" => "test tcp",
          "host" => "935775b11580",
      "@version" => "1",
          "port" => 55752
}
```

## 过滤

### grok

```
grok_simple.conf
#172.16.213.135 [07/Apr/2022:22:08:00 +0800] "PUT / HTTP/1.1" 403 5059
{
       "message" => "172.16.213.135 [07/Feb/2022:22:08:00 +0800] \"PUT / HTTP/1.1\" 403 5059",
      "clientip" => "172.16.213.135",
         "bytes" => "5059",
      "response" => "403",
     "timestamp" => "07/Feb/2022:22:08:00 +0800",
    "@timestamp" => 2022-04-07T14:24:03.965Z,
      "referrer" => "\"PUT / HTTP/1.1\"",
          "host" => "935775b11580",
      "@version" => "1"
}

grok.conf
172.16.213.135 [09/Feb/2022:22:08:00 +0800] "PUT / HTTP/1.1" 403 5059
{
           "bytes" => 5059.0,
    "new_response" => "403",
        "@version" => "1",
        "referrer" => "PUT / HTTP/1.1",
      "@timestamp" => 2022-02-09T14:08:00.000Z,
        "clientip" => [
        [0] "172",
        [1] "16",
        [2] "213",
        [3] "135"
    ],
       "timestamp" => "09/Feb/2022:22:08:00 +0800"
}
```

## 输出

### elasticsearch

执行命令：

```
./bin/logstash -f elasticsearch.conf
```

在kibana上查询

````
GET /logstash-2022.04.06-000001/_search
{
  "query": {
    "match_all": {}
  }
}
````

结果：

```
{
  "took" : 1,
  "timed_out" : false,
  "_shards" : {
    "total" : 1,
    "successful" : 1,
    "skipped" : 0,
    "failed" : 0
  },
  "hits" : {
    "total" : {
      "value" : 98,
      "relation" : "eq"
    },
    "max_score" : 1.0,
    "hits" : [
      {
        "_index" : "logstash-2022.04.06-000001",
        "_type" : "_doc",
        "_id" : "xC0sAYABWrTNO53xT2bh",
        "_score" : 1.0,
        "_source" : {
          "host" : "935775b11580",
          "@timestamp" : "2022-04-06T23:18:42.528Z",
          "message" : "[2021-03-13 20:57:32:634 - INFO](Login):LoggerManager created, name is Login",
          "@version" : "1",
          "path" : "/home/logstash/log/mylog.log"
        }
      },
```

### output

```
./bin/logstash -f ./file.conf --path.data=/home/logstash/log

[root@935775b11580 log]# cd /home/logstash/log/
[root@935775b11580 log]# cd ./2022-04-07/935775b11580_23.log
```

# 脚本制作docker镜像
```
[root@iZuf61kbf845xt6tz10abgZ logstash]# ./build_logstash.sh
[root@iZuf61kbf845xt6tz10abgZ logstash]# docker images
REPOSITORY                                    TAG                 IMAGE ID            CREATED             SIZE
docker.io/klc407073648/stibel-logstash        latest              c846fc9d99c0        4 minutes ago       1.08 GB


[root@iZuf61kbf845xt6tz10abgZ logstash]# docker tag c846fc9d99c0  docker.io/klc407073648/stibel-logstash:v1.0
[root@iZuf61kbf845xt6tz10abgZ logstash]# docker push  docker.io/klc407073648/stibel-logstash:v1.0  The push refers to a repository [docker.io/klc407073648/stibel-logstash]
```

# 将MySQL数据同步给Elasticsearch

sql_last_value 是取上次查到的数据的最后一行的指定的字段，如果要全量更新，只要删除掉

E:\software\ElasticStack\logstash-7.17.9\data\plugins\inputs\jdbc\logstash_jdbc_last_run文件即可（这个文件存储了上次同步到的数据）

注意查询浯句中要按updateTime排序，保证最后一条是最大的

字段变小写，通过rename修正

不需要的字段，可以remove_field删除

```
input{
	jdbc{
	jdbc_driver_library => "E:\softwar\mysql-connector-java-8.0.29.jar"
	jdbc_driver_class => "com.mysql.jdbc.Driver"
	jdbc_connection_string => "jdbc:mysql://localhost:3306/my_db"
	jdbc_user => "root"
	jdbc_password => "123456"
	statement=>"SELECT * from post where updateTime > :sql_lastvalue and updateTime < now() order by updateTime desc"
	tracking_column => "updatetime"
	tracking_column_type => "timestamp"
	use_column_va1ue => true
	parameters => { "favoriteartist" => "Beethoven" }
	schedule => "*/5 * * * * *"
	jdbc_default_timezone=>"Asia/Shanghai"
	}
}

filter {
    mutate {
        rename => {
            "updatetime" => "updateTime"
            "userid" => "userId"
            "createtime" => "createTime"
            "isdelete" => "isDelete"
        }
        remove_field => ["thumbnum","favournum"]
    }
}

output{
	stdout{ codec=>rubydebug }

  elasticsearch {
    host => "127.0.0.1:9200"
    index => "post_v1"
    document_id => "%{id}"
  }
}
```
