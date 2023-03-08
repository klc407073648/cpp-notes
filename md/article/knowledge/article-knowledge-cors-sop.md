# 知识 - 服务网格

> Service Mesh 是微服务时代的 TCP/IP 协议。

[[toc]]

# 参考资料

* [同源策略（SOP](https://en.wikipedia.org/wiki/Same-origin_policy)
* [跨源资源共享](https://en.wikipedia.org/wiki/Cross-origin_resource_sharing) 

## 同源策略

在计算领域，**同源策略（SOP，Same origin policy）**是网络应用程序安全模型中的一个重要概念。根据该政策，Web 浏览器允许第一个网页中包含的脚本访问第二个网页中的数据，但前提是两个网页具有相同的来源。源被定义为**URI 协议、主机名和端口号**的组合。此策略**可防止一个页面上的恶意脚本通过该页面的文档对象模型**获取对另一个网页上敏感数据的访问权限。

这种机制对于广泛依赖HTTP cookie 来维护经过身份验证的用户会话的现代 Web 应用程序具有特殊意义，因为服务器基于 HTTP cookie 信息来显示敏感信息或采取状态更改操作。必须在客户端维护不相关站点提供的内容之间的严格分离，以防止数据机密性或完整性丢失。

记住同源策略只适用于脚本是非常重要的。这意味着可以通过相应的 HTML 标签跨源访问图像、CSS 和动态加载的脚本等资源（字体是一个明显的例外）。攻击利用了同源策略不适用于 HTML 标记这一事实。

* 放宽同源政策
    * 数据污染
    * 文档.域属性
    * 跨源资源共享
    * 跨文档消息传递
    * JSONP
    * WebSockets

## 跨源资源共享

CORS(Cross origin resource sharing)是一种机制，允许从提供第一个资源的域之外的另一个域请求网页上的受限资源。

网页可以自由嵌入跨源图像、样式表、脚本、iframe和视频。同源安全策略默认禁止某些“跨域”请求，尤其是Ajax请求。CORS 定义了一种方式，浏览器和服务器可以通过这种方式进行交互以确定允许跨源请求是否安全。它允许比纯粹的同源请求更多的自由和功能，但比简单地允许所有跨源请求更安全。（一般只服务端（后端）设置Access-Control-Allow-Origin即可，前端无须设置，若要带cookie请求：前后端都需要设置。）

例如：在spring boot中提供了 @CrossOrigin 注解用于解决跨域问题。

```java
//origin="*"代表所有域名都可访问
//maxAge飞行前响应的缓存持续时间的最大年龄，简单来说就是Cookie的有效期 单位为秒若maxAge是负数,则代表为临时Cookie,不会被持久化,Cookie信息保存在浏览器内存中,浏览器关闭Cookie就消失
@CrossOrigin(origins = "*",maxAge = 3600)
```

与 CORS 相关的 HTTP 标头是：

* 请求标头
    * Origin                              源
    * Access-Control-Request-Method       请求的方法
    * Access-Control-Request-Headers      请求的头

* 响应头
    * Access-Control-Allow-Origin       允许请求的域
    * Access-Control-Allow-Credentials  表示是否允许发送cookie
    * Access-Control-Expose-Headers     暴露的头
    * Access-Control-Max-Age            本次预检的有效期
    * Access-Control-Allow-Methods      允许请求的方法
    * Access-Control-Allow-Headers      允许请求的头


预检示例：

在执行某些类型的跨域 Ajax 请求时，支持 CORS 的现代浏览器会发起一个额外的“预检”请求，以确定它们是否有权执行该操作。跨源请求以这种方式进行预检，因为它们可能会对用户数据产生影响。

以百度搜索，关键词"haha"为例，可以看到存在两次请求：

![](/_images/article/knowledge/百度搜索预检.png)

“预检”请求和响应结果：

![](/_images/article/knowledge/百度搜索预检请求与响应.png)

正式请求和响应结果：

![](/_images/article/knowledge/百度搜索正式请求与响应.png)

可以看出预检请求方法为OPTIONS，正式请求方法为POST；且预检请求响应结果为Content-Type为 text/plain，正式请求响应结果为Content-Type为 application/json。


