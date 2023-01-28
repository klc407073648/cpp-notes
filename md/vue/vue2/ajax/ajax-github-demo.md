# Vue中的Ajax - github案例学习

# 内容

```
components
   List.Vue     ————  展示查询到的数据
   Search.Vue   ————  利用axios请求github里输入关键字的内容
App.vue
```

查询结果：axios.get(`https://api.github.com/search/users?q=${this.keyWord}`)

效果图：

![](/_images/vue/ajax/github示例图.png)
