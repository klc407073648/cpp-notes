#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <list>
#include <string>

using namespace std;
typedef string State;

class Observer;

class Subject
{
	public:
		virtual ~Subject();
		virtual void Attach(Observer* obv);
		virtual void Detach(Observer* obv);
		virtual void Notify();
		virtual void SetState(const State& st) = 0;
		virtual State GetState() = 0;
	
	protected:
		Subject();
		
	private:
	list<Observer* >* _obvs;
};

class ConcreteSubject:public Subject
{
	public:
		ConcreteSubject();
		~ConcreteSubject();
		State GetState();
		void SetState(const State& st);
		
	protected:
	
	private:
		State _st;
};
#endif //~_SUBJECT_H_