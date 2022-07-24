#include "Decorator.h"
#include <iostream>

Component::Component()
{
}

Component::~Component()
{
}

void Component::Operation()
{
}

ConcreteComponent::ConcreteComponent()
{
}

ConcreteComponent::~ConcreteComponent()
{
}

void ConcreteComponent::Operation()
{
    std::cout << "ConcreteComponent operation... " << std::endl;
}

Decorator::Decorator(Component *com)
{
    this->_com = com;
}

Decorator::~Decorator()
{
    delete _com;
}

void Decorator::Operation()
{
}

ConcreteDecorator::ConcreteDecorator(Component *com) : Decorator(com)
{
}

ConcreteDecorator::~ConcreteDecorator()
{
}

void ConcreteDecorator::AddedBehavior()
{
    std::cout << "ConcreteDecorator::Added Behacior...." << std::endl;
}

void ConcreteDecorator::Operation()
{
    _com->Operation();
    this->AddedBehavior();
}