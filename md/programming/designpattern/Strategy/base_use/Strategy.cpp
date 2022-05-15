#include "Strategy.h"
#include <iostream>
using namespace std;

StrategyBase::StrategyBase()
{

}

StrategyBase::~StrategyBase()
{
	cout<<"~StrategyBase....."<<endl;
}
void StrategyBase::AlgrithmInterface()
{

}

StrategyA::StrategyA()
{

}

StrategyA::~StrategyA()
{
	cout<<"~StrategyA....."<<endl;
}

void StrategyA::AlgrithmInterface()
{
	cout<<"test StrategyA....."<<endl;
}

StrategyB::StrategyB()
{
	
}

StrategyB::~StrategyB()
{
	cout<<"~StrategyB....."<<endl;
}

void StrategyB::AlgrithmInterface()
{
	cout<<"test StrategyB....."<<endl;
}