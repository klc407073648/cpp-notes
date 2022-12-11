# ♥优质博客♥

# 优质博客推荐

* [酷 壳 – CoolShell](https://www.coolshell.cn/)
* [维基百科 —— 查概念](https://encyclopedia.thefreedictionary.com/)
* 很多经典的方法论，都是很老的前人经验积累的内容，多看一些基础性文章

# 文章推荐

* [研发共建」提升中台效能初探](https://tech.youzan.com/open-source-mode-from-middle-platform/)
::: details
* 团队建设中台，提高系统的可复用性，降低重复功能的研发成本

* 问题：各个业务域及子业务域有自己的需求优先级列表backlog, 中台如何应对各个业务域不同的诉求？

1. 建立公司级 backlog 运作机制
2. 建立基于 OKR 的目标对齐机制
3. 中台按比例支持各业务域
4. 研发共建，开发中台代码，供其他业务团队开发中台代码

![](/_images/article/read/业务和中台需求规划的示意图.png)
:::
    
* [有赞持续集成容器化实践](https://tech.youzan.com/cd-in-k8s/)
::: details
* Jenkins CI 采用的是 Master-Slave 架构, Master 和 Slave 都是物理机搭建。存在如下问题：

1. 当 Job 越来越多时需要通过增加 Slave 机器来解决，新增 Slave 上的软件得重新安装。
2. 资源分配不均衡有浪费，有的 Slave 上运行的 Job 出现排队等待，而有的 Slave 处于空闲状态。
3. 每个 Slave 总有点差异维护起来比较麻烦。
4. 当 Master 有故障时，整个流程都不可用。

* 解决方案：kubernetes Jenkins CI/CD 技术，将 Jenkins Master 和 Slave 交给 k8s 动态调度

* 工作流程： 当调用 Jenkins Master API 发起构建请求时，Jenkins k8s plugin 会根据 Job 配置的 Label 动态创建一个运行在 Pod Jenkins Slave 并注册到 Master 上，当 Job 结束后，这个 Slave 会被注销并且这个 Pod 也会自动删除，恢复到最初状态,这样集群资源得到充分的利用。
:::

* 陈皓文章收录
    * [如何超过大多数人](https://coolshell.cn/articles/19464.html)
    * [如何做一个有质量的技术分享](https://coolshell.cn/articles/21589.html)
    * [技术人员的发展之路](https://coolshell.cn/articles/17583.html)
    * [我做系统架构的一些原则](https://coolshell.cn/articles/21672.html)

* [Service Mesh在有赞的实践与发展](https://tech.youzan.com/service-meshzai-you-zan-de-shi-jian-yu-fa-zhan/)

* [Service Mesh服务网格](https://zhuanlan.zhihu.com/p/61901608)

* [最经典的两种软件架构模式](https://tech.youzan.com/zui-jing-dian-de-liang-chong-ruan-jian-jia-gou-mo-shi/)

* [如何优雅地记录操作日志](https://tech.meituan.com/2021/09/16/operational-logbook.html)


# 问题解决

* [iptables 详解](https://blog.cdn.net/shujuliu818/article/detais/125649998)

# 一手英文文献

* [Service Mesh](https://philcalcado.com/2017/08/03/pattern_service_mesh.html) 

# TO READ

* [编程能力与编程年龄](https://coolshell.cn/articles/10688.html)

* [云飞的博客](https://blog.codingnow.com/)

* [30 个提升团队研发效能的锦囊](https://mp.weixin.qq.com/s/RyqO8ry29zAL40ToVitxTQ)

https://github.com/easychen/howto-make-more-money

article-reading-system-arch.md 文章里的论文待阅读

