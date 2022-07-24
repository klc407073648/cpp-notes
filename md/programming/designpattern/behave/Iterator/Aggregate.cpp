#include "Aggregate.h"
#include "Iterator.h"
#include <iostream>
using namespace std;

Aggregate::Aggregate()
{
}

Aggregate::~Aggregate()
{
}

ConcreteAggregate::ConcreteAggregate()
{
    for (int i = 0; i < SIZE; i++)
        _objs[i] = i;
}

ConcreteAggregate::~ConcreteAggregate()
{
}

Iterator *ConcreteAggregate::CreateIterator()
{
    return new ConcreteIterator(this);
}

Object ConcreteAggregate::GetItem(int idx)
{
    if (idx < this->GetSize())
        return _objs[idx];
    else
        return -1;
}

int ConcreteAggregate::GetSize()
{
    return SIZE;
}