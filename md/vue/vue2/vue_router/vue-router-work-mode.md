# Vue Router - 工作模式

# 内容

vue-router 默认 hash 模式 —— 使用 URL 的 hash 来模拟一个完整的 URL，于是当 URL 改变时，页面不会重新加载。

如果不想要很丑的 hash，可以用路由的 history 模式，这种模式充分利用 history.pushState API 来完成 URL 跳转而无须重新加载页面。

```js
const router = new VueRouter({
  mode: 'history',
  routes: [...]
})
```
hash 和 history 模式的对比：

1. 对于一个`url`，`hash` => #及其之后的内容
    * `hash`值不会包含在HTTP请求中，即`hash`值不会带给服务器
    * `hash`模式：
        1. 地址中永远带着#号，不美观 。
        2. 若以后将地址通过第三方手机app分享，若app校验严格，则地址会被标记为不合法。
        3. 兼容性较好。
2. `history`模式：
   1. 地址干净，美观 。
   2. 兼容性和`hash`模式相比略差。
   3. 应用部署上线时需要后端人员支持，解决刷新页面服务端404的问题。

5. 开启方式：创建路由器时配置

   ```vue
   mode:'history'
   mode:'hash'
   ```