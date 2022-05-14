# 第四章：序列式容器 list

[[toc]]

# list概述

相比于vector的连续线性空间，list显得更为复杂；**但list每次插入或删除一个元素时，就将配置或释放一个元素。**因此，list对于空间的运用有绝对的精准，一点也不浪费。对于任何位置的插入或元素删除，list永远是常数时间。

**list的节点**

下面是STL list的节点结构，显然是一个双向链表。

```cpp
template <class T>
struct __list_node {
	typedef void* void_pointer; 
	void_pointer prev; //型别为void*,其实可设为__list_node<T>*
	void_pointer next;
	T data;
};
```

# list的迭代器

* list中的元素由于都是节点，因此其迭代器递增时取用的是下一个节点，递减时取用上一个节点，取值时取的是节点的数据值，成员存取时取用的是节点的成员；
* 由于list是双向链表，迭代器必须具备前移、后移的能力，因此，list提供的是Bidirectional Iterators；
* list的插入和接合操作都不会导致原有迭代器失效，但vector的插入可能造成存储空间重新分配，导致原有的迭代器全部失效。

![list节点和list迭代器](/_images/book-note/stlsource/list节点和list迭代器.png)

```cpp
reference operator*() const { return (*node).data; }//取结点数据值
 
pointer operator->() const { return &(operator*()); }//成员存取

self& operator++() { //运算符前置++的重载
    node = (link_type)((*node).next);
    return *this;
}
self operator++(int) { //运算符后置++的重载
   self tmp = *this;
   ++*this;
   return tmp;
}

self& operator--() { //运算符前置--的重载
    node = (link_type)((*node).prev);
    return *this;
}
selfoperator--(int) { //运算符后置--的重载
   self tmp = *this;
   --*this;
   return tmp;
}
```

# list的数据结构

SGI list是一个双向链表，而且是一个环状双向链表:

```cpp
template<class T,class Alloc = alloc> //缺省使用alloc为配置器:w
class list{
protected :
	typedef	__list_node<T> list_node ;
public  :
	typedef	list_node* link_type ;
protected :
	link_type node ; //只要一个指针，便可以表示整个环状双向链表
};
```

如果让指针 node 指向刻意置于尾端的一个空白节点， node 便能符合 STL 对于“前闭后开”区间的要求，成为 last 迭代器。

```cpp
//取首元素，node是尾端的一个空节点
iterator begin()  {  return  (link_type) ((*node).next); }
//取尾元素的下一个，即node
iterator end()     {  return node;  }
//为空，说明只有node
bool empty() const  {  return node->next == node; }
size_type size()  const {
	size_type result = 0;
	distance(begin(), end(), result);
	return result;
}
reference front()    { return *begin(); }
reference back()    {  return *(--end());  }
```

![list示意图](/_images/book-note/stlsource/list示意图.png)

# list的构造与内存管理

list采用list_node_allocator来配置节点空间，以下四个函数分别用来配置、释放、构造、销毁一个节点。

```cpp
template<class T,class Alloc = alloc> //缺省使用alloc为配置器:w
class list{
protected :
	typedef	__list_node<T> list_node ;
    //专属之空间配置器，每次配置一个节点大小
	typedef	simple_alloc<list_node,Alloc> list_node_allocator;
    ...
};

//既然说到配置空间，就将配置、释放、构造、销毁一并提了吧
//配置一个节点
link_type get_node() 	{ return list_node_allocator::allocate(); }  
//释放一个节点
void put_node(link_type p)	{ list_node_deallocator::deallocate(p); }
//产生一个节点，带有元素值
link_type create_node(const T& x)  {
	link_type p = get_node();
	construct(&p->data, x);
	return p;
}
//销毁一个节点
void destroy_node(link_type p) {
	destroy(&p->data);
	put_node(p);
}
```

list提供了默认的构造函数，使得可以创建一个空list：

```cpp
public:
	list()   {  empty_initialize();  }   //默认构造函数
protected:
	void empty_initialize() {
		node = get_node();       //配置一个节点空间
		node->next = node;
		node->prev = node;
	}
```

# list元素操作

insert()是一个重载函数，最简单的一种如下：

```cpp
iterator insert(iterator position, const T& x){//在迭代器position所指位置插入一个节点，内容为x
	link_type tmp = create_node(x);
	tmp->next = position.node;
	tmp->prev = position.node->node;
	(link_type(position.node->prev))->next = tmp;
    position.node->prev =tmp;
	return tmp;
}
```

push_front() 函数：将新元素插入于list头端，内部调用insert()函数。

```cpp
void push_front(const T&x)  { insert(begin(),x); }
```

push_back()函数：将新元素插入于list尾端，内部调用insert()函数。

```cpp
void push_back(const T& x)   {  insert(end(),x); }
 erase() 函数：移除迭代器position所指节点。

iterator erase(iterator position){
link_type next_node=link_type(position.node->next);
link_type prev_node=link_type(position.node->prev);
prev_node->next=next_node;
next_node->prev=prev_node;
destroy_node(position.node);
return iterator(next_node);
}
```

pop_front()函数：移除头结点，内部调用erase()函数。

```cpp
void pop_front()  {  erase(begin());  }
pop_back() 函数：移除尾结点，内部调用erase()函数。

void pop_back(){
iterator i=end();
erase(--i);
}
```

clear()函数：清除所有节点：

```cpp
template <class T, class Alloc>  
void list<T, Alloc>::clear()  
{  
  link_type cur = (link_type) node->next;//node原来指向list的end,node->next为begin  
  while (cur != node)  
  {  
    link_type tmp = cur;  
    cur = (link_type) cur->next;  
    destroy_node(tmp);  
  }  
  // 恢复node原始状态  
  node->next = node;  
  node->prev = node;  
}  
```

 transfer()迁移函数:将[ frirst , last ) 内所有元素移动到position之前。

```cpp
void transfer(iterator position, iterator first, iterator last) {
    if (position != last) {
      (*(link_type((*last.node).prev))).next = position.node; //(1)
      (*(link_type((*first.node).prev))).next = last.node;    //(2)
      (*(link_type((*position.node).prev))).next = first.node;//(3)
      link_type tmp = link_type((*position.node).prev);       //(4)
      (*position.node).prev = (*last.node).prev;              //(5)
      (*last.node).prev = (*first.node).prev;                 //(6)
      (*first.node).prev = tmp;                               //(7)
    }
  }
```

![list-transfer](/_images/book-note/stlsource/list-transfer.png)

splice结合操作：

```cpp
int iv[5] = { 5,6,7,8,9 };
list<int> ilist2(iv,iv+5);

//目前，ilist的内容为 0 2 99 3 4
ite = find(ilist.begin(),ilist.end(),99);
ilist.splice(ite,ilist2);  // 0 2 5 6 7 8 9 99 3 4
ilist.reverse();           // 4 3 99 9 8 7 6 5 2 0
ilist.sort();              // 0 2 3 4 5 6 7 8 9 99

// 将链表x移动到position所指位置之前  
void splice(iterator position, list& x)  
{  
    if (!x.empty())  
        transfer(position, x.begin(), x.end());  
}  
  
// 将链表中i指向的内容移动到position之前  
void splice(iterator position, list&, iterator i)  
{  
     iterator j = i;  
     ++j;  
     if (position == i || position == j) return;  
     transfer(position, i, j);  
}  
```