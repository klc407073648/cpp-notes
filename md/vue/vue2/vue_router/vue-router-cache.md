# Vue Router - 缓存组件

# 内容

1. 组件：让不展示的路由组件保持挂载，不被销毁(在展示组件的地方挂载)

2. 代码示例

* 通过`keep-alive`标签来控制路由组件，不被销毁
* **include** => 组件名，可以指定保持挂载的组件名称
   ```vue
   <template>
		<div>
			<h2>Home组件内容</h2>
			<div>
				<ul class="nav nav-tabs">
					<li>
						<router-link class="list-group-item" active-class="active" to="/home/news">News</router-link>
					</li>
					<li>
						<router-link class="list-group-item" active-class="active" to="/home/message">Message</router-link>
					</li>
				</ul>
				<!-- 缓存多个路由组件 -->
				<!-- <keep-alive :include="['News','Message']"> -->
					
				<!-- 缓存一个路由组件 -->
				<keep-alive include="News">
					<router-view></router-view>
				</keep-alive>
			</div>
		</div>
	</template>

	<script>
		export default {
			name:'Home',
			/* beforeDestroy() {
				console.log('Home组件即将被销毁了')
			}, */
			/* mounted() {
				console.log('Home组件挂载完毕了',this)
				window.homeRoute = this.$route
				window.homeRouter = this.$router
			},  */
		}
	</script>
   ```