#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;
const vector<pair<int, int>> directions = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
// Dijkstra
pair<int, int> findLowestCostPath(const vector<string> &grid,
                                  tuple<int, int, int> start,
                                  pair<int, int> end)
{
    int n = grid.size();
    int m = grid[0].size();

    // 花费数组，三维：dist[x][y][d] 表示到 (x, y) 且面向 d 的最低花费
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(4, INT_MAX)));

    // 优先队列：存储 (总花费, 当前行, 当前列, 当前方向)
    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>> pq;

    // 初始化起点
    auto [x, y, dir] = start;
    dist[x][y][dir] = 0;
    pq.emplace(0, x, y, dir);
    while (!pq.empty())
    {
        auto [cost, x, y, dir] = pq.top();
        pq.pop();

        // 如果到达终点，返回当前最低花费
        if (x == end.first && y == end.second)
        {
            return {cost, dir};
        }

        // 如果当前花费大于记录的最小花费，跳过
        if (cost > dist[x][y][dir])
        {
            continue;
        }

        // 遍历所有邻居
        for (int newDir = 0; newDir < 4; ++newDir)
        {
            int newX = x + directions[newDir].first;
            int newY = y + directions[newDir].second;

            // 检查是否越界或遇到障碍物
            if (newX < 0 || newX >= n || newY < 0 || newY >= m || grid[newX][newY] == '#')
            {
                continue;
            }

            // 计算新花费
            int turnCost = (newDir == dir) ? 0 : 1000; // 转弯代价
            int newCost = cost + 1 + turnCost;         // 总花费

            // 如果找到更优的花费路径，更新并加入队列
            if (newCost < dist[newX][newY][newDir])
            {
                dist[newX][newY][newDir] = newCost;
                pq.emplace(newCost, newX, newY, newDir);
            }
        }
    }

    // 如果终点不可达，返回 -1
    return {-1, -1};
}

int main()
{
    ifstream file{"input"};
    if (!file)
        return 1;
    string line{};
    vector<string> map{};
    while (getline(file, line))
    {
        map.push_back(line);
    }

    pair<int, int> start, end;
    for (int i{}; i < map.size(); ++i)
    {
        for (int j{}; j < map[0].size(); ++j)
        {
            if (map[i][j] == 'S')
                start.first = i, start.second = j;
            if (map[i][j] == 'E')
                end.first = i, end.second = j;
        }
    }
    auto [cost, dir] = findLowestCostPath(map, {start.first, start.second, 3}, end);
    cout << cost << endl;
    set<pair<int, int>> seats{};
    for (int i{}; i < map.size(); ++i)
    {
        for (int j{}; j < map[0].size(); ++j)
        {
            auto [curr_cost, dir] = findLowestCostPath(map, {start.first, start.second, 3}, {i, j});
            if (curr_cost == -1)
                continue;
            else if (curr_cost + findLowestCostPath(map, {i, j, dir}, end).first == cost)
                seats.insert({i, j});
        }
    }
    cout << seats.size() << endl;
    return 0;
}