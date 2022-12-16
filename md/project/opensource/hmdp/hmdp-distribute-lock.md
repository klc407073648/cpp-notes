# hmdp - 分布式锁

# 分布式锁

## 基本原理和实现方式对比

> 分布式锁：满足分布式系统或集群模式下多进程可见并且互斥的锁。

核心思想：让大家都使用同一把锁，只要大家使用的是同一把锁，那么就能锁住线程，不让线程进行，让程序串行执行。

### 分布式锁应该满足一些什么样的条件？

![](/_images/project/opensource/hmdp/distribute-lock/分布式锁.png)

* 可见性：多个线程都能看到相同的结果，注意：这个地方说的可见性并不是并发编程中指的内存可见性，只是说多个进程之间都能感知到变化的意思

* 互斥：互斥是分布式锁的最基本的条件，使得程序串行执行

* 高可用：程序不易崩溃，时时刻刻都保证较高的可用性

* 高性能：由于加锁本身就让性能降低，所有对于分布式锁本身需要他就较高的加锁性能和释放锁性能

* 安全性：安全也是程序中必不可少的一环

## 常见的分布式锁有三种

* MySQL：MySQL本身就带有锁机制，但是由于MySQL性能本身一般，所以采用分布式锁的情况下，其实使用mysql作为分布式锁比较少见

* Redis：redis作为分布式锁是非常常见的一种使用方式，现在企业级开发中基本都使用redis或者zookeeper作为分布式锁，利用setnx这个方法，如果插入key成功，则表示获得到了锁，如果有人插入成功，其他人插入失败则表示无法获得到锁，利用这套逻辑来实现分布式锁

* Zookeeper：zookeeper也是企业级开发中较好的一个实现分布式锁的方案，由于本套视频并不讲解zookeeper的原理和分布式锁的实现，所以不过多阐述

**三者比较**

|        | MySQL                     | Redis                    | Zookeeper                      |
| ------ | ------------------------- | ------------------------ | ------------------------------ |
| 互斥   | 利用mysql本身的互斥锁机制 | 利用setnx这样的互斥命令  | 利用节点唯一性和有序性实现互斥 |
| 高可用 | 好                        | 好                       | 好                             |
| 高性能 | 一般                      | 好                       | 一般                           |
| 安全性 | 断开连接，自动释放锁      | 利用锁超时时间，到期释放 | 临时节点，断开连接自动释放锁   |

## Redis分布式锁的实现核心思路

实现分布式锁时需要实现的两个基本方法：

* 获取锁：

  * 互斥：确保只能有一个线程获取锁
  * 非阻塞：尝试一次，成功返回true，失败返回false

* 释放锁：

  * 手动释放
  * 超时释放：获取锁时添加一个超时时间


```lua
#添加锁 NX实现互斥，EX实现过期释放
SET lock thread1 NX EX 10
# 手动释放
DEL key
```

![](/_images/project/opensource/hmdp/distribute-lock/分布式锁获取和释放.png)

核心思路：

利用redis 的setnx 方法，当有多个线程进入时，我们就利用该方法，第一个线程进入时，redis 中就有这个key 了，返回了1，如果结果是1，则表示他抢到了锁，那么他去执行业务，然后再删除锁，退出锁逻辑，没有抢到锁的线程，等待一定时间后重试即可。

 ![](/_images/project/opensource/hmdp/distribute-lock/多线程抢占使用.png)

## 实现分布式锁

### 基于Redis实现分布式锁——初级版本

* 加锁

**锁的基本接口**

```java
public interface ILock {

    /**
     * 尝试获取锁
     * @param timeoutSec 锁持有的超时时间，过期后自动释放
     * @return true代表获取锁成功; false代表获取锁失败
     */
    boolean tryLock(long timeoutSec);

    /**
     * 释放锁
     */
    void unlock();
}
```

**SimpleRedisLock**

利用setnx方法进行加锁，同时增加过期时间，防止死锁，此方法可以保证加锁和增加过期时间具有原子性

```java
private static final String KEY_PREFIX="lock:"
@Override
public boolean tryLock(long timeoutSec) {
    // 获取线程标示
    String threadId = Thread.currentThread().getId()
    // 获取锁
    Boolean success = stringRedisTemplate.opsForValue()
            .setIfAbsent(KEY_PREFIX + name, threadId + "", timeoutSec, TimeUnit.SECONDS);
    return Boolean.TRUE.equals(success);
}
```

* 释放锁

SimpleRedisLock

释放锁，防止删除别人的锁

```java
public void unlock() {
    //通过del删除锁
    stringRedisTemplate.delete(KEY_PREFIX + name);
}
```

* 修改业务代码

```java
  @Override
    public Result seckillVoucher(Long voucherId) {
        // 1.查询优惠券
        SeckillVoucher voucher = seckillVoucherService.getById(voucherId);
        // 2.判断秒杀是否开始
        if (voucher.getBeginTime().isAfter(LocalDateTime.now())) {
            // 尚未开始
            return Result.fail("秒杀尚未开始！");
        }
        // 3.判断秒杀是否已经结束
        if (voucher.getEndTime().isBefore(LocalDateTime.now())) {
            // 尚未开始
            return Result.fail("秒杀已经结束！");
        }
        // 4.判断库存是否充足
        if (voucher.getStock() < 1) {
            // 库存不足
            return Result.fail("库存不足！");
        }
        Long userId = UserHolder.getUser().getId();
        //创建锁对象(新增代码)
        SimpleRedisLock lock = new SimpleRedisLock("order:" + userId, stringRedisTemplate);
        //获取锁对象
        boolean isLock = lock.tryLock(1200);
		//加锁失败
        if (!isLock) {
            return Result.fail("不允许重复下单");
        }
        try {
            //获取代理对象(事务)
            IVoucherOrderService proxy = (IVoucherOrderService) AopContext.currentProxy();
            return proxy.createVoucherOrder(voucherId);
        } finally {
            //释放锁
            lock.unlock();
        }
    }
```

#### 初级版本存在Redis分布式锁误删的问题

逻辑说明：

1. 持有锁的线程在锁的内部出现了阻塞，导致他的锁超时自动释放；
2. 此时，其他线程如线程2来尝试获得锁，就拿到了这把锁，然后线程2在持有锁执行过程中，线程1反应过来，继续执行，而线程1执行过程中，走到了删除锁逻辑，此时就会把本应该属于线程2的锁进行删除，这就是误删别人锁的情况

解决方案：

在每个线程释放锁的时候，去判断一下当前这把锁是否属于自己，如果属于自己，则不进行锁的删除。

假设还是上边的情况，线程1卡顿，锁自动释放，线程2进入到锁的内部执行逻辑，此时线程1反应过来，然后删除锁，但是线程1，一看当前这把锁不是属于自己，于是不进行删除锁逻辑，当线程2走到删除锁逻辑时，如果没有卡过自动释放锁的时间点，则判断当前这把锁是属于自己的，于是删除这把锁。

![](/_images/project/opensource/hmdp/distribute-lock/锁被其他线程误删.png)

### 改进Redis的分布式锁

需求：修改之前的分布式锁实现，满足：

1. 在获取锁时存入线程标示（可以用UUID表示）

2. 在释放锁时先获取锁中的线程标示，判断是否与当前线程标示一致

   * 如果一致则释放锁

   * 如果不一致则不释放锁


核心逻辑：在存入锁时，放入自己线程的标识，在删除锁时，判断当前这把锁的标识是不是自己存入的，如果是，则进行删除，如果不是，则不进行删除。

![](/_images/project/opensource/hmdp/distribute-lock/改进Redis的分布式锁逻辑.png)

具体代码如下：

* 加锁

```java
private static final String ID_PREFIX = UUID.randomUUID().toString(true) + "-";
@Override
public boolean tryLock(long timeoutSec) {
   // 获取线程标示
   String threadId = ID_PREFIX + Thread.currentThread().getId();
   // 获取锁
   Boolean success = stringRedisTemplate.opsForValue()
                .setIfAbsent(KEY_PREFIX + name, threadId, timeoutSec, TimeUnit.SECONDS);
   return Boolean.TRUE.equals(success);
}
```

* 释放锁

```java
public void unlock() {
    // 获取线程标示
    String threadId = ID_PREFIX + Thread.currentThread().getId();
    // 获取锁中的标示
    String id = stringRedisTemplate.opsForValue().get(KEY_PREFIX + name);
    // 判断标示是否一致
    if(threadId.equals(id)) {
        // 释放锁
        stringRedisTemplate.delete(KEY_PREFIX + name);
    }
}
```

**有关代码实操说明：**

修改完此处代码后，重启工程：

1. 启动两个线程，第一个线程持有锁后，手动释放锁；
2. 第二个线程 此时进入到锁内部，再放行第一个线程，此时第一个线程由于锁的value值并非是自己，所以不能释放锁，也就无法删除别人的锁；
3. 此时第二个线程能够正确释放锁。

通过这个案例初步说明我们解决了锁误删的问题。

## 分布式锁的原子性问题

更为极端的误删逻辑说明：

1. 线程1现在持有锁之后，在执行业务逻辑过程中，他正准备删除锁，而且已经走到了条件判断的过程中；
2. 比如线程1已经拿到了当前这把锁确实是属于他自己的，正准备删除锁时，但是锁超时到期了；
3. 此时线程2进来，仍然可以拿到锁，但是线程1卡顿结束后，会接着往后执行，他直接就会执行删除锁那行代码，相当于条件判断并没有起到作用，这就是**删锁时的原子性问题**。

之所以有这个问题，是因为线程1的拿锁，比锁，删锁，实际上并不是原子性的，要防止刚才的情况发生。

![](/_images/project/opensource/hmdp/distribute-lock/锁的原子性.png)

###  Lua脚本解决多条命令原子性问题

Redis提供了Lua脚本功能，在一个脚本中编写多条Redis命令，**确保多条命令执行时的原子性**。

Lua是一种编程语言，它的基本语法大家可以参考网站：[https://www.runoob.com/lua/lua-tutorial.html](https://www.runoob.com/lua/lua-tutorial.html)。

这里重点介绍Redis提供的调用函数，可以使用lua去操作redis，又能保证他的原子性，这样就可以实现拿锁、比锁、删锁是一个原子性动作了。

Redis提供的调用函数，语法如下：

```lua
redis.call('命令名称', 'key', '其它参数', ...)
```

例如，要执行set name jason，则脚本是这样：

```lua
redis.call('set', 'name', 'jason')
```

例如，要先执行set name json，再执行get name，则脚本如下：

```lua
# 先执行 set name jason
redis.call('set', 'name', 'jason')
# 再执行 get name
local name = redis.call('get', 'name')
# 返回
return name
```

写好脚本以后，需要用Redis命令来调用脚本，调用脚本的常见命令如下：

```lua
127.0.0.1:6379> help @scripting

  EVAL script numkeys key [key ...] arg [arg ...]
  summary: Execute a Lua script server side
  since: 2.6.0
```

例如，要执行 redis.call('set', 'name', 'jason') 这个脚本，语法如下：

```lua
127.0.0.1:6379> EVAL "redis.call('set', 'name', 'jason')" 0
(nil)
127.0.0.1:6379> get name
"jason"
```

如果脚本中的key、value不想写死，可以作为参数传递。key类型参数会放入KEYS数组，其它参数会放入ARGV数组，在脚本中可以从KEYS和ARGV数组获取这些参数：

下面例子中，1表示脚本需要的key类型的参数个数。

```lua
127.0.0.1:6379> EVAL "redis.call('set', KEYS[1], ARGV[1])" 1 phone 123456
(nil)
127.0.0.1:6379> get phone
"123456"
```

回顾前文的释放锁逻辑：

	1. 获取锁中的线程标示
	1. 判断是否与指定的标示（当前线程标示）一致
	1. 如果一致则释放锁（删除）
	1. 如果不一致则什么都不做

如果用Lua脚本来表示则是这样的，操作redis的拿锁比锁删锁的lua脚本就会变成这样：

```lua
-- 这里的 KEYS[1] 就是锁的key，这里的ARGV[1] 就是当前线程标示
-- 获取锁中的标示，判断是否与当前线程标示一致
if (redis.call('GET', KEYS[1]) == ARGV[1]) then
  -- 一致，则删除锁
  return redis.call('DEL', KEYS[1])
end
-- 不一致，则直接返回
return 0
```

### 利用Java代码调用Lua脚本改造分布式锁

lRedisTemplate中，可以利用execute方法去执行lua脚本，参数对应关系就如下图

![](/_images/project/opensource/hmdp/distribute-lock/Lua脚本实现分布式锁.png)

**Java代码**

```java
private static final DefaultRedisScript<Long> UNLOCK_SCRIPT;
    static {
        UNLOCK_SCRIPT = new DefaultRedisScript<>();
        UNLOCK_SCRIPT.setLocation(new ClassPathResource("unlock.lua"));
        UNLOCK_SCRIPT.setResultType(Long.class);
    }

public void unlock() {
    // 调用lua脚本
    stringRedisTemplate.execute(
            UNLOCK_SCRIPT,
            Collections.singletonList(KEY_PREFIX + name),
            ID_PREFIX + Thread.currentThread().getId());
}
经过以上代码改造后，我们就能够实现 拿锁比锁删锁的原子性动作了~
```

经过以上代码改造后，我们就能够实现 拿锁比锁删锁的原子性动作了。

## 总结

基于Redis的分布式锁实现思路：

* 利用set nx ex获取锁，并设置过期时间，保存线程标示
* 释放锁时先判断线程标示是否与自己一致，一致则删除锁

特性：
  * 利用set nx满足互斥性
  * 利用set ex保证故障时锁依然能释放，避免死锁，提高安全性
  * 利用Redis集群保证高可用和高并发特性

我们一路走来，利用添加过期时间，防止死锁问题的发生，但是有了过期时间之后，可能出现误删别人锁的问题，这个问题我们开始是利用删之前 通过拿锁，比锁，删锁这个逻辑来解决的，也就是删之前判断一下当前这把锁是否是属于自己的，但是现在还有原子性问题，也就是我们没法保证拿锁比锁删锁是一个原子性的动作，最后通过lua表达式来解决这个问题。

但是目前还剩下一个问题锁不住，什么是锁不住呢，你想一想，如果当过期时间到了之后，我们可以给他续期一下。

比如续个30s，就好像是网吧上网， 网费到了之后，然后说，来，网管，再给我来10块的，是不是后边的问题都不会发生了，那么续期问题怎么解决呢，可以依赖于后面要学习redission。

**测试逻辑：**

第一个线程进来，得到了锁，手动删除锁，模拟锁超时了，其他线程会执行lua来抢锁，当第一天线程利用lua删除锁时，lua能保证他不能删除他的锁，第二个线程删除锁时，利用lua同样可以保证不会删除别人的锁，同时还能保证原子性。
