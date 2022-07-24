#include "Abstraction.h"
#include "AbstractionImp.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	AbstractionImp *imp = new ConcreteAbstractionImpA();
	Abstraction *abs = new RefinedAbstraction(imp);
	abs->Operation();

	imp = new ConcreteAbstractionImpB();
	abs = new RefinedAbstraction(imp);
	abs->Operation();

	return 0;
}