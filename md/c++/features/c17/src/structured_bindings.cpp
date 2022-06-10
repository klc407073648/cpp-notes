#include <iostream>
#include <unordered_map>
#include <tuple>

void c11_fun()
{
	auto student = std::make_tuple(std::string{"YongDu"}, 26, std::string{"man"});
	std::string name;
	size_t age;
	std::string gender;
	std::tie(name, age, gender) = student;
	std::cout << name << ", " << age << ", " << gender << std::endl;
}

struct Student
{
	std::string name;
	size_t age;
};

Student getStudent() { return {"dycc", 26}; }

void c17_fun()
{
	auto student = std::make_tuple(std::string{"YongDu"}, 26, std::string{"man"});
	auto [name, age, gender] = student;
	std::cout << name << ", " << age << ", " << gender << std::endl;
	// YongDu, 26, man

	std::unordered_map<std::string, size_t> students;
	students.emplace(std::make_pair("DuYong", 26));
	students.emplace(std::make_pair("YongDu", 26));

	for (auto &[name, age] : students)
	{
		std::cout << name << ", " << age << std::endl;
	}

	auto [_name, _age] = getStudent();
	std::cout << _name << ", " << _age << std::endl;
}

int main()
{
	c11_fun();
	c17_fun();

	return 0;
}