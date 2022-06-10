// test_module.ixx
export module test_module;

namespace _module {
auto _print() { return "hello world"; }
export auto print() { return _print(); }
} // namespace _module

/*——————————————————————————————————————————*/

// main.cpp
import test_module;
#include <iostream>

int main() {
  std::cout << _module::print() << std::endl; // hello world
  return 0;
}
