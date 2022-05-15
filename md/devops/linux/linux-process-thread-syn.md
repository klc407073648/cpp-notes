# Linux编程——线程和进程同步

[[toc]]
​
# 线程同步

同步即协同步调，按预定的先后次序运行。
线程同步，指一个线程发出某一功能调用时，在没有得到结果之前，该调用不返回。同时其它线程为保证数据一致性，不能调用该功能。

银行取款问题，产生的现象叫做“与时间有关的错误”(time related)。为了避免这种数据混乱，线程需要同步。
因此，所有“多个控制流，共同操作一个共享资源”的情况，都需要同步。

# 互斥量

Linux中提供一把互斥锁mutex（也称之为互斥量）。
每个线程在对资源操作前都尝试先加锁，成功加锁才能操作，操作结束解锁。

pthread_mutex_init函数：
1. 静态初始化：pthead_mutex_t muetx = PTHREAD_MUTEX_INITIALIZER;
2. 动态初始化：pthread_mutex_init(&mutex, NULL)

```cpp
pthread_mutex_destroy函数
pthread_mutex_lock函数
pthread_mutex_trylock函数
pthread_mutex_unlock函数
```

注意：在访问共享资源前加锁，访问结束后立即解锁。锁的“粒度”应越小越好。

死锁情况：
1. 线程试图对同一个互斥量A加锁两次。
2. 线程1拥有A锁，请求获得B锁；线程2拥有B锁，请求获得A锁

# 读写锁

读时共享，写时独占。写锁优先级高。

```cpp
pthread_rwlock_init函数
pthread_rwlock_destroy函数
pthread_rwlock_rdlock函数  
pthread_rwlock_wrlock函数
pthread_rwlock_tryrdlock函数
pthread_rwlock_trywrlock函数
pthread_rwlock_unlock函数
```

# 条件变量

```cpp
pthread_cond_init函数
pthread_cond_destroy函数

pthread_cond_wait函数：阻塞等待一个条件变量
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
```

函数作用：
1. 阻塞等待条件变量cond（参1）满足    
2. 释放已掌握的互斥锁（解锁互斥量）相当于pthread_mutex_unlock(&mutex);1.2.两步为一个原子操作。
3. 当被唤醒，pthread_cond_wait函数返回时，解除阻塞并重新申请获取互斥锁pthread_mutex_lock(&mutex);

```cpp
pthread_cond_timedwait函数
pthread_cond_signal函数：唤醒至少一个阻塞在条件变量上的线程
pthread_cond_broadcast函数：唤醒全部阻塞在条件变量上的线程
```

# 信号量

```cpp
sem_init函数：初始化一个信号量
int sem_init(sem_t *sem, int pshared, unsigned int value);
    参1：sem信号量    
    参2：pshared取0用于线程间；取非0（一般为1）用于进程间    
    参3：value指定信号量初值
    
sem_destroy函数：销毁一个信号量
int sem_destroy(sem_t *sem);

sem_wait函数：给信号量加锁 -- 
int sem_wait(sem_t *sem);

sem_post函数：给信号量解锁 ++
int sem_post(sem_t *sem);

sem_trywait函数：尝试对信号量加锁 --    
sem_timedwait函数：限时尝试对信号量加锁 --
```

# 进程间同步
互斥量：
进程间也可以使用互斥锁，来达到同步的目的。但应在pthread_mutex_init初始化之前，修改其属性为进程间共享。
mutex的属性修改函数主要有以下几个：

```cpp
pthread_mutexattr_t mattr 类型：        用于定义mutex锁的【属性】
pthread_mutexattr_init函数：            初始化一个mutex属性对象
pthread_mutexattr_destroy函数：            销毁mutex属性对象 (而非销毁锁)
pthread_mutexattr_setpshared函数：        修改mutex属性。
```

文件锁：
借助 fcntl函数来实现锁机制。    操作文件的进程没有获得锁时，可以打开，但无法执行read、write操作。
fcntl函数：    获取、设置文件访问控制属性。
int fcntl(int fd, int cmd, ... /* arg */ );
参2：
    F_SETLK (struct flock *)    设置文件锁（trylock）
    F_SETLKW (struct flock *) 设置文件锁（lock）W --> wait
    F_GETLK (struct flock *)    获取文件锁
参3：
    struct flock {
            ...
            short l_type;        锁的类型：F_RDLCK 、F_WRLCK 、F_UNLCK
            short l_whence;      偏移位置：SEEK_SET、SEEK_CUR、SEEK_END 
            off_t l_start;           起始偏移：1000
            off_t l_len;             长度：0表示整个文件加锁
            pid_t l_pid;         持有该锁的进程ID：(F_GETLK only)
            ...
        };

​