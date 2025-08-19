#include <iostream>
#include <string.h>


class Computer
{
public:
    Computer(int price, const char *brand) {
        _price = price;
        this->_brand = new char[strlen(brand) + 1];
        strcpy(this->_brand, brand);
    }

    ~Computer() {
        if(this->_brand)
        {
            delete[] _brand;
            _brand = nullptr;
        }
    }

private:
    int _price;
    char *_brand;
};

template <typename T>
class RAII
{
public:
    RAII(T *ptr) : _ptr(ptr)
    {
        //std::cout << "RAII" << std::endl;
    }

    ~RAII()
    {
        if(_ptr)
        {
            delete _ptr;
            _ptr = nullptr;
        }
    }

private:
    T *_ptr;
};

int main()
{
    RAII<Computer> computer = new Computer(10000, "Dell");
    return 0;
}