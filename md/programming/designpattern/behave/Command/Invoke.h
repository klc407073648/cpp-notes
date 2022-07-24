#ifndef _INVOKER_H_
#define _INVOKER_H_
#include <vector>
#include <iostream>

using namespace std;

class Command;
class Invoker
{
public:
    Invoker(Command *cmd);
    Invoker();
    ~Invoker();

    void Add(Command *cmd);
    void Remove(Command *cmd);
    void RemoveAll();
    void Notify();

protected:
private:
    Command *_cmd;
    vector<Command *> _commands;
};
#endif //~_INVOKER_H_