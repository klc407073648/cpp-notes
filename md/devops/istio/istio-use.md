# istio 使用

Bookinfo 是 [Istio](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#istio) 社区官方推荐的示例应用之一。它可以用来演示多种 [Istio](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#istio) 的特性，并且它是一个异构的微服务应用。该应用由四个单独的微服务构成。 这个应用模仿了在线书店，可以展示书店中书籍的信息。例如页面上会显示一本书的描述，书籍的细节（ ISBN、页数等），以及关于这本书的一些评论。

Bookinfo 应用分为四个单独的微服务， 这些服务对 [Istio](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#istio) 并无依赖，但是构成了一个有代表性的服务网格的例子：它由多个不同语言编写的服务构成，并且其中有一个应用会包含多个版本。

- `productpage` 会调用 `details` 和 `reviews` 两个微服务，用来生成页面。
- `details` 中包含了书籍的信息。
- `reviews` 中包含了书籍相关的评论。它还会调用 `ratings` 微服务。
- `ratings` 中包含了由书籍评价组成的评级信息。

`reviews` 微服务有 3 个版本，可用来展示各服务之间的不同的调用链路：

- v1 版本不会调用 `ratings` 服务。
- v2 版本会调用 `ratings` 服务，并使用 1 到 5 个黑色星形图标来显示评分信息。
- v3 版本会调用 `ratings` 服务，并使用 1 到 5 个红色星形图标来显示评分信息。

下图展示了这个应用的端到端架构。

 ![Bookinfo-Application-without-Istio](/_images/devops/istio/Bookinfo-Application-without-Istio.png)

# 启动应用服务

1. 创建命名空间`istio-ns`，并打上标签 `istio-injection=enabled`

```
[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl create namespace istio-ns
namespace/istio-ns created
[root@iZuf61kbf845xt6tz10abgZ ~]# kubectl label namespace istio-ns istio-injection=enabled
namespace/istio-ns labeled
[root@iZuf61kbf845xt6tz10abgZ ~]# cd /home/istio/istio-1.5.0/
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# kubectl apply -f samples/bookinfo/platform/kube/bookinfo.yaml -n istio-ns
service/details created
serviceaccount/bookinfo-details created
deployment.apps/details-v1 created
service/ratings created
serviceaccount/bookinfo-ratings created
deployment.apps/ratings-v1 created
service/reviews created
serviceaccount/bookinfo-reviews created
deployment.apps/reviews-v1 created
deployment.apps/reviews-v2 created
deployment.apps/reviews-v3 created
service/productpage created
serviceaccount/bookinfo-productpage created
deployment.apps/productpage-v1 created
```

2. 查看服务和pod的状态

```
# pod处于Init状态
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# kubectl get pods -n istio-ns 
NAME                              READY   STATUS            RESTARTS   AGE
details-v1-74f858558f-m4lg8       0/2     Init:0/1   0          4s
productpage-v1-76589d9fdc-fzwlw   0/2     Init:0/1   0          3s
ratings-v1-7855f5bcb9-zvq7k       0/2     Init:0/1   0          4s
reviews-v1-64bc5454b9-l4ffj       0/2     Init:0/1   0          3s
reviews-v2-76c64d4bdf-jdvhw       0/2     Init:0/1   0          4s
reviews-v3-5545c7c78f-xfwvg       0/2     Init:0/1   0          4s

# pod处于PodInitializing状态
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# kubectl get pods -n istio-ns
NAME                              READY   STATUS            RESTARTS   AGE
details-v1-74f858558f-m4lg8       0/2     PodInitializing   0          6s
productpage-v1-76589d9fdc-fzwlw   0/2     PodInitializing   0          5s
ratings-v1-7855f5bcb9-zvq7k       0/2     PodInitializing   0          6s
reviews-v1-64bc5454b9-l4ffj       0/2     PodInitializing   0          5s
reviews-v2-76c64d4bdf-jdvhw       0/2     PodInitializing   0          6s
reviews-v3-5545c7c78f-xfwvg       0/2     PodInitializing   0          6s

# 查看pod详细信息，发现在拉取镜像
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# kubectl describe pod details-v1-74f858558f-m4lg8 -n istio-ns

Events:
  Type    Reason     Age   From                              Message

----    ------     ----  ----                              -------

  Normal  Scheduled  114s  default-scheduler                 Successfully assigned istio-ns/details-v1-74f858558f-m4lg8 to izuf61kbf845xt6tz10abgz
  Normal  Pulled     112s  kubelet, izuf61kbf845xt6tz10abgz  Container image "docker.io/istio/proxyv2:1.5.0" already present on machine
  Normal  Created    112s  kubelet, izuf61kbf845xt6tz10abgz  Created container istio-init
  Normal  Started    111s  kubelet, izuf61kbf845xt6tz10abgz  Started container istio-init
  Normal  Pulling    109s  kubelet, izuf61kbf845xt6tz10abgz  Pulling image "docker.io/istio/examples-bookinfo-details-v1:1.15.0"
  
# 等待一段时间后，服务正常
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# kubectl get pods -n istio-ns
NAME                              READY   STATUS    RESTARTS   AGE
details-v1-74f858558f-m4lg8       2/2     Running   0          22m
productpage-v1-76589d9fdc-fzwlw   2/2     Running   0          22m
ratings-v1-7855f5bcb9-zvq7k       2/2     Running   0          22m
reviews-v1-64bc5454b9-l4ffj       2/2     Running   0          22m
reviews-v2-76c64d4bdf-jdvhw       2/2     Running   0          22m
reviews-v3-5545c7c78f-xfwvg       2/2     Running   0          22m
```

3. 确定 Ingress 的 IP 和端口

现在 Bookinfo 服务启动并运行中，您需要使应用程序可以从外部访问 Kubernetes 集群，可以使用浏览器通过访问 [Istio](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#istio) Gateway 来访问应用，通过以下操作步骤来实现。

* 应用程序定义 Ingress 网关：

```
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# kubectl apply -f samples/bookinfo/networking/bookinfo-gateway.yaml -n istio-ns
gateway.networking.istio.io/bookinfo-gateway created
```

* 确认网关创建完成：

```
[root@iZuf61kbf845xt6tz10abgZ istio]# kubectl get gateway -n istio-ns
NAME               AGE
bookinfo-gateway   34m
```

* 设置访问网关的 `INGRESS_HOST` 和 `INGRESS_PORT` 变量，例如node port模式。即当前环境未使用外部负载均衡器，需要通过 node port 访问。执行如下命令:

```
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# export INGRESS_PORT=$(kubectl -n istio-system get service istio-ingressgateway -o jsonpath='{.spec.ports[?(@.name=="http2")].nodePort}')
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# export SECURE_INGRESS_PORT=$(kubectl -n istio-system get service istio-ingressgateway -o jsonpath='{.spec.ports[?(@.name=="https")].nodePort}')
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# export INGRESS_HOST=127.0.0.1
```

* 设置 `GATEWAY_URL`：

```
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# export GATEWAY_URL=$INGRESS_HOST:$INGRESS_PORT
[root@iZuf61kbf845xt6tz10abgZ istio-1.5.0]# echo $GATEWAY_URL
127.0.0.1:30069
```

* 集群外部访问应用
  * 确认可以用浏览器打开网址`http://$GATEWAY_URL/productpage`，来浏览应用的 Web 页面。如果刷新几次应用的页面，就会看到 `productpage` 页面中会随机展示 `reviews` 服务的不同版本的效果（红色、黑色的星形或者没有显示）。`reviews` 服务出现这种情况是因为默认情况下的配置会随机访问三个版本，如果想设置个性化配置则可以用 [Istio](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#istio) 来控制版本的路由。(http://139.196.82.84:30069/productpage)

reviews_1:

![reviews_1](/_images/devops/istio/reviews_1.png)

reviews_2:

![reviews_2](/_images/devops/istio/reviews_2.png)

reviews_3:

![reviews_3](/_images/devops/istio/reviews_3.png) 

# 使用场景

注意事项：

* 每次执行完后，要执行要delete删除：`kubectl delete -f virtual-service-reviews-50-v3.yaml -n istio-ns`

## 基于版本方式控制流量

执行命令：

* 进入指定路径，创建所有规则，然后创建指向v3的service,不断刷新 http://139.196.82.84:30069/productpage 界面，只会显示上述reviews_3的图

```
cd /home/istio/istio-1.5.0/samples/bookinfo/networking/
kubectl apply -f destination-rule-all.yaml -n istio-ns
kubectl apply -f virtual-service-reviews-v3.yaml -n istio-ns
```

## 基于权重方式控制流量

执行命令：

* 不断刷新 http://139.196.82.84:30069/productpage 界面，会出现reviews_1和reviews_3交替出现的情况

```
kubectl apply -f virtual-service-reviews-50-v3.yaml  -n istio-ns

kubectl delete -f virtual-service-reviews-50-v3.yaml  -n istio-ns
```

## 基于用户流量控制

执行命令：

* 只有请求header头部带jason才访问reviews_2，否则访问reviews_3

```
kubectl apply -f virtual-service-reviews-jason-v2-v3.yaml  -n istio-ns
```

## 故障注入

执行命令：

* 非jason用户访问时，会有50%概率，延迟2s返回结果。

```
kubectl apply -f fault-injection-reviews-v3.yaml -n istio-ns
```

![fault-inject](/_images/devops/istio/fault-inject.png)

## 流量迁移

执行命令，整个过程完成了从v1版本到v3版本的流量的稳步切换：

* 首先所有流量都到v1版本
* 然后v1,v3版本各50%
* 最后全部切到v3版本

```
kubectl apply -f virtual-service-all-v1.yaml -n istio-ns
kubectl apply -f virtual-service-reviews-50-v3.yaml -n istio-ns
kubectl apply -f virtual-service-reviews-v3.yaml -n istio-ns
```









