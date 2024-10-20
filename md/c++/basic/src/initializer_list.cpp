#include <iostream>
#include <initializer_list>

void print_ints(std::initializer_list<int> ints) {
    for (auto i : ints) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 创建一个包含三个整数的列表
    std::initializer_list<int> ints = {1, 2, 3};

    // 将列表作为参数传递给函数
    print_ints(ints);

    // 在函数调用时直接创建列表
    print_ints({4, 5, 6});

    return 0;
}