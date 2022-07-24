# 结构型 - 组合(Composite)

> 组合模式(composite pattern): 允许你将对象组合成树形结构来表现"整体/部分"层次结构. 组合能让客户以一致的方式处理个别对象以及对象组合

​[[toc]]

# 概念

Composite 模式典型的结构图为：

![](/_images/programming/designpattern/structure/Composite.png)

组件(Component)类是组合类(Composite)和叶子类(Leaf)的父类，可以把组合类看成是树的中间节点。 组合对象拥有一个或者多个组件对象，因此组合对象的操作可以委托给组件对象去处理，而组件对象可以是另一个组合对象或者叶子对象。

# 代码实现

<<< @/md/programming/designpattern/structure/Composite/Component.h

<<< @/md/programming/designpattern/structure/Composite/Component.cpp

<<< @/md/programming/designpattern/structure/Composite/Composite.h

<<< @/md/programming/designpattern/structure/Composite/Composite.cpp

<<< @/md/programming/designpattern/structure/Composite/Leaf.h

<<< @/md/programming/designpattern/structure/Composite/Leaf.cpp

<<< @/md/programming/designpattern/structure/Composite/main.cpp

```bash
[root@VM-16-6-centos Composite]# ./ComponentTest
Leaf operation.....
Leaf operation.....
Leaf operation.....
```

## 代码说明

Composite 模式在实现中有一个问题就是要提供对于子节点（ Leaf）的管理策略，这里使用的是 STL 中的 vector，可以提供其他的实现方式，如数组、链表、 Hash 表等。

## 讨论

Composite 模式通过和 Decorator 模式有着类似的结构图， 但是 Composite 模式旨在构造类，而 Decorator 模式重在不生成子类即可给对象添加职责。 Decorator 模式重在修饰， 而Composite 模式重在表示。