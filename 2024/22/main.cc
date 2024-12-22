#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;

LL mix(const LL lhs, const LL rhs)
{
    return lhs ^ rhs;
}
LL prune(const LL lhs)
{
    return ((lhs % 16777216) + 16777216) % 16777216;
}
LL generate_sec_num(LL num)
{
    num = prune(mix(num, num * 64));
    num = prune(mix(num, floor(num / 32)));
    num = prune(mix(num, num * 2048));
    return num;
}
int main()
{
    fstream file{"input"};
    if (!file)
        return 1;
    LL num{};
    vector<LL> init_sec_nums{};
    while (file >> num)
        init_sec_nums.push_back(num);
    LL result{};
    vector<vector<int>> price(init_sec_nums.size(), vector<int>(2000, -1));
    map<vector<int>, set<int>> diffs{};
    for (int k{}; k < init_sec_nums.size(); ++k)
    {
        LL n = init_sec_nums[k];
        for (int i{}; i < 2000; ++i)
        {
            n = generate_sec_num(n);
            price[k][i] = n % 10;
            if (i >= 4)
            {
                vector<int> diff(4);
                diff[0] = price[k][i - 3] - price[k][i - 4];
                diff[1] = price[k][i - 2] - price[k][i - 3];
                diff[2] = price[k][i - 1] - price[k][i - 2];
                diff[3] = price[k][i] - price[k][i - 1];
                diffs[diff].insert(k);
            }
        }
        result += n;
    }
    cout << "Question 1: " << result << endl;

    vector<LL> bananas{};
    vector<vector<int>> seqs;
    for (const auto &[key, value] : diffs)
    {
        seqs.push_back(key);
    }

    // Sort the keys based on the corresponding set<int> size
    sort(seqs.begin(), seqs.end(),
         [&diffs](const vector<int> &a, const vector<int> &b)
         {
             return diffs[a].size() > diffs[b].size();
         });
    for (int j{}; j < 20; ++j)
    {
        LL banana{};
        for (int k{}; k < price.size(); ++k)
        {
            for (int i{4}; i < price[k].size(); ++i)
            {
                vector<int> diff(4);
                diff[0] = price[k][i - 3] - price[k][i - 4];
                diff[1] = price[k][i - 2] - price[k][i - 3];
                diff[2] = price[k][i - 1] - price[k][i - 2];
                diff[3] = price[k][i] - price[k][i - 1];
                if (diff == seqs[j])
                {
                    banana += price[k][i];
                    break;
                }
            }
        }
        bananas.push_back(banana);
    }
    LL max_banana{};
    for (LL p : bananas)
        max_banana = max(max_banana, p);
    cout << max_banana << endl;
    return 0;
}