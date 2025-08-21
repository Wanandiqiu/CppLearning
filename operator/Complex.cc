#include <iostream>
using namespace std;

class Complex {
private:
    double real; // 实部
    double imag; // 虚部

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    double getReal() const { return real; }

    double getImag() const { return imag; }

    // 加法运算符重载 (成员函数)
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // 减法运算符重载 (成员函数)
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // 加法赋值运算符重载
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }

    // 减法赋值运算符重载
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }

    // 前缀自增 (返回引用)
    Complex& operator++() {
        ++real;
        return *this;
    }

    // 后缀自增 (返回旧值)
    Complex operator++(int) {
        Complex temp = *this;
        ++real;
        return temp;
    }

    // 前缀自减 (返回引用)
    Complex& operator--() {
        --real;
        return *this;
    }

    // 后缀自减 (返回旧值)
    Complex operator--(int) {
        Complex temp = *this;
        --real;
        return temp;
    }

    // 输出运算符重载 (友元函数)
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << "+";
        os << c.imag << "i";
        return os;
    }
};

int main() {
    // 测试运算符重载
    Complex a(3.0, 4.0);
    Complex b(1.5, 2.5);
    
    cout << "a = " << a << endl;       // 3+4i
    cout << "b = " << b << endl;       // 1.5+2.5i
    
    Complex c = a + b;
    cout << "a + b = " << c << endl;   // 4.5+6.5i
    
    Complex d = a - b;
    cout << "a - b = " << d << endl;   // 1.5+1.5i
    
    a += b;
    cout << "a += b: " << a << endl;   // 4.5+6.5i
    
    a -= b;
    cout << "a -= b: " << a << endl;   // 3+4i
    
    cout << "++a: " << ++a << endl;    // 4+4i (前缀)
    cout << "a: " << a << endl;        // 4+4i
    
    cout << "a++: " << a++ << endl;    // 4+4i (后缀)
    cout << "a: " << a << endl;        // 5+4i
    
    cout << "--a: " << --a << endl;    // 4+4i (前缀)
    cout << "a: " << a << endl;        // 4+4i
    
    cout << "a--: " << a-- << endl;    // 4+4i (后缀)
    cout << "a: " << a << endl;        // 3+4i
    
    return 0;
}