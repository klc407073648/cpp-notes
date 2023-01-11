# Vue基础 - 列表渲染

## 基本列表

1. `v-for`指令

   1. 用于展示列表数据
   2. 语法：`v-for="(item,index) in xxx" :key="yyy"`
   3. 可遍历：数组、对象、字符串（少）、指定次数（少）

2. 代码示例

<<< @/md/vue/code/vue_basic/12_列表渲染/1.基本列表.html

## key的原理

1. 虚拟DOM中Key的作用 => Key是虚拟DOM对象的**标识**，当数据发生变化时，VUe会根据【新数据】生成【新的虚拟DOM】，随后Vue进行【新虚拟DOM】和【旧虚拟DOM】的差异比较，**比较规则**如下
   1. 旧虚拟DOM中找到与新虚拟DOM相同的Key
      1. 若虚拟DOM中内容没变，直接使用之前的真实DOM
      2. 若虚拟DOM中内容变了，则生成新的真实DOM，随后替换掉页面中之前的真实DOM
   2. 旧虚拟DOM中未找到与新虚拟DOM相同的Key
      1. 创建新的真实DOM，随后渲染到页面

2. 用`index`作为Key可能会引发的问题
   1. 若对数据进行“逆序添加、逆序删除等”破坏顺序的操作 => 会产生没有必要的真实DOM的更新 => 界面渲染没有问题，但是效率低下
   2. 如果结构中还包含输入类DOM => 会产生错误DOM更新 => 界面有问题

3. 开发中选择Key
   1. 使用每条数据的唯一标识作为Key，比如id、手机号、身份证号等
   2. 如果不存在对数据的逆序添加、逆序删除等破坏顺序的操作，仅用于渲染列表展示，使用index作为Key是没有问题的

4. 示意图

   ![](/_images/vue/basic/Key的原理.png)

<<< @/md/vue/code/vue_basic/12_列表渲染/2.key的原理.html

## 列表过滤

<<< @/md/vue/code/vue_basic/12_列表渲染/3.列表过滤.html

## 列表排序

<<< @/md/vue/code/vue_basic/12_列表渲染/4.列表排序.html   

## Vue监视数据的原理

1. Vue会监视`data`中所有层次的数据
2. 监视对象中的数据 => 通过`setter`实现监视，且要在创建Vue示例时就要传入要监视的数据
   1. 对象中后追加的属性，Vue默认不做响应式处理
   2. 如需给后添加的属性做响应式 => 使用API
      1. `Vue.set(target,propertyName/index,value)`
      2. `vm.$set(target,propertyName/index,value)`

3. 监视数组中的数据 => 通过包裹数组更新元素的方法实现，本质做了两件事

   1. 调用Js原生对应的方法对数组进行更新
   2. 重新解析模板，进而更新页面

4. 在Vue修改数组中的某个元素的方法

   1. API:`push()、pop()、shift()、unshift()、splice()、sort()、reverse()`
   2. `Vue.set()` or `vm.$set()`

5. 注意事项

   1. `Vue.set()` 和 `vm.$set()`不能给**vm**或者**vm的根数据对象**添加属性

6. 代码案例

<<< @/md/vue/code/vue_basic/12_列表渲染/10.总结数据监测.html

## 收集表单数据

1. 若：`<input type="text"/>`，则`v-model`收集的是`value`值，用户输入的就是`value`值
2. 若：`<input type="radio"/>`，则`v-model`收集的是`value`值，且要给标签配置`value`值
3. 若：`<input type="checkbox"/>`
   1. 没有配置`input`的`value`属性，那么收集的就是`checked`（勾选 or 未勾选，是布尔值）
   2. 配置`input`的`value`属性
      1. `v-model`的初始值是非数组，那么收集的就是`checked`（勾选 or 未勾选，是布尔值）
      2. `v-model`的初始值是数组，那么收集的的就是`value`组成的数组

4. 代码示例

<<< @/md/vue/code/vue_basic/13_收集表单数据/收集表单数据.html