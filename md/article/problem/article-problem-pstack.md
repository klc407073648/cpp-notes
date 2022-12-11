# 问题 - 跟踪进程栈(pstack命令)

> pstack是一个基于GDB的脚本命令，可现实每个进程的栈跟踪。pstack命令必须由相应进程的属主或root运行。可以使用pstack来确定进程挂起的位置。此命令允许使用的唯一选项是要检查的进程的PID.

[[toc]]

# 参考文献

* [详解命令-pstack](https://blog.csdn.net/u014389734/article/details/78993792)
* [Linux lsof命令](https://blog.csdn.net/qq_27870421/article/details/92803453)
* [Linux下内存使用分析思路](https://blog.csdn.net/odeng888/article/details/80062544)
* [Linux内存占用分析的几个方法](https://blog.csdn.net/daocaokafei/article/details/120611883)

# pstack命令详解

pstree以树结构显示进程

```bash
[root@VM-16-6-centos build]# pstree -p root |grep YDService
           |-YDService(12807)-+-sh(12976)-+-{sh}(12977)
           |                  |-{YDService}(12809)
           |                  |-{YDService}(12810)
           |                  |-{YDService}(12811)
           |                  |-{YDService}(12812)
           |                  |-{YDService}(12813)
           |                  |-{YDService}(12814)
           |                  |-{YDService}(12815)
           |                  |-{YDService}(12816)
           |                  |-{YDService}(12830)
           |                  |-{YDService}(12831)
           |                  |-{YDService}(12837)
           |                  |-{YDService}(12847)
           |                  |-{YDService}(12848)
           |                  |-{YDService}(12849)
           |                  |-{YDService}(12850)
           |                  |-{YDService}(12851)
           |                  |-{YDService}(12868)
           |                  |-{YDService}(12869)
           |                  |-{YDService}(12870)
           |                  |-{YDService}(12941)
           |                  |-{YDService}(12996)
           |                  `-{YDService}(19034)
```

root为工作用户，-p为显示进程识别码，YDService共启动了23个子线程，加上主线程共24个线程。

```
[root@VM-16-6-centos build]# ps -Lf 12807
UID        PID  PPID   LWP  C NLWP STIME TTY      STAT   TIME CMD
root     12807     1 12807  0   23 Aug10 ?        Sl     0:01 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12809  0   23 Aug10 ?        Sl     0:00 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12810  0   23 Aug10 ?        Sl    20:49 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12811  0   23 Aug10 ?        Sl     5:11 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12812  0   23 Aug10 ?        Sl     0:14 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12813  0   23 Aug10 ?        Sl     0:00 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12814  0   23 Aug10 ?        Sl     0:40 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12815  0   23 Aug10 ?        Sl     0:42 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12816  0   23 Aug10 ?        Sl     2:10 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12830  0   23 Aug10 ?        Sl    24:02 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12831  0   23 Aug10 ?        Sl     2:36 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12837  0   23 Aug10 ?        Sl     0:07 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12847  0   23 Aug10 ?        Sl     0:00 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12848  0   23 Aug10 ?        Sl     9:01 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12849  0   23 Aug10 ?        Sl     9:33 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12850  0   23 Aug10 ?        Sl     1:47 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12851  0   23 Aug10 ?        Sl     8:48 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12868  0   23 Aug10 ?        Sl     2:23 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12869  0   23 Aug10 ?        Sl     2:22 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12870  0   23 Aug10 ?        Sl     2:40 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12941  0   23 Aug10 ?        Sl     9:54 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 12996  0   23 Aug10 ?        Sl     9:33 /usr/local/qcloud/YunJing/YDEyes/YDService
root     12807     1 19034  0   23 Aug12 ?        Sl     6:49 /usr/local/qcloud/YunJing/YDEyes/YDService
```

进程共启动了24个线程

pstack显示每个进程的栈跟踪:

```
[root@VM-16-6-centos build]# pstack 12807
Thread 23 (Thread 0x7f2aeab95700 (LWP 12809)):
#0  0x0000000000a85683 in ?? ()
#1  0x0000000000a4e566 in ?? ()
#2  0x00000000027042e8 in ?? ()
#3  0x0000000000000080 in ?? ()
#4  0x0000000000000000 in ?? ()
Thread 22 (Thread 0x7f2ac3783700 (LWP 12810)):
#0  0x0000000000a8506d in ?? ()
#1  0x0000000000000000 in ?? ()
Thread 21 (Thread 0x7f2ac2f82700 (LWP 12811)):
#0  0x00007f2aeac950e3 in epoll_wait () from /lib64/libc.so.6
#1  0x000000000088fa75 in CEpollLoop::loop(unsigned int) ()
#2  0x000000000088f5a6 in pollLoop() ()
#3  0x0000000000a82be8 in ?? ()
#4  0x0000000000a5ac43 in ?? ()
#5  0x000000c000001980 in ?? ()
#6  0x000000c000076178 in ?? ()
#7  0x0000000000000001 in ?? ()
#8  0x000000c000000d80 in ?? ()
#9  0x00000000000000a0 in ?? ()
#10 0x000000c0002c6600 in ?? ()
#11 0x000000c000001980 in ?? ()
#12 0x0000000000000000 in ?? ()
Thread 20 (Thread 0x7f2ac2781700 (LWP 12812)):
#0  0x00007f2aeac5b9fd in nanosleep () from /lib64/libc.so.6
#1  0x00007f2aeac5b90b in sleep () from /lib64/libc.so.6
#2  0x000000000142d406 in run_container_scan_thread ()
#3  0x0000000000a82be8 in ?? ()
#4  0x0000000000a5ac43 in ?? ()
#5  0x000000c000001980 in ?? ()
#6  0x000000c000076178 in ?? ()
#7  0x0000000000000001 in ?? ()
#8  0x000000c000001380 in ?? ()
#9  0x00000000000000c8 in ?? ()
#10 0x000000c0004aa180 in ?? ()
#11 0x000000c000001980 in ?? ()
#12 0x0000000000000000 in ?? ()
Thread 19 (Thread 0x7f2ac1f80700 (LWP 12813)):
#0  0x0000000000a85683 in ?? ()
#1  0x0000000000a4e566 in ?? ()
#2  0x0000000002758d98 in ?? ()
#3  0x0000000000000080 in ?? ()
#4  0x0000000000000000 in ?? ()
Thread 18 (Thread 0x7f2ac0fab700 (LWP 12814)):
#0  0x00007f2aeac5b9fd in nanosleep () from /lib64/libc.so.6
#1  0x00007f2aeac8c2d4 in usleep () from /lib64/libc.so.6
#2  0x000000000058be47 in ?? ()
#3  0x00000000006134c0 in ?? ()
#4  0x00000000006134d9 in ?? ()
#5  0x00007f2aeb78bea5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f2aeac94b0d in clone () from /lib64/libc.so.6
Thread 17 (Thread 0x7f2ac07aa700 (LWP 12815)):
#0  0x00007f2aeac5b9fd in nanosleep () from /lib64/libc.so.6
#1  0x00007f2aeac8c2d4 in usleep () from /lib64/libc.so.6
#2  0x000000000058be7c in ?? ()
#3  0x00000000006134c0 in ?? ()
#4  0x00000000006134d9 in ?? ()
#5  0x00007f2aeb78bea5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f2aeac94b0d in clone () from /lib64/libc.so.6
Thread 16 (Thread 0x7f2abffa9700 (LWP 12816)):
#0  0x00007f2aeac5b9fd in nanosleep () from /lib64/libc.so.6
#1  0x00007f2aeac8c2d4 in usleep () from /lib64/libc.so.6
#2  0x0000000000595aca in ?? ()
#3  0x00000000006134c0 in ?? ()
#4  0x00000000006134d9 in ?? ()
#5  0x00007f2aeb78bea5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f2aeac94b0d in clone () from /lib64/libc.so.6
Thread 15 (Thread 0x7f2abf7a8700 (LWP 12830)):
#0  0x00007f2aeb78fde2 in pthread_cond_timedwait@@GLIBC_2.3.2 () from /lib64/libpthread.so.0
#1  0x000000000137b3bc in SharedQueue<std::string>::dequeue_for(std::string&, int) ()
#2  0x000000000137ae09 in EventParseLoop() ()
#3  0x0000000000a82be8 in ?? ()
#4  0x0000000000a5ac43 in ?? ()
#5  0x000000c000001980 in ?? ()
#6  0x000000c000076178 in ?? ()
#7  0x0000000000000001 in ?? ()
#8  0x000000c000087080 in ?? ()
#9  0x00000000000000a0 in ?? ()
#10 0x000000c000673800 in ?? ()
#11 0x000000c000001980 in ?? ()
#12 0x0000000000000000 in ?? ()
Thread 14 (Thread 0x7f2abefa7700 (LWP 12831)):
#0  0x0000000000a85683 in ?? ()
#1  0x0000000000a4e566 in ?? ()
#2  0x000000c00026a848 in ?? ()
#3  0x0000000000000080 in ?? ()
#4  0x0000000000000000 in ?? ()
Thread 13 (Thread 0x7f2abe726700 (LWP 12837)):
#0  0x00007f2aeb79275d in read () from /lib64/libpthread.so.0
#1  0x00000000008d90df in ?? ()
#2  0x00007f2aeb78bea5 in start_thread () from /lib64/libpthread.so.0
#3  0x00007f2aeac94b0d in clone () from /lib64/libc.so.6
Thread 12 (Thread 0x7f2abdf25700 (LWP 12847)):
#0  0x0000000000a85683 in ?? ()
#1  0x0000000000a4e566 in ?? ()
#2  0x0000000002758ea0 in ?? ()
#3  0x0000000000000080 in ?? ()
#4  0x0000000000000000 in ?? ()
Thread 11 (Thread 0x7f2abd724700 (LWP 12848)):
#0  0x0000000000a85683 in ?? ()
#1  0x0000000000a4e566 in ?? ()
#2  0x000000c000084f48 in ?? ()
#3  0x0000000000000080 in ?? ()
#4  0x0000000000000000 in ?? ()
Thread 10 (Thread 0x7f2abcf23700 (LWP 12849)):
#0  0x0000000000a85830 in ?? ()
#1  0x0000000000a4e244 in ?? ()
#2  0x0000000000000009 in ?? ()
#3  0x00007f2abcf226c8 in ?? ()
#4  0x0000001300000080 in ?? ()
#5  0x0000000000000000 in ?? ()
Thread 9 (Thread 0x7f2abc722700 (LWP 12850)):
#0  0x00007f2aeac5b9fd in nanosleep () from /lib64/libc.so.6
#1  0x00007f2aeac8c2d4 in usleep () from /lib64/libc.so.6
#2  0x0000000000544d9b in ?? ()
#3  0x00000000006134c0 in ?? ()
#4  0x00000000006134d9 in ?? ()
#5  0x00007f2aeb78bea5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f2aeac94b0d in clone () from /lib64/libc.so.6
Thread 8 (Thread 0x7f2abbf21700 (LWP 12851)):
#0  0x0000000000a85683 in ?? ()
#1  0x0000000000a4e566 in ?? ()
#2  0x000000c00026b648 in ?? ()
#3  0x0000000000000080 in ?? ()
#4  0x0000000000000000 in ?? ()
Thread 7 (Thread 0x7f2abb720700 (LWP 12868)):
#0  0x00007f2aeac5b9fd in nanosleep () from /lib64/libc.so.6
#1  0x00007f2aeac8c2d4 in usleep () from /lib64/libc.so.6
#2  0x0000000000614361 in ?? ()
#3  0x00007f2aeb78bea5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f2aeac94b0d in clone () from /lib64/libc.so.6
Thread 6 (Thread 0x7f2abaf1f700 (LWP 12869)):
#0  0x00007f2aeac5b9fd in nanosleep () from /lib64/libc.so.6
#1  0x00007f2aeac8c2d4 in usleep () from /lib64/libc.so.6
#2  0x0000000000614361 in ?? ()
#3  0x00007f2aeb78bea5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f2aeac94b0d in clone () from /lib64/libc.so.6
Thread 5 (Thread 0x7f2aba71e700 (LWP 12870)):
#0  0x00007f2aeac5b9fd in nanosleep () from /lib64/libc.so.6
#1  0x00007f2aeac5b90b in sleep () from /lib64/libc.so.6
#2  0x000000000059e250 in ?? ()
#3  0x00000000006134c0 in ?? ()
#4  0x00000000006134d9 in ?? ()
#5  0x00007f2aeb78bea5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f2aeac94b0d in clone () from /lib64/libc.so.6
Thread 4 (Thread 0x7f2ab9f1d700 (LWP 12941)):
#0  0x0000000000a85683 in ?? ()
#1  0x0000000000a4e566 in ?? ()
#2  0x000000c00026a148 in ?? ()
#3  0x0000000000000080 in ?? ()
#4  0x0000000000000000 in ?? ()
Thread 3 (Thread 0x7f2ab9508700 (LWP 12996)):
#0  0x0000000000a85683 in ?? ()
#1  0x0000000000a4e566 in ?? ()
#2  0x000000c00026af48 in ?? ()
#3  0x0000000000000080 in ?? ()
#4  0x0000000000000000 in ?? ()
Thread 2 (Thread 0x7f2ab8d07700 (LWP 19034)):
#0  0x0000000000a85683 in ?? ()
#1  0x0000000000a4e566 in ?? ()
#2  0x000000c0000519c8 in ?? ()
#3  0x0000000000000080 in ?? ()
#4  0x0000000000000000 in ?? ()
Thread 1 (Thread 0x7f2aebeb6780 (LWP 12807)):
#0  0x00007f2aeac950e3 in epoll_wait () from /lib64/libc.so.6
#1  0x00000000005fb515 in ?? ()
#2  0x000000000053abb9 in ?? ()
#3  0x00007f2aeabb8555 in __libc_start_main () from /lib64/libc.so.6
#4  0x000000000053eac1 in _start ()
```