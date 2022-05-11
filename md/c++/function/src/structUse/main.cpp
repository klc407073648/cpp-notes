#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;

struct userInfo
{
    string userName;     
    int age;
	string address;
	
	userInfo():
	userName("null"),
	age(0),
	address("null")
	{}
	
	userInfo(const string& m_userName,int m_age,const string& m_address):
	userName(m_userName),
	age(m_age),
	address(m_address)
	{}
};

struct Day
{
   explicit Day(int d)
	       :val(d)
			{}
   int val;
};


int main()
{
	userInfo m_userInfo("jason",26,"Nanjing");
	Day m_Day(20.2);
	
	printf("userInfo userName:%s,age:%d,address:%s\n",m_userInfo.userName.c_str(),m_userInfo.age,m_userInfo.address.c_str());
	printf("m_Day:%d\n",m_Day.val);
	return 0;
}