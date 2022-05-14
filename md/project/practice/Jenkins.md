# Docker安装Jenkins

[[toc]]

## 参考资料

* [Docker 安装 Jenkins](https://segon.cn/install-jenkins-using-docker.html)
* [Docker + Jenkins 部署完整node项目](https://segmentfault.com/a/1190000021462867?utm_source=tag-newest)

## Docker安装Jenkins详细过程

## 安装环境 

* CentOS 7.5
* Docker version 1.13.1

```
[root@VM-0-10-centos local]# docker -v
Docker version 1.13.1, build 0be3e21/1.13.1
[root@VM-0-10-centos local]# cat /etc/*release
CentOS Linux release 7.5.1804 (Core)
```

## 安装过程

**拉取镜像**

安装的版本是2.222.3-centos，可从以下地址获取其他目标版本: https://hub.docker.com/_/jenkins?tab=tags

```bash
docker pull jenkins/jenkins:2.222.3-centos
```

**创建本地数据卷**

我这里映射本地数据卷的路径为/home/jenkins/data/jenkins_home/，可自行定义。

```bash
mkdir -p /data/jenkins_home/
```

需要修改下目录权限，因为当映射本地数据卷时，/home/jenkins/data/jenkins_home/目录的拥有者为root用户，而容器中jenkins用户的 uid 为 1000。

```bash
chown -R 1000:1000 /home/jenkins/data/jenkins_home/
```

**创建容器**
```bash
docker run -d --name jenkins -p 9090:8080 -p 50000:50000 -v /home/jenkins/data/jenkins_home:/var/jenkins_home jenkins/jenkins:2.222.3-centos
```

参数说明：
```
-d 标识是让 docker 容器在后台运行
--name 定义一个容器的名字，如果没有指定，那么会自动生成一个随机数字符串当做UUID
-p 9090:8080 端口映射，我本地的8080被占用了，所以随便映射了一个9090
-p 50000:50000 端口映射
-v /home/jenkins/data/jenkins_home:/var/jenkins_home 绑定一个数据卷，/home/jenkins/data/jenkins_home是刚才创建的本地数据卷
```

**总结**

```
cd /home/jenkins/
mkdir -p ./data/jenkins_home/
chown -R 1000:1000 /home/jenkins/data/jenkins_home/
docker run -d --name jenkins -p 9090:8080 -p 50000:50000 -v /home/jenkins/data/jenkins_home:/var/jenkins_home 
```

## 配置过程

**打开 Jenkins**

通过浏览器访问 http://1.15.105.166:9090/  （注意替换成你自己的IP和端口）进入初始页，如果 Jenkins 还没有启动完成，会显示如下内容：

![1](/_images/project/practice/Jenkins/Jenkins访问.png)

**输入管理员密码**

这里要求输入初始的管理员密码，根据提示密码在/var/jenkins_home/secrets/initialAdminPassword这个文件中，注意这个路径是 Docker 容器中的，所以我们通过如下命令获取一下。

```bash
docker exec jenkins cat /var/jenkins_home/secrets/initialAdminPassword
85770376692448b7b6a8e301fb437848
别忘了我们映射了本地数据卷/home/jenkins/data/jenkins_home，所以也可以通过如下命令输出

cat /home/jenkins/data/jenkins_home/secrets/initialAdminPassword 
85770376692448b7b6a8e301fb437848
```
输入密码后，点击继续

![2](/_images/project/practice/Jenkins/解锁Jenkins.png)

**安装插件**

![3](/_images/project/practice/Jenkins/自定义Jenkins.png)

这里选择安装推荐的插件，然后 Jenkins 会自动开始安装。

![4](/_images/project/practice/Jenkins/安装插件.png)

**创建管理员**

![5](/_images/project/practice/Jenkins/创建用户.png)

**配置完成**

![5](/_images/project/practice/Jenkins/配置完成.png)


## 配置远程Linux工作节点

Jenkins ——> Manage Jenkins  ——>  Manage Nodes and Clouds

新建节点 ——> 配置节点  ——> 启动节点代理

备注：启动代理会用到宿主机上的JAVA,需要配置成1.8（jdk-8u221-linux-x64.tar.gz），详细内容见问题记录。


![6](/_images/project/practice/Jenkins/配置Linux节点.png)

然后节点任务内容：

![7](/_images/project/practice/Jenkins/配置节点任务挂载点.png)

![8](/_images/project/practice/Jenkins/配置节点任务构建脚本.png)

配置节点任务执行：
![9](/_images/project/practice/Jenkins/配置节点任务执行.png)


## 问题记录

1.启动代理会用到宿主机上的JAVA，看代理日志会一个个默认路径去找java
```
...
[05/02/21 13:41:27] [SSH] Checking java version of /usr/java/latest/bin/java
Couldn't figure out the Java version of /usr/java/latest/bin/java
bash: /usr/java/latest/bin/java: No such file or directory

[05/02/21 13:41:27] [SSH] Checking java version of /usr/local/bin/java
Couldn't figure out the Java version of /usr/local/bin/java
bash: /usr/local/bin/java: No such file or directory

[05/02/21 13:41:27] [SSH] Checking java version of /usr/local/java/bin/java
[05/02/21 13:41:27] [SSH] /usr/local/java/bin/java -version returned 1.8.0_221.
[05/02/21 13:41:27] [SSH] Starting sftp client.
[05/02/21 13:41:27] [SSH] Copying latest remoting.jar...
Source agent hash is 0146753DA5ED62106734D59722B1FA2C. Installed agent hash is 0146753DA5ED62106734D59722B1FA2C
Verified agent jar. No update is necessary.
Expanded the channel window size to 4MB
[05/02/21 13:41:38] [SSH] Starting agent process: cd "/home/jenkins" && /usr/local/java/bin/java  -jar remoting.jar -workDir /home/jenkins -jar-cache /home/jenkins/remoting/jarCache
May 02, 2021 9:41:39 PM org.jenkinsci.remoting.engine.WorkDirManager initializeWorkDir
INFO: Using /home/jenkins/remoting as a remoting work directory
May 02, 2021 9:41:39 PM org.jenkinsci.remoting.engine.WorkDirManager setupLogging
INFO: Both error and output logs will be printed to /home/jenkins/remoting
```

