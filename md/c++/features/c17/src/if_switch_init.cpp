#include <iostream>
#include <unordered_map>
#include <tuple>

void c11_fun()
{

	std::unordered_map<std::string, int> students{{"liBai", 18}, {"hanXin", 19}};
	auto iter = students.find("hanXin");
	if (iter != students.end())
	{
		std::cout << iter->second << std::endl;
	}
}

void c17_fun()
{
	std::unordered_map<std::string, int> students{{"liBai", 18}, {"hanXin", 19}};
	if (auto iter = students.find("hanXin"); iter != students.end())
	{
		std::cout << iter->second << std::endl;
	}
}

int main()
{
	//c11_fun();
	c17_fun();

	return 0;
}