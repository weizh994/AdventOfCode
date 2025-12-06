#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
template <typename T>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>> &a)
{
    if (a.empty())
        return {};

    size_t n = a.size();    // row
    size_t m = a[0].size(); // col

    std::vector<std::vector<T>> b(m, std::vector<T>(n));

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            b[j][i] = a[i][j];
        }
    }
    return b;
}
using ull = unsigned long long;
int main()
{
    std::ifstream file("input");
    if (!file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::vector<std::string> rawWorksheets{};
    std::string line{};
    while (std::getline(file, line))
    {
        rawWorksheets.push_back(line);
    }

    std::vector<std::vector<ull>> worksheets{};
    for (size_t i{}; i < rawWorksheets.size() - 1; ++i)
    {
        std::stringstream ss{rawWorksheets[i]};
        worksheets.push_back({std::istream_iterator<ull>(ss), {}});
    }
    std::vector<char> charas{};
    for (char c : rawWorksheets[rawWorksheets.size() - 1])
    {
        if (c == '*' || c == '+')
            charas.push_back(c);
    }
    ull sum{};
    auto worksheetsT{transpose(worksheets)};

    if (charas.size() != worksheetsT.size())
        return 1;
    for (size_t i{}; i < worksheetsT.size(); ++i)
    {
        if (charas[i] == '*')
        {
            sum += std::accumulate(worksheetsT[i].begin(), worksheetsT[i].end(), 1ULL, std::multiplies<>());
        }
        else if (charas[i] == '+')
        {
            sum += std::accumulate(worksheetsT[i].begin(), worksheetsT[i].end(), 0);
        }
    }
    std::cout << sum << std::endl;

    sum = 0;
    std::vector<std::vector<char>> newWorksheets;
    for (size_t i = 0; i < rawWorksheets.size() - 1; ++i)
    {
        newWorksheets.push_back(std::vector<char>(rawWorksheets[i].begin(), rawWorksheets[i].end()));
    }
    auto newWorksheetsT{transpose(newWorksheets)};
    newWorksheetsT.push_back(std::vector<char>(newWorksheetsT[0].size(), ' ')); // For last cal
    std::string gap{};
    gap.reserve(newWorksheetsT[0].size());
    while (gap.size() < newWorksheetsT[0].size())
    {
        gap += ' ';
    }
    size_t idx{};
    ull res = charas[idx] == '*' ? 1 : 0;
    for (auto &s : newWorksheetsT)
    {
        std::string str{s.begin(), s.end()};
        if (str == gap)
        {
            ++idx;
            sum += res;
            res = charas[idx] == '*' ? 1 : 0;
        }
        else
        {
            if (charas[idx] == '*')
            {
                res *= std::stoull(str);
            }
            else if (charas[idx] == '+')
            {
                res += std::stoull(str);
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}