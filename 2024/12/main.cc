#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

#define ll long long
#define coor std::pair<int, int>
coor operator+(const coor &lhs, const coor &rhs)
{
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}
const std::vector<coor> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
struct Land
{
    char type;
    std::set<coor> cells;
    Land(char type) : type{type}, cells{} {}
};
bool inBorder(int row, int col, const std::vector<std::string> &map)
{
    int ROWS = map.size();
    int COLS = map[0].size();
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}
void dfs(const std::vector<std::string> &map, std::vector<std::vector<bool>> &visited,
         int row, int col, char land_type, Land &land)
{
    if (!inBorder(row, col, map))
        return;
    if (visited[row][col] || map[row][col] != land_type)
        return;
    visited[row][col] = true;
    land.cells.insert({row, col});
    for (const auto &dir : directions)
    {
        int new_row = row + dir.first;
        int new_col = col + dir.second;
        dfs(map, visited, new_row, new_col, land_type, land);
    }
}
int calConers(const std::set<coor> &cells)
{
    int coners{};
    for (const auto &cell : cells)
    {
        std::vector<coor> diff_neighbours{};
        for (const auto &direction : directions)
        {
            coor temp = cell + direction;
            if (!cells.contains(temp))
                diff_neighbours.push_back(temp);
        }
        switch (diff_neighbours.size())
        {
        case 4:
            coners += 4;
            break;
        case 3:
            coners += 2;
            break;
        case 2:
            if (diff_neighbours[0].first != diff_neighbours[1].first && diff_neighbours[0].second != diff_neighbours[1].second)
                coners += 1;
            break;
        }

        for (const coor &offset : std::vector<coor>{{1, 1}, {-1, -1}, {1, -1}, {-1, 1}})
        {
            coor a = cell + coor{offset.first, 0};
            coor b = cell + coor{0, offset.second};
            if (cells.contains(a) && cells.contains(b) && !cells.contains(cell + offset))
                coners += 1;
        }
    }
    return coners;
}
int calPerimeter(const std::set<coor> &cells)
{
    int perimeter{};
    std::set<coor> visited{};
    for (const auto &cell : cells)
    {
        int row = cell.first, col = cell.second;
        perimeter += 4;
        visited.insert(cell);
        for (const auto &dir : directions)
        {
            coor new_cell = {row + dir.first, col + dir.second};

            if (visited.contains(new_cell))
            {
                perimeter -= 2;
            }
        }
    }
    return perimeter;
}

int main()
{
    std::ifstream file("input");
    while (!file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> garden{};
    while (std::getline(file, line))
    {
        garden.push_back(line);
    }
    size_t m{garden.size()}, n{garden[0].size()};
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
    std::vector<Land> lands{};
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (!visited[i][j])
            {
                char type = garden[i][j];
                Land land = {type};
                dfs(garden, visited, i, j, type, land);
                if (land.cells.size() > 0)
                {
                    lands.push_back(land);
                }
            }
        }
    }
    ll result{};
    ll price{};
    for (const auto &land : lands)
    {
        int perimeter = calPerimeter(land.cells);
        int corners = calConers(land.cells);
        result += perimeter * land.cells.size();
        price += corners * land.cells.size();
    }
    std::cout << "Question 1: " << result << std::endl;
    std::cout << "Question 2: " << price << std::endl;
}