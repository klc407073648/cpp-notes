// 类
class A
{
public:
    A() : a(0) { };             // 构造函数
    A(int x) : a(x) { };        // 初始化列表

    // const可用于对重载函数的区分
    int getValue();             // 普通成员函数
    int getValue() const;       // 常成员函数，不得修改类中的任何数据成员的值
private:
    const int a;                // 常对象成员，只能在初始化列表赋值
};

void fun()
{
    // 对象
    A b;                        // 普通对象，可以调用全部成员函数、更新常成员变量
    const A a;                  // 常对象，只能调用常成员函数
    const A *p = &a;            // 常指针
    const A &q = a;             // 常引用

    // 指针
    char greeting[] = "Hello";
    char* p1 = greeting;                // 指针变量，指向字符数组变量
    const char* p2 = greeting;          // 指针变量，指向字符数组常量
    char* const p3 = greeting;          // 常指针，指向字符数组变量
    const char* const p4 = greeting;    // 常指针，指向字符数组常量
}

// 函数
void fun1(const int Var);           // 传递过来的参数在函数内不可变
void fun2(const char* Var);         // 参数指针所指内容为常量
void fun3(char* const Var);         // 参数指针为常指针
void fun4(const int& Var);          // 引用参数在函数内为常量

// 函数返回值
const int fun5();      // 返回一个常数
const int* fun6();     // 返回一个指向常量的指针变量，使用：const int *p = fun6();
int* const fun7();     // 返回一个指向变量的常指针，使用：int* const p = fun7();

//const修饰函数时的重载

//实际上没有区别，因为函数调用的时候，存在形实结合的过程，所以不管有没有const都不会改变实参的值。所以不能通过编译，提示重定义。
void fun(const int i);
void fun(int i);

//char *a 中a指向的是一个字符串变量，而const char *a指向的是一个字符串常量，所以当参数为字符串常量时，调用第二个函数，而当函数是字符串变量时，调用第一个函数。
void fun(char *a);    
void fun(const char *a);

//这两个都是指向字符串变量，不同的是char *a是指针变量 而char *const a是指针常量。所以不能通过编译，提示重定义。
void fun(char *a);  
void fun(char * const a);  

//原因是第一个i引用的是一个变量，而第二个i引用的是一个常量，两者是不一样的，类似于上面的指向变量的指针的指向常量的指针。
void fun(int &i);  
void fun(const int &i);   
 
