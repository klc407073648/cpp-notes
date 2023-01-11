# Vue基础 - MVVM模型

# 概念

1. MVVM模型解释
    * M: 模型（Model）=> data中的数据
    * V: 视图（View) => 模板
    * VM: 视图模型（ViewModel) => Vue实例对象

![](/_images/vue/basic/MVVM模型.png)

2. 注意事项
    * data中的所有属性，**最后都出现在vm上**
    * vm上的所有属性及Vue原型上的所有属性，在Vue模板中都可以直接使用

## 数据代理

1. 理解：通过一个对象代理对另一个对象中属性的操作（读/写）

2. Vm中的数据代理
    * **通过vm对象来代理data对象中属性的操作**（读/写）
3. Vue中数据代理的好处
    * 更加方便的操作data中的数据
4. 基本原理
    * 通过`Object.definePorperty()`把data对象中所有属性添加到vm上
    * 为每一个添加到vm上的属性指定一个`getter/setter`
    * 在`getter/setter`内部去操作（读/写）data中对应的属性

<<< @/md/vue/code/vue_basic/06_数据代理/3.Vue中的数据代理.html

![](/_images/vue/basic/数据代理.png)
