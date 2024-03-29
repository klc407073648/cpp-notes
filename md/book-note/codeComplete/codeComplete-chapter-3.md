# 第3章 三思而后行: 前期准备

[[toc]]

# 前期准备的重要性

使用高质量的实践方法是能够创造高质量软件的前提。

准备工作的中心目标就是降低风险：一个好的项目规划者能够尽可能早地将主要的风险清除掉，以使项目的大部分工作能够尽可能平稳地进行。

## 准备不周全的诱因

1. 人员能力不具备: 项目规划、需求分析全面准确、创造高质量的架构等都需要一定的经验。
2. 知道却不去做: 很多程序员陷入了**尽快开始编码的误区**，事先规划分析清楚逻辑，才能加快后续的开发
3. 管理者不理解: 很多管理者不懂程序员前期分析的重要性，只要求尽快写出代码

## 前期准备重要性的依据

1. 诉诸逻辑
    * 管理角度: 制定计划，规定时间、人数和资源
    * 技术角度: 构建的目标、正确性

2. 诉诸类比
    * 程序员作为软件食物链的最后一环(**架构师吃掉需求，设计师吃掉架构，而程序员则消化设计**)
    * 针对需要构建的每一个片段，弄清楚哪些是最关键的需求和架构要素，按照正确的顺序去做事情。

3. 诉诸数据
    * 发现错误的时间要尽可能接近引入该错误的时间。
    * 修复缺陷的成本随着“从引入缺陷到检测该缺陷之间的时间”变长而急剧增加。

# 分辨从事软件的类型

![](/_images/book-note/codeComplete/软件类型.png)

## 迭代开发法对前期准备的影响

* 序列式开发：仅仅依赖测试来发现缺陷。
    * 适用场景：需求稳定，设计直截了当，而且理解透彻；开发对于应用领域非常熟悉；项目风险小；长期可预测性很重要；后期变更需求设计代价比较高
* 迭代式开发：随着项目开发不断找出错误，进行修正。
    * 适用场景：需求没有理解透彻；设计复杂且具有挑战性；开发对于应用领域不熟悉；长期可预测性不重要；后期变更需求设计代价较低

# 问题定义

只定义问题是什么，不涉及具体的解决方案。

采用客户的语言来书写，从客户角度描述问题。

# 需求

需求详细描述软件系统具体应该做什么。

稳定需求是个神话 ———— 一旦需求稳定，项目就能以有序、可预测、平稳的方式，完成从架构、设计、编码以及测试等一系列工作。

但是，随着项目的推进，客户对项目的理解深入，能够更加清楚理解自己的需求，进而触发需求变更。

## 构建期间处理需求变更

* 根据需求核对表(checklist)来评估需求的质量
* 确保每一个人都知道需求变更的代价
* 建立一套变更控制程序
* 使用能适应变更的开发方法
* 放弃项目 —— 需求特别糟糕、且极不稳定
* 注意项目的商业价值

**需求核对表**

![](/_images/book-note/codeComplete/需求核对表1.png)

![](/_images/book-note/codeComplete/需求核对表2.png)

# 架构

> 软件架构(software architecture)也称系统架构(system architecture)、高层设计(high-level design) 或 顶层设计(top-level design)。

## 架构的典型组成部分

* 程序组织
    * 在架构中，列出多种方案，并阐述最终方案的理由
        * 需要定义程序的主要构造块(可能是类或多个类组成的子系统)，
        * 明确构造块的责任，且明确区别于其他构造块。
        * 架构应该详细阐述当前构造块，能直接或间接使用哪些构造块，不能使用哪些构造块。

* 主要的类
    * 类的责任，以及与其他类的交互。
    * 对于那些构成系统80%行为的20%的类进行详细说明。

* 数据设计
    * 主要文件和数据表的设计。

* 业务规则
    * 详细描述架构依赖的特定的业务规则
        * 例如，保持客户端与服务端信息及时同步(30s 心跳检测)

* 用户界面设计

* 资源管理
    * 对系统资源进行统一管理：数据库连接池、线程池、句柄等。

* 安全性
    * 建立威胁模型，包括处理缓冲区方法、处理非受信数据、错误消息的处理等。

* 性能
    * 需要关注性能，则要给出详细的性能目标。

* 可伸缩性
    * 系统增长以满足未来需求的能力。
    * 描述系统应该如何应对用户数量、服务器数量、网络节点数量、数据库记录数等增长。

* 互用性

* 国际化/本地化
    * 国际化(Internationalization,I18n)：以支持多个地域的技术活动。
    * 本地化(Localization,L10n)：翻译一个程序，以支持当地特定的语言工作。

* 输入/输出

* 错误处理

* 容错性
    * 系统使用**表决算法**，后台存在多种计算方法，可以取多个计算结果的均值、中值或众数来作为最终结果

* 架构可行性

* 过度工程
    * 健壮性：系统在检测到错误后继续运行的能力。
    * 系统的健壮程度由各个部分组成，取决于所有薄弱部分的乘积。