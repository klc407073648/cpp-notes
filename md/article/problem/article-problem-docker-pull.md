# 问题 - 云服务器搭建

> 更新缓存的的Design Pattern有四种：Cache aside, Read through, Write through, Write behind caching。

[[toc]]

# Centos搭建过程

## 安装docker

```sh
sudo yum install -y yum-utils device-mapper-persistent-data lvm2
sudo yum-config-manager --add-repo http://mirrors.cloud.tencent.com/docker-ce/linux/centos/docker-ce.repo
sudo yum install -y docker-ce docker-ce-cli containerd.io
sudo systemctl start docker
sudo systemctl enable docker
```

## 安装docker-compose

```sh
sudo curl -L "https://github.com/docker/compose/releases/download/1.29.2/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
chmod 777 /usr/local/bin/docker-compose
docker-compose  version
```

## 修改docker配置文件

```sh
sudo mkdir -p /etc/docker
vi /etc/docker/daemon.json
```

json内容
```json
{
    "registry-mirrors": [
        "https://hub-mirror.c.163.com",
        "https://mirror.ccs.tencentyun.com",
        "https://05f073ad3c0010ea0f4bc00b7105ec20.mirror.swr.myhuaweicloud.com",
        "https://registry.docker-cn.com",
        "https://docker.m.daocloud.io",
        "https://docker.1panel.live",
        "https://hub.rat.dev",
        "https://dockerpull.com",
        "https://dockerproxy.cn",
        "https://docker.rainbond.cc",
        "https://docker.udayun.com",
        "https://docker.211678.top"
    ]
}
```

## 重启docker

```sh
sudo systemctl daemon-reload
sudo systemctl restart docker
```

## 配置git

```
ssh-keygen -t rsa -b 4096 -C "407073648@qq.com"
cat ~/.ssh/id_rsa.pub
```

# 搭建docker环境

## 问题

### docker: Error response from daemon

```
docker: Error response from daemon: Get “https://registry-1.docker.io/v2/
```

### 解决方案

1. 创建或修改 Docker 配置文件

打开或创建 /etc/docker/daemon.json 文件。如果文件不存在，你可以使用以下命令创建它：

```sh
sudo mkdir -p /etc/docker
vi /etc/docker/daemon.json

{
    "registry-mirrors": [
        "https://hub-mirror.c.163.com",
        "https://mirror.ccs.tencentyun.com",
        "https://05f073ad3c0010ea0f4bc00b7105ec20.mirror.swr.myhuaweicloud.com",
        "https://registry.docker-cn.com",
        "https://docker.m.daocloud.io",
        "https://docker.1panel.live",
        "https://hub.rat.dev",
        "https://dockerpull.com",
        "https://dockerproxy.cn",
        "https://docker.rainbond.cc",
        "https://docker.udayun.com",
        "https://docker.211678.top"
    ]
}
EOF
```

这里列出了几个可用的国内镜像源地址，你可以根据实际情况选择使用。

2. 重启 Docker 服务

修改配置文件后，需要重启 Docker 服务以使配置生效。你可以使用以下命令：

```
sudo systemctl daemon-reload
sudo systemctl restart docker
```

3. 验证配置

配置完成后，你可以使用 docker info 命令来查看当前的镜像源配置是否已经更新。如果配置正确，你应该能看到列出的镜像源地址。

```
Client: Docker Engine - Community
 Version:    26.1.4
 Context:    default
 Debug Mode: false
 Plugins:
  buildx: Docker Buildx (Docker Inc.)
    Version:  v0.14.1
    Path:     /usr/libexec/docker/cli-plugins/docker-buildx
  compose: Docker Compose (Docker Inc.)
    Version:  v2.27.1
    Path:     /usr/libexec/docker/cli-plugins/docker-compose

Server:
 Containers: 1
  Running: 1
  Paused: 0
  Stopped: 0
 Images: 2
 Server Version: 26.1.4
 Storage Driver: overlay2
  Backing Filesystem: extfs
  Supports d_type: true
  Using metacopy: false
  Native Overlay Diff: true
  userxattr: false
 Logging Driver: json-file
 Cgroup Driver: cgroupfs
 Cgroup Version: 1
 Plugins:
  Volume: local
  Network: bridge host ipvlan macvlan null overlay
  Log: awslogs fluentd gcplogs gelf journald json-file local splunk syslog
 Swarm: inactive
 Runtimes: io.containerd.runc.v2 runc
 Default Runtime: runc
 Init Binary: docker-init
 containerd version: d2d58213f83a351ca8f528a95fbd145f5654e957
 runc version: v1.1.12-0-g51d5e94
 init version: de40ad0
 Security Options:
  seccomp
   Profile: builtin
 Kernel Version: 3.10.0-1160.119.1.el7.x86_64
 Operating System: CentOS Linux 7 (Core)
 OSType: linux
 Architecture: x86_64
 CPUs: 2
 Total Memory: 3.607GiB
 Name: VM-4-8-centos
 ID: 5b16312d-0a52-49e2-bb8c-34f661e4b4fb
 Docker Root Dir: /var/lib/docker
 Debug Mode: false
 Experimental: false
 Insecure Registries:
  127.0.0.0/8
 Registry Mirrors:
  https://hub-mirror.c.163.com/
  https://mirror.ccs.tencentyun.com/
  https://05f073ad3c0010ea0f4bc00b7105ec20.mirror.swr.myhuaweicloud.com/
  https://registry.docker-cn.com/
  https://docker.m.daocloud.io/
  https://docker.1panel.live/
  https://hub.rat.dev/
  https://dockerpull.com/
  https://dockerproxy.cn/
  https://docker.rainbond.cc/
  https://docker.udayun.com/
  https://docker.211678.top/
 Live Restore Enabled: false
```

4. 拉取镜像测试
你可以尝试拉取一个镜像来测试配置是否有效，例如：

```
[root@VM-4-8-centos nginx]# docker pull ubuntu
Using default tag: latest
latest: Pulling from library/ubuntu
ff65ddf9395b: Pull complete
Digest: sha256:99c35190e22d294cdace2783ac55effc69d32896daaa265f0bbedbcde4fbe3e5
Status: Downloaded newer image for ubuntu:latest
docker.io/library/ubuntu:latest
```

# 配置git

## 操作流程

```
[root@VM-4-8-centos ~]# ssh-keygen -t rsa -b 4096 -C "xxx@qq.com"
Generating public/private rsa key pair.
Enter file in which to save the key (/root/.ssh/id_rsa):
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
Your identification has been saved in /root/.ssh/id_rsa.
Your public key has been saved in /root/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:qcV1DPPeZ2aoIrA4eACeuClB0n/bRc8JqZvOu/ax6Vk xxx@qq.com
The key's randomart image is:
+---[RSA 4096]----+
|          o      |
| .         *     |
|o..       = +    |
|=...   . = * o . |
|oo. . o S . = o =|
| + o o B +   . = |
|+ . + + = o E    |
|.  . . o.. B     |
|       .==*      |
+----[SHA256]-----+
```

2. 配置公钥复制到github的 https://github.com/settings/keys 地址，设置SSH keys
 cat ~/.ssh/id_rsa.pub

