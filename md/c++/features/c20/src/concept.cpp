#include <concepts>
#include <iostream>

template <typename T>
concept Integeral = std::is_integral<T>::value;

template <Integeral T>
auto isEqual(T left, T right) {
  return left == right;
}

int main() {
  cout << std::boolalpha;

  double a = 2.334;
  double b = 2.335;

  std::cout << isEqual(2, 2) << std::endl;         // true
  std::cout << isEqual(b - a, 0.001) << std::endl; // false

  return 0;
}
