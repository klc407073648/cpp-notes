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
          showDepth: 3,
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
    ],
    ['@vssue/vuepress-plugin-vssue', {
        // 设置平台，而不是 `api` 
        platform: 'github-v4',
        // 其他的 Vssue 配置
        owner: 'klc407073648', // 仓库的拥有者的名称
        repo: 'C++全栈知识体系', 
        clientId: 'b7c43bb6b9b38ea67c09', //Client ID  
        clientSecret: '9ea7a28c16600b06211061693996400bbdc49eb9', //Client secrets
        autoCreateIssue: true,//自动创建评论
      },
    ]
    //<global-RightBar/>
    /*{
        name: 'page-plugin',
        globalUIComponents: ['global-RightBar'],
    },*/
]