# rpc开发程序

[[toc]]

## 客户端

```cpp
#include <string>
#include <iostream>
#include <ctime>
#include "buttonrpc.hpp"
#include <stdio.h>

class Student
{
public:
	std::string toString(std::string name, int age, std::string address)
	{
		std::cout << "call Student::toString" << std::endl;
		return "name:" + name + " age:" + std::to_string(age) + " address:" + address;
	}
};

struct PersonInfo
{
	int age;
	std::string name;
	float height;

	// must implement
	friend Serializer &operator>>(Serializer &in, PersonInfo &d)
	{
		in >> d.age >> d.name >> d.height;
		return in;
	}
	friend Serializer &operator<<(Serializer &out, PersonInfo d)
	{
		out << d.age << d.name << d.height;
		return out;
	}
};

int main()
{
	buttonrpc client;
	client.as_client("127.0.0.1", 5555);
	client.set_timeout(2000);

	client.call<void>("testFun");

	client.call<void>("testInputValue", 20);

	int addResult = client.call<int>("testAdd", 10, 20).val();
	std::cout << "addResult: " << addResult << std::endl;

	Student stu;

	std::string retString = client.call<std::string>("toString", "Jason", 24, "NJ").val();

	std::cout << "retString: " << retString << std::endl;

	PersonInfo person = {10, "buttonrpc", 170};
	person = client.call<PersonInfo>("personFun", person, 10).val();

	std::cout << "person age: " << person.age << std::endl;
	std::cout << "person name: " << person.name << std::endl;
	std::cout << "person height: " << person.height << std::endl;

	value_t<void> testValue_t = client.call<void>("foo_7", 111, 222, 333);
	std::cout << "testValue_t val: " << testValue_t.val() << std::endl;
	std::cout << "testValue_t code: " << testValue_t.error_code() << std::endl;
	std::cout << "testValue_t msg: " << testValue_t.error_msg() << std::endl;

	return 0;
}

```

## 服务端

```cpp
#include <string>
#include <iostream>
#include "buttonrpc.hpp"

// 测试例子
void testFun()
{
	std::cout << "call testFun" << std::endl;
}

void testInputValue(int arg)
{
	std::cout << "call testInputValue" << std::endl;
}

int testAdd(int a, int b)
{
	std::cout << "call testAdd " << std::endl;
	return a + b;
}

class Student
{
public:
	std::string toString(std::string name, int age, std::string address)
	{
		std::cout << "call Student::toString" << std::endl;
		return "name:" + name + " age:" + std::to_string(age) + " address:" + address;
	}
};

struct PersonInfo
{
	int age;
	std::string name;
	float height;

	// must implement
	friend Serializer &operator>>(Serializer &in, PersonInfo &d)
	{
		in >> d.age >> d.name >> d.height;
		return in;
	}
	friend Serializer &operator<<(Serializer &out, PersonInfo d)
	{
		out << d.age << d.name << d.height;
		return out;
	}
};

PersonInfo personFun(PersonInfo d, int hight)
{
	std::cout << "call personFun" << std::endl;
	PersonInfo ret;
	ret.age = d.age + 10;
	ret.name = d.name + " is good";
	ret.height = d.height + hight;
	return ret;
}

int main()
{
	buttonrpc server;
	server.as_server(5555);

	server.bind("testFun", testFun);
	server.bind("testInputValue", testInputValue);
	server.bind("testAdd", std::function<int(int, int)>(testAdd));

	Student stu;
	server.bind("toString", &Student::toString, &stu);

	server.bind("personFun", personFun);

	std::cout << "run rpc server on: " << 5555 << std::endl;
	server.run();

	return 0;
}

```