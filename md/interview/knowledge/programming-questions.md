# 面试相关学习

> 用于记录面试相关问题，采用md格式记录。

[[toc]]

strcpy函数实现
atoi函数实现
c++ shared_ptr

c++虚函数原理

智能指针

c语言如何实现c++对象以及私有成员

c++多态实现

new和malloc的区别以及底层实现原理

STL中的vector怎么扩容

* 场景：1.当元素添加时导致的扩容；2.使用reserve函数导致的扩容

* 扩容比例：为什么是成倍扩容，而不是等差扩容

  * 如果扩容是个常量（M），即下次扩容的容量为上次的M+K，若共有N个元素需要添加进vector(push_back)
     则共需要N/M次扩容，若第一次容量为1，下一次1+M时需要复制1次，再下一次1+2*M,1+KM(K>=N)
     则添加N个元素需要时间复杂度：

     ![常数扩容](/_images/interview/常数扩容.png)

    平均时间复杂度为O(N)

  * 如果扩容量是倍数（M），级下次扩容的容量为上次的MK，同理，共需要<img src="/_images/interview/logmn.png" alt="logmn" style="zoom:50%;" />次，若第一次容量为1，下一次扩容为M时需要复制1次，再下一次M次···，MK(>=N)
    则添加N个元素需要时间复杂度：

     ![成倍扩容](/_images/interview/成倍扩容.png)

    平均时间复杂度为O(1)

  * 扩容比例：vs为1.5，gcc为2

    * 由于两倍扩容，因此每次都是正好比上一次分配的空间大，因此之前分配的空间无法再复用
      而若是1.5倍，同样的例子，可知，经历了几次扩容，之前的空间可以复用

虚函数指针的初始化过程

c++11原子变量介绍

c++11特性有哪些，说用过的

怎么理解重载与重写

怎么理解c++中的static关键字

vector和list 的区别

c++的内存分配

map与set的底层实现

类静态变量的初始化

析构函数可以是虚函数？为什么

