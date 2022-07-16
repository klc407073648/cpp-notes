#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

void testFun()
{
	std::multimap<char, int> mymultimap;
	std::multimap<char, int>::iterator it;

	// first insert function version (single parameter):
	mymultimap.insert(std::pair<char, int>('a', 100));
	mymultimap.insert(std::pair<char, int>('z', 150));
	it = mymultimap.insert(std::pair<char, int>('b', 75));

	// second insert function version (with hint position):
	mymultimap.insert(it, std::pair<char, int>('c', 300)); // max efficiency inserting
	mymultimap.insert(it, std::pair<char, int>('z', 400)); // no max efficiency inserting

	// third insert function version (range insertion):
	std::multimap<char, int> anothermultimap;
	anothermultimap.insert(mymultimap.begin(), mymultimap.find('c'));

	// showing contents:
	std::cout << "mymultimap contains:\n";
	for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << std::endl;
	;

	std::cout << "anothermultimap contains:\n";
	for (it = anothermultimap.begin(); it != anothermultimap.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << std::endl;
	;

	std::cout << "mymultimap.count('z'):" << mymultimap.count('z') << std::endl;
	std::cout << "mymultimap.size():" << mymultimap.size() << std::endl;

	mymultimap.erase('z');
	std::cout << "after erase mymultimap.size():" << mymultimap.size() << std::endl;
}

void testEmplace()
{
	std::multimap<std::string, float> mymultimap;

	mymultimap.emplace("apple", 1.50);
	mymultimap.emplace("coffee", 2.10);
	mymultimap.emplace("apple", 1.40);

	std::cout << "mymultimap contains:";
	for (auto &x : mymultimap)
		std::cout << " [" << x.first << ':' << x.second << ']';
	std::cout << std::endl;
}

int main()
{
	testFun();
	testEmplace();
	return 0;
}