#include <iostream>
#include <utility>

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
// 比较类型是否相同 //bool is_samev=is same<T, U>::value; Ce
// https://en.cppreference.com/w/cpp/types/is_same GCC 5.2(c++17) 和 GCC 12.1(c++17)区别

// =delete 
// 声明被删除的函数不能被调用;且需要首次定义时就删除
struct sometype
{
    void* operator new(std::size_t) = delete;
    void* operator new[](std::size_t) = delete;
};
sometype* p = new sometype; // error: attempts to call deleted sometype::operator new


struct sometype { sometype(); };
sometype::sometype() = delete; // error: must be deleted on the first declaration

//= default
//使用default显式告知编译器生成默认的缺省版本

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

// final:一般用于中途终止派生

1. 禁止重写
/*
class Super
{
  public:
    Super();
    virtual void fun() final;//final作用于虚函数，禁止子类重写
}

1. 禁止继承
class Super final
{
  ...
}
*/

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

3. 重定义，类重新定义父类中有相同名称的非虚函数(**参数列表可以不同**)，父类的方法就会被隐藏


右值引用(理解还是不深) 

lvalue 译为"loactor value"，指的是存储在内存中、有明确存储地址(可寻址)的数据， 
rvalue 译为"read value"，指的是那些可以提供数据值的数据(不一定可以寻址，例如存储于寄存器中的数据)。 

C++编程技巧，分别为移动语义和完美转发。 

**std::move(没有新内存的申请和分配，在大量对象的系统中，移动构造相对与拷贝构造可以显著提高性能)**


int main()
{

}