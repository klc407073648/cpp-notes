https://blog.csdn.net/win7583362/article/details/124660096

学习json格式和xml格式


* IOC：控制反转，控制反转的是对象的创建权
* DI：依赖注入，绑定对象与对象之间的依赖关系
* IOC容器：Spring创建了一个容器用来存放所创建的对象，这个容器就叫IOC容器
* Bean：容器中所存放的一个个对象就叫Bean或Bean对象


将学习知识概念  和 实际使用md区别开


tips:

不论是那种引用类型,直接打印对象名的时候,**默认调用toString方法**.
如果此类没有重写Object类中的toString方法,那么就调用Object类的toString方法,
即打印出来的是地址(全类名+@+16进制的hashCode).如果此类重写了toString方法,那么就打印重写的toString方法.

https://blog.csdn.net/weixin_48747169/article/details/123407628
https://www.codenong.com/cs105524649/


梗：
你终于表现出合格开发者的职业素养了，正常操作能返回，异常操作也能返回  ———— 异常处理器
流氓不可怕，可怕的是流氓会java，你不能预测或控制用户的输入，只能在后端代码层面做好自己的工作 —————— 不规范的用户行为

axios

ajax

JOPO

https://blog.csdn.net/u014199143/article/details/80692685

从Spring3.0，@Configuration用于定义配置类，可替换xml配置文件，被注解的类内部包含有一个或多个被@Bean注解的方法，
这些方法将会被AnnotationConfigApplicationContext或AnnotationConfigWebApplicationContext类进行扫描，并用于构建bean定义，初始化Spring容器。



找工作：

根据大厂招聘要求：
写契合度高的简历，补充项目
github找项目，改成自己的项目
再刷笔试题和八股文


tomcat是一个web服务器软件，它是由apache组织提供的。其特点是小巧灵活，免费开源，简单易用。
Apache(音译为阿帕奇)是世界使用排名第一的Web服务器软件。
apache的安装部署
        1、yum install httpd -y   ：下载并安装apache服务器（在linux系统的镜像中有安装包）
		
		
MAVEN

分模块开发
maven 直接依赖和间接依赖


版本管理：
snapshot
alpha
release

https://zhuanlan.zhihu.com/p/420745873   版本区别

写一个空的logback.xml会过滤掉无效的日志

User::getAge()  不应该是获取值吗？？？？


乐观锁

update version=version+1 where version= curval;