# 制作CAT-C++客户端 的docker镜像

## 参考资料

* [CAT-C++客户端集成Demo](https://blog.csdn.net/chentravelling/article/details/84614743)


## 制作CAT-C++的docker镜像

```
[root@iZuf61kbf845xt6tz10abgZ cat_cpp]# tree
.
├── build_cat_cpp.sh
├── build.sh
├── Dockerfile
└── environment
    ├── data
    │   └── appdatas
    │       └── cat
    │           └── client.xml
    ├── package
    │   └── cat-master.zip
    ├── shell
    │   └── build.sh
    └── src
        ├── main.cpp
        └── Makefile


整个构建过程，直接执行./build_cat_cpp.sh 即可

```

## 实践

```
[root@iZuf61kbf845xt6tz10abgZ cat_cpp]# docker run -it -d -v /etc/localtime:/etc/localtime --name cat_client_cplusplus docker.io/klc407073648/stibel_cat_cpp:v1.0
85cf4c457d71f848774bd1b3a2931d7bf713db80996b11505244430088509b66
[root@iZuf61kbf845xt6tz10abgZ cat_cpp]# docker exec -it cat_client_cplusplus bash
[root@85cf4c457d71 /]#
[root@85cf4c457d71 /]# cd /home/cat/mycat-client/src/
[root@85cf4c457d71 src]# ./catcpp
cppcat version: 3.0.0
encoder: 0
sampling: 1
multiprocessing: 0
heartbeat: 1
Using cat log file=/data/applogs/cat/cat_2022_04_09.logLog file has been opened in write mode by other process.
File: "/home/cat-master/lib/cpp/src/ccat/client_config.c", Line 128, in initCatClientConfig
2022-04-09 22:18:31  [95][[INFO] ] Current hostname: 85cf4c457d71
Using dataDir=/data/appdatas/cat/
Using CAT_HOME=/data/appdatas/cat/
Using client xml=/data/appdatas/cat/client.xml
File: "/home/cat-master/lib/cpp/src/ccat/message_manager.c", Line 83, in initMessageManager
2022-04-09 22:18:31  [95][[INFO] ] Current ip: 172.17.0.3
File: "/home/cat-master/lib/cpp/src/ccat/message_manager.c", Line 94, in initMessageManager
2022-04-09 22:18:31  [95][[INFO] ] Current ip hex: ac110003
File: "/home/cat-master/lib/cpp/src/ccat/server_connection_manager.c", Line 209, in getRouterFromServer
2022-04-09 22:18:31  [95][[INFO] ] Start connect to router server 139.196.82.84 : 8080.
File: "/home/cat-master/lib/cpp/src/ccat/server_connection_manager.c", Line 225, in getRouterFromServer
2022-04-09 22:18:31  [95][[INFO] ] Connect to router server 139.196.82.84 : 8080 Success.
File: "/home/cat-master/lib/cpp/src/ccat/server_connection_manager.c", Line 264, in getRouterFromServer
2022-04-09 22:18:31  [95][[INFO] ] Got available server list:
{"kvs":{"startTransactionTypes":"Cache.;Squirrel.","block":"false","routers":"139.196.82.84:2280;","sample":"1.0","matchTransactionTypes":"SQL"}}
File: "/home/cat-master/lib/cpp/src/ccat/aggregator.c", Line 53, in setSampleRate
2022-04-09 22:18:31  [95][[INFO] ] cat client sample rate has been set to 1.000000
File: "/home/cat-master/lib/cpp/src/ccat/server_connection_manager.c", Line 388, in updateCatServerConn
2022-04-09 22:18:31  [95][[DEBUG] ] Get router from server successfully
File: "/home/cat-master/lib/cpp/src/ccat/server_connection_manager.c", Line 395, in updateCatServerConn
2022-04-09 22:18:31  [95][[DEBUG] ] Trying connecting to the best server
File: "/home/cat-master/lib/cpp/src/ccat/server_connection_manager.c", Line 61, in tryConnBestServer
2022-04-09 22:18:31  [95][[INFO] ] Try connect to server 139.196.82.84:2280.
File: "/home/cat-master/lib/cpp/src/ccat/server_connection_manager.c", Line 71, in tryConnBestServer
2022-04-09 22:18:31  [95][[INFO] ] Connect success.
File: "/home/cat-master/lib/cpp/src/ccat/client.c", Line 154, in catClientInitWithConfig
2022-04-09 22:18:31  [95][[INFO] ] Cat has been initialized with appkey: cat_cpp_client
0
1
2
3
4
5
6
7
8
9
finish
[root@85cf4c457d71 src]#
```

界面查看：
![cat_cpp_out](/_images/micro-services/middleware/cat/cat_cpp_out.png)