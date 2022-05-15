# Linux编程——线程

[[toc]]

# 线程概念

LWP：light weight process 轻量级的进程，本质仍是进程(在Linux环境下)
    * 进程：独立地址空间，拥有PCB
    * 线程：也有PCB，但没有独立的地址空间(共享)
    * 区别：在于是否共享地址空间。    独居(进程)；合租(线程)。

Linux下：
    * 线程：最小的执行单位
    * 进程：最小分配资源单位，可看成是只有一个线程的进程

# 线程控制原语

```cpp
pthread_self函数：获取线程ID。
pthread_t pthread_self(void);    返回值：成功：0；    失败：无！

pthread_create函数：创建一个新线程。
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

pthread_exit函数：将单个线程退出
void pthread_exit(void *retval); 参数：retval表示线程退出状态，通常传NULL

pthread_join函数：阻塞等待线程退出，获取线程退出状态        。
int pthread_join(pthread_t thread, void **retval); 成功：0；失败：错误号

pthread_detach函数：实现线程分离
int pthread_detach(pthread_t thread);    成功：0；失败：错误号

pthread_cancel函数：杀死(取消)线程        
int pthread_cancel(pthread_t thread);    成功：0；失败：错误号
```

# 线程属性

可以通过设置pthread_attr_t来修改线程的默认属性，主要结构成员有

1. 线程分离状态;
2. 线程栈大小（默认平均分配）;
3. 线程栈警戒缓冲区大小（位于栈末尾）。

对应的控制函数：

初始化线程属性：

```cpp
int pthread_attr_init(pthread_attr_t *attr); 成功：0；失败：错误号
```

销毁线程属性所占用的资源：

```cpp
int pthread_attr_destroy(pthread_attr_t *attr); 成功：0；失败：错误号
```

设置线程属性，分离or非分离：

```cpp
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate); 
```

获取程属性，分离or非分离：

```cpp
int pthread_attr_getdetachstate(pthread_attr_t *attr, int *detachstate); 
```

线程的栈地址：

```cpp
int pthread_attr_setstack(pthread_attr_t *attr, void *stackaddr, size_t stacksize); 成功：0；失败：错误号
int pthread_attr_getstack(pthread_attr_t *attr, void **stackaddr, size_t *stacksize); 成功：0；失败：错误号
```

线程的栈大小：

```cpp
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize); 成功：0；失败：错误号
int pthread_attr_getstacksize(pthread_attr_t *attr, size_t *stacksize); 成功：0；失败：错误号
```

​