#include <iostream>

/**
 * @brief 单例模式实现方式一: 静态局部变量
 * 
 */

class Sigleton {
private:
    Sigleton() = default;
    Sigleton(const Sigleton&) = delete;
    Sigleton& operator=(const Sigleton&) = delete;

    ~Sigleton() {
        std::cout << "~Sigleton()" << std::endl;
    }

public:
    static Sigleton& getInstance() {   // 类名::getInstance
        // 静态局部变量，只会实例化一次
        static Sigleton sig;    // 构造和析构都发生在 getInstance()函数作用域内
        return sig;
    }
};

int main()
{
    Sigleton &s1 = Sigleton::getInstance();
    Sigleton &s2 = Sigleton::getInstance();
    std::cout << &s1 << std::endl;
    std::cout << &s2 << std::endl;


    return 0;
}