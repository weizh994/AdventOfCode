#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using ull = unsigned long long;
int main()
{
    std::ifstream file("input");
    if (!file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::vector<std::pair<ull, ull>> database{};
    std::string line{};
    while (std::getline(file, line))
    {
        if (line.empty())
            break;
        ull l = std::stoull(line.substr(0, line.find('-')));
        ull r = std::stoull(line.substr(line.find('-') + 1));
        database.push_back({l, r});
    }
    std::sort(database.begin(), database.end());
    size_t idx{};
    for (size_t i{}; i < database.size(); ++i)
    {
        if (database[i].first <= database[idx].second + 1)
        {
            database[idx].second = std::max(database[idx].second, database[i].second);
        }
        else
        {
            ++idx;
            database[idx] = database[i];
        }
    }
    database.resize(idx + 1);
    ull count{};
    while (std::getline(file, line))
    {
        if (line.empty())
            break;
        unsigned long long id{std::stoull(line)};
        auto it = std::upper_bound(database.begin(), database.end(), id, [](ull value, const std::pair<ull, ull> inter)
                                   { return value < inter.first; });
        if (it != database.begin())
            --it;
        if (it->first <= id && id <= it->second)
            ++count;
    }
    file.close();
    std::cout << count << std::endl;
    count = 0;
    for (const auto &ingredient : database)
    {
        count += (ingredient.second - ingredient.first + 1);
    }
    std::cout << count << std::endl;
    return 0;
}