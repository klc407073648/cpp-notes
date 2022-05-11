# hiredis使用

1.hiredis下载
https://github.com/redis/hiredis/releases    下载最新版本hiredis-0.14.1.tar.gz

2.安装hiredis

ssh 远程登录虚机，将下载的版本包放置指定目录
```
cd /home/believe123/myproject/hiredis/
tar -zxf hiredis-0.14.1.tar.gz
cd ./hiredis-0.14.1/
make
make install //将.h和.so拷贝到指定路径下，便于调用
```

3.测试能否正常使用

首先执行
```
[root@192 mytest]# cp /home/believe123/myproject/hiredis/hiredis-0.14.1/examples/example.c  /home/believe123/myproject/hiredis/mytest/
[root@192 mytest]# gcc -o  example example.c -I/usr/local/include/hiredis -L/usr/local/lib/ -lhiredis

export LD_LIBRARY_PATH=/home/klc/V6/build_comlib/hiredis/output/usr/local/lib:$LD_LIBRARY_PATH


g++ -o  testApp testApp.cpp -I/usr/local/include/cppunit -L/usr/local/lib/ -lcppunit -ldl 

[root@192 mytest]# ./example
PING: PONG
SET: OK
SET (binary API): OK
GET foo: hello world
INCR counter: 3
INCR counter: 4
0) element-9
1) element-8
2) element-7
3) element-6
4) element-5
5) element-4
6) element-3
7) element-2
8) element-1
9) element-0

```



