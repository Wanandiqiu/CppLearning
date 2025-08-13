#include <iostream>
#include <set>

template <typename T>
T add(T a, T b)
{
    return a + b;
}

template <typename T>
std::set<T> fusion(std::set<T> a, std::set<T> b)
{
    std::set<T> c;
    c.insert(a.begin(), a.end());
    c.insert(b.begin(), b.end());
    return c;
}

int main()
{
    std::cout << add(1, 2) << std::endl;
    std::cout << add(1.1, 2.2) << std::endl;

    std::cout << "-----------------" << std::endl;

    std::set<int> a = {1, 2, 3};
    std::set<int> b = {3, 4, 5};

    std::set<int> c = fusion(a, b);

    for(auto & elem : c)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}