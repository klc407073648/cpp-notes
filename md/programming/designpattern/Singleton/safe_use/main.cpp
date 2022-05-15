#include "Singleton.h"
#include <iostream>

using namespace std;

int main()
{
	Singleton::Ptr m_singleton = Singleton::getInstance();
	
	return 0;
}