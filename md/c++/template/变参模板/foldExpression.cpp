#include <iostream>
#include <string>

template <typename T>
class AddSpace
{
private:
    T const &ref; // refer to argument passed in constructor
public:
    AddSpace(T const &r) : ref(r)
    {
    }
    friend std::ostream &operator<<(std::ostream &os, AddSpace<T> s)
    {
        return os << s.ref << " "; // output passed argument and a space
    }
};

template <typename... Args>
void print(Args... args)
{
    (std::cout << ... << AddSpace<Args>(args)) << std::endl;
}

template<typename... T>
auto foldSum (T... s) {
    return (... + s); // ((s1 + s2) + s3) ...
}

int main()
{
    AddSpace<std::string> a("world");
    AddSpace<double> b(3.2);
    AddSpace<int> c(10);

    print(a,b,c);
    std::cout <<foldSum(6.6,8,10,3.33)<< std::endl;

    return 0;
}
