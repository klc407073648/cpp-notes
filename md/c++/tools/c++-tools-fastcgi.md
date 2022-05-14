# fastcgi

[[toc]]

[root@master01 build_lib]# gcc -o fastcgi_test fastcgi_test.cpp -I/home/build_lib/include/3partlib/fastcgi/include/ -L/home/build_lib/lib/3partlib -lfcgi
[root@master01 build_lib]# ./fastcgi_test
./fastcgi_test: error while loading shared libraries: libfcgi.so.0: cannot open shared object file: No such file or directory
[root@master01 build_lib]# export LD_LIBRARY_PATH=/home/build_lib/lib/3partlib:$LD_LIBRARY_PATH [root@master01 build_lib]# ./fastcgi_test
Content-type: text/html

<title>FastCGI Hello!</title><h1>FastCGI Hello!</h1>Request number 1 running on host <i>(null)</i>
[root@master01 build_lib]#
