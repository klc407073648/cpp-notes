# Vue Router - 多级路由（嵌套路由）

# 内容

1. 配置路由规则，使用`children`配置项

   ```js
   routes:[
           {
               path:'/about',
               component:About
           },
           {
               path:'/home',
               component:Home,
               children:[
                   {
                       path:'news',
                       component:News
                   },
                   {
                       path:'message',
                       component:Message
                   }
               ]
           }
       ]
   ```

2. 跳转（**完整路径**）

   ```vue
   <router-link class="list-group-item" active-class="active" to="/home/news">News</router-link>
   ```