# 常用开发库 - drogon

## 编译环境

docker run -it -d -v /home/test/:/home/test --name build_drogon docker.io/klc407073648/centos_build_lib:v3.0 /bin/bash
docker exec -it build_drogon bash

## 安装与使用

```shell
# 1. 安装依赖库
yum install -y libuuid-devel
yum install -y openssl-devel
yum install -y zlib-devel

# 2.安装jsoncpp
cd /home/
tar -zxvf jsoncpp-1.9.5.tar.gz
cd ./jsoncpp-1.9.5
mkdir build && cd build && cmake ..
make -j4
make install

# 安装后，使用下述语句解决 `drogon_ctl在创建的新项目的时候会找不到jsoncpp`
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib64
export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/lib64
source /etc/profile

# 3.编译drogon
cd /home/
tar -zxvf drogon-1.8.3.tar.gz
cd ./drogon-1.8.3
rm -rf ./trantor
cp ../trantor-1.5.10.tar.gz .
tar -zxvf trantor-1.5.10.tar.gz
mv trantor-1.5.10 trantor

mkdir -p build
cd ./build
cmake ..
make  -j4
make install

# 4.测试drogon代码
cd /home/cpp-backend/
cd ./build/
cmake ..
make
```