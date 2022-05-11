# C++智能指针——shared_ptr的使用

## 智能指针介绍

在C++中，动态内存的管理是通过成对运算符new和delete来完成的。new在动态内存中为对象分配空间并返回一个指向该对象的指针，可以选择对对象进行初始化; delete接受一个动态对象的指针，销毁该对象，并释放与之关联的内存。因为动态内存的申请和释放都是由程序员自己管理的，容易导致堆内存泄露（忘记释放），二次释放，程序发生异常时内存泄露等问题。

因此，引入了智能指针的概念，`通过智能指针来管理，析构的时候会自动释放其内存`。

C++11标准库提供了三种智能指针(smart pointer)类型来管理动态对象，包含在头文件<memory>中，`shared_ptr、weak_ptr和unique_ptr`（auto_ptr或已废弃）。

* shared_ptr控制对象的生命期。允许多个指针指向同一个对象,每使用它一次，引用计数+1，即强引用；

* weak_ptr不控制对象的生命期。它也是一个引用计数型智能指针，但是它不增加对象的引用计数，即弱引用。但是它知道对象是否还活着。如果对象还活着，那么它可以提升为有效的shared_ptr；如果对象已经死了，提升会失败，返回一个空的shared_ptr。即 weak_ptr只是提供了对管理对象的一个访问手段；

* unique_ptr则"独占"所指向的对象。与所指对象的内存紧密地绑定,不能与其他的unique_ptr类型的指针对象共享所指向对象的内存。

可以从以下三个方面理解智能指针: 

1. 从较浅的层面看，智能指针是利用了一种叫做RAII（资源获取即初始化）的技术对普通的指针进行封装，这使得智能指针实质是一个对象，行为表现的却像一个指针。
2. 智能指针的作用是防止忘记调用delete释放内存和程序异常的进入catch块忘记释放内存。另外指针的释放时机也是非常有考究的，多次释放同一个指针会造成程序崩溃，这些都可以通过智能指针来解决。
3. 智能指针还有一个作用是把值语义转换成引用语义。

```
Animal a;

Animal b = a;

这里是生成了两个对象。
```

## shared_ptr的使用

shared_ptr多个指针指向相同的对象。shared_ptr使用引用计数，每一个shared_ptr的拷贝都指向相同的内存。每使用他一次，内部的引用计数加1，每析构一次，内部的引用计数减1，减为0时，自动删除所指向的堆内存。shared_ptr内部的引用计数是线程安全的，但是对象的读取需要加锁。

注意事项: 

* 初始化。智能指针是一个模板类，可以指定类型，传入的指针通过构造函数进行初始化。也可以使用make_shared函数初始化。`不能将指针直接赋值给一个智能指针，因为一个是类，一个是指针`。例如std::shared_ptr<int> p = new int(1);的写法是错误的
* 拷贝和赋值。拷贝使得对象的引用计数增加1，赋值使得原对象引用计数减1，当计数为0时，自动释放内存。后来指向的对象引用计数加1，指向后来的对象。
* 通过get函数获取原始指针（raw pointer）。
* 注意不要用一个原始指针初始化多个shared_ptr，否则会造成二次释放同一内存空间。
* 注意避免循环引用，shared_ptr的一个最大的陷阱是循环引用，循环，循环引用会导致堆内存无法正确释放，导致内存泄漏。循环引用在weak_ptr中介绍。

以下是share_ptr支持的一些函数操作: 

![智能指针](/_images/c++/smart-ptr.png)

![share_ptr](/_images/c++/share-ptr.png)

下面举例来说明share_ptr的函数使用方法: 

[main.cpp](./src/share_ptrUse/main.cpp)

```c++
#include <iostream>
#include <memory>

using namespace std;

class Test
{
public:
    Test(string s)
	:str(s)
    {
       cout<<"Test() create str: "<<str<<endl;
    }
    ~Test()
    {
        cout<<"~Test() delete str: "<<str<<endl;
    }
    string& getStr()
    {
        return str;
    }
    void setStr(const string& s)
    {
        str = s;
    }
    void print()
    {
        cout<<"str: "<<str<<endl;
    }
private:
    string str;
};

int main()
{
    shared_ptr<Test> ptest(new Test("123"));
    shared_ptr<Test> ptest2(new Test("456"));
	shared_ptr<Test> ptest3 = make_shared<Test>("789");
	
    cout<<"ptest2->getStr():"<<ptest2->getStr()<<endl;
    cout<<"ptest2.use_count():"<<ptest2.use_count()<<endl;
	
    ptest = ptest2;//“123”引用计数减1,计数为0自动销毁; "456"引用次数加1. (p=q的规则，p,q都为share_ptr)
    ptest->print();
	
    cout<<"ptest2.use_count():"<<ptest2.use_count()<<endl;//2
    cout<<"ptest.use_count():"<<ptest.use_count()<<endl;//2
	
	Test* mtest = ptest.get();
	mtest->print();
	
    ptest.reset();
    ptest2.reset();//此时“456”销毁
	
	cout<<"ptest3.unique():"<<boolalpha<<ptest3.unique()<<endl;
	shared_ptr<Test> ptest4(ptest3);
	cout<<"ptest3.unique():"<<boolalpha<<ptest3.unique()<<endl;
	ptest3.reset();
	ptest4.reset();
	
    cout<<"done !"<<endl;
    return 0;
}
```

执行结果:
``` 
[root@192 智能指针学习]# ./main
Test() create str: 123
Test() create str: 456
Test() create str: 789
ptest2->getStr():456
ptest2.use_count():1
~Test() delete str: 123
str: 456
ptest2.use_count():2
ptest.use_count():2
str: 456
~Test() delete str: 456
ptest3.unique():true
ptest3.unique():false
~Test() delete str: 789
done !
```