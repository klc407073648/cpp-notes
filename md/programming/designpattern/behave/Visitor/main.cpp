#include "Element.h"
#include "Visitor.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	Visitor *vis = new ConcreteVisitorA();
	Element *elm = new ConcreteElementA();
	elm->Accept(vis);
	return 0;
}