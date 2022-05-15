# Linux编程——信号

[[toc]]

# 信号的概念

共性：1. 简单 2. 不能携带大量信息3. 满足某个特设条件才发送。

机制：

* 由于信号是通过软件方法实现，其实现手段导致信号有很强的延时性。
* 每个进程收到的所有信号，都是由内核负责发送的，内核处理。


# 信号的产生与处理方式

1. 按键产生，如：Ctrl+c、Ctrl+z、Ctrl+\
2. 系统调用产生，如：kill、raise、abort
3. 软件条件产生，如：定时器alarm
4. 硬件异常产生，如：非法访问内存(段错误)、除0(浮点数例外)、内存对齐出错(总线错误)
5. 命令产生，如：kill命令

信号的处理方式: 

1. 执行默认动作 
2. 忽略(丢弃) 
3. 捕捉(调用户处理函数)

阻塞信号集(信号屏蔽字)：

* 将某些信号加入集合，对他们设置屏蔽，当屏蔽x信号后，再收到该信号，该信号的处理将推后(解除屏蔽后)。

未决信号集: 

1. 信号产生，未决信号集中描述该信号的位立刻翻转为1，表信号处于未决状态。当信号被处理对应位翻转回为0。这一时刻往往非常短暂。 
2. 信号产生后由于某些原因(主要是阻塞)不能抵达。这类信号的集合称之为未决信号集。在屏蔽解除前，信号一直处于未决状态。

信号四要素：

1. 编号 2. 名称 3. 事件 4. 默认处理动作 

kill函数/命令产生信号

```cpp
int kill(pid_t pid, int sig);//给指定进程发送指定信号
int raise(int sig);//给当前进程发送指定信号 raise(signo) == kill(getpid(), signo);
void abort(void); //给自己发送异常终止信号 6) SIGABRT 信号，终止并产生core文件
```

软件条件产生信号

```cpp
unsigned int alarm(unsigned int seconds);//返回0或剩余的秒数，无失败。
int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
//设置定时器(闹钟)。 可代替alarm函数。精度微秒us，可以实现周期定时。
```

# 信号处理函数

信号集操作函数

* 内核通过读取未决信号集来判断信号是否应被处理。信号屏蔽字mask可以影响未决信号集。而我们可以在应用程序中自定义set来改变mask。已达到屏蔽指定信号的目的。

信号集设定

```cpp
    sigset_t  set;        // typedef unsigned long sigset_t; 
    int sigemptyset(sigset_t *set);                    将某个信号集清0                 成功：0；失败：-1
    int sigfillset(sigset_t *set);                    将某个信号集置1                  成功：0；失败：-1
    int sigaddset(sigset_t *set, int signum);        将某个信号加入信号集          成功：0；失败：-1
    int sigdelset(sigset_t *set, int signum);        将某个信号清出信号集           成功：0；失败：-1
    int sigismember(const sigset_t *set, int signum);判断某个信号是否在信号集中    返回值：在集合：1；不在：0；出错：-1  
```

处理函数：

```cpp
sigprocmask函数：用来屏蔽或解除屏蔽信号。其本质，读取或修改进程的信号屏蔽字(PCB中)。
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);    成功：0；失败：-1，
how:SIG_BLOCK;SIG_UNBLOCK;SIG_SETMASK (屏蔽，解除屏蔽，新屏蔽集)，oldset为旧的信号屏蔽集。
调用sigprocmask(SIG_SETMASK, &oldmask, NULL);来恢复原先的信号屏蔽集。

sigpending函数：读取当前进程的未决信号集
int sigpending(sigset_t *set);    set传出参数。   返回值：成功：0；失败：-1，设置errno
```

信号捕捉函数：

```cpp
signal函数：注册一个信号捕捉函数。
typedef void (*sighandler_t)(int);  //去掉typedef,即定义了一个函数指针，指向的函数接受一个整型参数并返回一个无类型指针
sighandler_t signal(int signum, sighandler_t handler);

sigaction函数：修改信号处理动作（通常在Linux用其来注册一个信号的捕捉函数）
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact); 
```

# 竞态条件(时序竞态)

pause函数：int pause(void);    返回值：-1 并设置errno为EINTR，仅有出错返回

* 调用该函数可以造成进程主动挂起，等待信号唤醒。调用该系统调用的进程将处于阻塞状态(主动放弃cpu) 直到有信号递达将其唤醒。

时序问题分析：

* 利用alarm和pause来实现sleep函数功能时，可能alarm函数调用完，就失去CPU。等再次得到CPU时，
直接去执行SIGALRM的信号处理函数，即pause永远等不到被外来信号中断，程序一直死等待。

解决时序问题：

* 可以通过设置屏蔽SIGALRM的方法来控制程序执行逻辑，但无论如何设置，程序都有可能在“解除信号屏蔽”与“挂起等待信号”这个两个操作间隙失去cpu资源。除非将这两步骤合并成一个“原子操作”。sigsuspend函数具备这个功能。在对时序要求严格的场合下都应该使用sigsuspend替换pause。    

```cpp
int sigsuspend(const sigset_t *mask);    挂起等待信号。
sigsuspend函数调用期间，进程信号屏蔽字由其参数mask指定。
```

可将某个信号（如SIGALRM）从临时信号屏蔽字mask中删除，这样在调用sigsuspend时将解除对该信号的屏蔽，
然后挂起等待，当sigsuspend返回时，进程的信号屏蔽字恢复为原来的值。如果原来对该信号是屏蔽态，
sigsuspend函数返回后仍然屏蔽该信号。


全局变量异步I/O

* 在父子进程中对全局变量同时进行操作时，可能导致程序运行出错。解决方法：利用锁机制。

可/不可重入函数

* 一个函数在被调用执行期间(尚未调用结束)，由于某种时序又被重复调用，称之为“重入”。根据函数实现的方法可分为“可重入函数”和“不可重入函数”两种。不可重入函数大多是在函数中使用了全局变量以及静态变量等，导致程序出错。

注意：信号捕捉函数应设计为可重入函数

SIGCHLD信号

SIGCHLD的产生条件：

1. 子进程终止时
2. 子进程接收到SIGSTOP信号停止时
3. 子进程处在停止态，接受到SIGCONT后唤醒时

SIGCHLD信号注意问题

1. 子进程继承了父进程的信号屏蔽字和信号处理动作，但子进程没有继承未决信号集spending。
2. 注意注册信号捕捉函数的位置。
3. 应该在fork之前，阻塞SIGCHLD信号。注册完捕捉函数后解除阻塞。

信号传参

发送信号传参：

sigqueue函数对应kill函数，但可在向指定进程发送信号的同时携带参数

```cpp
int sigqueue(pid_t pid, int sig, const union sigval value);成功：0；失败：-1，设置errno
```
捕捉函数传参：

```cpp
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
struct sigaction {
            void     (*sa_handler)(int);
            void     (*sa_sigaction)(int, siginfo_t *, void *);
            sigset_t   sa_mask;
            int       sa_flags;
            void     (*sa_restorer)(void);
        };
```

当注册信号捕捉函数，希望获取更多信号相关信息，不应使用sa_handler而应该使用sa_sigaction。
但此时的sa_flags必须指定为SA_SIGINFO。siginfo_t是一个成员十分丰富的结构体类型，可以携带各种与信号相关的数据。

# 中断系统调用

系统调用可分为两类：慢速系统调用和其他系统调用。

1. 慢速系统调用：可能会使进程永远阻塞的一类。如果在阻塞期间收到一个信号，该系统调用就被中断,
不再继续执行(早期)；也可以设定系统调用是否重启。如，read、write、pause、wait...
2. 其他系统调用：getpid、getppid、fork...