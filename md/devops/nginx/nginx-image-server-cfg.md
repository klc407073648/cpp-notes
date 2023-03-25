# Nginx应用 -nginx图片服务器配置

[[toc]]

# 参考资料

* [基于Docker搭建Nginx图片服务器](https://www.cnblogs.com/lyuzt/p/12575390.html)
* [linux下docker的安装及卸载](https://blog.csdn.net/weixin_43124843/article/details/100659286)
* [Linux上搭建图片服务器(Docker 安装的nginx,解决404)](https://www.cnblogs.com/sunxun/p/13451979.html)

# 配置过程

```
docker run -d -p 8081:80 --name nginx-server -v /home/stibel/nginx/html:/usr/share/nginx/html -v /home/stibel/nginx/conf/nginx.conf:/etc/nginx/conf.d/nginx.conf -v /home/stibel/nginx/logs:/var/log/nginx -v /home/stibel/nginx/conf.d/etc/nginx/conf.d nginx
```

nginx.conf文件：

```
#图片服务器
server {
    listen       80;
    server_name  localhost;
    charset utf-8;
    access_log  /var/log/nginx/img.access.log main;
    location /images/ {
        alias  /usr/share/nginx/html/images;#ok
        autoindex on; ##显示索引
        autoindex_exact_size on; ##显示大小
        autoindex_localtime on; ##显示时间
 
    }
    error_page  404              /404.html;
}
```

访问：

```
http://81.68.132.31:8081/images/1.png
```



