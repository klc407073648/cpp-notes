#include <iostream>
#include <unordered_map>
#include <tuple>

void fallthrough_fun()
{

	int i = 1;
	int result;
	switch (i)
	{
	case 0:
		result = 1; // warning
		std::cout<< "result=1"<<std::endl;
	case 1:
		result = 2;
		[[fallthrough]]; // no warning
		std::cout<< "result=2"<<std::endl;
	default:
		result = 0;
		std::cout<< "result=0"<<std::endl;
		break;
	}
}

[[nodiscard]] auto nodiscard_fun(int a, int b) { return a + b; }

int main()
{
	fallthrough_fun();
	auto ret=nodiscard_fun(2, 3); // 放弃具有 "nodiscard" 属性的函数的返回值
	std::cout<< ret<<std::endl;
	[[maybe_unused]] int y = 2;
	std::cout<< y<<std::endl;
	return 0;
}