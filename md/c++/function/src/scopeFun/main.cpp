#include <iostream>
using namespace std;

// 全局函数
void myFun()
{
    cout<<"global function myFun"<<endl;
}

class MyClass
{
public:
    int printFun1()
    {
    	//调用的是全局函数
        ::myFun();
    }

     int printFun2()
    {
    	//调用的是成员函数
        myFun();
    }
    void myFun()
    {
        cout<<"MyClass function myFun"<<endl;
    }
};

int main()
{
    MyClass m;
    m.printFun1();
    cout<<"————————————————————"<<endl;
    m.printFun2();
    return 0;
}

