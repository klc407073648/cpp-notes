# centos_build_lib 镜像构建

## scons

> 开放源码、以Python语言编码的自动化构建工具

安装：

```
unzip scons-3.1.1.zip
cd ./scons-3.1.1 && python setup.py install
```

## cmake

> 跨平台的构建工具,可以用简单的语句来描述所有平台的安装(编译过程)。

```
tar -zxf  cmake-3.14.5.tar.gz
cd ./cmake-3.14.5 

./bootstrap && gmake && gmake install 
ln -s /usr/local/bin/cmake /usr/bin/
```

## gcc

> 由GNU开发的编程语言译器。

1. 普通用户中下载gcc的最新源码包：(或在http://mirror.hust.edu.cn/gnu/gcc/gcc-9.1.0/中下载)

```
wget http://ftp.gnu.org/gnu/gcc/gcc-9.1.0/gcc-9.1.0.tar.gz
```

2. 解压安装包

```
tar -xzvf gcc-9.1.0.tar.gz
```

3. 进入目录gcc-9.1.0 

```
 cd gcc-9.1.0
```

4. 运行download_prerequisites脚本

```
./contrib/download_prerequisites
```

该脚本文件会帮我们下载、配置、安装依赖库

5. 建立目录，将所有输出放入该目录

```
mkdir gcc_temp
```

6. 进入目录

```
cd gcc_temp
```

7. 执行以下命令：

```
../configure -enable-checking=release -enable-languages=c,c++ -disable-multilib
```

8. 编译（比较耗时，大概2~4小时，编译时注意时间安排）

```
make  make install
```

9. 检查验证

```
gcc --version 
```

## 安装Python3.7

```
# 预处理
tar -xvf Python-3.7.10.tgz
cd ./Python-3.7.10 

# 编译
./configure --prefix=/home/tools/python3/ --with-ssl
make
make install

# 链接
ln -s /home/tools/python3/bin/python3.7 /usr/bin/python3
ln -s /home/tools/python3/bin/pip3 /usr/bin/pip3
python3 -m pip install --upgrade pip
```

