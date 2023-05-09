# 常用开发库 - poco

# 参考资料

* [源码](https://github.com/pocoproject/poco)

# 概述

POCO C++库是一组开源C++类库的集合，它们简化及加速了用C++来开发以网络功能为核心的可移植程序的过程。这些库，完美地与C++标准库结合到一起，并且填补了它所留下的那些空缺。它们具有模块化、高效的设计与实现，使得POCO C++库特别适合于进行嵌入式开发。而这是C++编程语言正在变得越来越流行的领域，因为，它既能进行底层(设备I/O、中断处理，等等)的开发，也能进行高级的面向对象的开发。当然，POCO也已经准备好面对企业级开发的挑战了。

![](/_images/develop/library/poco/poco_overview.png)

POCO由4个核心库及若干个附加库组成。

核心库：

* Foundation
* XML
* Util
* Net。

附加库：

* NetSSL，为Net 库中的网络类提供SSL 支持；
* Data，用来以统一的形式访问不同的SQL 数据库。

POCO致力于进行以**网络功能为核心的跨平台C++软件的开发**，可以类比于Ruby on Rails对于Web开发的作用——一个功能强大而又简单易用的平台，用来构建你自己的应用程序。POCO是严格围绕标准ANSI/ISO C++来开发的，并且支持标准库。贡献者们努力地达到以下要素之间的平衡：使用高级的C++特性；保持那些类的可理解性；保持代码的干净、一致及易维护性。


# 版本编译

> 基本版本（Basic Edition）不需要外部依赖

> 完整版本（Complete Edition）：需要外部依赖OpenSSL、MySQL 客户端和ODBC

## 精简版

```
cd $cur_path/$poco_path
poco_output="$cur_path/$poco_path/output"
mkdir -p  $poco_output
tar -zxvf poco-1.10.1-all.tar.gz
cd ./poco-1.10.1-all
./configure --config=Linux --no-tests --no-samples --minimal --prefix=$poco_output
make && make install

./configure --no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB,Redis, --prefix=/home/MyPrj_V12/build_comlib/poco/output

--no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB,Redis, --prefix=/home/MyPrj_V14/build_comlib/poco/output

./configure --config=Linux --no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB --prefix=/home/poco/poco-1.12.2-all/poco_output

选项说明：
–config=Linux：在Linux环境下编译
–minimal：最小功能编译，只构建XML、JSON、工具和网络
–no-tests：不编译测试部分的代码
–no-samples：不编译样例部分的代码
-prefix：指定安装路径
```

## 完整版

```
yum -y install unixODBC
yum -y install unixODBC-devel
yum -y install mysql
yum -y install mysql-devel
yum -y install openssl-devel 
yum -y install postgresql-devel
./configure
make && make install
```

执行过程
```
1.普通用户中下载gcc的最新源码包：(或在http://mirror.hust.edu.cn/gnu/gcc/gcc-9.1.0/中下载)

wget http://ftp.gnu.org/gnu/gcc/gcc-9.1.0/gcc-9.1.0.tar.gz

2. 解压安装包

tar -xzvf gcc-9.1.0.tar.gz

3. 进入目录gcc-9.1.0 

 cd gcc-9.1.0

4.运行download_prerequisites脚本

./contrib/download_prerequisites

该脚本文件会帮我们下载、配置、安装依赖库

5. 建立目录，将所有输出放入该目录

mkdir gcc_temp

6. 进入目录

cd gcc_temp

7. 执行以下命令：

../configure -enable-checking=release -enable-languages=c,c++ -disable-multilib

8. 编译（比较耗时，大概2~4小时，编译时注意时间安排）

make  make install

9. 检查验证

执行gcc --version 
```

## 最终POCO编译成功版本

```
[root@VM-16-6-centos ~]# docker run -it -d -v /home/klc/poco:/home/poco --name build_lib_0 docker.io/klc407073648/centos_build_lib:v3.0 bash
29ca61c7c80e4b67265864fe7d0fb44f4c921cb69ecaba7a94648c20b06304c6
[root@VM-16-6-centos ~]# docker exec -it build_lib_0 bash
[root@29ca61c7c80e /]# cd /home/poco/
[root@29ca61c7c80e poco]# tar -zxvf poco-1.12.2-all.tar.gz
[root@29ca61c7c80e poco]# cd ./poco-1.12.2-all
[root@29ca61c7c80e poco-1.12.2-all]# mkdir poco_output
[root@29ca61c7c80e poco-1.12.2-all]# yum install -y mysql mysql-devel openssl-devel
[root@29ca61c7c80e poco-1.12.2-all]# cp -r /usr/lib64/mysql/* /usr/lib/
[root@29ca61c7c80e poco-1.12.2-all]# ./configure --config=Linux --no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB --prefix=/home/poco/poco-1.12.2-all/poco_output
[root@29ca61c7c80e poco-1.12.2-all]# make
[root@29ca61c7c80e poco-1.12.2-all]# make install
```

# examples下的demo使用

路径: build_lib\examples\examples\3partlib\poco

测试XML库代码:

执行结果:

```
[root@5d4b980baaa2 poco]# ./pocoTest
<?xml version='1.0' encoding='UTF-8'?>
<!--This is comment.-->
<root_element>
        <child_element_a a1="1" a2="2"/>
        <child_element_b b1="3" b2="4"/><![CDATA[ignore parse txt !@#$%^&*()]]>txt_content</root_element>
```
