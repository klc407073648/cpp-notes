module.exports = {
    port: "3000",
    dest: "docs",
    ga: "UA-85414008-1",
    base: "/",
    markdown: {
        lineNumbers: true,
        externalLinks: {
            target: '_blank', rel: 'noopener noreferrer'
        }
    },
    locales: {
        "/": {
            lang: "zh-CN",
            title: "Still Believe Space",
            description: "包含：C++ 基础, 算法, 数据库,MySQL, ElasticSearch, Redis, 编程四大件, 微服务 , 中间件, ZeroMQ, 部署工具, Docker, k8s, Istio, Linux, , 实践|项目,  开源项目, 个人项目, 读书笔记, 面试题, 优质文章, 博客推荐..."
        }
    },
    head: [["link", {rel: "icon", href: `/favicon.ico`}]],
    plugins: [
        ['@vuepress/back-to-top', true],
        ['@vuepress/medium-zoom', {
            selector: 'img',
            options: {
              margin: 16
            }
        }]
    ],
    themeConfig: {
        docsRepo: "stibel/tech-arch-doc",
        editLinks: true,
        sidebarDepth:0,
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
                                    {text: '函数学习', link: '/md/c++/function/c++-function-functionAndbind.md'}
                                ]
                            },
                            {
                                text: 'C++ 知识点',
                                items: [
                                    {text: '知识点', link: '/md/c++/tips/c++-tips-copy-on-write.md'}
                                ]
                            },
                            {
                                text: 'C++ IO框架',
                                items: [
                                    {text: 'IO框架 详解', link: '/md/c++/io/c++-io-reuse.md'}
                                ]
                            },
                            {
                                text: 'C++ 常用库学习',
                                items: [
                                    {text: '常用库学习 详解', link: '/md/c++/tools/c++-tools-cppcheck.md'}
                                ]
                            }
                        ]
                    },
                    {
                        text: '算法',
                        items: [
                            {text: '领域算法', link: '/md/algorithm/domain/alg-domain-bloom-filter.md'},
                            {text: '分布式算法', link: '/md/algorithm/distribute/alg-distribute-raft.md'},
                        ]
                    },
                    {
                        text: '数据库',
                        items: [
                            {
                                text: 'SQL 数据库',
                                items: [
                                    {text: 'MySQL', link: '/md/database/mysql/mysql-basic-concept.md'}
                                ]
                            },
                            {
                                text: 'NoSQL 数据库',
                                items: [
                                    {text: 'Redis', link: '/md/database/redis/redis-basic-application.md'},
                                    {text: 'ElasticSearch', link: '/md/database/es/es-install.md'}
                                ]
                            }
                        ]
                    },
                    {
                        text: '编程四大件',
                        items: [
                            {text: '数据结构与算法', link: '/md/programming/network/network-physical.md'},
                            {text: '计算机网络', link: '/md/programming/network/network-physical.md'},
                            {text: '操作系统', link: '/md/programming/network/network-physical.md'},
                            {text: '设计模式', link: '/md/programming/network/network-physical.md'}
                        ]
                    },
                    {
                        text: '开发',
                        items: [
                            {text: '开发', link: '/md/develop/todo.md'},
                        ]
                    },
                    {
                        text: '微服务',
                        items: [
                            {text: '微服务框架', link: '/md/micro-services/frame/frame-architecture.md'}
                        ]
                    },
                    {
                        text: '架构|中间件',
                        items: [
                            {text: 'ZeroMQ', link: '/md/middleware/zeromq/zeromq-demo.md'}
                        ]
                    },
                    {
                        text: '工具|部署',
                        items: [
                            {
                                text: '工具',
                                items: [
                                    {text: 'Linux', link: '/md/devops/linux/linux-cmd-tips.md'},
                                    {text: 'Nginx', link: '/md/devops/nginx/nginx-study-note.md'},
                                ]
                            },
                            {
                                text: '部署',
                                items: [
                                    {text: 'Docker', link: '/md/devops/docker/docker.md'},
                                    {text: 'Kubernetes', link: '/md/devops/k8s/k8s.md'},
                                    {text: 'Service Mesh Istio', link: '/md/devops/istio/istio-basic.md'},
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
                                    {text: 'Docker-MySQL', link: '/md/project/practice/Docker-MySQL.md'}
                                ]
                            },
                            {
                                text: '开源项目学习',
                                items: [
                                    {text: '开源协程库 libco', link: '/md/project/opensource/libco/libco.md'},
                                    {text: 'buttonrpc', link: '/md/project/opensource/buttonrpc/buttonrpc-basic.md'},
                                    {text: 'Tars', link: '/md/project/opensource/tars/tars-brief.md'}
                                ]
                            },
                            {
                                text: '个人github项目总结',
                                items: [
                                    {text: 'build_lib', link: '/md/project/person/build_lib/build_lib.md'}
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
                                    {text: '深入理解计算机系统 详解', link: '/md/book-note/computersystem/computersystem-chapter-1.md'}
                                ]
                            },
                            {
                                text: '重构改善既有代码的设计',
                                items: [
                                    {text: '重构改善既有代码的设计 详解', link: '/md/book-note/refactor/refactor-chapter-1.md'}
                                ]
                            }
                        ]
                    },
                    {
                        text: '面试',
                        items: [
                            {text: '面试题', link: '/md/interview/cplusplus-knowledge.md'}
                        ]
                    },
                    {
                        text: '优质文章|博客推荐',
                        items: [
                            {text: '分布式相关', link: '/md/article/distribute/article-distributed-cellular.md'}
                        ]
                    },
                    {
                        text: '其他(待整理)', 
                        items: [
                            {text: '其他', link: '/md/other/todo.md'}
                        ]
                    },
                    {
                        text: '专业知识',
                        items: [
                            {text: '专业知识', link: '/md/knowledge/todo.md'}
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
                    "/md/middleware/": genSidebar4middleware(),
                    "/md/devops/": genSidebar4Devops(),
                    "/md/project/": genSidebar4project(),
                    "/md/book-note/": genSidebar4booknote(),
                    "/md/interview/": genSidebar4interview(),
                    "/md/article/": genSidebar4Article(),
                    "/md/other/": genSidebar4other(),
                    "/md/knowledge/": genSidebar4knowledge(),
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
                "function/c++-function-functionAndbind.md", 
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
function genSidebar4Database(){
    return [
        {
            title: "SQL - MySQL",
            collapsable: false,
            sidebarDepth: 0, 
            children: [
                "mysql/mysql-basic-concept.md",
                "mysql/mysql-basic-use.md",
                "mysql/mysql-index-design.md"
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
function genSidebar4Alg(){
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
function genSidebar4Program(){
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
        }
    ];
     
}

//develop page
function genSidebar4develop(){
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
function genSidebar4microServices(){
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

// middleware page
function genSidebar4middleware(){
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

// Devops page
function genSidebar4Devops(){
    return [
        {
            title: "Linux",
            collapsable: false,
            sidebarDepth: 0, 
            children: [
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
                "docker/docker-use.md"
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
function genSidebar4project(){
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
            title: "个人github项目 - build_lib",
            collapsable: false,
            sidebarDepth: 0, 
            children: [
                "person/build_lib/build_lib.md"
            ]
        }
    ];  
}

// book-note page
function genSidebar4booknote(){
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
        }
    ];
     
}

// interview page
function genSidebar4interview(){
    return [
        {
            title: "面试题",
            collapsable: false,
            sidebarDepth: 0, 
            children: [
                "c11-feature.md",
                "computer-network.md",
                "cookie-session-token.md",
                "cplusplus-knowledge.md",
                "database.md",
                "operating-system.md",         
                "programming-questions.md",
                "STL.md"
            ]
        }
    ];
     
}

// article page
function genSidebar4Article(){
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

// About page
function genSidebar4other(){
    return [
        {
            title: "其他",
            collapsable: false,
            sidebarDepth: 0, 
            children: [
                "todo.md"
            ]
        }
    ];
}

// About page
function genSidebar4knowledge(){
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
// About page
function genSidebar4About(){
    return [
        {
            title: "关于",
            collapsable: false,
            sidebarDepth: 0, 
            children: [
                "me/about-me.md"
            ]
        }
    ];
}





