#ifndef _COLLEAGE_H_
#define _COLLEAGE_H_
#include <string>
using namespace std;
class Mediator;
class Colleage
{
public:
    virtual ~Colleage();
    virtual void Aciton() = 0;
    virtual void SetState(const string &sdt) = 0;
    virtual string GetState() = 0;

protected:
    Colleage();
    Colleage(Mediator *mdt);
    Mediator *_mdt;

private:
};

class ConcreteColleageA : public Colleage
{
public:
    ConcreteColleageA();
    ConcreteColleageA(Mediator *mdt);
    ~ConcreteColleageA();
    void Aciton();
    void SetState(const string &sdt);
    string GetState();

protected:
private:
    string _sdt;
};

class ConcreteColleageB : public Colleage
{
public:
    ConcreteColleageB();
    ConcreteColleageB(Mediator *mdt);
    ~ConcreteColleageB();
    void Aciton();
    void SetState(const string &sdt);
    string GetState();

protected:
private:
    string _sdt;
};
#endif //~_COLLEAGE_H_