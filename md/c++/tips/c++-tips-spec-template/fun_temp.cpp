#include <iostream>
#include <string.h>
using namespace std;

template<typename T> 
T compareMax(T t1,T t2) {
	return (t1>t2)?t1:t2;
}

template<> 
const char* compareMax<const char*>(const char* s1,const char* s2) {
	return (strcmp(s1,s2)>0)?s1:s2;
}

template <typename A, typename B>
void f(A a, B b) {
    std::cout << "Normal version." << std::endl;
}

template <typename A>
void f<A, int>(A a, int b) {
    std::cout << "Partial version." << std::endl;
}

int main() {
	// 隐式调用实例：int max<int>(int,int)
	int i=compareMax(10,5);
	
	// 显式调用特化版本：const char* max<const char*>(const char*,const char*)
	const char* p=compareMax<const char*>("abc","bcd");
	cout<<"i:"<<i<<endl;
	cout<<"p:"<<p<<endl;

	//测试2，会编译报错
	int a = 10;
	double b = 12.0;
	f(a, b);
	f(a, a);
	/*
	fun_temp.cpp: error: function template partial specialization ‘f<A, int>’ is not allowed
	void f<A, int>(A a, int b) {

	*/
	return 0;
}
