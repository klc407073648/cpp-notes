# 观察者模式

​[[toc]]

> 观察者模式(Observer): 定义了一种一对多的依赖关系,让多个观察者对象同时监听某一主题对象,在它的状态发生变化时,会通知所有的观察者。

具体思路解析：

1. Subject 提供依赖于它的观察者 Observer 的注册（Attach）和注销（Detach）操作，并且提供了使得依赖于它的所有观察者同步的操作（Notify）。

2. Subject通过维护list<Observer* >* _obvs，Object维护Subject* _sub，使用时。先创建Subject* sub，然后将其作为变量传递给Observer* o1,o2，使得ConcreteObserver在构造时完成Attach操作，将监听对象加入Subject的监听队列_obvs。

3. Subject* sub 通过SetState函数改变状态，在调用Notify去遍历监听队列_obvs，更新Observer* o1,o2的状态。

```cpp
	Subject* sub = new ConcreteSubject();
	Observer* o1 = new ConcreteObserverA(sub);
	Observer* o2 = new ConcreteObserverB(sub);
	
	sub->SetState("old");
	sub->Notify();
	sub->SetState("new"); // 也可以由Observer 调用
	sub->Notify();

——————————————————————————————————————————————————————————————————————————————————

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

void ConcreteObserverA::Update(Subject* sub)
{
	_st = sub->GetState();
	PrintInfo();
}

void ConcreteObserverA::PrintInfo()
{
	cout<<"ConcreteObserverA observer...."<<_sub->GetState()<<endl;
}
```

执行结果如下，因为list是头插法，后加入的ConcreteObserverB在sub广播通知list的开头，所以通知的消息先到达B：

```bash
[root@192 base_use]# ./Observer
ConcreteObserverB observer....old
ConcreteObserverA observer....old
ConcreteObserverB observer....new
ConcreteObserverA observer....new
```
​