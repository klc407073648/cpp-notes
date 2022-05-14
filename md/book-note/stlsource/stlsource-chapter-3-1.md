# 第三章：迭代器（iterators）概念与traits编程技法（一）

[[toc]]

# 迭代器概述

Iterator是一种抽象的设计概念《Design Patterns》其中对于iterator模式定义如下：提供一种方法，使之能够依序巡访某个聚合物（容器）所包含的各个元素，而又无需暴露该聚合物的内部表达方式。

STL的中心思想在于：将数据容器（containers）和算法（algorithms）分开彼此独立设计，最后再以一贴粘合剂将其撮合。**这个粘合剂就是Iterator**。迭代器是一种类似指针的对象，最重要的便是对operator *和operator->进行重载，为了让迭代器适用于任何型态的结点，需要把它设计为class template。以算法的find函数为例，它接受两个迭代器和一个“查找目标”：

```cpp
template <class InputIter, class T>
inline InputIter find(InputIter first, InputIter last,
                       const T& val)
{
  while (first != last && !(*first == val))
    ++first;
  return first;
}
```

只要给予不同的迭代器，find()函数便能对不同的容器进行查找操作：

```cpp
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;

// 迭代器是一种行为类似指针的对象，对operator*和operator->进行重载

int main() {
    const int arraySize = 7;
    int ia[arraySize] = {0, 1, 2, 3, 4, 5, 6};

    vector<int> ivect(ia, ia + arraySize);
    list<int> ilist(ia, ia + arraySize);
    deque<int> ideque(ia, ia + arraySize);

    vector<int>::iterator it1 = find(ivect.begin(), ivect.end(), 4);
    if (it1==ivect.end())
        cout << "4 not found." << endl;
    else
        cout << "4 found. " << *it1 << endl;

    list<int>::iterator it2 = find(ilist.begin(), ilist.end(), 6);
    if (it2==ilist.end())
        cout << "6 not found." << endl;
    else
        cout << "6 found. " << *it2 << endl;

    deque<int>::iterator it3 = find(ideque.begin(), ideque.end(), 8);
    if (it3==ideque.end())
        cout << "8 not found." << endl;
    else
        cout << "8 found. " << *it3 << endl;
	
	return 0;
}
```

执行结果：
```bash
[root@192 3_STL_iterator]# ./3_1_find
4 found. 4
6 found. 6
8 not found.
```

在算法中运用迭代器，很可能会用到其相应型别，而C++之支持sizeof( )，并未支持typeof( )，即便动用RTTI性质中的typeid( )，获得的也只是型别的别名，不能用来当变量声明用。

解救的办法有几个：

## 利用function template的参数推导机制

```cpp
 template <class I, class T>
  void func_impl(I iter, T t) {
          T tmp; // 这里就是迭代器所指物的类型新建的对象
          // ... 功能实现
  }
  ​
  template <class I>
  inline
  void func(I iter) {
          func_impl(iter, *iter); // 传入iter和iter所指的值，class自动推导
  }
  ​
  int main() {
      int i;
      func(&i);
  }

```

我们以func()对外接口，却把实际操作全部置于func_imp1()之中。由于func_imp1()是一个function template，一旦被调用，编译器会自动进行template参数推导。于是导出型别T，顺利解决问题。但是，template参数推导机制推导的只是参数，无法推导返回值型别，所以如果迭代器所指对象的型别必须用于函数的传回值时，只能采用声明内嵌型别的方法。

## 声明内嵌型法

```cpp
 template <class T>
  struct MyIter {
      typedef T value_type; // 内嵌型别声明
      // ...
  };
  ​
  template <class I>
  typename I::value_type //这一行是func的回返值型别，typename告诉编译器I::value_type是一个型别
  func(I ite) {
      return *ite;
  }
  ​
  // ...
  MyIter<int> ite(new int(8));
  cout << func(ite);
```

看起来似乎解决了问题，但是忽略了一个问题，并不是所有迭代器都是class type，原生指针就不是。如果不是class type，就无法定义它内嵌型别。但STL绝对必须接受原生指针作为一种迭代器。进一步引入（template partial specialization）模板偏特化的概念。

## 模板偏特化

Partial Specialization (偏特化)意义：如果class template拥有一个以上的template参数，我们可以针对其中某个（或数个，但非全部）template参数进行特化工作。换句话说，我们可以在泛化设计中提供一个特化版本（也就是将泛化版本中的某些template参数赋予明确的指定）。

《泛型思维》对Partial Specialization 定义：针对（任何）template参数更进一步的条件限制所设计出来的一个特化版本。由此，面对以下这么一个class template：

```cpp
template<typename T>
class C {……};  //这个泛化版本允许（接受）T为任何型别
  ​
//我们更容易接受它有一个形如下的Partial Specialization 
template<typename T>
class C<T*> {……};  //这个泛化版本仅适用于"T为原生指针"的情况，便是"T为任何型别"的一个更进一步的条件限制
template <class I>
struct iterator_traits {
      typedef typename I::value_type value_type;
};
  ​
template <class I>
struct iterator_traits<T*> {
      typedef T value_type;
};
  ​
template <class I> typename iterator_traits<I>::value_type
func(I ite) {
      return *ite;
}
```

func在调用 I 的时候，首先把 I 传到萃取器中，然后萃取器就匹配最适合的 value_type。（萃取器会先匹配最特别的版本）这样当你传进一个原生指针的时候，首先匹配的是带<T*>的偏特化版本，这样 value_type 就是 T，而不是没有事先声明的 I::value_type。这样返回值就可以使用 typename iterator_traits<I>::value_type 来知道返回类型。如下是STL源码剖析里的traits所扮演的特性萃取机图。

![traits特性萃取机](/_images/book-note/stlsource/traits特性萃取机.png)

如图说明了traits所扮演的“特性萃取机”角色，萃取各个迭代器的特性，这里所谓的迭代器特性，指的是迭代器的相应型别。最常见的迭代器型别有5种value_type、difference_type、pointer、reference、iterator_category，因此traits中会有这5个类型。

```cpp
template <class I>
struct iterator_traits {
  typedef typename I::iterator_category iterator_category;
  typedef typename I::value_type        value_type;
  typedef typename I::difference_type   difference_type;
  typedef typename I::pointer           pointer;
  typedef typename I::reference         reference;
};
```

iterator_traits 必须针对传入之型别为pointer及pointer-to-const者，设计特化版本。

​