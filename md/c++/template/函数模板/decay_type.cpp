#include <iostream>

template<class T>
T max(T a,T b)
{
  return a>b?a:b;
}

int main()
{
  const int c = 42;
  int i = 1;   
  ::max(i, c); // OK: T 被推断为 int，c中的 const 被 decay 掉
  ::max(c, c); // OK: T 被推断为 int
  int &ir = i;
  ::max(i, ir); // OK: T 被推断为 int， ir 中的引用被 decay 掉
  int arr[4];
  ::max(4, 7.2); // ERROR: 不确定 T 该被推断为 int 还是 double

  return 0;
}