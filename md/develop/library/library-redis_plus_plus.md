# redis++使用

[[toc]]

# 选择Redis库

找Redis官网, C++语言的客户端连接库: [https://redis.io/docs/clients](https://redis.io/docs/clients)

* [redis-plus-plus](https://github.com/sewenew/redis-plus-plus)
* [C++ redis client: redis_plus_plus](https://blog.csdn.net/qq2399431200/article/details/123292652)
* [C++ 的redis 连接库:RedisPlusplus](https://blog.csdn.net/ILOVEYOULEEHUIJIE/article/details/108315296)

## 安装过程

首先安装hiredis，然后安装redis-plus-plus(基于hiredis)

```bash
tar -zxvf hiredis-1.0.2.tar.gz
cd ./hiredis-1.0.2
make && make install

cd ..
tar -zxvf redis-plus-plus-1.3.5.tar.gz
cd ./redis-plus-plus-1.3.5
 mkdir build
cd ./build/
cmake ..
make
make install
```

测试程序：

```
export LD_LIBRARY_PATH=/usr/local/lib
/usr/bin/g++-10 -std=c++17 -o app main.cpp -lredis++ -lhiredis -pthread
./app

执行结果:
val
list: [a, b, c, a, b, c, a, b, c, a, b, c, a, b, c]
hash:[(field1,val1),(field,val),(field2,val2)]
set:(m1,m2,m3)
```