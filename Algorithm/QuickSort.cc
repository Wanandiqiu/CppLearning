#include <iostream>
#include <vector>

using std::vector;

// 自定义比较规则

template <typename T, typename Compare = std::less<T>>
class MyQsort
{
public:
    MyQsort(T *arr, size_t size, Compare com);

    void quick(int left, int right, Compare &com);

    int partition(int left, int right, Compare &com);

    void print();

private:
    vector<T> _vec;
};

template <typename T, typename Compare>
void MyQsort<T, Compare>::print()
{
    for (auto &elem : _vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// 构造函数
template <typename T, typename Compare>
MyQsort<T, Compare>::MyQsort(T *arr, size_t size, Compare com)
{
    // 初始化 vector 对象
    for (int i = 0; i < size; i++)
    {
        _vec.push_back(arr[i]);
    }

    // 进行快速排序
    quick(0, size - 1, com);
}

// 划分
template <typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right, Compare &com)
{
    int pivot = _vec[left];

    while (left < right)
    {

        // 用自定义的 Compare 进行比较划分
        while (left < right && com(_vec[left], pivot))
            left++;
        if (com(pivot, _vec[left]))
            _vec[right] = _vec[left];

        while (left < right && com(pivot, _vec[right]))
            right--;
        if (com(_vec[right], pivot))
            _vec[left] = _vec[right];
    }

    _vec[left] = pivot;

    return left;
}

template <typename T, typename Compare>
void MyQsort<T, Compare>::quick(int left, int right, Compare &com)
{
    if (left < right)
    {
        int size = _vec.size();
        int part = partition(left, right, com); // 划分

        // part 将一个数组划分，小于part的和大于part的
        quick(left, part - 1, com);
        quick(part + 1, right, com);
    }
}

int main()
{
    int arr[] = {3, 4, 1, 12, 6, 17, 32, 21, 13, 66};

    MyQsort<int> q(arr, 10, std::less<int>());
    q.print();

    return 0;
}