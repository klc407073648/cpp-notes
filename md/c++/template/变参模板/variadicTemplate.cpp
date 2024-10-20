#include <iostream>
void print()
{
}

template <typename T, typename... Types>
void print(T firstArg, Types... args)
{
  std::cout << firstArg << std::endl; // print first argument
  print(args...);                     // call print() for remaining arguments
}

template <typename T, typename... Types>
void printSize(T firstArg, Types... args)
{
  std::cout << firstArg << std::endl;         // print first argument
  std::cout << sizeof...(Types) << std::endl; // print number of remaining
  std::cout << sizeof...(args) << std::endl;  // print number of remaining
}

int main()
{
  std::string s("world");
  print(7.5, "hello", s);
  printSize(7.5, "hello", s);
  return 0;
}
