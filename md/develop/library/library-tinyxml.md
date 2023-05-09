# 常用开发库 - tinyxml

# 参考资料

* [源码](https://sourceforge.net/projects/tinyxml/)
* [TinyXML 使用](http://foolishflyfox.xyz/blog/2020/04/12/cpp/tinyxml/)
* [TinyXML用法小结](https://blog.csdn.net/qq_32619837/article/details/87601131)

# 概述

> TinyXML是一个C++的轻量级的XML解析库, 它基于文档对象模型(DOM)来进行解析。在解析时，一次性的将整个XML文档进行分析，并在内存中形成对应的树结构。同时，向用户提供一系列的接口来访问和编辑该树结构。

这种方式虽然占用内存大，但是可以给用户提供一个面向对象的访问接口，对用户更为友好，非常方便用户使用。

## 类图

![](/_images/develop/library/tinyxml/类图关系.png)

* TiXmlBase: 整个TinyXML模型的基类
    * TiXmlAttribute: 元素的属性
    * TiXmlNode: DOM结构中的节点
        * TiXmlComment: 注释
        * TiXmlDeclaration: 申明部分
        * TiXmlDocument: 整个文档
        * TiXmlElement: 元素
        * TiXmlText: 文字部分
        * TiXmlUnknown: 未知部分
        * TiXmlHandler: 针对XML的一些操作

## 常用方法

### 基本方法

* TiXmlDocument::LoadFile: 载入并解析xml文件，成功返回true，失败返回false
* TiXmlNode::Type(): 获取节点类型，共有6种类型：TINYXML_DOCUMENT / TINYXML_COMMENT / TINYXML_ELEMENT / * TINYXML_TEXT / TINYXML_UNKNOWN / TINYXML_DECLARATION，为定义在 TiXmlNode 中的枚举类型
* TiXmlNode::Value(): 读取Comment、Element、Text的内容
* TiXmlNode* TiXmlNode::FirstChild(): 获取当前节点的第一个子节点
* TiXmlNode* TiXmlNode::FirstChild(const char* value): 获取元素名为 value 的子节点
* TiXmlNode::NextSibling(): 获取当前节点的下一个兄弟节点
* TiXmlAttribute* TiXmlElement::FirstAttribute(): 获取 Element 的第一个属性

### 获取属性信息

* TiXmlAttribute::Next(): 获取下一个属性地址
* string TiXmlAttribute::Value(): 获取属性值
* int TiXmlAttribute::QueryIntValue(int*): 将属性值转为int类型，成功返回TIXML_SUCCESS
* int TiXmlAttribute::QueryDoubleValue(double*): 将属性值转为double类型，返回值同上
* int TiXmlElement::QueryStringAttribute(const char* name, string* _value): 获取元素节点的指定属性，返回值同上

### 类型转换

* TiXmlText* TiXmlNode::ToText()
* TiXmlElement* TiXmlNode::ToElement()

### 其他常用的函数

* TiXmlDocument::RootElement(): 获取DOM的根元素，本质上是获取节点的第一个子Element

# examples下的demo使用

路径: build_lib\examples\examples\3partlib\tinyxml

代码

```cpp
#include "tinyxmlUtil.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "StiBel/Util.h"

using namespace std;
string curPath;
string myPrintPath = "/../../../examples/3partlib/tinyxml/conf/school.xml";
string myWritePath = "/../../../examples/3partlib/tinyxml/conf/school-write.xml";
string finalPath;

int main()
{
	printSchoolXml();
	readSchoolXml();
	writeSchoolXml();

	return 0;
}
```

执行结果:

```
[root@5d4b980baaa2 tinyxml]# ./tinyxmlTest
<School name="计算机学院">
    <Class name="C++">
        <Student name="Jason" number="1001">
            <grade>98</grade>
            <address>China</address>
        </Student>
        <Student name="Steven" number="1002">
            <grade>80</grade>
            <address>america</address>
        </Student>
    </Class>
    <Class name="Java">
        <Student name="Lucy" number="1003">
            <grade>100</grade>
            <address>London</address>
        </Student>
        <Student name="Marry" number="1004">
            <grade>85</grade>
            <address>Japan</address>
        </Student>
    </Class>
</School>
name : Jason
number : 1001
grade : 98
address : China
name : Steven
number : 1002
grade : 80
address : america
name : Lucy
number : 1003
grade : 100
address : London
name : Marry
number : 1004
grade : 85
address : Japan
```


