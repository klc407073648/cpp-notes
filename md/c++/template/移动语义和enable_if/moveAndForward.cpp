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