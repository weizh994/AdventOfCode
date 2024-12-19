#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
// unordered_map<string, bool> memo;
// bool dfs(const string &design, const vector<string> &patterns)
// {
//     if (memo.contains(design))
//         return memo[design];
//     if (design.size().empty())
//         return memo[design] = true;

//     for (const string &pattern : patterns)
//     {
//         if (design.size() >= pattern.size() &&
//             design.substr(0, pattern.size()) == pattern)
//         {
//             if (dfs(design.substr(pattern.size()), patterns))
//                 return memo[design] = true;
//         }
//     }
//     return memo[design] = false;
// }
long long count_builds(size_t pos, const string &design, const vector<string> &patterns, vector<long long> &memo)
{
    if (pos == design.size())
        return 1;
    if (memo[pos] != -1)
        return memo[pos];

    unsigned long long count = 0;

    for (const string &pattern : patterns)
    {
        size_t p_size = pattern.size();
        if (pos + p_size > design.size())
            continue;
        if (design.compare(pos, p_size, pattern) == 0)
        {
            count += count_builds(pos + p_size, design, patterns, memo);
        }
    }

    return memo[pos] = count; // 记录并返回结果
}

int main()
{
    ifstream file{"input"};
    if (!file)
        return -1;
    vector<string> patterns{};
    vector<string> designs{};
    bool isPatterns{true};
    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            isPatterns = false;
            continue;
        }
        if (isPatterns)
        {
            istringstream iss{line};
            string pattern;
            while (getline(iss, pattern, ','))
            {
                if (pattern[0] == ' ')
                    pattern = pattern.substr(1, pattern.size() - 1);
                patterns.push_back(pattern);
            }
        }
        else
        {
            designs.push_back(line);
        }
    }
    int result{};
    unsigned long long total_count{};
    for (const auto &design : designs)
    {
        vector<long long> memo(design.size() + 1, -1);
        long long count = count_builds(0, design, patterns, memo);
        if (count)
            result++;
        total_count += count;
    }
    cout << "Question 1: " << result << endl;
    cout << "Question 2: " << total_count << endl;
    return 0;
}