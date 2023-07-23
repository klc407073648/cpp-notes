# 第一章 - 关于对象

[[toc]]

# 什么是C++对象模型

有两个概念可以解释C++对象模型:

1. 语言中直接支持面向对象程序设计的部分
2. 对于各种支持的**底层实现机制**

C++对象模型的第一个概念是一种“不变量"。例如，C++ class的完整virtual functions在编译时期就固定下来了，程序员没有办法在**执行期动态增加或取代其中某一个**。这使得虚拟调用操作得以有快速的派送（dispatch）结果，付出的成本则是执行期的弹性。

目前所有编译器对于virtual function的实现法都是使用各个class专属的virtual table，大小固定，并且在程序执行前就构造好了。

C++ 第一套编译器cfront

原文名词

::: details
![](/_images/book-note/objectModel/原文名词1.png)

![](/_images/book-note/objectModel/原文名词2.png)

![](/_images/book-note/objectModel/原文名词3.png)
:::

OMG和Microsoft分别提出CORBA(Common Obect Request Breaker Architecture) 和 COM(Component Object Model)标准，
CORBA模型主要应用于UNIX操作系统平台上，而COM则主要应用于Microsof tWindows操作系统平台上。

SOM（System Object Model）

# 概述

在c语言中，“数据"和“处理数据的操作（函数）”是分开来声明的，即语言本身并没有支持“数据和函数"之间的关联性。我们把这种程序方法称为**程序性**的（procedural）。

struct结构体里一般只定义数据类型，或构造函数？ TODO

[C++ 基础 - 宏函数、内联函数、普通函数](/md/c++/basic/c++-basic-function.md)

操作符重载一般也是inline 

## 加上封装后的布局成本(Layout Costs for Adding Encapsulation)

data members直接内含在每一个class object之中，就像C strct的情况一样，而member functions虽然含在class的声明之内，却不出现在object之中，每一个non-inline member function只会诞生一个函数实体，至于每一个"拥有零个或一个定义"的inline function 则会在其每一个使用者（模块）身上产生一个函数实体。

C++在布局以及存取时间上主要的额外负担是由**virtual引起**，包括：

* virtual function机制用以支持一个有效率的“执行期绑定"(runtime binding)。
* virtual base class 用以实现“多次出现在继承体系中的 base class，有一个单一而被共享的实体。

此外，还有一些多重继承下的额外负担，发生在"一个derived class和其第二或后继之baseclass的转换"之间。然而，一般言之，并没有什么天生的理由说C++程序一定比其c兄弟庞大或迟缓。

# C++ 对象模式

在C++中，有两种class data members：static和nonstatic，以及三种class member functions：static、和virtual。已知下面这个class Point声明:

```
class Point{
    public:
        Point(float xval);
        virtual ~Point();

        float x() const;
        static int PointCount();
    protected:
        virtual ostream& print(ostream &os) const;

        float _x;
        static int _point_count; 
}
```

## 简单对象模型(A Simple Object Model)

![](/_images/book-note/objectModel/简单对象模型.png)

第一个模型十分简单，它可能是为了尽量减低C++编译器的设计复杂度而开发出来的，赔上的则是空间和执行期的效率。在这个简单模型中，一个object是一系列的slots，每一个slot指向一个members。Members按其声明顺序，各被指定一个slot。每一个data member或function member都有自己的一个slot。

在这个简单模型中，members本身并不放在object之中，只有“指向member的指针”才放在object内。这么做可以避免“members有不同的类型，因而需要不同的存储空间”所招致的问题。

虽然这个模型并没有被应用于实际产品上，**不过关于索引或slot数目的观念，倒是被应用到C++的“指向成员的指针"（pointer-to-member）观念之中**。

## 表格驱动对象模型(A Table-driven Object Model)

为了对所有classes的所有objects都有一致的表达方式，另一种对象模型是把所有与members相关的信息抽出来，放在一个data member table和一个member function table之中，class obJect本身则内含指向这两个表格的指针，Member function table是一系列的slots，每一个slot指出一个member function：Data member table则直接含有data本身。

![](/_images/book-note/objectModel/表格驱动对象模型.png)

虽然这个模型也没有实际应用于真正的C++编译器身上，但member functio ntable这个观念却成为支持virtual functions的一个有效方案。

## C++对象模型(The C++ Object Model)

Stroustrup当初设计（当前亦仍占有优势）的C++对象模型是从简单对象模型派生而来的，并对内存空间和存取时间做了优化。在此模型中，Non static data members被配置于每一个class obJect之内，static data members则被存放在所有的class object之外，Static 和 nonstatic function members也被放在所有的class object之外。

Virtual functions则以两个步骤支持之：

1. 每一个class产生出一堆指向 virtual functions 的指针，放在表格之中．这个表格被称为 virtual table(vtbl)。

2. 每一个 class object 被安插了一个指针，指向相关的virtual table。通常这个指针被称为vptr。vptr的设定(setting)和重置（resetting)都由每一个class的constructor、destructor 和 copy assignment 运算符自动完成。每一个class所关联的 type_info object (用以支持 runtime type identification,RTTI) 也经由virtual table被指出来，通常是放在表格的第一个slot处。

vtbl属于类，vptr属于类对象。

![](/_images/book-note/objectModel/C++对象模型.png)

这个模型的主要优点在于它的空间和存取时间的效率；主要缺点则是，如果应用程序代码本身未曾改变，但所用到的class objects的nonstatic data members有所修改（可能是增加、移除或更改），那么那些应用程序代码同样得重新编译，关于这点，前述的双表格模型就提供了较大的弹性，因为它多提供了一层间接性，不过它也因此付出空间和执行效率两方面的代价就是了。

### 加上继承

```
class istream : virtual public ios {...};
class ostream : virtual public ios {...};
class iostream : public istream,ostream {...};
```
在虚拟继承的情况下，base class不管在继承串链中被派生（derived）多少次，永远只会存在一个实体（称为sub object）。例如，iostream 之中就只有virtual ios base class的一个实体。

# 关键词所带来的差异(A Keyword Distinction)

**如果不是为了努力维护与C之间的兼容性，C++远可以比现在更简单。**

什么时候一个人应该使用struct取代class? ————> 当它让一个人感觉比较好的时候。

```
//继承方式
struct C_point {...};
class Point : public C_point {...};

//组合方式
class Point {
    public:
        operator C_point() { return _c_point; }
        ...
    private:
        C_point _c_point;
}
```

组合而非继承，才是把C和C++结合在一起的唯一可行方法。

# 对象的差异(An Object Distinction)

C++程序设计模型直接支持三种programming paradigms（程序设计典范）：


paradigm 含义

```
一种环境设计和方法论的模型或范例：系统和软件以此模型来开发和运行。一个现役的典范可能会有数个开发中的替代典范。以下是一些大家比较熟悉的典范：函数化程序设计、逻辑程序设计、语意数据模型、几何计算、数值计算、面向对象设计、原型设计、自然语言。
```

1. 程序模型（procedural model)，就像C一样，C++当然也支持它。字符串的处理就是一个例子。
2. 抽象数据类型模型(abstract datatype model,ADT)。该模型所谓的“抽象”是和一组表达式（public接口）一起提供，而其运算定义仍然隐而未明，例如string class。

```cpp
string addr = "nanjing";
string city;

// string::operator=()
city = addr;
// string::operator==()
if( city == addr)
```

3. 面向对象模型(object-oriented model)。在此模型中有一些彼此相关的类型，通过一个抽象的base class（用以提供共通接口）被封装起来。

```cpp
void check_in(Library_materials *pmat)
{
    if( pmat->late() )
        pmat->fine()
    pmat—>check_in()；

    if( Lender *plend=pmat->reserved() )
        pmat—>notify(plend);
    ...
}
```

纯粹一种paradigm写程序，有助于整体行为的良好稳固。然而如果混合了不同的paradigms，就可能会带来让人惊吓的后果，特别是在没有谨慎处理的情况下。最常见的疏忽发生在当你以一个base class的具体实体如：

`Library_materials thing1`

来完成某种多态(polymorphism)局面时：

```cpp
Library_materials thing1;
Book book;

thing1 = book;

thing1.check_in();//调用Library_materials::check_in()

//应该多使用
Library_materials &thing2 = book;

thing2.check_in();//调用Book::check_in()
```

虽然你可以直接或间接处理继承体系中的一个base class object，但只有通过**pointer或reference的间接处理**，才支持OO程序设计所需的多态性质。

C++以下列方法支持多态：

1. 经由一组隐含的转化操作，例如把一个 derived class 指针转化为一个指向其public base type的指针：

`shape *ps= new circle();`

2. 经由virtual function机制：

`ps->rotate();`

3. 经由 dynamic_cast 和 typeid 运算符、

`if(circle *pc = dynamic_cast<circie*>(ps) ) ...`

多态的主要用途是**经由一个共同的接口来影响类型的封装**，这个接口通常被定义在一个抽象的base class中。当派生类型有所增加、修改、或删减时，我们的程序代码不需改变，只需要派生类实现基类的接口即可。

**需要多少内存才能够表现一个class object?**

一般而言要有：

* 其nonstatic data members的总和大小：
* 加上任何由于alignment的需求而填补上去的空间
* 加上为了支持 virtual 而由内部产生的任何额外负担（overhead）

# 指针的类型(The Type of a Pointer)

一个指针，不管它指向哪一种数据类型，指针本身所需的大小是固定的。

```cpp
class ZooAnimal{
    public:
        ZooAnimal();
        virtual ~ZooAnimal();
        // ...
        virtual void rotate();
    protected:
        int loc;
        String name;
}
```

![](/_images/book-note/objectModel/ZooAnimal.png)

## 加上多态之后(Adding Polymorphism)

```cpp
class Bear : public ZooAnimal{
    public:
        Bear();
        ~Bear();
        // ...
        void rotate();
        virtual void dance();
    protected:
        enum Dances { ... }

        Dances dances_known;
        int cell_block;
}
```

![](/_images/book-note/objectModel/Bear.png)


```cpp
Bear b;
ZooAnimal *pz = &b;
Bear *pb = &b;
```

除了 ZooAnimal subobject中出现的members，你不能够使用来直接处理Bear的任何members。唯一例外是通过virtual机制:

```cpp
//不合法：cell_block不是ZooAnimal的一个member，
//虽然我们知道 pz 当前指向一个 Bear object
pz->cell_block,
//ok：经过一个明白的downcast操作就没有问题！
((Bear*)pz)->cell_block;
//下面这样更好，但它是一个run-time operation 
if( Bear* pb2 = dynamic_cast<Bear*>(pz) )
    pb2->cell_block
//ok：因为cell_block是Bear的一个member.
pb->cell_block;
```

# 总结

<font color='red'>**重要：**</font>

* 当一个base class object被直接初始化为（或是被指定为）一个 derived class object时，derived object 就会被**切割（sliced）**以塞人较小的base type内存中, 多态不再呈现。

* 多态是一种威力强大的设计机制，允许你继一个抽象的public接口之后，封装相关的类型。需要付出的代价就是**额外的间接性**一不论是在“内存的获得"或是在“类型的决断"上。C++ 通过class的pointers和references来支持多态，这种程序设计风格就称为“面向对象"。

* C++也支持具体的ADT程序风格，如今被称为object-based(OB)。例如String class，一种非多态的数据类型，String class可以展示封装的非多态形式，它提供一个public接口和一个private实现品，包括数据和算法，但是不支持类型的扩充。**一个OB设计可能比一个对等的OO设计速度更快而且空间更紧凑**。速度快是因为所有的函数引发操作都在编译时期解析完成，对象建构起来时不需要设置 virtual 机制：空间紧凑则是因为每一个class object不需要负担传统上为了支持virtual机制而需要的额外负荷，不过，OB设计比较没有弹性。

* **在弹性(OO)和效率（OB）之间常常存在着取与舍。一个人在能够有效选择其一之前，必须先清楚了解两者的行为和应用领域的需求。**