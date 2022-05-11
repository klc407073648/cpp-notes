# git配置公钥

# 参考资料

* [Centos7安装配置git公钥](https://blog.csdn.net/gexiaoyizhimei/article/details/93345587)
* [Docker + Jenkins 部署完整node项目](https://segmentfault.com/a/1190000021462867?utm_source=tag-newest)

# 配置过程

```
[root@iZuf61kbf845xt6tz10abgZ mytest]# git config --global user.name "klc407073648"
[root@iZuf61kbf845xt6tz10abgZ mytest]# git config --global user.email "407073648@qq.com"
[root@iZuf61kbf845xt6tz10abgZ mytest]# ssh-keygen -t rsa -C "407073648@qq.com"
Generating public/private rsa key pair.
Enter file in which to save the key (/root/.ssh/id_rsa):
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
Your identification has been saved in /root/.ssh/id_rsa.
Your public key has been saved in /root/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:RZtIY5QjEMNPQ0ALHidRScOlqkWgVeS9sgfTdPc0iA4 407073648@qq.com
The key's randomart image is:
+---[RSA 2048]----+
|. *X&Bo.=..      |
|.+ *+*+oo= +     |
|. o +oEo+.* o    |
| . . o.= o o .   |
|  o + o S   .    |
| o   =           |
|.   . .          |
|     .           |
|                 |
+----[SHA256]-----+
[root@iZuf61kbf845xt6tz10abgZ mytest]# cd ~/.ssh
[root@iZuf61kbf845xt6tz10abgZ .ssh]# ls
authorized_keys  id_rsa  id_rsa.pub  known_hosts
[root@iZuf61kbf845xt6tz10abgZ .ssh]# cat id_rsa.pub
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDfETihkb8YyUL5CQVDD4k+bHM3woZAkqUGEXpiCGh+BycGQ+nufH9QpvbHdGGhjxxe7t+kUgnc964nhx+a9Mrsq9nX1Kp0zppYV7L2vxaAClw4210NA50v2a17wOgnGVe59HIBwnxvgrY2E1qcHSkl/9AHulZwigOwTWXX9PL/E6ESElANLUpYzjR1GNrfMxQmjvDgiwy6b/xXW7ObHEKvoBBZ/UfgwlC4D30gRP+0WeoncsNOxRXk6uiSQcrmvLiE3dyoRbMUf7+6/SoYjewIUzl8ZCVH8YsV2WZWBrDbjeUEhxmZA7hbrfZf3qFHoXjMfr//UQqQo3htvGto90mT 407073648@qq.com

将上述公钥内容，配置到码云或github
```

