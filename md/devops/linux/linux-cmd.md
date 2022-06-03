# Linux常用命令大全

[[toc]]

## 参考资料


# 系统信息 

```bash
arch                        # 显示机器的处理器架构(1)   x86_64
uname -m                    # 显示机器的处理器架构(2)   x86_64
uname -r                    # 显示正在使用的内核版本    3.10.0-862.14.4.el7.x86_64
cat /proc/cpuinfo           # 显示CPU info的信息 
cat /proc/interrupts        # 显示中断 
cat /proc/meminfo           # 校验内存使用 
date                        # 显示系统日期 
```

显示内核的版本:
```
[root@iZuf61kbf845xt6tz10abgZ ~]# cat /etc/*release
CentOS Linux release 7.5.1804 (Core)
NAME="CentOS Linux"
VERSION="7 (Core)"
ID="centos"
ID_LIKE="rhel fedora"
VERSION_ID="7"
PRETTY_NAME="CentOS Linux 7 (Core)"
ANSI_COLOR="0;31"
CPE_NAME="cpe:/o:centos:centos:7"
HOME_URL="https://www.centos.org/"
BUG_REPORT_URL="https://bugs.centos.org/"
```

# 关机 (系统的关机、重启以及登出 ) 

```bash
shutdown -h now                 # 关闭系统(1) 
init 0                          # 关闭系统(2) 
telinit 0                       # 关闭系统(3) 
shutdown -h hours:minutes &     # 按预定时间关闭系统 
shutdown -c                     # 取消按预定时间关闭系统 
shutdown -r now                 # 重启(1) 
reboot                          # 重启(2) 
logout                          # 注销 
```

# 文件和目录 

```bash
cd /home                     # 进入 '/ home' 目录' 
cd ..                        # 返回上一级目录 
cd ../..                     # 返回上两级目录 
cd -                         # 返回上次所在的目录
pwd                          # 显示工作路径 
ls                           # 查看目录中的文件 
ls -F                        # 查看目录中的文件 
ls -l                        # 显示文件和目录的详细资料 
ls -a                        # 显示隐藏文件 
ls *[0-9]*                   # 显示包含数字的文件名和目录名 
tree                         # 显示文件和目录由根目录开始的树形结构(1) 
lstree                       # 显示文件和目录由根目录开始的树形结构(2) 
mkdir dir1                   # 创建一个叫做 'dir1' 的目录' 
mkdir dir1 dir2              # 同时创建两个目录 
mkdir -p /tmp/dir1/dir2      # 创建一个目录树 
rm -f file1                  # 删除一个叫做 'file1' 的文件' 
rmdir dir1                   # 删除一个叫做 'dir1' 的目录' 
rm -rf dir1                  # 删除一个叫做 'dir1' 的目录并同时删除其内容 
rm -rf dir1 dir2             # 同时删除两个目录及它们的内容 
mv dir1 new_dir              # 重命名/移动 一个目录 
cp file1 file2               # 复制一个文件 
cp -rf dir/* .               # 复制一个目录下的所有文件到当前工作目录 
cp -a /tmp/dir1 .            # 复制一个目录到当前工作目录 
cp -a dir1 dir2              # 复制一个目录 
ln -s file1 lnk1             # 创建一个指向文件或目录的软链接 
ln file1 lnk1                # 创建一个指向文件或目录的物理链接 
```
 
# 文件搜索 

find:

作用： 按文件结构遍历搜素，找到符合条件的文件并按照相应的操作来展现

格式：

```
find option [expression]
```

OPTIONS说明：
* -name	按名称寻找文件
* -exec	找到文件后再执行exec命令后面的操作
* -type	按类型查找文件
* -print	输出找到的文件的信息
* -user	按所有者（文件的主人）来查找文件
* -mtime -n +n	根据修改时间找到文件

备注：
在使用 find命令的-exec选项处理匹配到的文件时， find命令将所有匹配到的文件一起传递给exec执行。但有些系统对能够传递给exec的命令长度有限制，这样在find命令运行几分钟之后，就会出现溢出错误。错误信息通常是“参数列太长”或“参数列溢出”。这就是xargs命令的用处所在，特别是与find命令一起使用。


```bash
find / -name file1                                              # 从 '/' 开始进入根文件系统搜索文件和目录 
find / -user user1                                              # 搜索属于用户 'user1' 的文件和目录 
find /home/user1 -name \*.bin                                   # 在目录 '/ home/user1' 中搜索带有'.bin' 结尾的文件 
find /usr/bin -type f -atime +100                               # 搜索在过去100天内未被使用过的执行文件 
find /usr/bin -type f -mtime -10                                # 搜索在10天内被创建或者修改过的文件 
find ./ -name \*.sh -exec chmod 777 '{}' \;                     # 搜索以 '.sh' 结尾的文件并定义其权限777                        
find /home/klc/shell/ -type f -mmin +20  -exec rm {} \;         # 删除20分钟前的文件
find /home/klc/shell/ -type f -mmin +20  -exec ls -l {} \;      # 显示20分钟前的文件
find . -type f -print | xargs file                              # 查找系统中的每一个普通文件，然后使用xargs命令来测试它们分别属于哪类文件

whereis halt                                                    # 显示一个二进制文件、源码或man的位置 
which halt                                                      # 显示一个二进制文件或可执行文件的完整路径 

grep -rn "query_string" *                                       # Linux目录下全局查找所有文件中是否包含指定字符串（-r：递归；-n：显示行号）
```
Linux命令（三）find,xargs
https://blog.csdn.net/lingfy1234/article/details/107453631
https://baijiahao.baidu.com/s?id=1704821742084725538&wfr=spider&for=pc

命令大全
https://blog.csdn.net/liuwei0376/article/details/88245472
https://blog.csdn.net/lydms/article/details/101368670


# 打包和压缩文件 

```bash
tar -zcvf archive.tar.gz ./dir1                 # 把当前文件夹下的dir1文件夹打包成archive.tar.gz 
tar -zxvf archive.tar.gz                        # 把target.tar.gz解压到当前文件夹 
zip file1.zip file1                             # 创建一个zip格式的压缩包 
zip -r file1.zip file1 file2 dir1               # 将几个文件和目录同时压缩成一个zip格式的压缩包 
unzip file1.zip                                 # 解压一个zip格式压缩包    
```

# OS包管理器

## RPM 包-（Fedora, Redhat及类似系统）

```bash
rpm -ivh package.rpm 安装一个rpm包 
rpm -ivh --nodeps package.rpm 安装一个rpm包而忽略依赖关系警告 
rpm -U package.rpm 更新一个rpm包但不改变其配置文件 
rpm -F package.rpm 更新一个确定已经安装的rpm包 
rpm -e [--nodeps] package_name.rpm 删除一个rpm包[--nodeps表示忽略依赖关系] 
rpm -qa 显示系统中所有已经安装的rpm包 
rpm -qa | grep httpd 显示所有名称中包含 "httpd" 字样的rpm包 
rpm -qi package_name 获取一个已安装包的特殊信息 
rpm -qg "System Environment/Daemons" 显示一个组件的rpm包 
rpm -ql package_name 显示一个已经安装的rpm包提供的文件列表 
rpm -qc package_name 显示一个已经安装的rpm包提供的配置文件列表 
rpm -q package_name --whatrequires 显示与一个rpm包存在依赖关系的列表 
rpm -q package_name --whatprovides 显示一个rpm包所占的体积 
rpm -q package_name --scripts 显示在安装/删除期间所执行的脚本l 
rpm -q package_name --changelog 显示一个rpm包的修改历史 
rpm -qf /etc/httpd/conf/httpd.conf 确认所给的文件由哪个rpm包所提供 
rpm -qp package.rpm -l 显示由一个尚未安装的rpm包提供的文件列表 
rpm --import /media/cdrom/RPM-GPG-KEY 导入公钥数字证书 
rpm --checksig package.rpm 确认一个rpm包的完整性 
rpm -qa gpg-pubkey 确认已安装的所有rpm包的完整性 
rpm -V package_name 检查文件尺寸、 许可、类型、所有者、群组、MD5检查以及最后修改时间 
rpm -Va 检查系统中所有已安装的rpm包- 小心使用 
rpm -Vp package.rpm 确认一个rpm包还未安装 
rpm2cpio package.rpm | cpio --extract --make-directories *bin* 从一个rpm包运行可执行文件 
rpm -ivh /usr/src/redhat/RPMS/`arch`/package.rpm 从一个rpm源码安装一个构建好的包 
rpmbuild --rebuild package_name.src.rpm 从一个rpm源码构建一个 rpm 包 
```

## YUM 软件包升级器-（Fedora, RedHat及类似系统）

```bash
yum install package_name                # 下载并安装一个rpm包 (如: yum -y install zip unzip)
yum localinstall package_name.rpm       # 将安装一个rpm包，使用你自己的软件仓库为你解决所有依赖关系 
yum update package_name.rpm             # 更新当前系统中所有安装的rpm包 
yum update package_name                 # 更新一个rpm包 
yum remove package_name                 # 删除一个rpm包 
yum list | grep tmux                    # 列出所有可安裝的软件清单命令
yum search package_name                 # 在rpm仓库中搜寻软件包 
yum clean packages                      # 清理rpm缓存删除下载的包 
yum clean headers                       # 删除所有头文件 
yum clean all                           # 删除所有缓存的包和头文件 
```

## DEB 包 (Debian, Ubuntu 以及类似系统) 

```bash
dpkg -i package.deb                      # 安装/更新一个 deb 包 
dpkg -r package_name                     # 从系统删除一个 deb 包 
dpkg -l                                  # 显示系统中所有已经安装的 deb 包 
dpkg -l | grep httpd                     # 显示所有名称中包含 "httpd" 字样的deb包 
dpkg -s package_name                     # 获得已经安装在系统中一个特殊包的信息 
dpkg -L package_name                     # 显示系统中已经安装的一个deb包所提供的文件列表 
dpkg --contents package.deb              # 显示尚未安装的一个包所提供的文件列表 
dpkg -S /bin/ping                        # 确认所给的文件由哪个deb包提供 
```

## APT 软件工具 (Debian, Ubuntu 以及类似系统) 

```bash
apt-get install package_name             # 安装/更新一个 deb 包 
apt-cdrom install package_name           # 从光盘安装/更新一个 deb 包 
apt-get update                           # 升级列表中的软件包 
apt-get upgrade                          # 升级所有已安装的软件 
apt-get remove package_name              # 从系统删除一个deb包 
apt-get check                            # 确认依赖的软件仓库正确 
apt-get clean                            # 从下载的软件包中清理缓存 
apt-cache search searched-package        # 返回包含所要搜索字符串的软件包名称 
```

# 文本查看、处理

## 查看文件内容 

```bash
cat file1                         # 从第一个字节开始正向查看文件的内容 
tac file1                         # 从最后一行开始反向查看一个文件的内容 
more file1                        # 查看一个长文件的内容 
less file1                        # 类似于 'more' 命令，但是它允许在文件中和正向操作一样的反向操作 
head -2 file1                     # 查看一个文件的前两行 
tail -2 file1                     # 查看一个文件的最后两行 
tail -f /var/log/messages         # 实时查看被添加到一个文件中的内容 
```

## 文本处理 

```bash
cat file1 file2 ... | command <> file1_in.txt_or_file1_out.txt general syntax for text manipulation using PIPE, STDIN and STDOUT 
cat file1 | command( sed, grep, awk, grep, etc...) > result.txt 合并一个文件的详细说明文本，并将简介写入一个新文件中 
cat file1 | command( sed, grep, awk, grep, etc...) >> result.txt 合并一个文件的详细说明文本，并将简介写入一个已有的文件中 

grep Aug /var/log/messages                              # 在文件 '/var/log/messages'中查找关键词"Aug" 
grep ^Aug /var/log/messages                             # 在文件 '/var/log/messages'中查找以"Aug"开始的词汇 
grep [0-9] /var/log/messages                            # 选择 '/var/log/messages' 文件中所有包含数字的行 
grep Aug -R /var/log/*                                  # 在目录 '/var/log' 及随后的目录中搜索字符串"Aug" 
grep -E 'string_1|string_2' /var/log/test.log           # 在日志中同时查询包含 string_1或包含string_2的记录
```

**grep显示匹配行的上下行内容**专题：

```bash
grep -A2 "userId" test.txt           # 返回匹配行和匹配行的后两行
grep -B2 "userId" test.txt           # 返回匹配行和匹配行的前两行
grep -C2 "userId" text.txt           # 返回匹配行和匹配行的前后两行
 
-A -B -C 后面跟阿拉伯数字
-A 返回匹配后和它后面的n行,(After，之后)。
-B 返回匹配行和它前面的n行,(Before，之前)。
-C 返回匹配行和它前后各n行，通-A和-B联用,(Context，上下文即前后)。
```

**sed内容**专题：

> sed 可依照脚本的指令来处理、编辑文本文件。主要用来自动编辑一个或多个文件、简化对文件的反复操作、编写转换程序等。


```bash
sed -i 's/string1/string2/g' example.txt            # 将example.txt文件中的 "string1" 替换成 "string2"
sed '/^$/d' example.txt                             # 从example.txt文件中删除所有空白行 
sed '/ *#/d; /^$/d' example.txt                     # 从example.txt文件中删除所有注释和空白行 
sed -e '1d' result.txt                              # 从文件example.txt 中排除第一行 
sed -n '/string1/p' example.txt                     # 查看只包含词汇 "string1"的行 
sed -e 's/ *$//'   example.txt                      # 删除每一行最后的空白字符 
sed -e 's/string1//g'example.txt                    # 从文档中只删除词汇 "string1" 并保留剩余全部 
sed -n '1,5p;5q' example.txt                        # 查看从第一行到第5行内容 
sed -n '5p;5q' example.txt                          # 查看第5行 
sed -e 's/00*/0/g' example.txt                      # 用单个零替换多个零
sed -i '3i helloword' test.txt                      # 在test.txt文件的第三行插入‘helloword’字符串

echo 'hElloWorld' | tr '[:lower:]' '[:upper:]' 找出所有的小写字母并全部替换为大写字母 
```
**sed按指定字符串删除**专题：

```bash
用sed删除匹配到字符串的行：
语法：sed-i'/关键字符/d'文件名

举例1：匹配"\etc\install.sh"
set -i '/\/etc\/install.sh/d' 1.txt

搜索匹配\/etc\/install.sh，就是“/etc/install.sh”
-i 表示操作在源文件上生效.否则操作内存中数据,并不写入文件中.
在分号内的/d表示删除匹配的行。
 
举例2：
删除以a开头的行
sed -i '/^a.*/d' tmp.txt
^a表示开头是a, .*表示后跟任意字符串
```
# 判别大全

## 文件目录是否存在
 
```bash
if [ ! -d "workpath" ];then
    mkdir workpath
else
    echo "File already exists"
fi
```

## 文件类型的参数判别大全

> shell脚本判断文件类型,shell判断文件,目录是否存在或者具有权限 

```bash
#!/bin/sh 
 
myPath="/var/log/httpd/" 
myFile="/var/log/httpd/access.log" 
 
# 这里的-x 参数判断$myPath是否存在并且是否具有可执行权限 
if [ ! -x "$myPath"]; then 
    mkdir "$myPath" 
fi 
 
# 这里的-d 参数判断$myPath是否存在 
if [ ! -d "$myPath"]; then 
    mkdir "$myPath" 
fi 
 
# 这里的-f参数判断$myFile是否存在 
if [ ! -f "$myFile" ]; then 
    touch "$myFile" 
fi 
 
# 其他参数还有-n,-n是判断一个变量是否是否有值 
if [ ! -n "$myVar" ]; then 
    echo "$myVar is empty" 
    exit 0 
fi 
 
# 两个变量判断是否相等 
if [ "$var1" = "$var2" ]; then 
    echo '$var1 eq $var2' 
else 
    echo '$var1 not eq $var2' 
fi
```
 
文件的判别逻辑大全：
```
--------------------------------------------------------------------
-a file exists. 
-b file exists and is a block special file. 
-c file exists and is a character special file. 
-d file exists and is a directory. 
-e file exists (just the same as -a). 
-f file exists and is a regular file. 
-g file exists and has its setgid(2) bit set. 
-G file exists and has the same group ID as this process. 
-k file exists and has its sticky bit set. 
-L file exists and is a symbolic link. 
-n string length is not zero. 
-o Named option is set on. 
-O file exists and is owned by the user ID of this process. 
-p file exists and is a first in, first out (FIFO) special file or 
named pipe. 
-r file exists and is readable by the current process. 
-s file exists and has a size greater than zero. 
-S file exists and is a socket. 
-t file descriptor number fildes is open and associated with a 
terminal device. 
-u file exists and has its setuid(2) bit set. 
-w file exists and is writable by the current process. 
-x file exists and is executable by the current process. 
-z string length is zero. 
 
注意-s 和 -f 参数的区别
```

# cat,echo,sort,comm命令

```bash
cat -n file1 标示文件的行数 
cat example.txt | awk 'NR%2==1' 删除example.txt文件中的所有偶数行 
echo a b c | awk '{print $1}' 查看一行第一栏 
echo a b c | awk '{print $1,$3}' 查看一行的第一和第三栏 
paste file1 file2 合并两个文件或两栏的内容 
paste -d '+' file1 file2 合并两个文件或两栏的内容，中间用"+"区分 
sort file1 file2 排序两个文件的内容 
sort file1 file2 | uniq 取出两个文件的并集(重复的行只保留一份) 
sort file1 file2 | uniq -u 删除交集，留下其他的行 
sort file1 file2 | uniq -d 取出两个文件的交集(只留下同时存在于两个文件中的文件) 
comm -1 file1 file2 比较两个文件的内容只删除 'file1' 所包含的内容 
comm -2 file1 file2 比较两个文件的内容只删除 'file2' 所包含的内容 
comm -3 file1 file2 比较两个文件的内容只删除两个文件共有的部分 
```

使用cut提取文本字符串：

```bash
head -n 5 /etc/passwd | cut -d : -f 1,3-5  # 按“:”分割，提取/etc/passwd中第1,3,4,5列数据，按原分隔符":"进行拼接。
```

sort和uniq的使用:

```bash
sort target_file | uniq  # 去除重复行 
sort target_file | uniq -u  # 查找非重复行 
sort target_file | uniq -d  # 查找重复行 
sort target_file | uniq -c  # 统计每一个文件出现的次数 
```

sort linux下的排序工具

参数说明:
* -r　　降序排列
* -u　　去重
* -n　　以数字大小排序(默认是首字母排序)
* -t　　指定分隔符 这里我们指定'|'为分隔符
* -k　　指定分隔后的第几位进行排序 这里我们指定第2位

任务:report.txt文件里有以下内容：记录了一些方法的执行时间，要求按执行时间降序排列.

命令：sort -run -k 2 -t '|' report.txt

# 文件格式转换 

```bash
dos2unix filedos.txt fileunix.txt 将一个文本文件的格式从MSDOS转换成UNIX 
```

# 网络 - （以太网和WIFI无线） 

```bash
ifconfig eth0                                       # 显示一个以太网卡的配置 
ifup eth0                                           # 启用一个 'eth0' 网络设备 
ifdown eth0                                         # 禁用一个 'eth0' 网络设备 
ifconfig eth0 192.168.1.1 netmask 255.255.255.0     # 控制IP地址 
ifconfig eth0 promisc                               # 设置 'eth0' 成混杂模式以嗅探数据包 (sniffing) 
dhclient eth0                                       # 以dhcp模式启用 'eth0' 
route -n                                            # show routing table 
netstat -apn |grep 8080                             # 查看对应端口是否被使用
hostname                                            # show hostname 
nslookup www.baidu.com                              # lookup hostname to resolve name to ip address and viceversa 
```