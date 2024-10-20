#include "stack1.h"
#include <iostream>
#include <string>

int main()
{
  Stack<int> intStack;

  intStack.push(7);
  std::cout << intStack.top() << std::endl;

  using floatStack = Stack<float> ;
  floatStack fStack;
  fStack.push(5.5);
  std::cout << fStack.top() << std::endl;
  
  //特例化
  Stack<std::string> stringStack; 
  stringStack.push("hello");
  std::cout << stringStack.top() << std::endl;
  stringStack.pop();

  //部分特例化
  Stack< int*> ptrStack; // stack of pointers (specialimplementation)
  ptrStack.push(new int{42});
  std::cout << *ptrStack.top() << std::endl;
  delete ptrStack.pop();

  return 0;
}