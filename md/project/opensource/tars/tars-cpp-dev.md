# Tars - Cpp开发

> 本节主要介绍Tars Cpp服务开发和编译时需要的开发环境。

[[toc]]

## 参考资料

* [tars项目介绍](https://tarscloud.gitbook.io/tarsdocs/)

* [tars_cpp_quickstart](https://github.com/TarsCloud/TarsDocs/blob/91fd046369b5f6fa43d02288ae2bf9be670fdb30/demo/tarscpp/tars_cpp_quickstart.md)

## 编译包依赖下载

```
yum install glibc-devel gcc gcc-c++ bison flex
yum install zlib-devel
yum -y install  libatomic
##cmake 需要单独安装3.0以上版本
```



## 下载项目源码

```
cd /home/klc/tars/
git clone https://github.com/TarsCloud/TarsCpp.git --recursive
cd ./TarsCpp/
git submodule update --init ##下载过程可能有些文件下载失败，可以进入TarsCpp文件夹后继续下载

mkdir build
cd build
cmake ..
make
make install

#gcc9.1需要修改的地方
ln -sf /usr/local/lib64/libstdc++.so.6.0.26 /lib64/libstdc++.so.6
直接把/lib64/libstdc++.so.6.0.19 移到其他路径下，创建上述软链接
```

# TarsCPP 快速入门

## 创建服务

```
cd /usr/local/tars/cpp/script/
./cmake_tars_server.sh TestApp HelloServer Hello
```

命令执行后，会在当前目录的/HelloServer/src 目录下，生成下面文件：

```
HelloServer.h HelloServer.cpp Hello.tars HelloImp.h HelloImp.cpp CMakeLists.txt
```

## 编译服务

```
cd ./HelloServer/build/
cmake ..
make -j4
```

## 服务实现

```
cd build
cmake ..
make -j4
make HelloServer-tar
make HelloServer-upload
```

重新make cleanall;make;make tar，会重新生成HelloServer.tgz发布包。

# 客户端同步/异步调用服务

```
mkdir -p /home/tarsproto/TestApp/HelloServer
make HelloServer-release
cd /home/tarsproto/
mkdir TestHelloClient
cd ./TestHelloClient/
touch main.cpp
touch makefile
make
./TestHelloClient
```

创建计算服务：

```
cd /usr/local/tars/cpp/script/
./cmake_tars_server.sh TestCalcApp CalcServer Calc
cd /usr/local/tars/cpp/script/CalcServer/build/
cmake ..
make -j4
make -j4
make CalcServer-tar
make cleanall;make;make tar
mkdir -p /home/tarsproto/TestCalcApp/CalcServer
make CalcServer-release
cd /home/tarsproto/
mkdir -p TestCalcClient
cd ./TestCalcClient/
touch main.cpp
touch makefile
```

同步与异步主要代码：

```cpp
int iRet = prx->testHello(sReq, sRsp);
cout<<"iRet:"<<iRet<<" sReq:"<<sReq<<" sRsp:"<<sRsp<<endl;

HelloPrxCallbackPtr cb = new HelloCallBack();
prx->async_testHello(cb, sReq);
cout<<" sReq:"<<sReq<<endl;

void HelloServer::initialize()
{
    //initialize application here:
    //...

    addServant<HelloImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".HelloObj");
}

服务框架中有全局的结构ServerConfig，它记录了服务的基本信息。
ServerConfig的成员变量都是静态的，在服务框架初始化时会自动从服务配置文件中初始化这些参数。
例如，在web界面——运维管理——服务部署下面，设置需要部署服务的一些信息，应用、服务名称、Obj等。
```

# 基于对象的接口处理

所谓基于对象接口的处理表示该命令接口是针对服务中的对象的。

例如针对CalcImp对象，这个时候如果发送一个命令给服务，则**每个线程中的CalcImp的命令接口都会被执行一次**，并且执行这些接口的过程和执行HelloImp的自身的接口是互斥的（即线程安全的）。

假设CalcImp有成员变量my_str，需要发送命令通知每个CalcImp对象将\_hello修改为自定义的值，步骤如下：

在CalcImp中增加处理函数

```cpp
bool CalcImp::setStr(const std::string& command, const std::string& params, std::string& result)
{
	TLOGDEBUG("CalcImp::setStr:"<<params<<endl);
	my_str = params;
    return true;
}

bool CalcImp::showStr(const std::string& command, const std::string& params, std::string& result)
{
	TLOGDEBUG("CalcImp::showStr:"<<my_str<<endl);
    return true;
}
```

在CalcImp的初始化中注册函数：

```cpp
void CalcImp::initialize()
{
    //initialize servant here:
    //...
	//注册处理函数：
    TARS_ADD_ADMIN_CMD_NORMAL("SETSTRING", CalcImp::setStr);
	TARS_ADD_ADMIN_CMD_NORMAL("SHOWSTRING", CalcImp::showStr);
}
```

# 注意事项

```
/usr/local/tars/cpp/script/cmake_tars_server.sh [App] [Server] [Servant]
##会生成所需代码框架

采用tars2cpp工具自动生成c++文件：/usr/local/tars/cpp/tools/tars2cpp Hello.tars会生成Hello.h文件，里面包含客户端和服务端的代码( 编译时会自动处理)。

即客户端和服务器都需要Hello.h

服务端:HelloImp是Servant的接口实现类，需要用户实现Hello.tars所定义的接口
客户端：引用Hello.h头文件，调用接口的函数来测试调用是否正常。

生成的Hello.h中包含多种代理的类定义 和 服务提供者的定义
HelloPrxCallback   		/* callback of async proxy for client */
HelloCoroPrxCallback	/* callback of coroutine async proxy for client */
HelloProxy				/* proxy for client */
Hello 					/* servant for server */

```

实际使用时，通过 通信器 Communicator 拿到代理对应的服务信息，然后进行调用。

```cpp
Communicator comm;

    try
    {
        HelloPrx prx;
        comm.stringToProxy("TestApp.HelloServer.HelloObj@tcp -h 172.25.0.3 -p 20001" , prx);

        try
        {
            string sReq("hello world");
            string sRsp("");

            int iRet = prx->testHello(sReq, sRsp);
            cout<<"iRet:"<<iRet<<" sReq:"<<sReq<<" sRsp:"<<sRsp<<endl;

        }
        catch(exception &ex)
        {
            cerr << "ex:" << ex.what() << endl;
        }
        catch(...)
        {
            cerr << "unknown exception." << endl;
        }
    }
```

