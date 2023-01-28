# Vue Router - 编程式路由导航

# 内容

## 相关 API

1. this.$router.push(path): 相当于点击路由链接(可以返回到当前路由界面)
2. this.$router.replace(path): 用新路由替换当前路由(不可以返回到当前路由界面)
3. this.$router.back(): 请求(返回)上一个记录路由
4. this.$router.forward(): 请求(返回)下一个记录路由
5. this.$router.go(): 在 history 记录中向前或者后退多少步
    * this.$router.go(-1): 请求(返回)上一个记录路由
    * this.$router.go(1): 请求下一个记录路由

## 使用

1. 作用：不借助`<router-link>`实现路由跳转，让路由跳转更加灵活

2. 代码示例

   ```js
   //$router的两个API
   this.$router.push({
   	name:'xiangqing',
   		params:{
   			id:xxx,
   			title:xxx
   		}
   })
   
   this.$router.replace({
   	name:'xiangqing',
   		params:{
   			id:xxx,
   			title:xxx
   		}
   })
   ```