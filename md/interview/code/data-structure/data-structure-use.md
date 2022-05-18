# 知识点

[[toc]]

Adapter的定义，：将一个Class的接口转换成另一个Class的接口，使原本因接口不兼容而不能合作的Class可以一起运作。

STL里面主要有两种接配器（Adapter）：容器接配器（Container Adapter）和迭代器接配器（Iterator Adapter）：

Container Adapter：

　　最常用的容器接配器无非是queue和stack，从意义上来说，他们为底层的容器提供了一层包装，使得底层的容器只表现出这些接配器所定义的数据结构的功能。
这里假设底层容器是deque，双向开口，而且两端插入删除都能够实现O(1)的时间复杂的。当作为queue进行包装的时候deque就会封闭一端的插入操作，封闭另一端的删除操作，使得整个deque表现出FIFO的特性，在作为stack的时候同理。
可以看到Container Adapter做到的功能很直观，也很好理解，只是对于容器的一层包装，改变了数据结构的接口的同时方便了我们对其的理解和使用。

Iterator Adapter（#include<iterator>）：

　　对于STL中iterator的使用最多的也就是begin(),end(),const_iterator,rbegin()等等，而在这里要讲的Iterator Adapter主要有三种：
分别是insert iterator，reverse iterator，iostream iterator。

1. insert iterator：从定义上来讲，它的作用是将一般迭代器的赋值（assign）操作转变为插入（insert）操作。理解了这句话也就理解了insert iterator的本质。
2. reverse iterator：显然作用是使得iterator方向相反，常和rbegin,rend一起使用
3. iostream iterator：这种Adapter将iterator和输入输出流(可以是文件流)相关联，经常和copy函数联合使用

Iterator是一种抽象的设计概念《Design Patterns》其中对于iterator模式定义如下：提供一种方法，使之能够依序巡访某个聚合物（容器）所包含的各个元素，而又无需暴露该聚合物的内部表达方式。

因此，对于根据定义不允许顺序或随机访问的数据结构，迭代器没有任何意义。这就是堆栈和队列没有迭代器的原因。


unordered_map和map
unordered_map存储机制是哈希表，，即unordered_map内部元素是无序的。

map是红黑树，map中的元素是按照二叉搜索树存储，进行中序遍历会得到有序遍历。

unordered_set和set
unordered_set基于哈希表，是无序的。

set实现了红黑树的平衡二叉检索树的数据结构，插入元素时，它会自动调整二叉树的排列，把元素放到适当的位置，以保证每个子树根节点键值大于左子树所有节点的键值，小于右子树所有节点的键值；另外，还得保证根节点左子树的高度与右子树高度相等。


**priority_queue:**

| Member functions | description                     |
| ---------------- | ------------------------------- |
| (constructor)    | Construct priority queue        |
| empty            | Test whether container is empty |
| size             | Return size                     |
| top              | Access top element              |
| push             | Insert element                  |
| emplace          | Construct and insert element    |
| pop              | Remove top element              |
| swap             | Swap contents                   |

**queue:**

| Member functions | description                     |
| ---------------- | ------------------------------- |
| (constructor)    | Construct queue                 |
| empty            | Test whether container is empty |
| size             | Return size                     |
| front            | Access next element             |
| back             | Access last element             |
| push             | Insert element                  |
| emplace          | Construct and insert element    |
| pop              | Remove next element             |
| swap             | Swap contents                   |

The next element is the "oldest" element in the queue and the same element that is popped out from the queue when queue::pop is called.

**stack:**

| Member functions | description                     |
| ---------------- | ------------------------------- |
| (constructor)    | Construct stack                 |
| empty            | Test whether container is empty |
| size             | Return size                     |
| top              | Access next element             |
| push             | Insert element                  |
| emplace          | Construct and insert element    |
| pop              | Remove top element              |
| swap             | Swap contents                   |

**list:**

| Element access: | description          |
| --------------- | -------------------- |
| front           | Access first element |
| back            | Access last element  |

| Modifiers:    | description                               |
| ------------- | ----------------------------------------- |
| assign        | Assign new content to container           |
| emplace_front | Construct and insert element at beginning |
| push_front    | Insert element at beginning               |
| pop_front     | Delete first element                      |
| emplace_back  | Construct and insert element at the end   |
| push_back     | Add element at the end                    |
| pop_back      | Delete last element                       |
| emplace       | Construct and insert element              |
| insert        | Insert elements                           |
| erase         | Erase elements                            |
| swap          | Swap content                              |
| resize        | Change size                               |
| clear         | Clear content                             |

| Operations: | description                          |
| ----------- | ------------------------------------ |
| splice      | Transfer elements from list to list  |
| remove      | Remove elements with specific value  |
| remove_if   | Remove elements fulfilling condition |
| unique      | Remove duplicate values              |
| merge       | Merge sorted lists                   |
| sort        | Sort elements in container           |
| reverse     | Reverse the order of elements        |

Set

| Member functions | description            |
| ---------------- | ---------------------- |
| (constructor)    | Construct set          |
| (destructor)     | Set destructor         |
| operator=        | Copy container content |

| Iterators  | description                                        |
| ---------- | -------------------------------------------------- |
| begin      | Return iterator to beginning                       |
| end        | Return iterator to end                             |
| rbegin     | Return reverse iterator to reverse beginning       |
| rend       | Return reverse iterator to reverse end             |
| cbegin     | Return const_iterator to beginning                 |
| cend       | Return const_iterator to end                       |
| crbegin    | Return const_reverse_iterator to reverse beginning |
| crend      | Return const_reverse_iterator to reverse end       |

| Capacity  | description                     |
| --------- | ------------------------------- |
| empty     | Test whether container is empty |
| size      | Return container size           |
| max_size  | Return maximum size             |

| Modifiers    | description                            |
| ------------ | -------------------------------------- |
| insert       | Insert element                         |
| erase        | Erase elements                         |
| swap         | Swap content                           |
| clear        | Clear content                          |
| emplace      | Construct and insert element           |
| emplace_hint | Construct and insert element with hint |

| Observers  | description              |
| ---------- | ------------------------ |
| key_comp   | Return comparison object |
| value_comp | Return comparison object |

| Operations  | description                          |
| ----------- | ------------------------------------ |
| find        | Get iterator to element              |
| count       | Count elements with a specific value |
| lower_bound | Return iterator to lower bound       |
| upper_bound | Return iterator to upper bound       |
| equal_range | Get range of equal elements          |

Allocator:
get_allocator
Get allocator 