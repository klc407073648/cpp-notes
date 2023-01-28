# Vue脚手架 - ref和props

# ref属性

1. 作用：给元素或者子组件注册引用信息（id的替代）
2. **应用在html标签上获取的是真实DOM元素，应用在组件标签上是组件实例对象**
3. 使用方式
   1. 标识：`<h1 ref="xxx">...</h1>`或者`<School ref="xxx>></School>`
   2. 获取：`this.$refs.xxx`

# props配置项

1. 作用：让组件接收外部传入的数据（一般用于父组件给子组件传递数据）
2. 传递数据：`<Demo name="XXX"/>`
3. 接收数据：
   1. 方式一（只接收）：`props:['name']`
   2. 方式二（限制类型）：`props:{name:String}`
   3. 方式三（限制类型、限制必要性、指定默认值）：

      ```js
      props:{
          name:{
              type:String, //类型
              required:true, //必要性
              default:'Jason' //默认值    
          }
      }
      ```

   > 备注：props是**只读的**，Vue底层会监测你对props的修改，如果进行了修改，就会发出警告，若业务需求确实需要修改，那么请复制props的内容到data中一份，然后去修改data中的数据
