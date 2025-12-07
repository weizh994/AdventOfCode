// Tried DFS for part2, but data explode. Get back to method in part 1 and then realize it's DP LOL
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
using ull = unsigned long long;
std::vector<std::string> diagram{};
bool split(std::vector<std::vector<ull>> &timeline, size_t row, size_t col)
{
    if (diagram[row][col] == '.' || diagram[row][col] == '|')
    {
        timeline[row][col] += timeline[row - 1][col];
        diagram[row][col] = '|';
        return false;
    }
    else if (diagram[row][col] == '^')
    {
        // left
        if (col > 0 && (diagram[row][col - 1] == '.' || diagram[row][col - 1] == '|'))
        {

            timeline[row][col - 1] += timeline[row - 1][col];
            diagram[row][col - 1] = '|';
        }
        // right
        if (col < diagram[row].size() - 1 && (diagram[row][col + 1] == '.' || diagram[row][col + 1] == '|'))
        {
            timeline[row][col + 1] += timeline[row - 1][col];
            diagram[row][col + 1] = '|';
        }
        return true;
    }
    return false;
};
void visual()
{
    std::cout << "\033[2J\033[H";
    for (const auto &row : diagram)
    {
        for (const auto &col : row)
            std::cout << col << ' ';
        std::cout << '\n';
    }
    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
};
int main()
{
    std::ifstream file("input");
    if (!file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::string line{};
    while (std::getline(file, line))
    {
        diagram.push_back(line);
    }
    size_t start{};
    for (size_t i{}; i < diagram[0].size(); ++i)
    {
        if (diagram[0][i] == 'S')
        {
            start = i;
            break;
        }
    }
    ull count{}, timelines{};
    std::vector<std::vector<ull>> timeline(diagram.size(), std::vector<ull>(diagram[0].size(), 0));
    timeline[0][start] = 1;
    for (size_t row{1}; row < diagram.size(); ++row)
    {
        if (row == 1)
        {
            if (split(timeline, row, start))
                ++count;
        }
        else
        {
            for (size_t col{}; col < diagram[row].size(); ++col)
            {
                if (diagram[row - 1][col] == '|' && split(timeline, row, col))
                    ++count;
            }
        }
        visual();
    }
    std::cout << "\033[2J\033[H";
    std::cout << count << std::endl;
    for (size_t col = 0; col < timeline.back().size(); ++col)
    {
        timelines += timeline.back()[col];
    }
    std::cout << timelines << std::endl;
    return 0;
}