#include <queue>
#include <iostream>

class Point
{
public:
    Point() = default;

    Point(int x, int y) : _x(x),
                          _y(y)
    {
    }

    int getX() const { return _x; }
    int getY() const { return _y; }

private:
    int _x;
    int _y;
};

template <>
struct std::less<Point>
{
    bool operator()(const Point &lhs, const Point &rhs)
    {
        if (lhs.getX() != rhs.getX())
            return lhs.getX() < rhs.getX();

        return lhs.getY() < rhs.getY();
    }
};

std::ostream &operator<<(std::ostream &os, const Point &pt)
{
    os << "(" << pt.getX() << ", " << pt.getY() << ")" << std::endl;
    return os;
}

int main()
{
    std::priority_queue<Point/*, std::vector<Point>, std::greater<Point>*/> priQue;

    priQue.push(Point(1, 1));
    std::cout << "优先级最高的 :" << priQue.top() << std::endl;
    priQue.push(Point(1, 2));
    std::cout << "优先级最高的 :" << priQue.top() << std::endl;
    priQue.push(Point(2, 2));
    std::cout << "优先级最高的 :" << priQue.top() << std::endl;
    priQue.push(Point(5, 3));
    std::cout << "优先级最高的 :" << priQue.top() << std::endl;
    priQue.push(Point(3, 1));
    std::cout << "优先级最高的 :" << priQue.top() << std::endl;

    return 0;
}