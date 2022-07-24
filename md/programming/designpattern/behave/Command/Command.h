#ifndef _COMMAND_H_
#define _COMMAND_H_
#include <iostream>

using namespace std;
class Reciever;

class Command
{
public:
    virtual ~Command();
    virtual void Excute() = 0;

protected:
    Command();

private:
};

class ConcreteCommandA : public Command
{
public:
    ConcreteCommandA(Reciever *rev);
    ~ConcreteCommandA();
    void Excute();

protected:
private:
    Reciever *_rev;
};

class ConcreteCommandB : public Command
{
public:
    ConcreteCommandB(Reciever *rev);
    ~ConcreteCommandB();
    void Excute();

protected:
private:
    Reciever *_rev;
};

#endif //~_COMMAND_H_