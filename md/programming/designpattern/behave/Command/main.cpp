#include "Reciever.h"
#include "Invoke.h"
#include "Command.h"

int main(int argc, char *argv[])
{
	Reciever *pstReceiver = new Reciever();
	Command *pstConcreteCommandA = new ConcreteCommandA(pstReceiver);
	Command *pstConcreteCommandB = new ConcreteCommandB(pstReceiver);
	Invoker *pstInvoke = new Invoker();

	pstInvoke->Add(pstConcreteCommandA);
	pstInvoke->Add(pstConcreteCommandA);
	pstInvoke->Add(pstConcreteCommandB);
	pstInvoke->Notify();
	cout << "------------------" << endl;

	pstInvoke->Remove(pstConcreteCommandA); //撤销操作
	// pstInvoke->Remove(pstConcreteCommandB);
	pstInvoke->Notify();
	cout << "------------------" << endl;

	return 0;
}