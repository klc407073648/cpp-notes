#include "Invoke.h"
#include "Command.h"

Invoker::Invoker(Command *cmd) : _cmd(cmd)
{
}

Invoker::Invoker()
{
}

Invoker::~Invoker()
{
    delete _cmd;
}

void Invoker::Add(Command *cmd)
{
    _commands.push_back(cmd);
}

void Invoker::Remove(Command *cmd)
{
    for (std::vector<Command *>::iterator iter = _commands.begin(); iter != _commands.end(); )
    {
        if (*iter == cmd)
        {
            iter =_commands.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

void Invoker::RemoveAll()
{
    _commands.clear();
}

void Invoker::Notify()
{
    std::vector<Command *>::iterator it = _commands.begin();
    for (; it != _commands.end(); ++it)
    {
        _cmd = *it;
        _cmd->Excute();
    }
}