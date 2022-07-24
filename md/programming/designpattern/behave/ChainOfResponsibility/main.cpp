#include "Handle.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	Handle *h1 = new ConcreteHandleA();
	Handle *h2 = new ConcreteHandleB();
	h1->SetSuccessor(h2);
	h1->HandleRequest();
	return 0;
}