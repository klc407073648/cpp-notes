# Docker - docker-compose学习

# 参考资料

* [docker compose官网](https://docs.docker.com/compose/)
* [Dockerfile 中的 CMD 与 ENTRYPOINT ](https://www.cnblogs.com/yungyu16/p/12604816.html)
* [docker-compose.yml 配置文件编写详解](https://blog.csdn.net/qq_36148847/article/details/79427878)

## 概念

Compose 项目是 Docker 官方的开源项目，负责实现对 Docker 容器集群的快速编排。使用前面介绍的Dockerfile我们很容易定义一个单独的应用容器。然而在日常开发工作中，经常会碰到需要多个容器相互配合来完成某项任务的情况。例如要实现一个 Web 项目，除了 Web 服务容器本身，往往还需要再加上后端的数据库服务容器；再比如在分布式应用一般包含若干个服务，每个服务一般都会部署多个实例。如果每个服务都要手动启停，那么效率之低、维护量之大可想而知。这时候就需要一个工具能够管理一组相关联的的应用容器，这就是Docker Compose。

Compose有2个重要的概念：

- 项目（Project）：由一组关联的应用容器组成的一个完整业务单元，在 docker-compose.yml 文件中定义。
- 服务（Service）：一个应用的容器，实际上可以包括若干运行相同镜像的容器实例。

## docker compose使用

`docker-compose.yml` 格式如下，注意：YAML 文件必须要键值之间的 `:` 后面必须有一个空格，缩进表示层级，要注意缩进
有使用到的 volumes 和 networks 必须声明

```yaml
# 指定版本
version: "3"
# 服务的集合
services:
  # 其中一个服务，服务名为：webapp
  webapp:
    # 指定该服务使用的镜像
    image: examples/web
    # 端口映射
    ports:
      - "80:80"
    # 数据卷
    volumes:
      - "/data"
```

## 简单上手

在一个 Compose 中启动 Tomcat, MySQL, redis，创建 `docker-compose.yml`

```yaml
version: "3.0"

services:
  tomcat:
    container_name: mytomcat # --name
    image: tomcat:8.0-jre8
    ports:
      - "8080:8080"
    volumes:
      - "tomcatwebapps:/usr/local/tomcat/webapps"
    networks:
      - some_network
    # tomcat 服务依赖于 mysql 和 redis
    depends_on:
      - mysql
      - redis
  mysql:
    container_name: mysql
    image: mysql:5.7.32
    ports:
      - "3306:3306"
    volumes:
      - "mysqldata:/var/lib/mysql"
      - "mysqlconf:/etc/mysql"
    environment:
      - MYSQL_ROOT_PASSWORD=1234
    networks:
      some_network:
  redis:
    container_name: redis
    image: redis:5.0.10
    ports:
      - "6379:6379"
    volumes:
      - "redisdata:/data"
    command: "redis-server --appendonly yes"
    networks:
      some_network:

# 使用到的 volumes 和 networks 必须声明
volumes:
  tomcatwebapps: 
  mysqldata:
  mysqlconf:
  redisdata: 

networks:
  # 声明名称为 “some_network” 的网络
  some_network:
```

在 `docker-compose.yml` 所在路径执行 `docker-compose up` 启动 Compose 项目，它会下载使用到的镜像并在前台运行打印日志，可以使用 Ctrl + C 终止

如果需要后台运行执行 `docker-compose up -d`，这时候使用 `docker ps` 可以看到 Compose 已经根据 yaml 创建了相关的容器，使用 `docker-compose down` 停止 Compse 并移除自动创建的网桥

使用 `docker network ls` 查看网络或者 `docker volume ls` 查看数据卷，Compose 定义的网络或数据卷名称格式为：docker-compose.yml所在文件夹的名称加上下划线再加上 yaml 中定义名称，如果在 "dockerfile" 文件夹下创建 yaml 文件并启动，那么网络名称为：`dockerfile_some_network`

tomcat 服务使用了 `depends_on`，**表示它依赖于 redis 和 mysql 服务，Compose 将优先启动它的依赖再启动它**

## 命令梳理

Docker Compose 的命令与 Dokcer 类似，可以使用 --help 参数，就可以查询到到对应命令的使用方法

```bash
docker-compose --help
```

默认启动的模版文件名为 docker-compose.yml，可以使用 -f 指定自定义的模版文件
可以通过 config 命令，检查模版文件语法是否正确

docker-compse 也包含很多子命令：
启动停止相关：up, down, restart, stop, pasue, unpause

资源相关：ps, top, kill, run

进入容器：exec

查看日志：logs

很多子命令都可以在后面跟上某个具体的 service 名称，定向地操作，下面不一一举例，
可以使用`docker-compose help` 再跟上子命令名称，查询其用法

```bash
# 后台启动 yaml 定义的所有容器
docker-compose up -d
# 仅启动 mysql 这个service，会启动其依赖的 service
docker-compose up mysql 指定启动的server名称，
# 停止容器并移除自动创建的网桥
docker-compose down 
# 重启所有 service 后面可以指定上某个具体的 service
docker-compose restart

# 暂停 和 恢复
docker-compose pause
docker-compose unpause

# 进入 redis 这个 service 使用 exit 退出
docker-compose exec redis bash

# 列出当前 yaml 中定义的容器的信息
docker-compose ps

# 删除当前 yaml 中定义的容器，需要先 stop，后面可以指定上某个具体的 service
docker-compose rm

# 查看各个 service 容器内运行的进程情况
docker-compose top

# 查看日志默认查看 yaml 所有的，可以跟上具体 service
# -f 可以保持跟踪，新的日志会马上显示在屏幕上
docker-compose logs
```

## 配置选项

### build

服务除了可以基于指定的镜像，还可以基于一份 Dockerfile，在使用 up 启动之时执行构建任务，这个构建标签就是 build，它可以指定 Dockerfile 所在文件夹的路径。Compose 将会利用它自动构建这个镜像，然后使用这个镜像启动服务容器。

```jsx
build: /path/to/build/dir
```

也可以是相对路径，只要上下文确定就可以读取到 Dockerfile。

```undefined
build: ./dir
```

设定上下文根目录，然后以该目录为准指定 Dockerfile。

```undefined
build:
  context: ../
  dockerfile: path/of/Dockerfile
```

注意 build 都是一个目录，如果你要指定 Dockerfile 文件需要在 build 标签的子级标签中使用 dockerfile 标签指定，如上面的例子。
 如果你同时指定了 image 和 build 两个标签，那么 Compose 会构建镜像并且把镜像命名为 image 后面的那个名字。

```undefined
build: ./dir
image: webapp:tag
```

既然可以在 docker-compose.yml 中定义构建任务，那么一定少不了 arg 这个标签，就像 Dockerfile 中的 ARG 指令，它可以在构建过程中指定环境变量，但是在构建成功后取消，在 docker-compose.yml 文件中也支持这样的写法：

```undefined
build:
  context: .
  args:
    buildno: 1
    password: secret
```

下面这种写法也是支持的，一般来说下面的写法更适合阅读。

```undefined
build:
  context: .
  args:
    - buildno=1
    - password=secret
```

与 ENV 不同的是，ARG 是允许空值的。例如：

```undefined
args:
  - buildno
  - password
```

这样构建过程可以向它们赋值。

> 注意：YAML 的布尔值（true, false, yes, no, on, off）必须要使用引号引起来（单引号、双引号均可），否则会当成字符串解析。

### command

使用 command 可以覆盖容器启动后默认执行的命令。

```bash
command: bundle exec thin -p 3000
```

也可以写成类似 Dockerfile 中的格式：

```bash
command: [bundle, exec, thin, -p, 3000]
```

### container_name

前面说过 Compose 的容器名称格式是：<项目名称>*<服务名称>*<序号>

虽然可以自定义项目名称、服务名称，但是如果你想完全控制容器的命名，可以使用这个标签指定：

```undefined
container_name: app
```

这样容器的名字就指定为 app 了。

### depends_on

在使用 Compose 时，最大的好处就是少打启动命令，但是一般项目容器启动的顺序是有要求的，如果直接从上到下启动容器，必然会因为容器依赖问题而启动失败。

例如在没启动数据库容器的时候启动了应用容器，这时候应用容器会因为找不到数据库而退出，为了避免这种情况我们需要加入一个标签，就是 depends_on，这个标签解决了容器的依赖、启动先后的问题。

例如下面容器会先启动 redis 和 db 两个服务，最后才启动 web 服务：

```yaml
version: '2'
services:
  web:
    build: .
    depends_on:
      - db
      - redis
  redis:
    image: redis
  db:
    image: postgres
```

注意的是，默认情况下使用 docker-compose up web 这样的方式启动 web 服务时，也会启动 redis 和 db 两个服务，因为在配置文件中定义了依赖关系。

### dns

和 --dns 参数一样用途，格式如下：

```css
dns: 8.8.8.8
```

也可以是一个列表：

```css
dns:
  - 8.8.8.8
  - 9.9.9.9
```

### dns_search 

dns_search 的配置也类似

```css
dns_search: example.com
dns_search:
  - dc1.example.com
  - dc2.example.com
```

### tmpfs

挂载临时目录到容器内部，与 run 的参数一样效果：

```undefined
tmpfs: /run
tmpfs:
  - /run
  - /tmp
```

### deploy
指定与部署和运行服务相关的配置

```yaml
version: '3'
services:
  redis:
    image: redis:alpine
    deploy:
      replicas: 6
      update_config:
        parallelism: 2
        delay: 10s
      restart_policy:
        condition: on-failure
```

这里有几个子选项

#### endpoint_mode
指定连接到群组外部客户端服务发现方法

* endpoint_mode:vip ：Docker 为该服务分配了一个虚拟 IP(VIP),作为客户端的 “前端“ 部位用于访问网络上的服务。
* endpoint_mode: dnsrr : DNS轮询（DNSRR）服务发现不使用单个虚拟 IP。Docker为服务设置 DNS 条目，使得服务名称的 DNS 查询返回一个 IP 地址列表，并且客户端直接连接到其中的一个。如果想使用自己的负载平衡器，或者混合 Windows 和 Linux 应用程序，则 DNS 轮询调度（round-robin）功能就非常实用。

```yaml
version: "3.3"

services:
  wordpress:
    image: wordpress
    ports:
      - 8080:80
    networks:
      - overlay
    deploy:
      mode: replicated
      replicas: 2
      endpoint_mode: vip

  mysql:
    image: mysql
    volumes:
       - db-data:/var/lib/mysql/data
    networks:
       - overlay
    deploy:
      mode: replicated
      replicas: 2
      endpoint_mode: dnsrr

volumes:
  db-data:

networks:
  overlay:
```

#### labels
指定服务的标签，这些标签仅在服务上设置。

```yaml
version: "3"
services:
  web:
    image: web
    deploy:
      labels:
        com.example.description: "This label will appear on the web service"
```


通过将 deploy 外面的 labels 标签来设置容器上的 labels

```yaml
version: "3"
services:
  web:
    image: web
    labels:
      com.example.description: "This label will appear on all containers for the web service"
```

#### mode

* global:每个集节点只有一个容器
* replicated:指定容器数量（默认）

```yaml
version: '3'
services:
  worker:
    image: dockersamples/examplevotingapp_worker
    deploy:
      mode: global
```

#### placement
指定 constraints 和 preferences

```yaml
version: '3'
services:
  db:
    image: postgres
    deploy:
      placement:
        constraints:
          - node.role == manager
          - engine.labels.operatingsystem == ubuntu 14.04
        preferences:
          - spread: node.labels.zone
```

#### replicas
如果服务是 replicated（默认)，需要指定运行的容器数量

```yaml
version: '3'
services:
  worker:
    image: dockersamples/examplevotingapp_worker
    networks:
      - frontend
      - backend
    deploy:
      mode: replicated
      replicas: 6
```

#### resources
配置资源限制

```yaml
version: '3'
services:
  redis:
    image: redis:alpine
    deploy:
      resources:
        limits:
          cpus: '0.50'
          memory: 50M
        reservations:
          cpus: '0.25'
          memory: 20M
```

此例子中，redis 服务限制使用不超过 50M 的内存和 0.50（50％）可用处理时间（CPU），并且 保留 20M 了内存和 0.25 CPU时间

#### restart_policy
配置容器的重新启动，代替 restart

* condition:值可以为 none 、on-failure 以及 any(默认)
* delay: 尝试重启的等待时间，默认为 0
* max_attempts:在放弃之前尝试重新启动容器次数（默认：从不放弃）。如果重新启动在配置中没有成功 window，则此尝试不计入配置max_attempts 值。例如，如果 max_attempts 值为 2，并且第一次尝试重新启动失败，则可能会尝试重新启动两次以上。
* windows:在决定重新启动是否成功之前的等时间，指定为持续时间（默认值：立即决定）。

```yaml
version: "3"
services:
  redis:
    image: redis:alpine
    deploy:
      restart_policy:
        condition: on-failure
        delay: 5s
        max_attempts: 3
        window: 120s
```

#### update_config
配置更新服务，用于无缝更新应用（rolling update)

* parallelism：一次性更新的容器数量
* delay：更新一组容器之间的等待时间。
* failure_action：如果更新失败，可以执行的的是 continue、rollback 或 pause （默认）
* monitor：每次任务更新后监视失败的时间(ns|us|ms|s|m|h)（默认为0）
* max_failure_ratio：在更新期间能接受的失败率
* order：更新次序设置，top-first（旧的任务在开始新任务之前停止）、start-first（新的任务首先启动，并且正在运行的任务短暂重叠）（默认 stop-first）

```yaml
version: '3.4'
services:
  vote:
    image: dockersamples/examplevotingapp_vote:before
    depends_on:
      - redis
    deploy:
      replicas: 2
      update_config:
        parallelism: 2
        delay: 10s
        order: stop-first
```



### entrypoint

在 Dockerfile 中有一个指令叫做 ENTRYPOINT 指令，在 docker-compose.yml 中可以定义接入点，覆盖 Dockerfile 中的定义：

```jsx
entrypoint: /code/entrypoint.sh
```

格式和 Docker 类似，不过还可以写成这样：

```ruby
entrypoint:
    - php
    - -d
    - zend_extension=/usr/local/lib/php/extensions/no-debug-non-zts-20100525/xdebug.so
    - -d
    - memory_limit=-1
    - vendor/bin/phpunit
```

### env_file

从文件中添加环境变量。可以是单个值或是列表
如果已经用 docker-compose -f FILE 指定了 Compose 文件，那么 env_file 路径值为相对于该文件所在的目录

但 environment 环境中的设置的变量会会覆盖这些值，无论这些值未定义还是为 None

```css
env_file: .env
```

或者根据 docker-compose.yml 设置多个：

```jsx
env_file:
  - ./common.env
  - ./apps/web.env
  - /opt/secrets.env
```

环境配置文件 `env_file` 中的声明每行都是以 `VAR=VAL` 格式，其中以 `#` 开头的被解析为注释而被忽略。

注意环境变量配置列表的顺序*,例如下面例子

docker_compose.yml

```yaml
services:
  some-service:
    env_file:
      - a.env
      - b.env
```

a.env 文件

```
# a.env
VAR=1
```

b.env文件

```
# b.env
VAR=3
```

对于在文件a.env 中指定的相同变量但在文件 b.env 中分配了不同的值，如果 b.env 像下面列在 a.env 之后，则刚在 a.env 设置的值被 b.env 相同变量的值覆盖，此时 $VAR 值为3。此外，这里所说的环境变量是对宿主机的 Compose 而言的，如果在配置文件中有 build 操作，这些变量并不会进入构建过程中，如果要在构建中使用变量还是首选 arg 标签

### environment

与上面的 env_file 标签完全不同，反而和 arg 有几分类似，这个标签的作用是设置镜像变量，它可以保存变量到镜像里面，也就是说启动的容器也会包含这些变量设置，这是与 arg 最大的不同。
 一般 arg 标签的变量仅用在构建过程中。而 environment 和 Dockerfile 中的 ENV 指令一样会把变量一直保存在镜像、容器中，类似 docker run -e 的效果。

```bash
environment:
  RACK_ENV: development
  SHOW: 'true'
  SESSION_SECRET:
或
environment:
  - RACK_ENV=development
  - SHOW=true
  - SESSION_SECRET
```

### expose

这个标签与Dockerfile中的EXPOSE指令一样，用于指定暴露的端口，但是只是作为一种参考，实际上docker-compose.yml的端口映射还得ports这样的标签。

```bash
expose:
 - "3000"
 - "8000"
```

### external_links

在使用Docker过程中，我们会有许多单独使用docker run启动的容器，为了使Compose能够连接这些不在docker-compose.yml中定义的容器，我们需要一个特殊的标签，就是external_links，它可以让Compose项目里面的容器连接到那些项目配置外部的容器（前提是外部容器中必须至少有一个容器是连接到与项目内的服务的同一个网络里面）。
 格式如下：

```css
external_links:
 - redis_1
 - project_db_1:mysql
 - project_db_1:postgresql
```

### extra_hosts

添加主机名的标签，就是往/etc/hosts文件中添加一些记录，与Docker client的--add-host类似：

```bash
extra_hosts:
 - "somehost:162.242.195.82"
 - "otherhost:50.31.209.229"
```

启动之后查看容器内部hosts：

```css
162.242.195.82  somehost
50.31.209.229   otherhost
```

### healthcheck

用于检查测试服务使用的容器是否正常

```yaml
healthcheck:
  test: ["CMD", "curl", "-f", "http://localhost"]
  interval: 1m30s
  timeout: 10s
  retries: 3
  start_period: 40s
```

interval，timeout 以及 start_period 都定为持续时间

test 必须是字符串或列表，如果它是一个列表，第一项必须是 NONE，CMD 或 CMD-SHELL ；如果它是一个字符串，则相当于指定CMD-SHELL 后跟该字符串。

```
# Hit the local web app
test: ["CMD", "curl", "-f", "http://localhost"]

# As above, but wrapped in /bin/sh. Both forms below are equivalent.
test: ["CMD-SHELL", "curl -f http://localhost || exit 1"]
test: curl -f https://localhost || exit 1
```

如果需要禁用镜像的所有检查项目，可以使用 disable:true,相当于 test:["NONE"]

```
healthcheck:
  disable: true
```

### image

从指定的镜像中启动容器，可以是存储仓库、标签以及镜像 ID.如果镜像不存在，Compose 会自动拉去镜像。

```yaml
image: redis
image: ubuntu:14.04
image: tutum/influxdb
image: example-registry.com:4000/postgresql
image: a4bc65fd
```

### labels

向容器添加元数据，和Dockerfile的LABEL指令一个意思，格式如下：

```csharp
labels:
  com.example.description: "Accounting webapp"
  com.example.department: "Finance"
  com.example.label-with-empty-value: ""
labels:
  - "com.example.description=Accounting webapp"
  - "com.example.department=Finance"
  - "com.example.label-with-empty-value"
```

### links

还记得上面的depends_on吧，那个标签解决的是启动顺序问题，这个标签解决的是容器连接问题，与Docker client的--link一样效果，会连接到其它服务中的容器。格式如下：

```css
links:
 - db
 - db:database
 - redis
```

使用的别名将会自动在服务容器中的/etc/hosts里创建。例如：

```css
172.12.2.186  db
172.12.2.186  database
172.12.2.187  redis
```

相应的环境变量也将被创建。

### logging

这个标签用于配置日志服务。格式如下：

```bash
logging:
  driver: syslog
  options:
    syslog-address: "tcp://192.168.0.42:123"
```

默认的driver是json-file。只有json-file和journald可以通过docker-compose logs显示日志，其他方式有其他日志查看方式，但目前Compose不支持。对于可选值可以使用options指定。
有关更多这方面的信息可以阅读官方文档： [https://docs.docker.com/engine/admin/logging/overview/](https://link.jianshu.com?t=https://docs.docker.com/engine/admin/logging/overview/)

### pid

```bash
pid: "host"
```

将PID模式设置为主机PID模式，跟主机系统共享进程命名空间。容器使用这个标签将能够访问和操纵其他容器和宿主机的名称空间。

### ports

映射端口的标签。使用HOST:CONTAINER格式或者只是指定容器的端口，宿主机会随机映射端口。

```css
ports:
 - "3000"
 - "8000:8000"
 - "49100:22"
 - "127.0.0.1:8001:8001"
```

> 注意：当使用HOST:CONTAINER格式来映射端口时，如果你使用的容器端口小于60你可能会得到错误得结果，因为YAML将会解析xx:yy这种数字格式为60进制。所以建议采用字符串格式。

### security_opt

为每个容器覆盖默认的标签。简单说来就是管理全部服务的标签。比如设置全部服务的user标签值为USER。

```css
security_opt:
  - label:user:USER
  - label:role:ROLE
```

### stop_signal

设置另一个信号来停止容器。在默认情况下使用的是SIGTERM停止容器。设置另一个信号可以使用stop_signal标签。

```undefined
stop_signal: SIGUSR1
```

### volumes

挂载一个目录或者一个已存在的数据卷容器，可以直接使用 [HOST:CONTAINER] 这样的格式，或者使用 [HOST:CONTAINER:ro] 这样的格式，后者对于容器来说，数据卷是只读的，这样可以有效保护宿主机的文件系统。

Compose的数据卷指定路径可以是相对路径，使用 . 或者 .. 来指定相对目录。数据卷的格式可以是下面多种形式：

```jsx
volumes:
  // 只是指定一个路径，Docker 会自动在创建一个数据卷（这个路径是容器内部的）。
  - /var/lib/mysql

  // 使用绝对路径挂载数据卷
  - /opt/data:/var/lib/mysql

  // 以 Compose 配置文件为中心的相对路径作为数据卷挂载到容器。
  - ./cache:/tmp/cache

  // 使用用户的相对路径（~/ 表示的目录是 /home/<用户目录>/ 或者 /root/）。
  - ~/configs:/etc/configs/:ro

  // 已经存在的命名的数据卷。
  - datavolume:/var/lib/mysql
```

如果你不使用宿主机的路径，你可以指定一个volume_driver。

```undefined
volume_driver: mydriver
```

### network_mode

网络模式，与Docker client的--net参数类似，只是相对多了一个service:[service name] 的格式。例如：

```bash
network_mode: "bridge"
network_mode: "host"
network_mode: "none"
network_mode: "service:[service name]"
network_mode: "container:[container name/id]"
```

可以指定使用服务或者容器的网络。

### networks

加入指定网络，格式如下：

```undefined
services:
  some-service:
    networks:
     - some-network
     - other-network
```

关于这个标签还有一个特别的子标签aliases，这是一个用来设置服务别名的标签，例如：

```undefined
services:
  some-service:
    networks:
      some-network:
        aliases:
         - alias1
         - alias3
      other-network:
        aliases:
         - alias2
```

相同的服务可以在不同的网络有不同的别名。

### 其它

还有这些标签：cpu_shares, cpu_quota, cpuset, domainname, hostname, ipc, mac_address, mem_limit, memswap_limit, privileged, read_only, restart, shm_size, stdin_open, tty, user, working_dir
 上面这些都是一个单值的标签，类似于使用docker run的效果。

