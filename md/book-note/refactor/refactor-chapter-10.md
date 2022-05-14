# 第10章 简化函数调用

[[toc]]

**Rename Method(函数改名)**
函数的名称未能揭示函数的用途
修改函数名称

**Add Parameter(添加参数)**
某个函数需要从调用端得到更多信息
为此函数添加一个对象参数 让该对象带进函数所需信息

**Remove Parameter(移除参数)**
函数本体不再需要某个参数
将该参数去除

**Separate Query from Modifier(将查询函数和修改函数分离)**
某个函数既返回对象状态值 又修改对象状态
建立两个不同的函数 其中一个负责查询 另一个负责修改

**Parameterize Method(令函数携带参数)**
若干函数做了类似的工作 但在函数本体中却包含了不同的值
建立单一函数 以参数表达那些不同的值

**Replace Parameter with Explicit Methods(以明确函数取代参数)**
你有一个函数 其中完全取决于参数值而采取不同行为
针对该参数的每一个可能值 建立一个独立函数

**Preserve Whole Object(保持对象完整)**
你从某个对象中取出若干值 将它们作为某一次函数调用时的参数
改为传递整个对象

**Replace Parameter with Methods(以函数取代参数)**
对象调用某个函数 并将所得结果作为参数 传递给另一个函数 而接受该参数的函数本身也能够调用前一个函数
让参数接受者去除该项参数 并直接调用前一个函数

**Introduce Parameter Object(引入参数对象)**
某些参数总是很自然地同时出现
以一个对象取代这些参数

**Remove Setting Method(移除设值函数)**
类中的某个字段应该在对象创建时被设值 然后就不再改变
去掉该字段的所有设值函数

**Hide Method(隐藏函数)**
有一个函数 从来没有被其他任何类用到
将这个函数修改为private

**Replace Constructor with Factory Method(以工厂函数取代构造函数)**
你希望在创建对象时不仅仅是做简单的建构动作
将构造函数替换为工厂函数

**Encapsulate Downcast(封装向下转型)**
某个函数返回的对象 需要由函数调用者执行向下转型
将向下转型动作移到函数中

**Replace Error Code with Exception(以异常取代错误码)**
某个函数返回一个特定的代码 用以表示某种错误情况
改用异常

**Replace Exception with Test(以测试取代异常)**
面对一个调用者可以预先检查的条件 你抛出了一个异常
修改调用者 使它在调用函数之前先做检查
