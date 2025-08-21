#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>

using std::cout;
using std::endl;
using std::list;
using std::ostream_iterator;

int main()
{
    ostream_iterator<int> osi(cout, " ");

    list<int> lst = {1, 2, 3, 4, 5};

    std::copy(lst.begin(), lst.end(), osi);
    cout << endl;

    return 0;
}