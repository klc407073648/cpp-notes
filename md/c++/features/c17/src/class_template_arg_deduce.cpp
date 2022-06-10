#include <utility>
#include <tuple>
#include <iostream>
#include <functional>
#include <algorithm>

template <typename T>
class A
{
public:
	A(T, T){};
};

int main()
{
	std::pair p(2, 4.5);	 // std::pair<int, double> p
	std::tuple t(4, 3, 2.5); // std::tuple<int, int, double> t
	std::less l;			 // std::less<void> l
	auto y = new A{1, 2};	 // A<int>::A(int, int)

	return 0;
}