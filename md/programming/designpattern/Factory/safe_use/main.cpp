#include "Factory.h"
#include "Product.h"
#include <iostream>

using namespace std;

int main()
{
	Factory* fac = new ConcreteFactory();
	Product* p = fac->CreateProduct();
	
	delete p;
	delete fac;

	return 0;
}
