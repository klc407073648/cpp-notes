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

int main() {
	// 隐式调用实例：int max<int>(int,int)
	int i=compareMax(10,5);
	
	// 显式调用特化版本：const char* max<const char*>(const char*,const char*)
	const char* p=compareMax<const char*>("abc","bcd");
	cout<<"i:"<<i<<endl;
	cout<<"p:"<<p<<endl;
}
