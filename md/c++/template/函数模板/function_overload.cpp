#include <cstring>
#include <string>
#include <iostream>
// maximum of two values of any type:
template <typename T>
T max(T a, T b)
{
  return b < a ? a : b;
}

// maximum of two pointers:
template <typename T>
T *max(T *a, T *b)
{
  return *b < *a ? a : b;
}

// maximum of two C -strings : 
char const *max(char const *a, char const *b)
{
  return std::strcmp(b, a) < 0 ? a : b;
}

int main()
{
  int a = 7;
  int b = 42;
  auto m1 = ::max(a, b); // max() for two values of type int
  std::string s1 = "hey";
  std::string s2 = "you";
  auto m2 = ::max(s1, s2); // max() for two values of type std::string
  int *p1 = &b;
  int *p2 = &a;
  auto m3 = ::max(p1, p2); // max() for two pointers
  char const *x = "hello"; 
  char const *y = "world";
  auto m4 = ::max(x, y); // max() for two C-strings

  std::cout<<"m1:"<<m1<<std::endl;
  std::cout<<"m2:"<<m2<<std::endl;
  std::cout<<"m3:"<<m3<<std::endl;
  std::cout<<"m4:"<<m4<<std::endl;

  return 0;
}