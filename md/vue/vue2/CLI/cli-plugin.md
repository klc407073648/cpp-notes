# Vue脚手架 - 插件

# 内容

1. 作用：增强Vue

2. 本质：包含`install()` 方法的一个对象，`install`的第一个参数是Vue原型对象，第二个以后的参数是插件使用者传递的数据

3. 定义插件

   ```js
   对象.install = function(Vue,options) {
       // 1.添加全局过滤器
       Vue.filter(...)
                  
   	// 2.添加全局指令
       Vue.directive(...)
       
       // 3.配置全局混入
       Vue.mixin(....)
       
       // 4.添加实例方法
       Vue.prototype.$myMethod = function(){...}
       Vue.prototype.$myProperty = xxx
   }
   ```

4. 使用插件：`Vue.use(..)`

5. 示例代码

<<< @/md/vue/vue2/CLI/src/plugin.js

## scoped样式

1. 作用：让样式在局部生效，防止冲突
2. 写法：`<style scoped>`