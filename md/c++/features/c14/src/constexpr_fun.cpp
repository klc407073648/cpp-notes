#include <cmath>
#include <iostream>
using namespace std;

constexpr int factorial(int n) { // 在C++11或者C++14中均可以编译通过
  return n <= 1 ? 1 : (n * factorial(n - 1));
}

constexpr int factorial_c14(int n) { // 只有在C++14中可以编译通过
  int ret = 1;
  for (int i = 1; i <= n; ++i) {
    ret *= i;
  }
  return ret;
}

int main()
{
  
  std::cout << factorial(5) << std::endl;   // 120
  std::cout << factorial_c14(5) << std::endl; // 在c++11下,会报error: body of ‘constexpr’ function ‘constexpr int factorial_c14(int)’ not a return-statement
  return 0;
}
