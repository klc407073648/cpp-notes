# 通过阿里云ecs部署k8s集群

https://blog.csdn.net/weixin_47678667/article/details/121680938

https://segmentfault.com/a/1190000040421720

https://blog.csdn.net/qq_44895681/article/details/119956767

1. 搭建环境
2. 安装步骤
* 禁用Selinux
* Restart Docker
* 此处仅有两台服务器，一台master节点，一台node节点，后期可按照步骤继续增加node节点

1. 搭建环境
Master节点：
CPU : 2核、内存 ：4GiB、 操作系统：Centos7.6 64位、 带宽：3Mbps
Node节点：
CPU : 2核、内存 ：4GiB、 操作系统：Centos7.6 64位、 带宽：1Mbps
将公网所有端口都开放

集群版本：

```
k8s=v1.15.0 、docker=docker-ce-18.06.1.ce-3.el7 、etcd=3.3.10、 dashboard=v1.10.1、flannel=v0.11.0-amd64、coreDns= 1.3.1、pause=3.1
```

# 安装步骤
## 需要在每一个节点上进行的操作

### 提前准备

在K8s中为了高效运行，整个集群的机器需要关闭防火墙、SWAP分区以及Selinux，使用如下命令：

**关闭防火墙**

```
systemctl stop firewalld
systemctl disable firewalld
```

**暂时关闭SWAP分区**

```
swapoff -a
```

**永久禁用SWAP分区**

```
swapoff -a && sed -i '/ swap / s/^\(.*\)$/#\1/g' /etc/fstab
```

**禁用Selinux**

```
setenforce 0 && sed -i 's/^SELINUX=.*/SELINUX=disabled/' /etc/selinux/config
```


将系统中桥接的IPv4以及IPv6的流量串通：

```
cat >/etc/sysctl.d/k8s.conf << EOF
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
EOF
sysctl --system
```


## 安装Docker

这里我们使用阿里云的镜像。首先下载阿里云镜像仓库描述文件：

```
wget https://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo -O /etc/yum.repos.d/docker-ce.repo
```

然后指定Docker版本进行安装：

```
#如果已经存在docker，先卸载后安装
yum remove docker  docker-common docker-selinux docker-engine

yum -y install docker-ce-18.06.1.ce-3.el7
```


开启Docker的服务以及安装：

```
systemctl enable docker && systemctl start docker
docker --version
```


在K8S中建议Docker与K8S使用的Cgroupdriver值为 “systemd”，所以每一个节点还需要进行如下的修改 ：

```
Setup daemon.
cat > /etc/docker/daemon.json <<EOF
{
  "exec-opts": ["native.cgroupdriver=systemd"],
  "log-driver": "json-file",
  "log-opts": {
    "max-size": "100m"
  },
  "storage-driver": "overlay2",
  "storage-opts": [
    "overlay2.override_kernel_check=true"
  ]
}
EOF

mkdir -p /etc/systemd/system/docker.service.d
```

**Restart Docker**

```
systemctl daemon-reload
systemctl restart docker
```


## 安装Kubernetes的安装组件

在安装k8s之前也需要加上yum源：

```
vi /etc/yum.repos.d/kubernetes.repo

# 在这个文件中输入
[kubernetes]
name=Kubernetes
baseurl=https://mirrors.aliyun.com/kubernetes/yum/repos/kubernetes-el7-x86_64
enable=1
gpgcheck=0
repo_gpgcheck=0
gpgkey=https://mirrors.aliyun.com/kubernetes/yum/doc/yum-key.gpg
https://mirrors.aliyun.com/kubernetes/yum/doc/rpm-package-key.gpg
```

在腾讯云安装时候：

```
[kubernetes]
name=Kubernetes
baseurl=https://mirrors.aliyun.com/kubernetes/yum/repos/kubernetes-el7-x86_64/
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://mirrors.aliyun.com/kubernetes/yum/doc/yum-key.gpg https://mirrors.aliyun.com/kubernetes/yum/doc/rpm-package-key.gpg
```

指定版本进行kubeadm、kubelet、kubectl的安装：

```
yum install -y kubelet-1.15.0 kubeadm-1.15.0 kubectl-1.15.0
```


然后开启kubelet服务：

```
systemctl enable kubelet.service
```

需要在Master上操作

注意需要自己填写的地方，可以根据自己的情况进行修改，然后基于我的运行情况就是，执行如下命令：

```
kubeadm init \
--apiserver-advertise-address=139.196.82.84 \
--image-repository=registry.aliyuncs.com/google_containers \
--kubernetes-version=v1.15.0 \
--service-cidr=10.1.0.0/16 \
--pod-network-cidr=10.244.0.0/16
```

–apiserver-advertise-address string API 服务器所公布的其正在监听的 IP 地址。如果未设置，则使用默认网络接口。 默认设置位master节点ip地址 –pod-network-cidr string
通过这个值来设定pod网络的IP地址网段；设置了这个值以后，控制平面会自动给每个节点设置CIDRs（无类别域间路由，Classless
Inter-Domain Routing）。默认为10.1.0.0/16 –service-cidr string Default:
“10.96.0.0/12” 设置service的CIDRs，默认为 10.96.0.0/12。
因为阿里云ecs里没有配置公网ip，etcd无法启动，<font color='red'>所以kubeadm在初始化会出现”timeout“的错误</font>。

解决办法：

建立两个ssh对话，即用ssh工具新建两个标签，<font color='red'>一个用来初始化节点，另一个在初始化过程中修改配置文件</font>。 注意是初始化过程中，每次运行kubeadm init，kubeadm都会生成etcd的配置文件，如果提前修改了配置文件，在运行kubeadm init时会把修改的结果覆盖，那么也就没有作用了。

运行”kubeadm init …“上述的初始化命令，此时会卡在

```
[etcd] Creating static Pod manifest for local etcd in "/etc/kubernetes/manifests"
[wait-control-plane] Waiting for the kubelet to boot up the control plane as static Pods from directory "/etc/kubernetes/manifests". This can take up to 4m0s
[kubelet-check] Initial timeout of 40s passed.
```

在输入上述命令后，kubeadm即开始了master节点的初始化，但是由于etcd配置文件不正确，所以etcd无法启动，要对该文件进行修改。
文件路径"/etc/kubernetes/manifests/etcd.yaml"。

此处"xxx"为公网ip，要关注的是"–listen-client-urls"和"–listen-peer-urls"。需要把"–listen-client-urls"后面的公网ip删除，把"–listen-peer-urls"改为本地的地址。

```
修改前：	
	- --listen-client-urls=https://127.0.0.1:2379,https://139.196.82.84:2379
	- --listen-peer-urls=https://139.196.82.84:2380

修改后：
    - --listen-client-urls=https://127.0.0.1:2379
    - --listen-peer-urls=https://127.0.0.1:2380
```

如果没有来得及修改etcd.yaml导致init失败：

```
运行：kubeadm reset &&  
rm -rf $HOME/.kube/config  && rm -rf $HOME/.kube && rm -rf /var/lib/etcd
iptables -F && iptables -t nat -F && iptables -t mangle -F && iptables -X

kubeadm init \
--apiserver-advertise-address=139.196.82.84 \
--image-repository=registry.aliyuncs.com/google_containers \
--kubernetes-version=v1.15.0 \
--service-cidr=10.1.0.0/16 \
--pod-network-cidr=10.244.0.0/16
```

稍等后master节点初始化就会完成

```
Your Kubernetes control-plane has initialized successfully!

To start using your cluster, you need to run the following as a regular user:

  mkdir -p $HOME/.kube
  sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
  sudo chown $(id -u):$(id -g) $HOME/.kube/config

You should now deploy a pod network to the cluster.
Run "kubectl apply -f [podnetwork].yaml" with one of the options listed at:
  https://kubernetes.io/docs/concepts/cluster-administration/addons/

Then you can join any number of worker nodes by running the following on each as root:

kubeadm join 139.196.82.84:6443 --token qrnucm.5bpx9b7c0qk44to3 \
    --discovery-token-ca-cert-hash sha256:997872de09fd338ca65571205d13cf5bc26c1317a7b26d51a07108bce690cfd1
```

注意：
在这个部分安装完成后，会得到一个如下的token，这个在后面node加入master要用的。

转到node节点窗口：

首先安装k8s:

````
备机操作:
#关闭防火墙,暂时关闭SWAP分区,禁用Selinux


cat >/etc/sysctl.d/k8s.conf << EOF
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
EOF
sysctl --system

# docker相关
wget https://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo -O /etc/yum.repos.d/docker-ce.repo
vi /etc/docker/daemon.json

```
{
   "registry-mirrors": [
       "https://mirror.ccs.tencentyun.com"
  ],
  "exec-opts": ["native.cgroupdriver=systemd"],
  "log-driver": "json-file",
  "log-opts": {
    "max-size": "100m"
  },
  "storage-driver": "overlay2",
  "storage-opts": [
    "overlay2.override_kernel_check=true"
  ]
}
```

mkdir -p /etc/systemd/system/docker.service.d
systemctl daemon-reload
systemctl restart docker

# k8s相关
vi /etc/yum.repos.d/kubernetes.repo

```
[kubernetes]
name=Kubernetes
baseurl=https://mirrors.aliyun.com/kubernetes/yum/repos/kubernetes-el7-x86_64/
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://mirrors.aliyun.com/kubernetes/yum/doc/yum-key.gpg https://mirrors.aliyun.com/kubernetes/yum/doc/rpm-package-key.gpg
```

yum install -y kubelet-1.15.0 kubeadm-1.15.0 kubectl-1.15.0
systemctl enable kubelet.service
````

通过”kubeadm join…"，将node节点加入到master集群中：

```
  139.196.82.84:6443 --token qrnucm.5bpx9b7c0qk44to3 \
    --discovery-token-ca-cert-hash sha256:997872de09fd338ca65571205d13cf5bc26c1317a7b26d51a07108bce690cfd1

默认token有效期为24小时，当过期之后，该token就不可用了。这时就需要重新创建token，操作如下：
kubeadm token create --print-join-command
```

使用下述命令可查看集群中节点情况:
kubectl get node

```
[root@VM-16-6-centos yum.repos.d]# kubectl get nodes
The connection to the server localhost:8080 was refused - did you specify the right host or port?
```

有报错：报错原因：环境变量，kubernetes master没有与本机绑定，集群初始化的时候没有绑定，此时设置在本机的环境变量即可解决问题。

将master节点/etc/kubernetes/admin.conf文件传到Node节点并刷新就好:

```
echo "export KUBECONFIG=/etc/kubernetes/admin.conf" >> ~/.bash_profile  
source ~/.bash_profile
```

master节点完成初始化后以及node节点加入后，通过阅读终端信息，我们还需执行几个命令：

使用下述命令可查看集群中节点情况

```
#首先master节点执行
  mkdir -p $HOME/.kube
  sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
  sudo chown $(id -u):$(id -g) $HOME/.kube/config

[root@VM-16-6-centos yum.repos.d]# kubectl get nodes
NAME                      STATUS      ROLES    AGE     VERSION
izuf61kbf845xt6tz10abgz   NotReady    master   8h      v1.15.0
vm-16-6-centos            NotReady    <none>   5m55s   v1.15.0
```

但是会查看到master节点和node节点都是NotReady状态。 因为在K8S中，整个系统处于一个扁平的网络之下，其中在谷歌内部的网络架构中，这个是天然存在的，但是在我们自己的环境里这个需要设置。
查看网络日志，提示没有网络

```
journalctl -f
```

所以下一步就是部署网络环境，此处我们使用的就是由Centos开发的flannel网络组件。

```
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
```

其中需要在master节点和node节点都安装flannel插件。
使用“kubectl get node”可查看所有节点都处于ready状态了

```
[root@VM-16-6-centos yum.repos.d]# kubectl get nodes
NAME                      STATUS   ROLES    AGE     VERSION
izuf61kbf845xt6tz10abgz   Ready    master   8h      v1.15.0
vm-16-6-centos            Ready    <none>   5m56s   v1.15.0
```

使用“kubectl get pods --all-namespaces”可查看所有Pod都在running状态：

```
[root@VM-16-6-centos yum.repos.d]# kubectl get pods --all-namespaces
NAMESPACE     NAME                                              READY   STATUS     RESTARTS   AGE
kube-system   coredns-bccdc95cf-j9dfd                           1/1     Running    0          9h
kube-system   coredns-bccdc95cf-jdkvk                           1/1     Running    0          9h
kube-system   etcd-izuf61kbf845xt6tz10abgz                      1/1     Running    0          8h
kube-system   kube-apiserver-izuf61kbf845xt6tz10abgz            1/1     Running    2          8h
kube-system   kube-controller-manager-izuf61kbf845xt6tz10abgz   1/1     Running    0          8h
kube-system   kube-flannel-ds-fwj8t                             1/1     Running    0          24m
kube-system   kube-flannel-ds-xmtsp                             0/1     Evicted    0          26s
kube-system   kube-proxy-9j5c8                                  1/1     Running    0          24m
kube-system   kube-proxy-s475t                                  0/1     Evicted    0          4m46s
kube-system   kube-scheduler-izuf61kbf845xt6tz10abgz            1/1     Running    0          9h

是虚机硬盘容量不足，删除后运行正常
[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl get pods --all-namespaces
NAMESPACE     NAME                                              READY   STATUS    RESTARTS   AGE
default       nginx-554b9c67f9-bscs5                            1/1     Running   0          11s
kube-system   coredns-bccdc95cf-j9dfd                           1/1     Running   0          21h
kube-system   coredns-bccdc95cf-jdkvk                           1/1     Running   0          21h
kube-system   etcd-izuf61kbf845xt6tz10abgz                      1/1     Running   0          21h
kube-system   kube-apiserver-izuf61kbf845xt6tz10abgz            1/1     Running   2          21h
kube-system   kube-controller-manager-izuf61kbf845xt6tz10abgz   1/1     Running   0          21h
kube-system   kube-flannel-ds-fwj8t                             1/1     Running   0          13h
kube-system   kube-flannel-ds-r7jg6                             1/1     Running   0          110s
kube-system   kube-proxy-9j5c8                                  1/1     Running   0          13h
kube-system   kube-proxy-t55hs                                  1/1     Running   0          103s
kube-system   kube-scheduler-izuf61kbf845xt6tz10abgz            1/1     Running   0          21h
```

## 测试k8s集群

```
[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl create deployment nginx --image=nginx
deployment.apps/nginx created
[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl expose deployment nginx --port=80 --type=NodePort
service/nginx exposed
[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl  get pods
NAME                     READY   STATUS    RESTARTS   AGE
nginx-554b9c67f9-8cbws   1/1     Running   0          15s

[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl get pod -o wide
NAME                     READY   STATUS    RESTARTS   AGE     IP           NODE             NOMINATED NODE   READINESS GATES
nginx-554b9c67f9-8cbws   1/1     Running   0          2m13s   10.244.1.4   vm-16-6-centos   <none>           <none>

[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl get pod,svc
NAME                         READY   STATUS    RESTARTS   AGE
pod/nginx-554b9c67f9-8cbws   1/1     Running   0          2m44s

NAME                 TYPE        CLUSTER-IP     EXTERNAL-IP   PORT(S)        AGE
service/kubernetes   ClusterIP   10.1.0.1       <none>        443/TCP        9h
service/nginx        NodePort    10.1.131.117   <none>        80:30555/TCP   2m35s
```

访问地址：http://NodeIP:Port  ，注意是nodeip

```
主节点coredns出问题：
systemctl stop kubelet
systemctl stop docker
iptables --flush
iptables -tnat --flush
systemctl start kubelet
systemctl start docker

从节点出问题，重新装:
rm -rf /etc/kubernetes/kubelet.conf
rm -rf /etc/kubernetes/bootstrap-kubelet.conf
rm -rf /etc/kubernetes/pki/ca.crt

[root@VM-16-6-centos ~]# netstat -apn |grep 10250
tcp6       0      0 :::10250                :::*                    LISTEN      2128945/kubelet    
[root@VM-16-6-centos ~]# kill -9 2128945

/etc/kubernetes/admin.conf 还要从主机拷贝过来
kubeadm join 139.196.82.84:6443 --token rw810q.0qfpcfqds3gvvuye     --discovery-token-ca-cert-hash sha256:f9f24096fe03459d859d7a7063e378dc43ec02bae1ae76fb3138047ca182dcb9
```

### 删除docker image

命令：

```
rm -rf  /var/lib/docker/image/overlay2/imagedb/content/sha256/
```
