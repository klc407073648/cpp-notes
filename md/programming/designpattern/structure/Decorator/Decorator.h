#ifndef _DECORATOR_H_
#define _DECORATOR_H_

class Component
{
public:
    virtual ~Component();
    virtual void Operation();

protected:
    Component();

private:
};

class ConcreteComponent : public Component
{
public:
    ConcreteComponent();
    ~ConcreteComponent();
    void Operation();

protected:
private:
};

class Decorator : public Component
{
public:
    Decorator(Component *com);
    virtual ~Decorator();
    void Operation();

protected:
    Component *_com;

private:
};

class ConcreteDecorator : public Decorator
{
public:
    ConcreteDecorator(Component *com);
    ~ConcreteDecorator();
    void Operation();
    void AddedBehavior();

protected:
private:
};
#endif //~_DECORATOR_H_