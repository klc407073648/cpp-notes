# 第13章 拷贝控制

拷贝控制操作：拷贝构造函数、拷贝赋值运算符、移动构造函数、移动赋值运算符和析构函数。

## 拷贝构造函数

拷贝初始化和直接初始化？

常见容器的insert和push操作，**容器会对其元素进行拷贝初始化（创建局部临时对象，将其压入容器中）；用emplace操作创建的元素是直接初始化（在容器管理的内存空间中直接创建对象）**

拷贝构造函数：与合成默认构造函数不同，即使定义了其他构造函数，**编译器也会合成一个拷贝构造函数**。
```cpp
Object(const Object& obj)
{}
```

说明：形参加上&，为了防止无限的构造，形成死递归。

浅拷贝导致重复析构和内存泄漏，含有指针的成员数据，应该采用深拷贝。

重复析构：指针A和指针B指向同一内容，对象B释放指针B后，实际上对应内存已经被释放了，这时，对象A析构时，就会重复析构。
内存泄漏：本来对象A,B单独创建，然后将对象B赋值给A时，导致指针A和指针B指向同一内容，实际上A原先的指针所指向的内容永远得不到释放。

https://blog.csdn.net/m0_54355780/article/details/122474441

采用深拷贝，通过malloc和memcpy的方式拷贝原先指针的内容，而不是简单粗暴地将两个指针相等。

## 拷贝赋值运算符

与拷贝构造函数一样，如果类未定义自己的拷贝赋值运算符，编译器会为它合成一个。

```
Object& operator=(const Object& obj)
{}
```

## 析构函数

析构函数没有返回值，也不接受参数。由于析构函数不接受参数，因此它不能被重载。

在一个构造函数中，成员的初始化是在函数体执行之前完成的，且按照它们在类中出现的顺序进行初始化(**函数体内的都是赋值操作**)。一个析构函数中，**首先执行函数体，然后销毁成员**。成员按照初始化顺序的逆序销毁。

一般而言，一个类不需要自己定义析构函数，编译器会为它定义一个合成析构函数。**如果一个类需要自定义析构函数，它肯定也需要定义拷贝赋值运算符和拷贝构造函数**（例如类成员有指针的场景，需要使用深拷贝来拷贝指针，避免多次析构指向同一个地址的指针）。

**使用=defalut显示地要求编译器生成合成的版本**，与此对应的**使用=delete表明希望它定义为删除的**

C++中声明虚函数但不实现是合法的。虚函数可以在基类中声明，然后在派生类中进行具体的实现。如果你只想在基类中声明虚函数，并且不需要为其提供默认的实现，那么你可以将其声明为纯虚函数。纯虚函数使用 "= 0" 来表示，它要求派生类必须提供自己的实现。一个类中包含了一个或多个纯虚函数的时候，这个类就成为抽象类，它不能被实例化，只能用来作为其他子类的基类。

## 类值拷贝赋值运算符

通过先拷贝右侧运算对象，可以处理自赋值情况，并能保证在异常发生时代码也是安全的。在完成拷贝后，释放左侧运算对象的资源，并更新指针指向新分配的string。

```cpp
HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    auto newp = new string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
}
```

## 交换操作

swap的存在就是为了优化代码，因此将其定义为inline函数。如果存在类型特定的swap版本，其匹配程度会优于std中定义的版本。

在赋值运算符中使用swap，拷贝并交换的技术。这种技术将左侧运算对象与右侧运算对象的一个副本进行交换。

```cpp
HasPtr& HasPtr::operator=(HasPtr rhs)
{
    swap(*this,rhs); //rhs指向原对象所使用的内存
    return *this;   //rhs被销毁，自动delete的原对象中的指针
}
```

## 对象移动

新标准中的一个特性：可以移动而非拷贝对象的能力。右值引用指向要被销毁的对象。

int &&r = std::move(i)

## 移动构造函数和移动赋值运算符

从给定对象“窃取”资源而不是拷贝资源。

不抛出异常的移动移动构造函数和移动赋值运算符必须标记为 noexcept。 与拷贝操作不同，编译器根本不会为某些类合成移动操作。

只有当一个类没有定义任何自己版本的拷贝控制成员，且它的所有数据成员都能移动构造或移动赋值时，编译器才会为它合成移动构造函数或移动赋值运算符。

区别移动和拷贝的重载函数通常有一个版本接受一个const T&，而另一个版本接受一个T&&

```cpp
void push_back(const std::string&); //拷贝元素
void push_back(std::string&&);      //移动元素

std::string str = "hello";
vec.push_back(str);    // 调用push_back(const std::string&)
vec.push_back("done"); // 调用push_back(std::string&&)
```

## 引用限定符

引用限定符可以是&或&&，分别指出this可以指向一个左值或右值。类似const限定符，引用限定符只能用于（非static）成员函数，且必须同时出现在函数的声明和定义中。

```cpp
Foo sorted() &&;        //可用于可改变的右值
Foo sorted() const &;   //可用于任何类型的Foo
```

# 第16章 模板与泛型编程

模板是C++中泛型编程的基础，一个模板就是一个创建类或函数的蓝图或者说公式。

## 编写类型无关的代码

编写泛型代码的两个重要原则：

* 模板中的函数参数是const的引用。
* 函数体中的条件判断仅使用<比较运算。
    * 降低了对compare函数要处理类型的要求，仅需要支持<,但不需要支持>。

## 模板编译

当编译器遇到一个模板定义时，它并不生成代码。只有我们实例化出模板的一个特定版本时，编译器才会生成代码。

一般情况，当我们调用一个函数时，编译器只需要掌握函数的声明。当我们使用一个类类型的对象时，类的定义必须可用，但是成员函数的定义不一定已经出现。因此，我们把类的定义和函数声明放在头文件，普通函数和类的成员函数放在源文件中。

但是对于模板来说，为了生成一个实例化版本，**编译器需要掌握函数模板或类模板成员函数的定义**，因此，我们也将模板的定义放在头文件里面。

函数模板可以用来生成针对特定类型的函数版本。

## 类模板

类模板是用来生成类的蓝图的。但是与函数模板不同之处是 ，编译器不能为类模板推断模板参数类型。

**对应一个实例化的类模板，其成员函数只有在使用时才被实例化**

**当希望通知编译器一个名字表示类型时，必须使用关键字typename，而不能使用class**

```cpp
typename T::value_type top(const T&)
```

## 控制实例化

**当模板被使用时才能进行实例化，相同的实例可能出现在多个对象文件中。**当两个或多个独立编译的源文件使用了相同的模板，并提供了相同的模板参数时，每个文件中都会有该模板的一个实例。

在新标准中，可以通过显示实例化来避免这种开销。

```cpp
extern template declaration;
template declaration;
```

# 第17章 标准库特殊设施

## tuple类型

当希望将一些数据组合成单一对象，但又不想麻烦地定义一个新数据结构来表示这些数据时，tuple是非常适合的。其最常见的用途就是从一个函数返回多个值。

## bitset

bitset使得位运算的使用更为容易。

## 使用正则表达式regex

```cpp
#include <regex>
#include <iostream>
#include <string>

int main() {
    std::string target = "@abc def--";
    std::regex e("(\\w+)\\W+(\\w+)");//\\w 单词字符（字母数字下划线），\W非单词字符。
    std::smatch sm; 
    std::regex_search(target, sm, e); 

    std::cout << "sm.prefix: " << sm.prefix() << std::endl;
    for (int i = 0; i < sm.size(); ++i) {
        std::cout << "sm[" << i << "]: " << sm[i] << std::endl;
    }   
    std::cout << "sm.suffix: " << sm.suffix() << std::endl;

    return 0;
}
```

# 第18章 用于大型程序的工具

## 异常处理

异常处理机制允许程序中独立开发的部分能够在运行时就出现的问题进行通信并做出相应的处理。在C++语言中，通过抛出(throwing)一条表达式来引发(raised)一个异常。被抛出的表达式类型以及当前的调用链共同决定了哪段处理代码(handler)将被用来处理该异常。

throw之后的处理机制

* 沿着调用链的函数可能会提早退出。
* 一旦程序开始执行异常处理代码，则沿着调用链创建的对象将被销毁。

栈展开过程沿着嵌套函数的调用链不断查找，直到找到匹配的catch或主程序终止。

重新抛出，catch语句中处理后向外层再次抛出异常。

## noexcept异常说明

C++11通过提供noexcept说明指定某个函数不会抛出异常。对于一个函数来说，noexcept说明要么出现在该函数的所有声明语句和定义语句中，要么一次也不出现。

**违反异常说明**：一旦一个noexcept函数抛出了异常，程序就会调用terminate以确保遵守不在运行时抛出异常的承诺。因此，noexcept适用场景：1、确认函数不会抛出异常；2、根本不知道异常应该如何处理。

## 异常类层次

异常类包括： exception，以及对应的子类bad_cast、runtime_error、logic_error和bad_alloc

补图 783

## 命名空间

命名空间：为防止名字冲突提供了更加可控的机制。多个库将名字放置在全局命名空间中将引发命名空间污染。

每一个命名空间都是一个作用域。
命名空间可以是不连续的，分别定义在多个文件中。

全局命名空间，表示形式 ::member name 

未命名的命名空间：指关键字namespace 后紧跟花括号括起来的一系列声明语句。

命名空间的别名

namespace cplusplus_primer  ——>  namespace primer = cplusplus_primer 

## using声明和using指示

using声明一次之引入命名空间中的一个成员。

using指示使得某个特定的命名空间中所有的名字都可见。

## 头文件与using声明或指示

头文件如果在其顶层作用域中含有using指示或using声明，则会将名字注入到所有包含了该头文件的文件中。通常情况下，头文件应该只负责定义接口部分的名字，而不定义实现部分的名字。因此，**头文件最多只能在它的函数或命名空间内使用using指示或using声明。**


对命名空间内部名字的查找遵循常规的查找规则：由内向外依次查找每个外层作用域。外层作用域也可能是一个或多个嵌套的命名空间，直到最外层的全局命名空间查找过程终止。

## 重载与using声明

一个using声明包括了重载函数的所有版本以确保不违反命名空间的接口。

`using NS::print`

关键字 final 表示不能被继承

# 特殊工具与技术

## 重载 new 和  delete

new: 分配内存；构造对象；返回指针
delete: 销毁对象；释放内存

## 运行时类型识别

运行时类型识别（run-time type identification, RTTI）

* typeid 运算符，用于返回表达式的类型
* dynamic_cast 运算符，用基类指针或引用安全地转换成派生类的指针或引用

类型含有**虚函数**时，运算符将使用指针或引用所绑定对象的动态类型。

```cpp
if(Derived *dp = dynamic_cast<Derived*>(bp)){
    // 使用dp指向的 Derived 对象
}
else{
    // 使用bp指向的 Base 对象
}
```

```cpp
if(typeid(*bp) == typeid(*dp)){
    //bp 和 dp指向同一类型对象
}

if(typeid(*bp) == typeid(Derived)){
    //bp 实际指向Derived对象
}

if(typeid(bp) == typeid(Derived)){
    //永远不被指向，bp是指向Base的指针
}

```

## type_info类

```cpp
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual void print() {}
};

class Derived : public Base {
public:
    virtual void print() {}
};

int main() {
    Base* basePtr = new Derived();
    
    // 使用typeid运算符获取类型信息
    const std::type_info& type = typeid(*basePtr);
    
    // 输出类型的名称
    std::cout << "Type name: " << type.name() << std::endl;
    
    // 比较类型
    if (type == typeid(Base)) {
        std::cout << "Type is Base" << std::endl;
    } else if (type == typeid(Derived)) {
        std::cout << "Type is Derived" << std::endl;
    } else {
        std::cout << "Type is unknown" << std::endl;
    }
    
    delete basePtr;
    
    return 0;
}
```

```
Type name: class Derived
Type is Derived
```

## 枚举类型

C++ 包含两种枚举：限定作用域和不限定作用域

```cpp
enum class open_modes {input,output,append};//限定作用域
int i = open_modes::input;//限定作用域的枚举类型不会进行隐式转换

enum color {red,yellow,green};//不限定作用域
int j = color::red;//不限定作用域的枚举类型的枚举成员隐式转换成int
```