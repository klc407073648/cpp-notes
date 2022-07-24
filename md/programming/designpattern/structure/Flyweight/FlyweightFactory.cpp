#include "FlyweightFactory.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

FlyweightFactory::FlyweightFactory()
{
}

FlyweightFactory::~FlyweightFactory()
{
}

Flyweight *FlyweightFactory::GetFlyweight(const string &key)
{
    vector<Flyweight *>::iterator it = _fly.begin();
    for (; it != _fly.end(); it++)
    {
        //找到了，就一起用， ^_^
        if ((*it)->GetIntrinsicState() == key)
        {
            cout << "already created by users...." << endl;
            return *it;
        }
    }
    Flyweight *fn = new ConcreteFlyweight(key);
    _fly.push_back(fn);
    return fn;
}