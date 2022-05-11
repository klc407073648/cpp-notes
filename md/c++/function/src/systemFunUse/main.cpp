#include <iostream>
#include "util.h"
using namespace std;


int main()
{
   ShellUtil::execShell("touch klc.txt");
   ShellUtil::execShell("chmod 777 klc.txt");
   //string str=ShellUtil::execShellPipe("ls -al >> klc.txt");
   string str=ShellUtil::execShellPipe("ls -al ");
   cout<<ShellUtil::getParamValue("name","my.conf");
   cout<<ShellUtil::getParamValue("age","my.conf");
   ShellUtil::modParamValue("age","44","my.conf");
   cout<<ShellUtil::getParamValue("age","my.conf");
   //cout<<str<<endl;
    return 0;
}

