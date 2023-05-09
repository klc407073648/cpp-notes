# 常用开发库 - hiredis

# 参考资料

* [redis官网](https://redis.io/)
* [redis常用客户端连接库](https://redis.io/resources/clients/)
* [hiredis官网](https://github.com/redis/hiredis)
* [Hiredis README翻译](https://blog.csdn.net/lhl_blog/article/details/78665285)

# 概述

> Hiredis是Redis数据库的简约C客户端库。它是简约的，因为它只是增加了对协议的最小支持，但是同时它使用了一个高级别的printf-like API，所以对于习惯了printf风格的C编程用户来说，其非常容易使用，而且API中没有**明确的绑定每个Redis命令**。

除了支持发送命令和接收回复之外，它还附带了一个与I/O层分离的回复解析器。为了方便复用，其设计成为一个流解析器，例如可以在更高级别的语言绑定中使用，以实现高效的回复解析。

Hiredis仅支持二进制安全(binary-safe)的Redis协议，因此您可以将其与任何Redis版本(> = 1.2.0)配合使用。

该库带有多个API，**有同步API，异步API和答复解析API(重要)**。

## Synchronous API

要使用SynchronousAPI，只需要引入几个函数调用：

```c
redisContext *redisConnect(const char *ip, int port);
void *redisCommand(redisContext *c, const char *format, ...);
void freeReplyObject(void *reply);
```

### Connecting

函数redisConnect用于创建所谓的redisContext结构。redisContext是Hiredis持有连接状态的地方。

当连接处于错误状态时，redisContext结构的整数err字段不为零。errstr字段将包含一个描述错误的字符串。 

有关错误的更多信息可以在Errors部分找到。 尝试使用redisConnect连接到Redis后，应检查err字段以查看建立连接是否成功：

```c
redisContext *c = redisConnect("127.0.0.1", 6379);
if (c == NULL || c->err) {
    if (c) {
        printf("Error: %s\n", c->errstr);
        // handle error
    } else {
        printf("Can't allocate redis context\n");
    }
}
```

* 注意: 一个redisContext结构是线程非安全的。

### Sending commands

有几种方法可以向Redis发出命令。 首先介绍的是redisCommand。这个函数的格式类似于printf。 最简单的形式是这样使用的：

```c
reply = redisCommand(context, "SET foo bar");
```

说明符％s在命令中插入一个字符串，并使用strlen来确定字符串的长度：

```c
reply = redisCommand(context, "SET foo %s", value);
```

当您需要在命令中传递二进制安全字符串时，可以使用％b说明符。 与指向字符串的指针一起，它需要字符串的size_t长度参数：

```c
reply = redisCommand(context, "SET foo %b", value, (size_t) valuelen);
```

在内部，Hiredis将命令拆分为不同的参数，并将其转换为与Redis进行通信的协议。 一个或多个空格分隔参数，因此您可以在参数的任何位置使用说明符：

```c
reply = redisCommand(context, "SET key:%s %s", myid, value);
```

### Using replies

当命令成功执行时，redisCommand的返回值保留一个回复。 发生错误时，返回值为NULL，上下文中的err字段将被设置（请参阅Errors部分）。 

* **一旦错误返回，上下文不能被重用，你应该建立一个新的连接。**
    * 代码里将 m_pRedisContext = NULL ,下次重新拿新的上下文。

redisCommand的标准回复类型是redisReply。 应该使用redisReply中的类型字段来测试收到的答复类型：

* REDIS_REPLY_STATUS:
    * 该命令回复了命令执行状态。 状态字符串可以使用reply-> str来访问。 这个字符串的长度可以使用reply-> len来访问。

* REDIS_REPLY_ERROR:
    * 该命令回复了一个错误。 错误字符串可以被访问REDIS_REPLY_STATUS来获得。

* REDIS_REPLY_INTEGER:
    * 该命令用一个整数来回答。 可以使用long long类型的reply-> integer字段来访问整数值。

* REDIS_REPLY_NIL：
    * 该命令回答了一个无效的nil对象。 其表示没有数据可以访问。

* REDIS_REPLY_STRING:
    * 批量数据（字符串）回复。 答复的值可以使用reply-> str来访问。 这个字符串的长度可以使用reply-> len来访问。

* REDIS_REPLY_ARRAY:

    * 多批量数据回复。 多批量数据回复中的元素数量存储在reply->elements。多批量回复中的每个元素也是一个redisReply对象，可以通过reply->element [.. index ..]进行访问。 Redis可能会回应嵌套数组，但这也是完全支持的。

应使用freeReplyObject()函数释放回复。 请注意，这个函数将负责释放包含在数组和嵌套数组中的子回复对象，所以用户不需要释放子回复（这实际上是有害的，会损坏内存）。

**重要提示:hiredis（0.10.0）版本在使用异步API时会主动释放回复对象。这意味着当你使用这个API时你不应该调用freeReplyObject。 在回调返回之后，回复对象被hiredis清除。 这种行为在未来的版本中可能会发生变化，因此请务必在升级时密切关注更新日志（请参阅问题＃39）。**

### Cleaning up

要断开和释放上下文，可以使用以下功能：

```c
void redisFree(redisContext *c);
```

这个函数立即关闭套接字，然后释放创建上下文的分配。

### Sending commands (cont’d)

与redisCommand功能类似一起，函数redisCommandArgv也可用于发出命令。 它有以下原型：

```c
void *redisCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen);
```

它需要参数的数量argc，一个字符串数组argv和参数数组argv的长度。 为了方便，argvlen可以设置为NULL，函数将在每个参数上使用strlen来确定它的长度。 显然，当任何参数需要binary-safe时，应提供整个参数数组的长度。

返回值与redisCommand具有相同的语义。

### Pipelining

为了解释Hiredis如何支持阻塞连接中的流水线，需要了解内部执行流程。

当redisCommand系列中的任何函数被调用时，Hiredis首先根据Redis协议格式化命令,格式化的命令然后被放入输出缓冲区下, 这个输出缓冲区是动态的，所以它可以容纳任意数量的命令。将命令放入输出缓冲区后，然后调用redisGetReply。 这个函数遵循两个执行路径：

1. 输出缓冲区非空:
    * 尝试解析来自输入缓冲区的单个回复并将其返回
    * 如果没有答复可以解析，请继续2

2. 输出缓冲区为空:
    * 将整个输出缓冲区写入套接字
    * 从套接字等待读取，直到可以解析一个单一的答复

函数redisGetReply作为Hiredis 的数据导出API，可以在用于套接字上等待预期回复的场景。

对于管道命令，唯一需要做的事情是填充输出缓冲区。 为了实现这个功能，可以使用两个与redisCommand类似的命令，但它们不返回一个回复：

```c
void redisAppendCommand(redisContext *c, const char *format, ...);
void redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen);
```

在调用一个或多个上述函数之后，redis Get Reply可以用来接收随后的答复。这个函数的返回值是REDIS_OK或REDIS_ERR，其中后者意味着在处理答复时发生错误。 正如其他命令一样，上下文中的“err”字段可用于找出导致此错误的原因。

下面的例子显示了一个简单的流水线（导致一次调用write(2)和一次调用read（2）):

```c
redisReply *reply;
redisAppendCommand(context,"SET foo bar");
redisAppendCommand(context,"GET foo");
redisGetReply(context,&reply); // reply for SET
freeReplyObject(reply);
redisGetReply(context,&reply); // reply for GET
freeReplyObject(reply);
```

这个API也可以用来实现阻塞的用户订阅：

```c
reply = redisCommand(context,"SUBSCRIBE foo");
freeReplyObject(reply);
while(redisGetReply(context,&reply) == REDIS_OK) {
    // consume message
    freeReplyObject(reply);
}
```

### Errors

当一个函数调用不成功时，根据函数返回值为“NULL”或“REDIS_ERR”。 上下文中的“err”字段将不为零，并设置为其中的一个以下常量:

* REDIS_ERR_IO
    * 创建连接时其试图写入到套接字或从套接字读取数据，但该操作出现I/O了错误。如果你包了errno.h在你的应用程序中，你可以使用全局的errno变量来找出是什么错误。

* REDIS_ERR_EOF
    * 服务器关闭导致一次空的读取。

* REDIS_ERR_PROTOCOL
    * 解析Redis协议时出现问题。

* REDIS_ERR_OTHER
    * 其他类型的错误。目前，其仅使用于指定的主机地址无法解析的情况下。

在任何情况下，上下文中的errstr字段将被设置为保存字符串形式的错误提示。

## Asynchronous API

Hiredis提供了一个异步API，可以轻松地与任何事件库一起工作。可以参考Hiredis使用的事件库为: libev或[libevent](http://monkey.org/~provos/libevent/).

### Connecting

函数redisAsyncConnect可以用来建立一个与Redis的非阻塞连接。它返回一个指向新创建的redisAsyncContext结构的指针。err字段应在创建后检查，看看是否有错误的创建连接。**由于要创建的连接是非阻塞的，因此如果指定的主机和端口能够接受连接，内核将无法立即返回。**

注意:一个redisAsyncContext是非线程安全的

```c
redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
if (c->err) {
    printf("Error: %s\n", c->errstr);
    // handle error
}
```

redisAsyncContext可以保存链接异常处理回调函数，用于处理链接断开时的事务(可能由于链接错误或是用户主动要求断开链接)。回调函数的原型如下:

```c
void(const redisAsyncContext *c, int status);
```

在断开连接时,当用户主动断开连接时status参数被设置为REDIS_OK，当断线是由错误引起时，status参数被设置为REDIS_ERR。当它是REDIS_ERR时，可以访redisAsyncContext中的err字段来找出错误的原因。断开连接回调后,redisAsyncContext总是被释放。 当需要重新连接时，上述的回调函数是一个很好的选择。

一个redisAsyncContext只能被设置一次处理链接断开的回调函数，其重复设置将导致REDIS_ERR。设置回调函数的函数原型如下：

```c
int redisAsyncSetDisconnectCallback(redisAsyncContext *ac, 
redisDisconnectCallback *fn);
```

### Sending commands and their callbacks

异步上下文中，由于事件循环的性质，命令会自动进行流水线处理。因此，与同步API不同，发送命令只有一种方法。因为命令是异步发送给Redis的，所以发出一个命令需要一个回调函数在收到回复时调用。 回复回调应该有以下原型:

```c
void(redisAsyncContext *c, void *reply, void *privdata);
```

参数private可以保存任意需要传递给回调函数的数据，数据可以来自命令开始执行入队到开始执行回调函数之间的任意数据。

可用于在异步上下文中发出命令的函数是：

```c
int redisAsyncCommand(
  redisAsyncContext *ac, redisCallbackFn *fn, void *privdata,
  const char *format, ...);
int redisAsyncCommandArgv(
  redisAsyncContext *ac, redisCallbackFn *fn, void *privdata,
  int argc, const char **argv, const size_t *argvlen);
```

这两个功能都像阻塞的API那样工作。 命令返回值是REDIS_OK表示已成功添加到输出缓冲区，否则就是REDIS_ERR。例如，当每个用户请求断开连接时，不会有新的命令添加到输出缓冲区，并且在调用redisAsyncCommand系列函数时返回REDIS_ERR。如果读取了具有NULL回调的命令的回复，则立即释放该回复。当一个命令的回调不是NULL时，内存在回调后立即被释放：回复数据仅在回调期间有效。当上下文遇到错误时，所有挂起的回调函数都会得到NULL的回复。

### Disconnecting

异步连接可以使用以下命令来终止：

```c
void redisAsyncDisconnect(redisAsyncContext *ac);
```

当这个函数被调用时，连接是not立即终止。相反，新命令不再被接受，连接只有在所有待处理的命令已经写入套接字，并且它们各自的应答已经被读取并且它们各自的回调已经被执行，连接才会终止。之后，断开回调以“REDIS_OK”状态执行，上下文对象被释放。

### Hooking it up to event library X

上下文对象创建后需要设置几个钩子函数。参考与libev和libevent绑定的apapters/。

## Reply parsing API

Hiredis提供了回复解析API，可以轻松编写更高级别的语言绑定。回复解析API由以下功能组成：

```c
redisReader *redisReaderCreate(void);
void redisReaderFree(redisReader *reader);
int redisReaderFeed(redisReader *reader, const char *buf, size_t len);
int redisReaderGetReply(redisReader *reader, void **reply);
```

在创建正常的Redis上下文时，hiredis在内部使用相同的一组函数，上面的API只是将其公开给用户以供直接使用。

### Usage

函数redisReaderCreate创建一个redisReader结构，它为协议解析器保存一个缓冲区，其中包含未分析的数据和状态。

传入数据 - 很可能来自套接字 - 可以使用redisReaderFeed放置在redisReader的内部缓冲区中。 这个函数会对由buf指向的长度为len缓冲区做一个拷贝 这个数据在调用redisReaderGetReply时被解析。 这个函数通过void ** reply返回一个整数状态和一个回复对象（如上所述）。 返回的状态可以是REDIS_OK或REDIS_ERR，后者意味着出了问题（协议错误或内存不足错误）。

解析器将多个批量有效负载的嵌套级别限制为7.如果多重批量嵌套级别高于此值，解析器将返回一个错误。

### Customizing replies

函数redisReaderGetReply创建redisReply，并使函数参数reply指向创建redisReply变量。 例如，如果“REDIS_REPLY_STATUS”类型的响应，则“redisReply”的“str”字段将保持状态为香草C字符串(a vanilla C string)。 但是，负责创建redisReply实例的函数可以通过在redisReader结构中设置fn字段来定制。 这应该在创建redisReader之后立即完成。例如，[hiredis-rb](https://github.com/pietern/hiredis-rb/blob/master/ext/hiredis_ext/reader.c)，使用自定义的回复对象函数来创建

### Reader max buffer

当直接使用Reader API或通过普通的Redis上下文间接使用Reader API时，redisReader结构使用缓冲区来累积服务器的数据。

通常这个缓冲区在空并且大于16 KiB的时候被释放，以避免在未使用的缓冲区中浪费内存。

但是，当处理非常大的有效载荷时，破坏缓冲区可能会显着降低性能，因此可以修改空闲缓冲区的最大大小，将读取器结构的maxbuf字段的值更改为所需的值。 0的特殊值意味着空闲缓冲区没有最大值，所以缓冲区永远不会被释放。

例如，如果你有一个正常的Redis上下文，你可以设置最大空闲缓冲区为零（无限），只需：

```c
context->reader->maxbuf = 0;
```

这应该只是为了在处理大型有效载荷时使性能最大化。 应尽快将上下文重新设置为REDIS_READER_MAX_BUF，以防止分配无用的内存。

# examples下的demo使用

路径: build_lib\examples\examples\3partlib\hiredis

代码:

```cpp
#include "CMyRedis.h"
#include "CErrorMsg.h"
#include <stdio.h>
#include <iostream>

int main()
{
	CMyRedis myRedis;

	try
	{
        //需要填写实际ip,port,密码
        //在docker容器执行时，不能填127.0.0.1
        //示例:myRedis.Connect("1.1.1.1", 6379,"123456")
		myRedis.Connect("127.0.0.1", 6379,"123456");

		std::cout << "connect success!" << std::endl;
		std::cout << myRedis.CheckConenct() << std::endl;
		myRedis.Set("hello", "world");
		std::cout << myRedis.Get("Work") << std::endl;
		myRedis.Set("set", "get");
		std::cout << myRedis.Get("hello") << std::endl;
        //....省略其他代码
    }
    catch (CErrorMsg &cErr)
	{
		printf("error code = %d, errmsg=%s, hint=%s \n", cErr.get_errorCode(), cErr.get_errorMsg().c_str(),cErr.get_errorHint().c_str());
	}

	return 0;
}
```


执行结果:

```
# 正常结果
[root@5d4b980baaa2 3partlib]#./hiredis/hiredis_Test
connect success!
...

# 异常结果
[root@5d4b980baaa2 3partlib]# ./hiredis/hiredis_Test
error code = 1, errmsg=Connection refused, hint=connect error!
```



