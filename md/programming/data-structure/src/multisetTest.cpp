#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

void testFun()
{
	int myints[] = {15, 98, 77, 77, 39};

	std::multiset<int> mymultiset(myints, myints + 5);
	std::multiset<int>::iterator it;

	std::cout << "mymultiset contains:";
	for (std::multiset<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << std::endl;

	std::cout << "mymultiset.count(77):" << mymultiset.count(77) << std::endl;
	std::cout << "mymultiset.size():" << mymultiset.size() << std::endl;

	mymultiset.erase(77);
	std::cout << "after erase mymultiset.size():" << mymultiset.size() << std::endl;

	std::cout << "mymultiset contains:";
	for (std::multiset<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << std::endl;
}

int main()
{
	testFun();
	return 0;
}