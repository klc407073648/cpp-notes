# 技术选型 - 基于drogon实现用户中心后端

[[toc]]

# 技术选型
   * 语言选择：c++
   * web框架选型：Drogon，Oat++   （https://github.com/search/advanced）
      * 搜索条件: ` C++ web framework stars:>1000 pushed:>2022-04-01 language:C++`

# drogon安装过程

* [wiki drogon](https://github.com/drogonframework/drogon/wiki/)
* [c++高性能web框架drogon入门教程一](https://blog.csdn.net/zh7314/article/details/115652164)
* [Github drogon](https://github.com/drogonframework/drogon)
* [Github jsoncpp](https://github.com/open-source-parsers/jsoncpp)
* [drogon-realworld](https://github.com/arslan2012/drogon-realworld-example-app)

## 依赖库

```
trantor，non-blocking I/O C++网络库，也是作者开发，已作为git仓库submodule，无需提前安装；
jsoncpp，json的c++库，版本不低于1.7；
libuuid，生成uuid的c库；
zlib，用于支持压缩传输；
OpenSSL，并非必须，如果安装了OpenSSL库，drogon将支持HTTPS，否则drogon只支持HTTP；
c-ares, 并非必须，如果安装了ares库，drogon对DNS的支持会具有更好的性能；
libbrotli，并非必须，如果安装了brotli库，drogon的HTTP响应会支持brotli压缩；
boost，版本不低于1.61，只在C++编译器不支持c++17时才需要安装；
postgreSQL, mariadb, sqlite3的客户端开发库，并非必须，安装后drogon会提供对响应的库的访问能力；
gtest, 并非必须，如果安装了gtest库，drogon的单元测试代码可以被编译；
```

jsoncpp
```
git clone https://github.com/open-source-parsers/jsoncpp
cd ./jsoncpp && mkdir build && cd build && cmake .. && make && make install

安装后，使用下述语句解决 `drogon_ctl在创建的新项目的时候会找不到jsoncpp`

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib64   
export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/lib64    
source /etc/profile
```

uuid
```
yum install -y libuuid-devel
```

OpenSSL
```
yum install -y openssl-devel
```

zlib
```
yum install -y zlib-devel
```

postgresql
```
yum install -y postgresql-devel
```

mysql
```
yum install -y mariadb-devel
```

drogon
```
git clone https://github.com/drogonframework/drogon.git
cd drogon
git submodule update --init
mkdir build
cd build
cmake ..
make && sudo make install
```

如果需要使用postgresql
```
docker run -it -d --name postgresql -e POSTGRES_USER=postgres -e POSTGRES_DB=student -e POSTGRES_PASSWORD=456789 -p 5432:5432 -v /data/postgres_data:/var/lib/postgresql/data --privileged postgres

pg_hba.conf
# IPv4 local connections:
host    all        all        0.0.0.0/0        password
```

## 创建工程的全过程

```
# 创建工程
dg_ctl create project usercenter

# 控制器创建
cd ./usercenter/controllers/
dg_ctl create controller -h ControllerTest

# 过滤器创建
cd ../filters/
dg_ctl create filter LoginFilter

# 创建模型，需要配置config.json里mysql配置信息
cd ..
dg_ctl create model models
```

# 实现设计

1. 根据dg_ctl命令创建restful api
   * 控制器创建：`dg_ctl create controller -h api::user`
   * 测试：
      * 输入：
         ```
         curl -XPOST 127.0.0.1:8082/api/user/register -H 'content-type:  application/json' -d '{"userAccount":"111","userPassword":"222","checkPassword":"333","planetCode":"4444"}'
         ```
      * 输出：
         ```
         {"code":200,"data":{"checkPassword":"333","email":"","planetCode":"4444","userAccount":"111","userPassword":"222"},"description":"ok","message":"ok","object":{"checkPassword":"333","email":null,"planetCode":"4444","userAccount":"111","userPassword":"222"}}
         ```
   * 小步验证：前端与后端的 `/api/user/register`  接口交互是否正常

2. 设计类，封装类

   * common
      * BaseResponse ———— 基础响应
      * ErrorCode ———— 错误码
      * ResultUtils ———— 结果工具类: 封装基础响应内容
      * Response2json ———— 响应转换类: 适配drogon框架的HttpResponse::newHttpJsonResponse，将结果工具类转换成JSON对象
   * constant
      * UserConstant ———— 用户常量定义
   * controllers
      * api_user ————> UserController
   * exception
      * BusinessException ———— 业务异常类
   * models
      * 利用 `dg_ctl create model models` 自动生成表对应的内容
         * User.h,User.cc 
      * request ———— 暂未实现 替代方案  UserController 中 fromRequest函数重写，以便从HttpRequest中获取User对象
         * UserLoginRequest
         * UserRegisterRequest
   * services
      * UserService ———— 接口
      * UserServiceImpl ———— 实现

# docker方式从0-1部署项目

## 环境准备
```bash
# 下载安装docker和docker-compose
yum install -y docker
systemctl enable docker
systemctl start docker
curl -L https://get.daocloud.io/docker/compose/releases/download/1.25.5/docker-compose-`uname -s`-`uname -m` > /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose
docker-compose --version
```
## 前端

```bash
# 将前端文件放置到 /home/klc/frontend/ 路径下，执行构建命令
cd /home/klc/frontend/
docker build -t user-center-frontend:v0.0.1 .
docker run -p 81:80 -d user-center-frontend:v0.0.1
```
## 数据库

```bash
# 将数据库文件放置到 /home/klc/mysql/ 路径下，执行构建命令
cd /home/klc/mysql/
 ./build_mysql.sh
```

## 后端

```bash
# 将后端文件放置到 /home/klc/backend/drogon/ 路径下，执行构建命令
docker pull docker.io/drogonframework/drogon
docker run -it -d -p 8082:8082 -v /home/klc/backend/drogon/:/home/ --name drogon_test docker.io/drogonframework/drogon /bin/bash

docker exec -it drogon_test bash
cd /home/build
cmake ..
make
./usercenter
```


## 测试过程

**注册接口测试**
```bash
后端:
root@bb2ddc2a86db:/home/build# ./usercenter
20220604 00:34:55.012521 UTC 1130 DEBUG [UserController] UserController constructor! - UserController.h:48
20220604 00:35:07.316278 UTC 1131 INFO  UserController::fromRequest:{
   "checkPassword" : "333",
   "planetCode" : "4444",
   "userAccount" : "111",
   "userPassword" : "222"
   
}
 - UserController.cc:20
20220604 00:35:07.316331 UTC 1131 INFO  UserController::userRegister in - UserController.cc:29
20220604 00:35:07.316345 UTC 1131 INFO  UserServiceImpl::userRegister in - UserServiceImpl.cc:11
20220604 00:35:07.316348 UTC 1131 INFO  userAccount:111 - UserServiceImpl.cc:12
20220604 00:35:07.316351 UTC 1131 INFO  userPassword:222 - UserServiceImpl.cc:13
20220604 00:35:07.316353 UTC 1131 INFO  checkPassword:333 - UserServiceImpl.cc:14
20220604 00:35:07.316356 UTC 1131 INFO  planetCode:4444 - UserServiceImpl.cc:15
20220604 00:35:07.316460 UTC 1131 INFO  BusinessException error: message:请求参数错误,description用户账号小于4位 - UserController.cc:59

测试注册：
[root@VM-16-6-centos ~]# curl -XPOST 81.68.132.31:8082/api/user/register -H 'content-type:  application/json' -d '{"userAccount":"111","userPassword":"222","checkPassword":"333","planetCode":"4444"}'
{"code":40000,"data":0,"description":"用户账号小于4位","message":"请求参数错误"}

是不是返回的data = null 注册就会错？？？
```


TDD：

```
测试场景：
异常测试：JSON Body不填会core
 1. 非空
 分别验证：账户、密码、校验密码、星球编号为空的场景。
 
 
 登陆有问题，在保存登陆状态的函数里 —————— 需要修改config.json里 "enable_session": true
```

TODO:

* 使用orm模型： 学习使用navicat 转化mysql模型到postgresql
* 后续整理接口测试文件，测试功能


