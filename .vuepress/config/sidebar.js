/*
import {
    genSidebar4Cplusplus, genSidebar4Database, genSidebar4Alg, genSidebar4Program, genSidebar4develop, genSidebar4microServices,
    genSidebar4arch, genSidebar4method, genSidebar4Devops, genSidebar4project, genSidebar4booknote, genSidebar4interview, genSidebar4Article,
    genSidebar4dailyUse, genSidebar4About
} from "./conifg/function.js";
*/

module.exports = {
    "/md/c++/": genSidebar4Cplusplus(),
    "/md/database/": genSidebar4Database(),
    "/md/algorithm/": genSidebar4Alg(),
    "/md/programming/": genSidebar4Program(),
    "/md/develop/": genSidebar4develop(),
    "/md/micro-services/": genSidebar4microServices(),
    "/md/arch/": genSidebar4arch(),
    "/md/method/": genSidebar4method(),
    "/md/devops/": genSidebar4Devops(),
    "/md/project/": genSidebar4project(),
    "/md/book-note/": genSidebar4booknote(),
    "/md/interview/": genSidebar4interview(),
    "/md/article/": genSidebar4Article(),
    "/md/daily-use/": genSidebar4dailyUse(),
    "/md/about/": genSidebar4About(),
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
                "basic/c++-basic-oop.md"
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
                "system/doc.md"
            ]
        },
        {
            title: "设计模式",
            collapsable: false,
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
            title: "开发",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "todo.md"
            ]
        },
        {
            title: "常用开发库",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "library/library-cppcheck.md",
                "library/library-cppunit.md",
                "library/library-fastcgi.md",
                "library/library-hiredis.md",
                "library/library-jsoncpp.md",
                "library/library-log4cpp.md",
                "library/library-mysql.md",
                "library/library-poco.md"
            ]
        }
    ];
}

// micro-services page
function genSidebar4microServices() {
    return [
        {
            title: "理论基础",
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
            title: "ZeroMQ",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "middleware/zeromq/zeromq-demo.md",
                "middleware/zeromq/zeromq-part1.md",
                "middleware/zeromq/zeromq-part2.md",
                "middleware/zeromq/zeromq-part3.md"
            ]
        }
    ];

}

// arch page
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
                "concept/concept-agent.md",
                "concept/concept-communication.md"
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
                "code-style/code-style-google-c++.md"
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
            title: "Nginx",
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
            title: "常用快捷键",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "shortcut/linux.md",
                "shortcut/vim.md",
                "shortcut/vscode.md",
                "shortcut/idea.md"
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
            title: "实践 - Docker",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "practice/docker/jenkins/practice-docker-jenkins.md",
                "practice/docker/mysql/practice-docker-mysql.md",
                "practice/docker/redis/practice-docker-redis.md"
            ]
        },
        {
            title: "实践 - 工具类",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "practice/tools/practice-tools-git-config-key.md",
                "practice/tools/practice-tools-git.md",
                "practice/tools/practice-tools-gitbook.md"
            ]
        },
        {
            title: "实践 - 实用型",
            collapsable: false,
            sidebarDepth: 0,
            children: [
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
            title: "书籍推荐",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "book-note-index.md"
            ]
        },
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
        },
        {
            title: "大型网站技术架构——核心原理与案例分析 详解",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "websiteTechArch/websiteTechArch-index.md",
                "websiteTechArch/websiteTechArch-chapter-1-1.md",
                "websiteTechArch/websiteTechArch-chapter-1-2.md",
                "websiteTechArch/websiteTechArch-chapter-1-3.md",
                "websiteTechArch/websiteTechArch-chapter-2-1.md",
                "websiteTechArch/websiteTechArch-chapter-2-2.md",
                "websiteTechArch/websiteTechArch-chapter-2-3.md",
                "websiteTechArch/websiteTechArch-chapter-2-4.md",
                "websiteTechArch/websiteTechArch-chapter-2-5.md"
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
                "knowledge/programming-questions.md"
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
                "distribute/article-distributed-cellular.md"
            ]
        },
        {
            title: "成长",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "grow/article-grow-Stay_hungry_Stay_foolish.md",
                "grow/article-grow-Stay_hungry_Stay_young.md",
                "grow/article-grow-cross-life-valley.md"
            ]
        },
        {
            title: "问题解决",
            collapsable: false,
            sidebarDepth: 0,
            children: [
                "problem/article-problem-top.md",
                "problem/article-problem-pstack.md"
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
                "tools/daily-use-tools-overview.md"
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
