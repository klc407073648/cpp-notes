#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

void testFun()
{
	std::stack<int> mystack;

	for (int i = 0; i < 5; ++i)
		mystack.push(i);

	for (int i = 5; i < 10; ++i)
		mystack.emplace(i);

	std::cout << "mystack.empty():" << mystack.empty() << std::endl;
	std::cout << "mystack.size():" << mystack.size() << std::endl;

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}

	std::cout << std::endl;
}

int main()
{
	testFun();
	return 0;
}