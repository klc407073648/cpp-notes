# Tars - Go开发

> 本节主要介绍Tars Go服务开发和编译时需要的开发环境。

[[toc]]

# Go语言开发

Linux下安装Golang

```
##将安装文件解压到 /usr/local目录下：
cd /usr/local/
tar -zxvf go1.16.6.linux-amd64.tar.gz  -C /usr/local/
vi /etc/profile

```

**添加环境变量:**

```
1、打开配置文件profile
    命令：vi /etc/profile
    
2、在文件最后添加以下内容（环境变量）:
        export GOROOT=/usr/local/go
        export GOPATH=/home/klc/tars/TarsGo
        export PATH=$PATH:$GOROOT/bin:$GOPATH/bin
    保存并退出。
    
3、重启系统或刷新配置文件。
    命令：source /etc/profile
    
4、检查是否安装成功。
    命令：go version
```

设置go env

```
 go env -w GO111MODULE=auto
 go env -w GOPROXY=https://mirrors.aliyun.com/goproxy/
```

go客户端和服务端代码编写

```
cd /home/klc/tars/TarsGo
go get -u github.com/TarsCloud/TarsGo/tars
mkdir -p $GOPATH/bin
cd $GOPATH/src/github.com/TarsCloud/TarsGo/tars/tools/tars2go && go build
cp tars2go $GOPATH/bin/


sh $GOPATH/src/github.com/TarsCloud/TarsGo/tars/tools/create_tars_server.sh GoApp HelloGo SayHello
cd /home/klc/tars/TarsGo/src/GoApp/HelloGo

vi sayhello_imp.go ## 实现Add Sub 方法
make && make tar  ##生成发布包

##编写和运行客户端
touch HelloGoClient.go
go build HelloGoClient.go
./HelloGoClient
```