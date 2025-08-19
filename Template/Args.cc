#include <iostream>

template <typename ...Args>
auto add(Args ...args)
{
    // return (... + args);
    return (args + ...);
}

template <typename ...Args>
auto sub(Args ...args)
{
    return (0 - ... - args);    // 二元折叠  
}

int main()
{
    int && ref = 10;

    std::cout << add(1, 2, 3, 4, 5) << std::endl;
    std::cout << add(1.1, 2.2, 3.3, 4.4, 5.5) << std::endl;

    std::cout << sub(1, 2, 3, 4, 5) << std::endl;

    return 0;
}