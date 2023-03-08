# SSM框架 - SpringBoot

## 简介

`SpringBoot` 是由 `Pivotal` 团队提供的全新框架，其设计目的是用来**简化** `Spring` 应用的**初始搭建**以及**开发过程**。

使用了 `Spring` 框架后已经简化了我们的开发。而 `SpringBoot` 又是对 `Spring` 开发进行简化的，可想而知 `SpringBoot` 使用的简单及广泛性。

### 回顾 SpringMVC 开发过程

1. **创建工程，并在 `pom.xml` 配置文件中配置所依赖的坐标**

<img src="/_images/project/study/ssm/springboot/SpringMVC坐标.png" alt="SpringMVC坐标" style="zoom:50%;" />

2. **编写 `web3.0` 的配置类**

   作为 `web` 程序，`web3.0` 的配置类不能缺少，而这个配置类还是比较麻烦的，代码如下

<img src="/_images/project/study/ssm/springboot/Web配置.png" alt="Web配置" style="zoom:50%;" />

3. **编写 `SpringMVC` 的配置类**

<img src="/_images/project/study/ssm/springboot/SpringMVC配置类.png" alt="SpringMVC配置类" style="zoom:50%;" />

​    做到这只是将工程的架子搭起来。要想被外界访问，最起码还需要提供一个 `Controller` 类，在该类中提供一个方法。

4. **编写 `Controller` 类**

<img src="/_images/project/study/ssm/springboot/Controller类.png" alt="Controller类" style="zoom:50%;" />

从上面的 `SpringMVC` 程序开发可以看到，前三步都是在搭建环境，而且这三步基本都是固定的。

`SpringBoot` 就是对这三步进行简化了。接下来通过一个入门案例来体现 `SpingBoot` 简化 `Spring` 开发。

###  SpringBoot快速入门

#### 开发步骤

`SpringBoot` 开发起来特别简单，分为如下几步：

* 创建新模块，选择Spring初始化，并配置模块相关基础信息
* 选择当前模块需要使用的技术集
* 开发控制器类
* 运行自动生成的Application类

#### 1.创建新模块

* 点击 `+` 选择 `New Module` 创建新模块
* 选择 `Spring Initializr` ，用来创建 `SpringBoot` 工程
    * 以前选择的是 `Maven` ，选择 `Spring Initializr` 来快速构建 `SpringBoot` 工程。而在 `Module SDK` 这一项选择我们安装的 `JDK` 版本。

<img src="/_images/project/study/ssm/springboot/SpringBoot创建新模块.png" alt="SpringBoot创建新模块" style="zoom:60%;" />

* 对 `SpringBoot` 工程进行相关的设置

  <img src="/_images/project/study/ssm/springboot/SpringBoot工程设置.png" alt="SpringBoot工程设置" style="zoom:67%;" />

* 选中 `Web`，然后勾选 `Spring Web`

  由于我们需要开发一个 `web` 程序，使用到了 `SpringMVC` 技术，所以按照下图红框进行勾选

<img src="/_images/project/study/ssm/springboot/web设置勾选.png" alt="web设置勾选" style="zoom:60%;" />

* 下图界面不需要任何修改，直接点击 `Finish` 完成 `SpringBoot` 工程的构建

<img src="/_images/project/study/ssm/springboot/完成SpringBoot工程构建.png" alt="完成SpringBoot工程构建" style="zoom:70%;" />

经过以上步骤后就创建了如下结构的模块，它会帮我们自动生成一个 `Application` 类，而该类一会再启动服务器时会用到

<img src="/_images/project/study/ssm/springboot/生成Application.png" alt="生成Application" style="zoom:80%;" />

#### 2.创建 Controller

在  `com.itheima.controller` 包下创建 `BookController` ，代码如下：

```java
@RestController
@RequestMapping("/books")
public class BookController {

    @GetMapping("/{id}")
    public String getById(@PathVariable Integer id){
        System.out.println("id **> "+id);
        return "hello , spring boot!";
    }
}
```

#### 3.启动服务器

只需运行项目 `com.itheima` 包下的 `Application` 类，就可以在控制台看出如下信息

![](/_images/project/study/ssm/springboot/启动服务器.png)

#### 4.进行测试

使用 `Postman` 工具来测试程序

![](/_images/project/study/ssm/springboot/Postman测试.png)

通过上面的入门案例我们可以看到使用 `SpringBoot` 进行开发，使整个开发变得很简单，那它是如何做到的呢？

要研究这个问题，需要看看 `Application` 类和 `pom.xml` 都书写了什么。

先看看 `Applicaion` 类，该类内容如下：

```java
@SpringBootApplication
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
}
```

这个类中的东西很简单，就在类上添加了一个 `@SpringBootApplication` 注解，而在主方法中就一行代码。我们在启动服务器时就是执行的该类中的主方法。

再看看 `pom.xml` 配置文件中的内容

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    
    <!--指定了一个父工程，父工程中的东西在该工程中可以继承过来使用-->
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.5.0</version>
    </parent>
    <groupId>com.itheima</groupId>
    <artifactId>springboot_01_quickstart</artifactId>
    <version>0.0.1-SNAPSHOT</version>

    <!--JDK 的版本-->
    <properties>
        <java.version>8</java.version>
    </properties>
    
    <dependencies>
        <!--该依赖就是我们在创建 SpringBoot 工程勾选的那个 Spring Web 产生的-->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
		<!--这个是单元测试的依赖，我们现在没有进行单元测试，所以这个依赖现在可以没有-->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-test</artifactId>
            <scope>test</scope>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <!--这个插件是在打包时需要的，而这里暂时还没有用到-->
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>
</project>
```

代码之所以能简化，就是因为指定的父工程和 `Spring Web` 依赖实现的。

### 对比

做完 `SpringBoot` 的入门案例后，接下来对比一下 `Spring` 程序和 `SpringBoot` 程序。如下图

<img src="/_images/project/study/ssm/springboot/Spring和SpringBoot对比.png" alt="Spring和SpringBoot对比" style="zoom:60%;" />

## SpringBoot工程快速启动

### 问题

后端可以将 `SpringBoot` 工程打成 `jar` 包，该 `jar` 包运行不依赖于 `Tomcat` 和 `Idea` 这些工具也可以正常运行，只需替换实际的 `Mysql` 数据库即可。如下图

<img src="/_images/project/study/ssm/springboot/前后端项目.png" alt="前后端项目" style="zoom:50%;" />

### 打包

在构建 `SpringBoot` 工程时已经在 `pom.xml` 中配置了如下插件

```xml
<plugin>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-maven-plugin</artifactId>
</plugin>
```

只需要使用 `Maven` 的 `package` 指令打包就会在 `target` 目录下生成对应的 `Jar` 包。

### 启动

进入 `jar` 包所在位置，在 `命令提示符` 中输入如下命令

```shell
jar -jar springboot_01_quickstart-0.0.1-SNAPSHOT.jar
```

执行上述命令就可以看到 `SpringBoot` 运行的日志信息

<img src="/_images/project/study/ssm/springboot/命令行运行结果.png" alt="命令行运行结果" style="zoom:60%;" />

## SpringBoot概述

`SpringBoot` 是由Pivotal团队提供的全新框架，其设计目的是用来**简化**Spring应用的**初始搭建**以及**开发过程**。

`SpringBoot` 主要作用：简化 `Spring` 的搭建过程和开发过程。

原始 `Spring` 环境搭建和开发存在以下问题：

* 配置繁琐
* 依赖设置繁琐

`SpringBoot` 程序优点恰巧就是针对 `Spring` 的缺点

* 自动配置：用来解决 `Spring` 程序配置繁琐的问题
* **起步依赖**： 用来解决 `Spring` 程序依赖设置繁琐的问题
* 辅助功能（内置服务器,...）：使用 `SpringBoot` 内置的服务器。

### 起步依赖

使用 `Spring Initializr`  方式创建的 `Maven` 工程的的 `pom.xml` 配置文件中自动生成了很多包含 `starter` 的依赖，如下图

<img src="/_images/project/study/ssm/springboot/起步依赖.png" alt="起步依赖" style="zoom:70%;" />

这些依赖就是**启动依赖**。

#### 探索父工程

从上面的文件中可以看到指定了一个父工程，进入到父工程，发现父工程中又指定了一个父工程，如下图所示

<img src="/_images/project/study/ssm/springboot/父工程.png" alt="父工程" style="zoom:80%;" />

再进入到该父工程中，在该工程中我们可以看到配置内容结构如下图所示

<img src="/_images/project/study/ssm/springboot/父工程配置内容.png" alt="父工程配置内容" style="zoom:80%;" />

* `properties` 标签中定义了各个技术软件依赖的版本，避免了在使用不同软件技术时考虑版本的兼容问题。
* `dependencyManagement` 标签是进行依赖版本锁定。
* `build` 标签中也对插件的版本进行了锁定。

看完了父工程中 `pom.xml` 的配置后不难理解我们工程的的依赖为什么都没有配置 `version`。

#### 探索依赖

在创建的工程中的 `pom.xml` 中配置了如下依赖

```
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>
```
进入到该依赖，查看 `pom.xml` 的依赖会发现它引入了 `spring-web` 、`spring-webmvc` 和 `spring-boot-starter-tomcat` 等依赖。

**结论：以后需要使用技术，只需要引入该技术对应的起步依赖即可**

#### 小结

**starter**

* `SpringBoot` 中常见项目名称，定义了当前项目使用的所有项目坐标，以达到减少依赖配置的目的

**parent**

* 所有 `SpringBoot` 项目要继承的项目，定义了若干个坐标版本号（依赖管理，而非依赖），以达到减少依赖冲突的目的
* 不同版本之间坐标版本号存在差异

**实际开发**

* 使用任意坐标时，仅书写GAV中的G和A，V由SpringBoot提供
  * G：groupid
  * A：artifactId
  * V：version

### 程序启动

每一个 `SpringBoot` 程序时都包含一个类似于下面的类，称作引导类

```java
@SpringBootApplication
public class Springboot01QuickstartApplication {
    
    public static void main(String[] args) {
        SpringApplication.run(Springboot01QuickstartApplication.class, args);
    }
}
```

####  切换web服务器

启动工程默认使用的是 `tomcat` 服务器，通过 `exclusion` 标签不使用 `tomcat` 而使用 `jetty` 服务器：

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
    <exclusions>
        <exclusion>
            <artifactId>spring-boot-starter-tomcat</artifactId>
            <groupId>org.springframework.boot</groupId>
        </exclusion>
    </exclusions>
</dependency>
```

引入 `jetty` 的起步依赖

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-jetty</artifactId>
</dependency>
```

运行引导类，在日志信息中就可以看到使用的是 `jetty` 服务器

![](/_images/project/study/ssm/springboot/jetty服务器.png)

**小结：**

通过切换服务器，我们不难发现在使用 `SpringBoot` 换技术时只需要导入该技术的起步依赖即可。

## 配置文件

### 配置文件格式

`SpringBoot` 提供了多种属性配置方式

* `application.properties`
* `application.yml`
* `application.yaml`

**注意：`SpringBoot` 程序的配置文件名必须是 `application` ，只是后缀名不同而已。**

### 三种配合文件的优先级

三种配置文件的优先级是：

**`application.properties`  >  `application.yml`   >  `application.yaml`**

**注意：**

* `SpringBoot` 核心配置文件名为 `application`
* `SpringBoot` 内置属性过多，且所有属性集中在一起修改，在使用时，通过提示键+关键字修改属性


### yaml格式

**YAML（YAML Ain't Markup Language），一种数据序列化格式。

不同书写格式的对比：

`xml` 格式：

```xml
<enterprise>
    <name>itcast</name>
    <age>16</age>
    <tel>4006184000</tel>
</enterprise>
```

`properties` 格式

```properties
enterprise.name=itcast
enterprise.age=16
enterprise.tel=4006184000
```

`yaml` 格式

```yaml
enterprise:
    name: itcast
    age: 16
    tel: 4006184000
```

**yml优点：**

* 容易阅读
* 容易与脚本语言交互
* 以数据为核心，重数据轻格式
    * `yaml` 更注重数据，而 `xml` 更注重格式

**YAML 文件扩展名：**

* `.yml` (主流)
* `.yaml`

上面两种后缀名都可以，以后使用更多的还是 `yml` 的。

####  语法规则

* 大小写敏感
* 属性层级关系使用多行描述，每行结尾使用冒号结束
* 使用缩进表示层级关系，同层级左侧对齐，只允许使用空格（不允许使用Tab键）
    * 空格的个数并不重要，只要保证同层级的左侧对齐即可。
* 属性值前面添加空格（属性名与属性值之间使用冒号+空格作为分隔）
* \# 表示注释

**核心规则：数据前面要加空格与冒号隔开**

数组数据在数据书写位置的下方使用减号作为数据开始符号，每行书写一个数据，减号与数据间空格分隔，例如

```yaml
enterprise:
  name: itcast
  age: 16
  tel: 4006184000
  subject:
    - Java
    - 前端
    - 大数据
```

### yaml配置文件数据读取

#### 环境准备

新创建一个名为 `springboot_03_read_data` 的 `SpringBoot` 工程，目录结构如下

<img src="/_images/project/study/ssm/springboot/springboot_03_read_data环境.png" alt="springboot_03_read_data环境" style="zoom:80%;" />

在 `com.itheima.controller` 包写创建名为 `BookController` 的控制器，内容如下

```java
@RestController
@RequestMapping("/books")
public class BookController {

    @GetMapping("/{id}")
    public String getById(@PathVariable Integer id){
        System.out.println("id **> "+id);
        return "hello , spring boot!";
    }
}
```

在 `com.itheima.domain` 包下创建一个名为 `Enterprise` 的实体类等会用来封装数据，内容如下

```java
public class Enterprise {
    private String name;
    private int age;
    private String tel;
    private String[] subject;
    
    //setter and getter
    
    //toString
}
```

在 `resources` 下创建一个名为 `application.yml` 的配置文件，里面配置了不同的数据，内容如下

```yaml
lesson: SpringBoot

server:
  port: 80

enterprise:
  name: itcast
  age: 16
  tel: 4006184000
  subject:
    - Java
    - 前端
    - 大数据
```

#### 读取配置数据

#####  使用 @Value注解

使用 `@Value("表达式")` 注解可以从配合文件中读取数据，注解中用于读取属性名引用方式是：`${一级属性名.二级属性名……}`

```java
@RestController
@RequestMapping("/books")
public class BookController {
    
    @Value("${lesson}")
    private String lesson;
    @Value("${server.port}")
    private Integer port;
    @Value("${enterprise.subject[0]}")
    private String subject_00;

    @GetMapping("/{id}")
    public String getById(@PathVariable Integer id){
        System.out.println(lesson);
        System.out.println(port);
        System.out.println(subject_00);
        return "hello , spring boot!";
    }
}
```

##### Environment对象

使用 `@Autowired` 注解注入 `Environment` 对象的方式读取数据。

```java
@RestController
@RequestMapping("/books")
public class BookController {
    
    @Autowired
    private Environment env;
    
    @GetMapping("/{id}")
    public String getById(@PathVariable Integer id){
        System.out.println(env.getProperty("lesson"));
        System.out.println(env.getProperty("enterprise.name"));
        System.out.println(env.getProperty("enterprise.subject[0]"));
        return "hello , spring boot!";
    }
}
```

> **注意：这种方式，框架内容大量数据，而在开发中我们很少使用。**

#####  自定义对象

`SpringBoot` 还提供了将配置文件中的数据封装到我们自定义的实体类对象中的方式。具体操作如下：

* 将实体类 `bean` 的创建交给 `Spring` 管理。
    * 在类上添加 `@Component` 注解

* 使用 `@ConfigurationProperties` 注解表示加载配置文件
    * 在该注解中也可以使用 `prefix` 属性指定只加载指定前缀的数据

* 在 `BookController` 中进行注入

**具体代码如下：**

`Enterprise` 实体类内容如下：

```java
@Component
@ConfigurationProperties(prefix = "enterprise")
public class Enterprise {
    private String name;
    private int age;
    private String tel;
    private String[] subject;

    .....
}
```

`BookController` 内容如下：

```java
@RestController
@RequestMapping("/books")
public class BookController {
    
    @Autowired
    private Enterprise enterprise;

    @GetMapping("/{id}")
    public String getById(@PathVariable Integer id){
        System.out.println(enterprise.getName());
        System.out.println(enterprise.getAge());
        System.out.println(enterprise.getSubject());
        System.out.println(enterprise.getTel());
        System.out.println(enterprise.getSubject()[0]);
        return "hello , spring boot!";
    }
}
```

### 多环境配置

以后在工作中，对于开发环境、测试环境、生产环境的配置肯定都不相同，例如不同环境使用的mysql数据库地址肯定不同：

<img src="/_images/project/study/ssm/springboot/多环境配置.png" alt="多环境配置" style="zoom:60%;" />

来回的修改配置会很麻烦，而 `SpringBoot` 给开发者提供了多环境的快捷配置，需要切换环境时只需要改一个配置即可。

#### yaml文件

`application.yml` 配置文件内容如下，通过spring.profiles.active确定当前环境使用的配置信息：

```yaml
#设置启用的环境
spring:
  profiles:
    active: dev

---
#开发
spring:
  profiles: dev
server:
  port: 80
---
#生产
spring:
  profiles: pro
server:
  port: 81
---
#测试
spring:
  profiles: test
server:
  port: 82
---
```

**注意：**

在上面配置中给不同配置起名字的 `spring.profiles` 配置项已经过时，最新用来起名字的配置项是 

```yaml
#开发
spring:
  config:
    activate:
      on-profile: dev
```

#### properties文件

`properties` 类型的配置文件配置多环境需要定义不同的配置文件

* `application-dev.properties`  是开发环境，配置端口号为 `80`
* `application-test.properties` 是测试环境，配置端口号为 `81`
* `application-pro.properties`  是生产环境，配置端口号为 `82`

`SpringBoot` 只会默认加载名为 `application.properties` 的配置文件，所以需要在 `application.properties` 配置文件中设置启用哪个配置文件，配置如下:

```properties
spring.profiles.active=pro
```

####  命令行启动参数设置

通过 命令行方式 在运行 `jar` 时设置开启指定的环境的方式，如下

```shell
java –jar xxx.jar –-server.port=88 –-spring.profiles.active=test
```

命令行配置的优先级参见 :

```
https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-external-config
```

进入上面网站后会看到如下页面

![](/_images/project/study/ssm/springboot/优先级.png)

如果使用了多种方式配合同一个配置项，优先级高的生效。

###  配置文件分类

有这样的场景，开发完毕后需要测试人员进行测试，由于测试环境和开发环境的很多配置都不相同，所以测试人员在运行我们的工程时需要临时修改很多配置，如下

```shell
java –jar springboot.jar –-spring.profiles.active=test --server.port=85 --server.servlet.context-path=/heima --server.tomcat.connection-timeout=-1 …… …… …… …… ……
```

针对这种情况，`SpringBoot` 定义了配置文件不同的放置的位置；而放在不同位置的优先级时不同的。

`SpringBoot` 中4级配置文件放置位置：

* 1级：classpath：application.yml  
* 2级：classpath：config/application.yml
* 3级：file ：application.yml
* 4级：file ：config/application.yml 

> **说明：**级别越高优先级越高

## SpringBoot整合junit

回顾 `Spring` 整合 `junit`

```java
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = SpringConfig.class)
public class UserServiceTest {
    
    @Autowired
    private BookService bookService;
    
    @Test
    public void testSave(){
        bookService.save();
    }
}
```

使用 `@RunWith` 注解指定运行器，使用 `@ContextConfiguration` 注解来指定配置类或者配置文件。

而 `SpringBoot` 整合 `junit` 特别简单，分为以下三步完成

* 在测试类上添加 `SpringBootTest` 注解
* 使用 `@Autowired` 注入要测试的资源
* 定义测试方法进行测试


**注意：**这里的引导类所在包必须是测试类所在包及其子包。

例如：

* 引导类所在包是 `com.itheima`
* 测试类所在包是 `com.itheima`

如果不满足这个要求的话，就需要在使用 `@SpringBootTest` 注解时，使用 `classes` 属性指定引导类的字节码对象。如 `@SpringBootTest(classes = Springboot07TestApplication.class)`

## SpringBoot整合mybatis

###  回顾Spring整合Mybatis

`Spring` 整合 `Mybatis` 需要定义很多配置类

* `SpringConfig` 配置类
  * 导入 `JdbcConfig` 配置类
  * 导入 `MybatisConfig` 配置类
*  `JdbcConfig` 配置类
  * 定义数据源（加载properties配置项：driver、url、username、password）
* `MybatisConfig` 配置类
  * 定义 `SqlSessionFactoryBean`
  * 定义映射配置

###  SpringBoot整合mybatis

1. 创建模块

* 创建新模块，选择 `Spring Initializr`，并配置模块相关基础信息

<img src="/_images/project/study/ssm/springboot/SpringBoot整合mybatis.png" alt="SpringBoot整合mybatis" style="zoom:80%;" />

* 选择当前模块需要使用的技术集（MyBatis、MySQL）

  <img src="/_images/project/study/ssm/springboot/选择mybatis_mysql.png" alt="选择mybatis_mysql" style="zoom:80%;" />

2. 定义实体类

在 `com.itheima.domain` 包下定义实体类 `Book`，内容如下

```java
public class Book {
    private Integer id;
    private String name;
    private String type;
    private String description;
    
    //setter and  getter
    
    //toString
}
```

3. 定义dao接口

在 `com.itheima.dao` 包下定义 `BookDao` 接口，内容如下

```java
@Mapper
public interface BookDao {
    @Select("select * from tbl_book where id = #{id}")
    public Book getById(Integer id);
}
```

4. 定义测试类

在 `test/java` 下定义包 `com.itheima` ，在该包下测试类，内容如下

```java
@SpringBootTest
class Springboot08MybatisApplicationTests {

	@Autowired
	private BookDao bookDao;

	@Test
	void testGetById() {
		Book book = bookDao.getById(1);
		System.out.println(book);
	}
}
```

5. 编写配置

在 `application.yml` 配置文件中配置如下内容

```yml
spring:
  datasource:
    driver-class-name: com.mysql.jdbc.Driver
    url: jdbc:mysql://localhost:3306/ssm_db
    username: root
    password: root
```

6. 测试

运行测试方法即可。

7. 使用Druid数据源

现在我们并没有指定数据源，`SpringBoot` 有默认的数据源，我们也可以指定使用 `Druid` 数据源，按照以下步骤实现

* 导入 `Druid` 依赖

  ```xml
  <dependency>
      <groupId>com.alibaba</groupId>
      <artifactId>druid</artifactId>
      <version>1.1.16</version>
  </dependency>
  ```

* 在 `application.yml` 配置文件配置

  可以通过 `spring.datasource.type` 来配置使用什么数据源。配置文件内容可以改进为

  ```yaml
  spring:
    datasource:
      driver-class-name: com.mysql.cj.jdbc.Driver
      url: jdbc:mysql://localhost:3306/ssm_db?serverTimezone=UTC
      username: root
      password: root
      type: com.alibaba.druid.pool.DruidDataSource
  ```