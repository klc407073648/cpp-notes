module.exports = 
[
    {
        text: 'C++',
        items: [
            {
                text: 'C++ 基础',
                items: [
                    { text: '基础', link: '/md/c++/basic/c++-basic-use.md' }
                ]
            },
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
            { text: '数据结构与算法', link: '/md/programming/data-structure/data-structure-overview.md' },
            { text: '计算机网络', link: '/md/programming/network/network-physical.md' },
            { text: '操作系统', link: '/md/programming/system/doc.md' },
            { text: '设计模式', link: '/md/programming/designpattern/designpattern-overview' }
        ]
    },
    {
        text: '开发',
        items: [
            { text: '开发 - 常用库', link: '/md/develop/library/library-cppcheck.md' },
        ]
    },
    {
        text: '架构',
        items: [
            { text: '架构基础', link: '/md/arch/frame/arch-frame-evolution.md' }
        ]
    },
    {
        text: '微服务|中间件',
        items: [
            {
                text: '微服务框架',
                items: [
                    { text: '理论基础', link: '/md/micro-services/frame/frame-architecture.md' }
                ]
            },
            {
                text: '中间件',
                items: [
                    { text: 'ZeroMQ', link: '/md/micro-services/middleware/zeromq/zeromq-demo.md' }
                ]
            },
        ]
    },
    {
        text: '方法论',
        items: [
            {
                text: '概念',
                items: [
                    { text: '正向代理和反向代理的区别', link: '/md/method/concept/concept-agent.md' },
                    { text: '计算机专有名词', link: '/md/method/concept/concept-communication.md' }
                ]
            },
            {
                text: '理论',
                items: [
                    { text: '事务理论 - ACID', link: '/md/method/theory/theory-acid.md' },
                    { text: '分布式理论 - CAP', link: '/md/method/theory/theory-cap.md' },
                    { text: '分布式理论 - BASE', link: '/md/method/theory/theory-base.md' },
                ]
            },
            {
                text: '架构设计原则',
                items: [
                    { text: '合适、简单、演化原则', link: '/md/method/arch-principle/arch-principle-design.md' },
                    { text: '正交四原则', link: '/md/method/arch-principle/arch-principle-four.md' },
                    { text: 'SOLID 原则', link: '/md/method/arch-principle/arch-principle-solid-detail.md' },
                    { text: 'DDD领域驱动设计', link: '/md/method/arch-principle/arch-principle-ddd.md' }
                ]
            },
            {
                text: '技术选型',
                items: [
                    { text: '常用的技术框架', link: '/md/method/tech/tech-select.md' },
                    { text: '如何写一个自己的项目', link: '/md/method/tech/tech-per-prj.md' }
                ]
            },
            {
                text: '代码规范',
                items: [
                    { text: 'Google C++ 编码规范', link: '/md/method/code-style/code-style-google-c++.md' }
                ]
            }
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
                    { text: 'Shortcut', link: '/md/devops/shortcut/linux.md' }
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
                    { text: '实践 - Docker', link: '/md/project/practice/docker/jenkins/practice-docker-jenkins.md' },
                    { text: '实践 - 工具类', link: '/md/project/practice/tools/practice-tools-git-config-key.md' },
                    { text: '实践 - 实用型', link: '/md/project/practice/ngx-admin-install.md' }
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
        text: '读书与笔记',
        items: [
            {
                text: '书籍推荐',
                items: [
                    { text: '推荐书籍目录', link: '/md/book-note/book-note-index.md' },
                ]
            },
            {
                text: '读书笔记',
                items: [
                    { text: '深入理解计算机系统 详解', link: '/md/book-note/computersystem/computersystem-chapter-1.md' },
                    { text: '重构改善既有代码的设计 详解', link: '/md/book-note/refactor/refactor-chapter-1.md' },
                    { text: 'Effective C++:改善程序与设计的55个具体做法 详解', link: '/md/book-note/effectivecpp/effectivecpp-chapter-2-1.md' },
                    { text: 'STL源码剖析 详解', link: '/md/book-note/stlsource/stlsource-chapter-1.md' },
                    { text: 'Linux多线程服务端编程——使用muduo C++ 网络库 详解', link: '/md/book-note/muduo/muduo-chapter-1.md' },
                    { text: '大型网站技术架构——核心原理与案例分析 详解', link: '/md/book-note/websiteTechArch/websiteTechArch-index.md' }
                ]
            }
        ]
    },
    {
        text: '优质文章|博客推荐',
        items: [
            { text: '并发', link: '/md/article/concurrent/article-concurrent-lock.md' },
            { text: '部署', link: '/md/article/deploy/article-deploy-blue-green.md' },
            { text: '分布式', link: '/md/article/distribute/article-distributed-cellular.md' },
            { text: '成长', link: '/md/article/grow/article-grow-Stay_hungry_Stay_foolish.md' },
            { text: '问题解决', link: '/md/article/problem/article-problem-top.md' }
        ]
    },
    {
        text: '日常使用',
        items: [
            { text: '技术文档', link: '/md/daily-use/doc/daily-use-doc-overview.md' },
            { text: '前沿资讯', link: '/md/daily-use/info/daily-use-info-overview.md' },
            { text: '常用软件', link: '/md/daily-use/software/daily-use-software-overview.md' },
            { text: '在线工具', link: '/md/daily-use/tools/daily-use-tools-overview.md' }
        ]
    },
    {
        text: '关于', link: '/md/about/me/about-me.md'
    }
]