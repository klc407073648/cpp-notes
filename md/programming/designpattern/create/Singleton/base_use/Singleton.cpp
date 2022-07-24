#include "Singleton.h"
#include <iostream>

Singleton* Singleton::_instance = 0;

Singleton::Singleton()
{
	cout<<"Singleton()"<<endl;
}

/* Singleton::~Singleton()
{
	cout<<"~Singleton()"<<endl;
} */

Singleton* Singleton::getInstance()
{
	if (_instance == 0)
	{
		_instance = new Singleton();
	}
	
	return _instance;
}