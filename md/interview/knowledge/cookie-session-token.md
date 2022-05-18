# cookie,session与token的区别

[[toc]]

## 概述

发展史，最早的web就是简单地浏览文档内容，但是随着交互式Web应用的兴起，例如在线购物网站，需要登陆的网站等，<font color='red'>将面临管理会话的难题，必须记录用户登录状态和购买物品的信息等</font>。因为HTTP请求是无状态的，所以考虑引入会话标识session id 来区分用户。发展到一定程度后，服务器存储成百上千万的session id会影响应用的扩展，例如机器AB需要进行session id 数据复制，才能保证在机器A宕机的情况下，机器B仍然能够识别用户的登陆状态。最终，引入了token机制来验证，将服务端的存储压力转移到客户端。

* cookie：诞生于服务器，发送给浏览器，浏览器把cookie以kv形式保存到某个目录下的文本文件内，下一次请求同一网站时会把该cookie发送给服务器。
  * 身份认证：服务器获取请求中的用户名和密码，判断和数据库的数据是否一致，如果数据一致，就回写用户名和密码的cookie到浏览器，跳转到主页。否则，响应用户或密码错误。
  * 保持登录状态：浏览器请求其他网页时，服务器判断是否有cookie数据，如果有就证明用户是在线的，显示对应界面。否则，表明用户不在线，需要重新登陆。

* session：诞生并保存于服务器中，由服务器主导一切，服务器使用session把用户的信息临时保存在了服务器上，用户离开网站后session会被销毁。
  * 身份认证：获取用户数据和数据库数据判断，如果数据相同就开辟sessoon，并将数据存入session域，回写sessionID，跳转到主页。否则，响应用户和密码错误。
  * 保持登陆状态：浏览器访问其他页面，判断sessionID是否一致，如果id一致就证明用户是在线的，去获取session域里的数据再去拿数据库数据，将数据显示到页面上。否则，表明用户并不在线，需要重新登录。

* token：诞生于服务器，但存储在客户端中，由客户端主导一切，可以放在cookie或者storage里面，持有token就像持有“令牌”一样允许访问服务器。服务器仅保存JWT签名密文。
  * 用途：用户后面每次登录都携带首次都登录生成的token字符串用于验证，能做到这点，关键就是token使用的某种算法根据用户签名和其它一些信息生成的令牌信息是一致的，可以验证通过
  * 优点：对于用户量庞大的系统，或者分布式，<font color='red'>避免了大量session对象的存储带来的内存消耗</font>，和各服务器之间session的复制或者专门用于存储session的服务器宕机带来的问题

## JWT的作用

JWT(JSON Web Token)

JWT由三部分组成(header.payload,signature)

* header:声明需要用什么算法生成签名
* payload:一些特定数据，例如有效期等
* signature:header和payload会经过Base64编码，再加上JWT签名密文，三者通过特定算法，最终得到签名信息

 ![JWT](/_images/interview/token/JWT.png)

## 基于服务器的验证

我们都是知道<font color='red'>HTTP协议是无状态的，这种无状态意味着程序需要验证每一次请求，从而辨别客户端的身份。</font>

在这之前，程序都是通过<font color='red'>在服务端存储的登录信息来辨别请求的</font>。这种方式一般都是通过<font color='red'>存储Session来完成</font>。

随着Web，应用程序，已经移动端的兴起，这种验证的方式逐渐暴露出了问题。尤其是在可扩展性方面。

基于服务器验证方式暴露的一些问题：

1. Seesion：每次认证用户发起请求时，服务器需要去创建一个记录来存储信息。当越来越多的用户发请求时，内存的开销也会不断增加。

2. 可扩展性：在服务端的内存中使用Seesion存储登录信息，伴随而来的是可扩展性问题。

3. CORS(跨域资源共享)：当我们需要让数据跨多台移动设备上使用时，跨域资源的共享会是一个让人头疼的问题。在使用Ajax抓取另一个域的资源，就可以会出现禁止请求的情况。

4. CSRF(跨站请求伪造)：用户在访问银行网站时，他们很容易受到跨站请求伪造的攻击，并且能够被利用其访问其他的网站。

在这些问题中，可扩展行是最突出的。因此我们有必要去寻求一种更有行之有效的方法。

## 基于Token的验证原理

基于Token的身份验证是无状态的，我们不将用户信息存在服务器或Session中。

这种概念解决了在服务端存储信息时的许多问题

No Session意味着你的程序可以根据需要去增减机器，而不用去担心用户是否登录。

<font color='red'>基于Token的身份验证的过程如下</font>:

1. 用户通过用户名和密码发送请求。

2. 程序验证。

3. 程序返回一个签名的token 给客户端。

4. 客户端储存token,并且每次用于每次发送请求。

5. 服务端验证token并返回数据。

每一次请求都需要token。token应该在HTTP的头部发送从而保证了Http请求无状态。<font color='red'>我们同样通过设置服务器属性Access-Control-Allow-Origin:* ，让服务器能接受到来自所有域的请求。</font>

需要主要的是，在ACAO头部标明(designating)*时，不得带有像HTTP认证，客户端SSL证书和cookies的证书。

<font color='red'>实现思路：</font>

1. 用户登录校验，校验成功后就返回Token给客户端。

2. 客户端收到数据后保存在客户端

3. 客户端每次访问API是携带Token到服务器端。

4. 服务器端采用filter过滤器校验。校验成功则返回请求数据，校验失败则返回错误码

当我们在程序中认证了信息并取得token之后，我们便能通过这个Token做许多的事情。

我们甚至能基于创建一个基于权限的token传给第三方应用程序，这些第三方程序能够获取到我们的数据（当然只有在我们允许的特定的token）

## Token的优势
### 无状态、可扩展

在客户端存储的Tokens是无状态的，并且能够被扩展。基于这种无状态和不存储Session信息，负载负载均衡器能够将用户信息从一个服务传到其他服务器上。

如果我们将已验证的用户的信息保存在Session中，则每次请求都需要用户向已验证的服务器发送验证信息(称为Session亲和性)。用户量大时，可能会造成一些拥堵。

但是不要着急。使用tokens之后这些问题都迎刃而解，因为tokens自己hold住了用户的验证信息。

### 安全性

请求中发送token而不再是发送cookie能够防止CSRF(跨站请求伪造)。即使在客户端使用cookie存储token，cookie也仅仅是一个存储机制而不是用于认证。不将信息存储在Session中，让我们少了对session操作。

token是有时效的，一段时间之后用户需要重新验证。我们也不一定需要等到token自动失效，token有撤回的操作，通过token revocataion可以使一个特定的token或是一组有相同认证的token无效。

### 可扩展性

Tokens能够创建与其它程序共享权限的程序。例如，能将一个随便的社交帐号和自己的大号(Fackbook或是Twitter)联系起来。当通过服务登录Twitter(我们将这个过程Buffer)时，我们可以将这些Buffer附到Twitter的数据流上(we are allowing Buffer to post to our Twitter stream)。

使用tokens时，可以提供可选的权限给第三方应用程序。当用户想让另一个应用程序访问它们的数据，我们可以通过建立自己的API，得出特殊权限的tokens。

### 多平台跨域

我们提前先来谈论一下CORS(跨域资源共享)，对应用程序和服务进行扩展的时候，需要介入各种各种的设备和应用程序。

Having our API just serve data, we can also make the design choice to serve assets from a CDN. This eliminates the issues that CORS brings up after we set a quick header configuration for our application.

只要用户有一个通过了验证的token，数据和资源就能够在任何域上被请求到。

Access-Control-Allow-Origin: *      

基于标准创建token的时候，你可以设定一些选项。我们在后续的文章中会进行更加详尽的描述，但是标准的用法会在JSON Web Tokens体现。

最近的程序和文档是供给JSON Web Tokens的。它支持众多的语言。这意味在未来的使用中你可以真正的转换你的认证机制。

