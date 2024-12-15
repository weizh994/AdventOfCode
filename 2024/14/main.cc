#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#define pii std::pair<int, int>
#define ll long long
struct Robot
{
    pii pos;
    pii vec;
};

int main()
{
    std::ifstream file{"input"};
    while (!file)
    {
        return 1;
    }
    std::vector<Robot> robots{};
    int MAX_H{103}, MAX_W{101};
    int MID_H = MAX_H / 2, MID_W = MAX_W / 2;
    std::string line;
    while (std::getline(file, line))
    {
        Robot robot{};
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &robot.pos.first, &robot.pos.second, &robot.vec.first, &robot.vec.second);
        robots.push_back(robot);
    }
    ll zone1{}, zone2{}, zone3{}, zone4{};
    for (const auto &robot : robots)
    {
        int x = (((robot.pos.first + (100 * robot.vec.first)) % MAX_W) + MAX_W) % MAX_W;
        int y = (((robot.pos.second + (100 * robot.vec.second)) % MAX_H) + MAX_H) % MAX_H;
        if (x == MID_W || y == MID_H)
            continue;
        if (y < MID_H)
        {
            if (x < MID_W)
                zone1++;
            else
                zone2++;
        }
        else
        {
            if (x < MID_W)
                zone3++;
            else
                zone4++;
        }
    }
    long long answer = zone1 * zone2 * zone3 * zone4;
    std::cout << "Question 1: " << answer << std::endl;

    answer = 0;
    while (true)
    {
        std::map<pii, int> map{};
        answer++;
        bool flag{false};
        for (const auto &robot : robots)
        {
            int x = (((robot.pos.first + (answer * robot.vec.first)) % MAX_W) + MAX_W) % MAX_W;
            int y = (((robot.pos.second + (answer * robot.vec.second)) % MAX_H) + MAX_H) % MAX_H;
            if (map.contains({x, y}))
            {
                flag = true;
                break;
            }
            else
                map[{x, y}]++;
        }
        if (!flag)
            break;
    }
    std::vector<std::vector<char>> map(MAX_H, std::vector<char>(MAX_W, ' '));
    for (const auto &robot : robots)
    {
        int x = (((robot.pos.first + (answer * robot.vec.first)) % MAX_W) + MAX_W) % MAX_W;
        int y = (((robot.pos.second + (answer * robot.vec.second)) % MAX_H) + MAX_H) % MAX_H;
        map[y][x] = '*';
    }
    for (const auto &row : map)
    {
        for (char c : row)
            std::cout << c;
        std::cout << std::endl;
    }
    std::cout << "Question 2: " << answer << std::endl;
    return 0;
}