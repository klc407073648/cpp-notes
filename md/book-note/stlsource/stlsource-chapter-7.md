# 第七章：仿函数

[[toc]]

# 仿函数概述

仿函数也叫作函数对象，是一种具有函数特质的对象，调用者可以像函数一样地调用这些对象，被调用者则以对象所定义的function call operator扮演函数的实质角色。就实现观点而言，**仿函数其实上就是一个“行为类似函数”的对象**。为了“行为类似函数”，其类别定义中必须自定义function call 运算子（operator（））。STL中仿函数代替函数指针的原因在于函数指针不能满足STL对抽象性的要求，也不能满足软件积木的要求，函数指针无法与STL其他组件搭配。

STL仿函数与STL算法之间的关系：

![STL仿函数与STL算法关系](/_images/book-note/stlsource/STL仿函数与STL算法关系.png)

STL仿函数的分类，若以操作数的个数划分，可以分为一元和二元仿函数；若以功能划分，可以分为算术运算（Arithmetic）、关系运算（Rational）、逻辑运算（Logical）三大类。其头文件为<functional> 。

STL仿函数应该有能力被函数适配器修饰，就像积木一样串接，然而，为了拥有配接能力，每个仿函数都必须定义自己的associative types（**主要用来表示函数参数类型和返回值类型**），就想迭代器如果要融入整个STL大家庭，也必须按照规定定义自己的5个相应的类型一样，**这些assocaiative type是为了让配接器可以取得仿函数的某些信息**，当然，这些associative type都只是一些typedef，所有必要操作在编译器就全部完成了，对程序的执行效率没有任何影响，不会带来额外的负担。

为了方便起见<stl_functional.h>定义了两个类classes，分别代表一元仿函数和二元仿函数。

unary_function用来呈现一元函数的参数型别和返回值型别。

```cpp
//STL规定，每一个Adaptable Unary Function都应继承此类别
template <class Arg, class Result>
struct unary_function {
	typedef Arg argument_type;
	typedef Result result_type;
};
```

binary_function用来呈现二元函数的第一参数型别、第二参数型别及返回值型别。

```cpp
//STL规定，每一个Adaptable Binary Function都应继承此类别
template <class Arg1, class Arg2, class Result>
struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};
```

# 算术类仿函数

STL内建算术类仿函数：加法：plus<T>，减法：minus<T>，乘法：multiplies<T>，除法：divides<T>，取模：modulus<T>，取反：negate<T>。

```cpp
template <class T>
struct plus : public binary_function<T,T,T> {
  T operator()(const T& x, const T& y) const { return x + y; }
};

template <class T>
struct minus : public binary_function<T,T,T> {
  T operator()(const T& x, const T& y) const { return x - y; }
};

template <class T>
struct multiplies : public binary_function<T,T,T> {
  T operator()(const T& x, const T& y) const { return x * y; }
};

template <class T>
struct divides : public binary_function<T,T,T> {
  T operator()(const T& x, const T& y) const { return x / y; }
};

template <class T>
struct modulus : public binary_function<T,T,T> 
{
  T operator()(const T& x, const T& y) const { return x % y; }
};

template <class T>
struct negate : public unary_function<T,T> 
{
  T operator()(const T& x) const { return -x; }
};
```

测试程序：

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() {
    // 产生仿函数实体
    plus<int> plusobj;
    minus<int> minusobj;
    multiplies<int> multipliesobj;
    divides<int> dividesobj;
    modulus<int> modulusobj;
    negate<int> negateobj;

    // 使用对象完成函数功能
    cout << plusobj(3, 5) << endl; 		 //8
    cout << minusobj(3, 5) << endl;		 //-2
    cout << multipliesobj(3, 5) << endl; //15
    cout << dividesobj(3, 5) << endl;    //0
    cout << modulusobj(3, 5) << endl;    //3
    cout << negateobj(3) << endl;		 //-3

    // 直接使用仿函数的临时对象完成函数功能
    cout << plus<int>()(3, 5) << endl;
    cout << minus<int>()(3, 5) << endl;
    cout << multiplies<int>()(3, 5) << endl;
    cout << divides<int>()(3, 5) << endl;
    cout << modulus<int>()(3, 5) << endl;
    cout << negate<int>()(3) << endl;
	
	return 0;
}
```

# 关系运算类仿函数

STL内建关系类仿函数：等于：equal_to<T>，不等于：not_equal_to<T>，大于：greater<T>，大于等于：greater_equal<T>，小于：less<T>，小于等于：less_equal<T>。

```cpp
template <class T>
struct equal_to : public binary_function<T,T,bool> 
{
  bool operator()(const T& x, const T& y) const { return x == y; }
};

template <class T>
struct not_equal_to : public binary_function<T,T,bool> 
{
  bool operator()(const T& x, const T& y) const { return x != y; }
};

template <class T>
struct greater : public binary_function<T,T,bool> 
{
  bool operator()(const T& x, const T& y) const { return x > y; }
};

template <class T>
struct less : public binary_function<T,T,bool> 
{
  bool operator()(const T& x, const T& y) const { return x < y; }
};

template <class T>
struct greater_equal : public binary_function<T,T,bool>
{
  bool operator()(const T& x, const T& y) const { return x >= y; }
};

template <class T>
struct less_equal : public binary_function<T,T,bool> 
{
  bool operator()(const T& x, const T& y) const { return x <= y; }
};
```

测试程序：

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() {
    // 产生仿函数实体
    equal_to<int> equal_to_obj;
    not_equal_to<int> not_equal_to_obj;
    greater<int> greater_obj;
    greater_equal<int> greater_equal_obj;
    less<int> less_obj;
    less_equal<int> less_equal_obj;

    // 使用对象完成函数功能
    cout << equal_to_obj(3, 5) << endl;			//0
    cout << not_equal_to_obj(3, 5) << endl;		//1
    cout << greater_obj(3, 5) << endl;			//0
    cout << greater_equal_obj(3, 5) << endl;	//0
    cout << less_obj(3, 5) << endl;				//1
    cout << less_equal_obj(3, 5) << endl;		//1

    // 直接使用仿函数的临时对象完成函数功能
    cout << equal_to<int>()(3, 5) << endl;
    cout << not_equal_to<int>()(3, 5) << endl;
    cout << greater<int>()(3, 5) << endl;
    cout << greater_equal<int>()(3, 5) << endl;
    cout << less<int>()(3, 5) << endl;
    cout << less_equal<int>()(3, 5) << endl;
	
	return 0;
}
```

# 逻辑运算类仿函数

STL内建逻辑类仿函数：逻辑运算And：logical_and<T>，逻辑运算Or：logical_or<T>，逻辑运算Not：logical_not<T>。

```cpp
template <class T>
struct logical_and : public binary_function<T,T,bool>
{
  bool operator()(const T& x, const T& y) const { return x && y; }
};

template <class T>
struct logical_or : public binary_function<T,T,bool>
{
  bool operator()(const T& x, const T& y) const { return x || y; }
};

template <class T>
struct logical_not : public unary_function<T,bool>
{
  bool operator()(const T& x) const { return !x; }
};
```

测试程序：

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main() {
    // 产生仿函数实体
    logical_and<int> and_obj;
    logical_or<int> or_obj;
    logical_not<int> not_obj;

    // 使用对象完成函数功能
    cout << and_obj(true, true) << endl;	//1
    cout << or_obj(true, false) << endl;	//1
    cout << not_obj(true) << endl;			//0

    // 直接使用仿函数的临时对象完成函数功能
    cout << logical_and<int>()(true, true) << endl;
    cout << logical_or<int>()(true, false) << endl;
    cout << logical_not<int>()(true) << endl;
	
	return 0;
}
```

# 证同、选择、投射

以下介绍的仿函数，都只是将其参数原封不动地传回。其中某些仿函数对传回的参数有刻意的选择，或者刻意的忽略。

```cpp
// 证同函数，任何函数经过后不会改变，用于set rb_tree keyOfValue op
// identity is an extensions: it is not part of the standard.
template <class _Tp>
struct _Identity : public unary_function<_Tp,_Tp> {
  const _Tp& operator()(const _Tp& __x) const { return __x; }
};

template <class _Tp> struct identity : public _Identity<_Tp> {};

// 选择函数，返回pair第一元素，用于map rb_tree keyOfValue op
// select1st and select2nd are extensions: they are not part of the standard.
template <class _Pair>
struct _Select1st : public unary_function<_Pair, typename _Pair::first_type> {
  const typename _Pair::first_type& operator()(const _Pair& __x) const {
    return __x.first;
  }
};

// 选择函数，返回pair第二元素
template <class _Pair>
struct _Select2nd : public unary_function<_Pair, typename _Pair::second_type>
{
  const typename _Pair::second_type& operator()(const _Pair& __x) const {
    return __x.second;
  }
};

template <class _Pair> struct select1st : public _Select1st<_Pair> {};
template <class _Pair> struct select2nd : public _Select2nd<_Pair> {};

// 传回一个忽略另一个
// project1st and project2nd are extensions: they are not part of the standard
template <class _Arg1, class _Arg2>
struct _Project1st : public binary_function<_Arg1, _Arg2, _Arg1> {
  _Arg1 operator()(const _Arg1& __x, const _Arg2&) const { return __x; }
};

template <class _Arg1, class _Arg2>
struct _Project2nd : public binary_function<_Arg1, _Arg2, _Arg2> {
  _Arg2 operator()(const _Arg1&, const _Arg2& __y) const { return __y; }
};

template <class _Arg1, class _Arg2> 
struct project1st : public _Project1st<_Arg1, _Arg2> {};

template <class _Arg1, class _Arg2>
struct project2nd : public _Project2nd<_Arg1, _Arg2> {};
```
​