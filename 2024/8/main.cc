#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>

bool in_bounds(const std::pair<int, int> &antinode, const std::vector<std::string> &map)
{
    return antinode.first >= 0 && antinode.first < map.size() && antinode.second >= 0 && antinode.second < map[0].size();
}

size_t set_h_antinodes(std::vector<std::string> &map, std::unordered_map<char, std::vector<std::pair<size_t, size_t>>> &antannas)
{
    std::set<std::pair<int, int>> antinodes{};
    for (const auto &[antanna, locations] : antannas)
    {
        for (size_t i{}; i < locations.size(); ++i)
        {
            for (size_t j{i + 1}; j < locations.size(); ++j)
            {
                auto antanna1 = locations[i];
                auto antanna2 = locations[j];
                int row_diff = antanna2.first - antanna1.first;
                int col_diff = antanna2.second - antanna1.second;
                std::pair<int, int> antinode1{antanna1};
                std::pair<int, int> antinode2{antanna2};
                while (in_bounds(antinode1, map))
                {
                    antinodes.insert(antinode1);
                    antinode1.first -= row_diff;
                    antinode1.second -= col_diff;
                }
                while (in_bounds(antinode2, map))
                {
                    antinodes.insert(antinode2);
                    antinode2.first += row_diff;
                    antinode2.second += col_diff;
                }
            }
        }
    }
    return antinodes.size();
}
size_t set_antinodes(std::vector<std::string> &map, std::unordered_map<char, std::vector<std::pair<size_t, size_t>>> &antannas)
{
    std::set<std::pair<int, int>> antinodes{};
    for (const auto &[antanna, locations] : antannas)
    {
        for (size_t i{}; i < locations.size(); ++i)
        {
            for (size_t j{i + 1}; j < locations.size(); ++j)
            {
                auto antanna1 = locations[i];
                auto antanna2 = locations[j];
                int row_diff = antanna2.first - antanna1.first;
                int col_diff = antanna2.second - antanna1.second;
                std::pair<int, int> antinode1{antanna1.first - row_diff, antanna1.second - col_diff};
                std::pair<int, int> antinode2{antanna2.first + row_diff, antanna2.second + col_diff};
                if (in_bounds(antinode1, map))
                {
                    antinodes.insert(antinode1);
                }
                if (in_bounds(antinode2, map))
                {
                    antinodes.insert(antinode2);
                }
            }
        }
    }
    return antinodes.size();
}
int main()
{
    std::ifstream file("input");
    if (!file.is_open())
    {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }
    std::vector<std::string> map;
    std::string line;
    while (std::getline(file, line))
    {
        map.push_back(line);
    }
    file.close();

    std::unordered_map<char, std::vector<std::pair<size_t, size_t>>> antannas{};
    for (size_t i{}; i < map.size(); ++i)
    {
        for (size_t j{}; j < map[i].size(); ++j)
        {
            if (map[i][j] != '.')
            {
                antannas[map[i][j]].push_back({i, j});
            }
        }
    }

    std::cout << "Question1: " << set_antinodes(map, antannas) << std::endl;
    std::cout << "Question2: " << set_h_antinodes(map, antannas) << std::endl;
}