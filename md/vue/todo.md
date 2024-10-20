## console.dir(vm)

console.dir() 方法: 用来对一个对象进行检查(inspect)，并以易于阅读和打印的格式显示。该方法对于输入 DOM 对象非常有用，因为 dir 方法会显示DOM对象的所有属性

console.log(Promise):可以看到一个输出的是 HTML 结构 
console.dir(Promise) :一个类似于 JSON 结构.


webpack

Vue组件需要export

App.vue 汇总所有组件


main.js是入口文件或者是index.js

根据官网内容再进行补充

babel  ES6 ===> ES5 转换工具
eslint 语法检查


## package.json 和 package-lock.json

* package.json：记录当前项目所依赖模块的版本信息，更新模块时**锁定模块的大版本号（第一位）,不能锁定后面的小版本**。
* package-lock.json：package-lock.json 是在 `npm install`时候生成一份文件。记录了node_modules目录下所有模块（包）的名称、版本号、下载地址、及这个模块又依赖了哪些依赖。

两者区别：

* npm5以前
    
	* npm5以前，没有package-lock.json这个文件。package.json文件会记录你项目中所需要的所有模块。
	* 当你执行npm install的时候，node会先从package.json文件中读取所有dependencies信息，然后根据dependencies中的信息与node_modules中的模块进行对比，没有的直接下载，已有的检查更新。
	* 因为package.json只能锁定模块的大版本号（版本号的第一位），不能锁定后面的小版本，所以你每次重新npm install时候拉取的都是该大版本下面最新的版本。一般我们为了稳定性考虑我们不能随意升级依赖包，因为如果换包导致兼容性bug出现很难排查，这样很容易出现问题，所以package-lock.json就是来解决包锁定不升级问题的
	* 另外，package.json文件只记录你通过npm install方式安装的模块信息，而这些模块所依赖的其他子模块的信息不会记录。

* npm5以后
        
	* package-lock.json文件**锁定所有模块的版本号，包括主模块和所有依赖子模块**。
	* 当你执行npm install的时候，node从package.json文件读取模块名称，从package-lock.json文件中获取版本号，然后进行下载或者更新。
	* 因此，正因为有了package-lock.json文件锁定版本号，所以当你执行npm install的时候，node不会自动更新package.json文件中的模块，必须用npm install packagename@x.x.x（指定版本号）来进行安装才会更新，package-lock.json文件中的版本号也会随着更新。

* package-lock.json的作用

如果重新 npm install 的时候以及当node_modules文件夹并不存在或被删除时，需要用到npm install重新装载全部依赖时，通过package-lock.json可以直接表明下载地址和相关依赖，就无需再从package.json逐个分析包的依赖项，因此会**大大加快安装速度**，package-lock.json目的就是**确保所有库包与你上次安装的完全一样**。  

备注：npm install 会生成 package-lock.json；yarn install 会生成yarn.lock
	  JS 包管理工具 (npm,yarn)
	  
	  
Vue：核心 + 模板解析器

直接引入 import Vue from 'vue' 实际上是引入 vue/dist/vue.runtime.esm.js  其中esm指代ES module

"module": "dist/vue.runtime.esm.js"
	  
	  
vue.config.js 是 webpack 里面的默认配置合并 

lintOnSave eslint语法检查

一般情况下，用户只输入对象数据相关的内容例如名称、性别等，id字段由数据库的默认策略或ID生成算法来决定

本地存储localStorage, 
JSON.stringify(Obj) : JavaScript 对象或值转换为 JSON 字符串
JSON.parase(Obj): 将数据转换为 JavaScript 对象    

**学习一下JSON和数组原生JS语法**

转为JSON字符串的用处：

本地存储的时候只能是存储基本数据类型，数组和对象等类型存入的话会是[object,object]，所以存数组或对象类型时，我们就可以想把数组或对象转为JSON字符串形式，就可以了。
向后端传递参数时，有时数组或对象类型参数，后端接收的是字符串格式，所以我们在向后端传递的时候，可以向用JSON.stringify()转为字符串格式就可以了。

实现深拷贝
实际开发中，如果怕影响原数据，我们常深拷贝出一份数据做任意操作
JSON.parse(JSON.stringify(obj))我们一般用来深拷贝，其过程就是利用JSON.stringify 将js对象序列化（JSON字符串），再使用JSON.parse来反序列化(还原)js对象；
   
Vue pina状态管理

事件总线，和5G网络中的总线  Namf  SBI总线

* 需要对应
	* $on 和 $off(beforeDestory)
	* subscribe 和 unsubscribe(beforeDestory)

* 消息发布和订阅 pubsub-js
	* 思考 发布者 和 接收者 

* 风格一致的css写在App.Vue中 不加scoped

展不展示 用v-show 比v-if好
	  
refs

**vuepress能设置编译忽略的路径吗**

解决Vue项目中，vueRouter 使用 history 模式访问资源 404 的问题。

　　1.安装 connect-history-api-fallback

connect-history-api-fallback 中间件很好的解决了这个问题。具体来说，每当出现符合以下条件的请求时，它将把请求定位到你指定的索引文件(默认为 /index.html)。

请求是Get请求
请求的Content-Type类型是text/html类型
不是直接的文件请求，即所请求的路径不包含.(点)字符
不匹配option参数中提供的模式
————————————————
版权声明：本文为CSDN博主「astonishqft」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/astonishqft/article/details/82762354

npm install babel-plugin-component -D     : -D表示 开发依赖，关注一下webpack教程 

整理前端 构建工具 和常用  客户端 UI和移动端UI组件库内容


	  
	  
	  
