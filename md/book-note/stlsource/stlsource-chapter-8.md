# 第八章：配接器

[[toc]]

# 配接器概述

配接器（adapters）在 STL 组件的灵活组合运用功能上，扮演着轴承、转换器的角色。Adapter 这个概念，事实上是一种设计模式。《Design Patterns》一书提到 23 个最普及的设计模式，其中对 adapter 样式的定义如下：**将一个 class 的接口转换为另一个 class 的接口，使原本因接口不兼容而不能合作的 classes，可以一起运作。**

## 配接器之概观与分类

STL 所提供的各种配接器中，改变容器（containers）接口者，我们称为 container adapter，改变迭代器（iterators）接口者，我们称之为 iterator adapter，改变仿函数（functors）接口者，我们称为 function adapter。

* 容器配接器：STL 提供的两个容器 queue 和 stack，其实都只不过是一种配接器，底层由deque构成。
* 迭代器配接器：STL 提供了许多应用于迭代器身上的配接器，包括 insert iterators，reverse iterators，iostream iterators。
* 仿函数配接器：是所有配接器中数量最庞大的一个族群，其配接灵活度也是前二者所不能及，可以配接、配接、再配接。

# container adapters

stack和queue是两个容器配接器，**底层默认由deque构成**。stack封住了所有的deque对外接口，只开放符合stack原则的几个函数；queue封住了所有的deque对外接口，只开放符合queue原则的几个函数。

```cpp
template <class T ,class Sequence = deque<T>>
class stack {
protected:
    Sequence  c ; //底层容器
    ...
};


template <class T ,class Sequence = deque<T>>
class queue{
protected:
    Sequence  c ; //底层容器
    ...
};
```

# iterator adapters

## insert iterators

insert iterators包括back_insert_iterator，front_insert_iterator和insert_iterator。主要观念是，每个insert iterators内部都维护有一个容器；容器有自己的迭代器，当客户端对insert iterators做赋值操作时，就在insert iterators中转为对该容器的迭代器做插入操作，其他的迭代器功能则被关闭（例如operator++、operator--、operator*）。

迭代器源码如下：

```cpp
// 迭代器配接器，用来将迭代器的赋值操作替换为插入操作
// 从容器尾端插入
template <class _Container>
class back_insert_iterator {
protected:
  _Container* container; // 底层容器
public:
  typedef _Container          container_type;
  typedef output_iterator_tag iterator_category; // 注意类型，只写
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;

  // 与容器绑定起来
  explicit back_insert_iterator(_Container& __x) : container(&__x) {}
  back_insert_iterator<_Container>&
  operator=(const typename _Container::value_type& __value) { 
    container->push_back(__value); // 这里是替换成插入操作
    return *this;
  }
  // 以下不起作用，关闭功能
  back_insert_iterator<_Container>& operator*() { return *this; }
  back_insert_iterator<_Container>& operator++() { return *this; }
  back_insert_iterator<_Container>& operator++(int) { return *this; }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class _Container>
inline output_iterator_tag
iterator_category(const back_insert_iterator<_Container>&)
{
  return output_iterator_tag();
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// 辅助函数
template <class _Container>
inline back_insert_iterator<_Container> back_inserter(_Container& __x) {
  return back_insert_iterator<_Container>(__x);
}

// 迭代器配接器，用来将迭代器的赋值操作替换为插入操作
// 从容器头端插入
// 不适用于vector，因为vector没有push_front
template <class _Container>
class front_insert_iterator {
protected:
  _Container* container;  // 底层容器
public:
  typedef _Container          container_type;
  typedef output_iterator_tag iterator_category; // 注意类型，只写
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;

  explicit front_insert_iterator(_Container& __x) : container(&__x) {}
  front_insert_iterator<_Container>&
  operator=(const typename _Container::value_type& __value) { 
    container->push_front(__value); // 替换成插入操作
    return *this;
  }
  // 关闭以下功能
  front_insert_iterator<_Container>& operator*() { return *this; }
  front_insert_iterator<_Container>& operator++() { return *this; }
  front_insert_iterator<_Container>& operator++(int) { return *this; }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class _Container>
inline output_iterator_tag
iterator_category(const front_insert_iterator<_Container>&)
{
  return output_iterator_tag();
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// 辅助函数
template <class _Container>
inline front_insert_iterator<_Container> front_inserter(_Container& __x) {
  return front_insert_iterator<_Container>(__x);
}

// 迭代器配接器，用来将迭代器的赋值操作替换为插入操作
// 从容器随机插入
template <class _Container>
class insert_iterator {
protected:
  _Container* container;  // 底层容器
  typename _Container::iterator iter;
public:
  typedef _Container          container_type;
  typedef output_iterator_tag iterator_category; // 类型只写
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;

  insert_iterator(_Container& __x, typename _Container::iterator __i) 
    : container(&__x), iter(__i) {}
  insert_iterator<_Container>&
  operator=(const typename _Container::value_type& __value) { 
    iter = container->insert(iter, __value); // 调用insert
    ++iter; // 使insert iterator永远随其目标贴身移动
    return *this;
  }
  // 关闭功能
  insert_iterator<_Container>& operator*() { return *this; }
  insert_iterator<_Container>& operator++() { return *this; }
  insert_iterator<_Container>& operator++(int) { return *this; }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class _Container>
inline output_iterator_tag
iterator_category(const insert_iterator<_Container>&)
{
  return output_iterator_tag();
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// 辅助函数
template <class _Container, class _Iterator>
inline 
insert_iterator<_Container> inserter(_Container& __x, _Iterator __i)
{
  typedef typename _Container::iterator __iter;
  return insert_iterator<_Container>(__x, __iter(__i));
}
```

## reverse iterators

reverse iterators将迭代器的移动行为倒转。 当迭代器被逆转，虽然实体位置不变，但逻辑位置必须改变，主要是为了配合迭代器区间的“前闭后开“习惯。

![reverse_iterator](/_images/book-note/stlsource/reverse_iterator.png)

源码如下：

```cpp
template <class _Iterator>
class reverse_iterator 
{
protected:
  _Iterator current;
public:
  typedef typename iterator_traits<_Iterator>::iterator_category
          iterator_category;
  typedef typename iterator_traits<_Iterator>::value_type
          value_type;
  typedef typename iterator_traits<_Iterator>::difference_type
          difference_type;
  typedef typename iterator_traits<_Iterator>::pointer
          pointer;
  typedef typename iterator_traits<_Iterator>::reference
          reference;

  typedef _Iterator iterator_type;
  typedef reverse_iterator<_Iterator> _Self;

public:
  reverse_iterator() {}
  explicit reverse_iterator(iterator_type __x) : current(__x) {}

  reverse_iterator(const _Self& __x) : current(__x.current) {}
#ifdef __STL_MEMBER_TEMPLATES
  template <class _Iter>
  reverse_iterator(const reverse_iterator<_Iter>& __x)
    : current(__x.base()) {}
#endif /* __STL_MEMBER_TEMPLATES */
    
  iterator_type base() const { return current; }
  reference operator*() const {
    _Iterator __tmp = current;
    return *--__tmp;
  }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */

  _Self& operator++() {
    --current;
    return *this;
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    --current;
    return __tmp;
  }
  _Self& operator--() {
    ++current;
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    ++current;
    return __tmp;
  }

  _Self operator+(difference_type __n) const {
    return _Self(current - __n);
  }
  _Self& operator+=(difference_type __n) {
    current -= __n;
    return *this;
  }
  _Self operator-(difference_type __n) const {
    return _Self(current + __n);
  }
  _Self& operator-=(difference_type __n) {
    current += __n;
    return *this;
  }
  reference operator[](difference_type __n) const { return *(*this + __n); }  
}; 
```

## stream iterators

stream iterators可以将迭代器绑定到某个stream对象身上。绑定一个istream object，其实就是在istream iterator内部维护一个istream member，客户端对这个迭代器做的operator++操作，会被导引调用内部所含的那个istream member的输入操作。绑定一个ostream object，就是在ostream iterator内部维护一个ostream member，客户端对这个迭代器做的operator=操作，会被导引调用内部所含的那个ostream member的输出操作。

源码如下：

```cpp
template <class _Tp, 
          class _CharT = char, class _Traits = char_traits<_CharT>,
          class _Dist = ptrdiff_t> 
class istream_iterator {
public:
  typedef _CharT                         char_type;
  typedef _Traits                        traits_type;
  typedef basic_istream<_CharT, _Traits> istream_type;

  typedef input_iterator_tag             iterator_category;
  typedef _Tp                            value_type;
  typedef _Dist                          difference_type;
  typedef const _Tp*                     pointer;
  typedef const _Tp&                     reference;

  istream_iterator() : _M_stream(0), _M_ok(false) {}
  istream_iterator(istream_type& __s) : _M_stream(&__s) { _M_read(); }

  reference operator*() const { return _M_value; }
  pointer operator->() const { return &(operator*()); }

  istream_iterator& operator++() { 
    _M_read(); 
    return *this;
  }
  istream_iterator operator++(int)  {
    istream_iterator __tmp = *this;
    _M_read();
    return __tmp;
  }

  bool _M_equal(const istream_iterator& __x) const
    { return (_M_ok == __x._M_ok) && (!_M_ok || _M_stream == __x._M_stream); }

private:
  istream_type* _M_stream;
  _Tp _M_value;
  bool _M_ok;

  void _M_read() {
    _M_ok = (_M_stream && *_M_stream) ? true : false;
    if (_M_ok) {
      *_M_stream >> _M_value;
      _M_ok = *_M_stream ? true : false;
    }
  }
};


template <class _Tp,
          class _CharT = char, class _Traits = char_traits<_CharT> >
class ostream_iterator {
public:
  typedef _CharT                         char_type;
  typedef _Traits                        traits_type;
  typedef basic_ostream<_CharT, _Traits> ostream_type;

  typedef output_iterator_tag            iterator_category;
  typedef void                           value_type;
  typedef void                           difference_type;
  typedef void                           pointer;
  typedef void                           reference;

  ostream_iterator(ostream_type& __s) : _M_stream(&__s), _M_string(0) {}
  ostream_iterator(ostream_type& __s, const _CharT* __c) 
    : _M_stream(&__s), _M_string(__c)  {}
  ostream_iterator<_Tp>& operator=(const _Tp& __value) { 
    *_M_stream << __value;
    if (_M_string) *_M_stream << _M_string;
    return *this;
  }
  ostream_iterator<_Tp>& operator*() { return *this; }
  ostream_iterator<_Tp>& operator++() { return *this; } 
  ostream_iterator<_Tp>& operator++(int) { return *this; } 
private:
  ostream_type* _M_stream;
  const _CharT* _M_string;
};
```

# 测试程序

```cpp
#include <iterator> // for iterator adapters
#include <deque>
#include <algorithm> // for copy()
#include <iostream>

using namespace std;

int main() {
    // 将outite绑定到cout，每次对outite指派一个元素，就后接一个“ ”
    ostream_iterator<int> outite(cout, " ");

    int ia[] = {0, 1, 2, 3, 4, 5};
    deque<int> id(ia, ia + 6);

    // 将所有元素拷贝到outite，即cout
    copy(id.begin(), id.end(), outite);
    cout << endl;

    // 将ia[]的部分元素拷贝到id内，使用front_insert_iterator
    // front_insert_iterator会将assign操作给push_front操作
    // vector不支持push_front操作，所以不以vector做示范对象
    copy(ia + 1, ia + 2, front_inserter(id));
    copy(id.begin(), id.end(), outite);
    cout << endl;

    // 将ia[]的部分元素拷贝到id内，使用back_insert_iterator
    copy(ia + 1, ia + 2, back_inserter(id));
    copy(id.begin(), id.end(), outite);
    cout << endl;

    // 搜寻元素5所在位置
    deque<int>::iterator ite = find(id.begin(), id.end(), 5);
    // 将ia[]的部分元素拷贝到id内，使用insert_iterator
    copy(ia + 1, ia + 2, inserter(id, ite));
    copy(id.begin(), id.end(), outite);
    cout << endl;

    // 将所有元素逆向拷贝到outite
    // rbegin()和rend()与reverse_iterator有关
    copy(id.rbegin(), id.rend(), outite);
    cout << endl;

    // 将inite绑定到cin，将元素拷贝到inite，知道eos出现
    istream_iterator<int> inite(cin), eos; // eos: end-of-stream
    copy(inite, eos, inserter(id, id.begin()));
    // 输入数字，停止时可以输入任意字符

    copy(id.begin(), id.end(), outite);

    return 0;
}

```

执行结果：

```bash
[root@192 8_STL_adapter]# ./8_1_2_iterator-adapter
0 1 2 3 4 5
1 0 1 2 3 4 5
1 0 1 2 3 4 5 1
1 0 1 2 3 4 1 5 1
1 5 1 4 3 2 1 0 1
1 2 3 e // 输入数字，停止时可以输入任意字符
1 2 3 1 0 1 2 3 4 1 5 1 
```

# function adapter

仿函数配接操作包括绑定(bind)、否定(negate)、组合(compose)、以及对一般函数或成员函数的修饰。仿函数配接器的价值在于，通过它们之间的绑定、组合、修饰能力，几乎可以创造出各种可能的表达式，配合STL算法。每一个仿函数配接器内藏了一个member object，其型别等同于它所要配接的对象。

使用场景：

* 对返回值进行逻辑否定：not1，not2
* 对参数进行绑定：bind1st，bind2nd
* 用于函数合成：compose1，compose2
* 用于函数指针：ptr_fun
* 用于成员函数指针：mem_fun，mem_fun_ref

count_if的实例：

![count_if](/_images/book-note/stlsource/count_if.png)

测试程序：

```cpp
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

// compose1在mingw中没有，所以把定义搬了过来
template <class _Operation1, class _Operation2>
class unary_compose
  : public unary_function<typename _Operation2::argument_type,
                          typename _Operation1::result_type> 
{
protected:
  _Operation1 _M_fn1;
  _Operation2 _M_fn2;
public:
  unary_compose(const _Operation1& __x, const _Operation2& __y) 
    : _M_fn1(__x), _M_fn2(__y) {}
  typename _Operation1::result_type
  operator()(const typename _Operation2::argument_type& __x) const {
    return _M_fn1(_M_fn2(__x));
  }
};

template <class _Operation1, class _Operation2>
inline unary_compose<_Operation1,_Operation2> 
compose1(const _Operation1& __fn1, const _Operation2& __fn2)
{
  return unary_compose<_Operation1,_Operation2>(__fn1, __fn2);
}


void print(int i) {
    cout << i << " ";
}

class Int {
public: 
    // explicit 只能修改只有一个参数的类构造函数，
    // 或是除了第一个参数外其他参数都有默认值的情况
    // 表明该构造函数是显示的而非隐式的
    // 作用是禁止类构造函数的隐式自动转换
    // implicit 表示隐式，类构造函数默认声明为隐式
    // google c++规范与effective c++都推荐使用explicit声明
    explicit Int(int i) : m_i(i) {}

    void print1() const {
        cout << "[" << m_i << "]";
    }

private:
    int m_i;
};

int main() {
    // 将outite绑定到cout，每次对outite指派一个元素，就后接一个“ ”
    ostream_iterator<int> outite(cout, " ");

    int ia[6] = {2, 21, 12, 7, 19, 23};
    vector<int> iv(ia, ia + 6);

    // 找出不小于12的元素个数
    cout << count_if(iv.begin(), iv.end(),
                     not1(bind2nd(less<int>(), 12)));
    cout << endl;

    // 令每个元素v执行(v+2)*3然后输往outite
    transform(iv.begin(), iv.end(), outite,
              compose1(bind2nd(multiplies<int>(), 3),
                       bind2nd(plus<int>(), 2)));
    cout << endl;

    // 将所有元素拷贝到outite
    copy(iv.begin(), iv.end(), outite);
    cout << endl;
    // 1. 使用函数指针搭配stl算法
    for_each(iv.begin(), iv.end(), print);
    cout << endl;

    // 2. 以修饰过的一般函数搭配stl算法
    for_each(iv.begin(), iv.end(), ptr_fun(print));
    cout << endl;

    Int t1(3), t2(7), t3(20), t4(14), t5(68);
    vector<Int> Iv;
    Iv.push_back(t1);
    Iv.push_back(t2);
    Iv.push_back(t3);
    Iv.push_back(t4);
    Iv.push_back(t5);
    // 3. 以修饰过的成员函数搭配stl算法
    for_each(Iv.begin(), Iv.end(), mem_fun_ref(&Int::print1));

    return 0;
}
```

执行结果：

```bash
[root@192 8_STL_adapter]# ./8_1_3_functor-adapter
4
12 69 42 27 63 75
2 21 12 7 19 23
2 21 12 7 19 23
2 21 12 7 19 23
[3][7][20][14][68][
```
​