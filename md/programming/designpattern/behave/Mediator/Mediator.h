#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_
class Colleage;
class Mediator
{
public:
    virtual ~Mediator();
    virtual void DoActionFromAtoB() = 0;
    virtual void DoActionFromBtoA() = 0;

protected:
    Mediator();

private:
};

class ConcreteMediator : public Mediator
{
public:
    ConcreteMediator();
    ConcreteMediator(Colleage *clgA, Colleage *clgB);
    ~ConcreteMediator();
    void SetConcreteColleageA(Colleage *clgA);
    void SetConcreteColleageB(Colleage *clgB);
    Colleage *GetConcreteColleageA();
    Colleage *GetConcreteColleageB();
    void IntroColleage(Colleage *clgA, Colleage *clgB);
    void DoActionFromAtoB();
    void DoActionFromBtoA();

protected:
private:
    Colleage *_clgA;
    Colleage *_clgB;
};
#endif //~_MEDIATOR_H