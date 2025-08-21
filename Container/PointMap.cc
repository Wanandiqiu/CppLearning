#include <iostream>
#include <map>
#include <string>

using std::map;
using std::string;

class Point
{
public:
    Point() = default;
    Point(int x, int y)
        : _x(x), _y(y)
    {
    }

    int getX() const
    {
        return _x;
    }

    int getY() const
    {
        return _y;
    }

private:
    int _x;
    int _y;
};

std::ostream &operator<<(std::ostream &os, const Point &pt)
{
    os << pt.getX() << " " << pt.getY();
    return os;
}

// 自定义比较类型
struct MyCompare
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        return (lhs.getX() > rhs.getX() && lhs.getY() > rhs.getY());
    }
};

// 模板特化
// template<>
// struct std::less<Point>
// {
//     bool operator()(const Point &lhs, const Point &rhs) const
//     {
//         return (lhs.getX() > rhs.getX() && lhs.getY() > rhs.getY());
//     }
// };

// 重载
bool operator<(const Point &lhs, const Point &rhs)
{
    return (lhs.getX() < rhs.getX()) &&
           (lhs.getY() < rhs.getY());
}

// 打印
void print(std::map<Point, std::string, MyCompare> &mp)
{
    for (auto &elem : mp)
    {
        std::cout << elem.first << " " << elem.second << " " << std::endl;
    }
}

void print(std::map<Point, std::string> &mp)
{
    for (auto &elem : mp)
    {
        std::cout << elem.first << " " << elem.second << " " << std::endl;
    }
}

int main()
{
    // std::map<Point, std::string, MyCompare> mp {{{1, 2}, "hello"}, {{2, 3}, "world"}, {{3, 4}, "monkey"}};

    std::map<Point, std::string> mp{{{1, 2}, "hello"}, {{2, 3}, "world"}, {{3, 4}, "monkey"}};

    print(mp);

    return 0;
}