#include <map>
#include <iostream>
#include <string>
#include <utility>

void visitMap(std::map<int, std::string> &map)
{
    for(auto &elem :map)
    {
        std::cout << elem.first << " " << elem.second << " ";
    }
    std::cout << std::endl;
}

void visitMap2(std::map<int, std::string> &map)
{
    for(auto it = map.begin(); it != map.end(); ++it)
    {
        std::cout << it->first << " " << it->second << " ";
    }
    std::cout << std::endl;
}

// 初始化
void testMap()    
{
    std::map<int, std::string> map {
        {1, "Tom"},
        {2, "Jerry"},
        {3, "Panda"},
    };

    visitMap(map);
    //visitMap2(map);

    std::map<int, std::string> map1 {
        std::make_pair(4, "Mickey"),
        std::make_pair(5, "Donald"),
    };

    visitMap(map1);
    
    std::map<int, std::string> map2 {
        std::pair<int, std::string>(6, "juddy"),
        std::pair<int, std::string>(7, "monkey"),
    };

    visitMap(map2);
}

void testMap2()
{
    std::map<int, std::string> m1;

    m1[1] = "Tom";
    m1[2] = "Jerry";

    visitMap(m1);
    
    if(m1.count(1))
    {
        std::cout << "find 1" << std::endl;
    }
    else
    {
        std::cout << "not find 1" << std::endl;
    }

    auto it = m1.find(2);
    if(it != m1.end())
    {
        std::cout << "find 2" << std::endl;
        std::cout << it->first << " " << it->second << std::endl;
    }
    else
    {
        std::cout << "not find 2" << std::endl;
    }
}

void testMapInsert()
{
    std::map<int, std::string> m1;

    m1.insert(std::pair<int, std::string>(3, "Panda"));

    m1.insert(std::make_pair(4, "Mickey"));

    visitMap(m1);
}

int main()
{   
    //testMap2();
    testMapInsert();

    return 0;
}