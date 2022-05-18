/*
在C++ STL中，push_back()函数向容器中加入一个临时对象（右值元素）时，首先会调用构造函数生成这个对象，然后调用拷贝构造函数将这个对象放入容器中，最后释放临时对象。
而emplace_back()函数向容器中加入临时对象，临时对象原地构造，没有拷贝或移动的操作，所以效率比较高。

g++ priority_queueTest.cpp -o priority_queueTest -std=c++11
*/

// priority_queue::top
#include <iostream> // std::cout
#include <queue>	// std::priority_queue
#include <vector>
#include <algorithm>

using namespace std;

void testFun()
{
	std::priority_queue<int> mypq;

	mypq.push(30);
	mypq.push(100);
	mypq.push(25);
	mypq.push(40);

	std::cout << "push 30 100 25 40 to mypq" << std::endl;
	std::cout << "mypq.top() is now " << mypq.top() << std::endl;

	if (!mypq.empty())
	{
		std::cout << "mypq.empty() is " << mypq.empty() << std::endl;
		std::cout << "mypq.size() is " << mypq.size() << std::endl;
	}

	mypq.pop();

	std::cout << "mypq.pop()" << std::endl;

	std::cout << "current mypq.top() is " << mypq.top() << std::endl;
}

void testSmallHeap()
{
	std::priority_queue<int, vector<int>, greater<int>> small_heap;

	small_heap.push(30);
	small_heap.push(100);
	small_heap.push(25);
	small_heap.push(40);

	std::cout << "push 30 100 25 40 to small_heap" << std::endl;
	std::cout << "small_heap.top() is now " << small_heap.top() << std::endl;
}

void testEmplace()
{
	std::priority_queue<std::string> mypq;

	mypq.emplace("orange");
	mypq.emplace("strawberry");
	mypq.emplace("apple");
	mypq.emplace("pear");

	std::cout << "mypq contains:";
	while (!mypq.empty())
	{
		std::cout << ' ' << mypq.top();
		mypq.pop();
	}
	std::cout << std::endl;
}

void testSwap()
{
	std::priority_queue<int> foo, bar;
	foo.push(15);
	foo.push(30);
	foo.push(10);
	bar.push(101);
	bar.push(202);

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
	testSmallHeap();
	return 0;
}