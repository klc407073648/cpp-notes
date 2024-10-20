#include <iostream>
#include <stdio.h>
#include <thread>

// 定义线程局部变量
thread_local int my_var = 0;

void my_thread_func() {
    my_var++;
    //std::cout << "my_var in thread " << std::this_thread::get_id() << " is " << my_var << std::endl;
    printf("my_var in thread %d is %d\n", std::this_thread::get_id(), my_var);
}

int main() {
    std::thread t1(my_thread_func);
    std::thread t2(my_thread_func);

    t1.join();
    t2.join();

    return 0;
}

/*
[root@VM-16-6-centos test]# g++ thread_local.cpp -o thread_local --std=c++11 -lpthread
[root@VM-16-6-centos test]# ./thread_local
my_var in thread 903399168 is 1
my_var in thread 911791872 is 1
*/