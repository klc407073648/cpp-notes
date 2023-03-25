module.exports = 
[
    ['@vuepress/active-header-links', {
        sidebarLinkSelector: '.sidebar-link',
        headerAnchorSelector: '.header-anchor'
    }], //页面滚动时自动激活侧边栏链接的插件
    ['@vuepress/search', {
        search: true,
        searchMaxSuggestions: 10
    }],
    ['@vuepress/back-to-top', true],
    ['vuepress-plugin-code-copy', true],
    ['@vuepress/medium-zoom', {
        selector: 'img',
        options: {
            margin: 16
        }
    }],
    ['copyright', {
        noCopy: false, // 允许复制内容
        minLength: 50, // 如果长度超过 100 个字符
        authorName: "https://stibel.icu",
        // clipboardComponent: "请注明文章出处, [Java 全栈知识体系](https://pdai.tech)"
    }],
    /*['sitemap', {
        hostname: 'https://stibel.icu'
    }],*/
    ['vuepress-plugin-baidu-autopush', {}],
    /* 锚点导航栏 showDepth=2 显示H2和H3标签*/
    ['vuepress-plugin-right-anchor',
        {
          showDepth: 2,
          ignore: [
            '/',
            '/api/'
            // more...
          ],
          expand: {
            trigger: 'hover',
            clickModeDefaultOpen: true
          },
          //customClass: 'your-customClass',
        }
    ]
]