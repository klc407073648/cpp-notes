#include "Composite.h"
#include "Component.h"
#define NULL 0 // define NULL POINTOR

Composite::Composite()
{
    // vector<Component*>::iterator itend =comVec.begin();
}

Composite::~Composite()
{
}

void Composite::Operation()
{
    vector<Component *>::iterator comIter = comVec.begin();
    for (; comIter != comVec.end(); comIter++)
    {
        (*comIter)->Operation();
    }
}

void Composite::Add(Component *com)
{
    comVec.push_back(com);
}

void Composite::Remove(Component *com)
{
    //comVec.erase(&com);

    for (std::vector<Component *>::iterator iter = comVec.begin(); iter != comVec.end(); )
    {
        if (*iter == com)
        {
            iter =comVec.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

Component *Composite::GetChild(int index)
{
    return comVec[index];
}