# Vue中的Ajax - 基础

# 内容

概念：Ajax即Asynchronous Javascript And XML（异步JavaScript和XML）。AJAX 是与服务器交换数据的艺术，**它在不重载全部页面的情况下，实现了对部分网页的更新。**

**同源机制**：协议名，主机名，端口号  ———— **CORS**可以通过代理服务器解决 或者 后端解决

请求方式：

* jQuery
   * 框架比较重，主要用于对于原生DOM操作的封装，同时也支持AJAX方法，支持HTTP的GET,POST等请求。
* axios
   * axios是通过Promise实现对Ajax技术的一种封装，比较轻量、易使用。
* fetch
   * 一种新的获取资源的接口方式，并不是对XMLHttpRequest的封装，且浏览器原生就支持。
* vue-resource
   * 一个非常轻量的用于处理HTTP请求的插件。

## 解决跨域问题

### 方式一

在`vue.config.js`中添加如下配置

```js
devServer:{
  proxy:"http://localhost:5000"
}
```

说明：

* 优点：配置简单，请求资源时直接发送给前端即可
* 缺点：不能配置多个代理，不能灵活的控制请求是否走代理
* 工作方式：若按照上述配置代理，当请求了前端不存在的资源时，那么该请求会转发给服务器（优先匹配服务器）
            （**当使用代理服务器时，如果请求的资源本地存在，则不会进行转发。**）

### 方式二

编写`vue.config.js`配置具体代理规则

```js
module.exports = {
	devServer: {
      proxy: {
      '/api1': {// 匹配所有以 '/api1'开头的请求路径
        target: 'http://localhost:port',// 代理目标的基础路径
        changeOrigin: true,
        pathRewrite: {'^/api1': ''}
      },
      '/api2': {// 匹配所有以 '/api2'开头的请求路径
        target: 'http://localhost:port',// 代理目标的基础路径
        changeOrigin: true,
        pathRewrite: {'^/api2': ''}
      }
    }
  }
}
/*
   changeOrigin设置为true时，服务器收到的请求头中的host为：localhost:5000
   changeOrigin设置为false时，服务器收到的请求头中的host为：localhost:8080
   changeOrigin默认值为true
*/
```

说明：

* 优点：可以配置多个代理，且可以灵活的控制请求是否走代理
* 缺点：配置略微繁琐，请求资源时必须加前缀


