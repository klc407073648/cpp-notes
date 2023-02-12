# Consul - 存储个K/V

[[toc]]

## 使用

设置一个值到user/config/connections 内容为5

```
consul kv put user/config/connections 5
```

获取特定的值:

```
[root@5d89639b9f5e home]# consul kv get -detailed user/config/connections
CreateIndex      203
Flags            0
Key              user/config/connections
LockIndex        0
ModifyIndex      203
Session          -
Value            5

```

