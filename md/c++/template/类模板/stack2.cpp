#include "stack2.h"
#include <iostream>
#include <deque>

int main()
{
  // stack of ints:
  Stack<int> intStack;
  // stack of doubles using a std::deque<> to manage the elements
  Stack<double, std::deque<double>> dblStack;
  // manipulate int stack
  intStack.push(7);
  std::cout << intStack.top() << std::endl;
  intStack.pop();
  // manipulate double stack
  dblStack.push(42.42);
  std::cout << dblStack.top() << std::endl;
  dblStack.pop();
  return 0;
}
