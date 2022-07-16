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
	
	cout<<"————————————————————查找操作—————————————————"<<endl;
	iter = stuMap.find(1001);
	if (iter != stuMap.end())
		cout <<"stuMap.find(1001) name:"<< iter->second << endl;
	
        
    return 0;
}