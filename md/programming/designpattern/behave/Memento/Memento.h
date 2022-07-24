#ifndef _MEMENTO_H_
#define _MEMENTO_H_
#include <string>
using namespace std;
class Memento;
class Originator
{
public:
    typedef string State;
    Originator();
    Originator(const State &sdt);
    ~Originator();
    Memento *CreateMemento();
    void SetMemento(Memento *men);
    void RestoreToMemento(Memento *mt);
    State GetState();
    void SetState(const State &sdt);
    void PrintState();

protected:
private:
    State _sdt;
    Memento *_mt;
};

class Memento
{
public:
protected:
private:
    //这是最关键的地方，将 Originator 为friend 类，可以访问内部信息，但是其他类不能访问
    friend class Originator;
    typedef string State;
    Memento();
    Memento(const State &sdt);
    ~Memento();
    void SetState(const State &sdt);
    State GetState();

private:
    State _sdt;
};
#endif //~_MEMENTO_H_