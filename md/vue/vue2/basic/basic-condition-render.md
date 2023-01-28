# Vue基础 - 条件渲染

# 内容

1. `v-if`

   * 写法：
      * `v-if="表达式"`
      * `v-else-if="表达式"`
      * `v-else="表达式"`
   * 注意事项
      1. `v-if`可以和`v-else-if`、`v-else`一起使用，但要求结构不能被“打断”

2. `v-show`

   * 写法：`v-show="表达式"`

3. v-if和v-show的主要区别

* v-if适用于切换频率较低的场景，而v-show适用于切换频率较高的场景。
* 使用v-if不展示的DOM元素会被从DOM树中删除掉，而使用v-show不展示的DOM元素未被删除掉，仅仅是将样式隐藏起来。
   ![](/_images/vue/basic/条件渲染.png)
* 使用v-if的时，元素可能无法获取到，而使用v-show一定可以获取到。


4. 代码案例

<<< @/md/vue/code/vue_basic/09_监视属性/4.天气案例_监视属性_简写.html