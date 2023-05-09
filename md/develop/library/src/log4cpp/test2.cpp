#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/Category.hh>
int main()
{
    // 1 读取解析配置文件
    // 读取出错, 完全可以忽略，可以定义一个缺省策略或者使用系统缺省策略
    // BasicLayout输出所有优先级日志到ConsoleAppender
    try
    {
        log4cpp::PropertyConfigurator::configure("./log4cpp.conf");
    }
    catch (log4cpp::ConfigureFailure &f)
    {
        std::cout << "Configure Problem: " << f.what() << std::endl;
        return -1;
    }
    // 2    实例化category对象
    //     这些对象即使配置文件没有定义也可以使用，不过其属性继承其父category
    //     通常使用引用可能不太方便，可以使用指针，以后做指针使用
    log4cpp::Category &root = log4cpp::Category::getRoot();
    log4cpp::Category &sub1 = log4cpp::Category::getInstance(std::string("sub1"));
    log4cpp::Category &sub2 = log4cpp::Category::getInstance(std::string("sub2"));
    log4cpp::Category &sub3 = log4cpp::Category::getInstance(std::string("sub3"));
    log4cpp::Category &sub4 = log4cpp::Category::getInstance(std::string("sub4"));
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
