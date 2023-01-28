# Vue3 - 创建Vue3.0工程

# 使用 vue-cli 创建

官方文档：https://cli.vuejs.org/zh/guide/creating-a-project.html#vue-create

```bash
## 查看@vue/cli版本，确保@vue/cli版本在4.5.0以上
vue --version
## 安装或者升级你的@vue/cli
npm install -g @vue/cli
## 创建
vue create vue_test
## 启动
cd vue_test
npm run serve
```

# 使用 vite 创建

官方文档：https://v3.cn.vuejs.org/guide/installation.html#vite

vite官网：https://vitejs.cn

- 什么是vite？—— 新一代前端构建工具。
- 优势如下：
  - 开发环境中，**无需打包操作，可快速的冷启动。**
  - 轻量快速的热重载（HMR）。
  - 真正的**按需编译**，不再等待整个应用编译完成。
- 传统构建 与 vite构建对比图

![](/_images/vue/vue3/bundle.png)

![](/_images/vue/vue3/esm.png)

```bash
## 创建工程
npm init vite-app <project-name>
## 进入工程目录
cd <project-name>
## 安装依赖
npm install
## 运行
npm run dev
```