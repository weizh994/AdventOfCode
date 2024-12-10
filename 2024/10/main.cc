#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#define ll long long

const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
struct position
{
    int height;
    std::pair<int, int> coord;
};
bool valid(int row, int col, int rows, int cols)
{
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

ll scores(const std::pair<int, int> &trailhead, const std::vector<std::vector<int>> &grid)
{
    position start{0, trailhead};
    int n = int(grid.size());
    int rows = n;
    int cols = int(grid[0].size());
    std::vector<std::vector<bool>> seen(n, std::vector<bool>(n, false));
    std::queue<position> queue;
    seen[trailhead.first][trailhead.second] = true;
    queue.push(start);

    ll answer{};
    while (!queue.empty())
    {
        position curr = queue.front();
        queue.pop();
        int row = curr.coord.first;
        int col = curr.coord.second;
        if (curr.height == 9)
        {
            answer++;
        }
        else
        {
            for (auto &direction : directions)
            {
                int nextRow = row + direction.first, nextCol = col + direction.second;
                if (valid(nextRow, nextCol, rows, cols) && !seen[nextRow][nextCol] && grid[nextRow][nextCol] == curr.height + 1)
                {
                    position next{grid[nextRow][nextCol], {nextRow, nextCol}};
                    seen[nextRow][nextCol] = true;
                    queue.push(next);
                }
            }
        }
    }
    return answer;
}
ll ratings(const std::pair<int, int> &trailhead, const std::vector<std::vector<int>> &grid)
{

    position start{0, trailhead};
    int n = int(grid.size());
    int rows = n;
    int cols = int(grid[0].size());
    std::queue<position> queue;
    queue.push(start);

    ll answer{};
    while (!queue.empty())
    {
        position curr = queue.front();
        queue.pop();
        int row = curr.coord.first;
        int col = curr.coord.second;
        if (curr.height == 9)
        {
            answer++;
        }
        else
        {
            for (auto &direction : directions)
            {
                int nextRow = row + direction.first, nextCol = col + direction.second;
                if (valid(nextRow, nextCol, rows, cols) && grid[nextRow][nextCol] == curr.height + 1)
                {
                    position next{grid[nextRow][nextCol], {nextRow, nextCol}};
                    queue.push(next);
                }
            }
        }
    }
    return answer;
}
int main()
{
    std::ifstream file("input");
    std::string line;
    std::vector<std::vector<int>> maps{};
    while (std::getline(file, line))
    {
        std::vector<int> row{};
        for (size_t i{}; i < line.size(); ++i)
            row.push_back(line[i] - '0');
        maps.push_back(row);
    }
    // find 0
    std::set<std::pair<int, int>> trailheads{};
    for (size_t i{}; i < maps.size(); ++i)
    {
        for (size_t j{}; j < maps[i].size(); ++j)
        {
            if (maps[i][j] == 0)
                trailheads.insert({i, j});
        }
    }
    ll answer{};
    for (const auto &trailhead : trailheads)
    {
        answer += scores(trailhead, maps);
    }
    std::cout << "Question1 : " << answer << std::endl;
    answer = 0;
    for (const auto &trailhead : trailheads)
    {
        answer += ratings(trailhead, maps);
    }
    std::cout << "Question2 : " << answer << std::endl;
}