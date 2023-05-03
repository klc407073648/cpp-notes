const nav = require('./config/nav')
const sidebar = require('./config/sidebar')
const plugins = require('./config/plugins')
const markdown = require('./config/markdown')

module.exports = {
    //theme: '@vuepress/blog',
    port: "3000",
    dest: "docs",
    ga: "UA-85414008-1",
    base: "/",
    markdown, //vuepress Markdown 拓展 配置
    locales: {
        "/": {
            lang: "zh-CN",
            title: "C++ 全栈知识体系",
            description: "包含：C++, 算法, 数据库, 编程四大件, 开发, 架构|微服务|中间件, 方法论, 工具|部署, 项目, 读书笔记, 文章, 成长, 前端学习, 日常使用 ..."
        }
    },
    head: [
        ["link", { rel: "icon", href: `/favicon.ico` }],
        ["meta", { name: "referrer", content: 'strict-origin-when-cross-origin' }],
        // 添加百度统计代码
        /*
        ['script', 
          {},
          `var _hmt = _hmt || [];
          (function() {
            var hm = document.createElement("script");
            hm.src = "https://hm.baidu.com/hm.js?1c71fc16572da6aad12188a3de4122fc";
            var s = document.getElementsByTagName("script")[0]; 
            s.parentNode.insertBefore(hm, s);
          })();`,
        ]
        */
        // baidu statstic
        ["script", { src: "https://hm.baidu.com/hm.js?1c71fc16572da6aad12188a3de4122fc" }]
    ],
    plugins,
    themeConfig: {
        docsRepo: "stibel/cpp-notes",
        editLinks: true,
        sidebarDepth: 0,
        locales: {
            "/": {
                label: "简体中文",
                selectText: "Languages",
                editLinkText: "在 GitHub 上编辑此页",
                lastUpdated: "上次更新",
                nav,
                sidebar,
            }
        }
    }
};