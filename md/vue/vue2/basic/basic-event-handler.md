# Vue基础 - 事件处理

#  事件的基本使用

1. 使用`v-on:XXX` 或者`@XXX`绑定事件，其中`XXX`是事件名

2. 事件的回调需要配置在**methods**对象中，最终会在**vm**上

3. methods中配置的函数，使用普通函数，this的指向是vm 或 组件实例对象；若使用箭头函数 => this 不再是vm

4. `@click="demo"`和`@click="demo($event)"`效果一致，但是后者可以传参

5. 代码示例

<<< @/md/vue/code/vue_basic/07_事件处理/1.事件的基本使用.html

# 事件修饰符

1. `prevent`: 阻止默认事件
2. `stop`: 阻止事件冒泡
3. `once`: 事件只触发一次
4. `capture`: 使用事件的捕获模式
5. `self`: 只有`event.target`是当前操作元素时才触发事件
6. `passive`: 事件的默认行为立即执行，无需等待事件回调执行完毕
7. 代码示例

<<< @/md/vue/code/vue_basic/07_事件处理/2.事件修饰符.html

# 键盘事件

1. Vue中常用的案件别名

   1. 回车 => `enter`
   2. 删除 => `delete `(捕获“删除”和“退格”键)
   3. 退出 => `esc`
   4. 空格 => `space`
   5. 换行 => `tab `(特殊，必须配合keydown去使用)
   6. 上 => `up`
   7. 下 => `down`
   8. 左 => `left`
   9. 右 => `right`

2. Vue未提供别名的按键，可以使用按键原始的key值去绑定，但注意要转为kebab-case（短横线命名）

3. 系统修饰键（用法特殊）：`ctrl`、`alt`、`shift`、`meta`

   1. 配合`keyup`使用：按下修饰键的同时，再按下其他键，随后释放其他键，事件才被触发
   2. 配合`keydown`使用：正常触发事件

4. 可以使用keyCode去指定具体的按键（不推荐）

5. `Vue.config.keyCodes.自定义键名 = 键码`  => 定制按键别名

6. 代码示例

<<< @/md/vue/code/vue_basic/07_事件处理/3.键盘事件.html
