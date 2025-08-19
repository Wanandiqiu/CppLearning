#include <iostream>
#include <memory>

class Child;

class Parent
{
public:
    Parent() { std::cout << "Parent()" << std::endl; }
    ~Parent() { std::cout << "~Parent()" << std::endl; }

    std::shared_ptr<Child> m_spChild;   // 子类指针
};


class Child
{
public:
    Child() { std::cout << "Child()" << std::endl; }
    ~Child() { std::cout << "~Child()" << std::endl; }

    std::weak_ptr<Parent> m_spParent;    // 父类型指针
};


/**
 * 测试函数，演示智能指针的使用和父子对象的关系
 */
void test()
{
    // // 在堆上创建了空间，用两个智能指针指向
    // std::shared_ptr<Parent> parentPtr(new Parent());  // 创建一个Parent对象的智能指针
    // std::shared_ptr<Child> ChildPtr(new Child());    // 创建一个Child对象的智能指针

    // // 建立父子关系，让父对象的成员指针指向子对象
    // parentPtr->m_spChild = ChildPtr;
    
    // // 建立父子关系，让子对象的成员指针指向父对象
    // ChildPtr->m_spParent = parentPtr;

    // std::cout << "parentPtr.use_count() = " << parentPtr.use_count() << std::endl;

    auto child = std::make_shared<Child>();
    auto parent = std::make_shared<Parent>();

    child->m_spParent = parent;
    parent->m_spChild = child;

    std::cout << "parentPtr.use_count() = " << parent.use_count() << std::endl;
    std::cout << "childPtr.use_count() = " << child.use_count() << std::endl;
}

int main()
{   
    test();

    return 0;
}