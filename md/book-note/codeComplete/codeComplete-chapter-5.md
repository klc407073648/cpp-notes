# 第5章 软件构建中的设计

[[toc]]

# 设计中的挑战

软件设计，即构思、创造或发明一套方案，把一份计算机软件的规格说明书要求转变为可以实际运行的软件。

* 设计是一个险恶的问题
    * 学校开发的项目和实际企业的项目大有不同
        * 学校项目：从头到尾是直线式的设计开发方式
        * 企业项目：需要应对变化，不断地调整完善，是迭代开发式的。

* 设计是了无章法的过程
    * 难以界定做到什么地步才算足够好。设计永无止境，到没有时间优化为止。(考虑项目的周期)

* 设计是确定取舍和调整顺序的过程
    * 去衡量彼此冲突的各项设计特性(例如，快速响应市场优于做出完整产品，可以先上线重点功能，后续再去补齐其他功能)

* 设计受到诸多约束
    * 人力、时间、资源成本

* 设计是不确定的
    * 解决问题的方法多种多样，不同的架构师风格也不一致，掌握的技术栈也不同

* 设计是一个启发式的过程
    * 设计过程中总会有试验和犯错误，一项技术也不可以通用于所有应用领域

* 设计是自然而然形成的
    * 分布式架构、云原生架构等，都是随着网络、科技不断进步以及业务需求不断变更下，逐渐萌发的技术。只有当前的技术无法满足实际的需求，才会促进大家去思考，如何解决当前面对的新问题。

# 关键的设计概念

## 软件的首要技术使命：管理复杂度

软件开发困难的两类问题

* 本质问题
    * 不断地去挖掘错综复杂，相互连接的整套软件系统的具体细节。很难精确而完整地识别出各种依赖关系与例外情况，设计出的系统只能大致正确而不能保证完全正确。
* 偶然问题
    * 偶然性：指一件事物碰巧拥有的属性，是附属的，任意的，非必要的或偶然出现的性质。
    * 偶然性问题由于编程语言的不断演进，操作系统的进步，集成编译环境的改善，在软件开发中的重要性也随着下降。

**如何去管理复杂度**

项目失败大多是归根于不尽人意的需求、规划和管理。但是，也存在由于技术因素导致失败的情况，当软件系统变得复杂，没人知悉修改这处代码会对其他代码带来什么影响时，项目也快走到尽头了。

在软件架构层面，通过将系统分解成多个子系统来降低问题的复杂度。人们通常能够理解多项简单的信息，而不是一项简单的信息，对信息进行合理的拆分便于人们理解。

**如何应对复杂度**

高代价、低效率的设计源于以下三种原因：

1. 用复杂方法解决简单问题
2. 用简单但错误的方法解决复杂问题
3. 用不恰当的复杂方法解决复杂问题

需要通过以下两种方法来管理复杂度

* 把任何人在同一时间需要处理的本质复杂度的量减到最少
* 不要让偶然性的复杂度无谓地快速增长

## 理想的设计特征

高质量的设计拥有很多常见的特征，要实现所有的目标比较困难，因为目标之间也会有相互抵触的情况，需要做出选择，确定一套折中的方案、

* 最小的复杂度
    * 做出简单易于理解的设计

* 易于维护
    * 能够自明的系统

* 松散耦合
    * 程序各个组成关联最小

* 可扩展性
    * 改动某个功能不影响其他功能

* 可重用性

* 高扇入
    * 定义：大量的类使用某个给定的类。
    * 意味着设计的系统能够很好地利用较低层次的工具类

* 低扇出
    * 定义：一个类少量或适中地使用其他的类。
    * 高扇出表明一个类使用大量的其他类，因此变得过于复杂。

* 可移植性

* 精简性
    * 设计的系统没有多余部分

* 层次性
    * 尽量保证系统各个分解层的层次性，从任意层面观察，都能得到某种一致性的效果。
    * 编写新系统负责和旧代码交互时，要让它能隐藏旧代码的低劣质量，同时为新的层次提供一组一致的服务。

* 标准技术
    * 使用标准化，常用的方法，让整个系统使人觉得熟悉

# 设计的层次

程序的设计层次如图所示：

![](/_images/book-note/codeComplete/程序的设计层次.png)

* 第1层：软件系统

* 第2层：分解为子系统和包
    * 识别出所有主要子系统，例如数据库、用户界面、业务规则、命令解释器和报表引擎。
    * 需要确定**不同子系统之间互相通信的规则**

当没有任何限制时，热力学第二定律就会起作用，整个系统的熵会增加。

原始：

![](/_images/book-note/codeComplete/六个子系统.png)

没有任何限制：

![](/_images/book-note/codeComplete/没有限制的子系统.png)

施加通信规则：

![](/_images/book-note/codeComplete/施加通信规则的子系统.png)

需要尽量简化子系统之间的交互关系：

* 最简单：子系统A去调用子系统B的子程序；
* 复杂一点：子系统A包含子系统B的类；
* 最复杂：子系统A继承子系统B的类。

程序中不应该有任何环形，即A调用B,B调用C,C调用A的情况。

* 第3层：分解为类
    * 类(Class)和对象(Object)的比较
    * 类似数据库术语中的模式(schema)和实例(instance)

* 第4层：分解成子程序
    * 将每个类细分为子程序

* 第5层：子程序内部的设计
    * 包括编写伪代码、选择算法、组织子程序内部代码块，以及用编程语言编写代码。

# 设计构造块：启发式方法

## 找出现实世界中的对象

使用对象进行设计的步骤：

* 辨识对象及其属性(方法和数据)   —— 顾客拥有名称、账单、地址等数据，和修改名称、修改地址等方法
* 确定可以对各个对象进行的操作   —— 
* 确认各个对象能对其他对象进行的操作  —— 关系通常有包含和继承
* 确定对象的哪些部分对其他对象可见   —— public 和 private的设置，例如，公有继承不能直接访问基类的私有方法
* 定义每个对象的公开接口

## 形成一致的抽象

抽象好处在于使你能够忽略无关的细节。

例如，接口里连接数据库，释放数据库连接等接口，都是抽象的，无需关注底层到底是用MySQL还是PostgreSQL。

抽象以简单视角考虑复杂问题，编程抽象，有利于站在高的角度看问题，能够更快、更稳妥地进行开发。

## 封装实现细节

封装 ———— 所见即所得，只能看到对外暴露的内容，不能看到对象的任何其他细节层次。

## 当继承能简化设计时就继承

定义对象之间的相同点和不同点。

可以利用已有的数据类型来定义新的数据类型。

## 隐藏秘密(信息隐藏)

设计类：关键点在于确定类的哪些特性对外暴露；哪些特性应该隐藏。

* 好的类接口就像冰山的尖儿，让类的大部分内容不会被暴露出来。
    * 例如，如果订单号按照2022010100001,2022010100002方式计算，很容易能知道网站的销售量。

![](/_images/book-note/codeComplete/冰山一角.png)

信息隐藏主要分为两大类：

* 隐藏复杂度
* 隐藏变化源

* 信息隐藏的障碍
    * 信息过度分散
    * 循环依赖
    * 把类内数据误认为全局数据
    * 性能的损耗

* 信息隐藏的价值
    * 便于修改程序
    * 有助于设计类的公开接口

## 找出容易改变的区域

优秀的设计师，都拥有一项特质 —— 对变化的预期能力。

好的程序设计面临的最大挑战就是适应变化。 ———— 目标：把不稳定的区域隔离出来，从而把变化所带来的影响限制在一个子程序、类或者包的内部。

应对各种变化的措施：

* 找出看起来容易变化的项目
* 把容易变化的项目分离出来
* 把看起来容易变化的项目隔离开来
    * 容易变化的区域
        * 业务规则
        * 硬件依赖
        * 输入和输出
        * 数据量限制

## 保持松散耦合

耦合度：类与类之间或子程序与子程序之间关系的紧密程度。

一个模块越容易被其他模块所调用，则它们之间的耦合关系越松散。

耦合种类：

* 简单数据参数耦合
* 简单对象耦合
* 对象参数耦合
* 语义上的耦合：需要了解模块内部工作原理

# 设计实践

* 分而治之
* 自上而下：从一般性的问题出发，把该问题分解成可控的部分
* 自下而上：从可控的部分出发，去构造一个通用的方案
* 建立试验性原型
* 合作设计





