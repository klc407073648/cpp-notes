# Apollo - 使用配置中心

[[toc]]

## 编写apollo配置

1. 打开http://localhost:8070

> ![apollo-login](/_images/micro-services/middleware/apollo/apollo-login.png)

2. 输入用户名apollo，密码admin后登录

  ![apollo-login](/_images/micro-services/middleware/apollo/apollo-sample-home.png)

3. 点击创建应用，进行应用的设置

 ![create_app](/_images/micro-services/middleware/apollo/create_app.png)

> 如果提示 <font color='red'>**系统出错，请重试或联系系统负责人**</font>，请稍后几秒钟重试一下，因为通过Eureka注册的服务有一个刷新的延时。
>
> 4. 创建后，界面如下：
>
>    ![app_ui](/_images/micro-services/middleware/apollo/app_ui.png)

5. 创建Namespace(TEST1.mysql)，发布mysql的信息：

   ![发布mysql配置](/_images/micro-services/middleware/apollo/发布mysql配置.png)

## 运行apollo go客户端程序

演示从Apollo配置中心获取配置。

```
# 构建apollo客户端镜像
cd /home/apollo_go/build_apollo_go/
chmod 777 *.sh
dos2unix  *.sh
./build_go.sh

# 使用镜像启动容器
docker run -it -d  --name apollo_go_client  docker.io/klc407073648/centos_build_go:v1.0

#进入容器
docker exec -it apollo_go_client bash

#修改go源码，需要修改AppID,NamespaceName等内容
cd /home/go/prj/
vi main.go
```

客户端返回：

```
[root@65d810cabb13 prj]# vi main.go
[root@65d810cabb13 prj]# go run main.go
[get all server info: [{"appName":"APOLLO-CONFIGSERVICE","instanceId":"bca74f4ac4e4:apollo-configservice:8080","homepageUrl":"http://172.27.0.2:8080/"}]]
[syncServerIpList started]
[init notifySyncConfigServices finished]
[[agollo start finished ! ]]
key :  HOST_MACHINE_MYSQL_PORT , value : 3308
key :  MYSQL_DATA_DIR , value : ./data/mysql
key :  MYSQL_LOG_DIR , value : ./logs/mysql
key :  MYSQL_IMAGE_NAME , value : stibel_mysql
key :  MYSQL_IMAGE_TAR , value : v1.0
key :  MYSQL_CONTAINER_NAME , value : stibel_mysql_0
[get all server info: [{"appName":"APOLLO-CONFIGSERVICE","instanceId":"bca74f4ac4e4:apollo-configservice:8080","homepageUrl":"http://172.27.0.2:8080/"}]]
[syncServerIpList started]
[init notifySyncConfigServices finished]
[[agollo start finished ! ]]
key :  MYSQL_DATA_DIR , value : ./data/mysql
key :  MYSQL_LOG_DIR , value : ./logs/mysql
key :  MYSQL_IMAGE_NAME , value : stibel_mysql
key :  MYSQL_IMAGE_TAR , value : v1.0
key :  MYSQL_CONTAINER_NAME , value : stibel_mysql_0
key :  HOST_MACHINE_MYSQL_PORT , value : 3308
```
