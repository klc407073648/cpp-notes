# C++ Tips - linux下c/c++头文件和动态库的搜索

> 本文讲解linux环境下c/c++头文件和动态库的搜索的内容。

[[toc]]

C/C++程序在linux下被编译和连接时，`GCC/G++会查找系统默认的include和link的路径`，以及自己在编译命令中指定的路径。下面，详细说明系统自动搜索的路径。

## include头文件路径

除了默认的`/usr/include, /usr/local/include`等include路径外，还可以通过设置环境变量来添加系统include的路径: 

```   
# C
export C_INCLUDE_PATH=XXXX:$C_INCLUDE_PATH
# CPP
export CPLUS_INCLUDE_PATH=XXX:$CPLUS_INCLUDE_PATH
```

以上修改可以直接命令行输入（一次性），可以在/etc/profile中完成（对所有用户生效），也可以在用户home目录下的.bashrc或.bash_profile中添加（针对某个用户生效），修改完后重新登录即生效。

**头文件搜索顺序**

1. 在gcc编译源文件的时候，通过参数-I指定头文件的搜索路径，如果指定路径有多个路径时，则按照指定路径的顺序搜索头文件。
2. 通过查找gcc的环境变量C_INCLUDE_PATH/CPLUS_INCLUDE_PATH/OBJC_INCLUDE_PATH来搜索头文件位置。
3. 再找内定目录搜索，分别是 /usr/include /usr/local/include /usr/lib/gcc-lib/i386-linux/2.95.2/include
4. 当#include使用相对路径的时候，gcc最终会根据上面这些路径，来最终构建出头文件的位置。如#include <sys/types.h>就是包含文件/usr/include/sys/types.h


## link链接库文件路径

    链接库文件在连接（静态库和共享库）和运行（仅限于使用共享库的程序）时被使用，其搜索路径是在系统中进行设置的（也可以在编译命令中通过 -l  -L 来指定，这里讲的是使用系统默认搜索路径）。

    一般 Linux 系统把/lib  /usr/lib  /usr/local/lib作为默认的库搜索路径，所以使用这几个目录中的链接库文件可直接被搜索到（不需要专门指定链接库路径）。对于默认搜索路径之外的库，则需要将其所在路径添加到gcc/g++的搜索路径之中。

    链接库文件的搜索路径指定有两种方式: 

1. 修改环境变量，在其中添加自己的路径
2. 修改`/etc/so.ld.conf`  

### 修改环境变量

```
动态链接库搜索路径: 
export LD_LIBRARY_PATH=XXX:$LD_LIBRARY_PATH
静态链接库搜索路径: 
export LIBRARY_PATH=XXX:$LIBRARY_PATH
```
以上修改可以直接命令行输入（一次性），可以在/etc/profile中完成（对所有用户生效），也可以在用户home目录下的.bashrc或.bash_profile中添加（针对某个用户生效）,修改完后重新登录即生效。

* 在/etc/ld.so.conf 中添加指定的链接库搜索路径（需要root权限），然后运行 /sbin/ldconfig，以达到刷新 /etc/ld.so.cache的效果。

    以上两种方式均可以达到指定链接库搜索路径的效果。
    
### 修改/etc/so.ld.conf

1. 第二种搜索路径的设置方式对于程序连接时的库（包括共享库和静态库） 的定位已经足够了，但是对于使用了共享库的程序的执行还是不够的。这是因为为了加快程序执行时对共享库的定位速度，避免使用搜索路径查找共享库的低效率，`系统会直接读取 /etc/ld.so.cache 并从中进行搜索的`。/etc/ld.so.cache 是一个非文本的数据文件，不能直接编辑，它是根据 /etc/ld.so.conf 中设置的搜索路径由 /sbin/ldconfig 命令将这些搜索路径下的共享库文件集中在一起而生成的（ldconfig 命令要以 root 权限执行）。因此，为了保证程序执行时对库的定位，`在 /etc/ld.so.conf 中进行了库搜索路径的设置之后，还要运行 /sbin/ldconfig 命令，更新 /etc/ld.so.cache 文件。`

2. ldconfig的作用就是将/etc/ld.so.conf 指定的路径下的库文件缓存到/etc/ld.so.cache 。因此当安装完一些库文件(例如刚安装好glib)，或者修改ld.so.conf增加新的库路径后，需要运行一下/sbin/ldconfig 使所有的库文件都被缓存到ld.so.cache中，不然修改的内容就等于没有生效。

3. 在程序连接时，对于库文件（静态库和共享库）的搜索路径，除了上面的设置方式之外，还可以通过 -L 和 -l 参数显式指定。因为用 -L 设置的路径将被优先搜索，所以在连接的时候通常都会以这种方式直接指定要连接的库的路径。

注意: 
    1）在配置环境变量的时候，等号前面不要加空格，否则可能出现 command not found
    2）修改/etc/ld.so.conf后，当系统重新启动后，所有基于 GTK2 的程序在运行时都将使用新安装的 GTK+ 库。由于 GTK+ 版本的改变，有时会给应用程序带来兼容性的问题，造成某些程序运行不正常。为了避免出现这些情况，在 GTK+ 及其依赖库的安装过程中对于库的搜索路径的设置将采用环境变量的方式
    export LD_LIBRARY_PATH=/opt/gtk/lib:$LD_LIBRARY_PATH

**link链接库文件搜索顺序**

1. gcc会去找-L指定的路径，例如: -L/usr/lib -L/usr/X11R6/lib -lgtk -lgdk
2. 再找gcc的环境变量LD_LIBRARY_PATH
3. 再找内定目录 /lib: /usr/lib:  /usr/local/lib: 这是当初compile gcc时写在程序内的
