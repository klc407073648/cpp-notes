# UML类图

> UML类图。

# 参考文献

*[14种UML图](https://blog.csdn.net/weixin_39593460/article/details/111118988)

# 概述

UML是Unified Model Language的缩写，中文是统一建模语言，是由一整套图表组成的标准化建模语言。

# 类图

## 符号

在UML类图中，常见的有以下几种关系：泛化（Generalization），实现（Realization），关联（Association），聚合（Aggregation），组合（Composition），依赖（Dependency）

![](/_images/programming/designpattern/UML箭头含义.png)

## 泛化(Generalization)

* 【泛化关系】是一种继承关系，表示子类继承父类的所有特征和行为。
* 【箭头指向】带三角箭头的实线，箭头指向父类。

![](/_images/programming/designpattern/泛化.png)

## 实现(Realization)

* 【实现关系】是一种类与接口的关系，表示类是接口所有特征和行为的实现。
* 【箭头指向】带三角箭头的虚线，箭头指向接口。

![](/_images/programming/designpattern/实现.png)

## 关联(Association)

* 【关联关系】是一种拥有关系，它使得一个类知道另一个类的属性和方法。
* 【代码体现】成员变量
* 【箭头指向】带普通箭头的实线，指向被拥有者。双向的关联可以有两个箭头，或者没有箭头。单向的关联有一个箭头。

![](/_images/programming/designpattern/关联.png)

> 自己买的车，想什么时候开就开。但是车是车，人是人，没有整体与部分的关系。

## 聚合(Aggregation)

* 【聚合关系】是一种整体与部分的关系。且部分可以离开整体而单独存在。聚合关系是关联关系的一种，是强的关联关系；关联和聚合在语法上无法区分，必须考察具体的逻辑关系。
* 【代码体现】成员变量
* 【箭头指向】带空心菱形的实线，空心菱形指向整体。

![](/_images/programming/designpattern/聚合.png)

> 电脑有键盘才能输入信息，电脑是整体，键盘是部分，键盘也可以离开电脑，单纯的拿去敲。所以是聚合。

## 组合(Composition)

* 【组合关系】是一种整体与部分的关系。但部分不能离开整体而单独存在，组合关系是关联关系的一种，是比聚合关系还要强的关系。
* 【代码体现】成员变量
* 【箭头指向】带实心菱形的实线，实心菱形指向整体。

![](/_images/programming/designpattern/组合.png)

> 鸟是整体，翅膀是部分。鸟死了，翅膀也就不能飞了。所以是组合。

我们再看一下，下面的一组经典的聚合组合关系的例子。

![](/_images/programming/designpattern/聚合组合.png)

> 一个公司拥有多个部门，公司和部门之间是组合关系，公司破产了，部门就不复存在了。部门和员工是聚合关系，部门被裁掉，员工就换下了。

## 依赖(Dependency)

* 【依赖关系】是一种使用关系，即一个类的实现需要另一个类的协助。
* 【箭头指向】带普通箭头的虚线，普通箭头指向被使用者。

![](/_images/programming/designpattern/依赖.png)

老司机只管开车，车是谁的不重要，给什么车开什么车。