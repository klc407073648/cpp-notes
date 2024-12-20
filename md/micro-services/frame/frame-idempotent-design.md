# 微服务 - 幂等性设计

> 本节主要介绍分布式系统中幂等性设计的内容。

[[toc]]

# 参考资料

* [幂等性解决方案](https://zhuanlan.zhihu.com/p/337245010)

* [分布式系统的接口幂等性设计](https://www.cnblogs.com/jack87224088/p/8688948.html)

# 幂等概念

幂等（idempotent、idempotence）是一个数学与计算机学概念，常见于抽象代数中。

* 编程中幂等操作的特点：<font color='red'>**任意多次执行所产生的影响均与一次执行的影响相同。**</font>
* 幂等函数，或幂等方法：可以使用相同参数重复执行，并能获得相同结果的函数。
* 这些函数不会影响系统状态，也不用担心重复执行会对系统造成改变。例如，“setTrue()”函数就是一个幂等函数,无论多次执行，其结果都是一样的.更复杂的操作幂等保证是利用唯一交易号(流水号)实现。

# 使用幂等的场景

## 前端数据重复提交

用户注册，用户创建商品、购买商品等操作，前端都会提交一些数据给后台服务。

后台需要根据用户提交的数据在数据库中创建记录。

如果用户不小心多点了几次，后端收到了多次提交，就会在数据库中重复创建了多条记录。这就是接口没有幂等性带来的 bug。

## 接口超时重试

对于给第三方调用的接口，有可能会因为网络原因而调用失败。一般在接口设计时，会添加**失败重试机制**。

如果第一次接口调用内容已经执行了一半时，发生了网络异常。这时再次调用时就会因为脏数据的存在而产生调用异常。

## 消息重复消费

在使用MQ消息中间件来处理消息队列，且手动 ack 确认消息被正常消费时。如果消费者突然断开连接，那么已经执行了一半的消息会重新放回队列。

当消息被其他消费者重新消费时，如果没有幂等性，就会导致消息重复消费时结果异常，如数据库重复数据，数据库数据冲突，资源重复等。

## 引入幂等性后对系统有什么影响

优点：

* 使调用接口保证任何幂等性操作，免去因重试等造成系统产生的未知的问题。

缺点：

* 增加了服务端的逻辑复杂性和成本

* 把并行执行的功能改为串行执行，降低了执行效率
* 增加了额外控制幂等的业务逻辑，复杂化了业务功能

因此，在使用时候需要考虑是否引入幂等性的必要性，根据实际业务场景具体分析，除了业务上的特殊要求外，一般情况下不需要引入的接口幂等性。

## Restful API 接口幂等性

| 方法类型 | 是否幂等 | 描述                                                         |
| -------- | -------- | ------------------------------------------------------------ |
| Get      | √        | get方法用于获取资源，不应有副作用，因此是幂等的。            |
| Post     | ×        | post方法用于创建资源，每次请求都会产生新的资源，因此不具备幂等性。 |
| Put      | -        | put方法用于更新资源。如果更新的是值，则为幂等；如果执行累加操作的更新是非幂等。 |
| Delete   | -        | delete方法用于删除资源。如果是根据唯一值进行删除，则为幂等；如果式带查询条件的删除就不是幂等了，例如在根据条件删除数据后，新增一条数据也满足该条件，然后再次执行删除，会导致新增的数据被删除。 |

# 保证幂等性的方法

**1.MVCC方案**

* 多版本并发控制，该策略主要使用<font color='red'>**update with condition（更新带条件）来保证多次外部请求调用对系统的影响是一致的。**</font>在系统设计的过程中，合理的使用乐观锁，通过version或者updateTime（timestamp）等其他条件，来做乐观锁的判断条件，这样保证更新操作即使在并发的情况下，也不会有太大的问题。例如

```
select * from tablename where condition=#condition# //取出要跟新的对象，带有版本versoin
update tableName set name=#name#,version=version+1 where version=#version#
```

　　在更新的过程中利用version来防止，其他操作对对象的并发更新，导致更新丢失。为了避免失败，通常需要一定的重试机制。

**2.去重表**

* 适用于在业务中有唯一标识的插入场景中。例如在支付场景中，如果一个订单只会支付一次，所以订单ID可以作为唯一标识。这时，我们就可以建一张去重表，并且把唯一标识作为唯一索引，在我们实现时，把创建支付单据和写入去重表，放在一个事务中，如果重复创建，数据库会抛出唯一约束异常，操作就会回滚。

**3.悲观锁**

* 使用select for update的方法，整个执行过程中锁定该订单对应的记录。注意**：这种在DB读大于写的情况下尽量少用**。

* 作用：<font color='red'>**select for update 是为了在查询时，避免其他用户以该表进行插入,修改或删除等操作,造成表的不一致性。**</font>

**4. select + insert**

* 在系统并发量不高或者一些特定任务流程，为了支持幂等，支持重复执行。最简单的处理方法是，先查询下对应关联数据，判断是否已经执行过，再进行业务处理，就可以了。注意**：核心高并发流程不要用这种方法**。

**5.状态机幂等**

* 在设计单据或任务相关的业务时，必然会涉及到状态机，即业务单据上面有个状态，状态在不同的情况下会发生变更。一般情况下存在有限状态机，这时候，如果状态机已经处于下一个状态，这时候来了一个上一个状态的变更，理论上是不能够变更的，这样的话，保证了有限状态机的幂等。例如，订单创建为状态0，付款成功为状态1，付款失败为状态-1。

**6. token机制，防止页面重复提交**

　　业务要求：页面的数据只能被点击提交一次
　　发生原因：由于重复点击或者网络重发，或者nginx重发等情况会导致数据被重复提交
解决办法：

- 集群环境：采用token加redis（redis单线程的，处理需要排队）
- 单JVM环境：采用token加redis或token加jvm内存

处理流程：

- 数据提交前要向服务的申请token，token放到redis或jvm内存，token有效时间
- 提交后后台校验token，同时删除token，生成新的token返回

　　token特点:要申请，一次有效性，可以限流 

**7.全局唯一ID**

* 如果使用全局唯一ID，就是根据业务的操作和内容生成一个全局ID，在执行操作前先根据这个全局唯一ID是否存在，来判断这个操作是否已经执行。如果不存在则把全局ID，存储到存储系统中，比如数据库、redis等。如果存在则表示该方法已经执行。

**8. 对外提供接口的api如何保证幂等** 

* 例如银联提供的付款接口：需要接入商户提交付款请求时附带：source来源，seq序列号。source+seq在数据库里面做唯一索引，防止多次付款，(并发时，只能处理一个请求)

# 总结

幂等性是程序开发当中很常见也很重要的需求，尤其是**支付**、**订单**等与金钱挂钩的服务，保证接口幂等性尤其重要。在实际开发中，我们需要针对不同的业务场景我们需要灵活的选择幂等性的实现方式：

1. 对于下单等存在唯一主键的，可以使用“**唯一主键方案**”的方式实现。
2. 对于更新订单状态等相关的更新场景操作，使用“**乐观锁方案**”实现更为简单。
3. 对于上下游这种，下游请求上游，上游服务可以使用“**下游传递唯一序列号方案**”更为合理。
4. 类似于**前端重复提交**、**重复下单**、**没有唯一ID号**的场景，可以通过 `Token` 与 `Redis` 配合的“**防重 Token 方案**”实现更为快捷。
