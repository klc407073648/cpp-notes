# Vue组件 - 非单文件组件

# 内容

## 基本使用

1. Vue中使用组件的三大步骤
   1. 定义组件（创建组件）
   2. 注册组件
   3. 使用组件（写组件标签）

2. 定义组件
   1. 使用`Vue.extend(options)`创建，其中`options`和`new Vue(options)`时传入的`options`几乎一样
   2. 区别：
      1. 不写`el` => 最终所有的组件都要经过一个vm的管理，由vm中的el决定
      2. 函数式`data` => 避免组件被复用时，数据存在引用关系
   3. 备注
      1. 使用`template`可以配置组件结构

3. 注册组件
   1. 局部注册：靠`new Vue()`的时候传入`components`选项
   2. 全局注册：靠`Vue.component('组件名',组件)`
   
4. 编写组件标签
   1. `<组件名></组件名>`

5. 代码示例

<<< @/md/vue/code/vue_basic/18_非单文件组件/1.基本使用.html

## 注意事项

1. 关于组件名:

   1. 一个单词组成
      1. 第一种写法(首字母小写)：school
      2. 第二种写法(首字母大写)：School

   2. 多个单词组成：

      1. 第一种写法(kebab-case命名)：my-school
      2. 第二种写法(CamelCase命名)：MySchool (需要Vue脚手架支持)

   3. 备注：

      1. 组件名尽可能回避HTML中已有的元素名称，例如：h2、H2都不行。
      2. 可以使用name配置项指定组件在开发者工具中呈现的名字

2. 关于组件标签:

   1. 第一种写法：<school></school>
   2. 第二种写法：<school/>
   3. 备注：不用使用脚手架时，<school/>会导致后续组件不能渲染。

3. 一个简写方式
   1. `const school = Vue.extend(options) ` => `const school = options`

4. 代码示例

<<< @/md/vue/code/vue_basic/18_非单文件组件/2.几个注意点.html

## 组件的嵌套

1. 代码示例

<<< @/md/vue/code/vue_basic/18_非单文件组件/3.组件的嵌套.html

2. 嵌套示意图

![](/_images/vue/component/组件的嵌套.png)

## VueComponent

1. 组件的本质是一个名为`VueComponent`的构造函数，不是由程序员定义，是`Vue.extend`生成的 

2. 编写组件标签时，`Vue`解析时会帮我们创建组件的实例对象，即`Vue`帮我们执行的：`new VueComponent(options)`

3. 特别注意：每次调用`Vue.extend`，返回的都是一个全新的`VueComponent`

   ```js
   Vue.extend = function (extendOptions) {
             /*………………*/
             var Sub = function VueComponent(options) {
                 this._init(options);
             };
             /*………………*/
             return Sub;
         };
   ```

4. 关于this指向

   1. 组件配置中

      data函数、methods中的函数、watch中的函数、computed中的函数，它们的this均是【**VueComponent实例对象**】

   2. `new Vue(options)`配置中

      data函数、methods中的函数、watch中的函数、computed中的函数，它们的this均是【**Vue实例对象**】

5. VueComponent的实例对象，以后简称vc（也可称之为：组件实例对象）

   Vue的实例对象，以后简称vm

6. 代码示例

<<< @/md/vue/code/vue_basic/18_非单文件组件/4.VueComponent.html

## 一个重要的内置关系

1. `VueComponent.prototype.__proto__ === Vue.prototype`
2. 作用 => **让组件实例对象能够访问到Vue原型上的属性、方法**
3. 分析示意图

![](/_images/vue/component/Vue和VueComponent关系.png)
