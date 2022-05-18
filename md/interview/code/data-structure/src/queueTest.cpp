#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

void testFun()
{
	std::queue<int> myqueue;

	myqueue.push(30);
	myqueue.push(100);
	myqueue.push(25);
	myqueue.push(40);

	std::cout << "push 30 100 25 40 to myqueue" << std::endl;
	std::cout << "myqueue.front() is " << myqueue.front() << std::endl;
	std::cout << "myqueue.back() is " << myqueue.back() << std::endl;

	if (!myqueue.empty())
	{
		std::cout << "myqueue.empty() is " << myqueue.empty() << std::endl;
		std::cout << "myqueue.size() is " << myqueue.size() << std::endl;
	}

	myqueue.pop();

	std::cout << "myqueue.pop()" << std::endl;

	std::cout << "current mypq.top() is " << myqueue.front() << std::endl;
}

void testEmplace()
{
	std::queue<std::string> myqueue;

	myqueue.emplace("First sentence");
	myqueue.emplace("Second sentence");

	std::cout << "myqueue contains:";
	while (!myqueue.empty())
	{
		std::cout << myqueue.front();
		myqueue.pop();
	}

	std::cout << std::endl;
}

void testSwap()
{
	std::queue<int> foo, bar;
	foo.push(10);
	foo.push(20);
	foo.push(30);
	foo.push(40);
	bar.push(111);
	bar.push(222);

	std::cout << "size of foo(before swap): " << foo.size() << std::endl;
	std::cout << "size of bar(before swap): " << bar.size() << std::endl;

	foo.swap(bar);

	std::cout << "size of foo(after swap): " << foo.size() << std::endl;
	std::cout << "size of bar(after swap): " << bar.size() << std::endl;
}

int main()
{
	testFun();
	testEmplace();
	testSwap();
	return 0;
}