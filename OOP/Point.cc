#include <iostream>
#include <string.h>
#include <cmath>

class Point
{
public:
    Point() = default;
    Point(int x, int y) : _x(x), _y(y) {}

    float getX(){ return _x; }
    float getY() { return _y; }

private:
    float _x;
    float _y;
};

class Color
{
public:
    Color() = default;
    Color(const char *color) : _color(new char[strlen(color) + 1]) {
        strcpy(_color, color);
    }

    void printColor()
    {
        std::cout << _color << std::endl;
    }

private:
    char *_color;
};

class Line
{
public:
    Line() = default;
    Line(int x1, int y1, int x2, int y2) : _p1(x1, y1), _p2(x2, y2)
    {
    }

    float Distance()
    {
        float dx = _p2.getX() - _p1.getX();
        float dy = _p2.getY() - _p1.getY();

        return std::sqrt(dx * dx + dy * dy);
    }

private:
    Point _p1;
    Point _p2;
};

class Triangle
    : public Line,
      public Color
{
public:
    Triangle(int x1, int y1, int x2, int y2, const char *color, float height)
        : _height(height),
          Color(color),
          Line(x1, y1, x2, y2)
    {
    }

    void getColor()
    {
        Color::printColor();
    }

    float Area()
    {
        float area = Line::Distance() * _height / 2;
        std::cout << "Area is " << area << std::endl;
        return area;
    }

    void perimeter()
    {
        float hypotenuse = std::sqrt(Line::Distance() * Line::Distance() +  _height * _height);
        
        float result = hypotenuse + _height + Line::Distance();
        std::cout << "hypotenuse is " << result << std::endl;
    }

private:
    float _height;
};


int main()
{
    Triangle t1(0, 0, 4, 0, "blue", 3);

    t1.Area();
    t1.perimeter();
    t1.getColor();

    return 0;
}