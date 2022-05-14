# 第四章：序列式容器 stack和queue

[[toc]]

# stack概述

stack是一种先进后出(First In Last Out,FILO)的数据结构，它只有一个出口。stack允许新增元素，移除元素、取得最顶端元素，但不允许有遍历行为。**若以deque为底部结构并封闭其头端开口，便轻而易举地形成了一个stack。同时，也可以使用list作为底层实现，它也是具有双向开口的数据结构**。由于stack系以底部容器完成其所有工作，而具有这种**修改某物接口，形成另一种风貌之性质者，称为adapter(配接器)。**因为stack的所有元素的进出都必须符合“先进后出”的条件，即只有stack顶端的元素，才会被外界取用，所以stack不提供走访功能，也不提供迭代器。

![stack](/_images/book-note/stlsource/stack.png)

## stack 完整定义

SGI STL以deque作为缺省情况下的stack底部结构。

```cpp
template<class T, class Sequence = deque<T> >
class stack{
	friend bool operator== __STL_NULL_TMPL_ARGS(const stack& , const stack&) ;
	friend bool operator< __STL_NULL_TMPL_ARGS(const stack& , const stack&) ;
public :
	typedef	typename Sequence::value_type value_type ;
	typedef	typename Sequence::size_type size_type ;	
	typedef	typename Sequence::reference reference ;
	typedef	typename Sequence::const_reference	const_reference ;
protected:
	Sequence e ; //底层容器
public :
	//以下完全利用Sequence c 的操作，完成stack的操作
	bool empty() const {return c.empty() ;} 
	size_type size() {return c.size();}
	reference top() {return c.back();}
	const_reference top() const {return c.back();}
	//deque是两头可进出，stack是末端进，末端出。
	void push(const value_type& x) {c.push_back(x) ;}
	void pop() {c.pop_back() ;}
	
} ;
```

## 以list作为stack的底部容器

```cpp
#include <stack>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    stack<int, list<int>> istack;
    //stack<int> istack; //缺省时使用deque
    istack.push(1);
    istack.push(3);
    istack.push(5);
    istack.push(7);

    cout << istack.size() << endl;   //4
    cout << istack.top() << endl;    //7

    istack.pop();
    cout << istack.top() << endl;    //5
    istack.pop();
    cout << istack.top() << endl;    //3
    istack.pop();
    cout << istack.top() << endl;    //1
    cout << istack.size() << endl;   //1
	
	return 0;
}
```

# queue

## queue概述

queue是一种先进先出(First In First Out,FIFO)的数据结构，它有两个出口。queue允许新增元素、移除元素、从最底端加入元素、取得最顶端元素，但不允许遍历行为，也不提供迭代器。**若以deque为底部结构并封闭其头端入口和尾部出口，便轻而易举地形成了一个queue。同时，也可以使用list作为底层实现，它也是具有双向开口的数据结构。**

![queue](/_images/book-note/stlsource/queue.png)

## queue 完整定义

SGI STL以deque作为缺省情况下的queue底部结构。

```cpp
template<class T, class Sequence = deque<T> >
class queue{
	
public :	
	typedef	typename Sequence::value_type value_type ;
	typedef	typename Sequence::size_type size_type ;
	typedef	typename Sequence::reference reference ;
	typedef	typename Sequence::const_reference const_reference ;
protected :
	Sequence c ; //底层容器
public :
	//以下完全利用Sequence c的操作，完成queue的操作
	bool empty() const {return c.empty();}
	size_type size() const {return c.size();}
	reference front() const {return c.front();}
	const_reference front() const {return c.front();}
	//deque是两头可进出，queue是末端进，前端出。
	void push(const value_type &x) {c.push_back(x) ;} 
	void pop() {c.pop_front();}
} ;
```

## 以list作为queue的底部容器

```cpp
#include <queue>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    queue<int, list<int>> iqueue;
	//queue<int> iqueue; //缺省时使用deque
    iqueue.push(1);
    iqueue.push(3);
    iqueue.push(5);
    iqueue.push(7);

    cout << iqueue.size() << endl;   //4
    cout << iqueue.front() << endl;  //1

    iqueue.pop();
    cout << iqueue.front() << endl;   //3
    iqueue.pop();
    cout << iqueue.front() << endl;   //5
    iqueue.pop();
    cout << iqueue.front() << endl;   //7
    cout << iqueue.size() << endl;   //1
	
	return 0;
}
```