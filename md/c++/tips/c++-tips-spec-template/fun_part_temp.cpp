
#include <vector>
#include <iostream> 
using namespace std;

// 函数模板
template<class T, class N> 
void compare(T num1, N num2) {
	cout << "standard function template" << endl;
	if(num1>num2) {
		cout << "num1:" << num1 << " > num2:" << num2 <<endl;
	} else {
		cout << "num1:" << num1 << " <= num2:" << num2 << endl;
	}
}

//对部分模板参数进行特化
template<class N> 
void compare(int num1, N num2) {
	cout<< "partitial specialization" <<endl;
	if (num1>num2)
		cout << "num1:" << num1 << " > num2:" << num2 << endl;
	else
		cout << "num1:" << num1 << " <= num2:" << num2 << endl;
}

//将模板参数特化为指针(模板参数的部分特性)
template<class T, class N> 
void compare(T* num1, N* num2) {
	cout << "new partitial specialization" << endl;
	if (*num1>*num2)
		cout << "num1:" << *num1 << " > num2:" << *num2 << endl;
	else
		cout << "num1:" << *num1 << " <= num2:" << *num2 << endl;
}

// 将模板参数特化为另一个模板类
template<class T, class N> 
void compare(std::vector<T>& vecLeft, std::vector<T>& vecRight) {
	cout << "to vector partitial specialization" << endl;
	if (vecLeft.size()>vecRight.size())
		cout << "vecLeft.size()" << vecLeft.size() << " > vecRight.size():" << vecRight.size() << endl;
	else
		cout << "vecLeft.size()" << vecLeft.size() << " <= vecRight.size():" << vecRight.size() << endl;
}

int main() {
	// 调用非特化版本 compare<int,int>(int num1, int num2)
	compare<int,int>(30,31);

	// 调用偏特化版本 compare<char>(int num1, char num2)
	compare(30,'10');

	int a = 30;
	char c = '1';
	// 调用偏特化版本 compare<int,char>(int* num1, char* num2)
	compare(&a, &c);

	vector<int> vecLeft{0};
	vector<int> vecRight{1,2,3};
	// 调用偏特化版本 compare<int,char>(int* num1, char* num2)
	compare<int,int>(vecLeft,vecRight);

    return 0;
}
