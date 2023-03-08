# 编码规范 - 常用编码命名规则


[[toc]]

# 驼峰命名法

> 最常见的一个命名法，命名方式使用大小写混合的格式来区别各个单词，并且单词之间不使用空格隔开或者连接字符连接的命名方式。

## 大驼峰命名法（CamelCase）

**通常类名需要使用大驼峰命名法**

```cpp
//正例：
ServiceDiscovery、ServiceInstance、LruCacheFactory
//反例：
serviceDiscovery、Serviceinstance、LRUCacheFactory
```

## 小驼峰命名法（lowerCamelCase）

**通常函数方法名、参数名、成员变量、局部变量需要使用小驼峰命名法**

```cpp
//正例：
getUserInfo()、createCustomThreadPool()、setNameFormat(String nameFormat)
Uservice userService;

//反例：
GetUserInfo()、CreateCustomThreadPool()、setNameFormat(String NameFormat)
Uservice user_service
```

# 蛇形命名法（snake_case）

**通常测试方法名、常量、枚举名称需要使用蛇形命名法。**

在蛇形命名法中，各个单词之间通过下划线“_”连接，比如

`should_get_200_status_code_when_request_is_valid、CLIENT_CONNECT_SERVER_FAILURE`

蛇形命名法的优势是命名所需要的单词比较多的时候，比上面通过小驼峰命名法得到的名称易读：

`shouldGet200StatusCodoWhenRequestIsValid`

```cpp
//正例：
@Test
void should_get_200_status_code_when_request_is_valid() {
  ......
}

//反例：

@Test
void shouldGet200StatusCodoWhenRequestIsValid() {
  ......
}
```

# 串式命名法（kebab-case）

在串式命名法中，各个单词之间通过下划线“-”连接

**建议项目文件夹名称使用串式命名法**

在Vue中，定义组件名

* kebab-case（短横线命名）
  * `Vue.component('my-component-name', { /* ... */ })`

* 使用 大驼峰命令（CamelCase）
  * `Vue.component('MyComponentName', { /* ... */ })`

# 匈牙利命名法（Hungarian）

hwnd：h 是类型描述，表示句柄， wnd 是变量对象描述，表示窗口，所以 hwnd 表示窗口句柄。
pfnEatApple：pfn 是类型描述，表示指向函数的指针， EatApple 是变量对象描述，所以它表示指向 EatApple 函数的函数指针变量。
g_cch：g_ 是属性描述，表示全局变量，c 和 ch 分别是计数类型和字符类型，一起表示变量类型，这里忽略了对象描述，所以它表示一个对字符进行计数的全局变量。

**匈牙利命名法基本原则：变量名=属性+类型+对象描述**

* 全局变量用g_开头,如一个全局的长型变量定义为g_lFailCount
* 静态变量用s_开头,如一个静态的指针变量定义为s_plPerv_Inst
* 成员变量用m_开头,如一个长型成员变量定义为m_lCount
* 局部变量用l_开头,如一个整型局部变量定义为l_inum

```
属性部分：
g_ 全局变量
c_ 　常量
m_ 　c++类成员变量
s_ 　静态变量
类型部分：
数组 a
指针　p
函数　fn
无效　v
句柄　h
长整型　l
布尔　b
浮点型（有时也指文件）　f
双字 　dw
字符串　 sz
短整型　 n
双精度浮点　d
计数　c（通常用cnt）
字符　ch（通常用c）
整型　i（通常用n）
字节　by
字　w
实型　r
无符号　u
描述部分：
最大　Max
最小　Min
初始化　Init
临时变量　T（或Temp）
源对象　Src
目的对象　Dest
```
