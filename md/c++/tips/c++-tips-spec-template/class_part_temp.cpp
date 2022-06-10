
#include <vector>
#include <iostream> 
using namespace std;

// 类模板
template<class T, class N> 
class Test {
public:
	static bool comp(T num1, N num2) {
		cout <<"standard class template"<< endl;
		return (num1<num2) ? true : false;
	}
};

// 对部分模板参数进行特化
template<class N> 
class Test<int, N> {
public:
	static bool comp(int num1, N num2) {
		cout << "partitial specialization" << endl;
		return (num1<num2) ? true : false;
	}
};

// 将模板参数特化为指针
template<class T, class N> 
class Test<T*, N*> {
public:
	static bool comp(T* num1, N* num2) {
		cout << "new partitial specialization" << endl;
		return (*num1<*num2) ? true : false;
	}
};

// 将模板参数特化为另一个模板类
template<class T, class N> 
class Test<vector<T>,vector<N>> {
public:
	static bool comp(const vector<T>& vecLeft, const vector<N>& vecRight) {
		cout << "to vector partitial specialization" << endl;
		return (vecLeft.size()<vecRight.size()) ? true : false;
	}
};

int main() {
	// 调用非特化版本
	cout << Test<char, char>::comp('0', '1') << endl;	
	
	// 调用部分模板参数特化版本
	cout << Test<int,char>::comp(30, '10') << endl;		

	// 调用模板参数特化为指针版本
	int a = 30;
	char c = '10';
	cout << Test<int*, char*>::comp(&a, &c) << endl;		

	// 调用模板参数特化为另一个模板类版本
	vector<int> vecLeft{1,2,3,4};
	vector<int> vecRight{5,6};
	cout << Test<vector<int>, vector<int>>::comp(vecLeft,vecRight) << endl;	

    return 0;
}
