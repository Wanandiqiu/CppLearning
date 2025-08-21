#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

template <typename T, typename Compare = std::less<T>>
class HeapSort
{
public:
    HeapSort(T *arr, size_t size);

    void heapAdjust(size_t, size_t);

    void sort();

    void print();

private:
    vector<T> _vec;
    Compare _cmp;
};

template <typename T, typename Compare>
void HeapSort<T, Compare>::print()
{
    for (auto &elem : _vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template <typename T, typename Compare>
HeapSort<T, Compare>::HeapSort(T *arr, size_t size):_cmp()
{
    for (int idx = 0; idx < size; idx++)
    {
        _vec.push_back(arr[idx]);
    }

    sort(); // 进行排序
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(size_t length, size_t idx) // 当前堆的大小 当前需要调整的节点索引
{
    // 初始化当当前要调整的节点和左右子树
    size_t temp = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    // 判断子树中最大的节点
    if (left < length && _cmp(_vec[temp], _vec[left]))
        temp = left;
    if (right < length && _cmp(_vec[temp], _vec[right]))
        temp = right;

    if (temp != idx)
    {
        std::swap(_vec[idx], _vec[temp]);
        // 递归调整受影响的子树
        heapAdjust(length, temp);
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort()
{
    int size = _vec.size();

    // 构建大根堆
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        // 从最后一个非叶子节点开始
        heapAdjust(size, i);
    }

    // 提取最大值并重新调整堆
    // 将堆顶元素与最后一个元素交换
    for (int i = size - 1; i >= 0; i--)
    {
        std::swap(_vec[0], _vec[i]);
        heapAdjust(i, 0); // 每次堆大小会减一
    }
}

int main()
{
    int arr[] = {3, 4, 1, 12, 6, 17, 32, 21, 13, 66};

    HeapSort<int, std::greater<int>> q(arr, 10);
    q.print();

    return 0;
}