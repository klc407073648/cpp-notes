# 第一章：STL概论和版本简介

[[toc]]

# STL概述
软件界一直期望建立一种可重复运用的方法，使得工程师、程序员不必困于重复编写前人已经编写过的源码，STL应运而生。它建立了数据结构和算法的一套标准，且各组件之间低耦合、独立性高。STL所实现的，是依据泛型思维架设起来的一个概念结构，这个以抽象概念为主题而非以实际类为主体的结构，形成了一个严谨的接口标准，在此接口下，任何组件都有最大的独立性，并以所谓迭代器胶合起来，或以所谓适配器互相配接，或以所谓仿函数动态选择某种策略。

STL提供了六大组件，彼此可以组合套用：

1. 容器（containers）：各种数据结构，如：vector、list、deque、set、map，主要用来存放数据。
2. 算法 (algorithms)：各种常见算法，如：sort、search、copy、erase......
3. 迭代器 (iterators)：扮演算法和容器中的胶合剂，是“泛型指针”。所有STL容器均有自己专属的迭代器。
4. 仿函数 (functors)：行为类似函数，可作为算法的某种策略。仿函数是一种重载了operator()的class或class template。
5. 配接器（adapters）: 修饰容器、仿函数、迭代器接口的东西。
6. 配置器（allocators）：负责空间配置和管理，配置器是一个实现了动态空间配置、空间管理、空间释放的class template.

# STL六大组件的交互关系

![STL六大组件](/_images/book-note/stlsource/STL六大组件.png)

Container通过Allocator取得数据储存空间，Algorithm通过Iterator存取Container内容，Functor可以协助Algorithm完成不同的策略变化，Adapter可以修饰或套接Functor。

# stl_config.h中的各种组态

## 组态: __STL_STATIC_TEMPLATE_MEMBER_BUG

```cpp
// file: 1config3.cpp 
// 测试在 class template中 拥有 static data members. 
// test __STL_STATIC_TEMPLATE_MEMBER_BUG, defined in <stl_config.h> 
// ref. C++ Primer 3/e, p.839 
// vc6[o] cb4[x] gcc[o] 
// cb4 does not support static data member initialization.

// 如果编译器无法处理static member of template classes(模板类静态成员)就定义。
// 即对于模板类中，模板类型不同时的静态变量不同。

#include <iostream>
using namespace std;

template <typename T>
class TestClass {
public:
    static int _data;
};

// 需要加上template<>，否则编译出错，进行内存配置
template<> int TestClass<int>::_data = 1;
template<> int TestClass<char>::_data = 1;

int main() {

    cout << TestClass<int>::_data << endl;
    cout << TestClass<char>::_data << endl;
    
    TestClass<int> obji1, obji2;
    TestClass<char> objc1, objc2;
    cout << obji1._data << " " << obji2._data << endl;
    cout << objc1._data << " " << objc2._data << endl;

    obji1._data = 3;
    objc2._data = 4;

    cout << obji1._data << " " << obji2._data << endl;
    cout << objc1._data << " " << objc2._data << endl;
}
```

## 组态：__STL_CLASS_PARTIAL_SPECIALIZATION

```cpp
// file: 1config5.cpp 
// 测试 class template partial specialization 
// — 在 class template的一般化设计之外，特别针对某些 template参数做特殊设计。
// test __STL_CLASS_PARTIAL_SPECIALIZATION in <stl_config.h> 
// ref. C++ Primer 3/e, p.860 
// vc6[x] cb4[o] gcc[o]

// 如果编译器支持 partial specialization of class templates(模板类偏特化)就定义。
// 在模板类一般化设计之外（全特化），针对某些template做特殊设计。
// “所谓的partial specialization的另一个意思是提供另一份template定义式,而其本身仍是templatized”
// 全特化就是所有的模板都为具体的类。
// T* 特化允许用指针类型匹配的模式（也只能匹配指针类型）。
// const T* 特化允许使用指向const的指针 类型匹配（也只能匹配指向const的指针）。

#include <iostream>
using namespace std;

// 一般化设计
template <class I, class O>
struct TestClass {
    TestClass() {
        cout << "I, O" << endl;
    }
};

// 特殊化设计
template <class T>
struct TestClass<T*, T*> {
    TestClass() {
        cout << "T*, T*" << endl;
    }
};

// 特殊化设计
template <class T>
struct TestClass<const T*, T*> {
    TestClass() {
        cout << "const T*, T*" << endl;
    }
};

int main() {
    TestClass<int, char> obj1;
    TestClass<int *, int *> obj2;
    TestClass<const int *, int *> obj3;
}
```

## 组态：__STL_MEMBER_TEMPLATES

```cpp
// file: 1config8.cpp 
// 测试 class template之内可否再有 template (members). 
// test __STL_MEMBER_TEMPLATES in <stl_config.h> 
// ref. C++ Primer 3/e, p.844 
// vc6[o] cb4[o] gcc[o] 

// 如果编译器支持template members of classes（模板类内嵌套模板） 就定义。

#include <iostream>
using namespace std;

class alloc {
};

template <class T, class Alloc=alloc>
class vec {
public:
    typedef T value_type;
    typedef value_type* iterator; // 迭代器为指针
    // typedef T *iterator; // 直接定义也可

    template <class I> // 模板嵌套模板
    void insert(iterator position, I first, I last) {
        cout << "insert()" << endl;
    }
};

int main() {
    int ia[5] = {0, 1, 2, 3, 4};

    vec<int> x;
    vec<int>::iterator ite;
    x.insert(ite, ia, ia + 5);
}
```

## 组态：__STL_LIMITED_DEFAULT_TEMPLATES 

```cpp
// file: 1config10.cpp 
// 测试 template参数可否根据前㆒个 template参数而设定默认值。
// test __STL_LIMITED_DEFAULT_TEMPLATES in <stl_config.h> 
// ref. C++ Primer 3/e, p.816 
// vc6[o] cb4[o] gcc[o]

// 如果编译器支持一个template参数可以根据前一个template的参数设置就定义。

#include <iostream>
#include <cstddef> // for size_t
using namespace std;

class alloc {
};

template <class T, class Alloc=alloc, size_t BufSiz=0>
class deque {
public:
    deque() {
        cout << "deque()" << endl;
    }
};

template <class T, class Sequence = deque<T>>
class stack {
public:
    stack() {
        cout << "stack" << endl;
    }
private:
    Sequence c;
};

int main() {
    stack<int> x;
}
```