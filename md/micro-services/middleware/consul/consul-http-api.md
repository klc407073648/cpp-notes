# Consul - 常用的API

> 本文主要介绍使用Consul注册中心的过程中，涉及到服务注册，服务注销，服务列表查询，检查点列表查询，检查点注销等等Http的API。

* Consul提供RESTful HTTP API，可以提供对节点，服务，检查，配置的CRUD操作。

[[toc]]

# 参考

* [consul HTTP API](https://www.consul.io/api-docs)
* [注册中心API](https://blog.csdn.net/chi0830/article/details/100590027)

# API 特点

## 过滤

```
curl --get localhost:8500/v1/agent/services --data-urlencode 'filter=ID ="web-server1"'
curl --get localhost:8500/v1/agent/services --data-urlencode 'filter=Port == "9000"'
```

# Consul 注册相关API

## 服务注册接口

命令:
```
curl -X PUT --data @redis.json http://localhost:8500/v1/agent/service/register
```

redis.json:
```json
{
  "ID": "redis1",
  "Name": "redis",
  "Tags": ["primary", "v1"],
  "Address": "127.0.0.1",
  "Port": 9000,
  "Meta": {
    "redis_version": "4.0"
  },
  "EnableTagOverride": false,
  "Check": {
    "DeregisterCriticalServiceAfter": "90m",
    "HTTP": "https://redis.io/",
    "Interval": "10s"
  },
  "Weights": {
    "Passing": 10,
    "Warning": 1
  }
}

报错：
{
  "ID": "redis1",
  "Name": "redis",
  "Tags": [
    "primary",
    "v1"
  ],
  "Address": "127.0.0.1",
  "Port": 8000,
  "Meta": {
    "redis_version": "4.0"
  },
  "EnableTagOverride": false,
  "Check": {
    "DeregisterCriticalServiceAfter": "90m",
    "Args": ["/usr/local/bin/check_redis.py"],
    "HTTP": "http://localhost:5000/health",
    "Interval": "10s",
    "TTL": "15s"
  },
  "Weights": {
    "Passing": 10,
    "Warning": 1
  }

```


会报错，Scripts are disabled on this agent from remote calls; to enable, configure 'enable_script_checks' to true，在docker启动参数中加上-enable-script-checks即可

## 服务查询接口

查询服务是以注册的服务Name字段查询。

命令：

```
curl http://localhost:8500/v1/agent/services
curl http://localhost:8500/v1/catalog/service/redis  #redis 是Name
```

返回：

```
[root@5d89639b9f5e home]# curl http://127.0.0.1:8500/v1/agent/services
{"redis1":{"ID":"redis1","Service":"redis","Tags":["primary","v1"],"Meta":{"redis_version":"4.0"},"Port":9000,"Address":"127.0.0.1","TaggedAddresses":{"lan_ipv4":{"Address":"127.0.0.1","Port":9000},"wan_ipv4":{"Address":"127.0.0.1","Port":9000}},"Weights":{"Passing":10,"Warning":1},"EnableTagOverride":false,"Datacenter":"dc1"},"test-service1":{"ID":"test-service1","Service":"test-service1","Tags":["test","v1"],"Meta":{"X-TAG":"testtag"},"Port":8000,"Address":"127.0.0.1","TaggedAddresses":{"lan_ipv4":{"Address":"127.0.0.1","Port":8000},"wan_ipv4":{"Address":"127.0.0.1","Port":8000}},"Weights":{"Passing":1,"Warning":1},"EnableTagOverride":false,"Datacenter":"dc1"}}[
```

## 服务注销接口

注销服务是使用注册的服务ID字段。

命令：

```
curl -X PUT http://127.0.0.1:8500/v1/agent/service/deregister/redis1 #redis1 是ID
```

返回：

```
[]
```

## 检查点查询接口

命令：

```
curl http://127.0.0.1:8500/v1/agent/checks
```

返回：

```
[root@5d89639b9f5e /]# curl http://127.0.0.1:8500/v1/agent/checks
{"service:test-service1":{"Node":"node2","CheckID":"service:test-service1","Name":"Service 'test-service1' check","Status":"passing","Notes":"","Output":"HTTP GET http://zhihu.com: 200 OK Output: :{\"editingSubtitleItem\":{},\"editingVideoItem\":{}},\"selectedTrackItems\":[],\"outlineRemoveMaterial\":{},\"outlineAppliedStyle\":{},\"timbres\":[],\"timbreId\":\"\",\"timbreTests\":[],\"newRecordBlob\":{},\"exportErrorUrls\":[],\"defaultTimbreId\":\"1\"}},\"readStatus\":{},\"draftHistory\":{\"history\":{},\"drafts\":{}},\"notifications\":{\"recent\":{\"isFetching\":false,\"isDrained\":false,\"isPrevDrained\":false,\"result\":[],\"next\":null,\"key\":null},\"history\":{\"isFetching\":false,\"isDrained\":false,\"isPrevDrained\":false,\"result\":[],\"next\":null,\"key\":null},\"notificationActors\":{\"isFetching\":false,\"isDrained\":false,\"isPrevDrained\":false,\"result\":[],\"next\":null,\"key\":null},\"recentNotificationEntry\":\"all\"},\"specials\":{\"entities\":{},\"all\":{\"data\":[],\"paging\":{},\"isLoading\":false}},\"collections\":{\"hot\":{\"data\":[],\"paging\":{},\"isLoading\":false},\"collectionFeeds\":{}},\"userProfit\":{\"permission\":{\"permissionStatus\":{\"zhiZixuan\":0,\"recommend\":-1,\"task\":0,\"plugin\":0,\"infinity\":0},\"visible\":false}},\"mcn\":{\"bindInfo\":{},\"memberCategoryList\":[],\"producerList\":[],\"categoryList\":[],\"lists\":{},\"banners\":{},\"protocolStatus\":{\"isAgreedNew\":true,\"isAgreedOld\":true},\"probationCountdownDays\":0},\"mcnActivity\":{\"household\":{\"products\":{},\"rankList\":{\"total\":{},\"yesterday\":{}}}},\"brand\":{\"contentPlugin\":{}},\"host\":{\"roundtable\":{\"subjects\":{},\"applications\":{\"total\":0},\"online\":{\"total\":0},\"applies\":{},\"details\":{},\"includedResource\":{},\"hotQuestions\":{},\"warmupContents\":{},\"batchInclude\":{}},\"special\":{\"applications\":{\"total\":0,\"pages\":{},\"entities\":{}},\"censorHistory\":{},\"drafts\":{}}},\"campaign\":{\"single\":{},\"list\":{},\"videoMakerAcq\":{},\"vote\":{},\"cardCollecting\":{\"message\":null,\"profile\":{\"balance\":\"0\",\"chance\":0,\"coinNum\":0,\"gatherClose\":false,\"isGotMagicCard\":false,\"isPay\":false,\"partitionStart\":false,\"totalDone\":0,\"withdrawStart\":false},\"sharePoster\":{\"share\":\"\",\"sendCard\":\"\",\"invite\":\"\"},\"shareLink\":null,\"shareIntention\":\"share\",\"shareKey\":null,\"shareCardId\":null,\"inviterInfo\":null,\"giverInfo\":null,\"prize\":null,\"receivedCard\":null,\"newCoinCount\":null,\"newCardList\":[],\"newUserCardCount\":1,\"taskList\":[],\"prizeList\":null,\"cardList\":null,\"panel\":{\"showTaskPanel\":false,\"showRewardPanel\":false},\"modal\":{\"showWelcomeModal\":false,\"showFusionModal\":false,\"showFusionPromptModal\":false,\"showShareModal\":false,\"showBackModal\":false}},\"zhiboPandian2020\":null,\"boarding\":{},\"searchGaokaoSubPage\":{},\"searchHealth\":{}},\"knowledgePlan\":{\"lists\":{},\"allCreationRankList\":{},\"featuredQuestions\":{}},\"wallE\":{\"protectHistory\":{\"total\":0,\"pages\":{},\"entities\":{}}},\"roundtables\":{\"hotQuestions\":{},\"warmupContents\":{},\"hotDiscussions\":{},\"selectedContents\":{},\"roundtables\":{}},\"helpCenter\":{\"entities\":{\"question\":{},\"category\":{}},\"categories\":[],\"commonQuestions\":[],\"relatedQuestions\":{}},\"republish\":{},\"commercialReport\":{\"commercialTypes\":[]},\"creatorMCN\":{\"mcn\":{},\"mcnStatistics\":{},\"isNoAuth\":false,\"creatorManageData\":[],\"creatorManageDataTotal\":1,\"mcnDomains\":[]},\"commentManage\":{\"commentList\":{\"ids\":[],\"entities\":{},\"nextOffset\":0,\"urlToken\":\"\"},\"subCommentList\":{\"ids\":[],\"entities\":{},\"paging\":{\"next\":\"\",\"isEnd\":false}}},\"zhiPlus\":{\"permissionStatus\":9999},\"streaming\":{},\"creationRanking\":{}},\"subAppName\":\"main\"}\u003c/script\u003e\u003cscript crossorigin=\"\" src=\"https://static.zhihu.com/heifetz/vendor.af68afae9067da0868d6.js\"\u003e\u003c/script\u003e\u003cscript crossorigin=\"\" src=\"https://static.zhihu.com/heifetz/main.lib_09e9ad9b.eaf491b2b867f9bbc6bf.js\"\u003e\u003c/script\u003e\u003cscript crossorigin=\"\" src=\"https://static.zhihu.com/heifetz/main.lib_5c7e3f8e.fe0aed30210ee0d5b7c9.js\"\u003e\u003c/script\u003e\u003cscript crossorigin=\"\" src=\"https://static.zhihu.com/heifetz/main.app.31c1cc434921c8b08cca.js\"\u003e\u003c/script\u003e\u003cscript crossorigin=\"\" src=\"https://static.zhihu.com/heifetz/main.shared_d1ef5af0010fdbecda3e7215eeb794b639ace47a.066a3b21675e0b5b6a6c.js\"\u003e\u003c/script\u003e\u003cscript crossorigin=\"\" src=\"https://static.zhihu.com/heifetz/main.sign-page.47459eaea7b8fb50e64b.js\"\u003e\u003c/script\u003e\u003cscript defer=\"\" src=\"//www.zhihu.com/wza/aria.js?appid=a3637ace5dc3a347f6863b0bac487599\"\u003e\u003c/script\u003e\u003c/body\u003e\u003cscript src=\"https://hm.baidu.com/hm.js?98beee57fd2ef70ccdd5ca52b9740c49\" async=\"\"\u003e\u003c/script\u003e\u003c/html\u003e","ServiceID":"test-service1","ServiceName":"test-service1","ServiceTags":["test","v1"],"Type":"http","Interval":"10s","Timeout":"","ExposedPort":0,"Definition":{},"CreateIndex":0,"ModifyIndex":0}}[
```

## 检查点注销接口

命令：

```
curl -X PUT http://127.0.0.1:8500/v1/agent/check/deregister/service:web-server1
```

返回：

```
[]
```

```
[root@VM-16-6-centos home]# docker ps |grep agent1
7ab7834bf646   consul:1.7.1          "docker-entrypoint.s…"   26 minutes ago   Up 21 minutes   8300-8302/tcp, 8301-8302/udp, 8600/tcp, 8600/udp, 0.0.0.0:8500->8500/tcp, :::8500->8500/tcp   agent1


8500 http 端口，用于 http 接口和 web ui
8300 server rpc 端口，同一数据中心 consul server 之间通过该端口通信
8301 serf lan 端口，同一数据中心 consul client 通过该端口通信
8302 serf wan 端口，不同数据中心 consul server 通过该端口通信
8600 dns 端口，用于服务发现
-bbostrap-expect 2: 集群至少两台服务器，才能选举集群leader
-ui：运行 web 控制台
-bind： 监听网口，0.0.0.0 表示所有网口，如果不指定默认未127.0.0.1，则无法和容器通信
-client ： 限制某些网口可以访问
```

# 健康检查实例

web.json，定义web网页的端口：

```json
{
    "ID": "web-server1",
    "Name": "web-server1",
    "Tags": [
        "stibel_web",
        "v1"
    ],
    "Address": "139.196.82.84",
    "Port": 4300,
    "Meta": {
        "X-TAG": "testtag"
    },
    "EnableTagOverride": false,
    "Check": {
        "DeregisterCriticalServiceAfter": "90m",
        "HTTP": "http://139.196.82.84:4300/",
        "Interval": "5s"
    }
}
```

使用方法：

```
[root@5d89639b9f5e home]# touch web.json
[root@5d89639b9f5e home]# vi web.json
[root@5d89639b9f5e home]# curl -X PUT --data @web.json http://localhost:8500/v1/agent/service/register


[root@iZuf61kbf845xt6tz10abgZ test]# docker stop stibel_nginx_web_0
stibel_nginx_web_0
[root@iZuf61kbf845xt6tz10abgZ test]# docker start stibel_nginx_web_0
stibel_nginx_web_0
```

# 其他常用API

## 获取集群信息

```
curl http://localhost:8500/v1/status/peers        #查看集群server成员
curl http://localhost:8500/v1/status/leader       #集群 Raf leader
curl http://localhost:8500/v1/catalog/services    #注册的所有服务
curl http://localhost:8500/v1/catalog/service/test-service1

curl http://localhost:8500/v1/catalog/nginx       #查看 nginx 服务信息
curl http://localhost:8500/v1/catalog/nodes       #集群节点详细信息
```

## agent

agent endpoints用来和本地agent进行交互，一般用来服务注册和检查注册，支持以下接口

```
/v1/agent/checks : 返回本地agent注册的所有检查(包括配置文件和HTTP接口)
/v1/agent/services : 返回本地agent注册的所有服务
/v1/agent/members : 返回agent在集群的gossip pool中看到的成员
/v1/agent/self : 返回本地agent的配置和成员信息
/v1/agent/join/<address> : 触发本地agent加入node
/v1/agent/force-leave/<node>>: 强制删除node
/v1/agent/check/register : 在本地agent增加一个检查项，使用PUT方法传输一个json格式的数据
/v1/agent/check/deregister/<checkID> : 注销一个本地agent的检查项
/v1/agent/check/pass/<checkID> : 设置一个本地检查项的状态为passing
/v1/agent/check/warn/<checkID> : 设置一个本地检查项的状态为warning
/v1/agent/check/fail/<checkID> : 设置一个本地检查项的状态为critical
/v1/agent/service/register : 在本地agent增加一个新的服务项，使用PUT方法传输一个json格式的数据
/v1/agent/service/deregister/<serviceID> : 注销一个本地agent的服务项12345678910111213
```

## catalog

catalog endpoints用来注册/注销nodes、services、checks

```
/v1/catalog/register : Registers a new node, service, or check
/v1/catalog/deregister : Deregisters a node, service, or check
/v1/catalog/datacenters : Lists known datacenters
/v1/catalog/nodes : Lists nodes in a given DC
/v1/catalog/services : Lists services in a given DC
/v1/catalog/service/<service> : Lists the nodes in a given service
/v1/catalog/node/<node> : Lists the services provided by a node1234567
```

## health

health endpoints用来查询健康状况相关信息，该功能从catalog中单独分离出来

```
/v1/healt/node/<node>: 返回node所定义的检查，可用参数?dc=
/v1/health/checks/<service>: 返回和服务相关联的检查，可用参数?dc=
/v1/health/service/<service>: 返回给定datacenter中给定node中service
/v1/health/state/<state>: 返回给定datacenter中指定状态的服务，state可以是"any", "unknown", "passing", "warning", or "critical"，可用参数?dc=1234
```

## session

session endpoints用来create、update、destory、query sessions

```
/v1/session/create: Creates a new session
/v1/session/destroy/<session>: Destroys a given session
/v1/session/info/<session>: Queries a given session
/v1/session/node/<node>: Lists sessions belonging to a node
/v1/session/list: Lists all the active sessions12345
```

## acl

acl endpoints用来create、update、destory、query acl

```
/v1/acl/create: Creates a new token with policy
/v1/acl/update: Update the policy of a token
/v1/acl/destroy/<id>: Destroys a given token
/v1/acl/info/<id>: Queries the policy of a given token
/v1/acl/clone/<id>: Creates a new token by cloning an existing token
/v1/acl/list: Lists all the active tokens123456
```

## event

event endpoints用来fire新的events、查询已有的events

```
/v1/event/fire/<name>: 触发一个新的event，用户event需要name和其他可选的参数，使用PUT方法
/v1/event/list: 返回agent知道的events12
```

## status

status endpoints用来或者consul 集群的信息

```
/v1/status/leader : 返回当前集群的Raft leader
/v1/status/peers : 返回当前集群中同事
```
