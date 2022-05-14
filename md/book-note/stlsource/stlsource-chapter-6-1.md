# 第六章：算法

[[toc]]

# 算法概观

算法，问题之解法也。以有限的步骤，解决逻辑或数学上的问题，这一专门科目称为算法。STL 正是将极具复用价值的算法进行封装，包含sort,find,copy等函数。

## STL算法总览

**所有的STL算法都作用在迭代器 [first,last) 所标出来的区间上**。根据是否改变操作对象的值，可以分为 **质变算法（mutating algorithms）和 非质变算法 （nomutating algorithms）**。

质变算法，是指运算过程中会更改区间内元素的内容的算法。

* 拷贝（copy），互换（swap），替换（replace），填写（fill），删除（remove），排列组合（permutation），分割（partition），随机重排（random shuffling），排序（sort）等。

非质变算法，是指运算过程中不会更改区间内元素的内容的算法。

* 查找（find），匹配（search），计数（count），巡访（for_each），比较（equal,mismatch），寻找极值（max,min）等。但是在for_each算法上应用一个会改变元素内容的仿函数，所在元素必然会改变：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template <class T>
struct myplus{
   void operator()(T& x) const
	{x =x+5;}
};

template <class T>
struct display{
   void operator()(T& x) const
        {cout<<x<<" ";}
};


int main()
{
	int ia[] = {1,2,3,4,5};
	vector<int> iv(ia,ia+sizeof(ia)/sizeof(int));
	for_each(iv.begin(),iv.end(),myplus<int>());
	for_each(iv.begin(),iv.end(),display<int>()); //6 7 8 9 10 

	return 0;
}
```

## 算法的泛化过程

如何将算法独立于其所处理的数据结构之外，不受数据结构的约束？关键在于，要把操作对象的型别加以抽象化，把操作对象的标示法和区间目标的移动行为抽象化，整个算法也就在一个抽象层面上工作了。整个过程称为算法的泛型化（generalized），简称泛化。

以简单的循序查找为例，编写find()函数，在array中寻找特定值。面对整数array，写出如下程序：

```cpp
int* find(int* arrayHead, int arraySize, int value)
{
    int i=0;
    for (; i<arraySize; ++i)
    {
        if (arrayHead[i] == value)
        {
            break;
        }
    }

    return &(arrayHead[i]);
}
```

上述find()函数写法暴露了太多的实现细节（例如arraySize），为了让find()适用于所有类型的容器，其操作应该更抽象化些。让find()接受两个指针作为参数，标示一个操作区间：

```cpp
int* find(int* begin, int*end, int value)
{
    while(begin !=end && *begin != value)
        ++begin;

    return begin;
}
```

由于find()函数之内并无任何操作是针对特定整数array而发的，所以我们可以把它改成一个template：

```cpp
template<typename T>
T* find(T* begin, T* end, const T& value)
{
    // 注意，以下用到了operator!=, operator*, operator++
    while (begin != end && *begin != value)
        ++begin;

    // 注意，以下返回操作用会引发copy行为
    return begin;
}
```

在上述代码中，传入的指针必须支持以下四种操作行为：

* inequality 判断不相等
* dereferencelm 提领
* prefix increment 前置式递增
* copy 复制

　　上述操作符可以被重载（overload），find()函数就可以从原生（native）指针的思想框框中跳脱出来。我们可以设计一个class，拥有原生指针的行为，这就是迭代器（iterator）：

```cpp
template<typename Iterator, typename T>
Iterator find(Iterator begin, Iterator end, const T& value)
{
    while(begin != end && *begin != value)
        ++begin;

    return begin;
}
```

至此，便是完全泛型化的find()函数。

# 数值算法

C++ STL 的数值算法(Numeric algorithms)是一组对容器元素进行数值计算的模板函数，包括容器元素求和 accumulate 、两序列元素的内积 inner_product 、容器元素的一系列部分元素和 partial_sum 、容器每对相邻元素的差adjacent_difference。其头文件为<numeric>，测试实例如下：

```cpp
// file: 6numeric.cpp

#include <numeric>
#include <vector>
#include <functional> // minus<int>()
#include <iostream>   // ostream_iterator
#include <iterator>

using namespace std;

int main() {
    int ia[5] = {1, 2, 3, 4, 5};
    vector<int> iv(ia, ia + 5);
    // 0+1+2+3...
    cout << accumulate(iv.begin(), iv.end(), 0) << endl; 
    //0是初值，T accumulate(InputIterator first, InputIterator last, T init)
    
    // 0-1-2-3
    cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;

    // 10 + 1*1 + 2*2 + ...
    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;

    // 10 - 1+1 - 2+2 - ...
    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10,
        minus<int>(), plus<int>()) << endl;

    // 将迭代器绑定到cout，作为输出用
    ostream_iterator<int> oite(cout, " ");

    // 1 3 6 10 15 累计和
    partial_sum(iv.begin(), iv.end(), oite);
    cout << endl;

    // 1 -1 -4 -8 -13 累计差
    partial_sum(iv.begin(), iv.end(), oite, minus<int>());
    cout << endl;

    // 1 1 1 1 1     new #n = #n - #n-1
    adjacent_difference(iv.begin(), iv.end(), oite);
    cout << endl;

    // 1 3 5 7 9      new #n = op(#n, #n-1)
    adjacent_difference(iv.begin(), iv.end(), oite, plus<int>());
    cout << endl;

    // mingw c++ 中stl没有power实现
    // cout << power(10, 3) << endl;
    // cout << power(10, 3, plus<int>()) << endl;

    int n = 3;
    iota(iv.begin(), iv.end(), n); // 填入n, n+1, n+2
    for (int i = 0; i < iv.size(); ++i)
        cout << iv[i] << ' ';
	
	return 0;
}
```

运行结果：

```bash
[root@192 6_STL_algorithms]# ./6_3_1_numeric
15
-15
65
-20
1 3 6 10 15
1 -1 -4 -8 -13
1 1 1 1 1
1 3 5 7 9
3 4 5 6 7 [
```

# 基本算法

equal作用：判断[first,last)区间两个元素是否相同，第二个迭代器多出来的元素不予考虑。

```cpp
template <class _InputIter1, class _InputIter2>//版本1
inline bool equal(_InputIter1 __first1, _InputIter1 __last1,
                  _InputIter2 __first2) {
  for ( ; __first1 != __last1; ++__first1, ++__first2)//遍历区间[first，last)元素
    if (*__first1 != *__first2)//只有有一个不相等返回false
      return false;
  return true;
}
 
template <class _InputIter1, class _InputIter2, class _BinaryPredicate>//版本2
inline bool equal(_InputIter1 __first1, _InputIter1 __last1,
                  _InputIter2 __first2, _BinaryPredicate __binary_pred) {
  for ( ; __first1 != __last1; ++__first1, ++__first2)
    if (!__binary_pred(*__first1, *__first2))//两个元素执行二元操作符
      return false;
  return true;
}
```

fill作用：将指定区间元素改为新值。

```cpp
template <class _ForwardIter, class _Tp>
void fill(_ForwardIter __first, _ForwardIter __last, const _Tp& __value) {
  for ( ; __first != __last; ++__first)//遍历整个区间
    *__first = __value;//指定新值
}
```

fill_n作用：将指定区间前n个元素改为新值。

```cpp
template <class _OutputIter, class _Size, class _Tp>
_OutputIter fill_n(_OutputIter __first, _Size __n, const _Tp& __value) {
  for ( ; __n > 0; --__n, ++__first)
    *__first = __value;
  return __first;
}
```

iter_swap作用：将两个迭代器所指对象调换。

```cpp
template <class _ForwardIter1, class _ForwardIter2, class _Tp>
inline void __iter_swap(_ForwardIter1 __a, _ForwardIter2 __b, _Tp*) {
  _Tp __tmp = *__a;
  *__a = *__b;
  *__b = __tmp;
}
 
template <class _ForwardIter1, class _ForwardIter2>
inline void iter_swap(_ForwardIter1 __a, _ForwardIter2 __b) {
  __iter_swap(__a, __b, __VALUE_TYPE(__a));
}
```

lexicographical_compare作用：以字典排序方式对两个序列进行比较，第一个元素小于第二个元素返回true。

mismatch作用：用来比较两个序列，指出两者之间第一个不匹配点。

copy函数: 由于copy进行的是复制操作，而复制操作不外乎用assignment operator或copy constructor(copy算法用的是前者)，但是某些元素型别拥有的是trivial assginment operator，因此，如果能够使用内存直接复制行为(例如C标准函数memmove或memcpy)，便能够节省大量时间。为此，SGI STL的copy算法用尽各种办法，包括函数重载、型别特性、偏特化等编程技巧，无所不用其极地加强效率。如下图所示：

![copy](/_images/book-note/stlsource/copy.png)

注意：

1. copy只是将输出区间内的元素赋予新值，不会产生新的元素，所以copy不能直接用来将元素插入空容器中.

2. copy的输出区间的起点如果位于输入区间内，可能会使copy算法出错。

​