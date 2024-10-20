#include <iostream>
using namespace std;

class Base {
public:
    virtual void func() const { cout << "Base::func()" << endl; }
};

class Derived : public Base {
public:
    void func() const override { cout << "Derived::func()" << endl; }
};

int main() {
    Base* p = new Derived();
    p->func();
    return 0;
}