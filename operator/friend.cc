#include <iostream>

class A
{
public:
    A(int a) : _a(a) {}
    void Print() const
    {
        std::cout << "A::_a = " << _a << std::endl;
    }

    // 使用友元函数而不是友元成员函数
    friend void showA(const A &a);

private:
    int _a;
};

class B
{
public:
    B(int b) : _b(b) {}
    void print() const
    {
        std::cout << "B::_b = " << _b << std::endl;
    }

private:
    int _b;
};

// 友元函数，可以访问 A 的私有成员
void showA(const A &a)
{
    std::cout << "A's private member: " << a._a << std::endl;
}

int main()
{
    B b(10);
    b.print();

    A a(20);
    a.Print();

    showA(a); // 调用友元函数

    return 0;
}
