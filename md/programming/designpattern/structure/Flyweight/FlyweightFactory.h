#ifndef _FLYWEIGHTFACTORY_H_
#define _FLYWEIGHTFACTORY_H_

#include "Flyweight.h"
#include <string>
#include <vector>
using namespace std;

class FlyweightFactory
{
public:
    FlyweightFactory();
    ~FlyweightFactory();
    Flyweight *GetFlyweight(const string &key);

protected:
private:
    vector<Flyweight *> _fly;
};
#endif //~_FLYWEIGHTFACTORY_H_