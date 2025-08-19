#include <iostream>
#include <string>
#include <deque>
#include <fstream>
#include <sstream>
#include <list>


using std::list;
using std::istringstream;
using std::ifstream;
using std::string;
using std::deque;


void test()
{
    string line;
    string word;
    deque<string> deq;

    while(getline(std::cin, line))
    {
        istringstream iss(line);
        
        while(iss >> word)
        {
            deq.push_back(word);
        }
    }

    for(auto it = deq.begin(); it != deq.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void test1()
{
    std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    std::deque<int> odd;    // 奇数
    std::deque<int> even;   // 偶数

    for(auto &elem : li)
    {
        if(elem % 2 == 0)
        {
            even.push_back(elem);
        }
        else odd.push_back(elem);
    }

    for(auto &elem : odd) 
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    for(auto &elem : even) 
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}


int main()
{
    test1();

    return 0;
}