# Vuex - 基础

# 内容

概念：专门在 Vue 中实现集中式状态（数据）管理的一个 Vue **插件**，对 vue 应用中多个组件的**共享**状态进行集中式的管理（读/写），也是一种组件间通信的方式，且适用于任意组件间通信。

Github 地址: https://github.com/vuejs/vuex

工作原理图:

![](/_images/vue/vuex/Vuex工作原理图.png)


## 搭建Vuex环境

1. 安装Vuex

   1. Vue2 => Vuex3 版本

      ```sh
      npm i vuex@3
      ```

2. 创建文件：`src/store/index.js`

   ```js
   // 引入Vue核心
   import Vue from 'Vue'
   // 引入Vuex
   import Vuex from 'vuex'
   // 应用Vuex插件
   Vue.use(Vuex)
   
   // 准备actions对象 => 响应组件中用户的动作
   const actions = {}
   // 准备mutations对象 => 修改state中的数据
   const mutations = {}
   // 准备state对象 => 保存具体的数据
   const state = {}
   // 创建并暴露store
   export default new Vuex.Store({
       actions,
       mutations,
       state
   })
   ```

3. 在`main.js`中创建vm时传入`store`配置项

   ```js
   .......
   // 引入store
   import store from './store'
   .......
   // 创建vm
   new Vue({
     render: h => h(App),
     store
   }).$mount('#app')
   ```
