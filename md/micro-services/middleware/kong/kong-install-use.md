# Kong - 安装与使用

[[toc]]

# Kong的安装过程

1 . 创建docker 虚拟网络

```shell script
docker network create kong-net
```

2.运行postgresql 的数据库

```shell script
docker run -d --name kong-database \
               --network=kong-net \
               -p 5432:5432 \
               -e "POSTGRES_USER=kong" \
               -e "POSTGRES_DB=kong" \
               -e "POSTGRES_PASSWORD=kong" \
               postgres:9.6
```

3 . 初始化数据库（迁移数据）

```shell script
docker run --rm \
     --network=kong-net \
     -e "KONG_DATABASE=postgres" \
     -e "KONG_PG_HOST=kong-database" \
     -e "KONG_PG_USER=kong" \
     -e "KONG_PG_PASSWORD=kong" \
     -e "KONG_CASSANDRA_CONTACT_POINTS=kong-database" \
     kong:latest kong migrations bootstrap
```

4 . 运行kong

```shell script
docker run -d --name kong \
     --network=kong-net \
     -e "KONG_DATABASE=postgres" \
     -e "KONG_PG_HOST=kong-database" \
     -e "KONG_PG_USER=kong" \
     -e "KONG_PG_PASSWORD=kong" \
     -e "KONG_CASSANDRA_CONTACT_POINTS=kong-database" \
     -e "KONG_PROXY_ACCESS_LOG=/dev/stdout" \
     -e "KONG_ADMIN_ACCESS_LOG=/dev/stdout" \
     -e "KONG_PROXY_ERROR_LOG=/dev/stderr" \
     -e "KONG_ADMIN_ERROR_LOG=/dev/stderr" \
     -e "KONG_ADMIN_LISTEN=0.0.0.0:8001, 0.0.0.0:8444 ssl" \
     -p 8000:8000 \
     -p 8443:8443 \
     -p 8001:8001 \
     -p 8444:8444 \
     kong:latest
```

Kong 默认监听的端口

- **8000** ： 监听来自客户端的`HTTP` 流量，转发到你的 `upstream` 服务上
- **8443** ： 监听`HTTPS`的流量，功能跟 `8000`一样，可以通过配置文件禁止。
- **8001** ： `kong`的`HTTP`监听的 admin api 管理接口
- **8444** ： `kong`的`HTTPS`监听的 admin api 管理接口

5 . 验证是否安装成功

```shell script
curl -i http://localhost:8001/
```

返回下面内容，表示安装成功，可以正常使用：

```
[root@iZuf61kbf845xt6tz10abgZ ~]# curl -i http://localhost:8001/
HTTP/1.1 200 OK
Date: Mon, 28 Mar 2022 23:06:40 GMT
Content-Type: application/json; charset=utf-8
Connection: keep-alive
Access-Control-Allow-Origin: *
Content-Length: 11040
X-Kong-Admin-Latency: 1
Server: kong/2.8.0
```

# 安装 kong 管理UI

konga带来的一个最大的便利就是可以很好地通过UI观察到现在kong的所有的配置，并且可以对于管理kong节点情况进行查看、监控和预警，konga主要特性如下：

- 多用户管理
- 管理多个Kong节点
- 电子邮件异常信息通知
- 管理所有Kong Admin API
- 使用快照备份，还原和迁移Kong节点
- 使用运行状况检查监控节点和API状态
- 轻松的数据库集成（MySQL，postgresSQL，MongoDB）

Konga支持PostgreSQL数据库，定义挂载卷konga-postgresql

```
docker volume create konga-postgresql
```

创建konga的数据库:
```
docker run -d --name konga-database \
               --network=kong-net \
               -v konga-postgresql:/var/lib/postgresql/data \
               -p 5433:5432 \
               -e "POSTGRES_USER=konga" \
               -e "POSTGRES_DB=konga" \
               -e "POSTGRES_PASSWORD=konga" \
               postgres:9.6
```

初始化数据库:
```
docker run --rm pantsel/konga:latest -c prepare -a postgres -u postgres://konga:konga@139.196.82.84:5433/konga
```

启动konga:

```shell script
docker run -p 1337:1337 \
             --network=kong-net \
             -e "DB_ADAPTER=postgres" \
             -e "DB_URI=postgres://konga:konga@konga-database:5432/konga" \
             -e "NODE_ENV=production" \
             -e "DB_PASSWORD=konga" \
             --name konga \
             pantsel/konga
```

# 创建konga和kong的连接关系

1.创建账号，并登陆：

 ![konga登陆](/_images/micro-services/middleware/kong/konga登陆.png)

2.对应konga数据库也能看到对应记录

 ![konga数据库记录](/_images/micro-services/middleware/kong/konga数据库记录.png)

3.konga创建与kong的连接：

 ![konga创建连接](/_images/micro-services/middleware/kong/konga创建连接.png)

# Kong的快速使用

## 动态负载均衡实现

典型的nginx的配置文件

```
upstream demoupstream {
        server localhost:9950 weight=100;
}
server {
        listen 8000;
        location /demo {
                proxy_pass http://demoupstream;
        }
}
```

上面的简单`Nginx`配置，可以转为如下**kong 配置**

1 . **配置 Upstream**

```awk
curl -X POST http://localhost:8001/upstreams --data "name=demoupstream"
```

2 . **配置 target**

```awk
curl -X POST http://localhost:8001/upstreams/demoupstream/targets --data "target=139.196.82.84:9950" --data "weight=100"
curl -X POST http://localhost:8001/upstreams/demoupstream/targets --data "target=139.196.82.84:4300" --data "weight=100"
```

3 . **配置 service**

```jboss-cli
curl -X POST http://localhost:8001/services --data "name=demo" --data "host=demoupstream" --data "path=/"
```

4 . **配置 route**

```awk
curl -X POST http://localhost:8001/services/demo/routes --data "name=demoroute" --data "paths[]=/demo"
```

5 . **验证**

```vim
curl -i http://localhost:8000/demo
```

输出结果:

```
[root@iZuf61kbf845xt6tz10abgZ ~]# curl -i http://localhost:8000/demo
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 31
Connection: keep-alive
Access-Control-Allow-Origin: *
X-Kong-Upstream-Latency: 5
X-Kong-Proxy-Latency: 1
Via: kong/2.8.0

{"method":"get","recvInfo":""}
```

postman验证1：

 ![postman验证1](/_images/micro-services/middleware/kong/postman验证1.png)

postman验证2：

特别注意:curl -X POST http://localhost:8001/services --data "name=demo" --data "host=demoupstream" --data "path=/"

对应konga的默认配置

```
Path	/
The path to be used in requests to the upstream server. Empty by default.
```

 ![postman验证2](/_images/micro-services/middleware/kong/postman验证2.png)

postman验证3：

 ![postman验证3](/_images/micro-services/middleware/kong/postman验证3.png)

