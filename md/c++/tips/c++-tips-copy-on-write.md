# C++ Tips - 写时拷贝技术(copy-on-write)

> 本文包含写时拷贝技术的内容。

[[toc]]

抛砖引玉：

* 《More Effective C++》中讲过一个例子：在你还在上学的时候，你的父母要你不要看电视，而去复习功课，于是你把自己关在房间里，做出一副正在复习功课的样子，其实你在干着别的诸如给班上的某位女生写情书之类的事，而一旦你的父母出来在你房间要检查你是否在复习时，你才真正捡起课本看书。**这就是“拖延战术”**，直到你非要做的时候才去做。

这种现实生活中的小套路，转变到编程世界里就成为了最有用的技术。正如C++中的可以随处声明变量的特点一样，Scott Meyers推荐我们，**在真正需要一个存储空间时才去声明变量（分配内存），这样会得到程序在运行时最小的内存花销。**执行到那才会去做分配内存这种比较耗时的工作，这会给我们的程序在运行时有比较好的性能。毕竟20%的程序运行了80%的时间(二八定律)。

拖延战术：

* 在真正需要一个存储空间时才去声明变量（分配内存），这样会得到程序在运行时最小的内存花销。

* 当一个程序运行结束时，操作系统并不会急着把其清除出内存，原因是有可能程序还会马上再运行一次（从磁盘把程序装入到内存是个很慢的过程），而只有当内存不够用了，才会把这些还驻留内存的程序清出。
* 写时才拷贝（*Copy-On-Write*）技术

<font color='red'>**二八定律**</font>

```
二八定律是19世纪末20世纪初意大利经济学家巴莱多发现的。他认为，在任何一组东西中，最重要的只占其中一小部分，约20%，其余80%尽管是多数，却是次要的，因此又称二八定律。
```

# 写时拷贝技术概念

程序需要根据网络持续传递的数据进行写操作，如果每一次写操作都通过fwrite或fprintf函数来进行一个磁盘的I/O读取的话，性能损失巨大。因此，一般的做法是每次写文件操作都写在一块特定大小的内存中（磁盘缓存），只有当接收完一段数据需要关闭文件时，才写到磁盘上。虽然上述方法能够提高性能，但同样会带来诸如非正常退出，数据丢失或文件损坏的风险。


# 标准C++类std::string的Copy-On-Write


STL标准模板库中的string类，就是一个具有写时才拷贝技术的类。C++曾在性能问题上被广泛地质疑和指责过，为了提高性能，STL中的许多类都采用了Copy-On-Write技术。这种偷懒的行为的确使使用STL的程序有着比较高要性能。

**string类内存分配的概念**

```
通常string类中必有一个私有成员，其是一个char*，用户记录从堆上分配内存的地址，其在构造时分配内存，在析构时释放内存。
因为是从堆上分配内存，所以string类在维护这块内存上是格外小心的，string类在返回这块内存地址时，只返回const char*，也就是只读的，如果需要写，只能通过string提供的方法进行数据的改写。
```

**测试程序**

```cpp
#include<iostream>
#include<stdio.h>
#include<string>

using namespace std;
main()
{
    string str1 = "hello world";
    string str2 = str1;
    
    cout<<"Sharing the memory:"<<endl;
    cout<<"str1's address: "<<(void *)(str1.c_str())<<endl;
    cout<<"str2's address: "<<(void *)(str2.c_str())<<endl;
    
    str1[1]='q';
    str2[1]='w';
 
    cout<<"After Copy-On-Write:"<<endl;
    cout<<"str1's address: "<<(void *)(str1.c_str())<<endl;
    cout<<"str2's address: "<<(void *)(str2.c_str())<<endl;
 
    return 0;
}
```

执行结果：

```cpp
[root@iZuf61kbf845xt6tz10abgZ code]# g++ -o stringTest stringTest.cpp

理论上：
[root@iZuf61kbf845xt6tz10abgZ code]# ./stringTest
Sharing the memory:
str1's address: 0x7fff54c24b70
str2's address: 0x7fff54c24b70
After Copy-On-Write:
str1's address: 0x7fff54c24b70
str2's address: 0x7fff54c24b50
    

实际上：
[root@iZuf61kbf845xt6tz10abgZ code]# ./stringTest
Sharing the memory:
str1's address: 0x7fff54c24b70
str2's address: 0x7fff54c24b50
After Copy-On-Write:
str1's address: 0x7fff54c24b70
str2's address: 0x7fff54c24b50
    
```

<font color='red'>**即不同的gcc或vs编译器对共享内存有不同的处理策略。有的环境可能直接是深拷贝，有的环境是共享内容。（扩展不同编译器的优化策略也不尽相同）**</font>

