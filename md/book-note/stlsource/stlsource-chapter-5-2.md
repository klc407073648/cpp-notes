# 第五章：关联式容器 set和 map

[[toc]]

# set概述
 set的特性是，所有元素都会根据元素的键值自动排序，set的元素不像map那样可以同时拥有实值和键值，**set元素的键值就是实值，实值就是键值，且不允许两个元素有相同的键值**。set具有以下特点：

* 不能通过set的迭代器改变set的元素，setiterators是一种constant iterators。
* 客户端对set进行元素新增或者删除操作时，操作之前的所有迭代器在操作后都依然有效，被删除的元素的迭代器例外。
* STL set以RB-tree为底层机制，set的操作几乎都是转调用RB-tree的函数而已。

## set测试程序

```cpp
// file: 5set-test.cpp

#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int i;
    int ia[5] = {0, 1, 2, 3, 4};
    set<int> iset{ia, ia + 5};

    cout << "size=" << iset.size() << endl;         //size=5
    cout << "3 count =" << iset.count(3) << endl;   //3 count =1
    iset.insert(3);
    cout << "size=" << iset.size() << endl;         //size=5
    cout << "3 count =" << iset.count(3) << endl;   //3 count =1

    iset.insert(5);
    cout << "size=" << iset.size() << endl;         //size=6
    cout << "5 count =" << iset.count(5) << endl;   //5 count =1

    iset.erase(1);
    cout << "size=" << iset.size() << endl;        //size=5
    cout << "3 count =" << iset.count(3) << endl;  //3 count =1
    cout << "1 count =" << iset.count(1) << endl;  //1 count =0

    set<int>::iterator ite1 = iset.begin();
    set<int>::iterator ite2 = iset.end();
    for (; ite1 != ite2; ++ite1) {
        cout << *ite1;                             //02345
    }
    cout << endl;

    // 使用STL算法find可以搜索元素，但不推荐
    ite1 = find(iset.begin(), iset.end(), 3);
    if (ite1 != iset.end())
        cout << "3 found" << endl;                //3 found

    ite1 = find(iset.begin(), iset.end(), 1);
    if (ite1 == iset.end())
        cout << "1 not found" << endl;            //1 not found

    // 关联式容器应使用专用的find函数搜索更有效率
    ite1 = iset.find(3);
    if (ite1 != iset.end())
        cout << "3 found" << endl;                //3 found

    ite1 = iset.find(1);
    if (ite1 == iset.end())
        cout << "1 not found" << endl;            //1 not found

    // *ite1 = 9; // 修改失败
}
```

## multiset

multiset的特性及用法和set完全相同，唯一的差别在于它允许键值重复，因为它的插入操作采用的是RB-tree的insert_equal()。

测试程序：

```cpp
#include<set>
#include<iostream>
using namespace std;
 
int main(){
	int ia[] = { 5, 3, 4, 1, 6, 2 };
	multiset<int> iset(begin(ia), end(ia));
 
	cout << "size=" << iset.size() << endl; //size=6
	cout << "3 count=" << iset.count(3) << endl;//3 count=1
 
	iset.insert(3); //和set区别的地方
	cout << "size=" << iset.size() << endl;//size=7
	cout << "3 count=" << iset.count(3) << endl;//3 count=2
 
	iset.insert(7);
	cout << "size=" << iset.size() << endl;//size=8
	cout << "3 count=" << iset.count(3) << endl;//3 count=2
 
	iset.erase(1);
	cout << "size=" << iset.size() << endl;//size=7
	cout << "1 count=" << iset.count(1) << endl;//1 count=0
 
	set<int>::iterator it;
	for (it = iset.begin(); it != iset.end(); ++it)
		cout << *it << " "; //2 3 3 4 5 6 7
	cout << endl;
 
	it = iset.find(3);
	if (it != iset.end())
		cout << "3 found" << endl;//3 found
 
	it = iset.find(1);
	if (it == iset.end())
		cout << "1 not found" << endl;//1 not found 
 
	return 0;
}
```

# map概述

map的特性是，**所有元素都会根据元素的键值自动排序，map的所有元素都是pair**，pair的第一元素是键值，第二元素是实值。

map具有以下特点：

* 不能通过map的迭代器改变map的键值，但通过map的迭代器能改变map的实值。因此map的iterators既不是一种const iterators，也不是一种mutable iterators。
* 客户端对map进行元素新增或者删除操作时，操作之前的所有迭代器在操作后都依然有效，被删除的元素的迭代器例外。
* STL map以RB-tree为底层机制，map的操作几乎都是转调用RB-tree的函数而已。

## map测试程序

```cpp
#include <map>
#include <iostream>
#include <string>

using namespace std;

int main() {
    map<int, string> stuMap;
    
	cout<<"————————————————————插入操作—————————————————"<<endl;
	stuMap[1001]="Jason";
	stuMap.insert(pair<int, string>(1002,"Helen"));
	stuMap.insert(make_pair(1003,"Steve"));

    map<int, string>::const_iterator iter = stuMap.begin();
    for (; iter != stuMap.end(); ++iter)
	{
		cout <<"id:"<< iter->first <<" name:"<< iter->second << endl;
	}
	cout<<"————————————————————取值操作—————————————————"<<endl;
	
	cout <<"stuMap[1004]:"<<stuMap[1004]<<endl;
	
	//使用at会进行关键字检查，因此下面语句会报错
	//stuMap.at(1005) = "Bob";
	cout<<"————————————————————查找操作—————————————————"<<endl;
	iter = stuMap.find(1001);
	if (iter!=stuMap.end())
	{
		cout <<"1001 found name:"<<iter->second<<endl;
	}
	
	iter = stuMap.find(1005);
	if ( iter==stuMap.end())
	{
		cout <<"1005 not found"<<endl;
	}
	
	cout<<"————————————————————容量查询—————————————————"<<endl;
	
	cout<<"stuMap empty state is "<<boolalpha<<stuMap.empty()<<endl;
	
	cout<<"stuMap size is "<<boolalpha<<stuMap.size()<<endl;
	
	cout<<"stuMap.count(1008) is "<<boolalpha<<stuMap.count(1008)<<endl;
	
	cout<<"————————————————————删除操作—————————————————"<<endl;
	cout<<"before delete"<<endl;
	iter = stuMap.begin();
    for (; iter != stuMap.end(); ++iter)
	{
		cout <<"id:"<< iter->first <<" name:"<< iter->second << endl;
	}
	
	stuMap.erase(1004);
	
	iter = stuMap.begin();
    for (; iter != stuMap.end(); ++iter)
	{
		if(iter->second=="Helen")	
		{
			stuMap.erase(iter);
			break;
		}
	}
	
	cout<<"after delete"<<endl;
	iter = stuMap.begin();
    for (; iter != stuMap.end(); ++iter)
	{
		cout <<"id:"<< iter->first <<" name:"<< iter->second << endl;
	}
        
    return 0;
}

```

执行结果：

```bash
[root@192 5_STL_associated_container]# ./5_4_map-test
————————————————————插入操作—————————————————
id:1001 name:Jason
id:1002 name:Helen
id:1003 name:Steve
————————————————————取值操作—————————————————
stuMap[1004]:
————————————————————查找操作—————————————————
1001 found name:Jason
1005 not found
————————————————————容量查询—————————————————
stuMap empty state is false
stuMap size is 4
stuMap.count(1008) is 0
————————————————————删除操作—————————————————
before delete
id:1001 name:Jason
id:1002 name:Helen
id:1003 name:Steve
id:1004 name:
after delete
id:1001 name:Jason
id:1003 name:Steve
```

## multiset

multimap的特性及用法和map完全相同，唯一的差别在于它允许键值重复，因为它的插入操作采用的是RB-tree的insert_equal()。

测试程序：

```cpp
#include<map>
#include<string>
#include<iostream>
using namespace std;
 
int main(){
	multimap<string, int> mp;//multimap没有下标操作
	mp.insert(pair<string, int>("Jason", 1));
	mp.insert(pair<string, int>("Steve", 2));
	mp.insert(pair<string, int>("Helen", 3));
	mp.insert(pair<string, int>("Tom", 5));              
	mp.insert(pair<string, int>("Jason", 8));             
	                                                      
	map<string, int>::iterator it;                      
	for (it = mp.begin(); it != mp.end(); ++it)         
		cout <<"name: "<<it->first << " num:" << it->second << endl; 
 
	it = mp.find("Helen");
	if (it != mp.end())
	{
		cout << "Helen found" << endl; 
		it->second = 8;
	}
 
	it = mp.find("Helen");
	cout <<"find Helen num:"<< it->second << endl;  
 
	return 0;
}
```

执行结果：

```bash
[root@192 5_STL_associated_container]# ./multimap
name: Helen num:3
name: Jason num:1
name: Jason num:8
name: Steve num:2
name: Tom num:5
Helen found
find Helen num:8
```