#include <iostream>
#include <string>
#include <vector>
#include <complex>

void print()
{
}

template <typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << firstArg << std::endl; // print first argument
    print(args...);                     // call print() for remaining arguments
}

template <typename... T>
void printDoubled(T const &...args)
{
    print(args + args...);
}

template <typename... T>
void addOne(T const &...args)
{
    print((args + 1)...);
}

template <typename T1, typename... TN>
constexpr bool isHomogeneous(T1, TN...)
{
    return (std::is_same<T1, TN>::value && ...); // since C++17
}

template <typename C, typename... Idx>
void printElems(C const &coll, Idx... idx)
{
    print(coll[idx]...);
}

int main()
{
    printDoubled(7.5, std::string("hello"), std::complex<float>(4, 2));
    addOne(5, 6.5, 7.77);
    isHomogeneous(43, -1, "hello");

    std::vector<std::string> coll = {"good", "times", "say", "bye"};
    printElems(coll, 2, 0, 3);

    return 0;
}