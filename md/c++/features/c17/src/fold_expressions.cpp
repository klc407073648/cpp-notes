#include <iostream>
#include <vector>

template <typename... Args>
void printer(Args &&...args)
{
	(std::cout << ... << args) << '\n';
}

template <typename... Args>
auto sub_right(Args... args)
{
	return (args - ...);
}

template <typename... Args>
auto sub_left(Args... args)
{
	return (... - args);
}

template <typename... Args>
auto sum_right(Args... args)
{
	return (args + ...);
}

int main()
{
	printer(1, 2, 3, "abc");

	std::cout << sub_right(8, 4, 2) << std::endl; // (8 - (4 - 2)) = 6
	std::cout << sub_left(8, 4, 2) << std::endl;  // ((8 - 4) - 2) = 2

	std::cout << sum_right(std::string{"hello "}, std::string{"world"})
			  << std::endl; // hello world
	
	return 0;
}