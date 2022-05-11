# Redis学习总结

* [Redis基本数据类型以及应用](./基本数据类型以及应用.md)
* [Redis持久化](./持久化.md)
* [Redis事务操作](./事务操作.md)
* [Redis删除策略](./删除策略.md)
* [Redis主从复制](./主从复制.md)
* [Redis哨兵模式](./哨兵模式.md)
* [Redis集群概念以及应用](./集群概念以及应用.md)
* [Redis企业级解决方案](./企业级解决方案.md)



docker容器搭建：

```
[root@iZuf61kbf845xt6tz10abgZ ~]# docker pull redis
[root@iZuf61kbf845xt6tz10abgZ ~]# docker run --name my-redis -p 6379:6379 -v /home/klc/code/redis/data:/data -d redis redis-server --appendonly yes
aea54a6820a6361e831352ed67a76535e6d8d69aeb0bcd255b0756d88de59929
[root@iZuf61kbf845xt6tz10abgZ ~]#
[root@iZuf61kbf845xt6tz10abgZ ~]# docker ps -a
CONTAINER ID        IMAGE                        COMMAND                  CREATED             STATUS              PORTS                                                                                                                                                             NAMES
aea54a6820a6        redis                        "docker-entrypoint..."   18 seconds ago      Up 17 seconds       0.0.0.0:6379->6379/tcp                                                                                                                                            my-redis
[root@iZuf61kbf845xt6tz10abgZ ~]# docker exec -it aea54a6820a6 bash

```



学习文档：

[redis官网](https://redis.io/)

