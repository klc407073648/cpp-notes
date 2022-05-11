# gitbook使用

# 参考资料

* [简单实用 | 用Gitbook做笔记 / 写书过程全记录](https://blog.csdn.net/weixin_41024483/article/details/100090621)
* [gitbook init问题解决](https://blog.csdn.net/weixin_42349568/article/details/108414441)
* [GITBOOK折叠菜单](https://www.freesion.com/article/8160301349/)
* [Windows上使用gitbook制作电子书](https://blog.csdn.net/zl1zl2zl3/article/details/71123902)

# 概念介绍

在使用git book之前，首先介绍 Gitbook、Github、Git 这三个东西的概念。

- **git** ：是一个开源的分布式版本控制系统，可以有效、高速地处理从很小到非常大的项目版本管理。
- **GitHub** ：是一个面向开源及私有软件项目的托管平台。类似的基于 git 的版本控制网站，还有 gitlab、gitee 等。
- **git book**：gitbook 跟 git 和 GitHub实际上没有任何关系！最初定位是面向软件说明文档的编写者的，但它同样适合任何类型的文字编辑工作者。不过 git book 可以同时结合强大的 git 和简单美观的 markdown，真的很适合程序员呢。
- **git book与GitHub联姻**：虽然 git book与GitHub 实际上没有任何关系，但是你完全可以把自己的一本书看作 git 里的一个仓库，和其他代码仓库没有任何区别，那么就可以把他托管放置在 GitHub 上。

## gitbook安装

要想安装 git book，就必须要先安装 nodejs，才能支持npm命令。

```
npm install gitbook -g
cnpm install -g gitbook-cli
gitbook init
```

其中gitbook init 会报错

```bash
D:\software\nodejs\node_cache\node_modules\gitbook-cli\node_modules\_npm@5.1.0@npm\node_modules\graceful-fs\polyfills.js:287
      if (cb) cb.apply(this, arguments)
                 ^

TypeError: cb.apply is not a function
    at D:\software\nodejs\node_cache\node_modules\gitbook-cli\node_modules\_npm@5.1.0@npm\node_modules\graceful-fs\polyfills.js:287:18
    at FSReqCallback.oncomplete (fs.js:184:5)
```



可以找到polyfills.js的287行，对应62-64行，直接注释就行。

```
  //fs.stat = statFix(fs.stat)
  //fs.fstat = statFix(fs.fstat)
  //fs.lstat = statFix(fs.lstat)
```

同时,如果gitbook init执行速度慢可以采用：

```
npm config get registry
#切换成淘宝镜像
npm config set registry https://registry.npm.taobao.org

npm config get registry
```



## git折叠菜单

步骤如下：

1. 下载插件

```
npm install gitbook-plugin-toggle-chapters 
```

2. 创建名为 book.json的文件

里面放 如下命令：

```json
{
"plugins":["expandable-chapters"]
}
```

3. 安装

```
gitbook install
```

4. 构建

```
gitbook build 
```

5. 生成web服务界面

```
gitbook serve
```

中间的执行日志：

```
D:\CODE\klc\markdown>gitbook install
info: installing 1 plugins using npm@3.9.2
info:
info: installing plugin "expandable-chapters"
info: install plugin "expandable-chapters" (*) from NPM with version 0.2.0
D:\CODE\klc\markdown
`-- gitbook-plugin-expandable-chapters@0.2.0

info: >> plugin "expandable-chapters" installed with success

D:\CODE\klc\markdown>gitbook build
info: 8 plugins are installed
info: 7 explicitly listed
info: loading plugin "expandable-chapters"... OK
info: loading plugin "highlight"... OK
info: loading plugin "search"... OK
info: loading plugin "lunr"... OK
info: loading plugin "sharing"... OK
info: loading plugin "fontsettings"... OK
info: loading plugin "theme-default"... OK
info: found 73 pages
info: found 1529 asset files
info: >> generation finished with success in 42.9s !

D:\CODE\klc\markdown>gitbook serve
Live reload server started on port: 35729
Press CTRL+C to quit ...

info: 8 plugins are installed
info: loading plugin "expandable-chapters"... OK
info: loading plugin "livereload"... OK
info: loading plugin "highlight"... OK
info: loading plugin "search"... OK
info: loading plugin "lunr"... OK
info: loading plugin "sharing"... OK
info: loading plugin "fontsettings"... OK
info: loading plugin "theme-default"... OK
info: found 82 pages
info: found 1515 asset files
info: >> generation finished with success in 26.8s !

Starting server ...
Serving book on http://localhost:4000
(node:21884) [DEP0066] DeprecationWarning: OutgoingMessage.prototype._headers is deprecated
(Use `node --trace-deprecation ...` to show where the warning was created)

```



![11](/_images/project/practice/gitbook/生成web界面.png)

# gitbook制作

1. 下载ebook-convert，直接到http://www.calibre-ebook.com/download_windows下载：
2. 直接安装软件，并在将安装目录添加到系统path中，默认安装在：C:\Program Files (x86)\Calibre2

3. 生成PDF文件，在电子书存档目录，如：E:\xx\gitbook\mybook_test执行 gitbook pdf .或者上一级目录执行gitbook pdf ./mybook_test

```
D:\CODE\klc\markdown>gitbook pdf .
info: 8 plugins are installed
info: 7 explicitly listed
info: loading plugin "expandable-chapters"... OK
info: loading plugin "highlight"... OK
info: loading plugin "search"... OK
info: loading plugin "lunr"... OK
info: loading plugin "sharing"... OK
info: loading plugin "fontsettings"... OK
info: loading plugin "theme-default"... OK
info: found 82 pages
info: found 1517 asset files
info: >> generation finished with success in 178.2s !
info: >> 1 file(s) generated

生成文件
D:\CODE\klc\markdown\book.pdf
```

