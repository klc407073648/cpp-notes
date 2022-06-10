#include <iostream>
using namespace std;

template <class T>
constexpr T pi = T(3.1415926535897932385L); // 变量模板

template <class T>
T circular_area(T r)
{                       // 函数模板
  return pi<T> * r * r; // pi<T> 是变量模板实例化
}

int main()
{
  cout << circular_area(2) << endl;   // 12
  cout << circular_area(2.0) << endl; // 12.5664
  return 0;
}