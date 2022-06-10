#include <iostream>
#include <unordered_map>
#include <tuple>
#include <optional>
#include <string>
#include <variant>
#include <any>

void variant_fun()
{
	std::cout << "variant_fun" << std::endl;
	std::variant<int, std::string> var("hello");
	std::cout << var.index() << std::endl;

	var = 123;
	std::cout << var.index() << std::endl;

	try
	{
		var = "world";
		std::string str = std::get<std::string>(var); // 通过类型获取
		var = 3;
		int i = std::get<0>(var); // 通过索引获取
		std::cout << str << ", " << i << std::endl;
	}
	catch (...)
	{
	}
}

std::optional<int> StoI(const std::string &str)
{
	try
	{
		return std::stoi(str);
	}
	catch (...)
	{
		return std::nullopt;
	}
}

void optional_fun()
{
	std::cout << "optional_fun" << std::endl;

	std::string str{"1234"};
	std::optional<int> result = StoI(str);
	if (result)
	{
		std::cout << *result << std::endl;
	}
	else
	{
		std::cout << "StoI() error." << std::endl;
	}
}

void any_fun()
{
	std::cout << "any_fun" << std::endl;

	std::any a = 1;
	std::cout << a.type().name() << ", " << std::any_cast<int>(a) << std::endl;

	a = 2.2f;
	std::cout << a.type().name() << ", " << std::any_cast<float>(a) << std::endl;

	if (a.has_value())
	{
		std::cout << a.type().name() << std::endl;
	}
	a.reset();
	if (a.has_value())
	{
		std::cout << a.type().name()<< std::endl;
	}
	a = std::string("hello");
	std::cout << a.type().name() << ", " << std::any_cast<std::string>(a) << std::endl;
}

class Test
{
public:
	Test(std::string name, size_t age) : _name(name), _age(age) { std::cout << "name: " << _name << ", age: " << _age << std::endl; }

private:
	std::string _name;
	size_t _age;
};

int add(int a, int b) { return a + b; }

void tuple_fun()
{
	std::cout << "tuple_fun" << std::endl;

	//创建元组
	std::tuple<int, char, double> tp(2, 'b', 8.5);
	auto data0 = std::get<0>(tp); //获得里面的元素
	auto data1 = std::get<1>(tp);
	auto data2 = std::get<2>(tp);
	auto tup1 = std::make_tuple("hello", 'a', 1.3);

	//解包tuple作为构造函数参数构造对象
	auto param = std::make_tuple("Jason", 25);
	std::make_from_tuple<Test>(std::move(param));

	// std::apply,将tuple元组解包，并作为函数的传入参数
	auto add_lambda = [](auto a, auto b, auto c)
	{ return a + b + c; };

	std::cout << std::apply(add, std::pair(2, 3)) << std::endl;
	std::cout << std::apply(add_lambda, std::tuple(2, 3, 4)) << std::endl;
}

void as_const_fun()
{
	std::cout << "as_const_fun" << std::endl;

	std::string str{"hello world"};
	std::cout << std::is_const<decltype(str)>::value << std::endl;

	const std::string str_const = std::as_const(str);
	std::cout << std::is_const<decltype(str_const)>::value << std::endl;
}

int main()
{
	variant_fun();
	optional_fun();
	any_fun();
	tuple_fun();
	as_const_fun();

	return 0;
}