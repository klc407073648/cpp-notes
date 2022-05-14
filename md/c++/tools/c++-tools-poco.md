# poco使用

[[toc]]

- 概述

```
基本版本（Basic Edition）不需要外部依赖
完整版本（Complete Edition）：需要外部依赖OpenSSL、MySQL 客户端和ODBC
```
- 精简版
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


选项说明：
–config=Linux：在Linux环境下编译
–minimal：最小功能编译，只构建XML、JSON、工具和网络
–no-tests：不编译测试部分的代码
–no-samples：不编译样例部分的代码
-prefix：指定安装路径
```

- 完整版
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

- 密码

```
密码至少包含 数字和英文，长度6-20

String reg = "^(?![0-9]+$)(?![a-zA-Z]+$)[0-9A-Za-z]{6,20}$";
 
密码包含 数字,英文,字符中的两种以上，长度6-20

String reg = "^(?![0-9]+$)(?![a-z]+$)(?![A-Z]+$)(?!([^(0-9a-zA-Z)])+$).{6,20}$";
 
至少包含数字跟字母，可以有字符

String reg = "(?=.*([a-zA-Z].*))(?=.*[0-9].*)[a-zA-Z0-9-*/+.~!@#$%^&*()]{6,20}$";
```

使用cmake方式安装，需要支持C++14标准，gcc4.8.5不支持，需要升级

```
https://github.com/pocoproject/poco


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


collect2: error: ld terminated with signal 9 [Killed]
make[3]: *** [lto1] Error 1
make[3]: *** Waiting for unfinished jobs....
make[3]: Leaving directory `/home/gcc/gcc-9.1.0/temp/gcc'
make[2]: *** [all-stage1-gcc] Error 2
make[2]: Leaving directory `/home/gcc/gcc-9.1.0/temp'
make[1]: *** [stage1-bubble] Error 2

https://www.cnblogs.com/godfather007/p/10444270.html
知识点扩展：

在网上寻找解决方案时碰到一些人说是因内存不足需要添加swap分区来解决，未实际验证，这里给出添加swap分区的方法

添加命令

SWAP=/tmp/swap

dd if=/dev/zero of=$SWAP bs=1M count=500 #500为swap分区大小

mkswap $SWAP

swapon $SWAP #启用swap



 docker commit 881a66970443 centos-vim

 https://gcc.gnu.org/projects/cxx-status.html#cxx14


