#include <iostream>

template <typename T1, typename T2>
constexpr auto max(T1 a, T2 b)
{
  return b < a ? a : b;
}

template <typename T1, typename T2>
auto min(T1 a, T2 b)
{
  return b < a ? a : b;
}

int a[::max(sizeof(char), 1000u)];

//constexpr表达式是指值不会改变并且在编译过程就能得到计算结果的表达式
//int b[::min(sizeof(char), 1000u)];

int main()
{
  a[0] = 1;
  std::cout << "a[0]:" << a[0] << std::endl;

  return 0;
}