#include <iostream>
#include <string>
#include "stackauto.h"

int main()
{
    Stack<int, 20u> int20Stack;         // stack of up to 20 ints
    Stack<std::string, 40> stringStack; // stack of up to 40 strings
    // manipulate stack of up to 20 ints
    int20Stack.push(7);
    std::cout << int20Stack.top() << std::endl;
    auto size1 = int20Stack.size();
    // manipulate stack of up to 40 strings
    stringStack.push("hello");
    std::cout << stringStack.top() << std::endl;
    auto size2 = stringStack.size();
    if (!std::is_same_v<decltype(size1), decltype(size2)>)
    {
        std::cout << "size types differ" << std::endl;
    }
}