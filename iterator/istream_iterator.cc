#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

void test()
{
    std::cout << "please input some number" << std::endl;

    std::istream_iterator<int> start(std::cin);     // 创建输入流迭代器，绑定到 std::cin

    std::istream_iterator<int> end;                // 默认构造函数创建一个结束迭代器

    std::vector<int> vec(start, end);              // 使用迭代器区间构造 vector

    std::cout << "vec contains: ";
    for (auto &elem : vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

void test1()
{
    // 使用 std::copy 将输入复制到容器
    std::cout << "please input some number" << std::endl;

    std::vector<int> numbers;

    // 使用 back_inserter 适配器，自动在 vector 末尾添加元素
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(numbers));

    std::cout << "共读取了 " << numbers.size() << " 个数字: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

void test2()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 创建一个输出流迭代器
    // - 绑定到 std::cout
    // - 每次输出后添加一个空格 " " 作为分隔符
    std::ostream_iterator<int> output_iter(std::cout, " ");

    // 使用 std::copy 将 vector 中的所有元素复制到输出迭代器
    // 这相当于对每个元素执行: *output_iter = element; ++output_iter;
    std::copy(numbers.begin(), numbers.end(), output_iter);

    // 注意：std::copy 不会为最后一个元素之后添加分隔符
    // 通常需要手动换行
    std::cout << std::endl;
}

int main()
{

    return 0;
}