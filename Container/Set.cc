#include <set>
#include <iostream>
#include <utility>

void visitSet(std::set<int> &s)
{
    for(auto &elem : s)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

void testSet()
{
    std::set<int> s {1, 2, 3, 4, 5, 5};     // set 会自动去重

    std::set<int> s2(s);        // 拷贝构造

    std::set<int> s3(s.begin(), s.find(4));

    visitSet(s);
    visitSet(s2);
    visitSet(s3);

}

void testSetCount()
{
    std::set<int> s {1, 2, 3, 4, 5, 5};

    // 找到返回1，否则返回0
    if(s.count(4) > 0)
    {
        std::cout << "find 4" << std::endl;
    }
    else
    {
        std::cout << "not find 4" << std::endl;
    }
}

void testSetInsert()
{
    std::set<int> s {1, 2, 3, 4, 5, 5};

    s.insert(6);
    visitSet(s);

    // 插入返回一个pair，第一个是迭代器，第二个是bool
    std::pair<std::set<int>::iterator, bool> ret = s.insert(6);

    if(ret.second)
    {
        std::cout << "insert 6 success" << std::endl;
    }
    else
    {
        std::cout << "insert 6 failed" << std::endl;
    }

}

void testSetInsert2()
{
    // 批量数据插入
    std::set<int> s {1, 2, 3, 4, 5, 6, 7};

    visitSet(s);

    std::set<int> s2 {8, 9, 10};

    s2.insert(s.begin(), s.find(5));   // 插入[begin, find(5))之间的数据

    visitSet(s2);
}


void testSetFind()
{
    std::set<int> s {1, 2, 3, 4, 5, 5};

    auto it = s.find(5);

    if(it != s.end())
    {
        std::cout << "find 5" << std::endl;
        std::cout << *it << std::endl;
    }
    else
    {
        std::cout << "not find 5" << std::endl;
    }
}

int main()
{
    // testSetCount();
    // testSetFind();
    // testSetInsert();
    testSetInsert2();
    // testSet();

    return 0;
}