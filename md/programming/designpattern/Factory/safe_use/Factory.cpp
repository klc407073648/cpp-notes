#include "Factory.h"
#include "Product.h"
#include <iostream>

using namespace std;

Factory::Factory()
{
	cout << "Factory....." << endl;
}

Factory::~Factory()// 纯虚函数事实上也能够有他自己的实现
{
	cout << "~Factory....." << endl;
}

ConcreteFactory::ConcreteFactory()
{
	cout << "ConcreteFactory....." << endl;
}

ConcreteFactory::~ConcreteFactory()
{
    cout << "~ConcreteFactory....." << endl;
}

Product *ConcreteFactory::CreateProduct()
{
	return new ConcreteProduct();
}
