#include <iostream>
#include <memory>

using std::shared_ptr;

class Point
{
public:
    Point(int x, int y)
    : x_(x)
    , y_(y)
    {
        std::cout << "Point()" << std::endl;
    }

private:
    int x_;
    int y_;
};


// 不能将一个原生指针交给不同的智能指针进行托管  -> double free
void test()
{
    Point *p = new Point(1, 2);
    shared_ptr<Point> p1(p);
    shared_ptr<Point> p2(p);
}


// test  enable_shared_from_this
class MyClass {
public:
    std::shared_ptr<MyClass> get_shared() {
        return std::shared_ptr<MyClass>(this); // 危险！创建了新的控制块
    }
};

void test1()
{
    auto ptr1 = std::make_shared<MyClass>();
    auto ptr2 = ptr1->get_shared();

    std::cout << ptr1.use_count() << std::endl; 
}



class MyClass2 : public std::enable_shared_from_this<MyClass2> {
public:
    std::shared_ptr<MyClass2> get_shared() {
        return shared_from_this(); // 安全获取 shared_ptr
    }
};

void test2()
{
    auto ptr1 = std::make_shared<MyClass2>();
    auto ptr2 = ptr1->get_shared();

    std::cout << ptr1.use_count() << std::endl;
    std::cout << ptr1.use_count() << std::endl;

}

int main()
{
    test2();
    return 0;
}