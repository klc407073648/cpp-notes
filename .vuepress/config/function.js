
// guide page
// 不需要
function genSidebar4Guide() {
    return [
        {
            title: "导航地图",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "guide-overview.md",
                "c++-overview.md",
                "algorithm-overview.md",
                "database-overview.md",
                "programming-overview.md",
                "develop-overview.md",
                "micro-services-overview.md",
                "method-overview.md",
                "devops-overview.md",
                "project-overview.md",
                "book-note-overview.md",
                "article-overview.md",
                "grow-overview.md",
                "vue-overview.md",
                "daily-use-overview.md",
                "person-github-overview.md",
            ]
        }
    ];
}

// C++ page
function genSidebar4Cplusplus() {
    return [
        {
            title: "C++ 基础",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "basic/c++-basic-use.md",
                "basic/c++-basic-oop.md",
                "basic/c++-basic-macro-definition.md"
            ]
        },
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
                "function/c++-function-va_listFun.md",
                "function/c++-function-ptr.md"
            ]
        },
        {
            title: "C++ 知识点",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "tips/c++-tips-copy-on-write.md",
                "tips/c++-tips-forward-declaration.md",
                "tips/c++-tips-search-head-lib.md",
                "tips/c++-tips-spec-template.md",
                "tips/c++-tips-override.md",
                "tips/c++-tips-return-temp-var.md",
                "tips/c++-tips-multi-define.md"
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
        }
    ]
}

// Database page
function genSidebar4Database() {
    return [
        {
            title: "数据库原理",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "base/base-db-work-theory.md",
                "base/base-db-mysql.md",
            ]
        },
        {
            title: "SQL语言",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "sql/sql-overview.md",
                "sql/sql-base.md",
                "sql/sql-function.md",
                "sql/sql-constraint.md",
                "sql/sql-con-query.md",
                "sql/sql-sub-query.md",
                "sql/sql-multi-query.md",
                "sql/sql-tips",
            ]
        },
        {
            title: "SQL - MySQL",
            collapsable: true,
            sidebarDepth: 0,
            children: [
                "mysql/mysql-overview.md",
                "mysql/basic/mysql-basic-concept.md",
                "mysql/basic/mysql-basic-3nf.md",
                "mysql/basic/mysql-basic-datatype.md",
                "mysql/basic/mysql-basic-view.md",
                "mysql/basic/mysql-basic-procedure.md",
                "mysql/advance/mysql-advance-store-engine.md",
                "mysql/advance/mysql-advance-innodb.md",
                "mysql/advance/mysql-advance-index-basic.md",
                "mysql/advance/mysql-advance-index-content.md",
                "mysql/advance/mysql-advance-index-use.md",
                "mysql/advance/mysql-advance-performance-analyze.md",
                "mysql/advance/mysql-advance-performance-opt.md",
                "mysql/advance/mysql-advance-lock.md",
                "mysql/advance/mysql-advance-trigger.md",
                "mysql/advance/mysql-advance-transaction.md",
                "mysql/advance/mysql-advance-manage.md",
                "mysql/operation/mysql-operation-log.md",
                "mysql/operation/mysql-operation-master-slave.md",
                "mysql/operation/mysql-operation-db-devide.md",
                "mysql/operation/mysql-operation-rw-separate.md",
                "mysql/practice/mysql-practice-sql-execute.md",
                "mysql/practice/mysql-practice-sql-parse.md",
                "mysql/practice/mysql-practice-mycat.md",
            ]
        },
        {
            title: "NoSQL - Redis",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "redis/basic/redis-basic-concept.md",
                "redis/basic/redis-basic-command.md",
                "redis/advance/redis-advance-persistence.md",
                "redis/advance/redis-advance-transaction-operation.md",
                "redis/advance/redis-advance-delete-policy.md",
                "redis/advance/redis-advance-master-slave-replication.md",
                "redis/advance/redis-advance-sentinel-mode.md",
                "redis/application/redis-application-cluster.md",
                "redis/application/redis-application-enterprise-solution.md"
            ]
        },
        {
            title: "NoSQL - ElasticSearch",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "es/es-cluster.md",
                "es/es-install.md",
                "es/es-cluster-deployment.md",
                "es/es-data-analysis-process.md",
                "es/es-data-search.md",
                "es/es-data-store.md",
                "es/es-db-syn.md",
                "es/es-use.md"
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
            title: "数据结构基础",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "data-structure/data-structure-overview.md",
                "data-structure/data-structure-array-vector.md",
                "data-structure/data-structure-list.md",
                "data-structure/data-structure-hashtable.md",
                "data-structure/data-structure-stack.md",
                "data-structure/data-structure-queue.md",
                "data-structure/data-structure-tree-overview.md",
                "data-structure/data-structure-tree-search.md",
                "data-structure/data-structure-tree-balance.md",
                "data-structure/data-structure-tree-redblack.md",
                "data-structure/data-structure-tree-trie.md",
                "data-structure/data-structure-graph-overview.md",
                "data-structure/data-structure-graph-bfs-dfs.md",
                "data-structure/data-structure-use.md",
            ]
        },
        {
            title: "算法思想",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "algorithm/core/algorithm-core-overview.md",
                "algorithm/core/algorithm-core-complexity.md"
            ]
        },
        {
            title: "常见排序算法",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "algorithm/sort/algorithm-sort-bubble.md",
                "algorithm/sort/algorithm-sort-select.md",
                "algorithm/sort/algorithm-sort-insert.md",
                "algorithm/sort/algorithm-sort-shell.md",
                "algorithm/sort/algorithm-sort-merge.md",
                "algorithm/sort/algorithm-sort-quick.md",
                "algorithm/sort/algorithm-sort-heap.md",
                "algorithm/sort/algorithm-sort-counting.md",
                "algorithm/sort/algorithm-sort-bucket.md",
                "algorithm/sort/algorithm-sort-radix.md"
            ]
        },
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
            title: "操作系统",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "system/system-overview.md",
                "system/system-thread-process.md",
                "system/system-sync-mode.md",
                "system/system-deadlock.md"
            ]
        },
        {
            title: "设计模式",
            collapsable: true,
            sidebarDepth: 0,
            children: [
                "designpattern/designpattern-overview",
                "designpattern/designpattern-create-singleton.md",
                "designpattern/designpattern-create-factory.md",
                "designpattern/designpattern-create-abstract-factory.md",
                "designpattern/designpattern-create-builder.md",
                "designpattern/designpattern-create-prototype.md",
                "designpattern/designpattern-structure-facade.md",
                "designpattern/designpattern-structure-adapter.md",
                "designpattern/designpattern-structure-bridge.md",
                "designpattern/designpattern-structure-composite.md",
                "designpattern/designpattern-structure-decorator.md",
                "designpattern/designpattern-structure-flyweight.md",
                "designpattern/designpattern-structure-proxy.md",
                "designpattern/designpattern-behave-chain-of-responsibility.md",
                "designpattern/designpattern-behave-strategy.md",
                "designpattern/designpattern-behave-template.md",
                "designpattern/designpattern-behave-command.md",
                "designpattern/designpattern-behave-observer.md",
                "designpattern/designpattern-behave-visitor.md",
                "designpattern/designpattern-behave-state.md",
                "designpattern/designpattern-behave-interpreter.md",
                "designpattern/designpattern-behave-iterator.md",
                "designpattern/designpattern-behave-mediator.md",
                "designpattern/designpattern-behave-memento.md"
            ]
        }
    ];

}

// develop page
function genSidebar4develop() {
    return [
        {
            title: "常用开发库",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "library/library-overview.md",
                "library/library-cppcheck.md",
                "library/library-cppunit.md",
                "library/library-drogon.md",
                "library/library-fastcgi.md",
                "library/library-googletest.md",
                "library/library-hiredis.md",
                "library/library-jsoncpp.md",
                "library/library-log4cpp.md",
                "library/library-poco.md",
                "library/library-protobuf.md",
                "library/library-tinyxml.md",
                "library/library-yamlcpp.md",
                "library/library-zeromq.md",
            ]
        }
    ];
}

// micro-services page
function genSidebar4microServices() {
    return [
        {
            title: "架构",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "arch/frame/arch-frame-evolution.md",
                "arch/frame/arch-frame-service.md",
                "arch/frame/arch-frame-orm.md",
                "arch/frame/arch-frame-rpc.md"
            ]
        },
        {
            title: "微服务",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "frame/frame-architecture.md",
                "frame/frame-study-route.md",
                "frame/frame-gateway.md",
                "frame/frame-registration-discovery.md",
                "frame/frame-message-queue.md",
                "frame/frame-protection.md",
                "frame/frame-distributed-search.md",
                "frame/frame-distributed-transaction.md",
                "frame/frame-multi-level-cache.md",
                "frame/frame-idempotent-design.md"
            ]
        },
        {
            title: "中间件 - ZeroMQ - 消息队列",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "middleware/zeromq/zeromq-demo.md",
                "middleware/zeromq/zeromq-part1.md",
                "middleware/zeromq/zeromq-part2.md",
                "middleware/zeromq/zeromq-part3.md"
            ]
        },
        {
            title: "中间件 - Dubbo - RPC调用",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "middleware/dubbo/dubbo.md",
            ]
        },
        {
            title: "中间件 - Consul - 配置中心",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "middleware/consul/consul-basic.md",
                "middleware/consul/consul-content.md",
                "middleware/consul/consul-install-use.md",
                "middleware/consul/consul-health.md",
                "middleware/consul/consul-http-api.md",
                "middleware/consul/consul-kv-store.md",
            ]
        },
        {
            title: "中间件 - Apollo - 配置中心",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "middleware/apollo/apollo-basic.md",
                "middleware/apollo/apollo-design.md",
                "middleware/apollo/apollo-docker.md",
                "middleware/apollo/apollo-use.md",
            ]
        },
        {
            title: "中间件 - Cat - 监控平台",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "middleware/cat/cat-basic.md",
                "middleware/cat/cat-docker-deploy.md",
                "middleware/cat/cat-c++-client.md",
            ]
        },
        {
            title: "中间件 - Logstash - 数据处理管道",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "middleware/logstash/logstash-basic.md",
                "middleware/logstash/logstash-work.md",
                "middleware/logstash/logstash-docker-deploy.md",
                "middleware/logstash/logstash-use.md",
            ]
        },
        {
            title: "中间件 - Kong - 服务网关",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "middleware/kong/kong-basic.md",
                "middleware/kong/kong-plugin.md",
                "middleware/kong/kong-install-use.md",
            ]
        }
    ];

}

// arch page 并入微服务
function genSidebar4arch() {
    return [
        {
            title: "理论基础",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "frame/arch-frame-evolution.md",
                "frame/arch-frame-service.md"
            ]
        },
        {
            title: "ORM架构",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "frame/arch-frame-orm.md"
            ]
        },
        {
            title: "RPC框架",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "frame/arch-frame-rpc.md"
            ]
        }
    ];
}

// method page
function genSidebar4method() {
    return [
        {
            title: "概念",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "concept/concept-basic.md",
                "concept/concept-communication.md",
                "concept/concept-agent.md",
                "concept/concept-cloud-network.md",
                "concept/concept-rest-api.md",
                "concept/concept-split-brain.md"
            ]
        },
        {
            title: "理论",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "theory/theory-acid.md",
                "theory/theory-cap.md",
                "theory/theory-base.md",
            ]
        },
        {
            title: "架构设计原则",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "arch-principle/arch-principle-design.md",
                "arch-principle/arch-principle-high-cohesion.md",
                "arch-principle/arch-principle-four.md",
                "arch-principle/arch-principle-solid-detail.md",
                "arch-principle/arch-principle-mvc.md",
                "arch-principle/arch-principle-clean-arch.md",
                "arch-principle/arch-principle-anemia-model.md",
                "arch-principle/arch-principle-ddd.md",
                "arch-principle/arch-principle-arch-develop.md",
            ]
        },
        {
            title: "协议",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "protocol/protocol-http",
                "protocol/protocol-snmp.md",
                "protocol/protocol-netconf.md",
                "protocol/protocol-ssl-tls.md",
                "protocol/protocol-http-wiki.md",
                "protocol/protocol-tcp-ip.md",
            ]
        },
        {
            title: "技术选型",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "tech/tech-select.md",
                "tech/tech-per-prj.md"
            ]
        },
        {
            title: "编码规范",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "code-style/code-style-google-c++.md",
                "code-style/code-style-code-style.md",
                "code-style/code-style-head-file.md",
                "code-style/code-style-naming-rule.md",
                "code-style/code-style-naming-specification.md"
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
                "linux/linux-output-with-color.md",
                "linux/linux-authority.md"
            ]
        },
        {
            title: "Nginx",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "nginx/nginx-study-note.md",
                "nginx/nginx-staic-web.md",
                "nginx/nginx-reverse-proxy-server.md",
                "nginx/nginx-error-log.md",
                "nginx/nginx-image-server-cfg.md"
            ]
        },
        {
            title: "实践",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "practice/docker/jenkins/practice-docker-jenkins.md",
                "practice/docker/mysql/practice-docker-mysql.md",
                "practice/docker/redis/practice-docker-redis.md",
                "practice/tools/practice-tools-git.md",
                "practice/tools/practice-tools-gitbook.md",
                "practice/practice-ngx-admin-install",
                "practice/practice-Robot-Framework-install.md"
            ]
        },
        {
            title: "常用快捷键",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "shortcut/shortcut-linux.md",
                "shortcut/shortcut-vim.md",
                "shortcut/shortcut-vscode.md",
                "shortcut/shortcut-idea.md"
            ]
        },
        {
            title: "容器化 - Docker",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "docker/docker-evolution.md",
                "docker/docker-dockerfile.md",
                "docker/docker-cmd.md"
            ]
        },
        {
            title: "容器编排 - Kubernetes",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "k8s/k8s-concept.md",
                "k8s/k8s-base-use.md",
                "k8s/k8s-cmd.md",
                "k8s/k8s-probe.md"
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
            title: "开源项目 - libco",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "opensource/libco/libco-learn.md"
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
            title: "学习项目 - hmdp",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "opensource/hmdp/hmdp-overview.md",
                "opensource/hmdp/hmdp-msglogin.md",
                "opensource/hmdp/hmdp-shop-query-cache.md",
                "opensource/hmdp/hmdp-seckill-opt.md",
                "opensource/hmdp/hmdp-distribute-lock.md",
                "opensource/hmdp/hmdp-redission.md",
                "opensource/hmdp/hmdp-msg-queue.md",
                "opensource/hmdp/hmdp-voucher-seckill.md",
                "opensource/hmdp/hmdp-nearby-shop.md",
                "opensource/hmdp/hmdp-uv-statisic.md",
                "opensource/hmdp/hmdp-user-sign.md",
                "opensource/hmdp/hmdp-friend-follow.md",
                "opensource/hmdp/hmdp-talent-shop.md",
            ]
        },
        {
            title: "学习项目 - SSM框架",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "study/ssm/spring/spring-basic.md",
                "study/ssm/spring/spring-concept.md",
                "study/ssm/spring/spring-integrate.md",
                "study/ssm/spring/spring-aop.md",
                "study/ssm/springmvc/springmvc-basic.md",
                "study/ssm/springmvc/springmvc-application.md",
                "study/ssm/maven/maven.md",
                "study/ssm/springboot/springboot.md",
                "study/ssm/mybatisplus/mybatisplus.md",
            ]
        },
        {
            title: "个人项目 - github",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "person/person-overview.md"
            ]
        },
        {
            title: "项目开发",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "develop/develop-cpp-recommend.md",
                "develop/develop-process.md",
                "develop/develop-opt.md",
                "develop/develop-notice.md",
                "develop/uml/develop-uml.md",
            ]
        },
        {
            title: "Idea",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "idea/idea-basic.md",
                "idea/idea-tech-use.md",
                "idea/idea-tips.md",
                "idea/idea-doublewrite-buffer",
                "idea/idea-collect-tips"
            ]
        }
    ];
}

// book-note page
function genSidebar4booknote() {
    return [
        {
            title: "书籍推荐",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "book-note-index.md"
            ]
        },
        {
            title: "深入理解计算机系统",
            collapsable: true,
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
            title: "重构改善既有代码的设计",
            collapsable: true,
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
            title: "Effective C++:改善程序与设计的55个具体做法",
            collapsable: true,
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
            title: "STL源码剖析",
            collapsable: true,
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
            title: "Linux多线程服务端编程——使用muduo C++ 网络库",
            collapsable: true,
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
        },
        {
            title: "大型网站技术架构——核心原理与案例分析",
            collapsable: true,
            sidebarDepth: 0,
            children: [
                "websiteTechArch/websiteTechArch-chapter-1-1.md",
                "websiteTechArch/websiteTechArch-chapter-1-2.md",
                "websiteTechArch/websiteTechArch-chapter-1-3.md",
                "websiteTechArch/websiteTechArch-chapter-2-1.md",
                "websiteTechArch/websiteTechArch-chapter-2-2.md",
                "websiteTechArch/websiteTechArch-chapter-2-3.md",
                "websiteTechArch/websiteTechArch-chapter-2-4.md",
                "websiteTechArch/websiteTechArch-chapter-2-5.md"
            ]
        },
        {
            title: "代码大全2",
            collapsable: true,
            sidebarDepth: 0,
            children: [
                "codeComplete/codeComplete-chapter-1.md",
                "codeComplete/codeComplete-chapter-2.md",
                "codeComplete/codeComplete-chapter-3.md",
                "codeComplete/codeComplete-chapter-4.md",
                "codeComplete/codeComplete-chapter-5.md",
            ]
        },
        {
            title: "数据密集型应用系统设计",
            collapsable: true,
            sidebarDepth: 0,
            children: [
                "dataIntensiveApp/dataIntensiveApp-chapter-1.md",
                "dataIntensiveApp/dataIntensiveApp-chapter-2.md",
                "dataIntensiveApp/dataIntensiveApp-chapter-3.md",
                "dataIntensiveApp/dataIntensiveApp-chapter-4.md",
                "dataIntensiveApp/dataIntensiveApp-chapter-5.md",
                "dataIntensiveApp/dataIntensiveApp-chapter-6.md",
                "dataIntensiveApp/dataIntensiveApp-chapter-7.md",
            ]
        },
        {
            title: "从零开始学架构",
            collapsable: true,
            sidebarDepth: 0,
            children: [
                "learnArchFromZero/learnArchFromZero-chapter-1.md",
                "learnArchFromZero/learnArchFromZero-chapter-2.md",
                "learnArchFromZero/learnArchFromZero-chapter-3.md",
                "learnArchFromZero/learnArchFromZero-chapter-4.md",
            ]
        },
        {
            title: "程序员的自我修养————链接、装载与库",
            collapsable: true,
            sidebarDepth: 0,
            children: [
                "linkersAndLoaders/linkersAndLoaders-chapter-1.md",
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
                "knowledge/computer-network.md",
                "knowledge/cookie-session-token.md",
                "knowledge/cplusplus-knowledge.md",
                "knowledge/database.md",
                "knowledge/operating-system.md",
                "knowledge/programming-questions.md",
                "knowledge/network-ip-address.md"
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
            title: "并发",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "article-overview.md",
                "concurrent/article-concurrent-lock.md"
            ]
        },
        {
            title: "部署",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "deploy/article-deploy-blue-green.md"
            ]
        },
        {
            title: "分布式",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "distribute/article-distributed-cellular.md",
                "distribute/article-distributed-lock.md"
            ]
        },
        {
            title: "知识",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "knowledge/article-knowledge-service-mesh.md",
                "knowledge/article-knowledge-share-bike.md",
                "knowledge/article-knowledge-software-architecture.md",
                "knowledge/article-knowledge-cors-sop.md",
                "knowledge/article-knowledge-feeddog-watchdog.md",
                "knowledge/article-knowledge-return-temp-var.md",
                "knowledge/article-knowledge-time.md",
                "knowledge/article-knowledge-vm-bm.md",
                "knowledge/article-knowledge-loadbalance.md",
            ]
        },
        {
            title: "问题",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "problem/article-problem-top.md",
                "problem/article-problem-pstack.md",
                "problem/article-problem-cache-update.md",
                "problem/article-problem-three-high.md"
            ]
        }
    ];

}

// daily-use page
function genSidebar4dailyUse() {
    return [
        {
            title: "技术文档",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "doc/daily-use-doc-overview.md",
                "doc/daily-use-doc-c++.md"
            ]
        },
        {
            title: "前沿资讯",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "info/daily-use-info-overview.md"
            ]
        },
        {
            title: "常用软件",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "software/daily-use-software-overview.md"
            ]
        },
        {
            title: "在线工具",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "tools/daily-use-tools-overview.md",
                "tools/daily-use-tools.md"
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
            ]
        },
        {
            title: "电影",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "movie/about-movie-like.md",
            ]
        },
        {
            title: "音乐",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "music/about-music-like.md",
            ]
        },
        {
            title: "阅读",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "read/about-read-list.md",
                "read/about-read-thinking.md",
                "read/about-read-the-courage-to-be-hate.md",
            ]
        },
        {
            title: "风景",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "scenery/about-scenery-record.md",
            ]
        }
    ];
}

// Grow page
function genSidebar4Grow() {
    return [
        {
            title: "个人",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "person/person-better-than-others.md",
                "person/person-tech-grow.md",
                "person/person-grow-Stay_hungry_Stay_young.md",
                "person/person-grow-Stay_hungry_Stay_foolish.md",
                "person/person-learn-new-things.md",
            ]
        },
        {
            title: "产品",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "product/product-requirement-instantiation.md",
                "product/product-compatibility-principle.md",
                "product/product-version.md",
            ]
        },{
            title: "团队",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "team/team-cross-life-valley.md",
                "team/team-system-arch.md",
                "team/team-tech-share.md",
                "team/team-member-define.md",
            ]
        }
    ];
}

// Grow page
function genSidebar4Vue() {
    return [
        {
            title: "Vue 基础",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "vue-overview.md",
                "vue2/basic/basic-concept.md",
                "vue2/basic/basic-use.md", 
                "vue2/basic/basic-template-syntax.md",
                "vue2/basic/basic-data-bind.md", 
                "vue2/basic/basic-mvvm.md",   
                "vue2/basic/basic-event-handler.md",  
                "vue2/basic/basic-compute-property.md",  
                "vue2/basic/basic-watch-property.md",
                "vue2/basic/basic-bind-style.md", 
                "vue2/basic/basic-condition-render.md",  
                "vue2/basic/basic-list-render.md", 
                "vue2/basic/basic-filter.md",    
                "vue2/basic/basic-inner-cmd.md", 
                "vue2/basic/basic-custom-cmd.md",     
                "vue2/basic/basic-lifecycle.md",  
            ]
        },
        {
            title: "Vue 组件",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "vue2/component/component-basic.md",
                "vue2/component/component-no-single-file-comp.md",
                "vue2/component/component-single-file-comp.md",
            ]
        },
        {
            title: "Vue 脚手架",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "vue2/CLI/cli-init.md",
                "vue2/CLI/cli-ref-props.md",
                "vue2/CLI/cli-mixin.md",
                "vue2/CLI/cli-plugin.md",
                "vue2/CLI/cli-todolist-demo.md",
                "vue2/CLI/cli-custom-event.md",
                "vue2/CLI/cli-global-event-bus.md",
                "vue2/CLI/cli-pub-sub.md",
                "vue2/CLI/cli-transition.md",
            ]
        },
        {
            title: "Vue中的Ajax",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "vue2/ajax/ajax-basic.md",
                "vue2/ajax/ajax-slot.md",
                "vue2/ajax/ajax-github-demo.md",
            ]
        },
        {
            title: "Vuex",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "vue2/vuex/vuex-basic.md",
                "vue2/vuex/vuex-use.md",
            ]
        },
        {
            title: "Vue Router",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "vue2/vue_router/vue-router-basic.md",
                "vue2/vue_router/vue-router-use.md",
                "vue2/vue_router/vue-router-multi.md",
                "vue2/vue_router/vue-router-deliver-params.md",
                "vue2/vue_router/vue-router-program.md",
                "vue2/vue_router/vue-router-cache.md",
                "vue2/vue_router/vue-router-life-hook.md",
                "vue2/vue_router/vue-router-nav-guard.md",
                "vue2/vue_router/vue-router-work-mode.md",
            ]
        },
        {
            title: "Vue3 学习",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "vue3/vue3-use.md",
                "vue3/vue3-project.md",
                "vue3/vue3-composition-api.md",
                "vue3/vue3-responsive-principle.md",
                "vue3/vue3-lifecycle.md",
                "vue3/vue3-other-composition.md",
                "vue3/vue3-options-composition.md",
                "vue3/vue3-new-component.md",
                "vue3/vue3-other.md",
            ]
        }
    ];
}

module.exports = {
    genSidebar4Guide,genSidebar4Cplusplus, genSidebar4Database, genSidebar4Alg, genSidebar4Program, genSidebar4develop, genSidebar4microServices,
    genSidebar4method, genSidebar4Devops, genSidebar4project, genSidebar4booknote, genSidebar4interview, genSidebar4Article,
    genSidebar4dailyUse, genSidebar4About, genSidebar4Grow,genSidebar4Vue
};