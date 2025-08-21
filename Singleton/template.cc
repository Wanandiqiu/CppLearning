#include <iostream>
#include <memory>
#include <mutex>

template<typename T>
class Singleton
{
public:
    ~Singleton() = default;
    static std::shared_ptr<T> getInstance()
    {
        static std::once_flag _flag;
        std::call_once(_flag, []{
            _pInstance = std::shared_ptr<T>(new T());
        });
        return _pInstance;
    }
protected:
    Singleton() = default;
    Singleton(const Singleton& lhs) = delete;
    Singleton& operator=(const Singleton &lhs) = delete;

    static std::shared_ptr<T> _pInstance;
};

template<typename T>
std::shared_ptr<T> Singleton<T>::_pInstance = nullptr;


// 继承这个基类
class SingleNet : public Singleton<SingleNet>
{
    friend class Singleton<SingleNet>;
private:
    SingleNet() = default;
public: 
    ~SingleNet()
    {
        std::cout << "~Singleton()" << std::endl;
    }
};


int main()
{
    std::shared_ptr<SingleNet> s1 =  Singleton<SingleNet>::getInstance();
    std::shared_ptr<SingleNet> s2 =  Singleton<SingleNet>::getInstance();

    std::cout << s1.get() << std::endl;
    std::cout << s2.get() << std::endl;

    return 0;
}
