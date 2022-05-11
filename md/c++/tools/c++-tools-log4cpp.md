# log4cpp使用

1.下载代码

```
git clone https://git.code.sf.net/p/log4cpp/codegit log4cpp-codegit
```

2.编译与安装

```
cd log4cpp-codegit/  
./autogen.sh    #需要yum install libtool
./configure  
make
make check
make install
```

3.配置环境变量

```
vi /etc/profile
加入
LD_LIBRARY_PATH=:$LD_LIBRARY_PATH:/usr/local/lib
export LD_LIBRARY_PATH

source /etc/profile   使其生效
```
4.测试代码

4.1不使用配置文件的测试代码：
g++ test_main.cpp -o test_main -llog4cpp -lpthread

```
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/BasicLayout.hh>

int main()
{
  log4cpp::Layout* layout =  new log4cpp::BasicLayout();
   // 2. 初始化一个appender 对象
  log4cpp::Appender* appender = new log4cpp::FileAppender("FileAppender","./test_log4cpp1.log");
    // 3. 把layout对象附着在appender对象上
  appender->setLayout(layout);
  // 4. 实例化一个category对象
  log4cpp::Category& warn_log = log4cpp::Category::getInstance("mywarn");
  // 5. 设置additivity为false，替换已有的appender
  warn_log.setAdditivity(false);
  // 5. 把appender对象附到category上
  warn_log.setAppender(appender);
  // 6. 设置category的优先级，低于此优先级的日志不被记录
  warn_log.setPriority(log4cpp::Priority::WARN);
  // 记录一些日志
  warn_log.info("Program info which cannot be wirten");
  warn_log.debug("This debug message will fail to write");
  warn_log.alert("Alert info");
  // 其他记录日志方式
  warn_log.log(log4cpp::Priority::WARN, "This will be a logged warning");
  log4cpp::Priority::PriorityLevel priority;
  bool this_is_critical = true;
  if(this_is_critical)
       priority = log4cpp::Priority::CRIT;
  else
       priority = log4cpp::Priority::DEBUG;
  warn_log.log(priority,"Importance depends on context");
        
  warn_log.critStream() << "This will show up << as " << 1 << " critical message"<< log4cpp::Priority::ERROR;
  // clean up and flush all appenders
  log4cpp::Category::shutdown();
  return 0;
}

```

4.2:使用配置文件

4.2.1配置内容：

```
############################## log4cpp.conf ########################################################
# a simple test config
#定义了3个category sub1, sub2, sub1.sub2
log4j.rootCategory=DEBUG, rootAppender
log4j.category.sub1=,A1
log4j.category.sub2=INFO
log4j.category.sub1.sub2=ERROR, A2
# 设置sub1.sub2 的additivity属性
log4j.additivity.sub1.sub2=false
#定义rootAppender类型和layout属性
log4j.appender.rootAppender=org.apache.log4j.ConsoleAppender
log4j.appender.rootAppender.layout=org.apache.log4j.BasicLayout
#定义A1的属性
log4j.appender.A1=org.apache.log4j.FileAppender
log4j.appender.A1.fileName=A1.log
log4j.appender.A1.layout=org.apache.log4j.SimpleLayout
#定义A2的属性
log4j.appender.A2=org.apache.log4j.ConsoleAppender
log4j.appender.A2.layout=org.apache.log4j.PatternLayout
log4j.appender.A2.layout.ConversionPattern=The message '%m' at time %d%n 
##################################################################################################
```
4.2.2测试代码：


```
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/Category.hh>
int main() {
    // 1 读取解析配置文件
    // 读取出错, 完全可以忽略，可以定义一个缺省策略或者使用系统缺省策略
    // BasicLayout输出所有优先级日志到ConsoleAppender
    try
    {
        log4cpp::PropertyConfigurator::configure("./log4cpp.conf");
    }
    catch (log4cpp::ConfigureFailure& f)
    {
        std::cout << "Configure Problem: " << f.what() << std::endl;
        return -1;
    }
    //2    实例化category对象
    //    这些对象即使配置文件没有定义也可以使用，不过其属性继承其父category
    //    通常使用引用可能不太方便，可以使用指针，以后做指针使用
    log4cpp::Category& root = log4cpp::Category::getRoot();
    log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));
    log4cpp::Category& sub2 = log4cpp::Category::getInstance(std::string("sub2"));
    log4cpp::Category& sub3 = log4cpp::Category::getInstance(std::string("sub3"));
    log4cpp::Category& sub4 = log4cpp::Category::getInstance(std::string("sub4"));
    //    正常使用这些category对象进行日志处理。
    root.fatal("root's log");
    //    sub1 has appender A1 and rootappender. since the additivity property is set true by default
    sub1.info("sub1's log");
    //    sub2 has appender A2 appender. since the additivity property is set to false
    sub2.alert("sub2's log");
    //    sub3 only has A3 appender. since the additivity property is set to false
    sub3.debug("sub3's log");
    sub3.alert("sub3's log");
    //    sub4 can not be found in the config file, so the root category's appender and layout are used
    sub4.warn("sub4's log");
    return 0;
}

```

参考内容：
https://blog.csdn.net/rain_qingtian/article/details/41849047