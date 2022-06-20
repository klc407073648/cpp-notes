#include <iostream>
int count = 0; // 全局（::）的 count

class A
{
public:
    static int count; // 类 A 的 count（A::count）
};

int A::count = 0;

int main()
{
    ::count = 1; // 设置全局的 count 的值为 1

    A::count = 2; // 设置类 A 的 count 为 2

    int count = 0; // 局部的 count
    count = 3;     // 设置局部的 count 的值为 3

    return 0;
}