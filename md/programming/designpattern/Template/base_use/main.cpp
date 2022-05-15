#include "Template.h"
#include <iostream>
using namespace std;
int main()
{
	TemplateBase* p1 = new Template1();
	TemplateBase* p2 = new Template2();

	p1->TemplateMethod();
	p2->TemplateMethod();

	return 0;
}