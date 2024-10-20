#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec{ 1, 2, 3, 4, 5 };

    for (auto & element : vec) {
        std::cout << element << " ";
    }

    return 0;
}