# C++11特性 new

```cpp
template <class T, class U>
auto add(T t, U u)
{
  return t + u;
}

void autoAndDecltypeTest()
{
  auto a = 1 + 2;       // type of a is int
  auto b = add(1, 1.2); // type of b is double
  decltype(a) c = b;    // C++11
  // decltype(auto)c=a;//C++14
  std::cout << "a:" << a << std::endl;
  std::cout << "b:" << b << std::endl;
  std::cout << "c:" << c << std::endl;

  std::cout << std::boolalpha; // 使bool型变量按照false、true的格式输出

  std::cout << std::is_same<decltype(a), decltype(c)>::value << std::endl;
}
// 比较类型是否相同 //bool is_same_v=is_same<T, U>::value; Ce
// https://en.cppreference.com/w/cpp/types/is_same GCC 5.2(c++17) 和 GCC 12.1(c++17)区别
```

## = delete 

声明被删除的函数不能被调用;且需要首次定义时就删除

```cpp
struct sometype
{
    void* operator new(std::size_t) = delete;
    void* operator new[](std::size_t) = delete;
};
sometype* p = new sometype; // error: attempts to call deleted sometype::operator new


struct sometype { sometype(); };
sometype::sometype() = delete; // error: must be deleted on the first declaration
```
## = default

使用default显式告知编译器生成默认的缺省版本

```cpp
// All special member functions of `trivial` are
// defaulted on their first declarations respectively,
// they are not user-provided
struct trivial
{
    trivial() = default;
    trivial(const trivial&) = default;
    trivial(trivial&&) = default;
    trivial& operator=(const trivial&) = default;
    trivial& operator=(trivial&&) = default;
    ~trivial() = default;
};
 
struct nontrivial
{
    nontrivial(); // first declaration
};
 
// not defaulted on the first declaration,
// it is user-provided and is defined here
nontrivial::nontrivial() = default;
```

## final

一般用于中止派生

禁止重写

```cpp
class Super
{
  public:
    Super();
    virtual void fun() final;//final作用于虚函数，禁止子类重写
}
```

禁止继承

```cpp
class Super final
{
  ...
}
```

## 重载、重写、重定义

1. 重载:相同函数名称，不同参数序列(包括参数的个数不同或参数的类型不同，仅返回类型不同不能重载) 
   * 左值 和 右值 
   * const 很特殊 
      * 有时候能重载(fun(char *a)和fun(const char *a))，字符串变量和字符串常量 
      * 不能重载 (fun(inti)和fun(const int i))，都是形参; int &i 和 const int &i可以重载 

2. 重写:子类重新定义父类中有相同名称和参数的虚函数(参数列表必须相同);父类的方法被覆盖了。
   * 重写函数需要满足以下要求:
     1)在父类中必须被声明为virtual 
     2)有相同的类型，名称和参数列表
     3)访问修饰符可以不同，在父类是private时，在子类可以是public或者protected 

3. 重定义: 类重新定义父类中有相同名称的非虚函数(**参数列表可以不同**)，父类的方法就会被隐藏


## 右值引用(理解还是不深) 

* lvalue 译为"loactor value"，指的是存储在内存中、有明确存储地址(可寻址)的数据， 
* rvalue 译为"read value"，指的是那些可以提供数据值的数据(不一定可以寻址，例如存储于寄存器中的数据)。 

* C++编程技巧，分别为移动语义和完美转发。 

**std::move(没有新内存的申请和分配，在大量对象的系统中，移动构造相对与拷贝构造可以显著提高性能)**

## std::exchange

std::exchange:Replaces the value of obj with new_value and returns the old value of obj

```cpp
<utility>
template< class T, class u =T >
T exchange( T& obj, U&& new_value );
```

## std::quoted

```cpp
template< class CharT >
/*unspecified*/quoted( const CharT*s,CharT delim=CharT('*'), CharT escape= CharT(''));
```

## Move assignment operator 移动赋值

```cpp
struct A
{  
  std::string s;
  A():s("test") {}
  A(const A& o): s(o.s) { std::cout << "move failed!\n"; }
  A(A&& o):s(std::move(o.s)){}

  A& operator=(const A& other){
    s = other.s;
    std::cout << "copy assigned\n"; 
    return *this;
  }
}
```

## scoped enum

C++11 的枚举是“域化的” (scoped enum)，相比 C++98 枚举的“非域化” (unscoped enum)，具有如下优点：

* **命名空间污染** 

```cpp
enum Color { yellow, green, blue}; // yellow, green, blue are in same scope as Color
auto yellow = false; // error! yellow already declared in this scope
Color  c = yellow; // fine
```

C++11 枚举的关键字为 enum class，可视为一个 "class"，能防止“命名空间污染”

```cpp
enum class Color { yellow, green, blue}; // yellow, green, blue are scoped to Color
auto yellow = false; // fine, no other "yellow" in scope
Color c = yellow; // error! no enumerator named "yellow" is in this scope
Color c = Color::yellow; // fine
auto c = Color::yellow; // also fine
```

* **强类型枚举**

非域化的枚举成员，可以隐式的转换为广义整型 (integral types)，如下所示：

```cpp
enum Color { yellow, green, blue}; // unscoped enum
std::vector<std::size_t> primeFactors(std::size_t x); // func. returning prime factors of x
 
Color c = blue;
 
if (c < 14.5) // compare Color to double (!)
{
    auto factors = primeFactors(c); // compute prime factors of a Color (!)
    …
}
```

域化的枚举成员，**却不可以隐式的转换为广义整型**

```cpp
enum class Color { yellow, green, blue }; // enum is now scoped
 
Color c = Color::blue; // as before, but with scope qualifier
 
if (c < 14.5)  // error! can't compare Color and double
{
    auto factors = primeFactors(c); // error! can't pass Color to function expecting std::size_t
    …
}
```

正确的方式是使用 C++ 的类型转换符 (cast)

```cpp
if (static_cast<double>(c) < 14.5)     // odd code, but it's valid
{
    auto factors = primeFactors(static_cast<std::size_t>(c)); // suspect, but it compiles
    …
}
```

* **前置声明**

域化枚举支持前置声明 (forward-declared)，也即可以不用初始化枚举成员而声明一个枚举类型

`enum class Color;`

**新增枚举成员:**

非域化枚举(unscoped enum) 在声明时，编译器会选择占用内存最小的一种潜在类型 (underlying types)，来代表每一个枚举成员

```cpp
enum Color { black, white, red };  // compiler may choose char type
```

下面的例子中，编译器可能会选择更大的能够包含 0 ~ 0xFFFFFFFF 范围的潜在类型

```cpp
enum Status {
    good = ,
    failed = ,
    incomplete = ,
    corrupt = ,
    indeterminate = 0xFFFFFFFF
};
```

非前置声明的缺点在于，当新增一个枚举成员时 (如下例的 audited )，整个系统将会被重新编译一遍，即使只有一个很简单的函数使用了新的枚举成员 (audited)

```cpp
enum Status {
    good = ,
    failed = ,
    incomplete = ,
    corrupt = ,
    audited = ,
    indeterminate = 0xFFFFFFFF
};
```

而使用前置声明，当新增枚举成员时，包含这些声明的头文件并不需要重新编译，源文件则根据新枚举成员的使用情况来决定是否重新编译

如下例，Status 中新增枚举成员 audited，如果函数 continuteProcesing 没有使用 audited，则函数 continuteProcesing 的实现并不需要重新编译

```cpp
enum class Status; // forward declaration
void continueProcessing(Status s); // use of fwd-declared enum
```

**潜在类型:**

域化枚举的潜在类型 (underlying type)，缺省为 int 型，当然也可以自行定义潜在类型。不管哪种方式，编译器都会预先知道枚举成员的大小

```cpp
enum class Status; // underlying type is int
 
enum class Status: std::uint32_t; // underlying type for Status is std::uint32_t (from <cstdint>)
 
enum class Status: std::uint32_t  // specify underlying type on enum's definition
{
    good = ,
    failed = ,
    incomplete = ,
    corrupt = ,
    audited = ,
    indeterminate = 0xFFFFFFFF
};
```

* std::tuple

一般而言，使用 C++11 域化枚举 (scoped enum) 是比较好的选择，但 C++98 非域化枚举 (unscoped enum) 也并非一无是处。

当涉及到 std::tuple 时，使用 C++98 非域化枚举反而会有优势

## constexpr 

constexpr 是 C++11引入的，一方面是为了引入更多的编译时计算能力，另一方面也是解决 C++98 的 const 的双重语义问题。

* const修饰的是类型，constexpr修饰的是用来算出值的那段代码。
  * 在 C 里面，const 很明确只有「只读」一个语义，不会混淆。
  * C++ 在此基础上增加了「常量」语义，也由 const 关键字来承担。
    * 因此引出来一些奇怪的问题，最后 C++11 把「常量」语义拆出来，交给新引入的 constexpr

字面类型(LiteralType)-- 用于编译期运算的对象

## List-initialization    

```cpp
struct Foo
{
  std::vector<int>mem={1，2,3}; // list-initialization of a non-static member 
  std::vector<int> mem2;

  Foo():mem2{-1，-2，-3}{}// list-initialization of a member in constructor};
}
```

## Delegating constructor--委托构造

```cpp
class Foo{
public;
  Foo(char x, int y) {}
  Foo(inty):Foo('a',y){} // Foo(int) delegates to Foo(char, int)};
};
```

## Inheriting constructors ---继承构造

## nullptr

nullptr是nullptr_t的别名:在<cstddef>中定义 

```cpp
typedef decltype(nullptr) nullptr_t;
```

是c++11引入的新的空指针字面值类型。区别于指针类型和成员指针类型。

在c++中尽量使用nullptr替代NULL赋值给空指针。

## long long  char16_t and char32_t

在C++11标准中添加两种新的字符类型char16_t和char32_t，它们分别用来对应Unicode字符集的UTF-16和UTF-32两种编码方法。

## Type alias

using intData = int;

## variadic templates(详细)可变参数模板

pod代表纯旧数据-也就是说，一个没有构造函数、析构函数和虚拟成员函数的类(无论是用关键字struct或关键字class定义的)。维基百科关于pod的文章更加详细，并将其定义为:

A Plain Old Data StructureinC++isanaggregate class that contains only PODS as members, has no user-defined destructor, no user-defined copy assignment operator, and no nonstatic members of pointer-to-member type.

## lambda表达式

https://blog.csdn.net/zhang_si_hang/article/details/127117260

lambda表达式就是定义了一个可调用的匿名函数，一般在局部。

[]{}是最简单的lambda表达式，但是该lambda表达式没有任何意义

格式

```
[capture-list] (parameters) mutable -> return-type { statement}
     
[capture-list] (parameters) mutable -> return-type { statement }
捕捉列表          参数                  返回值       函数体
```

示例

```cpp
auto Add1 = [ ](int x, int y)->int {return (x + y); };
```

lambda表达式各部分说明

1. [capture-list] : 捕捉列表，该列表总是出现在lambda函数的开始位置，**编译器根据[]来判断接下来的代码是否为lambda函数，捕捉列表能够捕捉上下文中的变量供lambda 函数使用。**
  * 捕捉的参数都是自带const的，想要去掉const属性可以用 mutable，但是捕捉的对象(变量)仍是一份拷贝，外部的a，b无法被修改，所以mutable 很少用，意义不大，不如用 [&]引用捕捉 ( )引用传参

2. (parameters)：参数列表。与普通函数的参数列表一致，如果不需要参数传递，则可以连同()一起省略。所传参数和捕捉参数不一样，不自带const，可以修改。

3. mutable：默认情况下，lambda函数总是一个const函数，mutable可以取消其常量性。使用该修饰符时，参数列表不可省略(即使参数为空时，也要带上小括号)。mutable 只是让传值捕捉变量const属性去掉了，但是捕捉的a，b仍是拷贝，外部的a，b无法被修改，所以mutable 很少用，意义不大

4. ->returntype：返回值类型。用追踪返回类型形式声明函数的返回值类型，没有返回值时此部分可省略。返回值类型明确情况下，也可省略，由编译器对返回类型进行推导。

5. {statement}：函数体。在该函数体内，除了可以使用其参数外，还可以使用所有捕获到的变量。

注意：

在lambda函数定义中，参数列表和返回值类型都是可省略部分，而捕捉列表和函数体可以为空，但不可省略，因此C++11中最简单的lambda函数为：[]{}; 该lambda函数不能做任何事情。

**待继续补充**

## noexcept

使用noexcept表明函数或操作不会发生异常，会给编译器更大的优化空间。

```cpp
void fun() throw(); //表示fun函数不允许抛出任何异常，即fun函数是异常安全的。C++11之前 
void fun() noexcept; //C++11之后 
void fun() throw(...); //表示fun函数可以抛出任何形式的异常。 
void fun() throw(exception Type); // 表示fun函数只能抛出exceptionType类型的异常。 
```
## alignas and alignof

alignas:设置对齐字节

alignof:获得对齐字节数

## C++11 内存模型

为什么需要memory order？

* 编译器出于优化的目的，在编译阶段将源码的顺序进行交换。
* 程序执行期间，指令流水被CPU乱序执行。
* Cache的分层及刷新策略使得有时候某些写，读操作的顺序被重排。
* 原子操作说的是，一个操作的状态要么就是未执行，要么就是已完成，不会看见中间状态。

内存模型

一个内存操作的效果，在其他线程中的可见性问题

C++11 中的 atomic library 中定义了以下6种语义来对内存操作的行为进行约定，这些语义分别规定了不同的内存操作在其它线程中的可见性问题:

```cpp
memoryorder {
  memory_order_relaxed, //不对执行顺序做任何保证
  memory_order_consume, //本线程中，所有后续的有关原子类型的操作，必须在本条原子操作完成之后执行
  memory_order_acquire, //本线程中，所有后续的读操作必须在本条原子操作完成后执行
  memory_order_release, //本线程中，所有之前的写操作完成后才能执行本条原子操作
  memory_order_acq_rel, //同时包含memory_order_acquire和memory_order_acq_rel标记
  memory_order_seg_cst  //全部存取都按顺序执行
}; 
```

https://blog.csdn.net/qq_35987777/article/details/106826312
https://blog.csdn.net/qq_28133013/article/details/104710999 
https://www.51cto.com/article/617888.html

## thread-local storage

C++11中的thread_local是C++存储期的一种，属于线程存储期。

线程局部存储(Thread Local Storage，TLS)是一种存储期(storage duration)，对象的存储是在**线程开始时分配，线程结束时回收，每个线程有该对象自己的实例**。TLS的一个例子是用全局变量errno表示错误号。这可能在多线程并发时产生同步错误。线程局部存储的errno是个解决办法。

https://blog.csdn.net/fengbingchun/article/details/108691986/