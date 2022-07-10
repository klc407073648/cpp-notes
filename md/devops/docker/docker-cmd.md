# Docker - 命令大全

> docker 常用的命令以及示例。

[[toc]]

# 参考资料

* [菜鸟教程docker](https://www.runoob.com/docker)


# 基本命令

```bash
`uname -r` ：查看内核
`systemctl start docker`: 启动docker镜像
`docker version` :查看docker版本
`docker info`：查看docker详细信息
`docker --help`：查看docker命令
```


# 镜像命令

```bash
docker images                                  # 查看镜像列表
​docker pull 镜像名称或ID                       # 拉取镜像到本地
​docker push keke/unbantu-test:lastest          # 上传镜像到仓库
​docker save -o 导出的路径 镜像ID               # 保存到本地镜像
​docker load -i 镜像路径                        # 加载本地镜像
​docker tag 镜像ID 新镜像名称：版本             # 修改镜像名称
docker rmi 镜像名称或ID                      ​ # 删除一个或者多个镜像

# 通过容器创建镜像：从已经创建的容器中更新镜像，并且提交这个镜像 使用 Dockerfile 指令来创建一个新的镜像 下面通过已存在的容器创建一个新的镜像。
docker commit -m="First Image" -a="keke" 7a15f99695c0 keke/unbantu:17.10.0

上面命令参数说明：
-m 提交的描述信息
-a 指定镜像作者
7a15f99695c0 ：记住这个是容器id，不是镜像id
keke/unbantu:17.10.0： 创建的目标镜像名
```

# 容器命令

创建一个新的容器并运行一个命令
```
docker run [OPTIONS] IMAGE [COMMAND] [ARG...]
```
OPTIONS说明：

* -a stdin: 指定标准输入输出内容类型，可选 STDIN/STDOUT/STDERR 三项；
* -d: 后台运行容器，并返回容器ID；
* -i: 以交互模式运行容器，通常与 -t 同时使用；
* -P: 随机端口映射，容器内部端口随机映射到主机的端口
* -p: 指定端口映射，格式为：主机(宿主)端口:容器端口
* -t: 为容器重新分配一个伪输入终端，通常与 -i 同时使用；
* --name="nginx-lb": 为容器指定一个名称；
* --dns 8.8.8.8: 指定容器使用的DNS服务器，默认和宿主一致；
* --dns-search example.com: 指定容器DNS搜索域名，默认和宿主一致；
* -h "mars": 指定容器的hostname；
* -e username="ritchie": 设置环境变量；
* --env-file=[]: 从指定文件读入环境变量；
* --cpuset="0-2" or --cpuset="0,1,2": 绑定容器到指定CPU运行；
* -m :设置容器使用内存最大值；
* --net="bridge": 指定容器的网络连接类型，支持 bridge/host/none/container: 四种类型；
* --link=[]: 添加链接到另一个容器；
* --expose=[]: 开放一个端口或一组端口；
* --volume , -v: 绑定一个卷


```
docker run 镜像ID|镜像名称[:tag]                            # 启动容器
docker run 镜像ID yum install -y -name                      # 在容器中安装新的程序:在执行 yum 命令的时候，要带上-y参数
docker run 镜像ID echo "hello wrold"                        # 在容器中运行"echo"命令，输出"hello world"
docker run -it 镜像ID /bin/bash                             # 交互式进入容器中
```

列出所有容器的ID:
```
docker ps -qa        
```

OPTIONS说明：

* -a :显示所有的容器，包括未运行的。
* -f :根据条件过滤显示的内容。
* --format :指定返回值的模板文件。
* -l :显示最近创建的容器。
* -n :列出最近创建的n个容器。
* --no-trunc :不截断输出。
* -q :静默模式，只显示容器编号。
* -s :显示总的文件大小。

```
docker ps                                                   # 列出当前所有正在运行的容器
docker ps -qa                                               # 列出所有容器的ID
docker ps -n 5                                              # 列出最近创建的5个容器信息

docker ps -f id=5b6                                         # 按id过滤
docker ps -f name=nginx                                     # 按name过滤
docker ps -f status=running                                 # 按status过滤
```

获取容器/镜像的元数据:
```
docker inspect --format='{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' mymysql
172.17.0.3

docker inspect mysql:5.6
[
    {
        "Id": "sha256:2c0964ec182ae9a045f866bbc2553087f6e42bfc16074a74fb820af235f070ec",
        "RepoTags": [
            "mysql:5.6"
        ],
        "RepoDigests": [],
...
```

执行容器中的shell：

```bash
docker exec -i 镜像ID /bin/bash -c "/home/build.sh"         
```

OPTIONS说明：
- d :分离模式: 在后台运行
- i :即使没有附加也保持STDIN 打开
- t :分配一个伪终端

# 操作容器

```
# 启动、停止、重启、杀死某个docker 容器
docker start 容器ID
docker stop 容器ID
docker restart 容器ID
docker kill 容器ID

docker rm Name/ID                                  # 删除容器
docker rm -f Name/ID                               # 强制删除某个容器
docker rm $(docker ps -qa)                         # 删除所有容器
docker rm $(docker ps -q -f status=exited)         # 删除所有状态为exit的容器

docker pause                                       # 暂停容器中所有的进程。
docker unpause                                     # 恢复容器中所有的进程。

docker create                                      # 创建一个新的容器但不启动它

docker top Name/ID                                 # 查看容器内运行的进程
docker attach Name/ID                              # 连接到正在运行中的容器
docker wait Name/ID                                # 阻塞运行直到容器停止，然后打印出它的退出代码。
docker cp NameID:容器内的文件路径 宿主机路径        # 从容器里面拷贝文件/目录到本地一个路径

```

从服务器获取实时事件:
```
docker events [OPTIONS]
```
OPTIONS说明：
- -f ：根据条件过滤事件；
- --since ：从指定的时间戳后显示所有事件;
- --until ：流水时间显示到指定的时间为止；

```
docker events -f "image"="mysql:5.6" --since="2016-07-01" 
```

查看容器日志
```
docker logs [OPTIONS] CONTAINER
```
OPTIONS说明：
- -f : 跟踪日志输出
- --since :显示某个开始时间的所有日志
- -t : 显示时间戳
- --tail :仅列出最新N条容器日志

```
docker logs --since="2016-07-01" --tail=10 mynginx   #查看容器mynginx从2016年7月1日后的最新10条日志
```