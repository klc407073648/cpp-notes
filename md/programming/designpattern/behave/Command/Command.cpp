#include "Command.h"
#include "Reciever.h"

Command::Command()
{
}

Command::~Command()
{
}

void Command::Excute()
{
}

ConcreteCommandA::ConcreteCommandA(Reciever *rev)
{
    this->_rev = rev;
}

ConcreteCommandA::~ConcreteCommandA()
{
}

void ConcreteCommandA::Excute()
{
    cout << "ConcreteCommandA Excute" << endl;
    _rev->Action();
}

ConcreteCommandB::ConcreteCommandB(Reciever *rev)
{
    this->_rev = rev;
}

ConcreteCommandB::~ConcreteCommandB()
{
}

void ConcreteCommandB::Excute()
{
    cout << "ConcreteCommandB Excute" << endl;
    _rev->Action();
}