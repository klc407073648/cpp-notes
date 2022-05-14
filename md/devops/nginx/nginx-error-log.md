# Nginx错误日志配置及信息详解

[[toc]]

## 1.Nginx错误日志信息介绍

Nginx的错误信息是调试Nginx服务的重要手段，属于核心功能模块（ngx_core_module）的参数，该参数的名字为error_log，可以放在Main区块中全局配置，也可以放在不同的虚拟主机中单独记录虚拟主机的错误信息

error_log的默认值：
```
#error_log  logs/error.log  error;
```

error_log的语法格式及参数语法说明如下:
```
    error_log    <FILE>    <LEVEL>;

    关键字        日志文件   错误日志级别

    关键字：其中关键字error_log不能改变

    日志文件：可以指定任意存放日志的目录

    错误日志级别：常见的错误日志级别有[debug | info | notice | warn | error | crit | alert | emerg]，级别越高记录的信息越少。

    生产场景一般是 warn | error | crit 这三个级别之一
```

error_log参数的标签段位置：
```
main, http, server, location
```

## 2.Nginx配置错误日志过程介绍

1. 插入error_log语句
```
server {
        listen       80;
        server_name  localhost;

        location / {
                root test;
                index index.html 
        }

        error_log  logs/error_test.log  info;
        #新增内容↑
}
```

2. 重启服务
```
nginx -t
#结果显示ok和success没问题便可重启
nginx -s reload
```

3. 查看错误日志文件
```
cd /usr/share/nginx/logs
tail -f error_test.log
```

