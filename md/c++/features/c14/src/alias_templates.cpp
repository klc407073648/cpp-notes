#include <iostream>
template <typename T, typename U>
struct A
{
  T t;
  U u;
};

template <typename T>
using B = A<T, int>;

int main()
{
  B<double> b;
  b.t = 10.5;
  b.u = 20.8;
  std::cout << b.t << ", " << b.u << std::endl; //10.5, 20
  return 0;
}
