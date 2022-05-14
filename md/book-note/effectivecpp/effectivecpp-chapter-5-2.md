# 第五章：实现（二）

[[toc]]

# 为“异常安全”而努力是值得的

```cpp
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    lock(&mutex);
    delete bgImage;
    ++imageChanges;
    bgImage = new Image(imgSrc);
    unlock(&mutex);
}
```

上述函数未满足异常安全的两个条件:

1. 不泄露任何资源；//new Image(imgSrc)抛出异常时，unlock操作无法执行，导致互斥锁被一直占用
2. 不允许数据败坏。//new Image(imgSrc)抛出异常,imageChanges已经累加，但是bgImage没有指向新的图像

改进，利用资源管理类保证资源被释放：

```cpp
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    Lock ml(&mutex);
    delete bgImage;
    ++imageChanges;
    bgImage = new Image(imgSrc);
}
```

**异常安全函数**提供以下三个保证之一：

* 基本承诺：如果异常被抛出，程序内的任何事物仍然保持在有效状态下。没有任何对象或数据结构会因此而败坏，所有对象都处于一种内部前后一致的状态。
* 强烈保证：如果异常被抛出，程序状态不改变。如果函数成功，就是完全成功；如果函数失败，程序会回复到“调用函数之前”的状态。往往能够以copy and swap实现。
* 不抛掷（nothrow）保证：承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能。作用于内置类型身上的所有操作都提供了nothrow保证。

```cpp
struct PMImpl
{
    std::tr1::shared_ptr<Image> bgImage;
    imageChanges;
};

class PrettyMenu
{
 private:
    Mutex mutex;
    std::tr1::shared_ptr<PMImpl> pImpl;
}

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    using std::swap; //不抛异常的swap函数
    Lock ml(&mutex);
    std::tr1::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));//拷贝对象的副本
    pNew->bgImage.reset(new Image(imgSrc));
    ++pNew->imageChanges;

    swap(pImpl,pNew);// 置换数据，释放mutex
    
}
```

# 透彻了解inlining的里里外外

平均而言一个程序往往将80%的执行时间花费在20%的代码上头，因此软件开发者需要找出有效增进程序整体效率的20%代码，然后将它inline或竭尽所能地将它瘦身。

inline的观念是将“对此函数的每一个调用”都以函数本体替换之。所以大多数inlining限制在小型且被频繁调用的函数身上。

# 将文件间的编译依存关系降至最低

```cpp
class Person
{
public:
    Person(const std::string& name, const Date& birthday ,const Address& addr);
    std::string name() const;
    std::string birthDay() const;
    std::string address() const;
private:
    std::string theName;      //实现细目
    Date        theBirthDay;  //实现细目
    Address     theAddress;   //实现细目
}
```

上述定义必须包含头文件

```cpp
#include<string>
#include"date.h"
#include"address.h"
```

Person定义文件和其含入文件之间形成了一种编译依存关系。如果这些头文件有任何一个被改变，或这些头文件所依赖的其他头文件有任何改变，那么每一个含入Person class的文件就得重新编译，任何使用Person class的文件也必须重新编译。

改进:

```cpp
#include<string>
#include<memory>

class PersonImpl; //Person实现类的前置声明
class Date;       //Person接口用到的class类的前置声明
class Address;

class Person
{
public:
    Person(const std::string& name, const Date& birthday ,const Address& addr);
    std::string name() const;
    std::string birthDay() const;
    std::string address() const;
private:
    std::tr1::shared_ptr<PersonImpl>   pImpl;//指针物，指向实现
    
}
```

Person类内只含有一个指针成员，指向其实现类。这般设计常被称为pimpl idiom(pointer to implementation).

改进的设计，使得Person的客户与Date，Address以及Person的实现细目分离了。那些class的任何实现修改都不需要Person客户端重新编译。

分离的关键：**以“声明的依存性”替换“定义的依存性”，这正是编译依存性最小化的本质。**

设计策略：

1. 如果使用object references 或 object pointers可以完成任务，就不要使用objects。
2. 如果能够，尽量以class声明式替换class定义式。
3. 为声明式和定义式提供不同的头文件。

Date的客户如果希望声明today和clearAppointments,应该这样写:

```cpp
#include"datefwd.h"
Date today();
void clearAppointments(Date d);
```

Person两个成员函数的实现：

```cpp
#include"Person.h" //include Person的定义式
#include"PersonImpl.h" //include PersonImpl的定义式,PersonImpl和Person有着完全相同的成员函数，两者接口完全相同

 Person(const std::string& name, const Date& birthday ,const Address& addr)
:pImpl(new PersonImpl(name,birthday,addr )) 
{}

std::string Person::name() const
{
    return pImpl->name();
}
```

注意事项：

1. 支持“编译依存性最小化”的一般构想是：相依于 声明式，不要相依于定义式。基于此构想的两个手段是Handle classes 和Interface classes。

2. 程序库头文件应该以“完全且仅有声明式”的形式存在。

​