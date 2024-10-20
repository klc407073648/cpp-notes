#include <iostream>
#include <string_view>

void print(std::string_view sv) {
  std::cout << sv << '\n';
}

int main() {
  std::string str = "Hello, World!";
  std::string_view sv(str);

  print(sv); // 输出 Hello, World!

  sv = sv.substr(7);
  print(sv); // 输出 World!

  return 0;
}