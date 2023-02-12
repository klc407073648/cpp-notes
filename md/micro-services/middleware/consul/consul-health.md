# Consul - 服务健康检查

[[toc]]

> TODO 待补充

# 参考

* [consul 服务健康检查](https://blog.csdn.net/xixihahalelehehe/article/details/108165840)
* [Consul 使用手册](https://blog.csdn.net/liuzhuchen/article/details/81913562)


```json
{
	"datacenter": "datacenter1",
	"data_dir": "/home/consul/data",
	"log_level": "INFO",
	"node_name": "server_node",
	"server": true,
	"ui": true,
	"bootstrap_expect": 1,
	"bind_addr": "0.0.0.0",
	"client_addr": "0.0.0.0",
	"ports": {
		"server": 8300,
		"serf_lan": 8301,
		"serf_wan": 8302,
		"http": 8500,
		"dns": 8600
	}
}
```

