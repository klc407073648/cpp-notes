# 使用Docker搭建Redis服务

[[toc]]

## 参考资料

* [Docker 安装 Redis 容器](https://blog.csdn.net/qq_24958783/article/details/107541425?spm=1001.2014.3001.5501)

## 获取Redis镜像

```bash
docker pull redis 
```

**检查是否拉取成功**

```bash
[root@VM-0-10-centos project]# docker images |grep redis
docker.io/redis             latest              739b59b96069        12 days ago         105 MB
```

**创建Redis容器并启动**

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