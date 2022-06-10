#include <cmath>
#include <iostream>
using namespace std;

int main()
{
  int a = 2;

  // 捕获列表的捕获变量“赋值”
  [a = sin(a)]()
  {
    std::cout << a << std::endl;      // 0.909297
    std::cout << cos(a) << std::endl; // 0.6143
  }();

  std::cout << a << std::endl;      // 2
  std::cout << cos(a) << std::endl; // -0.416147

  // lambda表达式参数可以为auto类型
  auto f = [](auto a)
  { return a; };
  std::cout << f(1) << std::endl;   // 1
  std::cout << f(1.1) << std::endl; // 1.1
  return 0;
}
