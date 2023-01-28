# Vue脚手架 - 全局事件总线

> 在main.js中创建全局事件总线，然后在组件A中绑定和解绑($on和$off)，组件B中发送消息($emit)

# 概念

1. Vue 原型对象上包含事件处理的方法:

1) $on(eventName, listener): 绑定自定义事件监听
2) $emit(eventName, data): 分发自定义事件
3) $off(eventName): 解绑自定义事件监听
4) $once(eventName, listener): 绑定事件监听, 但只能处理一次

2. 所有组件实例对象的原型对象的原型对象就是 Vue 的原型对象

1) 所有组件对象都能看到 Vue 原型对象上的属性和方法
2) Vue.prototype.$bus = new Vue(), 所有的组件对象都能看到$bus 这个属性对象

3. 全局事件总线

1) 包含事件处理相关方法的对象(只有一个)
2) 所有的组件都可以得到

# 使用

1. 一种组件间通信的方式，适用于<span style="color:red">任意组件间的通信</span>

2. 安装全局事件总线，main.js

   ```js
   new Vue({
       ......
       beforeCreate(){
       	Vue.prototype.$bus = this // 安装全局事件总线，$bus就是当前应用的vm
   	},
   })
   ```

3. 使用事件总线：

   1. 接收数据：School组件想要接收数据，则在School组件中给`$bus`绑定自定义事件：
      * 事件的<span style="color:red">回调留在组件自身</span>
      * 用`$off`去解绑<span style="color:red">当前组件所用到的</span>事件

      ```js
      <script>
         export default {
            name:'School',
            data() {
               return {
                  name:'Vue学习',
                  address:'北京',
               }
            },
            mounted() {
               this.$bus.$on('hello',(data)=>{
                  console.log('我是School组件，收到了数据',data)
               })
            },
            beforeDestroy() {
               this.$bus.$off('hello')
            },
         }
      </script>
      ```

   2. 提供数据：在组件Student中，使用emit来发送数据：
     
      ```js
      methods: {
            sendStudentName(){
               this.$bus.$emit('hello',this.name)
            }
         }
      ```
