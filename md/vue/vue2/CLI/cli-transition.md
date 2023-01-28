# Vue脚手架 - Vue封装的过渡和动画

# 内容

1. 作用：在插入、更新或者移除DOM元素时，在合适的时候给元素添加样式类名

2. 图示：

   ![](/_images/vue/CLI/Vue封装的过渡和动画.png)

3. 写法：

   1. 准备好样式：
      * 元素进入的样式
        1. `v-enter`:进入的起点
        2. `v-enter-active`:进入过程中
        3. `v-enter-to`:进入的终点
      * 元素离开的样式
        1. `v-leave`:离开的起点
        2. `v-leave-active`:离开过程中
        3. `v-leave-to`:离开的终点

   2. 使用`<transition>`包裹要过渡的元素，并配置name属性

      ```html
      <transition name="hello">
      	<h1 v-show="isShow">你好啊！</h1>
      </transition>
      ```
      
   3. 备注：若有多个元素需要过渡，则需要使用:`<transition-group>`，且每个元素都要指定`key`值
