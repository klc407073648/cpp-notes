#include <iostream>
#include <any>
#include <string>
#include <vector>

int main() {
  std::any a = 1; // 存储一个整数
  std::cout << std::any_cast<int>(a) << '\n'; // 输出 1

  a = 3.14; // 存储一个浮点数
  std::cout << std::any_cast<double>(a) << '\n'; // 输出 3.14

  a = std::string("Hello, World!"); // 存储一个字符串
  std::cout << std::any_cast<std::string>(a) << '\n'; // 输出 Hello, World!

  std::vector<int> v = {1, 2, 3, 4, 5};
  a = v; // 存储一个vector
  std::vector<int> b = std::any_cast<std::vector<int>>(a); // 从any中获取vector
  for (auto i : b) {
    std::cout << i << " ";
  }
  std::cout << '\n'; // 输出 1 2 3 4 5

  return 0;
}