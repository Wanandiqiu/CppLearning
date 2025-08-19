#include <iostream>
#include <vector>
#include <thread>

std::vector<int> unsafe_vec = {1, 2, 3};  // 非线程安全容器

void modify() {
    for (int i = 0; i < 1000; ++i) {
        // 并发修改：可能导致容量重分配
        unsafe_vec.push_back(i);
    }
}

void Read() {
    for (int i = 0; i < 1000; ++i) {
        // 并发读取：可能读到无效迭代器
        if (!unsafe_vec.empty()) {
            std::cout << unsafe_vec.back() << " ";  // 可能访问已失效的内存
        }
    }
}

int main() {
    std::thread t1(modify);
    std::thread t2(modify);  // 两个线程并发修改
    std::thread t3(Read);    // 同时读取

    t1.join();
    t2.join();
    t3.join();

    // 高概率出现以下一种或多种情况：
    // 1. 程序崩溃（segment fault）
    // 2. 输出乱码或异常值
    // 3. 容器大小不正确
    std::cout << "\nFinal size: " << unsafe_vec.size() << std::endl;
}