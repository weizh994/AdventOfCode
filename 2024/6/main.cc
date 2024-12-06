#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
enum class Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};
struct Point
{
    int row;
    int col;
    Direction dir;
};
struct PointHash
{
    std::size_t operator()(const Point &p) const
    {
        // 简单哈希: 组合 row, col, dir 的值
        // 可根据实际需求改进哈希函数
        return std::hash<int>()(p.row) ^ (std::hash<int>()(p.col) << 1) ^ (std::hash<int>()((int)p.dir) << 2);
    }
};

struct PointEq
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        return lhs.row == rhs.row && lhs.col == rhs.col && lhs.dir == rhs.dir;
    }
};

bool inLoop(const Point &curr, const std::unordered_set<Point, PointHash, PointEq> &trajs)
{
    return trajs.contains(curr);
}
bool outOfBound(int next_row, int next_col, const std::vector<std::string> &maps)
{
    int max_row = maps.size();
    int max_col = maps[0].size();
    return next_row < 0 || next_row >= max_row || next_col < 0 || next_col >= max_col;
}
bool simulate(const std::pair<int, int> &obstruction, const std::vector<std::string> &maps, Point &p)
{
    std::unordered_set<Point, PointHash, PointEq> trajs{};
    Point curr{p.row, p.col, p.dir};
    int max_row = maps.size();
    int max_col = maps[0].size();
    while (!inLoop(curr, trajs) && curr.row >= 0 && curr.row < max_row && curr.col >= 0 && curr.col < max_col)
    {
        // std::cout << curr.row << " " << curr.col << " " << static_cast<int>(curr.dir) << std::endl;
        trajs.insert(curr);
        switch (curr.dir)
        {
        case Direction::UP:
        {
            int next_row = curr.row - 1;
            int next_col = curr.col;
            if (outOfBound(next_row, next_col, maps))
            {
                return false;
            }
            if (maps[next_row][next_col] == '#' || (next_row == obstruction.first && next_col == obstruction.second))
            {
                curr.dir = Direction::RIGHT;
            }
            else
            {
                curr.row = next_row;
                curr.col = next_col;
            }
            break;
        }
        case Direction::RIGHT:
        {
            int next_row = curr.row;
            int next_col = curr.col + 1;
            if (outOfBound(next_row, next_col, maps))
            {
                return false;
            }
            if (maps[next_row][next_col] == '#' || (next_row == obstruction.first && next_col == obstruction.second))
            {
                curr.dir = Direction::DOWN;
            }
            else
            {
                curr.row = next_row;
                curr.col = next_col;
            }
            break;
        }
        case Direction::DOWN:
        {
            int next_row = curr.row + 1;
            int next_col = curr.col;
            if (outOfBound(next_row, next_col, maps))
            {
                return false;
            }
            if (maps[next_row][next_col] == '#' || (next_row == obstruction.first && next_col == obstruction.second))
            {
                curr.dir = Direction::LEFT;
            }
            else
            {
                curr.row = next_row;
                curr.col = next_col;
            }
            break;
        }
        case Direction::LEFT:
        {
            int next_row = curr.row;
            int next_col = curr.col - 1;
            if (outOfBound(next_row, next_col, maps))
            {
                return false;
            }
            if (maps[next_row][next_col] == '#' || (next_row == obstruction.first && next_col == obstruction.second))
            {
                curr.dir = Direction::UP;
            }
            else
            {
                curr.row = next_row;
                curr.col = next_col;
            }
            break;
        }
        }
    }
    return inLoop(curr, trajs);
}

int main()
{
    std::ifstream file{"input"};
    if (!file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::vector<std::string> maps{};
    std::string line{};
    while (std::getline(file, line))
    {
        maps.push_back(line);
    }
    file.close();
    std::set<std::pair<int, int>> traj{};
    std::pair<int, int> curr{};
    Direction dir{Direction::UP};

    bool start_found = false;
    for (size_t i = 0; i < maps.size() && !start_found; ++i)
    {
        for (size_t j = 0; j < maps[i].size(); ++j)
        {
            if (maps[i][j] == '^')
            {
                curr.first = i;
                curr.second = j;
                traj.insert(curr);
                start_found = true;
                break;
            }
        }
    }

    if (!start_found)
    {
        std::cerr << "No starting point '^' found in the map." << std::endl;
        return 1;
    }
    Point start{curr.first, curr.second, dir};
    int max_row = maps.size();
    int max_col = maps[0].size();

    while (curr.first >= 0 && curr.first < max_row && curr.second >= 0 && curr.second < max_col)
    {
        traj.insert(curr);
        switch (dir)
        {
        case Direction::UP:
        {
            int next_row = curr.first - 1;
            int next_col = curr.second;
            if (maps[next_row][next_col] == '#')
            {
                dir = Direction::RIGHT;
            }
            else
            {
                curr.first = next_row;
                curr.second = next_col;
            }
            break;
        }
        case Direction::RIGHT:
        {
            int next_row = curr.first;
            int next_col = curr.second + 1;
            if (maps[next_row][next_col] == '#')
            {
                dir = Direction::DOWN;
            }
            else
            {
                curr.first = next_row;
                curr.second = next_col;
            }
            break;
        }
        case Direction::DOWN:
        {
            int next_row = curr.first + 1;
            int next_col = curr.second;
            if (maps[next_row][next_col] == '#')
            {
                dir = Direction::LEFT;
            }
            else
            {
                curr.first = next_row;
                curr.second = next_col;
            }
            break;
        }
        case Direction::LEFT:
        {
            int next_row = curr.first;
            int next_col = curr.second - 1;
            if (maps[next_row][next_col] == '#')
            {
                dir = Direction::UP;
            }
            else
            {
                curr.first = next_row;
                curr.second = next_col;
            }
            break;
        }
        }
    }
    std::cout << "Question 1: " << traj.size() << std::endl;
    int answer{};
    for (int i{}; i < max_row; ++i)
    {
        for (int j{}; j < max_col; ++j)
        {
            if (traj.contains({i, j}) and !(i == start.row && j == start.col))
            {
                if (simulate({i, j}, maps, start))
                {
                    answer++;
                }
            }
        }
    }
    std::cout << "Question 2: " << answer << std::endl;
    return 0;
}