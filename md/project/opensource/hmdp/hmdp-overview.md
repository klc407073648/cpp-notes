# hmdp - 概览

# 概述

hmdp项目来自于 [黑马程序员Redis入门到实战教程](https://www.bilibili.com/video/BV1cr4y1671t/)，对于视频中所学到的知识进一步总结归纳，主要分为以下几个部分：

* 短信登录
  * 使用redis共享session来实现

* 商户查询缓存
  * 理解缓存击穿，缓存穿透，缓存雪崩等问题，通过代码进行实践

* 优惠卷秒杀
  * 学会Redis的计数器功能，结合Lua完成高性能的redis操作，同时学会Redis分布式锁的原理，包括Redis的三种消息队列

* 附近的商户
  * 利用Redis的GEOHash来完成对于地理坐标的操作

* UV统计
  * 使用Redis来完成统计功能

* 用户签到
  * 使用Redis的BitMap数据统计功能

* 好友关注
  * 基于Set集合的关注、取消关注，共同关注等等功能，这一块知识咱们之前就讲过，这次我们在项目中来使用一下

* 达人探店
  * 基于List来完成点赞列表的操作，同时基于SortedSet来完成点赞的排行榜功能

总体内容图如下：

![黑马点评](/_images/project/opensource/hmdp/msglogin/黑马点评.png)

