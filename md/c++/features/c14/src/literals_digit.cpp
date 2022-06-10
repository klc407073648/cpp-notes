#include <cmath>
#include <iostream>
using namespace std;

int main()
{
  int a = 0b0001'1111'1010;
  double b = 3.14'1592'6535'8979;
  std::cout << "a:" << a << std::endl; // 506
  std::cout << "b:" << b << std::endl; // 3.14159

  return 0;
}
