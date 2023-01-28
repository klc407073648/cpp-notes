# Vue脚手架 - 消息订阅与发布（pubsub)

# 概念

1. 这种方式的思想与全局事件总线很相似

2. 它包含以下操作:

   * 订阅消息 --对应绑定事件监听
   * 发布消息 --分发事件
   * 取消消息订阅 --解绑事件监听
   
3. 需要引入一个消息订阅与发布的第三方实现库: PubSubJS

# 内容

1. 一种组件间通信的方式，适用于<span style="color:red">任意组件间的通信</span>

2. 使用步骤

   1. 安装pubsub:`npm i pubsub-js`

   2. 引入： `import pubsub from 'pubsub-js'`

   3. 接收数据：School组件想要接收数据，则在School组件中订阅消息：
      * 订阅的<span style="color:red">回调留在A中</span>
      * 最好在`beforeDestroy`钩子中，用`pubsub.unsubscribe(pid)`去<span style="color:red">取消订阅</span>

      ```js
      export default {
		name:'School',
		data() {
			return {
				name:'Vue学习',
				address:'北京',
			}
		},
		mounted() {
			this.pubId = pubsub.subscribe('hello',(msgName,data)=>{
				console.log(this)
				// console.log('有人发布了hello消息，hello消息的回调执行了',msgName,data)
			})
		},
		beforeDestroy() {
			pubsub.unsubscribe(this.pubId)
		},
	}
      ```

   4. Student组件提供数据：
   ```js
   methods: {
			sendStudentName(){
				pubsub.publish('hello',666)
			}
		}
   ```


