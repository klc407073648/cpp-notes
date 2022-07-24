#include "AdapterObject.h"
#include <iostream>

TargetObject::TargetObject()
{
}

TargetObject::~TargetObject()
{
}

void TargetObject::Request()
{
    std::cout << "Target::Request" << std::endl;
}

AdapteeObject::AdapteeObject()
{
}

AdapteeObject::~AdapteeObject()
{
}

void AdapteeObject::SpecificRequest()
{
    std::cout << "Adaptee::SpecificRequest" << std::endl;
}

AdapterObject::AdapterObject(AdapteeObject *ade)
{
    this->_ade = ade;
}

AdapterObject::~AdapterObject()
{
}

void AdapterObject::Request()
{
    _ade->SpecificRequest();
}
