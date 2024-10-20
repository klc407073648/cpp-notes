#include<iostream>

template<class T1,class T2>
auto max(T1 a,T2 b)
{
  std::cout<<"auto max(T1 a,T2 b)"<<std::endl;
  return a>b?a:b;
}


template<class RT,class T1,class T2>
RT max(T1 a,T2 b)
{
  std::cout<<"RT max(T1 a,T2 b)"<<std::endl;
  return a>b?a:b;
}

int main()
{
  auto a=::max(4,7.2);
  auto b=::max<long double>(7.2,4);
  auto c=::max<int>(4,7.2);//call of overloaded ‘max<int>(int, double)’ is ambiguous
  return 0;
}