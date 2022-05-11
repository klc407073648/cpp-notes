# 第9章 简化条件表达式

**Decompose Conditional(分解条件表达式)**
你有一个复杂的条件(if-then-else)语句
从if then else三个段落中分别提炼出独立函数

**Consolidate Conditional Expression(合并条件表达式)**
你有一系列条件测试 都得到相同结果
将这些测试合并为一个条件表达式 并将这个条件表达式提炼成为一个独立函数

**Consolidate Duplicate Conditional Fragments(合并重复的条件片段)**
在条件表达式的每个分支上有着相同的一段代码
将这段重复代码搬移到条件表达式之外

**Remove Control Flag(移除控制标记)**
在一系列布尔表达式中 某个变量带有 控制标记 的作用
以break语句或return语句取代控制标记

**Replace Nested Conditional with Guard Clauses(以卫语句取代嵌套条件表达式)**
函数中的条件逻辑使人难以看清正常的执行路径
使用卫语句表现所有特殊情况

**Replace Conditional with Polymorphism(以多态取代条件表达式)**
你手上有个条件表达式 它根据对象类型的不同而选择不同的行为
将这个条件表达式的每个分支放进一个子类内的覆写函数中 然后将原始函数声明为抽象函数

**Introduce Null Object(引入Null对象)**
你需要再三检查某对象是否为null
将null值替换为null对象

**Introduce Assertion(引入断言)**
某一段代码需要对程序状态做出某种假设
以断言明确表现这种假设
