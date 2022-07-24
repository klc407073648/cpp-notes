#include "Context.h"
#include "Strategy.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    Strategy *ps;
    ps = new ConcreteStrategyA();
    Context *pc = new Context(ps);
    pc->DoAction();

    ps = new ConcreteStrategyB();
    pc = new Context(ps);
    pc->DoAction();

    if (NULL != pc)
        delete pc;
    return 0;
}