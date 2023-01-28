# Vue Router - 导航守卫

# 内容

1. 作用：对路由进行权限控制

2. 分类

   * 全局守卫
       * 前置守卫
	   * 解析守卫
	   * 后置守卫
   * 独享守卫
   * 组件内守卫

3. 代码示例

   * 全局守卫

     ```js
     //全局前置守卫：初始化时执行、每次路由切换前执行
     router.beforeEach((to,from,next)=>{
     	console.log('beforeEach',to,from)
     	if(to.meta.isAuth){ //判断当前路由是否需要进行权限控制
     		if(localStorage.getItem('school') === 'atguigu'){ //权限控制的具体规则
     			next() //放行
     		}else{
     			alert('暂无权限查看')
     			// next({name:'guanyu'})
     		}
     	}else{
     		next() //放行
     	}
     })

	 //在 2.5.0+ 你可以用 router.beforeResolve 注册一个全局守卫。这和 router.beforeEach 类似，区别是在导航被确认之前，同时在所有组件内守卫和异步路由组件被解析之后，解析守卫就被调用。
     
     //全局后置守卫：初始化时执行、每次路由切换后执行
     router.afterEach((to,from)=>{
     	console.log('afterEach',to,from)
     	if(to.meta.title){ 
     		document.title = to.meta.title //修改网页的title
     	}else{
     		document.title = 'vue_test'
     	}
     })
     ```

	 路由里配置meta元数据：
	 ```js
	const router =  new VueRouter({
		routes:[
			{
				name:'guanyu',
				path:'/about',
				component:About,
				meta:{title:'关于'}
			},
	 ```

   * 独享守卫

     可以在路由配置上直接定义 beforeEnter 守卫：

     ```js
	 const router =  new VueRouter({
		routes:[
			{
				name:'zhuye',
				path:'/home',
				component:Home,
				meta:{title:'主页'},
				children:[
					{
						name:'xinwen',
						path:'news',
						component:News,
						meta:{isAuth:true,title:'新闻'},
						beforeEnter(to,from,next){
							console.log('beforeEnter',to,from)
							if(to.meta.isAuth){ //判断当前路由是否需要进行权限控制
								if(localStorage.getItem('school') === 'atguigu'){
									next()
								}else{
									alert('暂无权限查看')
									// next({name:'guanyu'})
								}
							}else{
								next()
							}
					}
				]
			}
     ```

   * 组件内守卫

     ```js
     <script>
		export default {
			name:'About',
			...
			//通过路由规则，进入该组件时被调用
			beforeRouteEnter (to, from, next) {
				console.log('About--beforeRouteEnter',to,from)
				if(to.meta.isAuth){ //判断是否需要鉴权
					if(localStorage.getItem('school')==='atguigu'){
						next()
					}else{
						alert('学校名不对，无权限查看！')
					}
				}else{
					next()
				}
			},

			//通过路由规则，离开该组件时被调用
			beforeRouteLeave (to, from, next) {
				console.log('About--beforeRouteLeave',to,from)
				next()
			}
		}
	</script>
     ```

## 完整的导航解析流程

* 导航被触发。
* 在失活的组件里调用 beforeRouteLeave 守卫。
* 调用全局的 beforeEach 守卫。
* 在重用的组件里调用 beforeRouteUpdate 守卫 (2.2+)。
* 在路由配置里调用 beforeEnter。
* 解析异步路由组件。
* 在被激活的组件里调用 beforeRouteEnter。
* 调用全局的 beforeResolve 守卫 (2.5+)。
* 导航被确认。
* 调用全局的 afterEach 钩子。
* 触发 DOM 更新。
* 调用 beforeRouteEnter 守卫中传给 next 的回调函数，创建好的组件实例会作为回调函数的参数传入。