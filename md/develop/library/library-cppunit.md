# cppunit使用

[[toc]]

```bash
cd /home/tools/cppunit/
tar  -zxf cppunit-1.12.1.tar.gz
cd ./cppunit-1.12.1/
./configure
make
make install
```


[root@VM-0-10-centos cppunit]# export LD_LIBRARY_PATH=/usr/local/lib
[root@VM-0-10-centos cppunit]# g++ -o  testApp testApp.cpp -I/usr/local/include/cppunit -L/usr/local/lib -lcppunit -ldl
[root@VM-0-10-centos cppunit]# ./testApp
Test::testHelloWorldHello, world!
 : OK
 
[root@VM-0-10-centos cppunit]# g++ -o  simpleTest simpleTest.cpp -I/usr/local/include/cppunit -L/usr/local/lib -lcppunit -ldl
[root@VM-0-10-centos cppunit]# ./simpleTest

!!!FAILURES!!!
Test Results:
Run:  1   Failures: 1   Errors: 0


1) test:  (F) line: 13 simpleTest.cpp
equality assertion failed
- Expected: 0
- Actual  : 1



相关网址：
https://github.com/niceSimon7/HowToUseCppUnit


CppUnit快速入门:
https://blog.csdn.net/wyyy2088511/article/details/80107131?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522161744929916780271540473%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=161744929916780271540473&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-3-80107131.pc_search_result_before_js&utm_term=cppunit

cppunit使用详解
https://www.cnblogs.com/zhoug2020/p/4515729.html


[root@VM-0-10-centos ~]# cd /home/tools/cppunit/v1/
[root@VM-0-10-centos v1]# g++ -o  SimpleTest SimpleTest.cpp main.cpp -I/usr/local/include/cppunit -L/usr/local/lib -lcppunit -ldl
