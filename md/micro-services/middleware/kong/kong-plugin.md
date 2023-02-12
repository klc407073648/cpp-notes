# Kong - Konga 插件使用

[[toc]]

# 身份认证插件

## Basic-Auth验证

1、通过以下请求在服务上配置这个插件：

```js
curl -X POST http://localhost:8001/services/demo/plugins \
    --data "name=basic-auth"  \
    --data "config.hide_credentials=true"
```

2、在路由上启用插件：

```js
curl -X POST http://localhost:8001/routes/demoroute/plugins \
    --data "name=basic-auth"  \masu
    --data "config.hide_credentials=true"
```

3.添加玩上述插件后，直接访问，提示无鉴权：

 ![basic-auth-1](/_images/micro-services/middleware/kong/basic-auth-1.png)

4.创建用户并设置凭证：

 ![create_consumer](/_images/micro-services/middleware/kong/create_consumer.png)

设置凭证如下：

![create_credentials](/_images/micro-services/middleware/kong/create_credentials.png)

6. 使用凭证进行访问：

 ![basic-auth-2](/_images/micro-services/middleware/kong/basic-auth-2.png)

对应HTTP报文：

```
GET / HTTP/1.1
Host: 139.196.82.84:9950
Connection: keep-alive
X-Forwarded-For: 183.208.23.168
X-Forwarded-Proto: http
X-Forwarded-Host: 139.196.82.84
X-Forwarded-Port: 8000
X-Forwarded-Path: /demo
X-Forwarded-Prefix: /demo
X-Real-IP: 183.208.23.168
name: test-basic-auth
User-Agent: PostmanRuntime/7.26.8
Accept: */*
Postman-Token: e997b328-9755-4fd8-ade3-c64c1d746186
Accept-Encoding: gzip, deflate, br
X-Consumer-ID: b07d5dfc-8112-465a-aaab-760ab0b2e7db
X-Consumer-Username: test-basic-auth
X-Credential-Identifier: test
X-Credential-Username: test
```

# 限流配置

Kong 提供了 Rate Limiting插件，实现对请求的**限流**功能，避免过大的请求量，将后端服务击垮。

1、在服务上启用插件，设置每秒最多访问5次

```kotlin
$ curl -X POST http://localhost:8001/services/demo/plugins \
    --data "name=rate-limiting"  \
    --data "config.second=5" \
    --data "config.hour=10000"
```

2、在路由上启用插件

```kotlin
$ curl -X POST http://localhost:8001/routes/demoroute/plugins \
    --data "name=rate-limiting"  \
    --data "config.second=5" \
    --data "config.hour=10000"
```

3、在消费者中启用插件

```kotlin
$ curl -X POST http://localhost:8001/routes/demoroute/plugins \
    --data "name=rate-limiting" \
    --data "consumer_id={consumer_id}"  \
    --data "config.second=5" \
    --data "config.hour=10000"
```

4、在API上启用插件

```kotlin
$ curl -X POST http://kong:8001/apis/{api}/plugins \
    --data "name=rate-limiting"  \
    --data "config.second=5" \
    --data "config.hour=10000"
```

备注：

* config.second ：开发人员每秒可以生成的HTTP请求量。
* config.hour：开发人员每小时可以生成的HTTP请求量。
* config.limit_by : 汇总限额时将使用的实体:`consumer`( 默认 ), `credential`, `ip`
* config.policy ： 用于检索和增加限制的限速策略。`local`,`cluster`,`redis`
* config.hide_client_headers : 隐藏头信息。默认：false
* 如果`config.policy`选了`redis`则需要配置：`config.redis_host`，`config.redis_port`，`config.redis_password`，`config.redis_timeout`，`config.redis_database`

不断访问，提示API频率超过限制：

 ![rate-limiting-1](/_images/micro-services/middleware/kong/rate-limiting-1.png)

# 黑白名单限制

1.服务配置插件

```
curl -X POST http://localhost:8001/services/demo/plugins \
    --data "name=ip-restriction"  \
    --data "config.whitelist=192.168.32.84"
```

2.路由配置插件(暂时不可用)

```
curl -X POST http://localhost:8001/routes/b93e5045-2006-4812-925c-70619fc4bcb1/plugins \
    --data "name=ip-restriction"  \
    --data "config.whitelist=192.168.32.84"
```

3.设置后访问

 ![ip-restriction-1](/_images/micro-services/middleware/kong/ip-restriction-1.png)

4.删除限制后，可以正常访问