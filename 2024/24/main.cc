#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
map<string, int> cache{};
map<string, tuple<string, string, string>> orders{};
int getValue(const string &operand)
{
    if (cache.contains(operand))
        return cache.at(operand);
    else
    {
        string target = operand;
        const auto &[operand1, op, operand2] = orders[operand];
        int value1 = getValue(operand1);
        int value2 = getValue(operand2);

        if (op == "AND")
        {
            cache[target] = value1 & value2;
        }
        else if (op == "OR")
        {
            cache[target] = value1 | value2;
        }
        else if (op == "XOR")
        {
            cache[target] = value1 ^ value2;
        }
        return cache[target];
    }
}
int main()
{
    ifstream file{"input"};
    if (!file)
        return 1;
    string line{};
    bool isCache{true};
    unsigned long long x{}, y{};
    while (getline(file, line))
    {
        if (line.empty())
        {
            isCache = false;
            continue;
        }
        if (isCache)
        {
            size_t colonPos = line.find(':');
            if (colonPos != string::npos)
            {
                string r = line.substr(0, colonPos);
                int d = stoi(line.substr(colonPos + 1));
                cache[r] = d;
                if (r[0] == 'x')
                {
                    x = x * 2 + d;
                }
                else if (r[0] == 'y')
                {
                    y = y * 2 + d;
                }
            }
        }
        else
        {
            istringstream iss(line);
            string operand1, op, operand2, arrow, target;
            iss >> operand1 >> op >> operand2 >> arrow >> target;
            orders[target] = {operand1, op, operand2};
        }
    }
    map<int, int> z{};
    unsigned long long correct_z{x + y};
    cout << x << '+' << y << '=' << x + y << endl;
    for (const auto &[target, order] : orders)
    {
        if (target[0] == 'z')
        {
            int loc = stoi(target.substr(1, target.size() - 1));
            z[loc] = getValue(target);
        }
    }
    unsigned long long result{};
    for (int i = z.size() - 1; i >= 0; --i)
    {
        result = result * 2 + z[i];
    }
    cout << result << endl;
    return 0;
}