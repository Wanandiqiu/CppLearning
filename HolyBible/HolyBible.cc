#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using std::string;
using std::unordered_map;

class Dictionary
{
public:
    Dictionary() = default;
    ~Dictionary() = default;

    void read(const std::string &filename);
    void store(const std::string &filename);

private:
    string cleanWord(const std::string &word);
    unordered_map<string, int> _dict;
};

string Dictionary::cleanWord(const std::string &word)
{
    string cleaned;
    for (char c : word)
    {
        if (std::isalpha(c))
        {
            cleaned += std::tolower(c);
        }
    }
    return cleaned;
}

void Dictionary::read(const std::string &filename)
{
    std::ifstream ifs;
    ifs.open(filename);
    if (!ifs)
    {
        std::cerr << "file not exist!" << std::endl;
        return;
    }

    string line;
    while (getline(ifs, line))
    {
        std::istringstream iss(line);
        string word;
        while (iss >> word)
        {
            string cleaned = cleanWord(word);
            if (!cleaned.empty())
            {
                _dict[cleaned]++;
            }
        }
    }

    ifs.close();
}

void Dictionary::store(const std::string &filename)
{
    std::ofstream ofs;
    ofs.open(filename);
    if (!ofs)
    {
        std::cerr << "file not exist!" << std::endl;
        return;
    }

    // 按词频排序
    std::vector<std::pair<std::string, int>> sorted(_dict.begin(), _dict.end());
    std::sort(sorted.begin(), sorted.end(),
              [](const auto &a, const auto &b)
              { return a.second < b.second; });

    for (const auto &[word, count] : sorted)
    {
        ofs << word << " " << count << std::endl;
    }

    ofs.close();
}

int main()
{
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");

    dict.store("frequency.txt");

    return 0;
}