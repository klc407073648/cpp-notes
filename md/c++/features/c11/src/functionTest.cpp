/**
 * 函数概述: std::function 是一种通用的多态函数包装器,可以存储、复制和调用任何可调用的目标——普通函数、
 * lambda表达式、bind表达式或其他函数对象，以及指向成员函数的指针和指向数据成员的指针（统称为“可调用对象”）。
 * 存在意义：多个不同类型的可调用对象却拥有着相同的调用形式。例如 std::function<int(int,int)>
 */

#include <functional>
#include <assert.h>
#include <iostream>

using namespace std;
 

/*加减乘除举例*/
typedef std::function<int(int,int)>  mFunctor;

int add(int a,int b)
{
    return a+b;
}

struct sub
{
    int operator()(int a,int b)
    {
        return a-b;
    }
};

auto Lam = [](int a,int b)->int{return a*b;};

class Math
{
public:
    static int div(const int a, const int b)
    {
        assert(b);
        return a/b;
    }
	int print_sum(int n1, int n2)
    {
        return n1+n2;
    }
};


int main()
{
    int a = 10, b = 5;
	Math math;
	
    std::function<int(int,int)> fun1 = add;     //普通函数
    mFunctor fun2 = sub();						//重载了函数调用运算符的函数对象
    mFunctor fun3 = Lam;      					//lambada表达式
    mFunctor fun4 = Math::div;  				//类静态成员函数
	std::function<int(int,int)> fun5 = std::bind(&Math::print_sum, &math, std::placeholders::_1, std::placeholders::_2);//类成员函数
	
	cout<<"fun1 add:"<<fun1(10,5)<<endl;
	cout<<"fun2 sub():"<<fun2(10,5)<<endl;
	cout<<"fun3 Lam:"<<fun3(10,5)<<endl;
	cout<<"fun4 Math::div:"<<fun4(10,5)<<endl;
	cout<<"fun5 Math::print_sum:"<<fun5(10,5)<<endl;
    return 0;
}
