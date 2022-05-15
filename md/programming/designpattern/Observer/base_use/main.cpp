#include "Subject.h"
#include "Observer.h"
#include <iostream>
using namespace std;
int main(int argc,char* argv[])
{
	Subject* sub = new ConcreteSubject();
	Observer* o1 = new ConcreteObserverA(sub);
	Observer* o2 = new ConcreteObserverB(sub);
	
	sub->SetState("old");
	sub->Notify();
	sub->SetState("new"); // 也可以由Observer 调用
	sub->Notify();
	
	return 0;
}