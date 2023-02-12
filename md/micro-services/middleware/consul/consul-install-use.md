# Consul - 安装与使用

> 本节主要介绍Consul注册中心学习的内容。

[[toc]]

## 下载consul

下载地址：https://www.consul.io/downloads

```
wget https://releases.hashicorp.com/consul/1.7.0/consul_1.7.0_linux_amd64.zip
```

## 解压

```
unzip consul_1.7.0_linux_amd64.zip -d /usr/local/bin
```

## 设置环境变量

```
$ vi /etc/profile
export CONSUL_HOME=/usr/local/bin/consul
export PATH=$PATH:CONSUL_HOME
```

使环境变量生效：

```
source /etc/profile
```

## 运行参数说明

consul以agent的方式启动，相关参数说明：

- -server 以服务端模式运行，相应的还有客户端模式-client
- -ui 启动内置的Web UI
- -bootstrap-expect=3 集群最少节点数，类似zookeeper的配置一样，为了防止脑裂，一般为奇数
- -data-dir=/data/consul 数据存储目录
- -node=agent-1 集群的节点名称
- -client=0.0.0.0 指定客户端能访问的ip，类似于ip白名单。0.0.0.0表示不限制
- -bind=10.25.84.163 绑定了当前主机的IP地址
- -datacenter=dc1 数据中心名称
- -join agent启动时加入到代理服务器地址，不指定不会加入任何节点，可以在启动后通过consul join命令加入

```
consul agent --help
```

# 容器下使用

## 配置文件

test.json

```json
{
    "ID": "test-service1",
    "Name": "test-service1",
    "Tags": [
        "test",
        "v1"
    ],
    "Address": "127.0.0.1",
    "Port": 8000,
    "Meta": {
        "X-TAG": "testtag"
    },
    "EnableTagOverride": false,
    "Check": {
        "DeregisterCriticalServiceAfter": "90m",
        "HTTP": "http://zhihu.com",
        "Interval": "10s"
    }
}
```

conf.json

```json
{
 "ports":{
 "server":8300,
 "serf_lan":8301,
 "serf_wan":8302,
 "http":8500,
 "dns":8600
 },
 "data_dir":"/home/tools"
}
```

说明：

```
8500 http 端口，用于 http 接口和 web ui
8300 server rpc 端口，同一数据中心 consul server 之间通过该端口通信
8301 serf lan 端口，同一数据中心 consul client 通过该端口通信
8302 serf wan 端口，不同数据中心 consul server 通过该端口通信
8600 dns 端口，用于服务发现
```

## 操作过程

服务端：

```bash

docker run -it -d -p 8500:8500 --name consul_server docker.io/klc407073648/centos_build_lib:v3.0 /bin/bash
docker cp /home/klc/consul_1.11.4_linux_amd64.zip  consul_server:/home

docker exec -it consul_server bash
cd /home/
unzip consul_1.11.4_linux_amd64.zip -d /usr/local/bin

echo 'export CONSUL_HOME=/usr/local/bin/consul'  >> /etc/profile
echo 'export PATH=$PATH:CONSUL_HOME'  >> /etc/profile
source /etc/profile
vi conf.json
consul agent -server -node=node1 -bootstrap-expect 1 -bind=0.0.0.0 -client=0.0.0.0 -config-dir=./conf.json -ui
```

客户端：

```bash
docker run -it -d -p 8500:8500 --name consul_client docker.io/klc407073648/centos_build_lib:v3.0 /bin/bash
docker cp /home/klc/consul_1.11.4_linux_amd64.zip  consul_test_2:/home

docker exec -it consul_client bash
cd /home/
unzip consul_1.11.4_linux_amd64.zip -d /usr/local/bin

echo 'export CONSUL_HOME=/usr/local/bin/consul'  >> /etc/profile
echo 'export PATH=$PATH:CONSUL_HOME'  >> /etc/profile
source /etc/profile
vi conf.json

consul agent -node=node2  -retry-join=172.17.0.2 -bind=0.0.0.0 -client=0.0.0.0 -config-dir=./conf.json
```

然后，客户端同步信息到服务端：

```
docker exec -it consul_client bash

cd /home/
touch test.json
curl -X PUT --data @test.json http://localhost:8500/v1/agent/service/register
```
