# Consul - 学习内容

> 本节主要介绍Consul注册中心学习的内容。

[[toc]]

# 参考

> - [Consul：12:使用容器方式构建Consul集群](https://blog.csdn.net/liumiaocn/article/details/104636827)
> - [consul 集群](https://www.cnblogs.com/xiaohanlin/p/8016803.html)
> - [官网](https://www.consul.io/)
> - [Consul集群的安装与部署 ](https://www.cnblogs.com/liyuanhong/articles/14600711.html)
> - [docker-compose启动consul](https://www.cnblogs.com/brady-wang/p/14440649.html)
> - [使用Docker-Compose搭建consul集群环境](https://blog.csdn.net/m0_56444183/article/details/121717456)
> - [服务发现 - consul 的介绍、部署和使用](https://blog.csdn.net/buxiaoxia/article/details/69788114)
> - [c++ consul库](https://github.com/oliora/ppconsul )
>

# 基础学习

```
#启动Consul服务
#使用如下命令，使用Consul官方镜像以开发模式启动Consul服务，将Consul web UI端口映射出来给用户提供访问。
docker run -d --name=agent1 -p 8500:8500 consul:1.7.1 agent -dev -client=0.0.0.0 -bind=0.0.0.0
#获取Consul容器的IP
docker exec -t agent1 consul members
#加入新的节点：agent2
docker run -d --name agent2 consul agent -dev -bind=0.0.0.0 -join=172.17.0.3
#加入新的节点：agent3
docker run -d --name agent3 consul agent -dev -bind=0.0.0.0 -join=172.17.0.3

docker exec -t agent2 consul members
```

查看agent1:

```
[root@VM-16-6-centos home]# docker ps |grep agent1
7ab7834bf646   consul:1.7.1          "docker-entrypoint.s…"   26 minutes ago   Up 21 minutes   8300-8302/tcp, 8301-8302/udp, 8600/tcp, 8600/udp, 0.0.0.0:8500->8500/tcp, :::8500->8500/tcp   agent1
```

# consul C++库学习

使用conan管理依赖包

 git clone git@github.com:oliora/ppconsul.git

```
git submodule add https://github.com/oliora/ppconsul.git
```

yum install -y conan

```bash
# Install dependencies
conan install .

# Make workspace directory
mkdir workspace
cd workspace

# Configure:
cmake ..

#Build
cmake --build . --config Release

# Install
cmake --build . --config Release --target install
```
