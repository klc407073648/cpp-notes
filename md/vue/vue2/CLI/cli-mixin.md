# Vue脚手架 - 混入

# mixin（混入）

作用：可以把多个组件共用的配置提取成一个混入对象


## 使用方式：

需要导出和引入

1. 定义混合

```js
export const hunhe = {
	methods: {
		showName(){
			alert(this.name)
		}
	},
	mounted() {
		console.log('你好啊！')
	},
}
export const hunhe2 = {
	data() {
		return {
			x:100,
			y:200
		}
	},
}

```
2. 使用混入
   1. 全局混入：`Vue.mixin(XXX)`
   2. 局部混入：`mixins:['XXX']`

全局混入

```js
//引入Vue
import Vue from 'vue'
//引入App
import App from './App.vue'
import {hunhe,hunhe2} from './mixin'
//关闭Vue的生产提示
Vue.config.productionTip = false

Vue.mixin(hunhe)
Vue.mixin(hunhe2)


//创建vm
new Vue({
	el:'#app',
	render: h => h(App)
})
```

局部混入，在School.vue在script里引入

```js
<script>
	//引入一个hunhe
	import {hunhe,hunhe2} from '../mixin'

	export default {
		name:'School',
		data() {
			return {
				name:'尚硅谷',
				address:'北京',
				x:666
			}
		},
		mixins:[hunhe,hunhe2],
	}
</script>
```

3. 查看效果

在School.vue里即可使用混入引入的函数showName

```Vue
<template>
	<div>
		<h2 @click="showName">学校名称：{{name}}</h2>
		<h2>学校地址：{{address}}</h2>
	</div>
</template>
```

* 注意点：混入式，data数据以Component里自身的data为准，会进行覆盖