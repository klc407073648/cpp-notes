#include "Mediator.h"
#include "Colleage.h"

Mediator::Mediator()
{
}

Mediator::~Mediator()
{
}

ConcreteMediator::ConcreteMediator()
{
}

ConcreteMediator::~ConcreteMediator()
{
}

ConcreteMediator::ConcreteMediator(Colleage *clgA, Colleage *clgB)
{
    this->_clgA = clgA;
    this->_clgB = clgB;
}

void ConcreteMediator::DoActionFromAtoB()
{
    _clgB->SetState(_clgA->GetState());
}

void ConcreteMediator::SetConcreteColleageA(Colleage *clgA)
{
    this->_clgA = clgA;
}

void ConcreteMediator::SetConcreteColleageB(Colleage *clgB)
{
    this->_clgB = clgB;
}

Colleage *ConcreteMediator::GetConcreteColleageA()
{
    return _clgA;
}

Colleage *ConcreteMediator::GetConcreteColleageB()
{
    return _clgB;
}

void ConcreteMediator::IntroColleage(Colleage *clgA, Colleage *clgB)
{
    this->_clgA = clgA;
    this->_clgB = clgB;
}

void ConcreteMediator::DoActionFromBtoA()
{
    _clgA->SetState(_clgB->GetState());
}