# Tools - cmake使用指南

[[toc]]

# 参考

* [cmake官网](https://cmake.org/cmake-tutorial/)
* [cmake基础及交叉编译](https://blog.csdn.net/MyArrow/article/details/80480255)
* [cmake的file命令](https://blog.csdn.net/sinat_31608641/article/details/123858610) 
* [cmake的file命令官网](https://cmake.org/cmake/help/v3.14/command/file.html)
* [CMakeFile命令之file](https://blog.csdn.net/tantion/article/details/84378266)
* [cmake的install指令](https://blog.csdn.net/qq_38410730/article/details/102837401)

# 概述

CMake是开源、跨平台的构建工具，可以让我们通过编写简单的配置文件去生成本地的Makefile，这个配置文件是独立于运行平台和编译器的，这样就不用亲自去编写Makefile了，而且配置文件可以直接拿到其它平台上使用，无需修改，非常方便。

**cmake 即编程**

**cmake主要特点**：

* 开放源代码，使用类 BSD 许可发布
* 跨平台，并可生成 native 编译配置文件，在 Linux/Unix 平台，生成 makefile，在苹果平台，可以生成 xcode，在 Windows 平台，可以生成 MSVC 的工程文件
* 能够管理大型项目
* 简化编译构建过程和编译过程；Cmake 的工具链非常简单：cmake+make
* 高效虑，按照 KDE 官方说法，CMake 构建 KDE4 的 kdelibs 要比使用 autotools 来构建 KDE3.5.6 的 kdelibs 快 40%，主要是因为 Cmake 在工具链中没有 libtool
* 可扩展，可以为 cmake 编写特定功能的模块，扩充 cmake 功能
* 支持out-of-source build：一个最大的好处是，对于原有的工程没有任何影响，所有动作全部发生在编译目录。

**cmake基本结构**

* 依赖CMakeLists.txt(文件名区分大小写)文件，项目主目录只有一个，主目录中可指定包含的子目录
* 在项目CMakeLists.txt中使用project指定项目名称，add_subdirectory或subdirs添加子目录
* 子目录CMakeLists.txt将从父目录CMakeLists.txt继承设置(<font color='red'>**但set变量不可继承**</font>)

# 常用指令

* cmake_minimum_required 设置 cmake 的最低版本号要求
* project 设置工程名字
* set 设置变量
    * SET(CMAKE_CXX_COMPILER "g++")  # 设定编译器
* include 从文件或模块加载并运行CMake代码(CMakeLists.txt 文件，cmake 模块)
    * include(${PROJECT_SOURCE_DIR}/cmake/options.cmake)
* option 选项
    * option(BUILD_EXAMPLES "Enable build all examples" ON)
* add_subdirectory 增加编译子目录，也可以使用 `SUBDIRS` 不推荐
* list 列表相关的操作
* message 用于打印、输出信息
* add_definitions 向 C/C++编译器添加-D 定义
    * add_definitions(-DTESTCMAKE), 代码里可以判断对应标志位
* add_dependencies 
    * ADD_DEPENDENCIES(target-name depend-target1 depend-target2 …)
    * 定义 target 依赖的其他 target，确保在编译本 target 之前，其他的 target 已经被构建


获取源文件

* aux_source_directory  发现一个目录下所有的源代码文件并将列表存储在一个变量中，这个指 令临时被用来自动构建源文件列表
* file            <font color='red'>**CMake的文件操作命令**</font>
    * FILE (GLOB DATA_MYSQL_TEST_FILES ${DATA_MYSQL_TEST_SRC_DIR}/*.cpp)

工程相关

* include_directories     向工程添加多个特定的头文件搜索路径 ，相当于指定g++编译器的-I参数
* add_library             生成库文件
* add_executable          生成可执行文件
* link_directories        向工程添加多个特定的库文件搜索路径 —>相当于指定g++编译器的-L参数
* target_link_libraries   为 target 添加需要链接的共享库 —>相同于指定g++编译器-l参数
* install                 <font color='red'>**目标文件的安装**</font>

# Cmake变量

CMake共用七种变量，如下所示：

1. 提供信息的变量。
2. 控制变量。
3. 描述系统的变量。
4. 控制构建过程的变量。
5. 语言变量。
6. CTest变量。
7. CPack变量。

## CMake内置变量与系统变量对应关系

| 变量名称    |          CMake变量          |                           系统变量 |
| ----------- | :-------------------------: | ---------------------------------: |
| C编译器     |      CMAKE_C_COMPILER       |                                 CC |
| C++编译器   |     CMAKE_CXX_COMPILER      |                                CXX |
| 生成器      |        -G "*******"         | CMAKE_GENERATOR(CMAKE 3.15+才支持) |
| C编译选项   |        CMAKE_C_FLAGS        |                             CFLAGS |
| C++编译选项 | CMAKE_CXX_FLAGS	CXXFLAGS |                                    |

## CMake变量引用的方式

使⽤ ${} 进⾏变量的引⽤。在 IF 等语句中，是直接使⽤变量名⽽不通过 ${} 取值。

## cmake 定义变量的⽅式

主要有隐式定义和显式定义两种，举⼀个隐式定义的例⼦，就是 PROJECT 指令，他会隐式的定义_BINARY_DIR 和_SOURCE_DIR 两个变量。

⽽显式定义的例⼦，可以使⽤ SET 指令，就可以构建⼀个⾃定义变量了。

## 常用变量

**预定义变量**

| 变量名称                 |                             解释                             |
| ------------------------ | :----------------------------------------------------------: |
| PROJECT_SOURCE_DIR       |                         工程的根目录                         |
| PROJECT_BINARY_DIR       |  运行 cmake 命令的目录，通常是 ${PROJECT_SOURCE_DIR}/build   |
| PROJECT_NAME             |             返回通过 project 命令定义的项目名称              |
| CMAKE_CURRENT_SOURCE_DIR |             当前处理的 CMakeLists.txt 所在的路径             |
| CMAKE_CURRENT_BINARY_DIR |                       target 编译目录                        |
| CMAKE_CURRENT_LIST_DIR   |                  CMakeLists.txt 的完整路径                   |
| CMAKE_CURRENT_LIST_LINE  |                         当前所在的行                         |
| CMAKE_MODULE_PATH        | 定义自己的 cmake 模块所在的路径，SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)，然后可以用INCLUDE命令来调用自己的模块 |
| EXECUTABLE_OUTPUT_PATH   |            重新定义目标二进制可执行文件的存放位置            |
| LIBRARY_OUTPUT_PATH      |               重新定义目标链接库文件的存放位置               |

**环境变量**

* 使用环境变量：$ENV{Name}；
* 写入环境变量：set(ENV{Name} value)，这里没有“$”符号；

**系统信息**

| 变量名称                |                          解释                          |
| ----------------------- | :----------------------------------------------------: |
| CMAKE_MAJOR_VERSION     |           cmake 主版本号，比如 3.4.1 中的 3            |
| ­CMAKE_MINOR_VERSION    |           cmake 次版本号，比如 3.4.1 中的 4            |
| ­CMAKE_PATCH_VERSION    |           cmake 补丁等级，比如 3.4.1 中的 1            |
| ­CMAKE_SYSTEM           |              系统名称，比如 Linux-­2.6.22              |
| ­CMAKE_SYSTEM_NAME      |             不包含版本的系统名，比如 Linux             |
| ­CMAKE_SYSTEM_VERSION   |                 系统版本，比如 2.6.22                  |
| ­CMAKE_SYSTEM_PROCESSOR |                 处理器名称，比如 i686                  |
| ­UNIX                   | 在所有的类 UNIX 平台下该值为 TRUE，包括 OS X 和 cygwin |
| ­WIN32                  |     在所有的 win32 平台下该值为 TRUE，包括 cygwin      |
| APPLE                   |               在所有苹果平台下该值为TRUE               |


**主要开关选项**

```
BUILD_SHARED_LIBS：这个开关用来控制默认的库编译方式，如果不进行设置，使用 add_library 又没有指定库类型的情况下，默认编译生成的库都是静态库。如果 set(BUILD_SHARED_LIBS ON) 后，默认生成的为动态库
CMAKE_C_FLAGS：设置 C 编译选项，也可以通过指令 add_definitions() 添加
CMAKE_CXX_FLAGS：设置 C++ 编译选项，也可以通过指令 add_definitions() 添加，add_definitions(-DENABLE_DEBUG -DABC) # 参数之间用空格分隔
```

**其他常用变量**

| 变量名称                 |                解释                |
| ------------------------ | :--------------------------------: |
| CMAKE_C_COMPILER         |            指定C编译器             |
| CMAKE_CXX_COMPILER       |           指定C++编译器            |
| EXECUTABLE_OUTPUT_PATH   |      可执行文件输出的存放路径      |
| LIBRARY_OUTPUT_PATH      |        库文件输出的存放路径        |
| CMAKE_CURRENT_SOURCE_DIR |  当前处理的CMakeLists.txt位于目录  |
| CMAKE_CURRENT_LIST_DIR   | 这是当前正在处理的listfile中的目录 |

**编译选项**：CMAKE_CXX_FLAGS【CMAKE_C_FLAGS gcc编译选项】【CMAKE_CXX_FLAGS g++编译选项】

```
# 在CMAKE_CXX_FLAGS编译选项后追加-std=c++11
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
```

**编译类型**：CMAKE_BUILD_TYPE (Debug, Release)

```
# 设定编译类型为debug，调试时需要选择debug
set(CMAKE_BUILD_TYPE Debug) 
# 设定编译类型为release，发布时需要选择release
set(CMAKE_BUILD_TYPE Release) 
```

## cmake file详解

```
Reading
  file(READ <filename> <out-var> [...])
  file(STRINGS <filename> <out-var> [...])
  file(<HASH> <filename> <out-var>)
  file(TIMESTAMP <filename> <out-var> [...])
 
Writing
  file({WRITE | APPEND} <filename> <content>...)
  file({TOUCH | TOUCH_NOCREATE} [<file>...])
  file(GENERATE OUTPUT <output-file> [...])
 
Filesystem
  file({GLOB | GLOB_RECURSE} <out-var> [...] [<globbing-expr>...])
  file(RENAME <oldname> <newname>)
  file({REMOVE | REMOVE_RECURSE } [<files>...])
  file(MAKE_DIRECTORY [<dir>...])
  file({COPY | INSTALL} <file>... DESTINATION <dir> [...])
  file(SIZE <filename> <out-var>)
  file(READ_SYMLINK <linkname> <out-var>)
  file(CREATE_LINK <original> <linkname> [...])
 
Path Conversion
  file(RELATIVE_PATH <out-var> <directory> <file>)
  file({TO_CMAKE_PATH | TO_NATIVE_PATH} <path> <out-var>)
 
Transfer
  file(DOWNLOAD <url> <file> [...])
  file(UPLOAD <file> <url> [...])
 
Locking
  file(LOCK <path> [...])
```

使用实例：

<<< @/md/devops/tools/src/cmake/file/CMakeLists.txt
