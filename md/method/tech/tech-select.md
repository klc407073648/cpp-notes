# 常用的技术框架

[[toc]]


# 搜索

## github搜索

1. 搜索条件，内容，star数量，更新时间，语言，公司等

* [https://github.com/search/advanced](https://github.com/search/advanced)   
* 例如搜索一个C++的web框架
* web框架选型：Drogon，Oat++   
   * 搜索条件: ` C++ web framework stars:>1000 pushed:>2022-04-01 language:C++`

# 常用的技术框架

**前端**：

* 三件套 + React + 组件库 Ant Design + Umi + Ant Design Pro（现成的管理系统）
* Vue3 + Vite + Vant 移动端项目

# 前端框架

| 技术         | 说明                                    | 官网                                          |
| ------------ | --------------------------------------- | --------------------------------------------- |
| Vue          | 前端框架                                | https://vuejs.org/                            |
| Vue-router   | 路由框架                                | https://router.vuejs.org/                     |
| Vuex         | 全局状态管理框架                        | https://vuex.vuejs.org/                       |
| Axios        | 基于promise的网络请求库                 | https://github.com/axios/axios                |
| Vue CLI      | 一个构建数据驱动的 web 界面的渐进式框架 | https://cli.vuejs.org/zh/                     |
| React        | 用于构建用户界面的 JavaScript 库        | https://zh-hans.reactjs.org/                  |
| React Router | 完整的 React 路由解决方案               | http://react-guide.github.io/react-router-cn/ |


## 组件库

| 技术           | 说明                                                         | 官网                                         | 公司           |
| -------------- | ------------------------------------------------------------ | -------------------------------------------- | -------------- |
| Vant           | 轻量、可靠的移动端 Vue 组件库                                | https://youzan.github.io/vant/#/zh-CN        | 有赞           |
| Element        | Element，一套为开发者、设计师和产品经理准备的基于 Vue 2.0 的桌面端组件库 | https://element.eleme.io/           | 饿了么前端团队 |
| Element Plus   | 基于 Vue 3，面向设计师和开发者的组件库                       | https://element-plus.gitee.io/zh-CN/         | 饿了么前端团队 |
| v-charts       | 基于Echarts的图表框架(vue)                                   | https://v-charts.js.org/                     |                |
| Ant Design     | 是基于 Ant Design 设计体系的 React UI 组件库，主要用于研发企业级中后台产品。 | https://ant.design/index-cn   | 蚂蚁金服       |
| Ant Design Pro | 开箱即用的中台前端/设计解决方案                              | https://pro.ant.design/zh-CN/                | 蚂蚁金服       |
| UmiJs          | 是一个可插拔的企业级 React 应用框架                          | https://v3.umijs.org/zh-CN                   | 蚂蚁金服       |
| ProComponents  | 基于 Ant Design 而开发的模板组件，提供了更高级别的抽象支持，开箱即用 | https://procomponents.ant.design/components/ | 蚂蚁金服       |
| v-charts       | 基于Echarts的图表框架                                        | https://v-charts.js.org/                     | 蚂蚁金服       |

## 构建工具

| 技术       | 说明                                                         | 官网                      |
| ---------- | ------------------------------------------------------------ | ------------------------- |
| Vite       | 前端构建工具                                                 | https://vitejs.cn/        |
| Npm        | Node.js的默认包管理器                                        | https://router.vuejs.org/ |
| Yarn       | 前端包装管理器，可作为npm的替代品(通过缓存每个包来加快构建过程) | https://vuex.vuejs.org/   |
| Browserify | Node.js模块加载器，可以绑定前端依赖项，并将它们作为单个JavaScript文件加载到用户浏览器中 | https://vuex.vuejs.org/   |
| Webpack    | 高级模块绑定器，可以绑定所有依赖项，并将它们作为静态资产加载到用户浏览器中(Browserify只绑定Node.js模块，但Webpack可以处理任何类型的前端文件) | https://element.eleme.io/ |


# 后端框架

**后端**：

- java
   - spring（依赖注入框架，帮助你管理 Java 对象，集成一些其他的内容）
   - springmvc（web 框架，提供接口访问、restful接口等能力）
   - mybatis（Java 操作数据库的框架，持久层框架，对 jdbc 的封装）
   - mybatis-plus（对 mybatis 的增强，不用写 sql 也能实现增删改查）
   - springboot（**快速启动** / 快速集成项目。不用自己管理 spring 配置，不用自己整合各种框架）
   - junit 单元测试库
- c++
   - poco: 是一个开源的C++类库的集合,它主要提供简单的、快速的网络和可移植应用程序的C++开发
   - Boost：大量通用C++库的集合。
   - libev：功能齐全，高性能的时间循环，轻微地仿效libevent，但是不再像libevent一样有局限性，也修复了它的一些bug。
   - protobuf：协议缓冲，谷歌的数据交换格式。
- mysql 数据库

**部署**：服务器 / 容器（平台）

| 技术                   | 说明                 | 官网                                                 |
| ---------------------- | -------------------- | ---------------------------------------------------- |
| Spring Cloud           | 微服务框架           | https://spring.io/projects/spring-cloud              |
| Spring Cloud Alibaba   | 微服务框架           | https://github.com/alibaba/spring-cloud-alibaba      |
| Spring Boot            | 容器+MVC框架         | https://spring.io/projects/spring-boot               |
| Spring Security Oauth2 | 认证和授权框架       | https://spring.io/projects/spring-security-oauth     |
| MyBatis                | ORM框架              | http://www.mybatis.org/mybatis-3/zh/index.html       |
| MyBatisGenerator       | 数据层代码生成       | http://www.mybatis.org/generator/index.html          |
| PageHelper             | MyBatis物理分页插件  | http://git.oschina.net/free/Mybatis_PageHelper       |
| Knife4j                | 文档生产工具         | https://github.com/xiaoymin/swagger-bootstrap-ui     |
| Elasticsearch          | 搜索引擎             | https://github.com/elastic/elasticsearch             |
| RabbitMq               | 消息队列             | https://www.rabbitmq.com/                            |
| Redis                  | 分布式缓存           | https://redis.io/                                    |
| MongoDb                | NoSql数据库          | https://www.mongodb.com/                             |
| Docker                 | 应用容器引擎         | https://www.docker.com/                              |
| Druid                  | 数据库连接池         | https://github.com/alibaba/druid                     |
| OSS                    | 对象存储             | https://github.com/aliyun/aliyun-oss-java-sdk        |
| MinIO                  | 对象存储             | https://github.com/minio/minio                       |
| JWT                    | JWT登录支持          | https://github.com/jwtk/jjwt                         |
| LogStash               | 日志收集             | https://github.com/logstash/logstash-logback-encoder |
| Lombok                 | 简化对象封装工具     | https://github.com/rzwitserloot/lombok               |
| Seata                  | 全局事务管理框架     | https://github.com/seata/seata                       |
| Portainer              | 可视化Docker容器管理 | https://github.com/portainer/portainer               |
| Jenkins                | 自动化部署工具       | https://github.com/jenkinsci/jenkins                 |
| Kubernetes             | 应用容器管理平台     | https://kubernetes.io/                               |
