#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>

using std::deque;
using std::string;
using std::vector;

class Person
{
public:
    Person() = default;

    Person(string name, double score) : _name(name), _score(score)
    {
    }

    string getName() const { return _name; }
    double getScore() const { return _score; }

private:
    string _name;
    double _score;
};

std::ostream & operator<<(std::ostream &os, const Person &p)
{
    os << p.getName() << " " << p.getScore() << std::endl;
    return os;
}

int main()
{
    deque<vector<int>> scores;

    std::cout << "Please grade each contestant" << std::endl;
    // 给5个选手打分
    for (int i = 0; i < 5; i++)
    {
        std::cout << "Grading for player " << i + 1 << std::endl;
        vector<int> temp;
        for (int i = 0; i < 10; i++)
        {
            int number = 0;
            std::cin >> number;
            temp.push_back(number);

            // // 对分数排序
            // std::sort(temp.begin(), temp.end());

            // // 去掉最高分和最低分
            // temp.erase(temp.begin());
            // temp.pop_back();
        }

        // 对分数排序
        std::sort(temp.begin(), temp.end());

        // 去掉最高分和最低分
        temp.erase(temp.begin());
        temp.pop_back();

        scores.push_back(temp);
    }

    std::cout << "------" << std::endl;

    vector<double> average;
    // 如何遍历
    for (const auto &elem : scores)
    {
        int sum = 0;
        for (int score : elem)
        {
            sum += score;
            // std::cout << score << " ";
        }

        double avg = static_cast<double>(sum) / elem.size();
        average.push_back(avg);
        // std::cout << std::endl;
    }

    vector<Person> vec;

    vec.push_back(Person{"xiaowang", average[0]});
    vec.push_back(Person{"xiaosong", average[1]});
    vec.push_back(Person{"xiaozhang", average[2]});
    vec.push_back(Person{"xiaoli", average[3]});
    vec.push_back(Person{"xiaoliu", average[4]});

    for(auto &elem : vec)
    {
        std::cout << elem;
    }
    std::cout << std::endl;

    return 0;
}