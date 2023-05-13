# Tars - Docker部署

> 用于记录Tars Docker部署的内容。

[[toc]]

## 参考资料

* [TarsDocker部署](https://tarscloud.gitbook.io/tarsdocs/rumen/installation/docker)


## 创建 docker 虚拟网络

```
docker network create -d bridge --subnet=172.25.0.0/16 --gateway=172.25.0.1 tars
```

# 启动 MySQL

```
docker run -d -p 3306:3306 \
    --net=tars \
    -e MYSQL_ROOT_PASSWORD="123456" \
    --ip="172.25.0.2" \
    -v /data/framework-mysql:/var/lib/mysql \
    -v /etc/localtime:/etc/localtime \
    --name=tars-mysql \
    mysql:5.7
```

进入容器，执行以下命令：

```
mysql_upgrade -uroot -p --force
```

## 编译服务

```
cd ./HelloServer/build/
cmake ..
make -j4
```

## 服务实现

```
cd build
cmake ..
make -j4
make HelloServer-tar
make HelloServer-upload
```

重新make cleanall;make;make tar，会重新生成HelloServer.tgz发布包。

# 使用 tarscloud/framework 部署框架

```
docker run -d \
    --name=tars-framework \
    --net=tars \
    -e MYSQL_HOST="172.25.0.2" \
    -e MYSQL_ROOT_PASSWORD="123456" \
    -e MYSQL_USER=root \
    -e MYSQL_PORT=3306 \
    -e REBUILD=false \
    -e INET=eth0 \
    -e SLAVE=false \
    --ip="172.25.0.3" \
    -v /data/framework:/data/tars \
    -v /etc/localtime:/etc/localtime \
    -p 3000:3000 \
    -p 3001:3001 \
    tarscloud/framework:latest
```

# Docker 部署 Tars 应用节点

```
docker run -d \
    --name=tars-node \
    --net=tars \
    -e INET=eth0 \
    -e WEB_HOST="http://172.25.0.3:3000" \
    --ip="172.25.0.5" \
    -v /data/tars:/data/tars \
    -v /etc/localtime:/etc/localtime \
    -p 9000-9010:9000-9010 \
    tarscloud/tars-node:latest
```



备注：

```
阿里云 安全组设置
https://blog.csdn.net/m0_37383866/article/details/104387736

systemctl stop firewalld.service

vim /etc/ssh/ssh_config
systemctl restart sshd
编辑 /etc/ssh/ssh_config，找到 GSSAPIAuthentication no 这行，删掉前面的注释，然后保存退出
```

