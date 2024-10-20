#include <iostream>

constexpr int num = 5;
constexpr int result = num * num;

int main() {
    std::cout << "Square of " << num << " is " << result << std::endl;

    return 0;
}