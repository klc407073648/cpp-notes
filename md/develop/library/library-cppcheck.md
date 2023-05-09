# 常用开发库 - cppcheck

1. github官网下载tar.gz包

2. 安装过程

```
tar -zxvf cppcheck-2.6.tar.gz
cd ./cppcheck-2.6
mkdir build
mkdir cppcheck_output
cd ./build
cmake ..
make -j4
make install SRCDIR=. DESTDIR=../cppcheck_output/ CFGDIR=../cfg
```
 
3. 测试

```
cd /home/klc/code/cppcheck/cppcheck-2.6/cppcheck_output/usr/local/bin/
./cppcheck --enable=all  FunctionStudy/systemFunUse/util.cpp
```