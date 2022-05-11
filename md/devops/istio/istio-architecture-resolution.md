# 架构解析

作为新一代 Service Mesh 产品的领航者，Istio 创新性的在原有网格产品的基础上，添加了控制平面这一结构，使其产品形态更加的完善。这也是为什么它被称作第二代 Service Mesh 的原因。在此之后，几乎所有的网格产品都以此为基础进行架构的设计。下面介绍一下它的架构组成。

## Istio 的架构组成

Istio 的架构由两部分组成，分别是**<font color='red'>数据平面（Data Plane）和控制平面（Control Plane）</font>**。

**数据平面**

* 由整个网格内的 sidecar 代理组成，这些代理以 sidecar 的形式和应用服务一起部署。
* 每一个 sidecar 会接管<font color='red'>**进入和离开服务的流量**</font>，并配合控制平面完成流量控制等方面的功能。
* 可以把数据平面看做是网格内 sidecar 代理的网络拓扑集合。

**控制平面**

* 控制和管理数据平面中的 sidecar 代理，完成配置的分发、服务发现、和授权鉴权等功能。
* 架构中拥有控制平面的优势在于，可以统一的对数据平面进行管理。

<img src="/_images/devops/istio/istio-mesh-arch.png" alt="istio 架构" style="zoom: 50%;" /> 

# 数据平面

## Envoy

Istio 的数据平面默认使用 Envoy 作为 sidecar 代理，在未来也将支持使用 MOSN 作为数据平面。其流量控制功能主要分为三个方面：

- 请求路由和流量转移。
- 弹性能力：支持超时、重试和熔断等。
- 调试功能：如故障注入、流量镜像。

Envoy是一款由 Lyft 开源的高性能数据和服务代理软件，使用现代 C++ 语言（C++11 以及 C++14）开发，它提供了强大的流量治理能力和可观察性。其独创的 xDS 协议则成为了构建 Service Mesh通用数据面 API（UDPA）的基石。

具体来说，Envoy 具有以下的优点：

- 高性能：C++ 语言实现，基于 Libevent 事件机制以及非阻塞异步 IO，保障性能；
- 易扩展：利用其 L3/L4/L7 筛选器机制，Envoy可以在各个层次进行功能扩展。包括但不限于：额外代理协议支持、HTTP 流量治理功能扩展等等。且由于其良好的封装和现代 C++ 对各种操作的简化，其开发过程非常友好；此外，Envoy也提供了基于 WASM 的扩展支持以及基于 Lua 脚本的简单功能扩展；
- 多协议支持：原生支持代理 HTTP、Kafka、Dubbo、Redis 等多种协议；
- 动态化配置：基于 xDS 协议实现配置的完全动态化，简化配置更新操作，实现监听端口、路由规则、后端服务发现等全运行时动态下发及更新；
- 可观察性：内置日志，指标，追踪三个模块用于实现全方位、多维度流量和事件观察；
- HTTP 筛选器：社区原生提供了大量的功能强大的 HTTP 筛选器如限流、认证鉴权、缓存、压缩、GRPC 协议转换等等，开箱即用；
- 社区开放活跃：Envoy完全开源，不存在对应的商业版本，保证了它的发展不会受限于商业化；而且Envoy社区非常活跃，不断向前推动 Envoy的演进和发展。

其系统架构：

在 Envoy 中，

* 数据请求的入口方向被称之为下游（Downstream），而数据请求的出口方向则称之为上游（Upstream）。
* Envoy 接收来自下游的请求并将之转发给上游。
  *  在下游方向，Envoy 使用监听器（Listener）来监听数据端口，接受下游连接和请求；
  * 在上游方向，Envoy 使用集群（Cluster）来抽象上游服务，管理连接池以及与之相关的健康检查等配置。
  * 而在监听器和集群之间，Envoy 则使用筛选器（Filter）和路由（Router）将两者联系在一起。
    * 筛选器是 Envoy 中可拔插的多种功能组件的统称，简单来说，筛选器就是插件。
    *  L3/L4 筛选器主要用于处理连接和协议解析，不同的 L3/L4 筛选器可以使得 Envoy 代理不同协议的网络数据。
    * Envoy 中最为核心的 HTTP 代理功能就是构筑在一个名为“HTTP 连接管理器（Http Connection Manager）”的 L4 筛选器之上的。
    * L7 筛选器（绝大部分情况下 L7 筛选器都可以和 HTTP 筛选器划等号）则是作为 L4 筛选器的子筛选器存在，用于支撑实现更加丰富的流量治理能力。

<font color='red'>**监听器、集群、路由和筛选器**</font>构成了 Envoy 最为核心的骨架。

 <img src="/_images/devops/istio/concepts-envoy-arch-simple.png" alt="concepts-envoy-arch-simple" style="zoom: 33%;" />

# 控制平面

## Pilot

Pilot主要功能就是管理和配置部署在特定 Istio 服务网格中的所有 sidecar 代理实例。它管理 sidecar 代理之间的路由流量规则，并配置故障恢复功能，如超时、重试和熔断。

 <img src="/_images/devops/istio/pilot-arch.png" alt="pilot-arch" style="zoom:50%;" />

根据上图， Pilot 几个关键的模块如下。

**抽象模型 （Abstract Model）**

为了实现对不同服务注册中心 （Kubernetes、consul） 的支持，Pilot <font color='red'>需要对不同的输入来源的数据有一个统一的存储格式</font>，也就是抽象模型。

抽象模型中定义的关键成员包括 HostName（service 名称）、Ports（service 端口）、Address（service ClusterIP）、Resolution （负载均衡策略） 等。

**平台适配器 （Platform adapters）**

Pilot 的实现是基于平台适配器（Platform adapters） 的，借助<font color='red'>平台适配器 Pilot 可以实现服务注册中心数据到抽象模型之间的数据转换</font>。

例如 Pilot 中的 Kubernetes 适配器通过 Kubernetes API 服务器得到 Kubernetes 中 service 和 pod 的相关信息，然后翻译为抽象模型提供给 Pilot 使用。

通过平台适配器模式， Pilot 还可以从 Consul 等平台中获取服务信息，还可以开发适配器将其他提供服务发现的组件集成到 Pilot 中。

**xDS API**

Pilot 使用了一套起源于 Envoy 项目的标准数据面 API 来将服务信息和流量规则下发到数据面的 sidecar 中。这套标准数据面 API，也叫 xDS。

Sidecar 通过 xDS API 可以动态获取 Listener （监听器）、Route （路由）、Cluster （集群）及 Endpoint （集群成员）配置：

- LDS，Listener 发现服务：Listener 监听器控制 sidecar 启动端口监听（目前只支持 TCP 协议），并配置 L3/L4 层过滤器，当网络连接达到后，配置好的网络过滤器堆栈开始处理后续事件。
- RDS，Router 发现服务：用于 HTTP 连接管理过滤器动态获取路由配置，路由配置包含 HTTP 头部修改（增加、删除 HTTP 头部键值），virtual hosts （虚拟主机），以及 virtual hosts 定义的各个路由条目。
- CDS，Cluster 发现服务：用于动态获取 Cluster 信息。
- EDS，Endpoint 发现服务：用于动态维护端点信息，端点信息中还包括负载均衡权重、金丝雀状态等，基于这些信息，sidecar 可以做出智能的负载均衡决策。

通过采用该标准 API， Istio 将控制面和数据面进行了解耦，为多种数据平面 sidecar 实现提供了可能性。例如蚂蚁金服开源的 Golang 版本的 Sidecar [MOSN (Modular Observable Smart Network)](https://github.com/mosn/mosn)。

**用户 API （User API）**

Pilot 还定义了一套用户 API， 用户 API 提供了面向业务的高层抽象，可以被运维人员理解和使用。

运维人员使用该 API 定义流量规则并下发到 Pilot ，这些规则被 Pilot 翻译成数据面的配置，再通过标准数据面 API 分发到 sidecar 实例，可以在运行期对微服务的流量进行控制和调整。

通过运用不同的流量规则，可以对网格中微服务进行精细化的流量控制，如按版本分流、断路器、故障注入、灰度发布等。

**Pilot 实现**

 ![pilot](/_images/devops/istio/pilot.png)

图中实线连线表示控制流，虚线连线表示数据流。带 `[pilot]` 的组件表示为 Pilot 组件，图中关键的组件如下：

- Discovery service：即 pilot-discovery，主要功能是从 Service provider（如 kubernetes 或者 consul ）中获取服务信息。
  - 从 Kubernetes API Server 中获取流量规则（Kubernetes CRD Resource），并将服务信息和流量规则转化为数据面可以理解的格式，通过标准的数据面 API 下发到网格中的各个 sidecar 中。

- agent：即 pilot-agent 组件，该进程根据 Kubernetes API Server 中的配置信息生成 Envoy 的配置文件，负责启动、监控 sidecar 进程。
- proxy：既 sidecar proxy，是所有服务的流量代理，直接连接 pilot-discovery ，间接地从 Kubernetes 等服务注册中心获取集群中微服务的注册情况。
- service A/B：使用了 Istio 的应用，如 Service A/B，的进出网络流量会被 proxy 接管。

## Citadel

Citadel 是 Istio 中专门负责安全的组件，内置有身份和证书管理功能，可以实现较为强大的授权和认证等操作。

### Citadel 基本功能

总体来说，Istio 在安全架构方面主要包括以下内容：

- 证书签发机构（CA）负责密钥和证书管理
- API 服务器将安全配置分发给数据平面
- 客户端、服务端通过代理安全通信
- Envoy代理管理遥测和审计

### Citadel 工作原理

Citadel 主要包括 CA 服务器、SDS 服务器、证书密钥控制器等模块，它们的工作原理如下。

**CA 服务器**

Citadel 中的 CA 签发机构是一个 gRPC 服务器，启动时会注册两个 gRPC 服务。

* CA 服务：用来处理 CSR 请求（certificate signing request）；
* 证书服务：用来签发证书。
* CA 首先通过 `HandleCSR` 接口处理来自客户端的 CSR 请求，对客户端进行身份验证（包括 TLS 认证和 JWT 认证），验证成功后会调用 `CreateCertificate` 进行证书签发。

**SDS 服务器**

SDS 即安全发现服务（Secret discovery [service](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#service)），它是一种在运行时动态获取证书私钥的 API，[Envoy](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#envoy) 代理通过 SDS 动态获取证书私钥。[Istio](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#istio) 中的 SDS 服务器负责证书管理，并实现了安全配置的自动化。相比传统的方式，使用 SDS 主要有以下优点：

- 无需挂载 Secret 卷
- 动态更新证书，无需重启
- 可以监听多个证书密钥对 

 <img src="/_images/devops/istio/identity-provision.png" alt="identity-provision" style="zoom:50%;" />

目前的版本中，SDS 是默认开启的，它的工作流程如下：
- [Envoy](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#envoy) 通过 SDS API 发送证书和密钥请求
- [istio](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#istio)-agent 作为 [Envoy](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#envoy) 的代理，创建一个私钥和证书签名请求（CSR），并发送给 istiod
- CA 机构验证收到的 CSR 并生成证书
- [istio](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#istio)-agent 将私钥和从 istiod 收到的证书通过 SDS API 发送给 [Envoy](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#envoy)
- 以上流程周期性执行实现密钥和证书轮换

**证书密钥控制器**

证书密钥控制器（CaSecretController）监听 `istio.io/key-and-cert` 类型的 Secret 资源，它会周期性的检查证书是否过期，并更新证书。

**证书轮换**

如果没有自动证书轮换功能，当证书过期时，就不得不重启签发，并重启代理。证书轮换解决了这一问题，提高了服务的可用性。[Istio](https://www.servicemesher.com/istio-handbook/GLOSSARY.html#istio) 里通过一个轮换器（Rotator）自动检查自签名的根证书，并在证书即将过期时进行更新，它本质上是一个协程（goroutine）在后台轮询实现的：

- 获取当前证书，解析证书的有效期并获取下一次轮换时间
- 启动定时器，如果发现证书到达轮换时间，从 CA 获取最新的证书密钥对
- 更新证书

## Galley

Galley 是 Istio 1.1 版本中新增加的组件，其目的是将 Pilot 和底层平台（如 Kubernetes）进行解耦。它分担了原本 Pilot 的一部分功能，主要负责配置的验证、提取和处理等功能。

## Istio 的设计目标

Istio 一经发布就希望打造一个最终形态的 Service Mesh 产品，功能异常丰富，可以说是胸怀宇宙。在设计理念上，Istio 并未遵从最小可行性产品（MVP）的演进策略，而是较为激进的全盘压上，想借此提供一个完善而强大的产品和架构体系。下面的几点设计目标促成了其架构的形态：

- 对应用透明：从本质上来说，对应用透明是 Service Mesh 的特性，一个合格的 Service Mesh 产品都应该具有这一特性，否则也就失去了网格产品的核心竞争力。Istio 在这一点上做的无可厚非。通过借助 Kubernetes 的 admission controller ，配合 webhook 可以完成 sidecar 的自动注入。在配置方面，也基本做到了对应用无侵入。
- 可扩展性：Istio 认为，运维和开发人员随着深入使用 Istio 提供的功能，会逐渐涌现更多的需求，主要集中在策略方面。因此，为策略系统提供足够的扩展性，成为了 Istio 的一个主要的设计目标。Mixer 组件就是在这一理念下诞生的，它被设计为一个插件模型，开发人员可以通过接入各种适配器（Adapter），来实现多样化的策略需求。毫不夸张的说，Mixer 的这种插件设计为 Istio 提供了无限的扩展性。
- 可移植性：考虑到现有云生态的多样性，Istio 被设计为可以支持几种不同的底层平台，也支持本地、虚拟机、云平台等不同的部署环境。不过从目前的情况来看，Istio 和 Kubernetes 还是有着较为紧密的依赖关系。
- 策略一致性：Istio 使用自己的 API 将策略系统独立出来，而不是集成到 sidecar 中，这允许服务根据需要直接与之集成。同时，Istio 在配置方面也注重统一和用户体验的一致。一个典型的例子是路由规则都统一由虚拟服务来配置，可在网格内、外以及边界的流量控制中复用。

## Istio 的架构变迁之旅

从 2017 年 5 月发布以来，Istio 经历了四个重要的版本和由此划分的三个发展阶段。在不到三年的产品迭代过程中，出现了两次重大的架构变动。功能的调整无可厚非，但架构的多次重构就较为少见了。我们来简要分析一下这个变迁历程。

- 0.1 版本：2017 年 5 月发布。作为第二代 Service Mesh 的开创者，宣告了 Istio 的诞生，也燃起了网格市场的硝烟与战火。
- 1.0 版本：发布于 2018 年 7 月，对外宣传生产环境可用。从 0.1 到 1.0 版本，开发时间经历了一年多，但持续的发布了多个 0.x 版本，这一阶段处于快速迭代期。
- 1.1 版本：发布于 2019 年 3 月，号称企业级可用的版本。一个小的版本号变化居然耗费了半年之久，其主要原因是出现了第一次架构重构，这一阶段算是调整期。
- 1.5 版本：发布于 2020 年 3 月，再次进行架构的重建，将多组件整合为单体形态的 istiod。从 1.1 到 1.5 版本的一年中，Istio 开始遵循季节性发布，进入了产品的稳定发展期。

![Istio 架构演进](/_images/devops/istio/istio-arch-evolution.png)

在第一次架构变化中，Istio 团队认为虽然 Mixer 的插件模型为其带来了扩展性方面的优势，但与 Adapter 的相互依赖关系使得它会受到插件变化的影响。1.1 版本彻底贯彻了解耦原则，解决了存在的耦合问题，职责分明，结构清晰，做到了设计上的极致。然而物极必反，高度松散的结构引入了性能方面的问题，同时在易用性上也受人诟病。市场是检验真理的唯一标准，看到 Istio 在市场上的惨淡成绩后，Istio 团队痛定思痛，终于下定决心断臂自救，在 1.5 版本的时候以回归单体的形式进行了架构的重建，完成了一次自我救赎。

最新的 1.5 版本结构简洁，降低系统复杂度的同时也提升了易用性。尽管新版本还未受到市场的检验，但 Istio 团队敢于变革的勇气让我们对它的未来又有了新的期待。

接下来，我们会从控制平面和数据平面两方面，来详细介绍架构中各组件的主要功能和工作流程。
