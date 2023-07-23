# 第二章 - 构造函数语意学

[[toc]]

# Default Constructor 的构造操作

对于class X，如果没有任何user-declared constructor，那么会有一个default constructor被暗中（implicitly）声明出来一个被暗中声明出来的default constructor将是一个trivial（浅薄而无能，没啥用的）constructor ...

## 带有 “Default Constructor” 的Member Class Object

如果一个class没有任何constructor，但它内含一个member object，而后者有default constructor，那么这个class的implicit default constructor就是“nontrivial”，编译器需要为此class合成出一个default constructor。不过这个合成操作只有在constructor真正需要被调用时才会发生。

![](/_images/book-note/objectModel/bar_object.png)

**将Bar::foo初始化是编译器的责任，将Bar::str初始化则是程序员的责任**，被合成的 default constructor 类似为：

```cpp
inline Bar::Bar(){
    foo.Foo::Foo();
    ...
}
```

如果程序员已经定义 default constructor 

```cpp
Bar::Bar() { str = 0; }
```

现在程序的需求获得满足了，但是编译器还需要初始化member object foo。由于default constructor已经被明确地定义出来，编译器没办法合成第二个。

编译器的行动是：“如果class A内含一个或一个以上的member class objects，那么class A的每一个constructor必须调用每一个member classes的
default constructor”。编译器会扩张已存在的constructors，在其中安插一些码，使得user code在被执行之前，先调用必要的default constructors。沿续前一个例子，扩张后的constructors可能像这样：

```cpp
//扩展后的 default constructor
Bar::Bar() { 
    foo.Foo::Foo(); //附加上 compiler code //TODO
    str = 0; 
}
```

C++语言要求以member objects在class中的声明次序"来调用各个constructors。

![](/_images/book-note/objectModel/Snow_White.png)

如果 Snow_White 没有定义 default constructor，就会有一个nontrivial constructor被合成出来，**依序调用Dopey、Sneezy、Bashful的default constructors。** //TODO

## 带有 “Default Constructor” 的 Base Class 

类似的道理，如果一个没有任何constructors的class派生自一个“带有的base class，那么这个derived class的default constructor会被视为nontnvial，并因此需要被合成出来，它将调用上一层base classes的 default constructor（根据它们的声明次序）。对一个后继派生的class而言，这个合成的constructor和一个“被明确提供的default constructor”没有什么差异。

同理，如果 derived class 已提供多个 constructors ，但都没有base class的default constructor，那么编译器会扩张现有的每一个constructors，将“用以调用所有必要之default constructor”的程序代码加进去。

## “带有一个 Virtual Function” 的 Class 

![](/_images/book-note/objectModel/Widget.png)

下面两个扩张行动会在编译期间发生：

1．一个virtual function table 会被编译器产生出来，内放class的 virtual functions 地址。
2．在每一个class object中，一个额外的pointer member会被编译器合成出来，内含相关的class vtbl的地址。

为了让这个机制发挥功效，编译器必须为每一个Widget（或其派生类之）object的vptr设定初值，放置适当的virtual table地址，对于class所定义的每
一个constructor，编译器会安插一些码来做这样的事情。对于那些未声明任何constructors的classes，编译器会为它们合成一个 default constructor，以便正确地初始化每一个class object的vptr。

## “带有一个 Virtual Base Class” 的 Class 

![](/_images/book-note/objectModel/class_X.png)

编译器无法固定住foo()之中“经由 pa 而存取的 X::i ”的实际偏移位置，因为 pa 的真正类型可以改变，直到执行期才能决定。

`void foo(const A* pa) { pa->__vbcX->i = 1024; }`

其中 __vbcX 表示编译器所产生的指针，指向virtual base class X。

__vbcX是在class object建构期间被完成的。对于class所定义的每一个constructor，编译器会安插那些“允许每一个virtual base class的执行期存取操作”的代码，如果class没有声明任何constructors，编译器必须为它合成一个default constructor。

## 总结

有四种情况，会导致“编译器必须为未声明constructor之classes合成一个default constructor。C++ Stardand把那些合成物称为implicit nontrivial default constructors。被合成出来的constructor只能满足编译器（而非程序）的需要。它之所以能够完成任务，是借着调用member object或base class的 default constructor”或是“为每一个object初始化其 virtual function机制 或 virtual base class机制"而完成，至于没有存在那四种情况而又没有声明任何constructor的classes，我们说它们拥有的是implicit trivial default constructors，它们实际上并不会被合成出来。

在合成的default constructor中，**只有base class subobjects和 member class objects会被初始化**，所有其它的nonstatic data member，如整数、整数指针、整数数组等等都不会被初始化。这些初始化操作对程序而言或许有需要，但对编译器则并非必要。**如果程序需要一个“把某指针设为0”的default constructor，那么提供它的人应该是程序员。**

**C++新手一般有两个常见的误解**

1. 任何class如果没有定义default constructor，就会被合成出一个来。
2. 编译器合成出来的 default constructor 会显示设定"class内每一个data member的默认值”。

如你所见，没有一个是真的！

# Copy Constructor 的构造操作

## Default Memberwise Initialization

如果class没有提供一个explicit copy constructor又当如何？当class object以“相同class的另一个object”作为初值时，其内部是以所谓的default memberwise initialization 手法完成的，也就是把每一个内建的或派生的data member的值，从某个object拷贝一份到另一个object身上。不过它不会栲贝其的member class object，而是以递归的方式施行memberwise initialization。

一个class object可以从两种方式复制得到，一种是被初始化，另一种是被指定。从概念上而言这两个操作分别是以copy constructor copy assignment operator完成的。

## Bitwise Copy Semantics(位逐次拷贝)

memberwise copy 深拷贝 和 Bitwise Copy 浅拷贝

```cpp
Word noun("book");
Word verb = noun;

//以下声明展现了 Bitwise Copy Semantics
class Word{
    public:
        Word(const char*)
        Word() { delete [] str;}
        //...
    private:
        int cnt;
        char* str;
```

这种情况下并不需要合成出一个default copy constructor，因为上述声明展现了"default copy semantics”，而verb的初始化操作也就不需要以一个函数调用收场。然而，如果class Word是这样声明

```cpp
//以下声明展现了 Bitwise Copy Semantics
class Word{
    public:
        Word(const String*)
        Word() { delete [] str;}
        //...
    private:
        int cnt;
        String str;
```

其中 String 声明了一个 explicit copy constructor:

```cpp
class String{
    public:
        String(const char*)
        String()(const String&)
        //...
```

在这个情况下，**编译器必须合成出一个copy constructor以便调用member class String object 的copy constructor**:

```cpp
inline Word::Word(const Word& wd)
{
    str.String::String(wd.str);
    cnt = wd.cnt;
}
```

class 不展现 “Bitwise Copy Semantics” 的四种情况：

1．当class内含一个member object而后者的class声明有一个时。
2．当class继承自一个base class而后者存在有一个copy constructor时。
3．当class声明了一个或多个virtual functions时。
4. 当class派生自一个继承串链，其中有一个或多个virtual base classes时。

## 重新设定 Virtual Table 的指针copy constructor

定义两个类ZooAnimal，Bear：

![](/_images/book-note/objectModel/ZooAnimal_Bear.png)

ZooAnimal class object以另一个 ZooAnimal class object 作为初值，或Bear class object以另一个Bear class object作为初值，都可以直接靠"bitwise copy semantics”完成。

当一个base class object 以其 derived class 的object内容做初始化操作时，其vptr复制操作也必须保证安全。


```cpp
ZooAnimal franny = yogi;

draw( yogi ); // Bear::draw()
draw( franny ); // ZooAnimal::draw()
```

![](/_images/book-note/objectModel/yogi_fanny.png)

也就是说，合成出来的 ZooAnimal copy constructor会**明确设定object的vptr指向 ZooAnimal class的virtual table，而不是直接从右手边的class object中将其vptr现值拷贝过来。**

## 处理 Virtual Base Class Subobject

Virtual base class的存在需要特别处理，一个class object如果以另一个object作为初值，而后者有一个virtual，那么也会使"bitwise copy Semantics”失效。

如果以一个Raccoon object作为另一个Raccoon object的初值，那么"bitwise copy"就绰绰有余了：

![](/_images/book-note/objectModel/Raccoon.png)

在上述图的情况下，在这种情况下，为了完成正确的little_critter初值设定，编译器必须合成copy constructor，安插一些代码以设定virtual base class pointer/offset的初值（或只是简单地确定它没有被抹消），对每一个members执行必要的memberwise初始化操作，以及执行其它的内存相关工作。

# 程序转化语意学(Program Transformation Semantics)

## 显示的初始化操作(Explicit Initialization)

```cpp
X x0;

void foo_bar(){
    X x1(x0);
    X x2 = x0;
    X x3 = X(x0);
}
```

必要的程序转化有两个阶段：

1. 重写每一个定义，其中的初始化操作会被剥除。
2. class的copy constructor调用操作会被安插进去。

```cpp
void foo_bar(){
   X x1; //定义被重写，初始化操作被剥除
   X x2;
   X x3; 

   // 编译器安插 X copy constructorion 的调用操作
   x1.X::X( x0 );
   x2.X::X( x0 ); 
   x3.X::X( x0 );
}
```

## 参数初始化(Argument Initialization)

把一个class object当做参数传给一个函数（或是作为一个函数的返回值），相当于以下形式的初始化操作：

`X xx = arg;`

其中 xx 代表形式参数（或返回值）而arg代表真正的参数值。因此，若已知这个函数

`void foo(X x0)`

下面这样的调用方式：

```cpp
X xx;
//...
foo(xx);
```

将会要求局部实体（local instance）x0 以 memberwise 的方式将xx当做初值。在编译器实现技术上，有一种策略是导人所谓的暂时性 object ，并调用copy constructor 将它初始化，然后将该暂时性 object 交给函数。

```
X __temp0;
__temp0.X::X(xx);
foo(__temp0);
```

然而这样的转换只做了一半功夫而已。问题出在foo()的声明，暂时性 object 先以 class X的copy constructor正确地设定了初值，然后再以 bitwise 方式拷贝到x0这个局部实体中。更好的做法是：foo()的声明，形式参数必须从原先的一个class X object改变为一个class X reference。

`void foo(X& x0);`

另一种实现方法是以“拷贝建构”（copy construct）的方式把实际参数直接建构在其应该的位置上，该位置视函数活动范围的不同记录于程序堆栈中。在函
数返回之前，局部对象(local object)的destructor（如果有定义的话）会被执行。

## 返回值的初始化(Return Value Initialization)

```cpp
X bar()
{
    X xx;
    // 处理xx ...
    return xx;
}
```

bar()的返回值如何从局部变量xx中拷贝过来？解决方法是一个双阶段转化：

1. 首先加上一个额外参数，类型是class object的一个reference。这个参数将用来放置被 “拷贝建构（copy constructed）” 而得的返回值。

2. 在 return 指令之前安插一个copy constructor调用操作，以便将欲传回之object的内容当做上述新增参数的初值。

转换之后的伪代码：

```cpp
void bar(X& __result)
{
    X xx;

    xx.X::X();

    // 处理xx ...

    __result.X::XX(xx);

    return;
}
```

通过上述操作之后，编译器调用必须转换每一个bar()调用操作。

```cpp
X xx = bar();

//转化为

X xx;
bar(xx);
```

## 在使用者层面做优化(Optimization at User Level)

程序员优化观念的提出：定义一个计算用的 constructor 。

```cpp
//xx被 memberwise地拷贝到编译器所产生的__result之中。（copy constructor拷贝）
X bar(const T &y,const T &z)
{
    X xx;
    // 以y和z来处理xx
    return xx;
}

//定义constructor
X bar(const T &y,const T &z)
{
    return X(y,z);
}

//伪代码
void bar(X &__result, const T &y, const T &z)
{
    __result.X::X(y,z);
    return;
}
```

__result被直接计算出来，而不是经由copy constructor拷贝而得！不过这种解决方法受到了某种批评，怕那些特殊计算用途的constructor可能会大量扩散在这个层面上，class的设计是以效率考虑居多，而不是以“支持抽象化”为优先。

## 在编译器层面做优化(Optimization at Compiler Level)

在一个如bar()这样的函数中，所有的return指令传回相同的具名数值，因此编译器有可能自己做优化，方法是以参数取代named return value。例如下面的bar()定义：

```cpp
X bar()
{
    X xx;
    // 处理xx
    return xx;
}
```

编译器把其中的xx以__result取代：

```cpp
void bar(X &__result)
{
    __result.X::X();//default constructor 被调用
    // 直接处理__result
    return;
}

## Copy Constructor: 要还是不要？

实现 copy constructor 的最简单方法像这样：

```cpp
Point3d::Point3d(const Point3d &rhs)
{
    _x = rhs._x;
    _y = rhs._y;
    _z = rhs._z;
}
```

这没问题，但使用C++library的 memcpy() 会更有效率：

在C/C++标准库中，**memcpy函数用于将一个内存区域的内容拷贝到另一个内存区域中。相比于使用循环逐个进行赋值操作，使用memcpy函数能够实现更快的内存拷贝**。这是因为：

* memcpy函数是标准库函数，由编译器进行优化，能够充分利用底层平台的指令集，完成内存拷贝操作，而循环赋值则需要使用多个指令逐个赋值，效率较低。

* memcpy函数可以利用CPU的并行处理能力，通过同时读取多个字节实现更快的内存拷贝，而循环赋值则无法充分利用CPU的并行处理能力。

* memcpy函数可以利用CPU的缓存机制，通过预读取数据提高内存访问效率，而循环赋值则需要频繁进行内存访问，容易造成CPU缓存失效，效率较低。

```cpp
Point3d::Point3d(const Point3d &rhs)
{
    memcpy(this,&rhs,sizeof(Point3d))
}
```

然而不管使用 memcpy() 或 memset() ，都只有在“classes不含任何由编译器产生的内部members”时才能有效运行。如果Point3d class声明一个或一个以上的virtual functions，或内含一个virtual base class，那么使用上述函数将会导致那些“被编译器产生的内部members”的初值被改写。例如，已知下面声明：

```cpp
class Shape{
    public:
        Shape() { memset(this,0,sizeof(Shape)); }
        virtual ~Shape();
        //...
}
```

编译器为此 constructor 扩张的内容看起来像是：

```cpp
Shape()::Shape() 
{
    __vptr__Shape = __vtbl__Shape;

    //memset会将vptr清为0
    memset(this,0,sizeof(Shape)); }
}
```

## 成员们的初始化队伍(Member Initialization List)

<font color='red'>**memeber初始化操作必须在 Member Initialization List 中完成**</font>

list中的项目顺序是**由class中的members声明顺序决定**，不是由initialization list中的排列顺序决定。

总结：编译器会对initialization list一一处理并可能重新排序，以反映出members的声明次序·它会安插一些代码到constructor体内，并置于任何explicit user code之前，