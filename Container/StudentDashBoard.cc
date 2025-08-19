#include <iostream>
#include <string>
#include <list>

class Student
{
public:
    Student(std::string name, int age, int chinese, int math, int english)
        : _Name(name),
          _Age(age),
          _Chinese(chinese),
          _Math(math),
          _English(english)
    {
    }

    int getSum() const { return _Chinese + _Math + _English; }

    void print()
    {
        std::cout << _Name << " Score is: " << _Chinese << ", " << _Math << ", " << _English << std::endl;
    }

    bool operator>(const Student &lhs) const
    {
        return this->getSum() == lhs.getSum() ? this->_Chinese > lhs._Chinese : this->getSum() > lhs.getSum();
    }

private:
    std::string _Name;
    int _Age;
    int _Chinese;
    int _Math;
    int _English;
};

template <class T>
struct MyCompare
{
    bool operator()(const T & lhs,const T & rhs) const
    {
        return lhs > rhs;
    }
};

void display(std::list<Student> lst)
{
    for (auto &elem : lst)
    {
        elem.print();
    }
}

void test()
{
    Student s1("xiaoming", 10, 100, 90, 78);
    Student s2("xiaosong", 11, 70, 90, 68);
    Student s3("xiaozhao", 17, 90, 90, 88);
    Student s4("xiaogang", 12, 60, 100, 98);
    Student s5("xiaoxu", 14, 50, 90, 60);
    Student s6("xiaoli", 15, 89, 95, 94);

    std::list<Student> lst{s1, s2, s3, s4, s5, s6};

    MyCompare<Student> com;
    lst.sort(com);

    display(lst);
}

int main()
{
    test();
}
