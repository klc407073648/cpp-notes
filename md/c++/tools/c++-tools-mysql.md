# Centos下mysql安装以及使用

## 参考资料

* [centos7安装mysql5.7（rpm安装版）](https://www.cnblogs.com/helf/p/11244711.html)
* [MySQL安装以及登陆密码修改](https://blog.csdn.net/baidu_15952103/article/details/106597159)
* [mysql5.7初始化密码报错](https://blog.csdn.net/memory6364/article/details/82426052)

## mysql下载以及安装

```
wget http://repo.mysql.com/mysql57-community-release-el7-10.noarch.rpm

rpm -Uvh mysql57-community-release-el7-10.noarch.rpm

yum install  -y  mysql-community-server

systemctl start mysqld.service

环境安装：

yum install cmake

yum -y install gcc+ gcc-c++

yum install mysql-devel   解决mysql.h库
```

## rpm版本安装

参考链接：
```
tar -xvf mysql-5.7.33-1.el7.x86_64.rpm-bundle.tar
rpm -ivh mysql-community-common-5.7.33-1.el7.x86_64.rpm
rpm -ivh mysql-community-libs-5.7.33-1.el7.x86_64.rpm
rpm -ivh mysql-community-client-5.7.33-1.el7.x86_64.rpm
rpm -ivh mysql-community-server-5.7.33-1.el7.x86_64.rpm (yum  install    numactl)
rpm -ivh mysql-community-devel-5.7.33-1.el7.x86_64.rpm 
```
```
mysql -u root -p
vi  /etc/my.cnf
systemctl restart mysqld.service
mysql
vi  /etc/my.cnf
systemctl restart mysqld.service
mysql
mysql -u root -p
```

问题记录：

```
在PATH中加入
/usr/include/
```
```
一开始一直找不到mysqlclient，对应路径是/usr/lib64/mysql/libmysqlclient.so

/usr/bin/ld: cannot find -lmysqlclient

之前尝试 export LD_LIBRARY_PATH=/usr/lib64/mysql 方法无效

至于为什么找不到lmysqlclient库，是因为编译找的动态库是根据去找/usr/lib文件夹下的库，
因此，需要将在/usr/lib/下加入mysql库文件

创建软连接：
[root@VM-0-10-centos mysql]# ll /usr/lib64/mysql/libmysqlclient.so
lrwxrwxrwx 1 root root 20 Feb  7 22:13 /usr/lib64/mysql/libmysqlclient.so -> libmysqlclient.so.20

sudo ln -sv /usr/lib64/mysql/libmysqlclient.so.20 /usr/lib/libmysqlclient.so

cp -r /usr/lib64/mysql/* /usr/lib/

```


