# Vue基础 - 监视属性

# 内容

> 天气案例

1. 天气案例（methods实现）

<<< @/md/vue/code/vue_basic/09_监视属性/1.天气案例.html

2. 天气案例（监视属性）

<<< @/md/vue/code/vue_basic/09_监视属性/2.天气案例_监视属性.html

> 监视属性watch

1. 当被监视的属性变化时，回调函数自动调用，进行相关操作
2. 监事的属性必须存在，才能进行监视
3. 监视的两种写法
   1. `new Vue`时传入`watch`配置
   2. 通过`vm.$watch()` 监视

4. 深度监视

   1. Vue中的watch默认不监测对象内部值的改变
   2. 配置`deep:true`可以监测对象内部值的改变

<<< @/md/vue/code/vue_basic/09_监视属性/3.天气案例_深度监视.html

5. 简写形式（**只有handler()函数时**）

<<< @/md/vue/code/vue_basic/09_监视属性/4.天气案例_监视属性_简写.html

6. **`computed`和`watch`的区别**
   1. `computed`能完成的功能，`watch`也可以完成
   2. `watch`能完成的功能，`computed`不一定能完成。例如：`watch`可以进行异步操作
7. **两个重要的小原则**
   1. 所有被Vue管理的函数，最好写成普通函数，这样this的指向才是vm 或者 组件实例对象
   2. 所有不被Vue所管理的函数（定时器的回调函数、Ajax的回调函数、Promise的回调函数等）最好写成箭头函数，这样this的指向才是vm 或者 组件实例对象

