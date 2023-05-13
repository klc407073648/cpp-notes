# Docker - Dockerfile学习

[[toc]]

## 参考资料

* [使用docker部署一个简单的c/c++程序的方法](https://freexyz.cn/server/60289.html)
* [dockerfile——EXPOSE和端口映射参数-p、-P总结](https://blog.csdn.net/qq_17639365/article/details/86655177)

## 一、首先建立一个 hello-world.cpp 文件

```cpp
#include <iostream>
using namespace std;

int main () {
	cout << "hello-world" << endl;
	cout << "my first docker" << endl;
	return 0;
}
```

## 二、编写DockerFile文件

```
FROM codenvy/cpp_gcc 

RUN mkdir /home/user/myapp

ADD hello-world.cpp /home/user/myapp
ADD cmakeTest.tar.gz /home/user/myapp
ADD start.sh /home/user/myapp

WORKDIR /home/user/myapp

RUN g++ hello-world.cpp -o hello

ENV LD_LIBRARY_PATH /home/user/myapp/cmakeTest/comlib/3part/jsoncpp/lib:$LD_LIBRARY_PATH
ENV PATH /home/user/myapp/cmakeTest/comlib/3part/jsoncpp/lib:$PATH

CMD ["./hello"]
CMD ["./start.sh"]

EXPOSE 9950
```

具体含义
```
1、FROM codenvy/cpp_gcc
FROM是后面是该目标镜像使用的基础镜像。

2、RUN mkdir /home/user/myapp

RUN命令是容器构建时需要的命令，后面带有的就是我们常见的linux命令。

该命令就是在 /home/user 路径下新建一个 myapp 文件夹

3、ADD hello-world.cpp /home/user/myapp

ADD命令是将宿主机下的文件拷贝到镜像，也可以用COPY命令，不过ADD比COPY的功能更强大，ADD带有解压缩的功能。

该命令就是将第一步新建的 hello-world.cpp 源文件拷贝到镜像中的/home/user/myapp 路径下。

4、WORKDIR /home/user/myapp

WORKDIR命令就是指定创建容器时，容器的默认工作目录。

该命令将镜像中的 home/user/myapp 路径作为默认工作路径。

5、RUN g++ hello-world.cpp -o hello

该命令是使用g++编译 hello-world.cpp 源文件，构建一个可执行文件hello

6、CMD ["./hello"]

CMD是指定容器创建完成后第一个运行的命令。

该命令是运行上一步构建的可执行文件 hello
```

## 三、创建镜像

上述两个文件都放在/home/docker/路径下, 使用命令:

```
#docker build -f ./hello-dockerfile -t my_hello_docker:v1.0 .

[root@192 docker]# docker build -f ./hello-dockerfile -t my_hello_docker .
./hello-dockerfile: Dockerfile的所在位置
my_hello_docker:  新建的镜像的名字
v1.0:该镜像的标签。
```

## 四、通过该镜像运行一个容器

通过以下命令实例化一个容器:
```
[root@192 deploy]# docker run -it my_hello_docker bash
user@cc376d7c7865:~/myapp$

```


## 五、实践内容

端口映射，只能在宿主机上访问对应小网地址
```
因为dockerfile里面作了端口映射
EXPOSE 9950

在容器里:
[root@192 docker]# docker run -it my_hello_docker bash
user@43d6acc9aa4d:~/myapp$ cd ./cmakeTest/deploy/
user@43d6acc9aa4d:~/myapp/cmakeTest/deploy$ hostname -i
172.17.0.5
user@43d6acc9aa4d:~/myapp/cmakeTest/deploy$ ./myprj
_PTHREADS is not defined !
RequestData()
mem:comments value:[]
...

在宿主机,能通过小网地址访问容器里的资源文件:
[root@192 V5]# curl 172.17.0.5:9950
<html><title>哎~出错了</title><body bgcolor="ffffff">404 Not Found!<hr><em> STLBE's Web Server</em>
</body></html>[root@192 V5]# curl 172.17.0.5:9950/profile

{
        "author" : "Still",
        "title" : "hello world"
}
```


容器端口和宿主机映射:

将容器的9950端口映射到192.168.2.231:7001
```
[root@192 docker]# docker run -d --name my_hello_docker_1 -p 192.168.2.231:7001:9950 my_hello_docker
5e5947f49acd5702d59ae6659a05810b03bcf37ac93a9506fc6364ee0f413e32
[root@192 docker]# docker exec -it 5e5947f49ac bash
user@5e5947f49acd:~/myapp$
```

在postman上测试图如下:

![1](/_images/devops/docker/postman测试.png)


tips:

```
docker容器刚运行就自动退出了:
在网上查了原因后，Docker容器后台运行,就必须有一个前台进程，容器运行的命令如果不是那些一直挂起的命令（比如运行top，tail），就是会自动退出的。

docker run -d --name my_hello_docker_1 -p 192.168.2.231:7001:9950 my_hello_docker ping 8.8.8.8

删除已经退出的容器:
[root@192 V5]# docker rm $(docker ps -q -f status=exited)
43d6acc9aa4d

```
