#include "String.h"

String::String()
{
    std::cout << "String" << std::endl;
    _pstr = new char[1];
    _pstr[0] = '\0';
}

String::String(const char *pstr):_pstr(new char[strlen(pstr) + 1])
{
    std::cout << "String(const char *pstr)" << std::endl;
    strcpy(_pstr, pstr);
}

// 拷贝构造
String::String(const String &lhs) : _pstr(new char[strlen(lhs._pstr) + 1])
{
    std::cout << "String(const String &lhs)" << std::endl;
    strcpy(_pstr, lhs._pstr);
}

String &String::operator=(const String &rhs)
{
    std::cout << "String &operator(const String &rhs)" << std::endl;
    if(this == &rhs)
    {
        return *this;
    }

    delete []_pstr;

    _pstr = new char[strlen(rhs._pstr) + 1];
    strcpy(_pstr, rhs._pstr);

    return *this;
}

String::~String()
{
    if(_pstr != nullptr)
    {
        delete _pstr;
        _pstr = nullptr;
    }
}

String::String(String &&rhs)
{
    std::cout << "String(String &&)" << std::endl;
    _pstr = rhs._pstr;
    rhs._pstr = nullptr;
}

String &String::operator=(String &&rhs)
{
    std::cout << "String &operator=(String &&)" << std::endl;

    if(this != &rhs)
    {
        delete [] _pstr;
        _pstr = rhs._pstr;
        rhs._pstr = nullptr;
    }
    return *this;
}

String &String::operator+=(const String &lhs)
{
    std::cout << "String &operator+=(const String &lhs)" << std::endl;
    char *temp = new char[strlen(_pstr) + strlen(lhs._pstr) + 1];
    strcpy(temp, _pstr);

    strcat(temp, lhs.c_str());
    
    delete []_pstr;
    _pstr = temp;

    return *this;
}

String &String::operator+=(const char *lhs)
{
    std::cout << "String &operator+=(const char *lhs)" << std::endl;
    return *this += String(lhs);
}

char &String::operator[](std::size_t index)
{
    return _pstr[index];
}

const char &String::operator[](std::size_t index) const
{
    return _pstr[index];
}

const char* String::c_str() const
{
    return _pstr;
}

std::size_t String::size() const
{
    return strlen(_pstr);
}

std::ostream &operator<<(std::ostream &os, const String &lhs)
{
    os << lhs._pstr;
    return os;
}

std::istream &operator>>(std::istream &is, String &lhs)
{
    //is >> lhs._pstr;
    char buffer[1024];
    is >> buffer;

    delete [] lhs._pstr;  // 释放原有内存

    lhs._pstr = new char[strlen(buffer) + 1];
    strcpy(lhs._pstr, buffer);

    return is;
}

bool operator==(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) == 0;
}

bool operator!=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) != 0;
}

bool operator<(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}

bool operator>(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}

bool operator<=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}

bool operator>=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}

String operator+(const String &lhs, const String &rhs)
{
    String temp(lhs);
    temp += rhs;

    return temp;
}

String operator+(const String &lhs, const char *rhs)
{
    String temp(lhs);
    temp += rhs;
    return temp;
}

String operator+(const char *lhs, const String &rhs)
{
    String temp(lhs);
    temp += rhs;
    return temp;
}

int main()
{
    String s1;
    String s2("hello");

    String s3(s2);  // 拷贝构造
    s3 = s1;  // 赋值构造

    String s4(std::move(s3));  // 移动构造
    s4 = std::move(s2);  // 移动赋值

    // String s5 = "hello";
    // s5 += " shabi";

    // std::cout << s5 << std::endl;

    // const char *p = " ni hao ma";
    // s5 += p;

    // std::cout << s5 << std::endl;

    // std::cout << s5[0] << std::endl;
    // s5[0] = 'H';
    // std::cout << s5 << std::endl;

    // std::cout << s5.c_str() << std::endl;
    // std::cout << s5.size() << std::endl;


    // // String s6;
    // // std::cin >> s6;
    // // std::cout << s6 << std::endl;

    // String s7 = "hello";
    // String s8 = "Hello";

    // std::cout << (s7 == s8) << std::endl;
    // std::cout << (s7 != s8) << std::endl;

    // String s9 = s7 + s8;
    // std::cout << s9 << std::endl;

    // const char *p1 = "shabi";
    // String s10 = p1 + s8;
    // std::cout << s10 << std::endl;

}