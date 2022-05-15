#include "Singleton.h"
#include <iostream>

using namespace std;

int main()
{
	workerPtr::getInstance()->myWorkFun();
	
	return 0;
}