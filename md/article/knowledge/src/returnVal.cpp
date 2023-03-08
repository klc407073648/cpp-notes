#include <iostream>
using namespace std;

int test1(void)
{
  int a = 50;
  return a;
}
int *test2(void)
{
  int a = 100;
  int *p = &a;
  cout << "p的地址= " << p << endl;
  return p;
}
int main()
{
  int x = 10;
  x = test1();
  cout << "x= " << x << endl;
  int *p = NULL;
  p = test2();
  cout << "p= " << p << endl;
  cout << "*p= " << *p << endl;

  return 0;
}