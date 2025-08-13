#include <iostream>
#include <string>
#include <cmath>

using std::cout;
using std::endl;
using std::string;

class Figure
{
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

class Rectangle
:public Figure
{
public:
    Rectangle(int x, int y)
    :_x(x), _y(y)
    {}

    string getName() const override
    {
        return "矩形";
    }

    double getArea() const override
    {
        return _x * _y;
    }
private:
    double _x;
    double _y;
};

class Circle
:public Figure
{
public:
    Circle(double r)
    :_r(r)
    {}

    string getName() const override
    {
        return "圆形";
    }

    double getArea() const override
    {
        return 3.14 * _r * _r;
    }
private:
    double _r;
};

class Triangle
:public Figure
{
public:
    Triangle(double a, double b, double c)
    :_a(a), _b(b), _c(c)
    {}

    string getName() const override
    {
        return "三角形";
    }

    double getArea() const override
    {
        double p = (_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }
private:
    double _a;
    double _b;
    double _c;
};

void display(Figure &fig)
{
    cout << fig.getName() << "的面积是:" << fig.getArea() << endl;
}

void test()
{
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3, 4, 5);
    display(r);
    display(c);
    display(t);
}

int main()
{
    test();
    return 0;
}