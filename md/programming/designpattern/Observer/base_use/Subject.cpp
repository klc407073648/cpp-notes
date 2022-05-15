#include "Subject.h"
#include "Observer.h"
#include <iostream>
#include <list>
using namespace std;
typedef string state;

Subject::Subject()
{ 	//在模板的使用之前一定要 new，创建
	_obvs = new list<Observer*>;
}

Subject::~Subject()
{ 

}

void Subject::Attach(Observer* obv)
{
	_obvs->push_front(obv);
}

void Subject::Detach(Observer* obv)
{
	if (obv != NULL)
	{
		_obvs->remove(obv);
	}
}

void Subject::Notify()
{
	list<Observer*>::iterator it;
	it = _obvs->begin();
	for (;it != _obvs->end();it++)
	{ //关于模板和 iterator 的用法
		(*it)->Update(this);
	}
}

ConcreteSubject::ConcreteSubject()//会隐式调用基类的默认构造函数
{
	_st = '\0';
}

ConcreteSubject::~ConcreteSubject()
{ 

}

State ConcreteSubject::GetState()
{
	return _st;
}

void ConcreteSubject::SetState(const State& st)
{ 
	_st = st;
}