# Vue Router - 路由传参

# query参数

1. 传递参数

   ```Vue
   <!-- 跳转并携带query参数，to的字符串写法 -->
   <router-link :to="/home/message/detail?id=666&title=你好">跳转</router-link>
   				
   <!-- 跳转并携带query参数，to的对象写法 -->
   <router-link 
   	:to="{
   		path:'/home/message/detail',
   		query:{
   		   id:666,
           title:'你好'
   		}
   	}"
   >跳转</router-link>
   ```

2. 接收参数

   ```js
   <li>消息编号：{{$route.query.id}}</li>
   <li>消息标题：{{$route.query.title}}</li>
   ```

# 命名路由

1. 作用：可以简化路由的跳转

2. 使用方法：

   1. 给路由命名

      ```js
      {
      	path:'/demo',
      	component:Demo,
      	children:[
      		{
      			path:'test',
      			component:Test,
      			children:[
      				{
                        name:'hello' //给路由命名
      					path:'welcome',
      					component:Hello,
      				}
      			]
      		}
      	]
      }
      ```

   2. 简化跳转

      ```vue
      <!--简化前，需要写完整的路径 -->
      <router-link to="/demo/test/welcome">跳转</router-link>
      
      <!--简化后，直接通过名字跳转 -->
      <router-link :to="{name:'hello'}">跳转</router-link>
      
      <!--简化写法配合传递参数 -->
      <router-link 
      	:to="{
      		name:'hello',
      		query:{
      		   id:666,
               title:'你好'
      		}
      	}"
      >跳转</router-link>
      ```

# params参数

1. 配置路由，声明接收`params`参数

   ```js
   {
   	path:'/home',
   	component:Home,
   	children:[
   		{
   			path:'news',
   			component:News
   		},
   		{
   			component:Message,
   			children:[
   				{
   					name:'xiangqing',
   					path:'detail/:id/:title', //使用占位符声明接收params参数
   					component:Detail
   				}
   			]
   		}
   	]
   }
   ```

2. 传递参数

   ```vue
   <!-- 跳转并携带params参数，to的字符串写法 -->
   <router-link :to="/home/message/detail/666/你好">跳转</router-link>
   				
   <!-- 跳转并携带params参数，to的对象写法 -->
   <router-link 
   	:to="{
   		name:'xiangqing',
   		params:{
   		   id:666,
           title:'你好'
   		}
   	}"
   >跳转</router-link>
   ```

> 特别注意**：路由携带params参数时，若使用to的对象写法，则不能使用path配置项，必须使用name配置！**

3. 接收参数

   ```js
   <li>消息编号：{{$route.params.id}}</li>
   <li>消息标题：{{$route.params.title}}</li>
   ```

# props参数

* 作用：让路由组件更方便的接收参数

  ```js
  {
  	name:'xiangqing',
  	path:'detail/:id',
  	component:Detail,
  
  	//第一种写法：props值为对象，该对象中所有的key-value的组合最终都会通过props传给Detail组件
  	// props:{a:900}
  
  	//第二种写法：props值为布尔值，布尔值为true，则把路由收到的所有params参数通过props传给Detail组件
  	// props:true
  	
  	//第三种写法：props值为函数，该函数返回的对象中每一组key-value都会通过props传给Detail组件
  	props(route){
  		return {
  			id:route.query.id,
  			title:route.query.title
  		}
  	}
  }
  ```

# `<router-link>`的replace属性

1. 作用：控制路由跳转时操作浏览器历史记录的模式
2. 浏览器的历史记录的写入模式：`push`和`replace`，`push`是追加历史记录，`replace`是替换当前记录，路由跳转时候默认是`push`
3. 开启`replace`模式：`<router-link replace .......>News</router-link>`