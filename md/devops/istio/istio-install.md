# Istio - 安装

[[toc]]

## 参考资料

* [istio-handbook](https://www.servicemesher.com/istio-handbook/practice/setup-istio.html)

以 Istio 1.5 版本为例，介绍整个安装过程：

1. 直接在 官网下载对于版本：https://github.com/istio/istio/releases/tag/1.5.0 。

```bash
[root@iZuf61kbf845xt6tz10abgZ ~]# cd /home/istio/
[root@iZuf61kbf845xt6tz10abgZ istio]# tar -zxvf istio-1.5.0-linux.tar.gz
```

2. 设置环境变量。

```
vi /etc/profile
加入 export PATH=$PATH:/home/istio/istio-1.5.0/bin
source /etc/profile
```

3. 安装目录介绍：

| 目录      | 包含内容                                                     |
| --------- | ------------------------------------------------------------ |
| `bin`     | 包含 istioctl 的客户端文件                                   |
| `install` | 包含 Consul、GCP 和 Kubernetes 平台的 [Istio](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#istio) 安装脚本和文件 |
| `samples` | 包含示例应用程序                                             |
| `tools`   | 包含用于性能测试和在本地机器上进行测试的脚本                 |

# 安装过程

## 尝试集群下安装

执行安装命令：

```
[root@iZuf61kbf845xt6tz10abgZ ~]# istioctl manifest apply --set profile=demo
```

结果：

```
[root@iZuf61kbf845xt6tz10abgZ ~]# istioctl manifest apply --set profile=demo
Detected that your cluster does not support third party JWT authentication. Falling back to less secure first party JWT. See https://istio.io/docs/ops/best-practices/security/#configure-third-party-service-account-tokens for details.
- Applying manifest for component Base...
✔ Finished applying manifest for component Base.
- Applying manifest for component Pilot...
✔ Finished applying manifest for component Pilot.
- Applying manifest for component IngressGateways...
- Applying manifest for component EgressGateways...
- Applying manifest for component AddonComponents...
✔ Finished applying manifest for component EgressGateways.
2022-04-13T23:31:06.344536Z     error   installer       error running kubectl: exit status 1
✘ Finished applying manifest for component AddonComponents.
2022-04-13T23:31:34.877288Z     error   installer       error running kubectl: exit status 1
✘ Finished applying manifest for component IngressGateways.
```

失败问题，找https://github.com/istio/istio/ 中issues也无法定位，看错误日志是无法连同从节点的10250端口：

```
Events:
  Type     Reason     Age                    From                     Message
  ----     ------     ----                   ----                     -------
  Normal   Scheduled  4m26s                  default-scheduler        Successfully assigned istio-system/istio-tracing-c7b59f68f-dzrz6 to vm-16-6-centos
  Normal   Killing    3m16s (x2 over 3m56s)  kubelet, vm-16-6-centos  Container jaeger failed liveness probe, will be restarted
  Warning  Unhealthy  3m13s (x7 over 4m23s)  kubelet, vm-16-6-centos  Readiness probe failed: HTTP probe failed with statuscode: 503
  Normal   Pulled     3m3s (x3 over 4m25s)   kubelet, vm-16-6-centos  Container image "docker.io/jaegertracing/all-in-one:1.16" already present on machine
  Normal   Created    3m3s (x3 over 4m25s)   kubelet, vm-16-6-centos  Created container jaeger
  Normal   Started    3m3s (x3 over 4m24s)   kubelet, vm-16-6-centos  Started container jaeger
  Warning  Unhealthy  2m56s (x7 over 4m16s)  kubelet, vm-16-6-centos  Liveness probe failed: HTTP probe failed with statuscode: 503
[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl  logs -f --tail 200 istio-tracing-c7b59f68f-dzrz6 -n istio-system
Error from server: Get https://10.0.16.6:10250/containerLogs/istio-system/istio-tracing-c7b59f68f-dzrz6/jaeger?follow=true&tailLines=200: dial tcp 10.0.16.6:10250: i/o timeout
```

## 在master下安装

在网上查找其他方案，发现可以在不加入node的情况下，去安装istio

1. 清理从节点，调整mater节点能部署pod

```
kubectl delete node  vm-16-6-centos
kubectl get no -o yaml | grep taint -A 5
kubectl taint nodes --all node-role.kubernetes.io/master
istioctl manifest apply --set profile=demo
```

2. 执行后发现容器正常一段时间后又异常了,查看污点和容忍度，发现虚机的硬盘不足：

```
[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl get no -o yaml | grep taint -A 5
    taints:
    - effect: NoSchedule
      key: node.kubernetes.io/disk-pressure
      timeAdded: "2022-04-16T00:56:21Z"
  status:
    addresses:
    
# 去掉污点
kubectl taint nodes --all node.kubernetes.io/disk-pressure:NoSchedule-
```

3. 清理后，重新执行就正常了：

```bash
[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl get pods -n istio-system
NAME                                   READY   STATUS    RESTARTS   AGE
grafana-78bc994d79-p5g42               1/1     Running   0          9m56s
istio-egressgateway-7c9f7d5bd6-h5swx   1/1     Running   0          10m
istio-ingressgateway-f9b47d445-n7crd   1/1     Running   0          10m
istio-tracing-c7b59f68f-kbfsk          1/1     Running   0          9m56s
istiod-5745bd5f6b-2ptpt                1/1     Running   0          10m
kiali-57fb5bb5c6-26wq8                 1/1     Running   0          9m55s
prometheus-78f785fc6b-nwpm8            2/2     Running   0          9m55s
```

# 清理istio

执行命令:
```
istioctl manifest generate --set profile=demo | kubectl delete -f -
```
