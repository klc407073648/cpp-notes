#include <iostream>
#include <memory>

using namespace std;

//一维数组
typedef int intArr[10];
typedef std::string stringArr[20];

//二维数组
typedef int matrix[5][5];
typedef char nameTable[3][3];

//对已有类型定义别名
typedef int inData;
typedef char chData;


int main()
{
    intArr mIntArr = {1,2,3,4,5};
	stringArr mStrArr = { "hello","world"};
	
    for(int i=0 ;i< sizeof(mIntArr)/sizeof(int);i++)
	{
		if (mStrArr[i]=="") break;
		cout<<i <<"th mIntArr is "<<mIntArr[i]<<endl;
	}
	
	for(int i=0 ;i< sizeof(mStrArr)/sizeof(std::string);i++)
	{
		if (mStrArr[i]=="") break;
		cout<<i <<"th mStrArr is "<<mStrArr[i]<<endl;
	}
	
	cout<<"————————————————————————————————————————"<<endl;
	
	matrix mMat ={{1,2,3,4,5},{6,7,8,9,10},{11,12,13}};
	for(int i=0 ;i<5;i++)
	{
		for(int j=0 ;j<5;j++)
		{
			if (mMat[i][j]==0) break;
			cout<<"mMat["<<i<<"]["<<j<<"]:"<<mMat[i][j]<<endl;
		}
	}
	nameTable mNameTable ={{'a','b','c'},{'d','e','f'},{'g','h'}};
	
	for(int i=0 ;i<3;i++)
	{
		for(int j=0 ;j<3;j++)
		{
			if (mNameTable[i][j]==' ') break;
			cout<<"mNameTable["<<i<<"]["<<j<<"]:"<<mNameTable[i][j]<<endl;
		}
	}
	
	cout<<"————————————————————————————————————————"<<endl;
	inData m_int =100;
	chData m_char ='Z';
	
	cout<<"m_int is "<<m_int<<endl;
	cout<<"m_char is "<<m_char<<endl;
	
    return 0;
}