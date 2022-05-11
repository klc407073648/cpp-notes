#include <iostream>
#include <string.h>
#include <stdarg.h>

using namespace std;

/*
vasprintf()函数 :int vasprintf (char **buf, const char *format, va_list ap)
将格式化数据从可变参数列表写入缓冲区
*/
std::string  execute(const char* format, va_list ap);

void myFun1(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    execute(format, ap);
    va_end(ap);
}

std::string  execute(const char* format, va_list ap)
{
	char* buf = nullptr;
    auto len = vasprintf(&buf, format, ap);
    if(len == -1) {
        return "";
    }
    std::string ret(buf, len);
	cout<<"ret:"<<ret<<endl;
    free(buf);
    return ret;
}

int myFun2(int count, ...)
{
    va_list ap; 
    va_start(ap, count);
    cout << "count: "<< count << endl;
    int sumNum = 0;
   
	for(int i=0 ; i< count ;i++)
	{
		sumNum+=va_arg(ap, int);
	}

    va_end(ap);
	
    return sumNum;
}


int main()
{
	int  num = 100;
	char character = 'A';
	string str="mystring";
    myFun1("Test va_list_Fun num:%d character:%c str:%s",num,character,str.c_str());
	
	int count = 5;
	int sumNum = myFun2(count,1,2,3,4,5);
	cout << "sumNum: "<< sumNum << endl;
    return 0;
}

