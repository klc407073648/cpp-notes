#include <iostream>
#include <cmath>
#define PI 3.1415926

// 定义一个长度单位“米”的字面量后缀
constexpr long double operator "" _meters(long double meters) {
  return meters;
}

// 定义一个角度单位“弧度”的字面量后缀
constexpr long double operator "" _rad(long double radians) {
  return radians;
}

int main() {
  auto distance = 10.5_meters;
  auto angle = 45.0_rad;
  auto height = distance * std::tan(angle*PI/180);

  std::cout << "Height = " << height << " meters" << std::endl;
  
  return 0;
}