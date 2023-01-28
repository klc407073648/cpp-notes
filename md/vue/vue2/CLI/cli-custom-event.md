# Vue脚手架 - 自定义事件

# 内容

1. 一种组件间的通信方式，适用于: <strong style="color:red">子组件===>父组件</strong>

2.  使用场景：A是父组件，B是子组件，B想给A传数据，那么就要在A中给B绑定自定义事件（<span style="color:red">事件的回调在A中</span>）

3. 绑定自定义事件

   1. 方式一：在父组件中：`<Demo @mystyle="test"/>` 或者 `<Demo v-on:mystyle="test"/>`

   2. 方式二：在父组件中：

      ```js
      <Demo ref="demo"/>
      .......
      mounted(){
      	this.$refs.demo.$on('mystyle',this.test)
      }
      ```

   3. ​	若想让自定义事件只触发一次，可以使用`once`修饰符或者`$once`方法

4. 触发自定义事件：`this.$emit('mystyle',数据)`

5. 解绑自定义事件：`this.$off('mystyle')`

6. 组件上也可以绑定原生DOM事件，需要使用`native`修饰符

7. 注意：通过`this.$refs.xxx.$on('mystyle',回调)`绑定自定义事件时，**回调**<span style="color:red">要么配置在methods中，要么用箭头函数</span>，否则this指向会有问题


