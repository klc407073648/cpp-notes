# Robot Framework自动化测试框架搭建

[[toc]]

# 参考资料

* [Python3+RIDE+Robot Framework自动化测试框架搭建](https://www.cnblogs.com/panda-sweets/p/13641269.html)
* [Docker + Jenkins 部署完整node项目](https://segmentfault.com/a/1190000021462867?utm_source=tag-newest)

# Robot Framework搭建详细过程

## 安装环境 

* python 3.6.3
* windows 10

pip安装过程可能过慢，可以直接使用国内的镜像地址

```
阿里云 http://mirrors.aliyun.com/pypi/simple/
中国科技大学 https://pypi.mirrors.ustc.edu.cn/simple/
豆瓣 http://pypi.douban.com/simple/
清华大学 https://pypi.tuna.tsinghua.edu.cn/simple/
中国科学技术大学 http://pypi.mirrors.ustc.edu.cn/simple/

使用方法：pip install robotframework  -i https://pypi.tuna.tsinghua.edu.cn/simple/
```

配置webdriver:
下载 chromedriver  驱动，把 chromedriver.exe 放到  /python27/Scripts  路径下    [下载地址](http://chromedriver.storage.googleapis.com/index.html)

## 安装过程

**RobotFramework安装**

RF测试框架：

* 安装方法：CMD命令窗口运行pip命令。

```bash
pip install robotframework
```

**WxPython安装**

Wxpython是python非常有名的一个GUI库，RIDE就是基于这个库开发的。

```bash
pip install wxPython
```

**RIDE安装**

RIDE是一个图形界面工具，用于创建、组织、运行测试案例。

```bash
pip install robotframework-ride 
```

安装过程中会提示是否创建桌面快捷方式，选择是，安装完成后，双击桌面“ride.exe”即可打开。若未生成图标，参考[资料](https://zhuanlan.zhihu.com/p/346553476)

**各种库安装**

RF的selenium库，借助Selenium，可以模拟浏览器端的测试，通常用于Web自动化测试。

* Selenium测试可以在Windows、Linux上的 IE、Chrome和Firefox中运行。

RF的Requets库，Requests是Python的HTTP客户端库，可以通过调用request库发送GET、POST、PUT、DELETE请求。

* HttpLibrary当然也可以了。都可以应用到接口自动化中。

```bash
pip install robotframework-selenium2library
pip install robotframework-requests
pip install robotframework-httplibrary
```

参数说明：
```
-d 标识是让 docker 容器在后台运行
--name 定义一个容器的名字，如果没有指定，那么会自动生成一个随机数字符串当做UUID
-p 9090:8080 端口映射，我本地的8080被占用了，所以随便映射了一个9090
-p 50000:50000 端口映射
-v /home/jenkins/data/jenkins_home:/var/jenkins_home 绑定一个数据卷，/home/jenkins/data/jenkins_home是刚才创建的本地数据卷
```

**总结**

```
cd /home/jenkins/
mkdir -p ./data/jenkins_home/
chown -R 1000:1000 /home/jenkins/data/jenkins_home/
docker run -d --name jenkins -p 9090:8080 -p 50000:50000 -v /home/jenkins/data/jenkins_home:/var/jenkins_home 
```

# 运行测试

1）New Project，名字可自定义(type：**Directoy**；Format：**ROBOT**)

- 若选择Directoy，目录下面可以新增Suite，Suite下可新增CASE
- 若选择FILE，目录下只能创建CASE

2) New Suite，名字可自定义，可配置CASE中使用的关键字。(type：**File**；Format：**ROBOT**)

- 若选择Directoy，目录下还可以创建suite
- 若选择FILE，目录下只能创建CASE

3) New Test Case》名称可自定义，用例设计主要在这里。

一组相关的测试用例（Test Case）就是一个测试套件（Test Suite）。

也就是说，一个测试套件由多个测试用例串连组成，可以将测试套件理解为测试用例组。



测试程序：

* 测试访问百度网站，搜索指定关键字

```
*** Settings ***
Library           Selenium2Library

*** Test Cases ***
chormeTest
    Open Browser    http://www.baidu.com    Chrome
    Input Text    id=kw    robot framework学习
    Click Button    id=su
    sleep    2
    Close Browser
```

![1](/_images/project/practice/tools/RF/百度测试.png)

定位元素位置：可以[参考](https://www.cnblogs.com/yu2000/p/7141769.html)

![2](/_images/project/practice/tools/RF/定位元素.png)
