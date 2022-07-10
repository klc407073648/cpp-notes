# 关于 - 文档的排版模板

[[toc]]

# 参考资料

* [Markdown 拓展](https://www.vuepress.cn/guide/markdown.html)

# GitHub 风格的表格

| Tables        | Are           | Cool  |
| ------------- |:-------------:| -----:|
| col 3 is      | right-aligned | $1600 |
| col 2 is      | centered      |   $12 |
| zebra stripes | are neat      |    $1 |

# Emoji

:tada: :100: :wink:

# 目录

```
[[toc]]
```

# 自定义容器

::: tip
这是一个提示
:::

::: warning
这是一个警告
:::

::: danger
这是一个危险警告
:::

::: details
这是一个详情块，在 IE / Edge 中不生效
:::

# 代码块中的行高亮

``` js {4}
export default {
  data () {
    return {
      msg: 'Highlighted!'
    }
  }
}
```

# 导入代码段

```
<<< @/md/c++/features/c11/src/decltype.cpp
```

# 目录结构

```bash
.
├── docs
│   ├── .vuepress (可选的)
│   │   ├── components (可选的)
│   │   ├── theme (可选的)
│   │   │   └── Layout.vue
│   │   ├── public (可选的)
│   │   ├── styles (可选的)
│   │   │   ├── index.styl
│   │   │   └── palette.styl
│   │   ├── templates (可选的, 谨慎配置)
│   │   │   ├── dev.html
│   │   │   └── ssr.html
│   │   ├── config.js (可选的)
│   │   └── enhanceApp.js (可选的)
│   │ 
│   ├── README.md
│   ├── guide
│   │   └── README.md
│   └── config.md
│ 
└── package.json
```

```bash
docs/.vuepress: 用于存放全局的配置、组件、静态资源等。
docs/.vuepress/components: 该目录中的 Vue 组件将会被自动注册为全局组件。
docs/.vuepress/theme: 用于存放本地主题。
docs/.vuepress/styles: 用于存放样式相关的文件。
docs/.vuepress/styles/index.styl: 将会被自动应用的全局样式文件，会生成在最终的 CSS 文件结尾，具有比默认样式更高的优先级。
docs/.vuepress/styles/palette.styl: 用于重写默认颜色常量，或者设置新的 stylus 颜色常量。
docs/.vuepress/public: 静态资源目录。
docs/.vuepress/templates: 存储 HTML 模板文件。
docs/.vuepress/templates/dev.html: 用于开发环境的 HTML 模板文件。
docs/.vuepress/templates/ssr.html: 构建时基于 Vue SSR 的 HTML 模板文件。
docs/.vuepress/config.js: 配置文件的入口文件，也可以是 YML 或 toml。
docs/.vuepress/enhanceApp.js: 客户端应用的增强。
```