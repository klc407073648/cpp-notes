# Logstash - 工作原理

[[toc]]

# 内容

Logstash 包含3个主要部分： <font color='red'>输入（inputs），过滤器（filters）和输出（outputs）</font>。 你必须定义这些过程的配置才能使用 Logstash，尽管不是每一个都必须的。在有些情况下，我们可以甚至没有过滤器。在过滤器的部分，它可以对数据源的数据进行分析，丰富，处理等等。

 ![work_flow](/_images/micro-services/middleware/logstash/work_flow.png)

与其相关的插件：

 ![plugins](/_images/micro-services/middleware/logstash/plugins.png)

在下面的图中，我们可以看到一些常见的 inputs, filters 及 outputs:

![use_plugins](/_images/micro-services/middleware/logstash/use_plugins.png)


