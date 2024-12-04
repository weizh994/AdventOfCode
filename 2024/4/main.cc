#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

bool right_check(const std::vector<std::vector<char>> &maps, const std::pair<int, int> &p)
{
    int row = p.first;
    int col = p.second;
    if (col + 3 < maps[0].size())
    {
        if (maps[row][col] == 'X' && maps[row][col + 1] == 'M' && maps[row][col + 2] == 'A' && maps[row][col + 3] == 'S')
        {
            return true;
        }
    }
    return false;
}
bool left_check(const std::vector<std::vector<char>> &maps, const std::pair<int, int> &p)
{
    int row = p.first;
    int col = p.second;
    if (col - 3 >= 0)
    {
        if (maps[row][col] == 'X' && maps[row][col - 1] == 'M' && maps[row][col - 2] == 'A' && maps[row][col - 3] == 'S')
        {
            return true;
        }
    }
    return false;
}
bool up_check(const std::vector<std::vector<char>> &maps, const std::pair<int, int> &p)
{
    int row = p.first;
    int col = p.second;
    if (row - 3 >= 0)
    {
        if (maps[row][col] == 'X' && maps[row - 1][col] == 'M' && maps[row - 2][col] == 'A' && maps[row - 3][col] == 'S')
        {
            return true;
        }
    }
    return false;
}
bool down_check(const std::vector<std::vector<char>> &maps, const std::pair<int, int> &p)
{
    int row = p.first;
    int col = p.second;
    if (row + 3 < maps.size())
    {
        if (maps[row][col] == 'X' && maps[row + 1][col] == 'M' && maps[row + 2][col] == 'A' && maps[row + 3][col] == 'S')
        {
            return true;
        }
    }
    return false;
}
bool up_right_check(const std::vector<std::vector<char>> &maps, const std::pair<int, int> &p)
{
    int row = p.first;
    int col = p.second;
    if (row - 3 >= 0 && col + 3 < maps[0].size())
    {
        if (maps[row][col] == 'X' && maps[row - 1][col + 1] == 'M' && maps[row - 2][col + 2] == 'A' && maps[row - 3][col + 3] == 'S')
        {
            return true;
        }
    }
    return false;
}
bool up_left_check(const std::vector<std::vector<char>> &maps, const std::pair<int, int> &p)
{
    int row = p.first;
    int col = p.second;
    if (row - 3 >= 0 && col - 3 >= 0)
    {
        if (maps[row][col] == 'X' && maps[row - 1][col - 1] == 'M' && maps[row - 2][col - 2] == 'A' && maps[row - 3][col - 3] == 'S')
        {
            return true;
        }
    }
    return false;
}
bool down_right_check(const std::vector<std::vector<char>> &maps, const std::pair<int, int> &p)
{
    int row = p.first;
    int col = p.second;
    if (row + 3 < maps.size() && col + 3 < maps[0].size())
    {
        if (maps[row][col] == 'X' && maps[row + 1][col + 1] == 'M' && maps[row + 2][col + 2] == 'A' && maps[row + 3][col + 3] == 'S')
        {
            return true;
        }
    }
    return false;
}
bool down_left_check(const std::vector<std::vector<char>> &maps, const std::pair<int, int> &p)
{
    int row = p.first;
    int col = p.second;
    if (row + 3 < maps.size() && col - 3 >= 0)
    {
        if (maps[row][col] == 'X' && maps[row + 1][col - 1] == 'M' && maps[row + 2][col - 2] == 'A' && maps[row + 3][col - 3] == 'S')
        {
            return true;
        }
    }
    return false;
}

bool x_chect(const std::vector<std::vector<char>> &maps, const std::pair<int, int> &p)
{
    int row = p.first;
    int col = p.second;
    if (row - 1 >= 0 && row + 1 < maps.size() && col - 1 >= 0 && col + 1 < maps[0].size())
    {
        /*
        M.S
        .A.
        M.S
        */
        if (maps[row][col] == 'A' && maps[row - 1][col + 1] == 'S' && maps[row + 1][col + 1] == 'S' && maps[row - 1][col - 1] == 'M' && maps[row + 1][col - 1] == 'M')
        {
            return true;
        }
        /*
        M.M
        .A.
        S.S
        */
        else if (maps[row][col] == 'A' && maps[row - 1][col + 1] == 'M' && maps[row + 1][col + 1] == 'S' && maps[row - 1][col - 1] == 'M' && maps[row + 1][col - 1] == 'S')
        {
            return true;
        }
        /*
         S.M
         .A.
         S.M
        */
        else if (maps[row][col] == 'A' && maps[row - 1][col + 1] == 'M' && maps[row + 1][col + 1] == 'M' && maps[row - 1][col - 1] == 'S' && maps[row + 1][col - 1] == 'S')
        {
            return true;
        }
        /*
        S.S
        .A.
        M.M
        */
        else if (maps[row][col] == 'A' && maps[row - 1][col + 1] == 'S' && maps[row + 1][col + 1] == 'M' && maps[row - 1][col - 1] == 'S' && maps[row + 1][col - 1] == 'M')
        {
            return true;
        }
    }
    return false;
}

int main()
{
    std::ifstream file("input");
    if (!file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::vector<std::vector<char>> maps{};
    std::string line{};
    while (std::getline(file, line))
    {
        std::vector<char> map{};
        for (const char &c : line)
        {
            map.push_back(c);
        }
        maps.push_back(map);
    }
    file.close(); // 关闭文件
    std::set<std::pair<int, int>> x_place{};
    std::set<std::pair<int, int>> a_place{};
    for (int i{}; i < maps.size(); ++i)
    {
        for (int j{}; j < maps[i].size(); ++j)
        {
            if (maps[i][j] == 'X') // For Question 1
            {
                x_place.insert({i, j});
            }
            if (maps[i][j] == 'A') // For Question 2
            {
                a_place.insert({i, j});
            }
        }
    }
    int answer{};
    for (const auto &p : x_place)
    {
        std::cout << p.first << " " << p.second << std::endl;
        // right check
        if (right_check(maps, p))
            answer++;
        // left check
        if (left_check(maps, p))
            answer++;
        // up check
        if (up_check(maps, p))
            answer++;
        // down check
        if (down_check(maps, p))
            answer++;
        // up-right check
        if (up_right_check(maps, p))
            answer++;
        // up-left check
        if (up_left_check(maps, p))
            answer++;
        // down-right check
        if (down_right_check(maps, p))
            answer++;
        // down-left check
        if (down_left_check(maps, p))
            answer++;
    }
    std::cout << "Question 1: " << answer << std::endl;
    answer = 0;
    for (const auto &p : a_place)
    {
        if (x_chect(maps, p))
        {
            answer++;
        }
    }
    std::cout << "Question 2: " << answer << std::endl;
    return 0;
}