#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void testFun()
{
	vector<int> vec;
	cout << "————————————————————插入操作—————————————————" << endl;
	for (int i = 0; i < 10; i++)
	{
		vec.push_back(i);
	}

	cout << "push_back() 0-9" << endl;

	cout << "————————————————————遍历操作—————————————————" << endl;
	for (vector<int>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;

	cout << "————————————————————删除操作—————————————————" << endl;

	while (!vec.empty())
	{
		vec.pop_back();
	}

	cout << "pop_back() all nums" << endl;

	cout << "————————————————————容量查询—————————————————" << endl;

	cout << "vec empty state is " << boolalpha << vec.empty() << endl;

	cout << "vec size is " << boolalpha << vec.size() << endl;

	cout << "————————————————————插入操作—————————————————" << endl;

	int myarray[] = {5, 2, 4, -1, 2, 1, 10,5};
	vec.insert(vec.begin(), myarray, myarray + 8);

	cout << "insert() {5, 2, 4, -1, 2, 1, 10,5}" << endl;

	for (vector<int>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;

	cout << "————————————————————算法操作—————————————————" << endl;
	sort(vec.begin(), vec.end());
	cout << "after sort" << endl;

	for (vector<int>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;

	vector<int>::iterator new_end = unique(vec.begin(), vec.end());
	vec.erase(new_end, vec.end());

	cout << "after unique " << endl;

	for (vector<int>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;
}

int main()
{
	testFun();
	return 0;
}