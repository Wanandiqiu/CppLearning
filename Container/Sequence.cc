#include <iostream>
#include <list>
#include <deque>
#include <string>
#include <vector>

template <typename Container>
void traverse(Container &con)
{
    for(auto &elem : con)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

void testVector()
{
    std::vector<int> vec1;
    std::vector<int> vec2(10);
    std::vector<int> vec3(3, 5);
    std::vector<int> vec4(vec2.begin(), vec2.end());
    std::vector<int> vec5 {1, 2, 3, 4, 5};

    traverse(vec5);
}

void testlist()
{
    std::list<int> list1;
    std::list<int> list2(10);
    std::list<int> list(3, 5);
    std::list<int> list4(list2.begin(), list2.end());
    std::list<int> list5 {1, 2, 3, 4, 5};

    traverse(list5);
}


void testdeque()
{

    std::deque<int> deque1;
    std::deque<int> deque2(10);
    std::deque<int> deque3(3, 5);
    std::deque<int> deque4(deque2.begin(), deque2.end());
    std::deque<int> deque5 {1, 2, 3, 4, 5};

    traverse(deque5);
}

void testVectorAddr()
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6};

    std::cout << &vec[0] << std::endl;
    std::cout << &*vec.begin() << std::endl;
    std::cout << &vec.at(0) << std::endl;
    std::cout << vec.data() << std::endl;
    std::cout << &vec.front() << std::endl;
}


void InitStringFromVector()
{
    std::vector<char> vec {'s', 'h', 'a', 'b', 'i'};
    std::string s;
    for(auto &elem : vec)
    {
        s += elem;
    }
    std::cout << s << std::endl;
}

void printNine()
{
    std::vector<std::vector<int>> vec;
    for(int i = 1; i <= 9; i++)
    {
        std::vector<int> temp;
        for(int j = 1; j <= i; j++)
        {
            temp.push_back(j * i);
        }
        vec.push_back(temp);
    }

    for(int i = 1; i <= 9; i++)
    {
        for(int j = 1; j <= i; j++)
        {
            std::cout << i << " * " << " = " << j <<  vec[i-1][j-1] << "\t";
        }
        std::cout << std::endl;
    }
}


int main()
{
    testVector();
    testlist();
    testdeque();
    testVectorAddr();

    std::vector<char> vec {'h', 'e', 'l', 'l', 'o'};
    std::string str(vec.data(), vec.size());
    std::cout << str << std::endl;

    InitStringFromVector();

    printNine();
}