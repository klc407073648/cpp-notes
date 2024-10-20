# Vue基础 - 简介

> 主要介绍Vue的基本概念、特点、常用库等。


# Vue简介

官网：

* 英文官网: https://vuejs.org/
* 中文官网: https://cn.vuejs.org/
* v2.x版本: https://v2.cn.vuejs.org/

概念**：动态构建用户界面**的渐进式`JavaScript`框架

特点:

1. 采用**组件化**模式，提高代码复用率、且让代码更好维护
   ![](/_images/vue/basic/组件化.png)

2. **声明式**编码，让编码人员无需直接操作DOM，提高开发效率
   ```js
   <ul id="root">
       <li v-for="p in persons">
           {{p.id}} - {{p.name}} - {{p.age}}
       </li>
   </ul>
   ```

3. 使用**虚拟DOM**+优秀的**Diff算法**,可复用节点

   ![](/_images/vue/basic/Vue虚拟Dom.png)
   
4. 遵循 MVVM 模式
5. 编码简洁, 体积小, 运行效率高, 适合移动/PC 端开发
6. 它本身只关注 UI, 也可以引入其它第三方库开发项目

与其它 JS 框架的关联

1. 借鉴 Angular 的**模板和数据绑定**技术
2. 借鉴 React 的**组件化**和**虚拟 DOM 技术**

常用相关库：

1. vue-cli: vue 脚手架
2. vue-resource
3. axios
4. vue-router: 路由
5. vuex: 状态管理
6. element-ui: 基于 vue 的 UI 组件库(PC 端)