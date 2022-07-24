#include "Director.h"
#include "Builder.h"

Director::Director(Builder *bld)
{
    _bld = bld;
}

Director::~Director()
{
}

void Director::Construct()
{
    _bld->BuildPartA("user-defined");
    _bld->BuildPartB("user-defined");
    _bld->BuildPartC("user-defined");
}