# Vue脚手架 - 基础使用

# 初始化脚手架

## 说明

1. Vue脚手架是Vue官方提供的标准化开发工具（开发平台）
2. 最新的版本是4.x
3. 文档地址：https://cli.vuejs.org/zh/

## 具体步骤

* 官方文档：[Home | Vue CLI (vuejs.org)](https://cli.vuejs.org/zh/)

1. 安装**nodejs** 环境

   参考文档：https://www.cnblogs.com/netcore5/p/15259499.html

2. （仅第一次执行）：全局安装`@vue/cli`

   ```sh
   npm install -g @vue/cli
   # OR
   yarn global add @vue/cli
   ```

3. **切换到要创建项目的目录**，执行命令

   ```sh
   vue create my-project
   # OR
   vue ui
   ```

* 示意图

   ![](/_images/vue/basic/创建第一个vue项目.png)

* 备注
  * 创建项目过程如果报错，使用管理员权限打开`cmd`
  * 运行过程出现名称错误
    * 解决方案一： `ctrl + p` => `vue.config.js` => 添加配置 `lintOnSave:false`
  * Vue脚手架**隐藏了所有webpack相关的配置**，若想查看具体的webpack配置，执行

    ```sh
    vue inspect > output.js
    ```

## 脚手架文件结构

```
├── node_modules 
├── public
│   ├── favicon.ico: 页签图标
│   └── index.html: 主页面
├── src
│   ├── assets: 存放静态资源
│   │   └── logo.png
│   │── component: 存放组件
│   │   └── HelloWorld.vue
│   │── App.vue: 汇总所有组件
│   │── main.js: 入口文件
├── .gitignore: git版本管制忽略的配置
├── babel.config.js: babel的配置文件
├── package.json: 应用包配置文件 
├── README.md: 应用描述文件
├── package-lock.json：包版本控制文件
```

## render()函数 

**特殊的函数**

关于不同版本的Vue

1. `vue.js`与`vue.runtime.xxx.js`的区别：
   1. `vue.js`是完整版的Vue，包含**：核心功能**+**模板解析器**
   2. `vue.runtime.xxx.js`是运行版的Vue，**只**包含：核心功能；没有模板解析器

2. 因为`vue.runtime.xxx.js`没有模板解析器，所以不能使用template配置项，需要使用
​      `render`函数接收到的`createElement`函数去指定具体内容

## 脚手架默认配置

* 官方文档：[配置参考 | Vue CLI (vuejs.org)](https://cli.vuejs.org/zh/config/)

* 查看Vue脚手架默认配置

  ```sh
  vue inspect > output.js
  ```