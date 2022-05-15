# 线程安全的对象生命期管理

[[toc]]

# 线程安全的对象生命期管理

## 当析构函数遇到多线程
当一个对象能被多个线程同时看到，那么对象的销毁时机就会变得模糊不清，可能出现多种竞态条件（race condition）：

1. 在即将析构一个对象时，如何知道此时是否有别的线程正在执行该对象的成员函数？
2. 如何保证在执行成员函数期间，对象不会被另一个线程析构？
3. 在调用某个对象的成员函数之前，如何得知该对象还活着？它的析构函数会不会碰巧执行到一半？
解决这些race condition是C++多线程编程面临的基本问题？可以尝试通过智能指针shared_ptr解决上述问题。

## 对象的创建

对象构造要做到线程安全，唯一的要求是**在构造期间不要泄露this指针**，即：

* 不要在构造函数中注册任何回调；
* 不要在构造函数中将this指针传递给跨线程的对象；
* 即使在构造函数最后一行也不行。

因为构造函数在执行期间对象还没有完成初始化，this指针泄露给其他对象，可能别的线程访问的是一个半成品。

## 对象的销毁

mutex只能保证成员函数顺次执行的安全，但是作为数据成员的mutex不能保护析构：

![mutex不能保护析构](/_images/book-note/muduo/mutex不能保护析构.JPG)

尽管线程A在销毁对象x之后把x设为NULL，尽管线程B在调用x之前检查了指针x地值，但是还是无法避免一种race condition：

1. 线程A调用delete x，执行到析构函数(1)，已经持有了互斥锁mutex_，即将继续向下执行；
2. x并没有被线程A设为NULL，因此线程B能通过if(x)，进入x->update()，将阻塞在(2)处；
3. 之后因为析构函数销毁x地同时也将成员变量mutex_给销毁，因此(2)将会发生难以预料的结果（可能会永远阻塞在(2)处，也可能会进入“临界区”，然后core dump，或者发生更糟糕的情况）

结论：**作为class数据成员的mutex_只能同步本class的其他数据成员的读和写，不能保护安全的析构**。

# 对象的关系
在面向对象程序设计中，对象的关系主要有三种：composition、aggregation、association。

* composition（组合/复合），对象x的生命期由唯一拥有者owner控制，owner析构时会把x同步析构。例如Engine是Car的一部分。脱离Car的Engine是没有实在意义的，即表示Part-of 关系。

* aggregation（聚合），是一种特殊的联系，它表明了“部分”到“整体”的关系。例如Person有一个Address，但是Addess的存在是不依赖Person的，即表示Has-a关系。

* association（关联/联系），是一种很宽泛的关系，它表示一个对象a用到了另一个对象b，即a持有b的指针（或引用），但是b的生命期不由a单独控制。

Association描述的是类与类之间一般的关联关系，而Aggregation和Composition都有整体和部分的关系。其中Aggregation中的部分脱离了整体，部分仍然有意义，是共享式的。而Composition中的部分脱离了整体，部分将没有任何意义，是独占式的。

从实现的角度上讲：

　　三者中以属性出现时，有着不同的实现方法。其中Association中作为属性出现时，不需要对其进行强制赋值，只要在使用时对其进行初始化即可。Aggregation中作为属性出现时，需要在构造器中通过传递参数来对其进行初始化。Composition作为属性出现时，需要在整体的构造器中创建部分的具体实例，完成对其的实例化。

# 原始指针和智能指针

指向对象的原始指针是坏的，尤其当这个指针暴露给其他线程的时候。从而，引入智能指针shared_ptr/weak_ptr的概念。shared_ptr是强引用，只要有一个指向x对象的shared_ptr存在，则该对象不会被析构；weak_ptr是弱引用，如果对象还存在，则可以提升为强引用来使用。

应用shared_ptr/weak_ptr可以解决上述x->update()的问题，因为不是通过加锁来控制，而是每次尝试提升，成功执行update逻辑。

![应用到Observer](/_images/book-note/muduo/应用到Observer.JPG)

shared_ptr的线程安全问题：shared_ptr本身不是100%线程安全的，它的引用计数本身是安全且无锁的，但对象的读写则不是，因为shared_ptr有两个数据成员，读写操作不能原子化。还是需要借助mutex来保护多线程情况下对同一个shared_ptr的访问。

官方说法：


> Thread Safety

> shared_ptr objects offer the same level of thread safety as built-in types. A shared_ptr instance can be "read" (accessed using only const operations) simultaneously by multiple threads. Different shared_ptr instances can be "written to" (accessed using mutable operations such as operator= or reset) simultaneously by multiple threads (even when these instances are copies, and share the same reference count underneath.)

Any other simultaneous accesses result in undefined behavior.

即shared_ptr 只能保证一个shared_ptr 实例被多个线程同时读取，多个shared_ptr 实例被多个线程同时写入是安全的，其他行为是未定义的。

shared_ptr是强引用，使用时可能会**意外延长对象的生命期**。shared_ptr在做函数参数时，可以考虑以const reference方式传播。

# 对象池

假定Stock类表示一只股票的价格，每只股票有唯一的字符串标识。例如Tencent的key是“SJS:Tencent”，Alibaba是“SJS:Alibaba”。即同一个程序中，每一只股票只有一个Stock对象，存在多处使用，那么Stock对象一个被共享。从而设计出如下StockFactory对象池。

![对象池1](/_images/book-note/muduo/对象池1.JPG)

上述设计中get函数是从stocks_中根据key寻找对应的Stock对象，找到就返回stocks_[key]；否则新建一个Stock，并存入stocks_[key]。使用shared_ptr会导致Stock对象永远不被销毁，因此应该使用weak_ptr。

![对象池2](/_images/book-note/muduo/对象池2.JPG)

更进一步，利用shared_ptr的定制析构功能，在析构Stock对象的同时清理stocks_。

![对象池3](/_images/book-note/muduo/对象池3.JPG)

因为get函数中使用了this指针，如果StockFactory的生命期比Stock短，则析构Stock时调用StockFactory::deleteStock就会core dump。此时，可以使用enable_shared_from_this。

![对象池4](/_images/book-note/muduo/对象池4.JPG)

但是使用enable_shared_from_this后，StockFactory的生命期被延长了。下面，使用弱回调技术进行改进：

![对象池5](/_images/book-note/muduo/对象池5.JPG)

# 总结

1. 原始指针暴露给多个线程往往会造成race condition或额外的程序负担。
2. 统一用shared_ptr/scoped_ptr来管理对象的生命期，在多线程中尤为重要。
3. shared_ptr是值语意，当心意外延长对象的生命期。例如boost::bind和容器都可能拷贝shared_ptr。
4. weak_ptr是shared_ptr的好搭档，可以用作弱回调、对象池等。
​