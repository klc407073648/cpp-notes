
#include <iostream>
using namespace std;

template<class T>
class A {
	T num;
public:
	A(){
		num=T(0);
	}
	void print(){
		cout<<"A'num:"<<num<<endl;
	}
};

template<> 
class A<char*> 
{
	char* str;
public:
	A() {
		str="A' special definition: char*";
	}
	void print() {
		cout<<str<<endl;
	}
};

int main() {
	A<int> a1;      //显示模板实参的隐式实例化
	a1.print();
	A<char*> a2;    //使用特化的类模板
	a2.print();
	
	return 0;
}
