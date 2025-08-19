#include <iostream>
#include <vector>

void test()
{
    std::vector<std::vector<int>> vec;

    // vector打印乘法表
    for(int i = 1; i <= 9; ++i)
    {
        std::vector<int> tmp;
        for(int j = 1; j <= i; ++j)
        {
            tmp.push_back(j * i);
        }
        vec.push_back(tmp);
    }

    for(int i = 1; i <= 9; ++i)
    {
        for(int j = 1; j <= i; ++j)
        {
            std::cout << i << " * " << j << " = " << vec[i - 1][j - 1] << "\t";
        }
        std::cout << std::endl;
    }
}


void test1()
{
    
}

int main()
{
    std::printf("Nvidia fuck you!\n");
    test();
    return 0;
}