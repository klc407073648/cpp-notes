# 编码规范 - 编码命名规范

> 项目内统一即可，不同的公司也有各自偏爱的命名规范，没有好坏之分。

[[toc]]

# 模块

* 模块名必须是名称，且保证是小写，例如，告警（fm），性能（pm）

# 文件夹

必须是名词，且与namespace的层次相同，包含 include 和source（或src）

```cpp
#include "Poco/Data/MySQL/Connector.h"
对应
poco-master/Data/MySQL/include/Poco/Data/MySQL/Connector.h

poco-master\Data\MySQL
下面有include 和src
```

# 文件名

* 驼峰命名法 ，MySQLException.cpp      Poco
* 文件名要全部小写，gtest-printers.cc  gTest

## 文件内容

每一个类一个文件

### namespace

1. 名词，所有字母小写。
2. 按模块、业务分层，采用多层namespace,
    * 命名空间以小写字母命名. 最高级命名空间的名字取决于项目名称。
    * 顶级命名空间的名称应当是项目名或者是该命名空间中的代码所属的团队的名字
3. namespace左对齐，不缩进。

但是, Poco库也存在不满足上述要求的情况

```cpp
namespace Poco {
namespace Data {
namespace MySQL {
    ...
} } } // namespace Poco::Data::MySQL
```

# 类(结构体)名

1. 类名为单一名词或定语加名词，不能多个定语加名词·
2. 采用驼峰命名法。每一个单字的首字母都采用大写字母。
  * 所有类型命名 —— 类, 结构体, 类型定义 ( typedef ), 枚举, 类型模板参数 —— 均使用相同约定, 即以大写字母开始, 每个单词首字母均大写, 不包含下划线

```cpp
//正例
namespace HttpType {

    class HttpIpType

class Mylog
//反例
namespace HttpType {

    class http_ip_type
```

3. 类声明、定义左对齐，不缩进。

```cpp
//正例
namespace Poco {
namespace Data {
namespace MySQL {

class MySQL_API MySQLException: public Poco::Data::DataException
//反例
namespace Poco {
namespace Data {
namespace MySQL {

    class MySQL_API MySQLException: public Poco::Data::DataException
```

4. 信息与namespace不重复。

```cpp
//正例
namespace Http2Proxy {
namespace Client {

class Session
//反例
namespace Http2Proxy {
namespace Client {

class Http2ProxyClientSession
```

# 类成员

1. 采用蛇形命名法，全部字母小写。
2. 后接下划线

```cpp
//Poco里是前接下划线
```

3. 类成员不要定义为public
4. 名称不包含类信息

```cpp
//正例
Http2ProxyClientSession session_
//反例
Http2ProxyClientSession http2ProxyClientSession_
```

# 宏定义

全部大写，中间用“_”分隔，例如 TOTAL_NUM

# 枚举

* 枚举名称，驼峰
* 枚举值，全部大写，中间用“_”分隔

```cpp
enum MsgType
{
    MSG_SEND_SESSION_ID     = 0,
    MSG_ADD_EVENT           = 100,
}
```

# 全局变量，静态变量, 成员变量, 局部变量

* 全局变量用g_开头,如一个全局的长型变量定义为g_lFailCount
* 静态变量用s_开头,如一个静态的指针变量定义为s_plPerv_Inst
* 成员变量用m_开头,如一个长型成员变量定义为m_lCount
* 局部变量用l_开头,如一个整型局部变量定义为l_inum

# 函数名

* 名词，或者动宾结构
* 名称不包含 namespace

* 常规函数使用大小写混合, 取值和设值函数则要求与变量名匹配
    * 一般来说, 函数名的每个单词首字母大写 (即 “驼峰变量名” 或 “帕斯卡变量名”), 没有下划线. 对于首字母缩写的单词, 更倾向于将它们视作一个单词进行首字母大写 (例如, 写作 StartRpc() 而非 StartRPC() )