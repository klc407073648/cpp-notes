# Tools - curl使用方法

[[toc]]

# 参考

* [curl 命令详解](https://blog.csdn.net/Lakers2015/article/details/128627020)

# 概述

curl 是常用的命令行工具，用来请求 Web 服务器。它的名字就是客户端（client）的 URL 工具的意思。它的功能非常强大，命令行参数多达几十种。如果熟练的话，完全可以取代 Postman 这一类的图形界面工具。如果在一个curl命令中不指定具体的方法，那么默认的就是使用GET方法。对于其它的方法，可以在curl命令中指定：

语法：

curl [option] [url]

```shell
[root@VM-16-6-centos ~]# curl -h
Usage: curl [options...] <url>
Options: (H) means HTTP/HTTPS only, (F) means FTP only
     --anyauth       Pick "any" authentication method (H)
 -a, --append        Append to target file when uploading (F/SFTP)
     --basic         Use HTTP Basic Authentication (H)
     --cacert FILE   CA certificate to verify peer against (SSL)
     --capath DIR    CA directory to verify peer against (SSL)
 -E, --cert CERT[:PASSWD] Client certificate file and password (SSL)
     --cert-type TYPE Certificate file type (DER/PEM/ENG) (SSL)
     --ciphers LIST  SSL ciphers to use (SSL)
     --compressed    Request compressed response (using deflate or gzip)
 -K, --config FILE   Specify which config file to read
     --connect-timeout SECONDS  Maximum time allowed for connection
 -C, --continue-at OFFSET  Resumed transfer offset
 -b, --cookie STRING/FILE  String or file to read cookies from (H)
 -c, --cookie-jar FILE  Write cookies to this file after operation (H)
     --create-dirs   Create necessary local directory hierarchy
     --crlf          Convert LF to CRLF in upload
     --crlfile FILE  Get a CRL list in PEM format from the given file
 -d, --data DATA     HTTP POST data (H)
```

Curl支持:

![](/_images/devops/tools/curl_support.png)

# 基本使用方法

打印出服务器回应的 HTTP Header

![](/_images/devops/tools/curl_baidu.png)

保存访问的网页

使用linux的重定向功能保存

`curl http://www.baidu.com >> baidu.html`

可以使用curl的内置选项 -o (小写) 保存网页

`curl -o baidu.html http://www.baidu.com`

测试网页返回值(响应码)

```
[root@VM-16-6-centos ~]# curl -o /dev/null -s -w %{http_code} www.baidu.com
200
```

模仿浏览器

`curl -A "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.0)" http://www.linux.com`

curl下载文件

```shell
[root@VM-16-6-centos curltest]# curl -o bmw.jpg https://scpic.chinaz.net/files/pic/pic9/202205/apic40779.jpg
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100  339k  100  339k    0     0  1029k      0 --:--:-- --:--:-- --:--:-- 1031k
[root@VM-16-6-centos curltest]# ls -al
total 348
drwxr-xr-x  2 root root   4096 Aug 25 11:04 .
drwxr-xr-x 19 root root   4096 Aug 25 11:00 ..
-rw-r--r--  1 root root 347388 Aug 25 11:04 bmw.jpg
```

-v 输出通信的整个过程，用于调试。

![](/_images/devops/tools/curl_v.png)

