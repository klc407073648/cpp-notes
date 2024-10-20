#include <iostream>
#include <optional>

std::optional<int> divide(int a, int b) {
    if (b == 0) {
        return std::nullopt;
    } else {
        return a / b;
    }
}

int main() {
    auto result1 = divide(10, 2);
    if (result1.has_value()) {
        std::cout << "Result 1: " << result1.value() << std::endl;
    } else {
        std::cout << "Result 1: division by zero" << std::endl;
    }
    
    auto result2 = divide(10, 0);
    if (result2.has_value()) {
        std::cout << "Result 2: " << result2.value() << std::endl;
    } else {
        std::cout << "Result 2: division by zero" << std::endl;
    }
    
    return 0;
}