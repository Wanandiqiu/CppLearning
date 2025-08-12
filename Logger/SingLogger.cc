#include "SingLogger.h"

Logger *Logger::_pInstance = nullptr;
Category *Logger::_root = nullptr;

Logger *Logger::getInstance()
{
    if (_pInstance == nullptr)
    {
        _pInstance = new Logger();
    }
    return _pInstance;
}

Logger::~Logger()
{
    Category::shutdown();
}

void Logger::destroy()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = nullptr;
    }
}

Logger::Logger()
{
    // 初始化Category
    OstreamAppender *appender1 = new OstreamAppender("console", &std::cout);

    PatternLayout *Layout1 = new PatternLayout();

    Layout1->setConversionPattern("[%d] %c %p %m%n");

    appender1->setLayout(Layout1);

    FileAppender *appender2 = new FileAppender("file", "LOG.txt"); // 保存到文件

    PatternLayout *layout2 = new PatternLayout();

    layout2->setConversionPattern("[%d] %c %p %m%n"); // 时间 记录器名称 优先级 信息 换行

    appender2->setLayout(layout2);

    _root = &Category::getRoot().getInstance("logger");

    // 设置优先级
    _root->setPriority(Priority::DEBUG);

    // 添加输出器
    _root->addAppender(appender1);
    _root->addAppender(appender2);
}

void Logger::warn(const char *file, int line, const char *func, const char *msg)
{
    std::string format;

    std::ostringstream oss;

    oss << file << ":" << line << " in " << func << " [" << msg << "]";

    _root->warn(oss.str());
}

void Logger::error(const char *file, int line, const char *func, const char *msg)
{
    std::string format;

    std::ostringstream oss;

    oss << file << ":" << line << " in " << func << " [" << msg << "]";

    _root->error(oss.str());
}

void Logger::debug(const char *file, int line, const char *func, const char *msg)
{
    std::string format;

    std::ostringstream oss;

    oss << file << ":" << line << " in " << func << " [" << msg << "]";

    _root->debug(oss.str());
}

void Logger::info(const char *file, int line, const char *func, const char *msg)
{
    std::string format;

    std::ostringstream oss;

    oss << file << ":" << line << " in " << func << " [" << msg << "]";

    _root->info(oss.str());
}

int main()
{
    LOG_WARN("test warn msg");
    LOG_ERROR("test error msg");
    LOG_DEBUG("test debug msg");
    LOG_INFO("test info msg");

    Logger::destroy();
    return 0;
}