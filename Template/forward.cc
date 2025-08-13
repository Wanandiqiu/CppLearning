#include <iostream>
#include <string>
#include <utility>

// 目标函数，分别有左值和右值的重载
void process(const int &x) {
    std::cout << "process(const int&)" << std::endl;
}

void process(int &&x) {
    std::cout << "process(int&&)" << std::endl;
}

template<typename T>
void wrapper(T&& arg) {
    process(std::forward<T>(arg));  // 原样转发
}

int main()
{
    int a = 10;
    wrapper(a);
    wrapper(20);
    wrapper(std::move(a));

    return 0;
}