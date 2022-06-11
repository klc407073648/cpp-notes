module.exports = {
    port: "3000",
    dest: "docs",
    ga: "UA-85414008-1",
    base: "/",
    //vuepress Markdown 拓展 配置
    markdown: {
        lineNumbers: true, // 行号
        externalLinks: {
            target: '_blank', rel: 'noopener noreferrer'  // 外部链接
        },
        anchor: { permalink: false }, // markdown-it-anchor 
        toc: {
            includeLevel: [1, 2, 3, 4]  // markdown-it-toc 生成markdown目录层次
        }
    },
    locales: {
        "/": {
            lang: "zh-CN",
            title: "C++ 全栈知识体系",
            description: "包含：C++ 基础, 算法, 数据库,MySQL, ElasticSearch, Redis, 编程四大件, 微服务 , 中间件, ZeroMQ, 部署工具, Docker, k8s, Istio, Linux, 实践|项目,  开源项目, 个人项目, 读书笔记, 面试题, 优质文章, 博客推荐..."
        }
    },
    head: [
        ["link", { rel: "icon", href: `/favicon.ico` }],
        // 添加百度统计代码
        ['script', {},
            `
            var _hmt = _hmt || [];
            (function() {
            var hm = document.createElement("script");
            hm.src = "https://hm.baidu.com/hm.js?1c71fc16572da6aad12188a3de4122fc";
            var s = document.getElementsByTagName("script")[0]; 
            s.parentNode.insertBefore(hm, s);
            })();
            `
        ]
    ],
    plugins: [
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
            minLength: 100, // 如果长度超过 100 个字符
            authorName: "https://stibel.icu",
            // clipboardComponent: "请注明文章出处, [Java 全栈知识体系](https://pdai.tech)"
        }],
        /*['sitemap', {
            hostname: 'https://stibel.icu'
        }],*/
        ['vuepress-plugin-baidu-autopush', {}]
    ],
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
                nav: [
                    {
                        text: 'C++',
                        items: [
                            {
                                text: 'C++ 函数学习',
                                items: [
                                    { text: '函数学习', link: '/md/c++/function/c++-function-Linux_Hook.md' }
                                ]
                            },
                            {
                                text: 'C++ 知识点',
                                items: [
                                    { text: '知识点', link: '/md/c++/tips/c++-tips-copy-on-write.md' }
                                ]
                            },
                            {
                                text: 'C++ 新版本特性',
                                items: [
                                    { text: '新版本特性 详解', link: '/md/c++/features/c++-features-index.md' }
                                ]
                            },
                            {
                                text: 'C++ IO框架',
                                items: [
                                    { text: 'IO框架 详解', link: '/md/c++/io/c++-io-reuse.md' }
                                ]
                            },
                            {
                                text: 'C++ 常用库学习',
                                items: [
                                    { text: '常用库学习 详解', link: '/md/c++/tools/c++-tools-cppcheck.md' }
                                ]
                            }
                        ]
                    },
                    {
                        text: '算法',
                        items: [
                            { text: '领域算法', link: '/md/algorithm/domain/alg-domain-bloom-filter.md' },
                            { text: '分布式算法', link: '/md/algorithm/distribute/alg-distribute-raft.md' },
                        ]
                    },
                    {
                        text: '数据库',
                        items: [
                            {
                                text: 'SQL 数据库',
                                items: [
                                    { text: 'MySQL', link: '/md/database/mysql/mysql-basic-concept.md' }
                                ]
                            },
                            {
                                text: 'NoSQL 数据库',
                                items: [
                                    { text: 'Redis', link: '/md/database/redis/redis-basic-application.md' },
                                    { text: 'ElasticSearch', link: '/md/database/es/es-install.md' }
                                ]
                            }
                        ]
                    },
                    {
                        text: '编程四大件',
                        items: [
                            { text: '数据结构与算法', link: '/md/programming/network/network-physical.md' },
                            { text: '计算机网络', link: '/md/programming/network/network-physical.md' },
                            { text: '操作系统', link: '/md/programming/network/network-physical.md' },
                            { text: '设计模式', link: '/md/programming/designpattern/designpattern-overview' }
                        ]
                    },
                    {
                        text: '开发',
                        items: [
                            { text: '开发', link: '/md/develop/todo.md' },
                        ]
                    },
                    {
                        text: '微服务',
                        items: [
                            { text: '微服务框架', link: '/md/micro-services/frame/frame-architecture.md' }
                        ]
                    },
                    {
                        text: '架构',
                        items: [
                            { text: '架构基础', link: '/md/arch/frame/arch-frame-evolution.md' }
                        ]
                    },
                    {
                        text: '中间件',
                        items: [
                            { text: 'ZeroMQ', link: '/md/middleware/zeromq/zeromq-demo.md' }
                        ]
                    },
                    {
                        text: '方法论|概念',
                        items: [
                            { text: '理论|概念', link: '/md/method/concept/doc.md' }
                        ]
                    },
                    {
                        text: '工具|部署',
                        items: [
                            {
                                text: '工具',
                                items: [
                                    { text: 'Linux', link: '/md/devops/linux/linux-cmd-tips.md' },
                                    { text: 'Nginx', link: '/md/devops/nginx/nginx-study-note.md' },
                                ]
                            },
                            {
                                text: '部署',
                                items: [
                                    { text: 'Docker', link: '/md/devops/docker/docker.md' },
                                    { text: 'Kubernetes', link: '/md/devops/k8s/k8s.md' },
                                    { text: 'Service Mesh Istio', link: '/md/devops/istio/istio-basic.md' },
                                ]
                            }
                        ]
                    },
                    {
                        text: '实践|项目',
                        items: [
                            {
                                text: '实践',
                                items: [
                                    { text: 'Docker-MySQL', link: '/md/project/practice/Docker-MySQL.md' }
                                ]
                            },
                            {
                                text: '开源项目学习',
                                items: [
                                    { text: '开源协程库 libco', link: '/md/project/opensource/libco/libco.md' },
                                    { text: 'buttonrpc', link: '/md/project/opensource/buttonrpc/buttonrpc-basic.md' },
                                    { text: 'Tars', link: '/md/project/opensource/tars/tars-brief.md' }
                                ]
                            },
                            {
                                text: '个人github项目总结',
                                items: [
                                    { text: 'build_lib', link: '/md/project/person/build_lib/build_lib.md' }
                                ]
                            }
                        ]
                    },
                    {
                        text: '读书笔记',
                        items: [
                            {
                                text: '深入理解计算机系统',
                                items: [
                                    { text: '深入理解计算机系统 详解', link: '/md/book-note/computersystem/computersystem-chapter-1.md' }
                                ]
                            },
                            {
                                text: '重构改善既有代码的设计',
                                items: [
                                    { text: '重构改善既有代码的设计 详解', link: '/md/book-note/refactor/refactor-chapter-1.md' }
                                ]
                            },
                            {
                                text: 'Effective C++:改善程序与设计的55个具体做法',
                                items: [
                                    { text: 'Effective C++:改善程序与设计的55个具体做法 详解', link: '/md/book-note/effectivecpp/effectivecpp-chapter-2-1.md' }
                                ]
                            },
                            {
                                text: 'STL源码剖析',
                                items: [
                                    { text: 'STL源码剖析 详解', link: '/md/book-note/stlsource/stlsource-chapter-1.md' }
                                ]
                            },
                            {
                                text: 'Linux多线程服务端编程——使用muduo C++ 网络库',
                                items: [
                                    { text: 'Linux多线程服务端编程——使用muduo C++ 网络库 详解', link: '/md/book-note/muduo/muduo-chapter-1.md' }
                                ]
                            }
                        ]
                    },
                    {
                        text: '面试',
                        items: [
                            {
                                text: '八股文',
                                items: [
                                    { text: '八股文 详解', link: '/md/interview/knowledge/cplusplus-knowledge.md' }
                                ]
                            },
                            {
                                text: 'LeetCode编程题',
                                items: [
                                    { text: '数据结构', link: '/md/interview/code/data-structure/data-structure-overview.md' },
                                    { text: '刷题套路', link: '/md/interview/code/question-routine/question-routine-backtrack.md' },
                                    { text: '题型分类', link: '/md/interview/code/question-type/question-type-array.md' }
                                ]
                            }
                        ]
                    },
                    {
                        text: '优质文章|博客推荐',
                        items: [
                            { text: '分布式相关', link: '/md/article/distribute/article-distributed-cellular.md' }
                        ]
                    },
                    {
                        text: '专业知识',
                        items: [
                            { text: '专业知识', link: '/md/knowledge/todo.md' }
                        ]
                    },
                    {
                        text: '在线技术文档',
                        items: [
                            { text: '官网技术文档', link: '/md/tech-doc/online/doc.md' }
                        ]
                    },
                    {
                        text: '关于', link: '/md/about/me/about-me.md'
                    }
                ],
                sidebar: {
                    "/md/c++/": genSidebar4Cplusplus(),
                    "/md/database/": genSidebar4Database(),
                    "/md/algorithm/": genSidebar4Alg(),
                    "/md/programming/": genSidebar4Program(),
                    "/md/develop/": genSidebar4develop(),
                    "/md/micro-services/": genSidebar4microServices(),
                    "/md/arch/": genSidebar4arch(),
                    "/md/middleware/": genSidebar4middleware(),
                    "/md/method/": genSidebar4method(),
                    "/md/devops/": genSidebar4Devops(),
                    "/md/project/": genSidebar4project(),
                    "/md/book-note/": genSidebar4booknote(),
                    "/md/interview/": genSidebar4interview(),
                    "/md/article/": genSidebar4Article(),
                    "/md/knowledge/": genSidebar4knowledge(),
                    "/md/tech-doc/": genSidebar4techdos(),
                    "/md/about/": genSidebar4About(),
                }
            }
        }
    }
};

// C++ page
function genSidebar4Cplusplus() {
    return [
        {
            title: "C++ 函数学习",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "function/c++-function-Linux_Hook.md",
                "function/c++-function-parseCmdLine.md",
                "function/c++-function-scopeFun.md",
                "function/c++-function-share_ptrUse.md",
                "function/c++-function-structUse.md",
                "function/c++-function-typedefUse.md",
                "function/c++-function-va_listFun.md"
            ]
        },
        {
            title: "C++ 知识点",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "tips/c++-tips-copy-on-write.md",
                "tips/c++-tips-forward-declaration.md",
                "tips/c++-tips-search-head-lib.md"
            ]
        },
        {
            title: "C++ IO框架",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "io/c++-io-reuse.md",
                "io/c++-io-select.md",
                "io/c++-io-poll.md",
                "io/c++-io-epoll.md",
                "io/c++-io-reactor-proactor.md"
            ]
        },
        {
            title: "C++ 新版本特性",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "features/c++-features-index.md",
                "features/c11/c++-features-c11.md",
                "features/c14/c++-features-c14.md",
                "features/c17/c++-features-c17.md",
                "features/c20/c++-features-c20.md"
            ]
        },
        {
            title: "C++ 常用库",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "tools/c++-tools-cppcheck.md",
                "tools/c++-tools-cppunit.md",
                "tools/c++-tools-fastcgi.md",
                "tools/c++-tools-hiredis.md",
                "tools/c++-tools-jsoncpp.md",
                "tools/c++-tools-log4cpp.md",
                "tools/c++-tools-mysql.md",
                "tools/c++-tools-poco.md"
            ]
        }
    ]
}

// Database page
function genSidebar4Database() {
    return [
        {
            title: "SQL - MySQL",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "mysql/mysql-basic-concept.md",
                "mysql/mysql-basic-3nf.md",
                "mysql/mysql-basic-datatype-constraint.md",
                "mysql/mysql-basic-view.md",
                "mysql/mysql-basic-use.md",
                "mysql/mysql-basic-tips.md",
                "mysql/mysql-basic-cursor.md",
                "mysql/mysql-group-query.md",
                "mysql/mysql-join-query.md",
                "mysql/mysql-sub-query.md",
                "mysql/mysql-store-procedure.md",
                "mysql/mysql-cond-judge.md",
                "mysql/mysql-index-design.md",
                "mysql/mysql-index-content.md",
                "mysql/mysql-db-devide.md",
                "mysql/mysql-store-engine.md",
                "mysql/mysql-performance-opt.md",
                "mysql/mysql-sql-execute.md",
                "mysql/mysql-sql-parse.md",
            ]
        },
        {
            title: "NoSQL - Redis",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "redis/redis-basic-application.md",
                "redis/redis-persistence.md",
                "redis/redis-transaction-operation.md",
                "redis/redis-delete-policy.md",
                "redis/redis-master-slave-replication.md",
                "redis/redis-sentinel-mode.md",
                "redis/redis-cluster-application.md",
                "redis/redis-enterprise-solution.md"
            ]
        },
        {
            title: "NoSQL - ElasticSearch",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "es/es-install.md",
                "es/es-cluster-deployment.md",
                "es/es-cluster.md",
                "es/es-data-analysis-process.md",
                "es/es-data-search.md",
                "es/es-data-store.md",
                "es/es-db-syn.md"
            ]
        }
    ];
}

// Alg page
function genSidebar4Alg() {
    return [
        {
            title: "领域算法",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "domain/alg-domain-bloom-filter.md"
            ]
        },
        {
            title: "分布式算法",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "distribute/alg-distribute-raft.md"
            ]
        }
    ];

}

// Program page
function genSidebar4Program() {
    return [
        {
            title: "计算机网络",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "network/network-physical.md",
                "network/network-data-link.md",
                "network/network-network.md",
                "network/network-transport.md",
                "network/network-application.md",
                "network/network-concept.md"
            ]
        },
        {
            title: "设计模式",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "designpattern/designpattern-overview.md",
                "designpattern/designpattern-singleton.md",
                "designpattern/designpattern-observer.md",
                "designpattern/designpattern-factory.md"
            ]
        }
    ];

}

//develop page
function genSidebar4develop() {
    return [
        {
            title: "开发",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "todo.md"
            ]
        }
    ];
}

// micro-services page
function genSidebar4microServices() {
    return [
        {
            title: "微服务框架",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "frame/frame-architecture.md",
                "frame/frame-distributed-search.md",
                "frame/frame-distributed-transaction.md",
                "frame/frame-gateway.md",
                "frame/frame-idempotent-design.md",
                "frame/frame-message-queue.md",
                "frame/frame-multi-level-cache.md",
                "frame/frame-protection.md",
                "frame/frame-registration-discovery.md",
                "frame/frame-study-route.md"
            ]
        }
    ];

}

// arch page
function genSidebar4arch() {
    return [
        {
            title: "架构基础",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "frame/arch-frame-evolution.md",
                "frame/arch-frame-service.md"
            ]
        }
    ];
}

// middleware page
function genSidebar4middleware() {
    return [
        {
            title: "ZeroMQ",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "zeromq/zeromq-demo.md",
                "zeromq/zeromq-part1.md",
                "zeromq/zeromq-part2.md",
                "zeromq/zeromq-part3.md"
            ]
        }
    ];
}

// method page
function genSidebar4method() {
    return [
        {
            title: "理论|概念",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "concept/doc.md"
            ]
        }
    ];
}

// Devops page
function genSidebar4Devops() {
    return [
        {
            title: "Linux",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "linux/linux-cmd.md",
                "linux/linux-signal.md",
                "linux/linux-thread.md",
                "linux/linux-process.md",
                "linux/linux-process-thread-syn.md",
                "linux/linux-cmd-tips.md",
                "linux/linux-output-with-color.md"
            ]
        },
        {
            title: "Web服务器 - nginx",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "nginx/nginx-study-note.md",
                "nginx/nginx-staic-web.md",
                "nginx/nginx-reverse-proxy-server.md",
                "nginx/nginx-error-log.md"
            ]
        },
        {
            title: "容器化 - Docker",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "docker/docker.md",
                "docker/docker-use.md",
                "docker/docker-cmd.md"
            ]
        },
        {
            title: "容器编排 - Kubernetes",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "k8s/k8s.md",
                "k8s/k8s-base-use.md",
                "k8s/k8s-cmd.md",
                "k8s/k8s-probe.md",
                "k8s/k8s-note.md"
            ]
        },
        {
            title: "服务网格 - Service Mesh Istio",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "istio/istio-basic.md",
                "istio/istio-install.md",
                "istio/istio-use.md",
                "istio/istio-architecture-resolution.md",
                "istio/istio-observability.md",
                "istio/istio-k8s-install.md"
            ]
        }
    ];
}

// project page
function genSidebar4project() {
    return [
        {
            title: "实践",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "practice/Docker-MySQL.md",
                "practice/Docker-Redis.md",
                "practice/Git.md",
                "practice/gitbook-use.md",
                "practice/git-config-key.md",
                "practice/Jenkins.md",
                "practice/ngx-admin-install.md",
                "practice/Robot-Framework-install.md",
                "practice/nginx-image-server-cfg.md"
            ]
        },
        {
            title: "开源项目 - libco",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "opensource/libco/libco.md"
            ]
        },
        {
            title: "开源项目 - buttonrpc",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "opensource/buttonrpc/buttonrpc-basic.md",
                "opensource/buttonrpc/buttonrpc-intro.md",
                "opensource/buttonrpc/buttonrpc-demo.md"
            ]
        },
        {
            title: "开源项目 - Tars",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "opensource/tars/tars-brief.md",
                "opensource/tars/tars-basic.md",
                "opensource/tars/tars-cpp-dev.md",
                "opensource/tars/tars-go-dev.md",
                "opensource/tars/tars-docker-dev.md",
                "opensource/tars/tars-gateway-dev.md"
            ]
        },
        {
            title: "个人项目 - build_lib",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "person/build_lib/build_lib.md"
            ]
        }
    ];
}

// book-note page
function genSidebar4booknote() {
    return [
        {
            title: "深入理解计算机系统 详解",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "computersystem/computersystem-chapter-1.md",
                "computersystem/computersystem-chapter-2.md",
                "computersystem/computersystem-chapter-3.md",
                "computersystem/computersystem-chapter-5.md",
                "computersystem/computersystem-chapter-6.md",
                "computersystem/computersystem-chapter-7.md",
                "computersystem/computersystem-chapter-8.md",
                "computersystem/computersystem-chapter-9.md",
                "computersystem/computersystem-chapter-10.md",
                "computersystem/computersystem-chapter-11.md",
                "computersystem/computersystem-chapter-12.md"
            ]
        },
        {
            title: "重构改善既有代码的设计 详解",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "refactor/refactor-chapter-1.md",
                "refactor/refactor-chapter-2.md",
                "refactor/refactor-chapter-3.md",
                "refactor/refactor-chapter-5.md",
                "refactor/refactor-chapter-6.md",
                "refactor/refactor-chapter-7.md",
                "refactor/refactor-chapter-8.md",
                "refactor/refactor-chapter-9.md",
                "refactor/refactor-chapter-10.md",
                "refactor/refactor-chapter-11.md",
                "refactor/refactor-chapter-12.md"
            ]
        },
        {
            title: "Effective C++:改善程序与设计的55个具体做法 详解",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "effectivecpp/effectivecpp-chapter-2-1.md",
                "effectivecpp/effectivecpp-chapter-2-2.md",
                "effectivecpp/effectivecpp-chapter-2-3.md",
                "effectivecpp/effectivecpp-chapter-3.md",
                "effectivecpp/effectivecpp-chapter-4-1.md",
                "effectivecpp/effectivecpp-chapter-4-2.md",
                "effectivecpp/effectivecpp-chapter-5-1.md",
                "effectivecpp/effectivecpp-chapter-5-2.md",
                "effectivecpp/effectivecpp-chapter-6.md",
                "effectivecpp/effectivecpp-chapter-7.md"
            ]
        },
        {
            title: "STL源码剖析 详解",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "stlsource/stlsource-chapter-1.md",
                "stlsource/stlsource-chapter-2.md",
                "stlsource/stlsource-chapter-3-1.md",
                "stlsource/stlsource-chapter-3-2.md",
                "stlsource/stlsource-chapter-4-1.md",
                "stlsource/stlsource-chapter-4-2.md",
                "stlsource/stlsource-chapter-4-3.md",
                "stlsource/stlsource-chapter-4-4.md",
                "stlsource/stlsource-chapter-4-5.md",
                "stlsource/stlsource-chapter-4-6.md",
                "stlsource/stlsource-chapter-4-7.md",
                "stlsource/stlsource-chapter-5-1.md",
                "stlsource/stlsource-chapter-5-2.md",
                "stlsource/stlsource-chapter-5-3.md",
                "stlsource/stlsource-chapter-6-1.md",
                "stlsource/stlsource-chapter-6-2.md",
                "stlsource/stlsource-chapter-7.md",
                "stlsource/stlsource-chapter-8.md"
            ]
        },
        {
            title: "Linux多线程服务端编程——使用muduo C++ 网络库 详解",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "muduo/muduo-chapter-1.md",
                "muduo/muduo-chapter-2.md",
                "muduo/muduo-chapter-3.md",
                "muduo/muduo-chapter-4.md",
                "muduo/muduo-chapter-5.md",
                "muduo/muduo-chapter-6.md",
                "muduo/muduo-chapter-7.md",
                "muduo/muduo-chapter-8.md",
                "muduo/muduo-chapter-9.md",
                "muduo/muduo-chapter-10.md",
                "muduo/muduo-chapter-11.md",
                "muduo/muduo-chapter-12.md",
                "muduo/muduo-chapter-13.md"
            ]
        }
    ];

}

// interview page
function genSidebar4interview() {
    return [
        {
            title: "八股文",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "knowledge/c11-feature.md",
                "knowledge/computer-network.md",
                "knowledge/cookie-session-token.md",
                "knowledge/cplusplus-knowledge.md",
                "knowledge/database.md",
                "knowledge/operating-system.md",
                "knowledge/programming-questions.md",
                "knowledge/STL.md"
            ]
        },
        {
            title: "数据结构",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "code/data-structure/data-structure-overview.md",
                "code/data-structure/data-structure-use.md"
            ]
        },
        {
            title: "刷题套路",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "code/question-routine/question-routine-backtrack.md",
                "code/question-routine/question-routine-bfs.md",
                "code/question-routine/question-routine-binsearch.md",
                "code/question-routine/question-routine-dfs.md",
                "code/question-routine/question-routine-dp.md",
                //"code/question-routine/question-routine-graph.md",
                "code/question-routine/question-routine-hashmap.md",
                "code/question-routine/question-routine-list.md",
                "code/question-routine/question-routine-slidingwindow.md",
                "code/question-routine/question-routine-stack.md",
                "code/question-routine/question-routine-two-pointer.md"
            ]
        }, {
            title: "题型分类",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "code/question-type/question-type-array.md",
                "code/question-type/question-type-list.md",
                "code/question-type/question-type-quest.md",
                "code/question-type/question-type-string.md",
                "code/question-type/question-type-tips.md",
                "code/question-type/question-type-tree.md"
            ]
        }
    ];

}

// article page
function genSidebar4Article() {
    return [
        {
            title: "分布式相关",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "distribute/article-distributed-cellular.md"
            ]
        }
    ];

}

// knowledge page
function genSidebar4knowledge() {
    return [
        {
            title: "专业知识",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "todo.md"
            ]
        }
    ];
}

// tech-doc page
function genSidebar4techdos() {
    return [
        {
            title: "技术文档",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "online/doc.md"
            ]
        }
    ];

}

// About page
function genSidebar4About() {
    return [
        {
            title: "关于",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "me/about-me.md",
                "me/about-blog-changelist.md",
                "me/about-content-style.md",
                "me/about-todolist.md"
            ]
        }
    ];
}





