
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <cstdlib>

// 清空控制台
void clearConsole()
{
#ifdef _WIN32
    std::system("cls"); // Windows
#else
    std::system("clear"); // Linux/Unix/macOS
#endif
}
#define pii std::pair<int, int>
std::map<char, std::pair<int, int>> directions{
    {'^', {-1, 0}}, {'v', {1, 0}}, {'>', {0, 1}}, {'<', {0, -1}}};
bool can_move(char order, const std::pair<int, int> &pos, const std::vector<std::string> &map)
{

    int x = pos.first;
    int y = pos.second;
    int xn = x + directions[order].first;
    int yn = y + directions[order].second;

    if (map[x][y] == '#')
        return false;
    if (map[x][y] == '.')
        return true;
    if (order == '<' || order == '>')
        return can_move(order, {xn, yn}, map);
    else
    {
        if (map[x][y] == '[')
        {
            return can_move(order, {xn, yn}, map) && can_move(order, {xn, yn + 1}, map);
        }
        if (map[x][y] == ']')
        {
            return can_move(order, {xn, yn}, map) && can_move(order, {xn, yn - 1}, map);
        }
    }
    return true;
}
void move(char order, std::pair<int, int> &pos, std::vector<std::string> &map)
{
    if (!directions.contains(order))
        return;
    int x = pos.first;
    int y = pos.second;
    int xn = x + directions[order].first;
    int yn = y + directions[order].second;
    int ROWS = map.size();
    int COLS = map[0].size();
    if (xn < 0 || yn < 0 || xn >= ROWS || yn >= COLS)
        return;
    else if (map[xn][yn] == '#')
        return;
    else if (map[xn][yn] == 'O' || ((order == '<' || order == '>') && (map[xn][yn] == ']' || map[xn][yn] == '[')))
    {
        pii new_pos{xn, yn};
        move(order, new_pos, map);
    }
    else if (map[xn][yn] == '[')
    {
        pii new_pos{xn, yn};
        pii new_pos2{xn, yn + 1};
        move(order, new_pos, map);
        move(order, new_pos2, map);
    }
    else if (map[xn][yn] == ']')
    {
        pii new_pos{xn, yn};
        move(order, new_pos, map);
        pii new_pos2{xn, yn - 1};
        move(order, new_pos2, map);
    }
    if (map[xn][yn] == '.')
    {

        char temp = map[x][y];
        map[x][y] = '.';
        if (temp != '#')
            map[xn][yn] = temp;
        pos.first = xn;
        pos.second = yn;
    }
    return;
}
void exec(char order, std::pair<int, int> &pos, std::vector<std::string> &map)
{
    int x = pos.first;
    int y = pos.second;
    int xn = x + directions[order].first;
    int yn = y + directions[order].second;
    if (can_move(order, {xn, yn}, map))
    {
        if (order == '<' || order == '>')
        {
            move(order, pos, map);
        }
        else
        {
            move(order, pos, map);
            if (map[xn][yn] == '[')
            {
                pii pos2{pos.first, pos.second + 1};
                move(order, pos2, map);
            }
            else if (map[xn][yn] == ']')
            {
                pii pos2{pos.first, pos.second - 1};
                move(order, pos2, map);
            }
        }
    }
    else
        return;
}

int main()
{
    std::ifstream file{"input"};
    if (!file)
        return 1;
    std::string line;
    std::vector<std::string> map{};
    std::string order{};
    bool isOrder = false;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            isOrder = true;
            continue;
        }
        if (!isOrder)
            map.push_back(line);
        else
            order += line;
    }
    std::vector<std::string> map1{map};
    int ROWS = map1.size();
    int COLS = map1[0].size();
    std::pair<int, int> robot{};
    for (int i{}; i < ROWS; ++i)
    {
        for (int j{}; j < COLS; ++j)
        {
            if (map1[i][j] == '@')
                robot.first = i, robot.second = j;
        }
    }

    for (size_t i{}; i < order.size(); ++i)
    {
        move(order[i], robot, map1);
    }
    long long result{};
    for (int i{}; i < ROWS; ++i)
    {
        for (int j{}; j < COLS; ++j)
        {
            if (map1[i][j] == 'O')
                result += (100 * i + j);
        }
    }
    std::cout << "Question 1: " << result << std::endl;
    std::vector<std::string> map2{};
    for (int i{}; i < ROWS; ++i)
    {
        std::string new_line{};
        for (int j{}; j < COLS; ++j)
        {
            if (map[i][j] == '#')
                new_line += "##";
            else if (map[i][j] == 'O')
                new_line += "[]";
            else if (map[i][j] == '.')
                new_line += "..";
            else if (map[i][j] == '@')
                new_line += "@.";
            else
                std::cerr << "ERROR: " << map[i][j] << std::endl;
        }
        map2.push_back(new_line);
    }
    ROWS = map2.size();
    COLS = map2[0].size();
    for (int i{}; i < ROWS; ++i)
    {
        for (int j{}; j < COLS; ++j)
        {
            if (map2[i][j] == '@')
                robot.first = i, robot.second = j;
        }
    }
    for (size_t i{}; i < order.size(); ++i)
    {
        exec(order[i], robot, map2);
        // std::this_thread::sleep_for(std::chrono::seconds(0.2));
        // clearConsole();

        // for (const auto &row : map2)
        //     std::cout << row << std::endl;
        // std::cout << std::endl;
    }
    result = 0;
    for (int i{}; i < ROWS; ++i)
    {
        for (int j{}; j < COLS; ++j)
        {
            if (map2[i][j] == '[')
                result += (100 * i + j);
        }
    }
    std::cout << "Question 2: " << result << std::endl;

    return 0;
}