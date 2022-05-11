# jsoncpp使用

- 生成动态库的步骤

```
1.下载  jsoncpp-src-0.5.0.tar.gz 文件
2.切换到 jsoncpp 目录 ，执行
  python /usr/bin/scons platform=linux-gcc  (需要提前安装scons,解压zip包，cd ./scons-3.1.1/ python setup.py install)
3. 在/home/jsoncpp-src-0.5.0/libs/linux-gcc-9.1.0/ 路径下找到
   libjson_linux-gcc-9.1.0_libmt.so
   libjson_linux-gcc-9.1.0_libmt.a
4. 将 libjson_linux-gcc-9.1.0_libmt.so 重命名为  libjsoncpp.so 
5. 包含头文件，链接so文件即可使用
```

- 使用方法

```
1. 直接使用lib，调用jsoncpp函数
cd build
cmake ..
make
../deploy/jsonTest

|-- use_lib
|   |-- build
|   |   `-- gitkeep
|   |-- CMakeLists.txt
|   |-- deploy
|   |   `-- jsonTest
|   |-- include
|   |   `-- json
|   |       |-- autolink.h
|   |       |-- config.h
|   |       |-- features.h
|   |       |-- forwards.h
|   |       |-- json.h
|   |       |-- reader.h
|   |       |-- value.h
|   |       `-- writer.h
|   |-- lib
|   |   |-- libjsoncpp.so
|   |   `-- libjson_linux-gcc-9.1.0_libmt.a
|   `-- source
|       `-- main.cpp

2.使用头文件和源文件，调用jsoncpp函数
cd build
cmake ..
make
../deploy/jsonTest

`-- use_source_file
    |-- build
    |   `-- gitkeep
    |-- CMakeLists.txt
    |-- deploy
    |   `-- jsonTest
    |-- include
    |   `-- json
    |       |-- autolink.h
    |       |-- config.h
    |       |-- features.h
    |       |-- forwards.h
    |       |-- json.h
    |       |-- reader.h
    |       |-- value.h
    |       `-- writer.h
    `-- source
        |-- json_batchallocator.h
        |-- json_internalarray.inl
        |-- json_internalmap.inl
        |-- json_reader.cpp
        |-- json_value.cpp
        |-- json_valueiterator.inl
        |-- json_writer.cpp
        |-- main.cpp
        `-- sconscript


```

