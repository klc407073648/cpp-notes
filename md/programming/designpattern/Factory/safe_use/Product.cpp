#include "Product.h"
#include <iostream>
using namespace std;

Product::Product()
{
	cout << "Product...." << endl;
}

Product::~Product()
{
	cout << "~Product...." << endl;
}

ConcreteProduct::ConcreteProduct()
{
	cout << "ConcreteProduct...." << endl;
}

ConcreteProduct::~ConcreteProduct()
{
	cout << "~ConcreteProduct...." << endl;
}