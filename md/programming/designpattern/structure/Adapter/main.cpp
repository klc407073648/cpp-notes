#include "Adapter.h"
#include "AdapterObject.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	Target *adt = new Adapter();
	adt->Request();

	AdapteeObject *ade = new AdapteeObject();
	TargetObject *adtObject = new AdapterObject(ade);
	adtObject->Request();

	return 0;
}