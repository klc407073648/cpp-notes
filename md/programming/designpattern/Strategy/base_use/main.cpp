#include "Context.h"
#include "Strategy.h"
#include <iostream>
using namespace std;
int main()
{
	StrategyBase* m_StrategyBase;
	m_StrategyBase = new StrategyA();

	Context* m_Context = new Context(m_StrategyBase);
	m_Context->doAction();

	if (NULL != m_Context)
		delete m_Context;

	if (NULL != m_StrategyBase)
		delete m_StrategyBase;
		
	return 0;
}