# C++11新特性

[[toc]]

## auto类型推导

C++11 赋予 auto 关键字新的含义，使用它来做自动类型推导。也就是说，使用了 auto 关键字以后，<font color='red'>编译器会在编译期间自动推导出变量的类型</font>，这样我们就不用手动指明变量的数据类型了。

auto 关键字基本的使用语法如下：

```
auto name = value;
```

name 是变量的名字，value 是变量的初始值。

注意：<font color='red'>auto 仅仅是一个占位符，在编译器期间它会被真正的类型所替代</font>。或者说，C++ 中的变量必须是有明确类型的，只是这个类型是由编译器自己推导出来的。

### auto 的限制

1. auto 不能在函数的参数中使用(auto 要求必须对变量进行初始化)。
2. auto 不能作用于类的非静态成员变量（也就是没有 static 关键字修饰的成员变量）中。
3. auto 关键字不能定义数组。
4. auto 不能作用于模板参数。

### auto 的应用

* 使用 auto 定义迭代器

  * vector< vector<int> >::iterator i = v.begin();  ——> **auto** i = v.begin();

* auto用于泛型编程


## decltype类型推导

auto 和 decltype 关键字都可以自动推导出变量的类型，但它们的用法是有区别的：

```
auto varname = value;
decltype(exp) varname = value;
```

其中，varname 表示变量名，value 表示赋给变量的值，exp 表示一个表达式。

<font color='red'>auto 根据`=`右边的初始值 value 推导出变量的类型，而 decltype 根据 exp 表达式推导出变量的类型，跟`=`右边的 value 没有关系。</font>

另外，auto 要求变量必须初始化，而 decltype 不要求。这很容易理解，auto 是根据变量的初始值来推导出变量类型的，如果不初始化，变量的类型也就无法推导了。decltype 可以写成下面的形式：

```
decltype(exp) varname;
```

### decltype 的实际应用

```cpp
#include <vector>
using namespace std;
template <typename T>
class Base {
public:
    void func(T& container) {
        m_it = container.begin();
    }
private:
    typename T::iterator m_it;  //注意这里
};
int main()
{
    const vector<int> v;
    Base<const vector<int>> obj;
    obj.func(v);
    return 0;
}


template <typename T>
class Base {
public:
    void func(T& container) {
        m_it = container.begin();
    }
private:
    decltype(T().begin()) m_it;  //注意这里
};
```

## 使用using 定义别名

C++11 的 using 写法只是 typedef 的等价物。

```cpp
template <typename Val>
using str_map_t = std::map<std::string, Val>;

//可以统一处理以下场景
//typedef std::map<std::string, int> map_int_t;
//typedef std::map<std::string, std::string> map_str_t;

void testUsing()
{
	str_map_t<int> map1;
	str_map_t<std::string> map2;
	
	map1["age"]=27;
	map2["address"]="NJ";
	
	cout<<"map1[\"age\"]:"<<map1["age"]<<endl;
	cout<<"map2[\"address\"]:"<<map2["address"]<<endl;
}
```

## 支持函数模板的默认模板参数

C++11 支持为函数模板中的参数设置默认值，在实际使用过程中，我们可以选择使用默认值，也可以尝试由编译器自行推导得到，还可以亲自指定各个模板参数的类型。

```cpp
template <typename R = int, typename T, typename U>
R func(T v1,U v2)
{
    return v1+v2;
}

void testFunTemplate()
{
    auto r1=func(5.5,10);                    // R=int, T=double, U=int
    auto r2=func<double>(5.5,10);            // R=double, T=double, U=int
    auto r3=func<double, int, int>(5.5,10);  // R=double, T=int, U=int
	
	cout<<"r1:"<<r1<<endl;
	cout<<"r2:"<<r2<<endl;
	cout<<"r3:"<<r3<<endl;
}
```

## tuple元组

tuple 最大的特点是：<font color='red'>实例化的对象可以存储任意数量、任意类型的数据。</font>

tuple 的应用场景很广泛，例如当需要存储多个不同类型的元素时，可以使用 tuple；当函数需要返回多个数据时，可以将这些数据存储在 tuple 中，函数只需返回一个 tuple 对象即可。

```cpp
void testTuple()
{
    std::tuple<int, char> first;                             // 1)   first{}
    std::tuple<int, char> second(first);                     // 2)   second{}
    std::tuple<int, char> third(std::make_pair(20, 'b'));   // 3)   third{20,'b'}
    std::tuple<long, char> fourth(third);                    // 4)的左值方式, fourth{20,'b'}
    std::tuple<int, char> fifth(10, 'a');                    // 5)的右值方式, fifth{10.'a'}
    std::tuple<int, char,string> sixth(std::make_tuple(30, 'c',"address"));    // 6)的右值方式, sixth{30, 'c',"address"}
    
    std::cout << std::get<0>(fourth) << " " << std::get<1>(fourth) << std::endl;
    std::cout << std::get<0>(fifth) << " " << std::get<1>(fifth) << std::endl;
    std::cout << std::get<0>(sixth) << " " << std::get<1>(sixth) << " " << std::get<2>(sixth) << std::endl;
    
    int size = std::tuple_size<decltype(sixth)>::value;
    std::cout << size << std::endl;
}
```

## 列表初始化

在 C++11 中，初始化列表的适用性被大大增加了。它现在可以用于任何类型对象的初始化，请看下面的代码。

```cpp
class Foo
{
public:
    Foo(int) {}
private:
    Foo(const Foo &);
};
int main(void)
{
    Foo a1(123);
    Foo a2 = 123;  //error: 'Foo::Foo(const Foo &)' is private
    Foo a3 = { 123 };
    Foo a4 { 123 };
    int a5 = { 3 };
    int a6 { 3 };
    return 0;
}
```

在上例中，a3、a4 使用了新的初始化方式来初始化对象，效果如同 a1 的直接初始化。

a5、a6 则是基本数据类型的列表初始化方式。可以看到，它们的形式都是统一的。

这里需要注意的是，a3 虽然使用了等于号，但它仍然是列表初始化，因此，私有的拷贝构造并不会影响到它。

a4 和 a6 的写法，是 C++98/03 所不具备的。在 C++11 中，可以直接在变量名后面跟上初始化列表，来进行对象的初始化。

## lambda匿名函数

C++11 标准终于引入了 lambda，本节将带领大家系统地学习 lambda 表达式的具体用法。

定义一个 lambda 匿名函数很简单，可以套用如下的语法格式：

```
[外部变量访问方式说明符] (参数) mutable noexcept/throw() -> 返回值类型
{
   函数体;
};
```

| 外部变量格式      | 功能                                                         |
| ----------------- | ------------------------------------------------------------ |
| []                | 空方括号表示当前 lambda 匿名函数中不导入任何外部变量。       |
| [=]               | 只有一个 = 等号，表示以值传递的方式导入所有外部变量；        |
| [&]               | 只有一个 & 符号，表示以引用传递的方式导入所有外部变量；      |
| [val1,val2,...]   | 表示以值传递的方式导入 val1、val2 等指定的外部变量，同时多个变量之间没有先后次序； |
| [&val1,&val2,...] | 表示以引用传递的方式导入 val1、val2等指定的外部变量，多个变量之间没有前后次序； |
| [val,&val2,...]   | 以上 2 种方式还可以混合使用，变量之间没有前后次序。          |
| [=,&val1,...]     | 表示除 val1 以引用传递的方式导入外，其它外部变量都以值传递的方式导入。 |
| [this]            | 表示以值传递的方式导入当前的 this 指针。                     |

## for循环

 C++ 11 标准为 for 循环添加了一种全新的语法格式，如下所示：

```cpp
for (declaration : expression){
    //循环体
}
```

示例：

```cpp
void testForLoop()
{
    char arc[] = "abcdefg";
    //for循环遍历普通数组
    for (char ch : arc) {
        cout << ch;
    }
    cout << endl;
    vector<char>myvector(arc, arc + 23);
    //for循环遍历 vector 容器
    for (auto ch : myvector) {
        cout << ch;
    }
    cout << endl;
}
```

## constexpr

constexpr 关键字的功能是<font color='red'>使指定的常量表达式获得在程序编译阶段计算出结果的能力</font>，而不必等到程序运行阶段。C++ 11 标准中，constexpr 可用于修饰普通变量、函数（包括模板函数）以及类的构造函数。

C++11 标准中，定义变量时可以用 constexpr 修饰，从而使该变量获得在编译阶段即可计算出结果的能力。

```cpp
constexpr int num = 1 + 2 + 3;
int url[num] = {1,2,3,4,5,6};
cout<< url[1] << endl;
```

## 右值引用

C++11 标准新引入了另一种引用方式，称为右值引用，用 "&&" 表示。右值引用引申出的 2 种 C++ 编程技巧，分别为<font color='red'>移动语义和完美转发。</font>

lvalue 是“loactor value”的缩写，可意为存储在内存中、有明确存储地址（可寻址）的数据，而 rvalue 译为 "read value"，指的是那些可以提供数据值的数据（不一定可以寻址，例如存储于寄存器中的数据）。

和声明左值引用一样，右值引用也<font color='red'>必须立即进行初始化操作，且只能使用右值进行初始化。</font>

```cpp
int num = 10;
//int && a = num;  //右值引用不能初始化为左值
int && a = 10;
a = 100;
cout << a << endl;
```

### std::move

C++11最重要的一个改进之一就是引入了move语义，这样在一些对象的构造时可以获取到已有的资源（如内存）而不需要通过拷贝，申请新的内存，这样移动而非拷贝将会大幅度提升性能。

```cpp
//-fno-elide-constructions 关闭了g++编译器会省略函数返回值时临时对象的拷贝的优化。
class demo{
public:
    demo():num(new int(0)){
        cout<<"construct!"<<endl;
    }
    //拷贝构造函数
    demo(const demo &d):num(new int(*d.num)){
        cout<<"copy construct!"<<endl;
    }
    //移动构造函数
    demo(demo &&d):num(d.num){
        d.num = NULL;
        cout<<"move construct!"<<endl;
    }
    ~demo(){
      delete num;
      cout<<"class demo destruct!"<<endl;
   }
   
public:     //这里应该是 private，使用 public 是为了更方便说明问题
    int *num;
};

demo get_demo(){
    return demo();
}

void testMove()
{
    demo demo1;
    cout << "demo2:"<< endl;//拷贝构造函数
    demo demo2 = demo1;
    cout << "demo3:"<< endl;
    demo demo3 = std::move(demo1);//移动构造函数
}
```

在移动构造函数中，只是获取了被移动对象的资源(内存)的所有权，同时把被移动对象的成员指针置为空（以避免移动过来的内存被析构），这个过程中<font color='red'>没有新内存的申请和分配，在大量对象的系统中，移动构造相对与拷贝构造可以显著提高性能！</font>

### std::forward

完美转发：函数模板可以将自己的参数“完美”地转发给内部调用的其它函数。所谓完美，即不仅能准确地转发参数的值，还能保证被转发参数的左、右值属性不变。

```cpp
//重载被调用函数，查看完美转发的效果
void otherdef(int & t) {
    cout << "lvalue\n";
}
void otherdef(const int & t) {
    cout << "rvalue\n";
}
//实现完美转发的函数模板
template <typename T>
void function(T&& t) {
    otherdef(std::forward<T>(t));
}

void testForward(){
    string A("abc");
    string&& Rval = std::move(A);
    string B(Rval);    // this is a copy , not move.
    cout << A << endl;   // output "abc"
    string C(std::forward<string>(Rval));  // move.
    cout << A << endl;       /* output "" */
    
    function(5);  //rvalue
    int  x = 1;
    function(x);  //lvalue
}
```

## nullptr

C++11 标准下，相比 NULL 和 0，使用 nullptr 初始化空指针可以令我们编写的程序更加健壮。

```cpp
void isnull(void *c){
    cout << "void*c" << endl;
}
void isnull(int n){
    cout << "int n" << endl;
}

void testNullptr()
{
    cout<<"testNullptr:"<<endl;

    isnull(0); 
    //isnull(NULL); // C++ 98/03 标准中 输出 int n
    isnull(nullptr);
}
```
