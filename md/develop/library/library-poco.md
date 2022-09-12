# poco使用

[[toc]]

# 概述

```
基本版本（Basic Edition）不需要外部依赖
完整版本（Complete Edition）：需要外部依赖OpenSSL、MySQL 客户端和ODBC
```

##  精简版

```
cd $cur_path/$poco_path
poco_output="$cur_path/$poco_path/output"
mkdir -p  $poco_output
tar -zxvf poco-1.10.1-all.tar.gz
cd ./poco-1.10.1-all
./configure --config=Linux --no-tests --no-samples --minimal --prefix=$poco_output
make && make install

./configure --no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB,Redis, --prefix=/home/MyPrj_V12/build_comlib/poco/output
```

可以通过, `./configure -help` 查看参数

选项说明：

* config=Linux：在Linux环境下编译
* minimal：最小功能编译，只构建XML、JSON、工具和网络
* no-tests：不编译测试部分的代码
* no-samples：不编译样例部分的代码
* prefix：指定安装路径


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

## 最终POCO编译成功版本

```
docker run -it -d -v /home/klc/poco:/home/poco --name build_lib_0 docker.io/klc407073648/centos_build_lib:v3.0 bash

docker exec -it build_lib_0 bash

# 预处理
cd /home/poco/
tar -zxvf poco-1.12.2-all.tar.gz
cd ./poco-1.12.2-all
mkdir poco_output

# 安装依赖库
yum install -y mysql mysql-devel openssl-devel
cp -r /usr/lib64/mysql/* /usr/lib/

# 编译
./configure --config=Linux --no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB --prefix=/home/poco/poco-1.12.2-all/poco_output
make
make install
```

测试XML库

```
[root@29ca61c7c80e test]# cd ./build/
[root@29ca61c7c80e build]# cmake ..
-- The CXX compiler identification is GNU 9.1.0
-- Check for working CXX compiler: /usr/local/bin/g++
-- Check for working CXX compiler: /usr/local/bin/g++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
CMake Warning (dev) in CMakeLists.txt:
  AUTOGEN: No valid Qt version found for target example.  AUTOMOC, AUTOUIC
  and AUTORCC disabled.  Consider adding:

    find_package(Qt<QTVERSION> COMPONENTS Widgets)

  to your CMakeLists.txt file.
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Generating done
-- Build files have been written to: /home/poco/test/build
[root@29ca61c7c80e build]# make
Scanning dependencies of target example
[ 50%] Building CXX object CMakeFiles/example.dir/main.cpp.o
[100%] Linking CXX executable example
[100%] Built target example
[root@29ca61c7c80e build]# ./example
<?xml version='1.0' encoding='UTF-8'?>
<!--This is comment.-->
<root_element>
        <child_element_a a1="1" a2="2"/>
        <child_element_b b1="3" b2="4"/><![CDATA[ignore parse txt !@#$%^&*()]]>txt_content</root_element>
```
