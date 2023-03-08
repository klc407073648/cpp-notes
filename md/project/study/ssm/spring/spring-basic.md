# SSM框架 - Spring框架学习

Spring框架主要的优势是在<font color='red'>**简化开发**</font>和 <font color='red'>**框架整合**</font>上，其主要内容包括以下几点：

* 简化开发: 

  * <font color='red'>**IOC**</font>
  * <font color='red'>**AOP**</font>
    * <font color='red'>**事务处理**</font>
* 框架整合

  - <font color='red'>**MyBatis**</font>
  - MyBatis-plus
  - Struts
  - Struts2
  - Hibernate
  - ……
  
* 学习路线
  * Spring的IOC/DI
  * Spring的AOP
  * AOP的具体应用,事务管理
  * IOC/DI的具体应用,整合Mybatis


* 应用场景
  * web、微服务以及分布式系统等
* Spring全家桶：
  * Spring Framework:Spring框架，是Spring中最早最核心的技术，也是所有其他技术的基础。
  * SpringBoot:Spring是来简化开发，而**<font color='red'>SpringBoot是来帮助Spring在简化的基础上能更快速进行开发</font>**。
  * SpringCloud:这个是用来做分布式之微服务架构的相关开发。

* 官网：https://spring.io，


## 系统架构图

Spring Framework的5版本目前没有最新的架构图，而最新的是4版本，所以接下来主要研究的是4的架构图

![Spring框架](/_images/project/study/ssm/spring/Spring框架.png)

1.核心层

  * Core Container:核心容器，这个模块是Spring最核心的模块，其他的都需要依赖该模块

2.AOP层

  * AOP:面向切面编程，它依赖核心层容器，目的是==在不改变原有代码的前提下对其进行功能增强==
  * Aspects:AOP是思想,Aspects是对AOP思想的具体实现

3.数据层

  * Data Access:数据访问，Spring全家桶中有对数据访问的具体实现技术
  * Data Integration:数据集成，Spring支持整合其他的数据层解决方案，比如Mybatis
  * Transactions:事务，Spring中事务管理是Spring AOP的一个具体实现，也是后期学习的重点内容

4.Web层

  * 这一层的内容将在SpringMVC框架具体学习

5.Test层

  * Spring主要整合了Junit来完成单元测试和集成测试

## 核心概念

* IOC（Inversion of Control）控制反转：使用对象时，**<font color='red'>由主动new产生对象转换为由外部提供对象，此过程中对象创建控制权由程序转移到外部</font>**，此思想称为控制反转。
* Spring技术对IOC思想进行了实现：Spring提供了一个容器，称为<font color='red'>**IOC容器**</font>，用来充当IOC思想中的"外部"。
* IOC容器：负责对象的创建、初始化等一系列工作，其中包含了数据层和业务层的类对象。
* Bean：被创建或被管理的对象在IOC容器中统称为<font color='red'>**Bean**</font>，IOC容器中放的就是一个个的Bean对象。默认情况下，Spring创建的Bean对象都是<font color='red'>**单例**</font>的(scope设置为singleton 或prototype)。
* <font color='red'>**DI（Dependency Injection）依赖注入**</font>：在容器中建立bean与bean之间的依赖关系的整个过程。例如，业务层需要依赖数据层，service就要和dao建立依赖关系。

介绍完Spring的IOC和DI的概念后，会发现这两个概念的最终目标就是:<font color='red'>**充分解耦**</font>，具体实现:

* 使用IOC容器管理bean（IOC)

* 在IOC容器内将有依赖关系的bean进行关系绑定（DI）


最终结果为:<font color='red'>**使用对象时不仅可以直接从IOC容器中获取，并且获取到的bean已经绑定了所有的依赖关系**</font>。



## Bean

### Bean实例化

bean使用构造方法创建，Spring的IOC实例化对象的三种方式分别是:

* 构造方法(常用)
* 静态工厂(了解)
* 实例工厂(了解)
  * FactoryBean(实用)

###  Bean生命周期

(1)Spring中对bean生命周期控制提供了两种方式:

* 在配置文件中的bean标签中添加`init-method`和`destroy-method`属性
* 类实现`InitializingBean`与`DisposableBean`接口，这种方式了解下即可。

(2)对于bean的生命周期控制在bean的整个生命周期中所处的位置如下:

* 初始化容器
  * 1.创建对象(内存分配)
  * 2.执行构造方法
  * 3.执行属性注入(set操作)
  * 4.执行bean初始化方法
* 使用bean
  * 1.执行业务操作
* 关闭/销毁容器
  * 1.执行bean销毁方法

(3)关闭容器的两种方式:

* ConfigurableApplicationContext是ApplicationContext的子类
  * close()方法
  * registerShutdownHook()方法

## DI相关

Spring提供了两种注入方式，分别是:

* <font color='red'>**setter注入**</font>，提供可访问的<font color='red'>**set**</font>方法：setBookDao(BookDao bookDao)  
  * 简单类型
  * 引用类型
* <font color='red'>**构造器注入**</font>，BookServiceImpl(BookDao bookDao)  
  * 简单类型
  * 引用类型

上述注入方式，不可避免地需要编写大量的配置文件，下面介绍一种更轻量方便的方法： <font color='red'>**自动装配**</font>

自动装配方式：

* 按类型（常用）：autowire="byType"  
* 按名称
* 按构造方法
* 不启用自动装配

<font color='red'>**集合注入**</font>：

* 数组
* List
* Set
* Map
* Properties

编写方式，以数组为例：

```xml
<bean id="bookDao" class="com.itheima.dao.impl.BookDaoImpl">
        <!--数组注入-->
        <property name="array">
            <array>
                <value>100</value>
                <value>200</value>
                <value>300</value>
            </array>
        </property>
</bean>
```

## 思考

* 为什么bean默认为单例?
  * bean为单例的意思是在Spring的IOC容器中只会有该类的一个对象，只有一个就避免了对象的频繁创建与销毁，达到了bean对象的复用，性能高。
* bean在容器中是单例的，会不会产生线程安全问题?
  * 如果对象是有状态对象，即该对象有成员变量可以用来存储数据的，
  * 因为所有请求线程共用一个bean对象，所以会存在线程安全问题。
  * 如果对象是无状态对象，即该对象没有成员变量没有进行数据存储的，
  * 因方法中的局部变量在方法调用完成后会被销毁，所以不会存在线程安全问题。
* 哪些bean对象适合交给容器进行管理?
  * 表现层对象
  * 业务层对象
  * 数据层对象
  * 工具对象
* 哪些bean对象不适合交给容器进行管理?
  * 封装实例的域对象，因为会引发线程安全问题，所以不适合。
