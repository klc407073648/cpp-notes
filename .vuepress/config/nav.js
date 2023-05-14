module.exports = 
[
    {
        text: '✿导航', link: '/md/guide/guide-overview.md' ,
    },
    {
        text: '♥面试', link: '/md/interview/knowledge/cplusplus-knowledge.md',
    },
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
                    { text: '新版本特性', link: '/md/c++/features/c11/c++-features-c11.md' }
                ]
            },
            {
                text: 'C++ IO框架',
                items: [
                    { text: 'IO框架', link: '/md/c++/io/c++-io-reuse.md' }
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
                text: '数据库基础和原理',
                items: [
                    { text: '数据库原理', link: '/md/database/base/base-db-work-theory.md' },
                    { text: 'SQL语言', link: '/md/database/sql/sql-overview.md' }
                ]
            },
            {
                text: 'SQL 数据库',
                items: [
                    { text: 'MySQL', link: '/md/database/mysql/mysql-overview.md' }
                ]
            },
            {
                text: 'NoSQL 数据库',
                items: [
                    { text: 'Redis', link: '/md/database/redis/basic/redis-basic-concept.md' },
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
            { text: '操作系统', link: '/md/programming/system/system-overview.md' },
            { text: '设计模式', link: '/md/programming/designpattern/designpattern-overview' }
        ]
    },
    {
        text: '开发',
        items: [
            { text: '开发 - 常用库', link: '/md/develop/library/library-overview.md' },
        ]
    },
    {
        text: '架构|微服务|中间件',
        items: [
            {
                text: '架构',
                items: [
                    { text: '架构基础', link: '/md/micro-services/arch/frame/arch-frame-evolution.md' },
                ]
            },
            {
                text: '微服务框架',
                items: [
                    { text: '理论基础', link: '/md/micro-services/frame/frame-architecture.md' }
                ]
            },
            {
                text: '中间件',
                items: [
                    { text: 'ZeroMQ', link: '/md/micro-services/middleware/zeromq/zeromq-demo.md' },
                    { text: 'Dubbo', link: '/md/micro-services/middleware/dubbo/dubbo.md' },
                    { text: 'Consul', link: '/md/micro-services/middleware/consul/consul-basic.md' },
                    { text: 'Apollo', link: '/md/micro-services/middleware/apollo/apollo-basic.md' },
                    { text: 'Cat', link: '/md/micro-services/middleware/cat/cat-basic.md' },
                    { text: 'Logstash', link: '/md/micro-services/middleware/logstash/logstash-basic.md' },
                    { text: 'Kong', link: '/md/micro-services/middleware/kong/kong-basic.md' }
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
                    { text: '技术概念', link: '/md/method/concept/concept-basic.md' },
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
                text: '协议',
                items: [
                    { text: 'Http协议', link: '/md/method/protocol/protocol-http.md' },
                    { text: 'SNMP协议', link: '/md/method/protocol/protocol-snmp.md' },
                    { text: 'NETCONF协议', link: '/md/method/protocol/protocol-netconf.md' },
                    { text: 'TLS协议', link: '/md/method/protocol/protocol-ssl-tls.md' }
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
                    { text: 'Shortcut', link: '/md/devops/shortcut/shortcut-linux.md' }
                ]
            },
            {
                text: '部署',
                items: [
                    { text: 'Docker', link: '/md/devops/docker/docker-evolution.md' },
                    { text: 'Kubernetes', link: '/md/devops/k8s/k8s-concept.md' },
                    { text: 'Service Mesh Istio', link: '/md/devops/istio/istio-basic.md' },
                ]
            }
        ]
    },
    {
        text: '项目',
        items: [
            { text: '开源项目', link: '/md/project/opensource/libco/libco-learn.md' },
            { text: '学习项目', link: '/md/project/study/ssm/spring/spring-basic.md' },
            { text: '个人github项目', link: '/md/project/person/build_lib/build_lib.md' },
            { text: '项目开发', link: '/md/project/develop/develop-process.md' },
            { text: '项目Idea', link: '/md/project/idea/idea-basic.md' }
        ]
    },
    {
        text: '读书笔记',
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
                    { text: '深入理解计算机系统', link: '/md/book-note/computersystem/computersystem-chapter-1.md' },
                    { text: '重构改善既有代码的设计', link: '/md/book-note/refactor/refactor-chapter-1.md' },
                    { text: 'Effective C++:改善程序与设计的55个具体做法', link: '/md/book-note/effectivecpp/effectivecpp-chapter-2-1.md' },
                    { text: 'STL源码剖析', link: '/md/book-note/stlsource/stlsource-chapter-1.md' },
                    { text: 'Linux多线程服务端编程——使用muduo C++ 网络库', link: '/md/book-note/muduo/muduo-chapter-1.md' },
                    { text: '大型网站技术架构——核心原理与案例分析', link: '/md/book-note/websiteTechArch/websiteTechArch-chapter-1-1.md' },
                    { text: '代码大全2', link: '/md/book-note/codeComplete/codeComplete-chapter-1.md' },
                    { text: '数据密集型应用系统设计', link: '/md/book-note/dataIntensiveApp/dataIntensiveApp-chapter-1.md' },
                    { text: '从零开始学架构', link: '/md/book-note/learnArchFromZero/learnArchFromZero-chapter-1.md' },
                    { text: '程序员的自我修养————链接、装载与库', link: '/md/book-note/linkersAndLoaders/linkersAndLoaders-chapter-1.md' }
                ]
            }
        ]
    },
    {
        text: '文章',
        items: [
            { text: '并发', link: '/md/article/concurrent/article-concurrent-lock.md' },
            { text: '部署', link: '/md/article/deploy/article-deploy-blue-green.md' },
            { text: '分布式', link: '/md/article/distribute/article-distributed-cellular.md' },
            { text: '成长', link: '/md/article/grow/article-grow-Stay_hungry_Stay_foolish.md' },
            { text: '知识', link: '/md/article/knowledge/article-knowledge-service-mesh.md' },
            { text: '问题', link: '/md/article/problem/article-problem-top.md' }
        ]
    },
    {
        text: '成长',
        items: [
            { text: '个人', link: '/md/grow/person/person-better-than-others.md' },
            { text: '产品', link: '/md/grow/product/product-requirement-instantiation.md' },
            { text: '团队', link: '/md/grow/team/team-system-arch.md' },
        ]
    },
    {
        text: '前端',
        items: [
            {
                text: 'Vue2学习',
                items: [
                    { text: 'Vue 基础', link: '/md/vue/vue2/basic/basic-concept.md' },
					{ text: 'Vue 组件', link: '/md/vue/vue2/component/component-basic.md' },
					{ text: 'Vue 脚手架', link: '/md/vue/vue2/CLI/cli-init.md' },
					{ text: 'Vue中的Ajax', link: '/md/vue/vue2/ajax/ajax-basic.md' },
					{ text: 'Vuex', link: '/md/vue/vue2/vuex/vuex-basic.md' },
					{ text: 'Vue Router', link: '/md/vue/vue2/vue_router/vue-router-basic.md' },
                ]
            },
            {
                text: 'Vue3学习',
                items: [
                    { text: 'Vue3 - 学习', link: '/md/vue/vue3/vue3-use.md' }
                ]
            }
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