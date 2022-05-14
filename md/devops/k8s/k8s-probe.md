
#  Kubernetes 检测探针学习

[[toc]]

### 学习内容

* [Kubernetes-单机实验(入门)](https://www.cnblogs.com/douyi/p/11954910.html)
* [Kubernetes入门](https://www.cnblogs.com/zuoyang/p/9639961.html)
* [Kubernetes环境搭建(集群)](https://blog.csdn.net/u010884123/article/details/56485246)
* [Kubernetes中文指南/云原生应用架构实践手册](https://github.com/rootsongjc/kubernetes-handbook)

---
## k8s容器探针

探针是由 kubelet 对容器执行的`定期诊断`:

* ExecAction: 在容器内执行指定命令。如果命令退出时返回码为 0 则认为诊断成功
* TCPSocketAction: 对指定端口上的容器的 IP 地址进行 TCP 检查。如果端口打开,则诊断被认为是成功的
* HTTPGetAction: 对指定的端口和路径上的容器的 IP 地址执行 HTTP Get请求。如果响应的状态码大于等于200 且小于 400,则诊断被认为是成功的

每次探测都将获得以下三种结果之一:

* 成功:容器通过了诊断
* 失败:容器未通过诊断
* 未知:诊断失败,因此不会采取任何行动

Kubelet 可以选择是否执行在容器上运行的三种探针执行和做出反应:

* `livenessProbe`:指示容器是否正在运行。如果存活探测失败,则 kubelet 会杀死容器,并且容器将受到其**重启策略**的影响。如果容器不提供存活探针,则默认状态为 Success。
* `livenessProbe`:指示容器是否准备好服务请求。如果就绪探测失败,端点控制器将从与 Pod 匹配的所有 Service 的端点中删除该 Pod 的 IP 地址。初始延迟之前的就绪状态默认为 Failure。如果容器不提供就绪探针,则默认状态为 Success。
* startupProbe: 指示容器中的应用是否已经启动。如果提供了启动探测(startup probe),则禁用所有其他探测,直到它成功为止。如果启动探测失败,kubelet 将杀死容器,容器服从其重启策略进行重启。如果容器没有提供启动探测,则默认状态为成功Success。

## 探针实例

readiness-liveness-Probe.yaml文件内容如下

```
apiVersion: v1 
kind: Pod  
metadata:
  name: readiness-httpget-pod 
  namespace: default
spec:  
  containers:  
  - name: readiness-httpget-container  
    image: my_hello_docker 
    imagePullPolicy: IfNotPresent
    readinessProbe:
      httpGet:
        port: 9950
        path: /posts
      initialDelaySeconds: 1
      periodSeconds: 5
    livenessProbe:
      exec:
        command: ["test","-e","/home/live"]
      initialDelaySeconds: 1
      periodSeconds: 30
```

* 检测探针——就绪检测
  * 通过httpGet方式，获取容器9950端口的posts资源内容，若能成功获取则变成就绪态。

* 检测探针——存活检测
  * 通过exec方式，校验容器里/home/live文件是否存在，如果不存在且超过默认次数，容器会挂掉。

操作流程:

```bash
创建pod:
[root@192 docker]# kubectl create -f readinessProbe.yaml
pod "readiness-httpget-pod" created


持续观察pod,可以看出 READY 中状态从0-->1,表示就绪检测完成;因为容器里默认没有/home/live 文件，一直存活检测后容器会宕机。
[root@192 docker]# kubectl get pod -o wide -w
NAME                    READY     STATUS    RESTARTS   AGE       IP           NODE
mysql-96dm7             1/1       Running   0          55m       172.17.0.7   127.0.0.1
myweb-0x6g3             1/1       Running   0          55m       172.17.0.6   127.0.0.1
myweb-478zh             1/1       Running   0          55m       172.17.0.5   127.0.0.1
readiness-httpget-pod   1/1       Running   0          1m        172.17.0.2   127.0.0.1
NAME                    READY     STATUS    RESTARTS   AGE       IP           NODE
readiness-httpget-pod   0/1       Running   1          2m        172.17.0.2   127.0.0.1
readiness-httpget-pod   1/1       Running   1         2m        172.17.0.2   127.0.0.1
readiness-httpget-pod   0/1       Running   2         3m        172.17.0.2   127.0.0.1
readiness-httpget-pod   1/1       Running   2         3m        172.17.0.2   127.0.0.1
readiness-httpget-pod   0/1       Running   3         4m        172.17.0.2   127.0.0.1
readiness-httpget-pod   1/1       Running   3         4m        172.17.0.2   127.0.0.1
...

readiness-httpget-pod   0/1       CrashLoopBackOff   5          8m        172.17.0.2   127.0.0.1


通过手动拷贝的方式，使得容器通过存活检测。
[root@192 docker]# docker ps |grep readiness
eaefab8e99fc        my_hello_docker                                              "/home/user/entryp..."   41 seconds ago      Up 41 seconds                           k8s_readiness-httpget-container.f024ded2_readiness-httpget-pod_default_1fdcf57f-629f-11eb-ad1a-000c2925d2e7_90f191f4
5d4f3fd0fa0a        registry.access.redhat.com/rhel7/pod-infrastructure:latest   "/usr/bin/pod"           3 minutes ago       Up 3 minutes                            k8s_POD.ae8ee9ac_readiness-httpget-pod_default_1fdcf57f-629f-11eb-ad1a-000c2925d2e7_368b7d71
[root@192 docker]# docker cp live eaefab8e99fc:/home


```
