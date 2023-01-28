# Vue Router - 生命周期钩子

# 内容

1. 作用：路由组件所独有的两个钩子，用于捕获**路由组件的激活状态**（active-class="active"）

2. 具体名字：
   1. `activated` => 路由组件被激活时触发
   2. `deactivated` => 路由组件失活时触发

3. 使用示例：

   ```js
	<script>
		export default {
			name:'News',
			data() {
				return {
					opacity:1
				}
			},
			activated() {
				console.log('News组件被激活了')
				this.timer = setInterval(() => {
					console.log('@')
					this.opacity -= 0.01
					if(this.opacity <= 0) this.opacity = 1
				},16)
			},
			deactivated() {
				console.log('News组件失活了')
				clearInterval(this.timer)
			},
		}
	</script>
   ```