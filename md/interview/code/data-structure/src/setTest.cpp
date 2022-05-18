#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

void testFun()
{
	std::cout << "testFun() begin" << std::endl;

	std::set<int> myset;
	std::set<int>::iterator it;
	std::pair<std::set<int>::iterator, bool> ret;

	// set some initial values:
	for (int i = 1; i <= 5; ++i)
		myset.insert(i * 10); // set: 10 20 30 40 50

	ret = myset.insert(20); // no new element inserted

	if (ret.second == false)
		it = ret.first; // "it" now points to element 20

	myset.insert(it, 25); // max efficiency inserting
	myset.insert(it, 24); // max efficiency inserting
	myset.insert(it, 26); // no max efficiency inserting

	int myints[] = {5, 10, 15}; // 10 already in set, not inserted
	myset.insert(myints, myints + 3);

	std::cout << "myset contains:";
	for (it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	it = myset.find(25);
	myset.erase(it, myset.end());

	std::cout << "after erase myset contains:";
	for (it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	std::cout << "myset.count(5):" << myset.count(5) << std::endl;
	std::cout << "myset.size():" << myset.size() << std::endl;

	std::cout << "testFun() end" << std::endl;
}

void testEmplace()
{
	std::cout << "testEmplace() begin" << std::endl;

	std::set<std::string> myset;

	myset.emplace("foo");
	myset.emplace("bar");
	auto ret = myset.emplace("foo");

	if (!ret.second)
		std::cout << "foo already exists in myset"<< std::endl;

	auto it = myset.cbegin();

	myset.emplace_hint(it, "alpha");
	it = myset.emplace_hint(myset.cend(), "omega");
	it = myset.emplace_hint(it, "epsilon");
	it = myset.emplace_hint(it, "beta");

	std::cout << "myset contains:";
	for (const std::string &x : myset)
		std::cout << ' ' << x;
	std::cout << std::endl;

	std::cout << "testEmplace() end" << std::endl;
}

void testBound()
{
	std::cout << "testBound() begin" << std::endl;

	std::set<int> myset;
	std::set<int>::iterator itlow, itup;

	for (int i = 1; i < 10; i++)
		myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

	itlow = myset.lower_bound(30); //       ^
	itup = myset.upper_bound(60);  //                   ^

	myset.erase(itlow, itup); // 10 20 70 80 90

	std::cout << "myset contains:";
	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	std::cout << "testBound() end" << std::endl;
}

void testSwap()
{
	std::cout << "testSwap() begin" << std::endl;

	int myints[] = {12, 75, 10, 32, 20, 25};
	std::set<int> first(myints, myints + 3);	  // 10,12,75
	std::set<int> second(myints + 3, myints + 6); // 20,25,32

	std::cout << "first contains(before swap):";
	for (std::set<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	std::cout << "second contains(before swap):";
	for (std::set<int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	//
	first.swap(second);

	std::cout << "first contains(after swap):";
	for (std::set<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	std::cout << "second contains(after swap):";
	for (std::set<int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	std::cout << "testSwap() end" << std::endl;
}

int main()
{
	testFun();
	testEmplace();
	testBound();
	testSwap();
	return 0;
}