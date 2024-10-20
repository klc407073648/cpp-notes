#include <iostream>
#include <utility>
#include <tuple>

int main()
{
    std::pair<int, std::string> p{42, "hello"};
    std::tuple<std::string, int, int, std::string> q{"Jason",1001,24,"NJ"};
    auto [i, s] = p;
    std::cout << "i = " << i << ", s = " << s << std::endl;
    
    auto [a, b, c, d] = q;
    std::cout << "name = " << a << ", no = " << b << ", age = " << c << ", address = " << d << std::endl;
    return 0;
}