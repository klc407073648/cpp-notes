#include <iostream>

template <auto T>
void foo() { std::cout << T << std::endl; }

int main()
{
	foo<100>(); // foo<int>();
	//foo<8.8>(); // foo<double>(); 这个是错误的，待研究

	return 0;
}