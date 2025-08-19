#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 定义比较类，重载 operator()
struct Compare {
    bool operator()(int a, int b) const {
        return a > b;  // 降序排序：a > b
    }
};

int main() {
    vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};

    // 将函数对象实例作为第三个参数传给 sort
    Compare cm;
    sort(vec.begin(), vec.end(), cm);

    // 输出结果：9 6 5 4 3 2 1 1
    for (int x : vec) cout << x << " ";
    return 0;
}