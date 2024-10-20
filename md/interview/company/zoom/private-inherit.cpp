#include<stdio.h>


class Base{
public:
    void NoVirtualFun()
    {
        printf("Base::NoVirtualFun()!\n");
    }
    virtual void VirtualFun()
    {
        printf("Base::VirtualFun()!\n");
    }
};

class ClassA{
private:
    Base* m_pBase;
public:
    ClassA() : m_pBase(NULL)
    {}
    void AddBase(Base* pBase)
    {
        m_pBase = pBase;
    }
    void Print()
    {
        //此处使用的访问权限是Base::VirtualFun()的访问权限(public)
        //因此在ClassA中可以使用该虚函数，而忽略派生类Child中该函数的权限设置。
        m_pBase->VirtualFun();
    }
};

//注：私有继承
class Child: private Base{
private:
    ClassA* m_pClassA;
private:    //私有
    virtual void VirtualFun()
    {
        printf("Child::VirtualFun()!\n");
    }
public:
    Child(ClassA* pClassA)
    {
        m_pClassA = pClassA;
        m_pClassA->AddBase(this);
    }
};

//1.使用Private继承后，无法在类作用域外直接使用多态,
//  派生类指针无法自动转型为基类指针.
//2.从基类private继承虚函数后，若在派生类中将该虚函数重载，
//  并设置访问权限为public，该虚函数将为public成员函数.

int main(int argc, char* argv[])
{
    ClassA* classA = new ClassA();
    Child* chd = new Child(classA);
   
    //classA->AddBase((Base*)chd);    //允许强制转型为基类指针
    //classA->AddBase(chd);   //错误，无法自动转换为基类指针
    classA->Print();

//若在Child中将VirtualFun()指定为Public，该函数将作为public的成员函数,
//而不是private继承后的private成员函数
    //chd->VirtualFun();  //Error 此时为私有成员，若将Chlid::VirtualFun()的访问权限设为public则正确
    delete chd;
    delete classA;
    return 0;
}
