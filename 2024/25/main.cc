#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
bool isFit(const string &key, const string &lock)
{
    for (int i{}; i < 5; ++i)
    {
        if ((key[i] - '0') + (lock[i] - '0') > 7)
            return false;
    }
    return true;
}
int main()
{
    ifstream file{"input"};
    if (!file)
        return 1;
    string line;
    vector<string> locks, keys, temp;
    bool isKey{false};
    int no_line{};
    while (getline(file, line))
    {
        if (line.empty())
        {
            no_line = 0;
            temp.clear();
            continue;
        }
        temp.push_back(line);
        ++no_line;
        if (no_line == 7)
        {
            if (temp[0] == "#####" && temp[6] == ".....")
                isKey = false;
            else if (temp[6] == "#####" && temp[0] == ".....")
                isKey = true;
            string temp_str{};
            for (size_t j{}; j < temp[0].size(); ++j)
            {
                int num{};
                for (size_t i{}; i < temp.size(); ++i)
                {
                    if (temp[i][j] == '#')
                        num++;
                }
                temp_str += to_string(num);
            }
            if (isKey)
                keys.push_back(temp_str);
            else
                locks.push_back(temp_str);
        }
    }
    int result{};
    for (const auto &key : keys)
    {
        for (const auto &lock : locks)
        {
            if (isFit(key, lock))
                result++;
        }
    }
    cout << result << endl;
}