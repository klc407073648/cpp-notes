# Vue基础 - 数据绑定

# 内容

1. 分类
    * 单向绑定（v-bind）:数据只能从data流向页面
    * 双向绑定（v-model):数据不仅能从data流向页面，还可以从页面流向data。
2. 注意事项
    * 双向绑定一般都应用在**表单类元素上**（如：input、select等）
    * v-model:value可以简写为v-model,因为v-model默认收集的就是value值。

3. 代码实例

<<< @/md/vue/code/vue_basic/03_数据绑定/数据绑定.html


# el 和 data的两种写法

1. el的两种写法
    *  `new Vue()`的时候配置el属性
    * 先创建Vue实例，随后通过`vm.$mount(’挂载的容器‘)`指定el的值
2. data的两种写法
    * 对象式
    * 函数式（写成**普通函数** => this对象是当前的Vue实例）

3. 代码实例

<<< @/md/vue/code/vue_basic/04_el与data的两种写法/el与data的两种写法.html
