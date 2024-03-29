# 产品 - 兼容性原则

## 背景

系统对外是一个整体，兼容性主要考虑不同系统之间的接口兼容，操作维护呈现兼容，新增功能开启兼容等；

从单体时代到微服务时代后，出现如下三个显著变化:

1. 底层硬件/云平台/业务(上层应用) 三层分离
2. 复杂的业务从原来的大服务拆分成多个小服务；对外呈现支持每个小服务单域自治(支付功能，订单功能，账户管理功能)，支持子服务单独升级
3）CI/CD 自动化工具 大量引用系统配置，性能，告警，内部统计等相关信息对充运行状态进行监测，例如通过服务日志解析得到指标数据。
	* CI全称 Continuous Integration,表示持续集成,CD包含 Continuous Delivery和 Continuous Deployment,分别是持续交付和持续部署。

原来的内部交互接口，一旦对外暴露，变成外部交互接口，就会引发兼容性问题。导致子服务功能失效，或自动化工具大量失败。

国际软件质量评价标准ISO/IEC 25010:2011弥补了ISO/IEC9126质量模型的不足，描述了8个质量特性和31个子特性。

![](/_images/grow/product/软件产品质量.png)

## 软件兼容性

Software Compatibility，由于系列内各档机器从程序设计者看都具有相同的机器属性，因此按这个属性编制的机器语言程序以及编译程序都能不加修改地通用于各档机器，我们称这种情况下地各档机器是软件兼容的，它们的区别仅在于运行所需的时间不同。

软件兼容性是衡量软件好坏的一个重要指标，包括以下属性： 

1. 与软件无需采用有别于为该软件准备的活动或手段就可能适应不同的规定环境有关的软件属性 ；
2. 使软件遵循与可移植性有关的标准或约定的软件属性 ；
3. 与软件在该软件环境中用来替代制定的其他软件的机会和努力有关的软件属性。

兼容性主要包括共存性、互操作性、兼容性的依从性。

* 共存性：在与其他产品共享通用的环境和资源的条件下，产品能够有效执行其所需的功能并且不会对其他产品造成负面影响的程度。
* 互操作性：两个或多个系统、产品或组件能够交换信息并使用已交换的信息的程度。
* 兼容性的依从性：产品或系统遵循与兼容性相关的标准、约定或法规以及类似规定的程度。

## 兼容性原则

以微服务为最小单位，从共存性(纵向)和互操作性(横向)来解析: 

* 纵向：
	* 对底层硬件/驱动/云平台/操作系统的依赖和要求进行显示声明，各个微服务需要列出自身的需求内容，如果声明需要变更，需要给出兼容性处理方案。
	* 微服务对上层应用或用户提供的消息接囗/API函数接口/数据结构，必须兼容，特别是新老版本之间的兼容。
		* 例如，提供的C语言函数接口新增参数，导致的强制对齐；protobuf新增字段必须有默认值去兼容等。
横向：
	* 微服务内部子服务(子系统)间的消息交互接囗/交互时序/方式(同步或异步)/异常处理，需要考虑兼容，各个子系统 新 + 老 组合应该能正常执行。

### 原则细化

![](/_images/grow/product/兼容性细化.png)
