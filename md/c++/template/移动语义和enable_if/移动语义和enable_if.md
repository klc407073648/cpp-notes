# 移动语义和enable_if

## 完美转发

假设希望实现的泛型代码可以将被传递参数的基本特性转发出去：
* 可变对象被转发之后依然可变。
* Const 对象被转发之后依然是 const 的。
* 可移动对象（可以从中窃取资源的对象） 被转发之后依然是可移动的。
```c++
#include <utility>
#include <iostream>

class X
{
};
void g(X &)
{
    std::cout << "g() for variable\n";
}
void g(X const &)
{
    std::cout << "g() for constant\n";
}
void g(X &&)
{
    std::cout << "g() for movable object\n";
}
// let f() forward argument val to g():
/*
void f(X &val)
{
    g(val); // val is non-const lvalue => calls g(X&)
}
void f(X const &val)
{
    g(val); // val is const lvalue => calls g(X const&)
}
void f(X &&val)
{
    g(std::move(val)); // val is non-const lvalue => needs ::move() to call g(X &&)
}
*/

template <typename T>
void f(T &&val)
{
    g(std::forward<T>(val)); // call the right g() for any passed argument val
}
int main()
{
    X v;             // create variable
    X const c;       // create constant
    f(v);            // f() for nonconstant object calls f(X&) => calls g(X&)
    f(c);            // f() for constant object calls f(X const&) => calls g(X const&)
    f(X());          // f() for temporary calls f(X&&) => calls g(X&&)
    f(std::move(v)); // f() for movable variable calls f(X&&) => calls g(X &&)

    return 0;
}
```
注意 std::move 没有模板参数， 并且会无条件地移动其参数； 而 std::forward<>会跟据被传递参数的具体情况决定是否“转发” 其潜在的移动语义。

## 特殊成员函数模板

```c++
#include <utility>
#include <string>
#include <iostream>
class Person
{
private:
  std::string name;

public:
  // constructor for passed initial name:
  explicit Person(std::string const &n) : name(n)
  {
    std::cout << "copying string-CONSTR for " << name << std::endl;
  }
  explicit Person(std::string &&n) : name(std::move(n))
  {
    std::cout << "moving string-CONSTR for " << name << std::endl;
  }
  // copy and move constructor:
  Person(Person const &p) : name(p.name)
  {
    std::cout << "COPY-CONSTR Person " << name << std::endl;
  }
  Person(Person &&p) : name(std::move(p.name))
  {
    std::cout << "MOVE-CONSTR Person " << name << std::endl;
  }
};
int main()
{
  std::string s = "sname";
  Person p1(s);             // init with string object => calls copying
  Person p2("tmp");         // init with string literal => calls moving
  Person p3(p1);            // copy Person => calls COPY-CONSTR
  Person p4(std::move(p1)); // move Person => calls MOVE-CONST
  return 0;
}

```

## 总结
* 在模板中， 可以通过使用“ 转发引用” （ 亦称“万能引用” ， 声明方式为模板参数 T加&&） 和 std::forward<>将模板调用参完美地数转发出去。
* 将完美转发用于成员函数模板时， 在 copy 或者 move 对象的时候它们可能比预定义的特殊成员函数更匹配。
* 可以通过使用 std::enable_if<>并在其条件为 false 的时候禁用模板。
* 通过使用 std::enable_if<>， 可以避免一些由于构造函数模板或者赋值构造函数模板比隐式产生的特殊构造函数更加匹配而带来的问题。
* 可 以 通 过 删 除 对 const volatile 类 型 参 数 预 定 义 的 特 殊 成 员 函 数 ， 并 结 合 使 用std::enable_if<>， 将特殊成员函数模板化。
* 通过 concept 可以使用更直观的语法对函数模板施加限制。
