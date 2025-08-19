#include <iostream>
#include <vector>
#include <memory>  // 包含智能指针头文件

// 定义简单的 Point 类
class Point {
public:
    double x;
    double y;
    
    // 构造函数
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {
        std::cout << "构造点: (" << x << ", " << y << ")\n";
    }
    
    // 析构函数
    ~Point() {
        std::cout << "销毁点: (" << x << ", " << y << ")\n";
    }
    
    // 移动构造函数
    Point(Point&& other) noexcept : x(other.x), y(other.y) {
        std::cout << "移动构造点: (" << x << ", " << y << ")\n";
    }
};


int main() {
    std::unique_ptr<Point> p1(new Point(1.0, 2.0));

    std::vector<std::unique_ptr<Point>> points;

    points.push_back(std::move(p1));  // 移动指针 p1 到 vector
    points.push_back(std::make_unique<Point>(3.0, 4.0));

    for(auto &p : points) {
        // 使用智能指针访问对象
        std::cout << "访问点: (" << p->x << ", " << p->y << ")" << std::endl;
    }

    return 0;
}