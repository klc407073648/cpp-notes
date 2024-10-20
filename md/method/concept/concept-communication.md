# 概念 - 计算机专有名词

## 安全通信

* [浅谈SSL/TLS工作原理](https://zhuanlan.zhihu.com/p/36981565)
* [gRPC 官方文档中文版](http://doc.oschina.net/grpc?t=58010)

### 专有名词

* TLS(Transport Layer Security,传输层安全性协议); 及其前身SSL(Secure Sockets Layer,安全套接层)

* DES(Data Encryption Standard, 数据加密标准)

* AES(Advanced Encryption Standard,高级加密标准)

* CA(Certificate Authority,CA证书授权)

SSL/TLS目的是为**互联网通信提供安全及数据完整性保障**。

**加密算法发展过程**：

1. 对称加密算法(DES,AES) :双方共享密钥

2.  非对称加密算法(RSA) :非对称加密有一对密钥，公钥和私钥。可以用公钥加密,私钥解密;也可以用私钥加密，公钥解密。

3. CA 证书：通过CA（Certificate Authority）来保证public key的真实性。

**实际使用**：

- 通过CA体系交换public key
- 通过非对称加密算法，交换用于对称加密的密钥
- 通过对称加密算法，加密正常的网络通信
