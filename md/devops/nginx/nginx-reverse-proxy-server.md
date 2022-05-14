# nginx反向代理服务器

[[toc]]

## niginx正向代理与反向代理概念
nginx能够提供以下几种服务：

* http服务器
    * 能处理http协议
* 反向代理服务器
* 邮件服务器
    * IMAP/POP3/SMTP

## 正向代理

1. 代理内部网络对Internet的连接请求
2. 客户机必须指定代理服务器
3. 代理服务器是为用户服务的

![正向代理](/_images/devops/nginx/正向代理.png)

## 反向代理

1. 以代理服务器来接受Internet上的连接请求
2. 将请求转发给内部网络上的服务器
3. 将服务器上得到的结果返回给Internet上请求连接的客户端

![反向代理](/_images/devops/nginx/反向代理.png)

## 两者的区别

正向代理:
    * 典型用途是为在防火墙内的局域网客户端提供访问Internet的途径。
    * 正向代理还可以使用缓冲特性减少网络使用率。
反向代理:
    * 典型用途是将防火墙后面的服务器提供给Internet用户访问。
    * 反向代理还可以为后端的多台服务器提供负载平衡，或为后端较慢的服务器提供缓冲服务。

## 反向代理服务器简单实例

设计思路：

利用windows机器搭建nginx反向代理服务器，为创建的两个虚机的nginx的web服务器提供代理服务。

1. 远程登录192.168.2.230和192.168.2.231虚机，启动nginx服务

```bash
[root@192 ~]# systemctl stop httpd
[root@192 ~]# systemctl stop firewalld.service
[root@192 ~]# /usr/local/nginx/sbin/nginx
```

2. 校验是否能在window机器上访问对应IP地址：

![访问ip地址校验1](/_images/devops/nginx/访问ip地址校验1.png)
![访问ip地址校验2](/_images/devops/nginx/访问ip地址校验2.png)

3. 在window上启动nginx反向代理服务器，设置文件nginx.conf

```
设计的格式如下： 	

    #设置反向代理
	upstream myprj.test{
	   server 192.168.2.230:80;  
	}
	
	
	#要配置代理的服务器信息
	# myprj.com - 192.168.2.230 
    server {
        listen       80;
        server_name  myprj.com;

        location / {
            #设置代理
            proxy_pass http://myprj.test;
        }
	}
```

此外还需要手动修改windows机器上的C:\Windows\System32\drivers\etc 下的hosts文件，使得IP和主机名成映射关系。
```
192.168.2.230  myprj.com
192.168.2.231  myweb.com
```

4. 使用对应域名访问nginx服务器，如果能够访问成功，表明反向代理服务器搭建完成。

![通过域名访问](/_images/devops/nginx/通过域名访问.png)

## 负载均衡实例

修改nginx.conf文件的内容：
```
   #设置反向代理
	upstream linux.test{
	   server 192.168.2.230:80; 
	   server 192.168.2.231:80;  	   
	}
	

	#要配置代理的服务器信息
    server {
        listen       80;
        server_name  localhost;

        location / {
            #设置代理
            proxy_pass http://linux.test;
        }
	}
```

可以直接通过http://localhost/  网址 均等机会访问192.168.2.230:80 和192.168.2.231:80 的nginx服务器。

进一步，修改对应服务器的权值，使得性能高的服务器，更大几率被访问。
```
#设置反向代理
	upstream linux.test{
	   server 192.168.2.230:80 weight=5; 
	   server 192.168.2.231:80 weight=1;  	   
	}
```