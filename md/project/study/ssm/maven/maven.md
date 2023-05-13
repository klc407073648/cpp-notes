# SSM - Maven高级

[[toc]]

# 分模块开发

## 分模块开发设计

(1)按照功能拆分

现在的项目都是在一个模块中，比如前面的SSM整合开发。虽然这样做功能也都实现了，但是也存在了一些问题。以银行的项目为例：

* 网络没有那么发达的时候，我们需要到银行柜台或者取款机进行业务操作
* 随着互联网的发展,电脑普及后，我们就可以在网页上登录银行网站使用U盾进行业务操作
* 随着智能手机的普及，我们只需要用手机登录APP就可以进行业务操作

上面三个场景出现的时间是不相同的，如果非要把三个场景的模块代码放入到一个项目，那么当其中某一个模块代码出现问题，就会导致整个项目无法正常启动，从而导致银行的多个业务都无法正常班理。

所以会**按照功能**将项目进行拆分。

(2)按照模块拆分

比如，电商的项目中，有订单和商品两个模块，订单中需要包含商品的详细信息，所以需要商品的模型类，商品模块也会用到商品的模型类。

* 如果两个模块中都写模型类，就会出现重复代码，后期的维护成本就比较高。
    * 能不能将它们公共的部分抽取成一个独立的模块，其他模块要想使用可以像添加第三方jar包依赖一样来使用抽取的模块。

这样就解决了代码重复的问题,这种拆分方式就是**按照模块**拆分。

经过两个案例的分析，我们就知道:

* 将原始模块按照功能拆分成若干个子模块，方便模块间的相互调用，接口共享。

可以将domain层进行拆分，其他的层也可以拆成一个个对立的模块，如:

![1630768869208](/_images/project/study/ssm/maven/按模块拆分.png)

## 分模块开发实现

### 抽取domain层

1. 步骤1:创建新模块
    * maven_03_pojo的jar项目
2. 步骤2:项目中创建domain包
3. 步骤3:删除原项目中的domain包
4. 步骤4:建立依赖关系
    * 在maven_02_ssm项目的pom.xml添加maven_03_pojo的依赖
5. 步骤5:将项目安装本地仓库
    * 将需要被依赖的项目`maven_03_pojo`，使用maven的install命令，把其安装到Maven的本地仓库中。
6. 步骤6:编译`maven_02_ssm`项目
    * 执行`maven_02_ssm`的compile的命令后，就已经能够成功编译。


### 总结

对于项目的拆分，大致会有如下几个步骤:

(1) 创建Maven模块

(2) 书写模块代码

分模块开发需要先针对模块功能进行设计，再进行编码。不会先将工程开发完毕，然后进行拆分。拆分方式可以按照功能拆也可以按照模块拆。

(3)通过maven指令安装模块到本地仓库(install 指令)

团队内部开发需要发布模块功能到团队内部可共享的仓库中(私服)。

# 依赖管理

分模块开发章节已经能把项目拆分成一个个独立的模块，当在其他项目中想要使用独立出来的这些模块，只需要在其pom.xml使用<dependency>标签来进行jar包的引入即可。

依赖管理主要包括以下三个部分:

* 依赖传递
* 可选依赖
* 排除依赖

概念：依赖指当前项目运行所需的jar，一个项目可以设置多个依赖。

格式为:

```xml
<!--设置当前项目所依赖的所有jar-->
<dependencies>
    <!--设置具体的依赖-->
    <dependency>
        <!--依赖所属群组id-->
        <groupId>org.springframework</groupId>
        <!--依赖所属项目id-->
        <artifactId>spring-webmvc</artifactId>
        <!--依赖版本号-->
        <version>5.2.10.RELEASE</version>
    </dependency>
</dependencies>
```

## 依赖传递与冲突问题

依赖是具有传递性的:

![](/_images/project/study/ssm/maven/依赖传递.png)

**说明:**A代表自己的项目；B,C,D,E,F,G代表的是项目所依赖的jar包；D1和D2 E1和E2代表是相同jar包的不同版本

(1) A依赖了B和C,B和C有分别依赖了其他jar包，所以在A项目中就可以使用上面所有jar包，这就是所说的依赖传递

(2) 依赖传递有直接依赖和间接依赖

* 相对于A来说，A直接依赖B和C,间接依赖了D1,E1,G，F,D2和E2
* 相对于B来说，B直接依赖了D1和E1,间接依赖了G
* 直接依赖和间接依赖是一个相对的概念

(3)因为有依赖传递的存在，就会导致jar包在依赖的过程中出现冲突问题，具体什么是冲突?Maven是如何解决冲突的?

这里所说的**依赖冲突**是指项目依赖的某一个jar包，有多个不同的版本，因而造成类包版本冲突。

情况一: 在`maven_02_ssm`的pom.xml中添加两个不同版本的Junit依赖:

* 特殊优先：当同级配置了相同资源的不同版本，后配置的覆盖先配置的。

情况二: 路径优先：当依赖中出现相同的资源时，**层级越深，优先级越低，层级越浅，优先级越高**

* A通过B间接依赖到E1
* A通过C间接依赖到E2
* A就会间接依赖到E1和E2,Maven会按照层级来选择，E1是2度，E2是3度，所以最终会选择E1

情况三: 声明优先：当资源在相同层级被依赖时，配置顺序靠前的覆盖配置顺序靠后的

* A通过B间接依赖到D1
* A通过C间接依赖到D2
* D1和D2都是两度，这个时候就不能按照层级来选择，需要按照声明来，谁先声明用谁，也就是说B在C之前声明，这个时候使用的是D1，反之则为D2

但是对应上面这些结果，不需要刻意去记。因为不管Maven怎么选，最终的结果都会在Maven的`Dependencies`面板中展示出来，展示的是哪个版本，也就是说它选择的就是哪个版本，如:

![](/_images/project/study/ssm/maven/Dependencies面板.png)

如果想更全面的查看Maven中各个坐标的依赖关系，可以点击Maven面板中的`show Dependencies`

![](/_images/project/study/ssm/maven/show_Dependencies.png)

在这个视图中就能很明显的展示出jar包之间的相互依赖关系。

## 可选依赖和排除依赖

依赖传递介绍完以后，我们来思考一个问题，

![](/_images/project/study/ssm/maven/依赖传递关系.png)

* maven_02_ssm 依赖了 maven_04_dao
* maven_04_dao 依赖了 maven_03_pojo
* 因为现在有依赖传递，所以maven_02_ssm能够使用到maven_03_pojo的内容
* 如果说现在不想让maven_02_ssm依赖到maven_03_pojo，有哪些解决方案?

### 方案一:可选依赖

* 可选依赖指对外隐藏当前所依赖的资源---不透明

在`maven_04_dao`的pom.xml,在引入`maven_03_pojo`的时候，添加`optional`

```xml
<dependency>
    <groupId>com.itheima</groupId>
    <artifactId>maven_03_pojo</artifactId>
    <version>1.0-SNAPSHOT</version>
    <!--可选依赖是隐藏当前工程所依赖的资源，隐藏后对应资源将不具有依赖传递-->
    <optional>true</optional>
</dependency>
```

此时BookServiceImpl就已经报错了,说明由于maven_04_dao将maven_03_pojo设置成可选依赖，导致maven_02_ssm无法引用到maven_03_pojo中的内容，导致Book类找不到。

### 方案二:排除依赖

* 排除依赖指主动断开依赖的资源，被排除的资源无需指定版本---不需要

前面我们已经通过可选依赖实现了阻断maven_03_pojo的依赖传递。

对于排除依赖，则指的是已经有依赖的事实，也就是说maven_02_ssm项目中已经通过依赖传递用到了maven_03_pojo，此时我们需要做的是将其进行排除，所以接下来需要修改maven_02_ssm的pom.xml

```xml
<dependency>
    <groupId>com.itheima</groupId>
    <artifactId>maven_04_dao</artifactId>
    <version>1.0-SNAPSHOT</version>
    <!--排除依赖是隐藏当前资源对应的依赖关系-->
    <exclusions>
        <exclusion>
            <groupId>com.itheima</groupId>
            <artifactId>maven_03_pojo</artifactId>
        </exclusion>
    </exclusions>
</dependency>
```

这样操作后，BookServiceImpl中的Book类一样也会报错。

可选依赖和排除依赖简单梳理：

* `A依赖B,B依赖C`,`C`通过依赖传递会被`A`使用到，现在要想办法让`A`不去依赖`C`
* 可选依赖是在B上设置`<optional>`,`A`不知道有`C`的存在，
* 排除依赖是在A上设置`<exclusions>`,`A`知道有`C`的存在，主动将其排除掉。

# 聚合和继承

## 聚合

![](/_images/project/study/ssm/maven/聚合.png)

* 分模块开发后，需要将这四个项目都安装到本地仓库，目前我们只能通过项目Maven面板的`install`来安装，并且需要安装四个，如果我们的项目足够多，那么一个个安装起来还是比较麻烦的
* 如果四个项目都已经安装成功，当ssm_pojo发生变化后，我们就得将ssm_pojo重新安装到maven仓库，但是为了确保我们对ssm_pojo的修改不会影响到其他项目模块，我们需要对所有的模块进行重新编译，那又需要将所有的模块再来一遍

项目少的话还好，但是如果项目多的话，一个个操作项目就容易出现漏掉或重复操作的问题，所以我们就想能不能抽取一个项目，把所有的项目管理起来，以后我们要想操作这些项目，只需要操作这一个项目，其他所有的项目都走一样的流程，这个不就很省事省力。

这就用到了接下来要讲解的**聚合**，

* 聚合:将多个模块组织成一个整体，同时进行项目构建的过程。
* 聚合工程：通常是一个不具有业务功能的"空"工程（有且仅有一个pom文件）
* 作用：使用聚合工程可以将多个工程编组，通过对聚合工程进行构建，实现对所包含的模块进行同步构建
  * 当工程中某个模块发生更新（变更）时，必须保障工程中与已更新模块关联的模块同步更新，此时可以使用聚合工程来解决批量模块同步构建的问题。

关于聚合具体的实现步骤为:

1. 步骤1:创建一个空的maven项目
2. 步骤2:将项目的打包方式改为pom

**说明:**项目的打包方式有三种，分别是

* jar:默认情况，说明该项目为java项目
* war:说明该项目为web项目
* pom:说明该项目为聚合或继承(后面会讲)项目

3. 步骤3:pom.xml添加所要管理的项目

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.itheima</groupId>
    <artifactId>maven_01_parent</artifactId>
    <version>1.0-RELEASE</version>
    <packaging>pom</packaging>
    
    <!--设置管理的模块名称-->
    <modules>
        <module>../maven_02_ssm</module>
        <module>../maven_03_pojo</module>
        <module>../maven_04_dao</module>
    </modules>
</project>
```

4. 步骤4:使用聚合统一管理项目

![](/_images/project/study/ssm/maven/使用聚合统一管理项目.png)

测试发现，当`maven_01_parent`的`compile`被点击后，所有被其管理的项目都会被执行编译操作。这就是聚合工程的作用。

**说明：**聚合工程管理的项目在进行运行的时候，会按照项目与项目之间的依赖关系来自动决定执行的顺序和配置的顺序无关。

## 继承

多模块开发存在另外一个问题：`重复配置`的问题

![](/_images/project/study/ssm/maven/重复配置问题.png)

* 全部重复：`spring-webmvc`、`spring-jdbc`在三个项目模块中都有出现
* 部分重复：`spring-test`只在ssm_crm和ssm_goods中出现，而在ssm_order中没有
* 使用的spring版本目前是`5.2.10.RELEASE`,假如后期要想升级spring版本，所有跟Spring相关jar包都得被修改，涉及到的项目越多，维护成本越高

面对上面的这些问题，需要用**继承**来解决

* 继承:描述的是两个工程间的关系，与java中的继承相似，子工程可以继承父工程中的配置信息，常见于依赖关系的继承。
* 作用：
  - 简化配置
  - 减少版本冲突

1. 步骤1:创建一个空的Maven项目并将其打包方式设置为pom

2. 步骤2:在子项目中设置其父工程

分别在`maven_02_ssm`,`maven_03_pojo`,`maven_04_dao`的pom.xml中添加其父项目为`maven_01_parent`

```xml
<!--配置当前工程继承自parent工程-->
<parent>
    <groupId>com.itheima</groupId>
    <artifactId>maven_01_parent</artifactId>
    <version>1.0-RELEASE</version>
    <!--设置父项目pom.xml位置路径-->
    <relativePath>../maven_01_parent/pom.xml</relativePath>
</parent>
```

3. 步骤3:优化子项目共有依赖导入问题
    * 将子项目共同使用的jar包都抽取出来，维护在父项目的pom.xml中
    * 删除子项目中已经被抽取到父项目的pom.xml中的jar包，如在`maven_02_ssm`的pom.xml中将已经出现在父项目的jar包删除掉
        * 删除完后，你会发现父项目中有依赖对应的jar包，子项目虽然已经将重复的依赖删除掉了，但是刷新的时候，子项目中所需要的jar包依然存在。

4. 步骤4:优化子项目依赖版本问题   TODO还要看一下代码实现

如果把所有用到的jar包都管理在父项目的pom.xml，看上去更简单些，但是这样就会导致有很多项目引入了过多自己不需要的jar包。如上面看到的这张图:

![](/_images/project/study/ssm/maven/引入不需要的jar.png)

如果把所有的依赖都放在了父工程中进行统一维护，就会导致ssm_order项目中多引入了`spring-test`的jar包，如果这样的jar包过多的话，对于ssm_order来说也是一种"负担"。

那针对于这种部分项目有的jar包，我们该如何管理优化呢?

1. 在父工程mavne_01_parent的pom.xml来定义依赖管理
    * 定义junit的dependencyManagement内容
    * **`<dependencyManagement>`标签不真正引入jar包，而是配置可供子项目选择的jar包依赖**

2. 在maven_02_ssm的pom.xml添加junit的依赖

maven_02_ssm项目中的junit版本就会跟随着父项目中的标签dependencyManagement中junit的版本发生变化而变化。不需要junit的项目就不需要添加对应的依赖即可。

总结：

继承可以帮助做两件事

* 将所有项目公共的jar包依赖提取到父工程的pom.xml中，子项目就可以不用重复编写，简化开发
* 将所有项目的jar包配置到父工程的dependencyManagement标签下，实现版本管理，方便维护
  * **dependencyManagement标签不真正引入jar包，只是管理jar包的版本**
  * 子项目在引入的时候，只需要指定groupId和artifactId，不需要加version
  * 当dependencyManagement标签中jar包版本发生变化，所有子项目中有用到该jar包的地方对应的版本会自动随之更新

**父工程主要是用来快速配置依赖jar包和管理项目中所使用的资源**。

**小结**

继承的实现步骤:

* 创建Maven模块，设置打包类型为pom

  ```xml
  <packaging>pom</packaging>
  ```

* 在父工程的pom文件中配置依赖关系(子工程将沿用父工程中的依赖关系),一般只抽取子项目中公有的jar包

  ```xml
  <dependencies>
      <dependency>
          <groupId>org.springframework</groupId>
          <artifactId>spring-webmvc</artifactId>
          <version>5.2.10.RELEASE</version>
      </dependency>
      ...
  </dependencies>
  ```

* 在父工程中配置子工程中可选的依赖关系

  ```xml
  <dependencyManagement>
      <dependencies>
          <dependency>
              <groupId>com.alibaba</groupId>
              <artifactId>druid</artifactId>
              <version>1.1.16</version>
          </dependency>
      </dependencies>
      ...
  </dependencyManagement>
  ```

* 在子工程中配置当前工程所继承的父工程

  ```xml
  <!--定义该工程的父工程-->
  <parent>
      <groupId>com.itheima</groupId>
      <artifactId>maven_01_parent</artifactId>
      <version>1.0-RELEASE</version>
      <!--填写父工程的pom文件,可以不写-->
      <relativePath>../maven_01_parent/pom.xml</relativePath>
  </parent>
  ```

* 在子工程中配置使用父工程中可选依赖的坐标

  ```xml
  <dependencies>
      <dependency>
          <groupId>com.alibaba</groupId>
          <artifactId>druid</artifactId>
      </dependency>
  </dependencies>
  ```

注意事项:

1. 子工程中使用父工程中的可选依赖时，仅需要提供群组id和项目id，无需提供版本，版本由父工程统一提供，避免版本冲突
2. 子工程中还可以定义父工程中没有定义的依赖关系,只不过不能被父工程进行版本统一管理。

## 聚合与继承的区别

### 聚合与继承的区别

两种之间的作用:

* 聚合用于快速构建项目，对项目进行管理
* 继承用于快速配置和管理子项目中所使用jar包的版本

聚合和继承的相同点:

* 聚合与继承的pom.xml文件打包方式均为pom，可以将两种关系制作到同一个pom文件中
* 聚合与继承均属于设计型模块，并无实际的模块内容

聚合和继承的不同点:

* 聚合是在当前模块中配置关系，聚合可以感知到参与聚合的模块有哪些
* 继承是在子模块中配置关系，父模块无法感知哪些子模块继承了自己

# 属性

> 属性中会继续解决分模块开发项目存在的问题，版本管理主要是认识下当前主流的版本定义方式。

## 属性

### 问题分析

在父工程中的dependencyManagement标签中对项目中所使用的jar包版本进行了统一的管理。

但是更新Spring版本时，依然需要更新多个jar包的版本，有可能出现漏改导致程序出问题，而且改起来也是比较麻烦。

### 解决步骤

1. 步骤1:父工程中定义属性

```xml
<properties>
    <spring.version>5.2.10.RELEASE</spring.version>
    <junit.version>4.12</junit.version>
    <mybatis-spring.version>1.3.0</mybatis-spring.version>
</properties>
```

2. 步骤2:修改依赖的version

```xml
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-core</artifactId>
    <version>${spring.version}</version>
</dependency>
```

此时，只需要更新父工程中properties标签中所维护的jar包版本，所有子项目中的版本也就跟着更新。

## 配置文件加载属性

项目中的`jdbc.properties`，这个配置文件中的属性，也可以让Maven进行管理，具体的实现步骤为:

1. 步骤1:父工程定义属性

```xml
<properties>
   <jdbc.url>jdbc:mysql://127.1.1.1:3306/ssm_db</jdbc.url>
</properties>
```

2. 步骤2:jdbc.properties文件中引用属性

在jdbc.properties，将jdbc.url的值直接获取Maven配置的属性

```properties
jdbc.driver=com.mysql.jdbc.Driver
jdbc.url=${jdbc.url}
jdbc.username=root
jdbc.password=root
```

3. 步骤3:设置maven过滤文件范围

Maven在默认情况下是从当前项目的`src\main\resources`下读取文件进行打包。

现在我们需要打包的资源文件是在maven_02_ssm下,需要我们通过配置来指定下具体的资源目录。

```xml
<build>
    <resources>
        <!--设置资源目录-->
        <resource>
            <directory>../maven_02_ssm/src/main/resources</directory>
            <!--设置能够解析${}，默认是false -->
            <filtering>true</filtering>
        </resource>
    </resources>
</build>
```

4. 步骤4:测试是否生效

测试的时候，只需要将maven_02_ssm项目进行打包，然后观察打包结果中最终生成的内容是否为Maven中配置的内容。

![](/_images/project/study/ssm/maven/配置文件加载属性是否生效.png)

方式一:

```xml
<build>
    <resources>
        <!--设置资源目录，并设置能够解析${}-->
        <resource>
            <directory>../maven_02_ssm/src/main/resources</directory>
            <filtering>true</filtering>
        </resource>
        <resource>
            <directory>../maven_03_pojo/src/main/resources</directory>
            <filtering>true</filtering>
        </resource>
    </resources>
</build>
```

方式二:

```xml
<build>
    <resources>
        <!--
			${project.basedir}: 当前项目所在目录,子项目继承了父项目，
			相当于所有的子项目都添加了资源目录的过滤
		-->
        <resource>
            <directory>${project.basedir}/src/main/resources</directory>
            <filtering>true</filtering>
        </resource>
    </resources>
</build>
```

上面我们所使用的都是Maven的自定义属性，除了${project.basedir},它属于Maven的内置系统属性。

在Maven中的属性分为:

- 自定义属性（常用）
- 内置属性
- Setting属性
- Java系统属性
- 环境变量属性

![](/_images/project/study/ssm/maven/Maven中的属性.png)

## 版本管理

在Maven创建项目和引用别人项目的时候，看到过如下内容:

![](/_images/project/study/ssm/maven/版本管理中版本号.png)

这里面有两个单词，SNAPSHOT和RELEASE，它们所代表的含义是什么呢?

打开Maven仓库地址`https://mvnrepository.com/`

![](/_images/project/study/ssm/maven/版本管理版本号示例.png)

在jar包的版本定义中，有两个工程版本用的比较多:

- SNAPSHOT（快照版本）
  - 项目开发过程中临时输出的版本，称为快照版本
  - 快照版本会随着开发的进展不断更新
- RELEASE（发布版本）
  - 项目开发到一定阶段里程碑后，向团队外部发布较为稳定的版本，这种版本所对应的构件文件是稳定的
  - 即便进行功能的后续开发，也不会改变当前发布版本内容，这种版本称为发布版本
- alpha版:内测版，bug多不稳定内部版本不断添加新功能
- beta版:公测版，不稳定(比alpha稳定些)，bug相对较多不断添加新功能
- 纯数字版

# 多环境配置与应用

## 多环境开发

![](/_images/project/study/ssm/maven/多环境开发.png)

maven提供配置多种环境的设定，帮助开发者在使用过程中快速切换环境。具体实现步骤:

1. 步骤1:父工程配置多个环境,并指定默认激活环境

```xml
<profiles>
    <!--开发环境-->
    <profile>
        <id>env_dep</id>
        <properties>
            <jdbc.url>jdbc:mysql://127.1.1.1:3306/ssm_db</jdbc.url>
        </properties>
        <!--设定是否为默认启动环境-->
        <activation>
            <activeByDefault>true</activeByDefault>
        </activation>
    </profile>
    <!--生产环境-->
    <profile>
        <id>env_pro</id>
        <properties>
            <jdbc.url>jdbc:mysql://127.2.2.2:3306/ssm_db</jdbc.url>
        </properties>
    </profile>
    <!--测试环境-->
    <profile>
        <id>env_test</id>
        <properties>
            <jdbc.url>jdbc:mysql://127.3.3.3:3306/ssm_db</jdbc.url>
        </properties>
    </profile>
</profiles>
```

2. 步骤2:执行安装查看env_dep环境是否生效

3. 步骤3:切换默认环境为生产环境

```xml
    <!--生产环境-->
    <profile>
        <id>env_pro</id>
        <properties>
            <jdbc.url>jdbc:mysql://127.2.2.2:3306/ssm_db</jdbc.url>
        </properties>
        <!--设定是否为默认启动环境-->
        <activation>
            <activeByDefault>true</activeByDefault>
        </activation>
    </profile>
```

4. 步骤4:执行安装并查看env_pro环境是否生效

查看到的结果为`jdbc:mysql://127.2.2.2:3306/ssm_db`

虽然已经能够实现不同环境的切换，但是每次切换都是需要手动修改，如何来实现在不改变代码的前提下完成环境的切换呢?

5. 步骤5:命令行实现环境切换

`mvn install -P env_test`

6. 步骤6:执行安装并查看env_test环境是否生效

查看到的结果为`jdbc:mysql://127.3.3.3:3306/ssm_db`

总结：对于多环境切换只需要两步即可:

* 父工程中定义多环境
* 使用多环境(构建过程)
`mvn 指令 -P 环境定义ID[环境定义中获取]`

## 跳过测试

前面在执行`install`指令的时候，Maven都会按照顺序从上往下依次执行，每次都会执行`test`,

对于`test`来说有它存在的意义，

* 可以确保每次打包或者安装的时候，程序的正确性。
* 如果已经测试通过，在没有修改程序的前提下，再次执行打包或安装命令，这时测试会被再次执行，就有点耗费时间了。
* 功能开发过程中有部分模块还没有开发完毕，测试无法通过，但是想要把其中某一部分进行快速打包，此时由于测试环境失败就会导致打包失败。

遇到上面这些情况的时候，我们就想跳过测试执行下面的构建命令，具体实现方式有很多：

### 方式一:IDEA工具实现跳过测试

![](/_images/project/study/ssm/maven/IDEA工具实现跳过测试.png)

图中的按钮为`Toggle 'Skip Tests' Mode`,

### 方式二:配置插件实现跳过测试

在父工程中的pom.xml中添加测试插件配置

```xml
<build>
    <plugins>
        <plugin>
            <artifactId>maven-surefire-plugin</artifactId>
            <version>2.12.4</version>
            <configuration>
                <skipTests>false</skipTests>
                <!--排除掉不参与测试的内容-->
                <excludes>
                    <exclude>**/BookServiceTest.java</exclude>
                </excludes>
            </configuration>
        </plugin>
    </plugins>
</build>
```

* skipTests:如果为true，则跳过所有测试，如果为false，则不跳过测试
* excludes：哪些测试类不参与测试，即排除，针对skipTests为false来设置的
* includes: 哪些测试类要参与测试，即包含,针对skipTests为true来设置的

### 方式三:命令行跳过测试

使用Maven的命令行，`mvn 指令 -D skipTests`

注意事项:

* 执行的项目构建指令必须包含测试生命周期，否则无效果。例如执行compile生命周期，不经过test生命周期。
* 该命令可以不借助IDEA，直接使用cmd命令行进行跳过测试，需要注意的是cmd要在pom.xml所在目录下进行执行。

# 私服

## 私服简介

团队开发现状分析

![](/_images/project/study/ssm/maven/团队开发现状.png)

* A负责ssm_crm的开发，自己写了一个ssm_pojo模块，要想使用直接将ssm_pojo安装到本地仓库即可
* B负责ssm_order的开发，需要用到A所写的ssm_pojo模块，这个时候如何将A写的ssm_pojo模块交给B呢?
    * 直接拷贝：团队之间的jar包管理会非常混乱而且容器出错
    * 中央仓库下载：Maven的中央仓库不允许私人上传自己的jar包，自己搭建一个类似于中央仓库的东西，把自己的内容上传上去，其他人就可以从上面下载jar包使用

* 私服:公司内部搭建的用于存储Maven资源的服务器
* 远程仓库:Maven开发团队维护的用于存储Maven资源的服务器

所以说:

* 私服是一台独立的服务器，用于解决团队内部的资源共享与资源同步问题

搭建Maven私服的方式有很多，介绍其中一种使用量比较大的实现方式:

* Nexus
  * Sonatype公司的一款maven私服产品
  * 下载地址：https://help.sonatype.com/repomanager3/download

## 私服安装

1. 步骤1:下载解压

2. 步骤2:启动Nexus

使用cmd进入到解压目录下的`nexus-3.30.1-01\bin`,执行如下命令:

```
nexus.exe /run nexus
```

3. 步骤3:浏览器访问

访问地址为:

```
http://localhost:8081
```

![](/_images/project/study/ssm/maven/私服界面.png)

4. 步骤4:首次登录重置密码

如果要想修改一些基础配置信息，可以使用:

- 修改基础配置信息
  - 安装路径下etc目录中nexus-default.properties文件保存有nexus基础配置信息，例如默认访问端口。
- 修改服务器运行配置信息
  - 安装路径下bin目录中nexus.vmoptions文件保存有nexus服务器启动对应的配置信息，例如默认占用内存空间。

## 私服仓库分类

私服资源操作流程分析:

![](/_images/project/study/ssm/maven/私服资源操作流程.png)

所有私服仓库总共分为三大类:

宿主仓库hosted 

- 保存无法从中央仓库获取的资源
  - 自主研发
  - 第三方非开源项目,比如Oracle,因为是付费产品，所以中央仓库没有

代理仓库proxy 

- 代理远程仓库，通过nexus访问其他公共仓库，例如中央仓库

仓库组group 

- 将若干个仓库组成一个群组，简化配置
- 仓库组不能保存资源，属于设计型仓库

![](/_images/project/study/ssm/maven/私服仓库分类.png)

## 本地仓库访问私服配置

![](/_images/project/study/ssm/maven/本地仓库访问私服配置.png)

需要在本地Maven的配置文件`settings.xml`中进行配置。

1. 步骤1:私服上配置仓库

![](/_images/project/study/ssm/maven/私服上配置仓库.png)

2. 步骤2:配置本地Maven对私服的访问权限

```xml
<servers>
    <server>
        <id>itheima-snapshot</id>
        <username>admin</username>
        <password>admin</password>
    </server>
    <server>
        <id>itheima-release</id>
        <username>admin</username>
        <password>admin</password>
    </server>
</servers>
```

3. 步骤3:配置私服的访问路径

```xml
<mirrors>
    <mirror>
        <!--配置仓库组的ID-->
        <id>maven-public</id>
        <!--*代表所有内容都从私服获取-->
        <mirrorOf>*</mirrorOf>
        <!--私服仓库组maven-public的访问路径-->
        <url>http://localhost:8081/repository/maven-public/</url>
    </mirror>
</mirrors>
```

![](/_images/project/study/ssm/maven/配置私服的访问路径.png)

至此本地仓库就能与私服进行交互了。

## 私服资源上传与下载

本地仓库与私服已经建立了连接，需要往私服上上传资源和下载资源，具体的实现步骤为:

1. 步骤1:配置工程上传私服的具体位置

```xml
 <!--配置当前工程保存在私服中的具体位置-->
<distributionManagement>
    <repository>
        <!--和maven/settings.xml中server中的id一致，表示使用该id对应的用户名和密码-->
        <id>itheima-release</id>
         <!--release版本上传仓库的具体地址-->
        <url>http://localhost:8081/repository/itheima-release/</url>
    </repository>
    <snapshotRepository>
        <!--和maven/settings.xml中server中的id一致，表示使用该id对应的用户名和密码-->
        <id>itheima-snapshot</id>
        <!--snapshot版本上传仓库的具体地址-->
        <url>http://localhost:8081/repository/itheima-snapshot/</url>
    </snapshotRepository>
</distributionManagement>
```

2. 步骤2:发布资源到私服

执行Maven命令
```
mvn deploy
```

**注意:**

要发布的项目都需要配置`distributionManagement`标签，要么在自己的pom.xml中配置，要么在其父项目中配置，然后子项目中继承父项目即可。

发布成功，在私服中就能看到:

![](/_images/project/study/ssm/maven/私服发布成功.png)

现在发布是在itheima-snapshot仓库中，如果想发布到itheima-release仓库中就需要将项目pom.xml中的version修改成RELEASE即可。

如果想删除已经上传的资源，可以在界面上进行删除操作:

![](/_images/project/study/ssm/maven/私服进行删除.png)

如果私服中没有对应的jar，会去中央仓库下载，速度很慢。可以配置让私服去阿里云中下载依赖。

![](/_images/project/study/ssm/maven/私服去阿里云中下载依赖.png)

至此私服的搭建就已经完成，相对来说有点麻烦，但是步骤都比较固定，后期大家如果需要的话，就可以参考上面的步骤一步步完成搭建即可。