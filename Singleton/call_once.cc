#include <memory>
#include <iostream>
#include <mutex>

/**
 * @brief 单例模式实现方式二: call_once
 * 
 */

class Singleton {
public:
    static std::shared_ptr<Singleton> getInstance()
    {
        static std::once_flag flag;   // 判断 flag 有没有初始化，没有就初始化一次 
        std::call_once(flag, []{
            _instance = std::shared_ptr<Singleton>(new Singleton(), [](Singleton* p){
                delete p; // 引用计数为0时，释放资源  p 是智能指针管理的裸指针
            });
        });

        return _instance;
    }

private:
    Singleton() = default;

    ~Singleton() {
        std::cout << "~Sigleton" << std::endl;
    }

    Singleton(const Singleton &lhs) = delete;
    Singleton& operator=(const Singleton &lhs) = delete;

    static std::shared_ptr<Singleton> _instance;
};

std::shared_ptr<Singleton> Singleton::_instance = nullptr;


int main()
{
    std::shared_ptr<Singleton> s1 = Singleton::getInstance();
    std::shared_ptr<Singleton> s2 = Singleton::getInstance();

    std::cout << s1.get() << std::endl;
    std::cout << s2.get() << std::endl;

    return 0;
}