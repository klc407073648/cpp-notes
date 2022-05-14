# 第四章：序列式容器 deque

[[toc]]

# deque概述

deque（double-ended queue，双端队列）是一种具有队列和栈的性质的数据结构。相比于vector单向开口的连续线性空间而言，deque则是一种**双向开口的连续线性空间**，可以在头尾两端分别做元素的插入和删除操作。虽然vector从技术层面也可以对头部操作，但是效率极低。即deque与vector的最大差异在于:

1. deque可以在常数时间内完成对头部元素的插入或删除操作；
2. deque没有容量的概念，它是动态地以分段连续空间组合而成，随时可以增加一段新的空间并链接起来。

![deque](/_images/book-note/stlsource/deque.png)

# deque的中控器

deque由一段一段的定量连续空间构成。一旦有必要在dequer前端或尾端增加新空间，便配置一段定量连续空间，串接在整个deque的头端或尾端。deque的最大任务是在这些分段的定量连续空间上，维护其整体连续的假象，并提供随机存取的接口。**避开了“重新配置、复制、释放”的轮回，代价则是复杂的迭代器架构**。

deque采用一块所谓的map作为主控。这里所谓map是一小块连续空间，其中每个元素(此处称为一个节点，node)都是指针，指向另一段(较大的)连续线性空间，称为缓冲区。缓冲区才是deque的储存空间主体。

```cpp
template<class T, class Alloc = alloc, size_t BufSiz = 0>
class deque{
public :
	typedef	T value_type ;
	typedef	value_type* pointer ;
	...
protected :
	//元素的指针的指针(pointer of pointer of T)
	typedef	pointer* map_pointer ; //其实就是T**
 
protected :
	map_pointer map ; //指向map,map是块连续空间，其内的每个元素
					  //都是一个指针(称为节点)，指向一块缓冲区
	size_type map_size ;//map内可容纳多少指针
	...
};
```

![deque中控器](/_images/book-note/stlsource/deque中控器.png)

# deque的迭代器

deque是分段连续空间，维持”整体连续“假象的任务，落在迭代器的operator++和operator—两个运算子上。

```cpp
template<class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator{ //未继承std::iterator
	typedef	__deque_iterator<T,T&,T*,BufSize>	iterator ;
	typedef	__deque_iterator<T,const T&,const T*,BufSize>	const_iterator ;
	static	size_t	buffer_size() {return __deque_buf_size(BufSize,sizeof(T)) ;} 
 
	//未继承std::iterator，所以必须自行撰写五个必要的迭代器相应型别
	typedef	random_access_iterator_tag	iterator_category ;
	typedef	T	value_type ;
	typedef	Ptr	pointer ;
	typedef	Ref	reference ;
	typedef	size_t	size_type ;
	typedef	ptrdiff_t	difference_type ;
	typedef	T**	map_pointer ;
 
	typedef	__deque_iterator	self ;
 
	//保持与容器的联结
	T *cut ; //此迭代器所指之缓冲区中的现行(current)元素
	T *first ; //此迭代器所指之缓冲区的头
	T *last ;	//此迭代器所指之缓冲区的尾(含备用空间)
	map_pointer node ; //指向管控中心
	...
};
```

![deque中控器、缓冲区、迭代器的相互关系](/_images/book-note/stlsource/deque中控器、缓冲区、迭代器的相互关系.png)

# deque的数据结构

deque除了维护一个指向map的指针外，也维护start，finish两个迭代器，分别指向第一缓冲区的第一个元素和最后缓冲区的最后一个元素(的下一个位置)。

```cpp
template<class T, class Alloc = alloc, size_t BufSiz = 0>
class deque{
public :
	typedef	T	value_type ;
	typedef	value_type*	pointer ;
	typedef	size_t	size_type ;
public :
	typedef	__deque_iterator<T,T&,T*,BufSiz>	iterator ;
protected :
	//元素的指针的指针(pointer of pointer of T)
	typedef	pointer*	map_pointer ;
protected:
	iterator	start ; //表现第一节点
	iterator	finish ; //表现最后一个节点
	map_pointer	map ; //指向map,map是块连续空间，其每个元素都是个指针，指向一个节点(缓冲区)
	size_type	map_size ; //map内有多少指针
	...
} ;
```

# deque的构造与内存管理

以程序实现来初步了解deque的构造和内存管理：

```cpp
#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;

class alloc {
};

int main() {
    deque<int, allocator<int>> ideq(20, 9);
	//deque<int,alloc,8> ideq(20, 9);//在linux下不支持alloc
    cout << "size=" << ideq.size() << endl;

    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;

    for (int i = 0; i < 3; ++i)
        ideq.push_back(i);
    
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.push_back(3);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.push_front(99);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.push_front(98);
    ideq.push_front(97);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    deque<int, allocator<int>>::iterator itr;
    itr = find(ideq.begin(), ideq.end(), 99);
    cout << *itr << endl;
    cout << *(itr._M_cur) << endl;
}
```

执行结果:

```
[root@192 4_STL_sequence_container]# ./4_4_5_deque-test                         
size=20
9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 0 1 2
size=23
9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 0 1 2 3
size=24
99 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 0 1 2 3
size=25
97 98 99 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 0 1 2 3
size=27
99
99
```

上述程序的处理过程可以表现为如下图像：

![deque-1](/_images/book-note/stlsource/deque-1.png)

![deque-2](/_images/book-note/stlsource/deque-2.png)

![deque-3](/_images/book-note/stlsource/deque-3.png)

![deque-4](/_images/book-note/stlsource/deque-4.png)

deque的构造和析构函数：

```cpp
  deque():start(),finish(),map_size(0),map(0)
  {
      create_map_and_nodes(0);
  }
  deque(int n,const value_type& value):start(),finish(),map(0),map_size(0)
  {
      fill_initialize(n,value);
  }
  ~deque(){}

  void fill_initialize(size_type n,const value_type& value)
  { //负责产生并安排好deque的结构，并将元素的初值设定好
        create_map_and_nodes(n); //把deque的结构都安排好
        map_pointer cur;
        //已经获得空间,为每个节点缓冲区设定初值
        for(cur=start.node;cur<finish.node;++cur)
        {
            uninitialized_fill(*cur,*cur+buffer_size(),value);
        }
        //最后一个节点的设定稍有不同（尾端可能有备用空间，不必设初值）
        uninitialized_fill(finish.first,finish.cur,value);
    }

    void creat_map_and_nodes(size_type num_elements)
    { //产生并安排好deque的结构
        size_type num_nodes=num_elements/buffer_size()+1; 
        //一个map要管理几个节点，最少8个，最多是“所需节点数+2”，前后各预留一个，扩充时用
        map_size=max(initial_map_size(),num_nodes+2);
        map=map_allocator::allocate(map_size);

        map_pointer nstart=map+(map_size-num_nodes)/2;
        map_pointer nfinish=nstart+num_nodes-1;
        map_pointer cur;

        for(cur=nstart;cur<=nfinish;cur++)
        {
            *cur=allocate_node();
        }
        start.set_node(nstart);
        finish.set_node(nfinish);
        start.cur=start.first;
        finish.cur=finish.first+num_elements%buffer_size();
    }
```

# deque的元素操作

```cpp
void push_back(const value_type &t)
{
    if (finish.cur != finish.last - 1)
    {
        construct(finish.cur, t);
        ++finish.cur;
    }
    else //需要配置新的缓冲区
    {
        push_back_aux(t);
    }
}

void push_front(const value_type &t)
{
    if (start.cur != start.first)
    {
        construct(start.cur - 1, t);
    }
    else
    {
        push_front_aux(t);
    }
}

void pop_back()
{
    if (finish.cur != finish.first)
    {
        --finish.cur;
        destroy(finish.cur); //将最后元素析构,左开右闭
    }
    else
    {
        //最后缓冲区没有任何元素
        pop_back_aux(); //这里将进行缓冲区的释放工作
    }
}

void pop_front()
{
    if (start.cur != start.last - 1)
    {
        destroy(start.cur);
        ++start.cur;
    }
    else
        pop_front_aux();
}

void push_back_aux(const value_type &t) //只剩最后一个缓冲区的最后一个备用缓冲区
{                                       //先配置一块新的缓冲区，再设新元素内容，更改迭代器finish的状态
    value_type t_copy = t;
    reserve_map_at_back();                //若符合某种条件，则必须重换一个map
    *(finish.node + 1) = allocate_node(); //配置一新缓冲区
    construct(finish.cur, t_copy);
    finish.set_node(finish.node + 1);
    finish.cur = finish.first;
}

void push_front_aux(const value_type &t)
{
    value_type t_copy = t;
    reserve_map_at_front();
    *(start.node - 1) = allocate_node();
    start.set_node(start.node - 1);
    start.cur = start.last - 1;
    construct(start.cur, t_copy);
}

void reserve_map_at_back(size_type nodes_to_add = 1)
{
    if (nodes_to_add + 1 > map_size - (finish.node - map)) //map尾端的节点备用空间不足
    {
        //换一个map（配置更大的，拷贝原来的，释放原来的）
        reallocate_map(nodes_to_add, false);
    }
}

void reserve_map_at_front(size_type nodes_to_add = 1)
{
    if (nodes_to_add > start.node - map)
    {
        reallocate_map(nodes_to_add, true);
    }
}


void pop_back_aux()
{                                  //finish.cur==finish.first 释放该缓冲区
    deallocate_node(finish.first); //释放最后一个缓冲区
    finish.set_node(finish.node - 1);
    finish.cur = finish.last - 1;
    destroy(finish.cur); //析构
}

void pop_front_aux()
{
    destory(start.cur);
    deallocate_node(start.last);
    start.set_node(start.node + 1);
    start.cur = start.first;
}

void clear()
{
    for (map_pointer node = start.node + 1; node < finish.node; ++node)
    {
        destory(*node, *node + buffer_size());            //析构元素
        data_allocator::deallocate(*node, buffer_size()); //释放内存
    }

    if (start.node != finish.node) //至少有两个缓冲区
    {
        destroy(start.cur, start.last);
        destroy(finish.first, finish.cur);
        //保留头缓冲区
        data_allocator::deallocate(finish.first, buffer_size());
    }
    else
    {
        destroy(start.cur, finish.cur);
    }
    finish = start;
}

iterator begin() { return start; }
iterator end() { return finish; }

reference operator[](size_type n)
{
    //调用_deque_iterator<>::operator[]
    return *(start + n);
}

reference front() { return *start; }
reference back() { return *(finish - 1); }

size_type size() const { return finish - start; }
size_type max_size() const { return size_type(-1); }

bool empty() const { return finish == start; }
```