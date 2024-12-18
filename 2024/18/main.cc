#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
using namespace std;
typedef pair<int, int> pii;
vector<vector<char>> map(71, vector<char>(71, '.'));
vector<pii> directions{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int main()
{
    ifstream file{"input"};
    if (!file)
        return -1;
    string line{};
    vector<pii> bytes{};
    while (getline(file, line))
    {
        int row, col;
        sscanf(line.c_str(), "%d,%d", &row, &col);
        bytes.push_back({row, col});
    }
    for (int i{}; i < 1024; ++i)
    {
        auto [row, col] = bytes[i];
        map[row][col] = '#';
    }
    int tr{70}, tc{70};

    int lst = 1023;
    bool found{true};
    while (found)
    {
        lst++;
        auto [row, col] = bytes[lst];
        map[row][col] = '#';
        found = false;
        queue<pii> q{};
        vector<vector<int>> dist(71, vector<int>(71, INT_MAX));
        vector<vector<pii>> prev_pos(71, vector<pii>(71, {-1, -1}));
        dist[0][0] = 0;
        q.push({0, 0});
        while (!q.empty())
        {
            auto [cr, cc] = q.front();
            q.pop();

            if (cr == 70 && cc == 70)
            {
                found = true;
                break;
            }
            for (auto &dir : directions)
            {
                int nr = cr + dir.first;
                int nc = cc + dir.second;

                if (nr < 0 || nr >= 71 || nc < 0 || nc >= 71)
                    continue;
                else if (map[nr][nc] == '#')
                    continue;
                else if (dist[nr][nc] == INT_MAX)
                {
                    dist[nr][nc] = dist[cr][cc] + 1;
                    prev_pos[nr][nc] = {cr, cc};
                    q.push({nr, nc});
                }
            }
        }
        if (!found)
        {
            cout << "No path found" << endl;
        }
        else
        {
            cout << "Shortest path length: " << dist[70][70] << endl;
            // vector<pair<int, int>> path;
            vector<vector<char>> map_copy(map);
            int pr = tr, pc = tc;
            while (pr != -1 && pc != -1)
            {
                map_copy[pr][pc] = 'O';
                // path.push_back({pr, pc});
                auto [r, c] = prev_pos[pr][pc];
                pr = r;
                pc = c;
            }
            // reverse(path.begin(), path.end());
            for (const auto &row : map_copy)
            {
                for (char c : row)
                    cout << c;
                cout << endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            std::system("clear");
        }
    }
    cout << bytes[lst].first << "," << bytes[lst].second << endl;
    return 0;
}