#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual void print() {}
};

class Derived : public Base {
public:
    virtual void print() {}
};

int main() {
    Base* basePtr = new Derived();
    
    // 使用typeid运算符获取类型信息
    const std::type_info& type = typeid(*basePtr);
    
    // 输出类型的名称
    std::cout << "Type name: " << type.name() << std::endl;
    
    // 比较类型
    if (type == typeid(Base)) {
        std::cout << "Type is Base" << std::endl;
    } else if (type == typeid(Derived)) {
        std::cout << "Type is Derived" << std::endl;
    } else {
        std::cout << "Type is unknown" << std::endl;
    }
    
    delete basePtr;
    
    return 0;
}