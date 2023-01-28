# Vue Router - 基本使用

# 内容

1. 安装vue-router（Vue2 => vue-router3)

   ```sh
   npm i vue-router@3
   ```

2. 应用插件：`Vue.use(VueRouter)`

3. 编写router配置项:`src/router/index.js`

   ```js
   // 专门用于创建整个应用的路由器
   import VueRouter from "vue-router";
   
   // 引入组件
   import About from '@/components/About'
   import Home from '@/components/Home'
   
   // 创建并暴露路由
   export default new VueRouter({
       routes:[
           {
               path:'/about',
               component:About
           },
           {
               path:'/home',
               component:Home
           }
       ]
   })
   ```

4. 实现切换(`active-class`可以配置高亮样式)

   ```vue
   <router-link active-class="active" to="/about">About</router-link>
   ```

5. 指定展示位置

   ```vue
   <router-view></router-view>
   ```

## 注意事项

1. 路由组件通常存放在```pages```文件夹，一般组件通常存放在```components```文件夹
2. 通过切换，“隐藏”了的路由组件，**默认是被销毁掉的，需要的时候再去挂载**
3. 每个组件都有自己的```$route```属性，里面**存储着自己的路由信息**
4. 整个应用只有一个router，可以通过组件的```$router```属性获取到