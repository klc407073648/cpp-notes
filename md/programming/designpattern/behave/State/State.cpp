#include "State.h"
#include "Context.h"
#include <iostream>
using namespace std;

State::State()
{
}

State::~State()
{
}

void State::OperationInterface(Context *con)
{
    cout << "State::.." << endl;
}

bool State::ChangeState(Context *con, State *st)
{
    con->ChangeState(st);
    return true;
}

void State::OperationChangeState(Context *con)
{
}

ConcreteStateA::ConcreteStateA()
{
}

ConcreteStateA::~ConcreteStateA()
{
}

void ConcreteStateA::OperationInterface(Context *con)
{
    cout << "ConcreteStateA::OperationInterface...... " << endl;
}

void ConcreteStateA::OperationChangeState(Context *con)
{
    OperationInterface(con);
    this->ChangeState(con, new ConcreteStateB());
}

ConcreteStateB::ConcreteStateB()
{
}

ConcreteStateB::~ConcreteStateB()
{
}

void ConcreteStateB::OperationInterface(Context *con)
{
    cout << "ConcreteStateB::OperationInterface...... " << endl;
}

void ConcreteStateB::OperationChangeState(Context *con)
{
    OperationInterface(con);
    this->ChangeState(con, new ConcreteStateA());
}