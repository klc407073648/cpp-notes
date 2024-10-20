# 项目开发 - 注意事项

[[toc]]

# 参考文件

* [多环境设计](https://blog.csdn.net/weixin_41701290/article/details/120173283)

# 前端

* 按需引入组件
* 公用组件封装
* 公用接口封装

# 后端

* 操作接口**：一定要加入事务注解，特别是对多表操作的接口逻辑，一定要保证，所有表操作都成功才能继续，要不然就要回滚，避免引入脏数据**。
* 数据限制：很多数据不应该直接使用用户或前端传递的参数，
    * 例如，要对用户传递的数据做校验，同时，一些信息不能使用用户传递的参数，而是接口中自己去查数据来确定
* 模型中封装了各个Controller的请求头封装类
* 使用VO对象过滤敏感信息
* 全局异常封装类
* 全局请求类
* 全局响应类
* 自定义错误码，返回类支持返回正常和错误

## tips

1. 序列化的用法
2. 以debug模式启动，调试接口函数
3. 开启mybatis-plus的逻辑删除，默认会将删除转换成更新，isDelete字段来屏蔽查询
4. 用户管理接口鉴权
5. 不要过渡设计
6. 前端通过路由代理，解决跨域访问问题
7. 前后端都需要做数据校验，避免不了其他方式侵入
8. 写代码流程
   1. 先做设计
   2. 代码实现
   3. 持续优化！（复用代码、提取公共逻辑 / 常量）
   

# 知识点

## 如何知道是哪个用户登录了？

1. 连接服务器端后，得到一个 session 状态（匿名会话），返回给前端
2. 登录成功后，得到了登录成功的 session，并且给该session设置一些值（比如用户信息），返回给前端一个设置 cookie 的 命令
    * **session => cookie** 
3. 前端接收到后端的命令后，设置 cookie，保存到浏览器内
4. 前端再次请求后端的时候（相同的域名），在请求头中带上cookie去请求
5. 后端拿到前端传来的 cookie，找到对应的 session
6. 后端从 session 中可以取出基于该 session 存储的变量（用户的登录信息、登录名）

## 跨域问题

CORS:全称"跨域资源共享"(Cross-origin resource sharing)

> 浏览器为了用户的安全，仅允许向 **同域名、同端口** 的服务器发送请求。

如何解决跨域？———— 最直接的方式：把域名、端口改成相同的，不切实际。实际开发过程中ip和port都不同

解决方案：添加跨域头，让服务器告诉浏览器：允许跨域（返回 cross-origin-allow 响应头）

### 网关支持（Nginx）

```nginx
# 跨域配置
location ^~ /api/ {
    proxy_pass http://127.0.0.1:8080/api/;
    add_header 'Access-Control-Allow-Origin' $http_origin;
    add_header 'Access-Control-Allow-Credentials' 'true';
    add_header Access-Control-Allow-Methods 'GET, POST, OPTIONS';
    add_header Access-Control-Allow-Headers '*';
    if ($request_method = 'OPTIONS') {
        add_header 'Access-Control-Allow-Credentials' 'true';
        add_header 'Access-Control-Allow-Origin' $http_origin;
        add_header 'Access-Control-Allow-Methods' 'GET, POST, OPTIONS';
        add_header 'Access-Control-Allow-Headers' 'DNT,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Range';
        add_header 'Access-Control-Max-Age' 1728000;
        add_header 'Content-Type' 'text/plain; charset=utf-8';
        add_header 'Content-Length' 0;
        return 204;
    }
}
```

#### 修改后端服务

1. 配置 @CrossOrigin 注解，在Controller类上添加一个“@CrossOrigin“注解就可以实现对当前controller 的跨域 访问
`@CrossOrigin(origins = {"http://localhost:3000","http://localhost:8000"},allowedHeaders = "*",methods = {},allowCredentials = "true")`

2. 添加 web 全局请求拦截器

```java
   @Configuration
   public class WebMvcConfg implements WebMvcConfigurer {
    
       @Override
       public void addCorsMappings(CorsRegistry registry) {
           //设置允许跨域的路径
           registry.addMapping("/**")
                   //设置允许跨域请求的域名
                   //当**Credentials为true时，**Origin不能为星号，需为具体的ip地址【如果接口不带cookie,ip无需设成具体ip】
                   .allowedOrigins("http://localhost:9527")
                   //是否允许证书 不再默认开启
                   .allowCredentials(true)
                   //设置允许的方法
                   .allowedMethods("*")
                   //跨域允许时间
                   .maxAge(3600);
       }
   }
```

3. 定义新的 corsFilter Bean，参考：https://www.jianshu.com/p/b02099a435bd

## 访问项目流程

前端项目访问流程：用户输入网址 => 域名解析服务器（把网址解析为 ip 地址 / 交给其他的域名解析服务） => 服务器 =>（防火墙）=> nginx 接收请求，找到对应的文件，返回文件给前端 => 前端加载文件到浏览器中（js、css） => 渲染页面
后端项目访问流程：用户输入网址 => 域名解析服务器 => 服务器 => nginx 接收请求 => 后端项目（比如 8080端口）


## 多环境

> 多环境：指同一套项目代码在不同的阶段需要根据实际情况来调整配置并且部署到不同的机器上。

本地开发：localhost（127.0.0.1）

为什么需要多环境？

1. 每个环境互不影响
2. 区分不同的阶段：开发 / 测试 / 生产
3. 对项目进行优化：
   1. 本地日志级别
   2. 精简依赖，节省项目体积
   3. 项目的环境 / 参数可以调整，比如 JVM 参数

针对不同环境做不同的事情。



### 多环境部署

1. 本地环境（自己的电脑）localhost
2. 开发环境（远程开发）大家连同一台机器，为了大家开发方便
3. 测试环境（测试）开发 / 测试 / 产品，单元测试 / 性能测试 / 功能测试 / 系统集成测试，独立的数据库、独立的服务器
4. 预发布环境（体验服）：和正式环境一致，正式数据库，更严谨，查出更多问题
5. 正式环境（线上，公开对外访问的项目）：尽量不要改动，保证上线前的代码是 “完美” 运行
6. 沙箱环境（实验环境）：为了做实验



### 前端多环境部署

- 请求地址

  - 开发环境：localhost:8000
  - 线上环境：1.1.1.1:8080

  ```js
  startFront(env) {
      if(env === 'prod') {
          // 不输出注释 
          // 项目优化
          // 修改请求地址
      } else {
          // 保持本地开发逻辑
      }
  }
  ```

  用了 umi 框架，build 时会自动传入 NODE_ENV == production 参数，start NODE_ENV 参数为 development

- 启动方式

  - 开发环境：npm run start（本地启动，监听端口、自动更新）
  - 线上环境：npm run build（项目构建打包），可以使用 serve 工具启动（npm i -g serve）

- 项目的配置

  不同的项目（框架）都有不同的配置文件，umi 的配置文件是 config，可以在配置文件后添加对应的环境名称后缀来区分开发环境和生产环境。参考文档：https://umijs.org/zh-CN/docs/deployment

  - 开发环境：config.dev.ts
  - 生产环境：config.prod.ts
  - 公共配置：config.ts 不带后缀


### 后端多环境

SpringBoot 项目，通过 application.yml 添加不同的后缀来区分配置文件

可以在启动项目时传入环境变量：

```bash
java -jar .\user-center-backend-0.0.1-SNAPSHOT.jar --spring.profiles.active=prod
```

主要是改：

  - 依赖的环境地址
  - 数据库地址
  - 缓存地址
  - 消息队列地址
  - 项目端口号
  - 服务器配置