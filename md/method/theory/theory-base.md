# 分布式理论 - BASE

[[toc]]

> BASE理论的核心思想是**即使无法做到强一致性，应用也可以采用适合的方式达到最终一致性**。

# 概念

- **Basically Available （基本可用）**：分布式系统在出现故障时，允许损失部分可用性，即保证核心可用。
- **Soft State（软状态）**：允许系统中的数据存在中间状态，并认为该中间状态的存在不会影响系统的整体可用性，即允许系统在不同节点的数据副本之间进行数据同步的过程存在延时。
- **Eventually Consistent（最终一致性）**：虽然无法保证强一致性，但是在软状态结束后，系统中所有的数据副本经过一定时间后，最终能够达到一致的状态。

![BASE](/_images/method/theory/BASE.png)

BASE理论本质上是对CAP理论的延伸和补充，更具体地说，是对 CAP 中 AP 方案的一个补充。

前面在剖析 CAP 理论时，提到了其实和 BASE 相关的两点：

* CAP 理论是忽略延时的，而实际应用中延时是无法避免的。
    * 这一点就意味着完美的 CP 场景是不存在的，即使是几毫秒的数据复制延迟，在这几毫秒时间间隔内，系统是不符合 CP 要求的。因此 CAP 中的 CP 方案，**实际上也是实现了最终一致性，只是“一定时间”是指几毫秒而已**。

* AP 方案中牺牲一致性只是指分区期间，而不是永远放弃一致性。
    * 这一点其实就是 BASE 理论延伸的地方，分区期间牺牲一致性，但分区故障恢复后，系统应该达到最终一致性。

综合上面的分析，ACID 是数据库事务完整性的理论，CAP 是分布式系统设计理论，BASE 是 CAP 理论中 AP 方案的延伸。

# 一致性思想

在分布式系统中，无法保证强一致性，**因为短暂的数据存在延迟是允许的，但是最终数据一定要保持数据一致性**。

强一致性

各个副本的数据在物理存储中总是一致的； 数据更新操作结果和操作响应总是一致的， 即操作响应通知更新失败，那么数据一定没有被更新， 而不是处于不确定状态。

但是在分布式系统中这种强一致性是不可能存在的，各个服务之间在网络通讯的情况下，肯定存在延迟或者故障的。

弱一致性

即数据在物理存储中的各个副本的数据可能是不一致的，但是终端用户访问时，通过纠错和校验机制，可以确定一个一致的且正确的数据返回给用户。

最终一致性

物理存储的数据可能是不一致的，终端用户访问到的数据可能也是不一致的（同一用户连续访问，结果不同；或者不同用户同时访问，结果不同），但系统经过一段时间（通常是一个比较短的时间段） 的自我恢复和修正， 数据最终会达到一致。

因为难以满足数据强一致性，网站通常会综合成本、技术、业务场景等条件，结合应用服务和其他的数据监控与纠错功能，使存储系统达到用户一致，保证最终用户访问数据的正确性。


