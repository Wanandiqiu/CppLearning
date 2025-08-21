#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::cout << "please input some number : " << std::endl;

    std::vector<int> vec;

    std::copy(
        std::istream_iterator<int>(std::cin),  // 输入开始
        std::istream_iterator<int>(),  // 输入结束
        std::back_inserter(vec)
    );

    std::cout << " ----- " << std::endl;

    for(auto &elem : vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
