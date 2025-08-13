#include <iostream>
#include <string.h>
#include <vector>

class Person
{
public:
    Person() = default;

    Person(const char *name, int age) : _name(new char(strlen(name) + 1)), _age(age)
    {
        // std::cout << "Person(char*, int)" << std::endl;
        strcpy(_name, name);
    }

    ~Person()
    {
        delete [] _name;
    }

    Person(const Person &lhs) : _name(new char(strlen(lhs._name) + 1)), _age(lhs._age)
    {
        std::cout << "Person(const Person&)" << std::endl;
        strcpy(_name, lhs._name);
    }

    Person &operator=(const Person &lhs)
    {
        std::cout << "Person& operator=(const Person&)" << std::endl;
        if (this != &lhs)
        {
            delete[] _name;

            _age = lhs._age;
            _name = new char[strlen(lhs._name) + 1];
            strcpy(_name, lhs._name);
        }
        return *this;
    }

    virtual void display()
    {
        // std::cout << "Name : " << _name << " " << "Age: " << _age << std::endl;
    }

    char *getName() const { return _name; }

    int getAge() const { return _age; }

private:
    char *_name;
    int _age;
};

// 拷贝和赋值不会被继承，但是，在派生类的拷贝和赋值操作中，可以调用基类的对应操作来完成基类部分的复制
class Employee
    : public Person
{
public:
    Employee(const char *name, int age, const char *development, double salary) : Person(name, age), _development(new char[strlen(development) + 1]), _salary(salary)
    {
        strcpy(_development, development);
    }

    void display() override
    {
        std::cout << "Name : " << getName() << " " << "Age: " << getAge() << " " << "Salary: " << _salary << " " << "Development: " << _development << std::endl;
    }

    Employee(const Employee &lhs) : Person(lhs), _salary(lhs._salary)
    {
        std::cout << "Employee(const Employee&)" << std::endl;

        _development = new char[strlen(lhs._development) + 1];
        strcpy(_development, lhs._development);
    }

    ~Employee()
    {
        delete []_development;
    }

    Employee &operator=(const Employee &lhs)
    {
        if (this != &lhs)
        {
            Person::operator=(lhs); // 调用父类的赋值运算符函数

            delete[] _development;

            _salary = lhs._salary;
            _development = new char[strlen(lhs._development) + 1];
            strcpy(_development, lhs._development);
        }
        return *this;
    }

    // 计算平均工资
    static double averageSalary(std::vector<Employee> employee, int count)
    {
        if(count < 0) { return 0.0; }

        double total = 0.0;
        for(int i = 0; i < count; i++)
        {
            total += employee[i]._salary;
        }
        return total / count;
    }

private:
    char *_development;
    double _salary;
};

int main()
{
    Employee e("Tom", 20, "C++", 28000);
    e.display();

    Employee e1(e);
    e1.display();

    Employee e2("Jerry", 23, "Go", 24000);

    e = e2;
    e.display();

    Employee e3("Bob", 21, "C", 40000);

    Employee e4("Alice", 18, "Python", 20000);

    std::vector<Employee> EmployeeVec;

    EmployeeVec.push_back(e);
    EmployeeVec.push_back(e2);
    EmployeeVec.push_back(e3);
    EmployeeVec.push_back(e4);

    double average = Employee::averageSalary(EmployeeVec, EmployeeVec.size());

    std::cout << "average salary is " << average << std::endl;

    return 0;
}