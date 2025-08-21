#include <iostream>
#include <set>
#include <unordered_set>

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
    os << "(" << pt.getX() << " " << pt.getY() << ")";
    return os;
}

// 自定义比较类型  Hash
struct MyHash
{
    std::size_t operator()(const Point &pt) const
    {
        std::cout << "Hash自定义比较类型" << std::endl;
        return pt.getX() ^ (pt.getY() << 1);
    }
};

// 特化 Hash
template <>
struct std::hash<Point>
{
    std::size_t operator()(const Point &pt) const
    {
        std::cout << "Hash特化类型" << std::endl;
        return pt.getX() ^ (pt.getY() << 1);
    }
};

// 作用域

// 哈希冲突出现了几次
template <>
struct std::equal_to<Point>
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        std::cout << "equal_to 特化模板" << std::endl;
        if (lhs.getX() == rhs.getY() && lhs.getY() == rhs.getY())
        {
            return true;
        }
        else
            return false;
    }
};

// 自定义比较类型
struct MyEqual
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        std::cout << "equal_to 自定义比较类型模板" << std::endl;
        if (lhs.getX() == rhs.getY() && lhs.getY() == rhs.getY())
        {
            return true;
        }
        else
            return false;
    }
};

// 重载
bool operator==(const Point &lhs, const Point &rhs)
{
    std::cout << "==运算符重载" << std::endl;
    return (lhs.getX() == rhs.getX()) &&
           (lhs.getY() == rhs.getY());
}

template <class Container>
void display(const Container &con)
{
    for (auto &ele : con)
    {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
}

#if 0
void print(std::unordered_set<Point, MyHash> &st)
{
    for(auto &elem : st)
    {
        std::cout << elem << std::endl;
    }
}

void print(std::unordered_set<Point> &st)
{
    for(auto &elem : st)
    {
        std::cout << elem << std::endl;
    }
}
#endif

int main()
{
    // std::unordered_set<Point, MyHash> st{{1, 2}, {5, 8}, {-1, 1}, {3, 2}, {1, 2}};

    //std::unordered_set<Point> st{{1, 2}, {5, 8}, {-1, 1}, {3, 2}, {1, 2}};

    std::unordered_set<Point, MyHash, MyEqual> st{{1, 2}, {5, 8}, {-1, 1}, {3, 2}, {1, 2}};
    display(st);

    return 0;
}