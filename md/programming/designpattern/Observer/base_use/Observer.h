#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "Subject.h"
#include <string>

using namespace std;
typedef string State;

class Observer
{
	public:
		virtual ~Observer();
		virtual void Update(Subject* sub) = 0;
		virtual void PrintInfo() = 0;
		
	protected:
		Observer();
		State _st;
		
	private:
};

class ConcreteObserverA:public Observer
{
	public:
		virtual Subject* GetSubject();
		ConcreteObserverA(Subject* sub);
		virtual ~ConcreteObserverA();
		//传入 Subject 作为参数，这样可以让一个View 属于多个的 Subject。
		void Update(Subject* sub);
		void PrintInfo();
		
	protected:
	
	private:
		Subject* _sub;
};

class ConcreteObserverB:public Observer
{
	public:
		virtual Subject* GetSubject();
		ConcreteObserverB(Subject* sub);
		virtual ~ConcreteObserverB();
		//传入 Subject 作为参数，这样可以让一个View 属于多个的 Subject。
		void Update(Subject* sub);
		void PrintInfo();
		
	protected:
	
	private:
		Subject* _sub;
};
#endif //~_OBSERVER_H_
