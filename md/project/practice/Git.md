# Linux下git安装以及配置

## 参考资料

* [linux配置Git公钥](https://blog.csdn.net/chujing2309/article/details/100758680)

## 前提

* 安装git
    * yum install -y git

## 具体配置过程

步骤：

1. 配置git全局用户名和email
2. 生成ssh key——三次回车，会提示公钥文件id_rsa.pub的存储路径
3. 查看公钥，并在github上配置SSH keys

```bash
[root@VM-0-10-centos project]# git config --global user.name "klc407073648"
[root@VM-0-10-centos project]# git config --global user.email "407073648@qq.com"
[root@VM-0-10-centos project]# ssh-keygen -t rsa -C "407073648@qq.com"
Generating public/private rsa key pair.
Enter file in which to save the key (/root/.ssh/id_rsa):
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
Your identification has been saved in /root/.ssh/id_rsa.
Your public key has been saved in /root/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:nzG9s6RgkBfIQ98dEUlif69AalQArkvDCwD8YM6Ryik 407073648@qq.com
The key's randomart image is:
+---[RSA 2048]----+
|o .   . ..+o*+   |
| B   o + o =..   |
|* *   + + o + .  |
|E= o . + o + . . |
|.   . B S = o   .|
|     o * o + o . |
|      o o o + .  |
|       . . o o   |
|          . .    |
+----[SHA256]-----+
[root@VM-0-10-centos .ssh]# vi /root/.ssh/id_rsa.pub

```

github配置公钥：

![1](/_images/project/practice/Git/公钥配置.png)
