#include <iostream>
#include <string>
#include <vector>

std::vector<std::pair<int, int>> adjs = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool canAccess(std::vector<std::string> &diagram, int row, int col)
{
    unsigned count{};
    for (auto &adj : adjs)
    {
        int i = row + adj.first;
        int j = col + adj.second;
        if (i >= 0 && j >= 0)
        {
            if (diagram[i][j] == '@')
            {
                ++count;
            }
        }
    }
    return count < 4;
}

int main()
{
    int count{};
    std::string line{};
    std::vector<std::string> diagram{};
    while (std::getline(std::cin, line))
    {
        diagram.push_back(line);
    }
    while (true)
    {
        bool canRemove{false};
        for (int row{}; row < diagram.size(); ++row)
        {
            for (int col{}; col < diagram[0].size(); ++col)
            {
                if (diagram[row][col] != '@')
                    continue;
                if (canAccess(diagram, row, col))
                {
                    diagram[row][col] = 'x';
                    ++count;
                    canRemove = true;
                }
            }
        }
        if (canRemove == false)
            break;
    }
    std::cout << count << std::endl;
    return 0;
}