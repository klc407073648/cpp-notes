# Nginx应用 - 在centOs 上搭建nginx来部署静态页面网站

[[toc]]

## Nginx简介

轻量级、高性能的HTTP及反向代理服务器，占用内存少，并发能力强。

## 安装以及使用

### 安装以及启动

```
yum install nginx -y
nginx -v
```

nginx 

## 配置服务器的访问地址
启动好的nginx服务器默认访问的是它自己的目录，即/usr/share/nginx/html目录，可以在/etc/nginx/nginx.conf配置文件中配置你自己的项目目录，并让nginx正确访问。

主要修改以下字段：
```
    server {
        listen       90 default_server ;      #监听的默认端口
        listen       [::]:90 default_server;
        #server_name  www.klc.com;       #服务器名称，默认为localhost
        root         /home/Believe/nginx;  #修改root默认目录

        # Load configuration files for the default server block.
        include /etc/nginx/default.d/*.conf;

        location / {
           root /home/Believe/nginx;
           index first.html;     #访问的网址为first.html，不写默认为index.html
        }

        error_page 404 /404.html;
            location = /40x.html {
        }

        error_page 500 502 503 504 /50x.html;
            location = /50x.html {
        }
}

```
### 新建一个目录路径，创建index.html
```html
// index.html代码为
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>hello world</title>
</head>
<body>
Hello world！
</body>

```

## 重启nginx，访问

```
nginx -s reload
浏览器中输入：http://127.0.0.1:90/
```