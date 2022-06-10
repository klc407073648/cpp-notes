#include <iostream>

template <bool ok>
constexpr void foo()
{
	//在编译期进行判断，if和else语句不生成代码
	if constexpr (ok == true)
	{
		std::cout << "ok" << std::endl; //当ok为true时，下面的else块不生成汇编代码
	}
	else
	{
		std::cout << "not ok" << std::endl; //当ok为false时，上面的if块不生成汇编代码
	}
}

int main()
{
	foo<true>();  //输出ok，并且汇编代码中只有 std::cout << "ok" << std::endl;
	foo<false>(); //输出not ok，并且汇编代码中只有 std::cout << "not ok" << std::endl;

	constexpr auto foo = [](int a, int b)
	{ return a + b; };
	static_assert(6 == foo(2, 3), "compile-time judge"); //static_assert关键字，用来做编译期间的断言，因此叫做静态断言
	//compile_time_if_constexpr.cpp:24:18: error: static assertion failed: not compile-time
	return 0;
}