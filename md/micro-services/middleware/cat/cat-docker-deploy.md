# Cat - Docker快速部署

[[toc]]

## 说明

1. 支持本机模式快速部署。
2. docker/Dockerfile包含CAT依赖的环境，可以作为源码部署的参考。
3. 默认的运行方式是集成了一个mysql镜像，可以修改为自己的mysql的详细配置。默认运行的mysql服务，将mysql数据挂载到了`docker/mysql/volume`中。

## 容器构建

```bash
cd docker
docker-compose up -d
```

## 依赖配置说明

1. datasources.xml
    - CAT数据库配置，默认配置是mysql镜像，可以按需替换
2. docker-compose.yml
    - 通过docker-compose启动的编排文件，文件中包含cat和mysql。可以屏蔽掉mysql的部分，并且修改cat的环境变量，改为真实的mysql连接信息。
3. client.xml
    - CAT 初始化默认的路由列表，配置此文件可以将客户端数据上报指向到不同环境。
4. datasources.sh
    - 辅助脚本，脚本作用时修改`datasources.xml`，使用环境变量中制定的mysql连接信息。（通过sed命令替换）

## 访问

访问：
url：http://ip:8080/cat
config：用户：admin 密码：admin

![cat界面](/_images/micro-services/middleware/cat/server/cat界面.png)

### 修改配置

**修改服务端配置**

http://139.196.82.84:8080/cat/s/config?op=serverConfigUpdate

修改服务端配置，将127.0.0.1修改为139.196.82.84

![服务端配置](/_images/micro-services/middleware/cat/server/服务端配置.png)

**修改客户端路由配置**

http://139.196.82.84:8080/cat/s/config?op=routerConfigUpdate

修改客户端路由配置，将127.0.0.1修改为139.196.82.84

![客户端路由配置](/_images/micro-services/middleware/cat/server/客户端路由配置.png)

## cpp客户端使用

![Event输出](/_images/micro-services/middleware/cat/server/Event输出.png)

https://blog.csdn.net/chentravelling/article/details/84614743

遗留时间不同步问题，无法解决