#ifndef _COMPOSITE_H_
#define _COMPOSITE_H_
#include "Component.h"
#include <vector>
using namespace std;

class Composite : public Component
{
public:
    Composite();
    ~Composite();

public:
    void Operation();
    void Add(Component *com);
    void Remove(Component *com);
    Component *GetChild(int index);

protected:
private:
    vector<Component *> comVec;
};
#endif //~_COMPOSITE_H_