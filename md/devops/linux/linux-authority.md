# Linux - Linux权限整理

# 参考资料

* [capabilities(7) — Linux manual page](https://man7.org/linux/man-pages/man7/capabilities.7.html)
* [linux capability详解与容器中的capability](https://blog.csdn.net/weixin_42152531/article/details/120543324)
* [Linux Capabilities 简介](https://blog.csdn.net/qq_34127958/article/details/109853964)

# 概述

在Linux内核2.2之前，为了检查进程权限，将进程区分为两类：特权进程(euid=0)和非特权进程。特权进程(通常为带有suid的程序)可以获取完整的root权限来对系统进行操作。

在linux内核2.2之后引入了**capabilities机制**，来对root权限进行更加细粒度的划分。如果进程不是特权进程，而且也没有root的有效id，系统就会去检查进程的capabilities，来确认该进程是否有执行特权操作的的权限。

可以通过man capabilities来查看具体的capabilities。

linux一共由5种权限集合。

* Permitted ——可以赋予别人的权限。在下文中用大写P简称该权限
* Effective ——当前有限的权限（真正实行权限的东西）。在下文中用大写E简称该权限
* Inheritable ——可继承的权限。在下文中用大写I简称该权限
* Bounding ——边界权限。在下文中用大写B简称该权限
* Ambient——环境权限。在下文中用大写A简称该权限

下面是从 capabilities man page 中摘取的 capabilites 列表：

|capability 名称|描述|
|---|---|
|CAP_AUDIT_CONTROL|启用和禁用内核审计；改变审计过滤规则；检索审计状态和过滤规则|
|CAP_AUDIT_READ|允许通过 multicast netlink 套接字读取审计日志|
|CAP_AUDIT_WRITE|将记录写入内核审计日志|
|CAP_BLOCK_SUSPEND|使用可以阻止系统挂起的特性|
|CAP_CHOWN|修改文件所有者的权限|
|CAP_DAC_OVERRIDE|忽略文件的 DAC 访问限制|
|CAP_DAC_READ_SEARCH|忽略文件读及目录搜索的 DAC 访问限制|
|CAP_FOWNER|忽略文件属主 ID 必须和进程用户 ID 相匹配的限制|
|CAP_FSETID|允许设置文件的 setuid 位|
|CAP_IPC_LOCK|允许锁定共享内存片段|
|CAP_IPC_OWNER|忽略 IPC 所有权检查|
|CAP_KILL|允许对不属于自己的进程发送信号|
|CAP_LEASE|允许修改文件锁的 FL_LEASE 标志|
|CAP_LINUX_IMMUTABLE|允许修改文件的 IMMUTABLE 和 APPEND 属性标志|
|CAP_MAC_ADMIN|允许 MAC 配置或状态更改|
|CAP_MAC_OVERRIDE|覆盖 MAC(Mandatory Access Control)|
|CAP_MKNOD|允许使用 mknod() 系统调用|
|CAP_NET_ADMIN|允许执行网络管理任务|
|CAP_NET_BIND_SERVICE|允许绑定到小于 1024 的端口|
|CAP_NET_BROADCAST|允许网络广播和多播访问|
|CAP_NET_RAW|允许使用原始套接字|
|CAP_SETGID|允许改变进程的 GID|
|CAP_SETFCAP|允许为文件设置任意的 capabilities|
|CAP_SETPCAP|参考 capabilities man page|
|CAP_SETUID|允许改变进程的 UID|
|CAP_SYS_ADMIN|允许执行系统管理任务，如加载或卸载文件系统、设置磁盘配额等|
|CAP_SYS_BOOT|允许重新启动系统|
|CAP_SYS_CHROOT|允许使用 chroot() 系统调用|
|CAP_SYS_MODULE|允许插入和删除内核模块|
|CAP_SYS_NICE|允许提升优先级及设置其他进程的优先级|
|CAP_SYS_PACCT|允许执行进程的 BSD 式审计|
|CAP_SYS_PTRACE|允许跟踪任何进程|
|CAP_SYS_RAWIO|允许直接访问 /devport、/dev/mem、/dev/kmem 及原始块设备|
|CAP_SYS_RESOURCE|忽略资源限制|
|CAP_SYS_TIME|允许改变系统时钟|
|CAP_SYS_TTY_CONFIG|允许配置 TTY 设备|
|CAP_SYSLOG|允许使用 syslog() 系统调用|
|CAP_WAKE_ALARM|允许触发一些能唤醒系统的东西(比如 CLOCK_BOOTTIME_ALARM 计时器)|

## 查看当前用户的权限

查看/proc/$$/status文件中的Cap部分

```
[root@VM-16-6-centos ~]# cat /proc/$$/status | grep Cap
CapInh: 0000000000000000
CapPrm: 0000001fffffffff
CapEff: 0000001fffffffff
CapBnd: 0000001fffffffff
CapAmb: 0000000000000000
[root@VM-16-6-centos ~]# docker exec -it my_test bash
[root@6c70cdde62d5 /]# cat /proc/$$/status | grep Cap
CapInh: 0000000000000000
CapPrm: 00000000a80425fb
CapEff: 00000000a80425fb
CapBnd: 00000000a80425fb
CapAmb: 0000000000000000
```

```
## 主机侧权限
[root@VM-16-6-centos ~]# capsh --print
Current: = cap_chown,cap_dac_override,cap_dac_read_search,cap_fowner,cap_fsetid,cap_kill,cap_setgid,cap_setuid,cap_setpcap,cap_linux_immutable,cap_net_bind_service,cap_net_broadcast,cap_net_admin,cap_net_raw,cap_ipc_lock,cap_ipc_owner,cap_sys_module,cap_sys_rawio,cap_sys_chroot,cap_sys_ptrace,cap_sys_pacct,cap_sys_admin,cap_sys_boot,cap_sys_nice,cap_sys_resource,cap_sys_time,cap_sys_tty_config,cap_mknod,cap_lease,cap_audit_write,cap_audit_control,cap_setfcap,cap_mac_override,cap_mac_admin,cap_syslog,35,36+ep
Bounding set =cap_chown,cap_dac_override,cap_dac_read_search,cap_fowner,cap_fsetid,cap_kill,cap_setgid,cap_setuid,cap_setpcap,cap_linux_immutable,cap_net_bind_service,cap_net_broadcast,cap_net_admin,cap_net_raw,cap_ipc_lock,cap_ipc_owner,cap_sys_module,cap_sys_rawio,cap_sys_chroot,cap_sys_ptrace,cap_sys_pacct,cap_sys_admin,cap_sys_boot,cap_sys_nice,cap_sys_resource,cap_sys_time,cap_sys_tty_config,cap_mknod,cap_lease,cap_audit_write,cap_audit_control,cap_setfcap,cap_mac_override,cap_mac_admin,cap_syslog,35,36
Securebits: 00/0x0/1'b0
 secure-noroot: no (unlocked)
 secure-no-suid-fixup: no (unlocked)
 secure-keep-caps: no (unlocked)
uid=0(root)
gid=0(root)
groups=0(root)

## docker容器侧权限
[root@6c70cdde62d5 /]# capsh --print
Current: = cap_chown,cap_dac_override,cap_fowner,cap_fsetid,cap_kill,cap_setgid,cap_setuid,cap_setpcap,cap_net_bind_service,cap_net_raw,cap_sys_chroot,cap_mknod,cap_audit_write,cap_setfcap+ep
Bounding set =cap_chown,cap_dac_override,cap_fowner,cap_fsetid,cap_kill,cap_setgid,cap_setuid,cap_setpcap,cap_net_bind_service,cap_net_raw,cap_sys_chroot,cap_mknod,cap_audit_write,cap_setfcap
Securebits: 00/0x0/1'b0
 secure-noroot: no (unlocked)
 secure-no-suid-fixup: no (unlocked)
 secure-keep-caps: no (unlocked)
uid=0(root)
gid=0(root)
groups=
[root@6c70cdde62d5 /]# exit
exit
```

## 如何使用 capabilities

getcap 命令和 setcap 命令分别用来查看和设置程序文件的 capabilities 属性。下面演示如何使用 capabilities 代替 ping 命令的 SUID。
因为 ping 命令在执行时需要访问网络，这就需要获得 root 权限，常规的做法是通过 SUID 实现的(和 passwd 命令相同)：

为 ping 命令文件添加 capabilities:

```
sudo setcap cap_net_admin,cap_net_raw+ep /bin/ping
```

如果要移除刚才添加的 capabilities，执行下面的命令：

```
sudo setcap cap_net_admin,cap_net_raw-ep /bin/ping
```