# CI/CD - 部署

# 参考资料

* [SFTP协议和SSH协议简介](https://zhuanlan.zhihu.com/p/479742838)

# 刀耕火种的手工作坊时代：古老的SSH

以前的部署方式就是通过ssh实现，ssh是Linux内置的一个网络协议，通过ssh来实现远程登录以及文件传输。比较常见的可以通过ssh的sftp协议将本地编译好的应用（比如java中的包）传输到服务器上，或者通过ssh远程登录到服务器上然后git下载源码编译，然后在服务器上起一个持久化的应用。

进一步，可以编写一些自动化脚本帮助实现这类操作，例如自动运维、一键部署等。

然而，总的来看，将一个后端服务在服务器上启动的方式有很多种，但是这些方式也还是逃不开粗糙的本质，透过花里胡哨的操作与自动化脚本，究其本质还是脱离不了ssh的限制。其内核还是一个一对一的操作，即一个终端对应一个服务端，这就决定了不论怎么样，这种部署方式对于大规模去应用是不可行的。不管做到何种地步都逃脱不了其手工作坊的本质，更何况还会有各种各样运行环境带来的边界问题。

# 工业革命的制品工坊：Docker Image

docker的环境是**一个系统级别的环境**，比起应用级别的环境更加底层也更加彻底。**系统级别的环境隔离意味着在所有的环境都拥有完全一样的上下文**，一台服务器的成功意味着所有服务器的成功。所以我们可以看到，环境隔离是多么重要，而的成功也很大程度上来源于此。

![](/_images/devops/ci/Docker_Image.png)

docker意味着所有的操作都是可复制的。而工业制品与手工业的区别也在于此，后续，软件工程师们围绕着的强大隔离性和原子性，出现了诸如自动扩容、滚动升级、高可用、分布式以CI/CD等一系列提升软件质量与服务稳定的优秀实践。

# 基于Docker Image的持续部署

基于Docker的持续部署是Signal（发送端）、Proxy（接收端）、worker（执行端）组成。可以将一次git提交作为发送端，触发Jenkins流水线任务（接收端）、去执行预设的Pipeline脚本（执行端）。同时，执行端可以是Docker Compose、k8s等。

需要理解 发送端 ——> 接收端 ——> 执行端 这个流程

![](/_images/devops/ci/部署流程.png)