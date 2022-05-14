# Istio

> istio是kubernetes好帮手，可以帮kubernetes实现服务治理功能。
> kubernetes可以帮助istio实现

[[toc]]

* 数据平面
  * 利用一个pod可以运行多个容器的特点，实现数据平面功能
* 统一服务发现
  * Ingress是k8s的资源，外部请求通过Ingress, 转发给Pod(Ingress里配置域名的映射)
  *  配置提供外部可访问的 URL、负载均衡、SSL、基于名称的虚拟主机等。
* 基于CRD规则扩展自定义资源
  * istio通过CRD规则自定义资源，而资源数据通过apiserver保存到etcd里面

# 参考

* [istio-handbook](https://www.servicemesher.com/istio-handbook/concepts/microservices-in-post-kubernetes-era.html)
* [kubernetes-handbook](https://jimmysong.io/kubernetes-handbook/concepts/crd.html)
* [istio-handbook](https://jimmysong.io/istio-handbook)

https://cloud.tencent.com/developer/news/712301

https://github.com/chillzhuang/SpringBlade

注册中心

https://blog.csdn.net/qq_38340581/article/details/115540868

https://pro.ant.design/zh-CN/docs/getting-started



n > source-map-resolve > urix@0.1.0: Please see https://github.com/lydell/urix#deprecated
[2/4] Fetching packages...
error eslint-plugin-jest@26.1.4: The engine "node" is incompatible with this module. Expected version "^12.22.0 || ^14.17.0 || >=16.0.0". Got "14.15.0"
error Found incompatible module.
info Visit https://yarnpkg.com/en/docs/cli/install for documentation about this command.



# 使用

```
kubectl get pods -n kube-system | grep Evicted | awk '{print $1}' | xargs kubectl delete pod -n kube-system # k8s 批量删除Evicted pod
rm -rf  /var/lib/docker/image/overlay2/imagedb/content/sha256/ #删除无法docker rmi的镜像

kubectl exec -it podName  -c  containerName -n namespace -- shell comand

kubectl exec -it istio-ingressgateway-f9b47d445-8vq7h -c istio-proxy -n istio-system -- /bin/bash
```

