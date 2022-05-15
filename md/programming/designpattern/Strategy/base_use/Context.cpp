#include "Context.h"
#include "Strategy.h"
#include <iostream>
using namespace std;
Context::Context(StrategyBase *stg)
{
	_stg = stg;
}

Context::~Context()
{
	if (!_stg)
		delete _stg;
}

void Context::doAction()
{
	_stg->AlgrithmInterface();
}