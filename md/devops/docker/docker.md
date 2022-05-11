# 容器技术Docker、Docker-Compose、k8s的演变

越来越多的应用开始容器化以及上云，可能有些人直接接触的就是k8s(Kubernetes)的概念以及操作了，但是理清一下容器化技术的一些演变过程，是一件很有意思的事情，同时也可以加强我们对容器化技术的深入理解和具体场景下运用哪种技术。

## Docker vs 虚拟机
  KVM技术的发展，解放了单台服务器物理机的资源过剩的浪费，虚拟机的资源互相独立，部署应用不受影响，但缺点是占用资源多，有安全补丁更新时候要一起更新，管理起来比较麻烦。容器Docker就是为了解决这种困境，在耗费资源低的情况下，又可以方便部署资源和依赖互相独立的应用，从而实现快速部署。他们俩的层级差异如图：

![dockerVsVm](/_images/devops/docker/dockerVsVm.png)

![docker](/_images/devops/docker/docker.png)

  正如docker的鲸鱼图上的集装箱一样，docker的容器运行是以沙盒的机制运行，共享底层操作系统，会把应用需要的依赖打包在一起，以沙盒的方式，在同类型的操作系统上，可以自由迁移部署运行，如此就可以极大地解放了部署环境不一致的问题。

## Docker-Compose 的诞生
  容器化的盛行，也带来了新的问题，那就是如何高效地去部署和管理这些镜像呢？因为比较大型的应用服务，往往需要多个组件一起合作才能正常运行，这就给单docker容器部署提出了挑战，Docker-Compose就像下面这只八爪章鱼，可以同时进行多容器的构建以及部署运行。

![docker-compose](/_images/devops/docker/docker-compose.png)

## k8s(Kubernetes)的横空出世 vs Docker Swarm
  Docker和Docker-Compose的运用，充分地把单物理服务器的性能充分利用起来，并且可以快速地进行持续交付。但是如何把如下图中A机器的容器镜像迁移到其他服务器以及如果遇到高并发，如何进行负载均衡分流呢？

![负载均衡](/_images/devops/docker/负载均衡.png)

  重复地拷贝一下镜像到B服务器再运行？那如何高效地进行监控各个容器的健康运行情况以及崩溃后如何迁移服务呢？集群的管理问题，此时出现了Docker Swarm技术，是docker自家的技术，但是Google接着开源了其内部用了很久的容器治理编排工具Kubernetes，以其高效以及智能自动化的管理机制，吸引了大批开源开发者以及公司的青睐，从此一战成名，Docker Swarm的市场份额进一步低迷。故这里只介绍下k8s主要的原理以及解决了哪些痛点的问题。

![k8s](/_images/devops/docker/k8s.png)

  k8s就像一个领航员，把各种集装箱（container）有条不紊地组装起来，着重提供如下功能：

1. 快速部署功能：定义对应的charts，可以方便把大型的应用部署上去。
2. 智能的缩扩容机制：部署时候会自动去考虑容器应该部署在哪个服务器上，以及副本的数量可以自定义。
3. 自愈功能：某个节点的服务崩溃了，可以自动迁移到另外一个服务器节点来恢复来实现高可用。
4. 智能的负载均衡：利用Ingress，可以实现流量通过域名访问进来时候，进行流量的分流到不同服务器上。
5. 智能的滚动升降级：升级或者降级时候，会逐个替换，当自定义数量的服务升级OK后，才会进行其他的升级以及真正销毁旧的服务。

## 几种技术的应用场景及资源占用情况

技术 | 应用场景	资源占用情况
---|---
Docker | 单机部署简单应用 
Docker-Compose | 单机/少数机器部署应用 
k8s | 集群部署高可用应用 



#  Docker Compose 文件转换为 Kubernetes 资源

[docker-compose To K8s](https://kubernetes.io/zh/docs/tasks/configure-pod-container/translate-compose-kubernetes/)

docker **可视化管理工具**  Weave Scope  	https://github.com/weaveworks/scope

[portainer](https://github.com/portainer/portainer)

https://blog.csdn.net/horsefoot/article/details/51749528

