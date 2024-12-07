#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>

#define ll long long

ll concatenate(ll lhs, ll rhs)
{
    std::string l = std::to_string(lhs);
    std::string r = std::to_string(rhs);
    return std::stoll(l + r);
}
bool canHoldTarget(const std::vector<ll> &equation, ll target, size_t index, ll current)
{
    if (index == equation.size())
    {
        return current == target;
    }
    if (current > target)
    {
        return false;
    }

    return (canHoldTarget(equation, target, index + 1, current + equation[index])) ||
           (canHoldTarget(equation, target, index + 1, current * equation[index])) ||
           (canHoldTarget(equation, target, index + 1, concatenate(current, equation[index])));
}

int main()
{
    std::ifstream file("input");
    if (!file.is_open())
    {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }
    std::vector<std::pair<ll, std::vector<ll>>> equations;
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string key, value;
        if (std::getline(ss, key, ':') && std::getline(ss, value))
        {
            std::istringstream ss2(value);
            std::vector<ll> equation;
            ll num;
            while (ss2 >> num)
            {
                equation.push_back(num);
            }
            equations.push_back({std::stoll(key), equation});
        }
    }
    file.close();
    ll answer{};
    for (const auto &equation : equations)
    {
        ll key = equation.first;
        const auto &nums = equation.second;
        if (canHoldTarget(nums, key, 1, nums[0]))
            answer += key;
    }
    std::cout << answer << std::endl;
}