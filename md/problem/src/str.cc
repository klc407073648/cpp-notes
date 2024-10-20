#include <stdio.h>
#include <iostream>
#include <string>

int main()
{
  std::string str1="\320\000\120";  //011010000      010100000000111 001 010 000
  printf("str1 size:[%d], val:[%s]\n", str1.size(), str1.c_str());//5246544
  
  char arr[1024]="\320\000\120";
  std::string str2=arr;
  printf("str2 size:[%d], val:[%d]\n", str2.size(), str2.c_str());
  
  std::string str3 = std::string(arr,3);//指定对应长度，才不会因为八进制的空字符串“\000”截断
  printf("str3 size:[%d], val:[%s]\n", str3.size(), str3.c_str());
  
  return 0;
}