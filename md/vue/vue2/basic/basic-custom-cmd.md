# Vue基础 - 自定义指令

# 内容

1. 定义语法

   1. 局部指令

      ```html
      new Vue({
      	directives:{指令名：配置对象}
      })
      <!-- 或者 -->
      new Vue({
      	directives:{指令名：回调函数}
      })
      ```

   2. 全局指令

      ```html
      Vue.directive(指令名,配置对象)
      <!-- 或者 -->
      Vue.directive(指令名,回调函数)
      ```

2. 配置对象中常用的3个回调

   1. `bind`:指定与元素成功绑定时调用
   2. `inserted`:指令所在的元素被插入页面时调用
   3. `update`:指令所在的模板被重新解析时调用

3. 备注

   1. 指令定义时不加v-，但是使用时要在v-
   2. 指令名如果是多个单词，要使用`kabab-case`命名方式，不要使用`camelCase`命名

   备注：kebab-case: 短横线隔开命名法,每个单词首字母小写。 `user-name`
         camel-case: 驼峰式命名法。 `userName`

# 代码实例

<<< @/md/vue/code/vue_basic/16_自定义指令/1.自定义指令.html
