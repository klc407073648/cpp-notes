#include<iostream>
using namespace std;
class Base;
typedef int(Base::*p)();//定义成员函数指针类型
class Base
{
public:
    p virtual_p;//成员函数指针
    Base()
    {
        //初始化成员函数指针指向基类test
        virtual_p = (int(Base::*)())&Base::test;
    }
    ~Base(){}
    int test()//判断virtual_p的指向，如果指向派生类test就返回派生类的test调用
    {
        if (virtual_p == &Base::test)
        {
            cout << "Base" << endl;
            return 0;
        }
        else
            return (this->*virtual_p)();//返回派生类test调用,对virtual_p解引用后是test函数
    }
};
class Derived :public Base
{
public:
    Derived()
    {
        //初始化成员函数指针指向派生类test
        virtual_p = (int(Base::*)())&Derived::test;
    }
    ~Derived(){}
    int test()
    {
        cout << "Derived" << endl;
        return 0;
    }
};
int main()
{
    Base *b;//基类指针
    Derived d;//派生类对象
    Base bb;//基类对象
    //指向基类对象时调用基类test，指向派生类对象时调用派生类test,模拟了动态关联
    b = &d;
    cout << b->test() << endl;
    b = &bb;
    cout << b->test() << endl;
    return 0;
}