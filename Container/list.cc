#include <iostream>
#include <list>

template <class Container>
void print(Container &con)
{
    for (auto &elem : con)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

void testList()
{
    std::list<int> lst = {3, 2, 6, 8, 5};
    std::list<int> lst1 = {7, 9, 1, 4, 10};

    /*
        sort: std::less
    */
    std::list<int> lst2 = {4, 3, 2, 7, 1, 9, 5, 8};

    // 升序
    std::less<int> ls;
    lst2.sort(ls);
    print(lst2);

    // 降序
    lst2.sort(std::greater<int>());
    print(lst2);

    lst.merge(lst1); // 归并  3 2 6 7 8 5 9 1 4 10  局部有序

    print(lst);

    // merge : Merges two sorted lists into one sorted list.

    lst.sort();
    lst1.sort();
    lst.merge(lst1);

    print(lst);

    /*
        unique  删除相邻且重复的元素，它不会自动处理非相邻的重复元素
    */

    std::list<int> lst3{1, 1, 3, 3, 4, 5, 3, 2, 7, 8, 4, 3};
    lst3.sort();
    lst3.unique();
    print(lst3);

    // 链表反转
    lst3.reverse();
    print(lst3);

    // splice 拼接
    /*
        void splice( const_iterator pos, list& other );
        Transfers elements from other to *this. The elements are inserted at pos.
    */
   std::list<int> lst4{1, 3, 4, 5, 6, 8};
   std::list<int> lst5{2, 4, 5, 8, 7, 9};
   lst4.splice(++lst4.begin(), lst5);   // 将lst5插入到lst4的 1 后面
   print(lst4);

}

int main()
{
    testList();

    return 0;
}