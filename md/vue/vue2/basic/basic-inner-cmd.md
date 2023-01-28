# Vue基础 - 内置指令

# 已学的内置命令

>已经学过的指令
>
>1. v-bind   : 单向绑定解析表达式, 可简写为 :xxx
>2. v-model  : 双向数据绑定
>3. v-for    : 遍历数组/对象/字符串
>4. v-on     : 绑定事件监听, 可简写为@
>5. v-if     : 条件渲染（动态控制节点是否存存在）
>6. v-else   : 条件渲染（动态控制节点是否存存在）
>7. v-show   : 条件渲染 (动态控制节点是否展示,通过给标签加上 `display: none` 来实现)

## v-text

1. 作用：向其所在的节点中渲染文本内容
2. 与插值语法的区别：`v-text`会替换掉节点中的内容，`{{xx}}`不会

<<< @/md/vue/code/vue_basic/15_内置指令/1.v-text_指令.html

## v-html

1. 作用：向指定节点中渲染包含html结构的内容
2. 与插值语法的区别
   1. `v-html`会替换掉节点中所有的内容，`{{xx}}`不会
   2. `v-html`可以识别html结构
3. 注意事项
   1. **v-html有安全性问题**
      1. 在网站上动态渲染任意HTML是非常危险的，容易导致XSS攻击
      2. 一定要在可信的内容上使用`v-html`，永远不要使用在用户提交的内容上

<<< @/md/vue/code/vue_basic/15_内置指令/2.v-html_指令.html

## v-cloak

1. 没有值
2. 本质是一个特殊属性，**Vue实例创建完毕并接管容器后，会删掉`v-vloak`属性**
3. 使用css配合`v-cloak`可以解决网速慢时页面展示出现`{{XXX}}`的问题

<<< @/md/vue/code/vue_basic/15_内置指令/3.v-cloak_指令.html

## v-once

1. `v-once`所在的节点在初次动态渲染后，就被视为静态内容
2. 以后数据的改变不会引起`v-once`所在结构的更新，可以用于优化性能

<<< @/md/vue/code/vue_basic/15_内置指令/4.v-once_指令.html

## v-pre

1. 跳过其所在节点的编译过程
2. 可利用他跳过：没有使用指令语法、没有使用插值语法的节点，会加快编译

<<< @/md/vue/code/vue_basic/15_内置指令/5.v-pre_指令.html