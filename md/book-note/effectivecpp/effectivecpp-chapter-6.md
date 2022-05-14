# 第六章：继承与面向对象设计

[[toc]]

# 确认你的public继承塑模出is-a关系

C++面向对象编程，最重要的一个规则：public inheritance(公开继承)意味“is-a”（是一种）的关系。即能够施行于base class 对象身上的每件事情，也可以施行于derived class对象身上，因为derived class对象也都是一个base class对象。但是界限很难鉴别，举例如下：

```cpp
class Person{...};
class Student:public Person{...};
```

人的概念比学生更一般化，学生是人的一种特殊形式。

```cpp
class Bird{...};
class Penguin:public Bird {...};
```

鸟可以飞，企鹅是鸟，但是不能飞。这种情况下，应该在编译期拒绝企鹅飞行的设计，而不是在运行期才能侦测它们。

同理，正方形和矩形也可以是:

```cpp
class Square:public Rectangle
```
正方形一定时矩形，但是矩形的一些函数操作便不适用于正方形。

# 明智而审慎地使用private继承

如果classes之间的继承关系是private,编译器不会自动将一个derived class对象转换为一个base class对象。

```cpp
class Person{
};
class Student : private Person {};

void eat(const Person &p){};   // 任何人都会吃
void study(const Student &s){}; // 只有学生会学习

int main(){
    Person p;
    Student s;

    eat(p);  // 人会吃
    eat(s); // error！！！ 难道学生不是人？？？

    study(p); // error！！！不是所有的人都会学习
    study(s); // 只有学生会学习
}

```

会提示：

```bash
[root@iZuf61kbf845xt6tz10abgZ home]# g++ -o main  main.cpp
main.cpp: In function ‘int main()’:
main.cpp:14:10: error: ‘Person’ is an inaccessible base of ‘Student’
   14 |     eat(s); // error！！！ 难道学生不是人？？？
      |          ^
main.cpp:16:11: error: invalid initialization of reference of type ‘const Student&’ from expression of type ‘Person’
   16 |     study(p); // error！！！不是所有的人都会学习
```

注意事项：

1. private继承意味implemented-in-terms-of(根据某物实现出)。它通常比复合（composition）的级别低。但是当derived class需要访问protected base class的成员，或需要重新定义继承而来的virtual函数时，这么设计时合理的。
2. 和复合（composition）不同，private继承可以造成empty base 最优化。

# 通过复合塑模出has-a或“根据某物实现出”

STL中set可以用list实现出来，但是set和list并不是public继承关系，因为set中元素是唯一的，但是list可以拥有多个重复元素节点。

```cpp
template<class T>
class Set
{
public:
    bool member(const T& item) const;
    bool insert(const T& item) ;
    bool remove(const T& item) ;
private:
    std::list<T> rep;
}
```

# 避免遮掩继承而来的名称

```cpp
class Base
{
    public:
        Base(){};
        ~Base(){};
		virtual void mFun1() = 0;
		virtual void mFun1(int i){};
		virtual void mFun2(){};
		void mFun3(){};
		void mFun3(double d){};
    private:
        int x;
};

class Derived:public Base
{
    public:
		//using Base::mFun1;
		//using Base::mFun3;
        Derived(){};
        ~Derived(){};
		virtual void mFun1(){};
		void mFun3(){};
		void mFun4(){};
    private:
};

int main()
{
   Derived m_Derived;
    int x=10;
    m_Derived.mFun1();
    m_Derived.mFun1(x);//错误
    m_Derived.mFun2();
    m_Derived.mFun3();
    m_Derived.mFun3(x);//错误
    m_Derived.mFun4(); 
}
```

提示：

```bash
[root@iZuf61kbf845xt6tz10abgZ home]# g++ -o main  main.cpp
main.cpp: In function ‘int main()’:
main.cpp:34:22: error: no matching function for call to ‘Derived::mFun1(int&)’
   34 |     m_Derived.mFun1(x);//错误
      |                      ^
main.cpp:23:16: note: candidate: ‘virtual void Derived::mFun1()’
   23 |   virtual void mFun1();
      |                ^~~~~
main.cpp:23:16: note:   candidate expects 0 arguments, 1 provided
main.cpp:37:22: error: no matching function for call to ‘Derived::mFun3(int&)’
   37 |     m_Derived.mFun3(x);//错误
      |                      ^
main.cpp:24:8: note: candidate: ‘void Derived::mFun3()’
```

需要使用

```cpp
using Base::mFun1;
using Base::mFun3;

or

m_Derived.Base::mFun1(x);
m_Derived.Base::mFun3(x);
```

上述才能正常调用

如果继承base class并加上重载函数，而你又希望重新定义或覆写其中一部分，那么你必须为那些原本会被遮掩的**每个名称引入一个using声明式，否则某些你希望继承的名称会被遮掩。**

注意事项：

1. derived classes 内的名称会遮掩base classes内的名称。在publid继承下从来没有人希望如此。
2. 为了让被遮掩的名称再见天日，可使用using声明式或转交函数。 

# 绝不重新定义继承而来的non-virtual函数

**non-virtual函数是静态绑定的，virtual函数是动态绑定的。**public继承表示is-a的关系，non-virtual函数会为class建立起一个不变性，凌驾其特异性。

```cpp
class B
{
public:
    void mFun();
}

class D:public B
{
public:
    void mFun();
}

D x;
B* pB =&x;
D* pD =&x;
pB->mFun();//调用B::mFun()
pD->mFun();//调用D::mFun()
```

pB和pD指向相同的对象x,调用结果却不一致。是因为non-virtual是静态绑定，通过pB调用的non-virtual函数永远是B所定义的版本。

# 绝不重新定义继承而来的缺省参数值

继承一个带有缺省参数值的virtual函数是不正确的，因为virtual函数系动态绑定，而缺省参数值却是静态绑定。

# 明智而审慎地使用多重继承

C++标准程序库内含一个多重继承体系，basic_ios,basic_istream,basic_ostream和basic_iostream。basic_istream和basic_ostream  virtual public继承于basic_ios，basic_iostream  public继承于basic_istream和basic_ostream 。virtual public继承不会拥有两份basic_ios内容。

注意事项：

1. 多重继承比单一继承复杂，它可能导致新的歧义性，以及对virtual继承的需要。（例如继承的两个类中有相同的函数，可以用class::mFun指明调用的是哪个函数）。
2. virtual 继承会增加大小、速度、初始化（及赋值）复杂度等等成本。如果virtual base classes不带任何数据，将是最具使用价值的情况。
3. 多重继承的确有正当用途。其中一个情节涉及“public继承某个Interface class”和“private继承某个协助实现的class”两相结合。
​