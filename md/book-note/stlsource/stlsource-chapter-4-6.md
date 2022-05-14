# 第四章：序列式容器 priority_queue

[[toc]]

# priority_queue概述

priority_queue是一个**拥有权值观念的queue，它允许加入新元素，移除旧元素，审视元素值等功能**．只允许在尾部加入元素，并从头部取出元素，除此之外别无其他存取元素的途径。priority_queue缺省情况下是以vector为底层容器，再加上max-heap处理规则，STL priority_queue往往不被归类为Container(容器)，而被归类为container adapter。priority_queue的所有元素，进出都有一定规则，只有queue顶端的元素，才有机会被外界取用。它不提供遍历功能，也不提供迭代器。

![priority_queue](/_images/book-note/stlsource/priority_queue.png)

# priority_queue 完整定义

```cpp
template <class T, class Sequence = vector<T>,
	class Compare = less<typename Sequence::value_type> >
class priority_queue {
public:
	//vector自定义类型
protected:
	Sequence c;        //底层容器
	Compare comp; //元素大小比较标准
public：
	//...
	//用到heap泛型算法作为其实现
	//定义一个priority_queue实则是一个建堆的过程
	template <class InputIterator>
	priority_queue( InputIterator first,  InputIterator last, const Compare& x)
	  : c (first, last), comp(x) { make_heap(c.begin(), c.end(), comp);}
	priority_queue( InputIterator first,  InputIterator last)
	  : c (first, last) { make_heap(c.begin(), c.end(), comp);}
	//....
	void push(const value_type& x)  {
		__STL_TRY {
		//先利用底层容器的	push_back将新元素推入末端，再重排heap
			c.push_back(x);
			push_heap(c.begin(), c.end(), comp);
		}
		__STL_UNWIND(c.clear());
	}
	void pop()  {
		__STL_TRY {
		//先从heap内取出一个元素，并不是简单的弹出，而是重排heap，然后在以底层容器的pop_back取得被弹出的元素
			pop_heap(c.begin(), c.end(), comp);
			c.pop_back();
		}
		__STL_UNWIND(c.clear());
 	}
 };
```

# priority_queue测试实例

```cpp
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    // test priority queue
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    priority_queue<int> ipq(ia, ia + 9);
    cout << "size=" << ipq.size() << endl;

    for (int i = 0; i < ipq.size(); ++i)
        cout << ipq.top() << ' ';
    cout << endl;

    while(!ipq.empty()) {
        cout << ipq.top() << ' ';
        ipq.pop();
    }
    cout << endl;
}
```

执行结果：

```bash
[root@192 4_STL_sequence_container]# ./4_8_4_pqueue-test
size=9
9 9 9 9 9 9 9 9 9
9 8 5 4 3 3 2 1 0
```

​