
#  Kubernetes 基础应用

> Kubernetes单机基础实践

[[toc]]

### 学习内容

* [Kubernetes-单机实验(入门)](https://www.cnblogs.com/douyi/p/11954910.html)
* [Kubernetes入门](https://www.cnblogs.com/zuoyang/p/9639961.html)
* [Kubernetes环境搭建(集群)](https://blog.csdn.net/u010884123/article/details/56485246)
* [Kubernetes中文指南/云原生应用架构实践手册](https://github.com/rootsongjc/kubernetes-handbook)
* [k8s入门系列之svc基础篇](http://www.21yunwei.com/archives/6824)

---
## Kubernetes单机基础实践

### 一、安装kubernetes

1.关闭CentOS自带的防火墙服务

```
[root@192 ~]# systemctl disable firewalld
[root@192 ~]# systemctl  stop firewalld
```

2.安装etcd和Kubernetes软件（会自动安装Docker）

```
[root@192 ~]# yum  install  -y  etcd  kubernetes
```

3.安装好软件后，修改两个配置文件（其他的配置文件使用系统默认的配置参数即可）

* Docker配置文件为 /etc/sysconfig/docker，其中OPTIONS的内容为：

  * OPTIONS='--selinux-enabled=false --insecure-registry gcr.io'  

* Kubernetes apiserver配置文件为/etc/kubernetes/apiserver，把--admission_control参数中的ServiceAccount删除。


4.准备工作
```
[root@192 k8s]# yum install python-rhsm-certificates
...会提示:
Package python-rhsm-certificates-1.19.10-1.el7_4.x86_64 is obsoleted by subscription-manager-rhsm-certificates-1.24.45-1.el7.centos.x86_64 which is already installed
Nothing to do

解决方法：
[root@192 k8s]# wget http://mirror.centos.org/centos/7/os/x86_64/Packages/python-rhsm-certificates-1.19.10-1.el7_4.x86_64.rpm
[root@192 k8s]# rpm2cpio python-rhsm-certificates-1.19.10-1.el7_4.x86_64.rpm |cpio -iv --to-stdout ./etc/rhsm/ca/redhat- uep.pem > /etc/rhsm/ca/redhat-uep.pem
[root@192 k8s]# vim /etc/docker/daemon.json
```

5.配置docker加速器

```
[root@192 k8s]# vim /etc/docker/daemon.json
{
 "registry-mirrors": ["https://dhq9bx4f.mirror.aliyuncs.com"]
}
```

6.按顺序启动所有服务

```
[root@192 ~]# systemctl start etcd
[root@192 ~]# systemctl start docker
[root@192 ~]# systemctl start kube-apiserver
[root@192 ~]# systemctl start kube-controller-manager
[root@192 ~]# systemctl start kube-scheduler
[root@192 ~]# systemctl start kubelet
[root@192 ~]# systemctl start kube-proxy


备注：启动脚本k8s_start.sh
```

### 二、创建Mysql的RC和SVC

1.拉取mysql的docker镜像
```
[root@192 k8s]# docker pull registry.access.redhat.com/rhel7/pod-infrastructure:latest
[root@192 k8s]# docker pull mysql:5.6
```

2.创建rc文件、启动rc、查询是否有mysql-rc

```
[root@192 k8s]# vim mysql-rc.yaml

[root@192 k8s]# kubectl create -f mysql-rc.yaml
replicationcontroller "mysql" created

[root@192 k8s]# kubectl get rc
NAME      DESIRED   CURRENT   READY     AGE
mysql     1         1         0         49s

//等创建好STATUS  ContainerCreating --->  Running 
[root@192 k8s]# kubectl get pod
NAME          READY     STATUS              RESTARTS   AGE
mysql-cl332   0/1       ContainerCreating   0          1m

```
3.创建svc文件、启动svc、查询svc运行状态

```
[root@192 k8s]# vim mysql-svc.yaml

[root@192 k8s]# kubectl create -f mysql-svc.yaml
service "mysql" created

[root@192 k8s]# kubectl get svc
NAME         CLUSTER-IP       EXTERNAL-IP   PORT(S)    AGE
kubernetes   10.254.0.1       <none>        443/TCP    51m
mysql        10.254.253.220   <none>        3306/TCP   11s
```

mysql-svc.yaml和mysql-rc.yaml
```
selector:
app: mysql 指定具有app标签，且值为mysql 的pod全部纳入本组Service
通过create 创建好后可以查看到clusterIP和端口等信息:
```

4. 测试mysql服务能否正常使用

```
[root@192 k8s]# mysql -h 10.254.253.220 -u root -p123456

[root@192 k8s]# mysql -h 10.254.253.220  -u root -P 3306 -p123456 -Dmtest</home/k8s/student.sql
```

![1](/_images/devops/k8s/mysql.png)


### 三、创建Tomcat的RC和SVC

1.创建rc文件、启动rc、查询是否有myweb-rc、查询pod的状态
```
[root@192 k8s]# vim myweb-rc.yaml

[root@192 k8s]# kubectl create -f myweb-rc.yaml
replicationcontroller "myweb" created

[root@192 k8s]# kubectl get rc
NAME      DESIRED   CURRENT   READY     AGE
mysql     1         1         1         1h
myweb     2         2         2         1h

[root@192 k8s]# kubectl get pod
NAME          READY     STATUS    RESTARTS   AGE
mysql-cl332   1/1       Running   0          1h
myweb-6pmst   1/1       Running   0          59m
myweb-jr5jx   1/1       Running   0          59m

```

2.创建svc文件、启动svc、查询svc运行状态

```
[root@192 k8s]# vim myweb-svc.yaml

[root@192 k8s]# kubectl create -f myweb-svc.yaml
service "myweb" created


[root@192 k8s]# kubectl get svc
NAME         CLUSTER-IP       EXTERNAL-IP   PORT(S)          AGE
kubernetes   10.254.0.1       <none>        443/TCP          2h
mysql        10.254.253.220   <none>        3306/TCP         1h
myweb        10.254.205.120   <nodes>       8080:30001/TCP   1h

```

3.测试浏览器能否正常访问

myweb-svc.yaml定义了:
 type=NodePort 和 nodePort=30001 的两个属性，表型此 Service开启了 NodePort方式的外网访问模式，在Kubernetes集群之外，比如在本机的浏览器里，可以通过 30001 这个端口访问myweb(对应 8080 的虚端口上)。

在你的笔记本上打开浏览器，输入http://虚拟机 IP:30001/demo/。

![1](/_images/devops/k8s/myweb.png)

