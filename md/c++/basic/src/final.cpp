//1、用 final 修饰类，表示该类不能被继承：
class Base final {
public:
    // ...
};

// 错误示例，无法继承 final 类
class Derived : public Base {
public:
    // ...
};
//2、用 final 修饰虚函数，表示该虚函数不能被子类重写：

class Base {
public:
    virtual void foo() final {
        // ...
    }
};

class Derived : public Base {
public:
    // 错误示例，无法重写 final 函数
    virtual void foo() {
        // ...
    }
};