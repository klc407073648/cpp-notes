# STL内容

[[toc]]

## STL基本组成以及概念

STL提供了六大组件，彼此可以组合套用: 

1. 容器（containers）: 各种数据结构，如: vector、list、deque、set、map，主要用来存放数据。
2. 算法 (algorithms): 各种常见算法，如: sort、search、copy、erase......
3. 迭代器 (iterators): 扮演算法和容器中的胶合剂，是“泛型指针”。所有STL容器均有自己专属的迭代器。
4. 仿函数 (functors): 行为类似函数，可作为算法的某种策略。仿函数是一种重载了operator()的class或class template。
5. 配接器（adapters）: 修饰容器、仿函数、迭代器接口的东西。
6. 配置器（allocators）: 负责空间配置和管理，配置器是一个实现了动态空间配置、空间管理、空间释放的class template.

关系: 

* Container通过Allocator取得数据储存空间，Algorithm通过Iterator存取Container内容，Functor可以协助Algorithm完成不同的策略变化，Adapter可以修饰或套接Functor。



