#include <iostream>

using std::endl;
using std::cout;

#if 0
// 方法一
class Point
{
public:
    friend class Complex;

    Point(int x, int y) : x_(x), y_(y) {}

private:
    int x_;
    int y_;
};

class Complex
{
public:
    Complex(int real, int imag) : real_(real), imag_(imag) {}

    Complex operator=(const Point& p)
    {
        real_ = p.x_;
        imag_ = p.y_;
        return *this;
    }

    void print()
    {
        cout << real_ << " + " << imag_ << "i" << endl;
    }

private:
    int real_;
    int imag_;
};
#endif

class Complex
{
public: 
    Complex(int real, int imag) : real_(real), imag_(imag) {}

    void print()
    {
        cout << real_ << " + " << imag_ << "i" << endl;
    }

private:
    int real_;  
    int imag_;
};

// 方法二
class Point
{
public:
    Point(int x, int y) : x_(x), y_(y) {}

    operator Complex() const
    {
        std::cout << "operator Complex() called" << std::endl;
        return Complex(x_, y_);
    }

    void print()
    {
        cout << x_ << " " << y_ << endl;
    }

private:
    int x_;
    int y_;
};


#if 0
// 方法三
class Point
{
public:
    Point(int x, int y) : x_(x), y_(y) {}

    void print()
    {
        cout << x_ << " " << y_ << endl;
    }

    friend class Complex;

private:
    int x_;
    int y_;
};

class Complex {
public:
    Complex(const Point& p) : real_(p.x_), imag_(p.y_) {}

    Complex(int real, int imag) : real_(real), imag_(imag) {}

    void print()
    {
        cout << real_ << " + " << imag_ << "i" << endl;
    }

private:
    int real_;
    int imag_;
};
#endif


int main()
{
    Point p(1, 2);
    Complex c(p); 
    c = p;   // 调用 Point::operator Complex()

    c.print();

    return 0;
}