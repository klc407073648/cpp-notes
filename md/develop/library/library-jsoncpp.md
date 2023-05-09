# 常用开发库 - jsoncpp

# 参考资料

* [JsonCpp 使用指导](https://blog.csdn.net/bluebird_shao/article/details/125444805)
* [jsoncpp源码库](https://github.com/open-source-parsers/jsoncpp)

# 概述

> JSON 是一种轻量级数据交换格式。它可以表示数据、字符串、有序的值序列以及名称/值对的集合。

> JsonCpp 是一个 C++ 库，允许操作 JSON 值，包括字符串之间的序列化和反序列化。它还可以在反序列化/序列化步骤中保留现有注释，使其成为存储用户输入文件的方便格式。

## 使用方法

头文件中包含了 **Reader, Writer, Value** 这三个重要的类。

```cpp
#include <json/json.h>
```

按照**国际惯例，每一项技术的学习都可以从 “Hello World” 开始**，以下面的 json 字符串为例：

```cpp
#include <string>
#include <iostream>
#include <json/json.h>

int main(int argc, char const *argv[])
{
    std::string str = "{\"content\": \"Hello World\"}";

    Json::Reader reader;
    Json::Value root;
    if (reader.parse(str, root))
        std::cout << root["content"].asString() << std::endl;
    
    return 0;
}
```

## 读写文件常用的库

```cpp
#include <iostream> //读写io c++标准库
#include <fstream> //读写文件 c++标准库
#include <string> //字符串类 c++标准库
#include <sstream> //字符串流 c++标准库
#include "json/json.h" //jsoncpp的头文件
```

## 值类型

```cpp
enum ValueType
{
    nullValue = 0, ///< 'null' value
    intValue,      ///< signed integer value
    uintValue,     ///< unsigned integer value
    realValue,     ///< double value
    stringValue,   ///< UTF-8 string value
    booleanValue,  ///< bool value
    arrayValue,    ///< array value (ordered list)
    objectValue    ///< object value (collection of name/value pairs).
};
```

在 Value 类中提供了 type() 用于获取值类型(ValueType)，type() 定义如下：

```cpp
class Value {
    ...
    ValueType type() const;
    ...
};
```

### 类型判断

```cpp
class Value
{
    ... 
    bool isNull() const;
    bool isBool() const;
    bool isInt() const;
    bool isInt64() const;
    bool isUInt() const;
    bool isUInt64() const;
    bool isIntegral() const;
    bool isDouble() const;
    bool isNumeric() const;
    bool isString() const;
    bool isArray() const;
    bool isObject() const;
    ...
};
```

### 类型转换

```cpp
class Value {
    ...
    const char *asCString() const;
    String asString() const;
    Int asInt() const;
    Int64 asInt64() const;
    UInt asUInt() const;
    UInt64 asUInt64() const;
    float asFloat() const;
    double asDouble() const;
    bool asBool() const;
    ...
};
```

### 键值判断

Value.isMember() 接口用于判断 json 字符串中是否存在某个键值，函数原型：

```cpp
class Value {
    ...
    /// Return true if the object has a member named key.
    /// \note 'key' must be null-terminated.
    bool isMember(const char* key) const;
    /// Return true if the object has a member named key.
    /// \param key may contain embedded nulls.
    bool isMember(const String& key) const;
    /// Same as isMember(String const& key)const
    bool isMember(const char* begin, const char* end) const;
    ...  
};
```

**键值判断结合类型判断接口**，如果需要确定 json 中是否存在 “content” 键值，并且 “content” 的值为 string 类型，可以加入这样的判断条件：

```cpp
if (root.isMember("content") && root["content"].isString()) {
    // do something...
    val = root["content"].asString();
}
```

## 遍历 json 数据

```cpp
Json::Value root;
if (reader.parse(str, root)) {
    Json::Value::Members mem = root.getMemberNames();
    for (auto key : mem) 
        std::cout << key << std::endl;
}
```

## 读取数组

简单数组：

```json
{ "list": [1, 2, 3] }
```

```cpp
for (auto it : root["list"])
    std::cout << it.asInt();
```

如果数组是 ObjectValue 类型，比如说类似这种：

```json
{
    "list": [
        {
            "name": "John",
            "sex": "man"
        },
        {
            "name": "Marry",
            "sex": "women"
        }
    ]
}
```

```cpp
for (auto it : root["list"]) {
    std::cout << it["name"].asString() << std::endl;
    std::cout << it["sex"].asString() << std::endl;
}
```

## 写 json 数据

JsonCpp 提供 Writer 类用于写 json 数据。还是从最简单的例子开始，然后逐步展开。比如利用 JsonCpp 创建如下 json 文件：

```cpp
#include <json/json.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    Json::Value root;
    root["content"] = "Hello JsonCpp";
    std::cout << root.toStyledString();
    return 0;
}
```

运行结果:
```
{
   "content" : "Hello JsonCpp"
}
```

### 添加 ObjectValue 类型

如果需要添加嵌套的 json 子节点，可以定义一个 Value 对象来装载内部的 Key/Value 键值对，然后将该对象赋值给 json 的父节点

```cpp
Json::Value sub;
sub["province"] = "Guangdong";
sub["city"] = "Huizhou";

root["hometown"] = sub;
sub.clear();
```

如果嵌套的节点内容较简单，不想重新定义一个新的 Value 变量也可以采用另一种写法：

```cpp
root["hometown"]["province"] = "Guangdong";
root["hometown"]["city"] = "Huizhou";
``

以上两种写法最终产生的 json 内容都是一样的，如下所示：
```json
{
    "hometown": {
        "province": "Guangdong",
        "city": "Huizhou"
    }
}
```

## 添加数组类型

Value.append() 接口用于添加 json 数组类型，凡事宜从最简单的地方入手，一步一步深入:

```cpp
for (int i = 0; i < 3; ++i)
    root["list"].append(i);
```

生成的 json 内容如下：
```json
{
    "list": [0, 1, 2]
}
```

如果数组内的数据是 ObjectValue 类型，可以定义一个 Value 对象来装载内部的 Key/Value 键值对，然后将该对象添加到数组中：

```cpp
Json::Value item;
for (int i = 0; i < 2; ++i) {
    item["index"] = i;
    item["content"] = "Hello Array";
    root["data"].append(item);
}
```

生成的 json 内容如下：

```json
{
   "data" : [
      {
         "content" : "Hello Array",
         "index" : 0
      },
      {
         "content" : "Hello Array",
         "index" : 1
      }
   ]
}
```

## 格式化与非格式化

根据使用场合不同，需要将 json 内容转换为格式化或非格式化字符串，比如为了可视化的输出一般选择格式化 json 字符串，而在网络传输过程中，会尽量选择使用非格式化的字符串来达到减少传输数据量的目的。

```cpp
Json::Value root;
// root 中写入数据

// 格式化: 转为格式化字符串，里面加了很多空格及换行符，适合于展示
std::string strJson = root.toStyledString();

// 非格式化: 转为未格式化字符串，无多余空格及换行符，适合于传输
Json::FastWriter writer;
std::string strJson = writer.write(root);
```

## 写入文件

在这一小节的介绍中，更多的是说明标准 C++ 的文件流操作，因为上文已经通过格式化与非格式化将 json 字符串导出成一个标准 C++ 的字符串 std::string，接下来直接将 std::string 写入到文件中即可。示例代码：

```cpp
// root node
Json::Value root;
//...

try
{
    std::ofstream ofs;
    ofs.open(filename);
    if (ofs.fail())
    {
        fprintf(stderr, "open '%s' failed: %s", filename, strerror(errno));
        return false;
    }
    ofs << root.toStyledString();
    ofs.close();
}
catch (std::exception &e)
{
    fprintf(stderr, "%s", e.what());
    return false;
}
```

在文件写入完成之后使用 ofs.close() 接口关闭文件流。因为写入的过程在实际的系统运行会出现较复杂的情况：磁盘満了又或者磁盘损坏导致无法写入等，所以如果在写入的过程中出现异常，我们就需要使用 try...catch... 来捕获异常。

## 从文件读取

Reader 支持从 std::istream 流读取数据，可以直接将文件流作为输入参数给到 Reader.parse()，函数原型为：

```cpp
class Reader {
    ...
    bool parse(const std::string& document, Value& root, bool collectComments = true);
    bool parse(IStream& is, Value& root, bool collectComments = true);
    ...
};
```

比如现在有一个文件 hello.json：

```cpp
{
    "content": "Hello JsonCpp"
}
```

代码实现：
```cpp
#include <string.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <json/json.h>

int main(int argc, char const *argv[])
{
    const char *path ="hello.json"; 
    std::ifstream ifs(path);
    if (!ifs) {
        printf("open '%s' failed: %s\n", path, strerror(errno));
        return 1;
    }

    Json::Reader reader;
    Json::Value root;
    if (reader.parse(ifs, root)) {
        if (root.isMember("content") && root["content"].isString()) {
            printf("%s\n", root["content"].asCString());
        }
    }
    
    return 0;
}
```

# examples下的demo使用

路径: build_lib\examples\examples\3partlib\jsoncpp

代码

```cpp
#include <iostream>
#include "JsonUtil.h"

int main(int args, char *argv[])
{
    std::string str = "{\"uploadid\": \"teststr\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";
    std::cout << str << std::endl;
    std::cout << JsonUtil::isValid(str) << std::endl;
    std::cout << JsonUtil::getInt(str, "code") << std::endl;
    std::cout << JsonUtil::getStr(str, "uploadid") << std::endl;
    //...

    return 0;
}
```

执行结果:

```
[root@5d4b980baaa2 jsoncpp]# ./jsoncppTest
{"uploadid": "teststr","code": 100,"msg": "","files": ""}
1
100
teststr
-----Set func test---------
{
        "array" :
        [
                "1",
                "2",
                "3",
                "4",
                "5"
        ],
        "intKey" : 102,
        "json" :
        {
                "nam" : "Jason",
                "num" : 1024
        },
        "strKey" : "xxx"
}

------Get func test---------
102
xxx
{
        "nam" : "Jason",
        "num" : 1024
}

1
2
3
4
5
------new test---------
posts   :
author  : kkkk
id      : 2
title   : hello world
author  : k
id      : 3
title   : hello ld
test    : 1
weatherinfo     :
Radar   : JC_RADAR_AZ9010_JB
SD      : 17 %
WD      : 东南风
WS      : 1级
WSE     : 1
city    : 北京
cityid  : 101010100
isRadar : 1
njd     : 这是什么
qy      : 1011
rain    : 0
temp    : 18
time    : 17:05
------File func test---------
normalPath: /home/stibel/examples/deploy/3partlib/jsoncpp/../../../examples/3partlib/jsoncpp/conf/normal.json
arrayPath: /home/stibel/examples/deploy/3partlib/jsoncpp/../../../examples/3partlib/jsoncpp/conf/array.json
[readStringFromJson] 111
[readStringFromJson] file: /home/stibel/examples/deploy/3partlib/jsoncpp/../../../examples/3partlib/jsoncpp/conf/normal.json, res:{"checkPassword":"12345678","userAccount":"testuser","userPassword":"12345678"}
[readArrayStringFromJson] key: checkPasswordvalue: 12345678
[readArrayStringFromJson] key: userAccountvalue: testuser
[readArrayStringFromJson] key: userPasswordvalue: 12345678
[readArrayStringFromJson] key: checkPasswordvalue: 12345678333
[readArrayStringFromJson] key: userAccountvalue: testuser222
[readArrayStringFromJson] key: userPasswordvalue: 12345678333
[readArrayStringFromJson] file: /home/stibel/examples/deploy/3partlib/jsoncpp/../../../examples/3partlib/jsoncpp/conf/array.json, res:[{"checkPassword":"12345678","userAccount":"testuser","userPassword":"12345678"},{"checkPassword":"12345678333","userAccount":"testuser222","userPassword":"12345678333"}]
writeString2JsonFile result:1
```