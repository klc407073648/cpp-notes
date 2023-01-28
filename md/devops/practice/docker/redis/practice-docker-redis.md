# Docker实践 - redis容器搭建

[[toc]]

# 参考资料

* [docker 创建redis容器以及redis命令笔记 ](https://www.cnblogs.com/jinit/p/13739191.html)

# 基础使用

**1. 获取Redis镜像**

```bash
docker pull redis 
```

**2. 检查是否拉取成功**

```bash
[root@VM-0-10-centos project]# docker images |grep redis
docker.io/redis             latest              739b59b96069        12 days ago         105 MB
```

**3. 创建Redis容器并启动**

```bash
sudo docker run -itd --name redis1 -p 6390:6379 -v /home/project/mydata/redis/data:/data --restart always redis --appendonly yes --requirepass "123456"


[root@VM-0-10-centos project]# docker exec -it  redis1 bash
root@199f32c349fb:/data#
root@199f32c349fb:/data#
root@199f32c349fb:/data# redis-cli
127.0.0.1:6379> get name
(error) NOAUTH Authentication required.
127.0.0.1:6379> auth 123456
OK
127.0.0.1:6379> get name
(nil)
127.0.0.1:6379>
```

**详细说明：**
```
-d   -> 以守护进程的方式启动容器
-p 6390:6379      -> 绑定宿主机端口，6390宿主机端口，6379 容器端口
--name redis1      -> 指定容器名称
--restart always     -> 开机启动
--privileged=true     -> 提升容器内权限
--requirepass      -> 设置登录密码
-v /home/project/mydata/redis/data:/data -> 映射数据目录
--appendonly yes     -> 开启数据持久化
```

以文件启动：
```
[root@VM-0-10-centos project]# docker run -itd --name redis -p 6390:6379 --restart unless-stopped -v /home/project/mydata/redis/data:/data -v /home/project/mydata/redis/conf/redis.conf:/etc/redis/redis.conf  -d redis redis-server /etc/redis/redis.conf
```

# docker-compose方式启动

```lua
.
|-- build_redis.sh  -- 构建脚本
|-- data
|   `-- 6379.log
|-- docker-compose.yml
|-- environment   -- 环境信息
|   |-- conf
|   |   |-- redis-6379.conf
|   |   |-- redis.conf
|   |   `-- redis-simple.conf
|   |-- Dockerfile
|   `-- redis.env
`-- practice-docker-redis.md

```

## 实践

```
[root@VM-0-10-centos Redis]# ./build_redis.sh
[root@VM-0-10-centos Redis]# docker ps -a
CONTAINER ID        IMAGE                                      COMMAND                  CREATED             STATUS              PORTS                               NAMES
b1298edf0d30        docker.io/klc407073648/docker-redis:v1.0   "docker-entrypoint..."   10 minutes ago      Up 10 minutes       0.0.0.0:6380->6379/tcp              docker-redis
2c2b44463303        docker.io/klc407073648/docker-mysql:v1.0   "docker-entrypoint..."   41 minutes ago      Up 41 minutes       33060/tcp, 0.0.0.0:3307->3306/tcp   docker-mysql
80dd79144bf6        elasticsearch:7.12.1                       "/bin/tini -- /usr..."   2 months ago        Up 2 months         0.0.0.0:9200->9200/tcp, 9300/tcp    es01
[root@VM-0-10-centos Redis]# docker exec -it b1298edf0d30 bash
root@b1298edf0d30:/data# redis-cli
127.0.0.1:6379> keys *
(error) NOAUTH Authentication required.

```

解决方法：

1:命令行模式下，auth输入
```
root@b1298edf0d30:/data#  ./redis-cli
127.0.0.1:6379> auth 123456
OK
127.0.0.1:6379> keys *
1) "name"
127.0.0.1:6379> set num 44444
OK
127.0.0.1:6379>
```

2:输入redis-cli时，带指定参数
```
root@b1298edf0d30:/data# 
redis-cli -h 127.0.0.1 -p 6379 -a 123456
```