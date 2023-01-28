# Vue脚手架 - todoList案例

# 组件化开发过程

1. 组件化编码流程：
  1. 拆分静态组件：组件要按照**功能点拆分，命名不要与html元素冲突**。
  2. 实现动态组件：考虑好数据的存放位置，数据是**一个组件在用，还是一些组件在用**：
   1. 一个组件在用：放在组件自身即可
   2. 一些组件在用：放在他们共同的父组件上（<span style="color:red">状态提升</span>）
  3. 实现交互：从绑定事件开始

2. props适用于：
   1. 父组件 ==> 子组件 通信
   2. 子组件 ==> 父组件 通信（要求父先给子一个函数）
3. 使用v-model时要切记：v-model绑定的值不能是props传过来的值，因为props是不可以修改的！
4. props传过来的若是对象类型的值，修改对象中的属性时Vue不会报错，但不推荐这样做。


# webStorage

1. 存储内容大小一般支持5MB左右（依照浏览器）
2. 浏览器端通过`Window.localStorage`和`window.sessionStorage`属性来实现本地存储机制
3. 相关API
   1. `xxxStorage.setItem('key','value')` => 该方法接受一个键和值作为参数，会把键值对添加到存储中，如果键名存在，则更新其对应的值
   2. `xxxStorage.getItem('key')`         => 该方法接受一个键名作为参数，返回键名对应的值
   3. `xxxStorage.removeItem('key')`      => 该方法接受一个键名作为参数，并把该键名从存储中删除
   4. `xxxStorage.clear()`                => 该方法会清空存储中的所有数据
4. 备注
   1. LocalStorage的存储的内容需要手动清除才会消失
   2. SessionStorage存储的内容会随着浏览器窗口关闭而消失
   3. `xxxStorage.getItem('key')`如果key对应的Value获取不到，则此方法的返回值为null
   4. `Json.parse(null)`的结果依然是null



localStorage和sessionStorage对比：

|              | localStorage                                                 | sessionStorage                                               |
| ------------ | :----------------------------------------------------------- | :----------------------------------------------------------- |
| 生命周期     | 永久的，关闭页面或浏览器之后数据也不会消失。（除非主动删除数据） | 仅在当前会话下有效（关闭了浏览器窗口后就会被销毁。）。引入了“浏览器窗口”的概念，sessionStorage是在同源的窗口中始终存在的数据。（只要这个浏览器窗口没有关闭，即使刷新页面或者进入同源另一个页面，数据依然存在。同时独立的打开同一个窗口同一个页面，sessionStorage也是不一样的。 ） |
| 作用域       | 相同浏览器的不同标签在同源情况下可以共享                     | 只在当前标签可用，当前标签的iframe中且同源可以共享           |
| 存储大小     | 一般都是：5MB                                                | 同样                                                         |
| 存储位置     | 保存在客户端，不与服务器进行交互通信。                       | 同样                                                         |
| 存储内容类型 | 只能存储字符串类型，对于复杂的对象可以使用ECMAScript提供的JSON对象的stringify和parse来处理 | 同样                                                         |
| 获取方式     | window.localStorage                                          | window.sessionStorage                                        |
| 应用场景     | 常用于长期登录（+判断用户是否已登录），适合长期保存在本地的数据。 | 敏感账号一次性登录                                           |

原文链接：https://blog.csdn.net/XiaoSen207/article/details/123385073
