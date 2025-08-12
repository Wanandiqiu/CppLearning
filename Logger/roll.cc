#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>

using namespace log4cpp;

void test1()
{
    // 1. 创建输出器
    OstreamAppender *appender1 = new OstreamAppender("console", &std::cout);

    // 2. 创建格式化对象
    PatternLayout *Layout = new PatternLayout();

    // 3. 定义格式
    Layout->setConversionPattern("[%d] %c %p %m%n"); // 日志 记录器名称 优先级 信息 换行

    // 4. 格式器和输出器绑定
    appender1->setLayout(Layout);

    // 5. 获取根记录器
    Category &root = Category::getRoot();

    // 6. 设置优先级
    root.setPriority(Priority::DEBUG);

    // 7. 添加输出器
    root.addAppender(appender1);

    // 8. 产生日志信息 -> 测试
    root.debug("debug message");
    root.error("error message");
    root.alert("alert message");

    Category::shutdown();
}

// 添加多个输出器
void test2()
{
    OstreamAppender *appender1 = new OstreamAppender("console", &std::cout);

    PatternLayout *Layout1 = new PatternLayout();

    Layout1->setConversionPattern("[%d] %c %p %m%n"); // 日志 记录器名称 优先级 信息 换行

    appender1->setLayout(Layout1);

    FileAppender *appender2 = new FileAppender("file", "logger.txt");

    PatternLayout *Layout2 = new PatternLayout();

    Layout2->setConversionPattern("[%d] %c %p %m%n");

    appender2->setLayout(Layout2);

    Category &root = Category::getRoot();

    root.setPriority(Priority::DEBUG);

    root.addAppender(appender1); // 添加输出器1

    Category &childCategory = Category::getInstance("childCategory"); // 获取子输出器

    childCategory.setAdditivity(false); // 不继承root配置

    childCategory.setPriority(Priority::ERROR);

    childCategory.addAppender(appender2); // 添加输出器2

    root.debug("debug message");
    root.error("error message");
    root.alert("alert message");

    childCategory.debug("child debug message");
    childCategory.error("child error message");
    childCategory.alert("child alert message");

    Category::shutdown();
}

void test3()
{
    OstreamAppender *appender1 = new OstreamAppender("console", &std::cout);

    PatternLayout *Layout1 = new PatternLayout();

    Layout1->setConversionPattern("[%d] %c %p %m%n"); // 日志 记录器名称 优先级 信息 换行

    appender1->setLayout(Layout1);

    FileAppender *appender2 = new RollingFileAppender("file", "logger.txt", 100, 5);

    PatternLayout *Layout2 = new PatternLayout();

    Layout2->setConversionPattern("[%d] %c %p %m%n");

    appender2->setLayout(Layout2);

    Category &root = Category::getRoot();

    root.setPriority(Priority::DEBUG);

    root.addAppender(appender1); // 添加输出器1

    Category &childCategory = Category::getInstance("childCategory"); // 获取子输出器

    childCategory.setAdditivity(false); // 不继承root配置

    childCategory.setPriority(Priority::ERROR);

    childCategory.addAppender(appender2); // 添加输出器2

    root.debug("debug message");
    root.error("error message");
    root.alert("alert message");

    for (int i = 0; i < 10; i++)
    {
        childCategory.debug("child debug message");
        childCategory.error("child error message");
        childCategory.alert("child alert message");
    }
}

int main()
{
    test3();
    // char a[200] = {0};
    // std::cin.getline(a, 200, ' ');   // 遇到空格结束  设置了空格为分隔符
    // std::cout << a;
}