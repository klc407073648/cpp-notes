# 第四章：序列式容器 vector

[[toc]]


# 容器的概观与分类

容器，置物之所也。研究数据的特定排列方式，以利于搜寻或排序或其他特殊目的，这一专门学科称为数据结构。几乎可以说，任何特定的数据结构都是为了实现某种特定的算法。

![容器分类](/_images/book-note/stlsource/容器分类.png)

SGI STL的各个容器（本图以内缩方式来表达基层与衍生层的关系）。**这里所谓的，并非派生关系，而是内含关系。**例如，heap内含一个vector，priority-queue内含一个heap，stack和queue都内含一个deque，set/map/multiset/multimap都内含一个RB-tree，hash_set/hash_map/hash_multiset/hash_multimap都内含一个hashtabe。

## vector概述

vector的数据安排以及操作方式，与array非常相似。两者的唯一差别在于**空间的运用的灵活性**。array是静态空间，一旦配置了就不能改变；vector的动态空间 ，随着元素的加入，它的内部机制会自行扩充空间以容纳新元素。vector的实现技术，**关键在于对其大小的控制以及重新配置时的数据移动效率。**

vector的内部定义如下：

```cpp
class vector {
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

protected:
  typedef simple_alloc<value_type, Alloc> data_allocator; // SGI STL 空间配置器接口
  iterator start;               // 表示目前使用空间的头
  iterator finish;              // 表示目前使用空间的尾
  iterator end_of_storage;      // 表示目前可用空间的尾
  void insert_aux(iterator position, const T& x);
  void deallocate() {           // 释放空间
    if (start) data_allocator::deallocate(start, end_of_storage - start);
  }

  void fill_initialize(size_type n, const T& value) {
    start = allocate_and_fill(n, value);
    finish = start + n;
    end_of_storage = finish;
  }
public:
  // 各种迭代器
  iterator begin() { return start; }
  const_iterator begin() const { return start; }
  iterator end() { return finish; }
  const_iterator end() const { return finish; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  // size、max_size、capacity、empty
  size_type size() const { return size_type(end() - begin()); }
  size_type max_size() const { return size_type(-1) / sizeof(T); }
  size_type capacity() const { return size_type(end_of_storage - begin()); }
  bool empty() const { return begin() == end(); }
  // 重载 []
  reference operator[](size_type n) { return *(begin() + n); }
  const_reference operator[](size_type n) const { return *(begin() + n); }


  // 构造函数，大都调用 fill_initialize
  vector() : start(0), finish(0), end_of_storage(0) {}
  vector(size_type n, const T& value) { fill_initialize(n, value); }
  vector(int n, const T& value) { fill_initialize(n, value); }
  vector(long n, const T& value) { fill_initialize(n, value); }
  explicit vector(size_type n) { fill_initialize(n, T()); }


  // 析构函数
  ~vector() { 
    destroy(start, finish);
    deallocate();
  }

  // 首尾元素
  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }

  void push_back(const T& x) {
    if (finish != end_of_storage) {
      construct(finish, x);
      ++finish;
    }
    else
      insert_aux(end(), x);
  }

  // 插入操作
  iterator insert(iterator position, const T& x) {
    size_type n = position - begin();
    if (finish != end_of_storage && position == end()) {
      construct(finish, x);
      ++finish;
    }
    else
      insert_aux(position, x);
    return begin() + n;
  }

  // 删除最尾端元素
  void pop_back() {
    --finish;
    destroy(finish);
  }

  //清除某位置上的元素
  iterator erase(iterator position) {
    if (position + 1 != end())
      copy(position + 1, finish, position); // 后续元素往前移动
    --finish;
    destroy(finish);
    return position;
  }

  // 清除迭代器所指定的区间的元素
  iterator erase(iterator first, iterator last) {
    iterator i = copy(last, finish, first);
    destroy(i, finish);
    finish = finish - (last - first);
    return first;
  }

  // 重新设置 vector 大小，若设置值 new_size 大于当前 size，在尾端插入 x
  void resize(size_type new_size, const T& x) {
    if (new_size < size()) 
      erase(begin() + new_size, end());
    else
      insert(end(), new_size - size(), x);
  }
  void resize(size_type new_size) { resize(new_size, T()); }
  void clear() { erase(begin(), end()); }

protected:
  // 配置空间并填满内容，其中__STL_TRY、__STL_UNWIND 为异常相关的宏，在 stl_config.h 中定义
  iterator allocate_and_fill(size_type n, const T& x) {
    iterator result = data_allocator::allocate(n);
    __STL_TRY {
      uninitialized_fill_n(result, n, x);
      return result;
    }
    __STL_UNWIND(data_allocator::deallocate(result, n));
  }

};
```

# vector 的迭代器

vector 维护的是一个连续的线性空间，所以不论其元素型别如何，普通指针 都可以作为 vector 的迭代器而满足所有必要条件，因为 vector 迭代器所需要的操作行为，如 operator*，operator->，operator++， operator–， operator+，operator-，operator+=， operator-=，普通指针天生就具备。vector 支持随机存取，而普通指针正有这样的能力。所以，**vector 提供的是 Random Access Iterators**。

```cpp
template <class T, class Alloc = alloc>
class vector
{
public:
    typedef T             value_type;
    typedef value_type*   iterator;
    ...
}
```

根据定义，如果客户端写出这样的代码：

```cpp
vector<int>::iterator ivite;
vector<Shape>::iterator svite;
```

ivite 型别就是 int*，svite 的型别就是 Shape*。

# vector数据结构

vector采用线性连续空间的数据结构。它以两个迭代器start和finish分别指向配置的来的连续空间中目前已被使用的范围，并以迭代器end_of_storage指向整块连续空间（含备用空间）的尾端:

```cpp
template<class T,class Alloc = alloc>  
class vector{  
...  
protected :  
      iterator start ; //表示目前使用空间的头  
      iterator finish ; // 表示目前使用空间的尾  
      iterator end_of_storage ; //表示目前可用空间的尾  
};
```

为了降低空间配置时的速度成本，vector 实际配置的大小可能比客户端需求量更大一些，以备将来可能的扩充。这便是容量（capacity）的概念。添加新元素时，如果超出当时的容量，则容量会扩充至两倍，如果两倍容量仍不足，就扩充至足够大的容量。上述容量的扩张必须经历**“重新配置、元素移动、释放空间”**等过程。vector数据插入过程的示意图如下:

![vector示意图](/_images/book-note/stlsource/vector示意图.png)

# vector构造与内存管理

vector缺省使用alloc作为空间配置器，并据此另外定义了一个data_allocator，为的是更方便以元素大小为配置单位：

```cpp
template<class T, class Alloc = alloc>  
class vector{
protected:
    typedef simple_alloc<value_type,Alloc> data_allocator;
    ...
}
```

于是，data_allocator::allocate(n)表示配置n个元素空间。

当我们以push_back()将新元素插入vector尾端时，该函数先检查是否还有备用空间，如果有就直接在备用空间上构造元素，并调整迭代器finish，使vector变大。如果没有备用空间，就扩充空间（重新配置、移动数据、释放原空间）：

```cpp
void push_back(const T& x) {
    if (finish != end_of_storage) {
      construct(finish, x);
      ++finish;
    }
    else
      insert_aux(end(), x);
}

template<class T, class Alloc>  
  void vector<T, Alloc>::insert_aux(iterator position, const T&x){  
      if (finish != end_of_storage){//还有备用空间  
          construct(finish, *(finish - 1)); //在备用空间起始处构造一个元素，以vector最后一个元素值为其初值  
          ++finish; //调整finish迭代器  
          T x_copy = x;  
          copy_backward(position, finish - 2, finish - 1);  
          *position = x_copy;  
      }  
      else{//没有备用空间  
          const size_type old_size = size();  
          const size_type new_size = old_size != 0 ? 2 * old_size : 1;  
          iterator new_start = data_allocator::allocate(new_size);  
          iterator new_finish = new_start;  
          try{  
              new_finish = uninitialized_copy(start, position, new_start);//将原vector的内容拷贝到新vector  
              construct(new_finish, x);  
              ++new_finish;  
              new_finish = uninitialzed_copy(position, finish, new_finish);//将安插点的原内容也拷贝过来  
          }  
          catch (excetion e){  
              destroy(new_start, new_finish);//如果发生异常，析构移动的元素，释放新空间  
              data_allocator::deallocate(new_start, new_size);  
          }//析构并释放原空间  
          destroy(begin(), end());  
          deallocator();  
          start = new_start; //调整迭代器  
          finish = new_finish;  
          end_of_storage = new_start + new_size;//调整迭代器  
      }  
  }  
```

补充：

```cpp
template<class BidirectionalIterator1, class BidirectionalIterator2>
  BidirectionalIterator2 copy_backward ( BidirectionalIterator1 first,
                                         BidirectionalIterator1 last,
                                         BidirectionalIterator2 result);

 参数:

       first, last
       指出被复制的元素的区间范围[first，last).
       result
       指出复制到目标区间的具体位置[result-(last-first),result)

 返回值：

        返回一个迭代器，指出已被复制元素区间的起始位置
```

所谓动态增加大小，**并不是在原空间之后接续空间（因为无法包装原空间之后尚有可配置的空间），而是以原大小的两倍另外配置一块较大的空间**，然后将原来内容拷贝过来，然后才开始在原内容之后构造新元素，并释放原空间。因此对vector的任何操作，一旦引起空间重新配置，指向原vector的所有迭代器就都失效了。

# vector的元素操作

pop_back()实现：

```cpp
void pop_back(){
      --finish;            //将尾端标记往前移一格，表示放弃尾端元素
      destory(finish);     //finish原来指向容器尾部[strat,finish),--后指向最后一个元素，然后析构
  }
```

erase()实现：

```cpp
 //清除[first,last]中的所有元素
  iterator erase(iterator first,iterator last){
      iterator i=copy(last,finish,first);
      destroy(i,finish);
      finish=finish-(last-first);
  }
  //清除某个位置上的元素
  iterator erase(iterator position){
      if(position+1!=end())
          copoy(position+1,finish,position);
      --finish;
      destory(finish);
      return position;
  }
  //清除所有元素
  void clear() {erase(begin(),end());}
```

copy函数具体实现：

```cpp
//InputIterator 版本
template<class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag){
//如果只是 InputIterator 的话，以迭代器赞同与否，决定循环是否继续、速度慢
for( ; first != last; ++result, ++first)
*result = *first;
return result;
}
即

for( ; last != finish; ++first, ++last)
*first = *last;  //即将last开始的元素接到first后面
```

insert()实现，根据备用空间和插入元素的多少分为以下三种情况：

```cpp
template <class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const T& x) {
  // 当 n != 0 才进行以下所有操作
  if (n != 0) {
    // 备用空间大于等于新增元素个数
    if (size_type(end_of_storage - finish) >= n) {
      T x_copy = x;
      const size_type elems_after = finish - position;
      iterator old_finish = finish;
      // 针对插入点后现有元素与新增元素个数的数量采取不同的操作
      // 插入点后现有元素个数大于新增元素个数
      if (elems_after > n) {
        uninitialized_copy(finish - n, finish, finish);
        finish += n;
        copy_backward(position, old_finish - n, old_finish);
        fill(position, position + n, x_copy);
      }
      // 插入点后现有元素个数小于等于新增元素个数
      else {
        uninitialized_fill_n(finish, n - elems_after, x_copy);
        finish += n - elems_after;
        uninitialized_copy(position, old_finish, finish);
        finish += elems_after;
        fill(position, old_finish, x_copy);
      }
    }
    else {
      // 备用空间小于新增元素个数（必须配置额外的内存）
      // 首先决定新长度：旧长度的2倍，或者旧长度+新增元素个数
      const size_type old_size = size();        
      const size_type len = old_size + max(old_size, n);
      // 配置新的 vector 空间
      iterator new_start = data_allocator::allocate(len);
      iterator new_finish = new_start;
      __STL_TRY {
        new_finish = uninitialized_copy(start, position, new_start);
        new_finish = uninitialized_fill_n(new_finish, n, x);
        new_finish = uninitialized_copy(position, finish, new_finish);
      }
#         ifdef  __STL_USE_EXCEPTIONS 
      catch(...) {
        // 如有异常发生，实现 commit or rollback 语义
        destroy(new_start, new_finish);
        data_allocator::deallocate(new_start, len);
        throw;
      }
#         endif /* __STL_USE_EXCEPTIONS */
      // 清除并释放旧的 vector
      destroy(start, finish);
      deallocate();
      // 调整迭代器
      start = new_start;
      finish = new_finish;
      end_of_storage = new_start + len;
    }
  }
}
```

![insert-1](/_images/book-note/stlsource/insert-1.png)

![insert-2](/_images/book-note/stlsource/insert-2.png)

![insert-3](/_images/book-note/stlsource/insert-3.png)