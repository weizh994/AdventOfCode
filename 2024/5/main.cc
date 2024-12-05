#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <regex>
#include <algorithm>
#include <utility>
#include <set>
#include <unordered_map>
#include <unordered_set>
void sortUpdate(std::vector<int> &update, const std::map<int, std::vector<int>> &rules)
{
    // 构建节点集合
    std::unordered_set<int> unique_elements(update.begin(), update.end());

    // 构建有向图
    std::unordered_map<int, std::vector<int>> adj; // 邻接表
    std::unordered_map<int, int> in_degree;        // 入度表

    // 初始化入度为 0
    for (int elem : unique_elements)
    {
        in_degree[elem] = 0;
    }

    // 添加边和更新入度
    for (const auto &rule : rules)
    {
        int key = rule.first;
        for (int value : rule.second)
        {
            if (unique_elements.count(value))
            {
                adj[key].push_back(value);
                in_degree[value]++;
            }
        }
        // 确保键也在入度表中
        if (!in_degree.count(key))
        {
            in_degree[key] = 0;
        }
    }

    // 拓扑排序（Kahn 算法）
    std::queue<int> zero_in_degree;

    // 初始化零入度队列
    for (const auto &pair : in_degree)
    {
        if (pair.second == 0)
        {
            zero_in_degree.push(pair.first);
        }
    }

    std::vector<int> sorted_elements;

    while (!zero_in_degree.empty())
    {
        int u = zero_in_degree.front();
        zero_in_degree.pop();
        sorted_elements.push_back(u);

        for (int v : adj[u])
        {
            in_degree[v]--;
            if (in_degree[v] == 0)
            {
                zero_in_degree.push(v);
            }
        }
    }

    // 检测环路
    if (sorted_elements.size() != in_degree.size())
    {
        std::cerr << "错误：规则中存在循环，无法进行拓扑排序。" << std::endl;
        return;
    }

    // 创建元素在拓扑排序中的位置映射
    std::unordered_map<int, int> element_order;
    for (size_t i = 0; i < sorted_elements.size(); ++i)
    {
        element_order[sorted_elements[i]] = static_cast<int>(i);
    }

    // 创建辅助数组，包含元素值和原始索引
    std::vector<std::pair<int, int>> update_with_index;
    for (size_t i = 0; i < update.size(); ++i)
    {
        update_with_index.emplace_back(update[i], static_cast<int>(i));
    }

    // 自定义排序函数
    std::stable_sort(update_with_index.begin(), update_with_index.end(), [&element_order](const std::pair<int, int> &a, const std::pair<int, int> &b)
                     {
        auto it_a = element_order.find(a.first);
        auto it_b = element_order.find(b.first);
        if (it_a != element_order.end() && it_b != element_order.end()) {
            // 两个元素都在规则中，按拓扑排序的位置比较
            return it_a->second < it_b->second;
        } else if (it_a != element_order.end()) {
            // 只有 a 在规则中，a 优先
            return true;
        } else if (it_b != element_order.end()) {
            // 只有 b 在规则中，b 优先
            return false;
        } else {
            // 两个元素都不在规则中，按原始索引顺序排序
            return a.second < b.second;
        } });

    // 更新排序后的 update 数组
    for (size_t i = 0; i < update.size(); ++i)
    {
        update[i] = update_with_index[i].first;
    }
}
int main()
{
    std::ifstream file("input");
    if (!file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::vector<std::vector<int>> updates{};
    std::map<int, std::vector<int>> rules{};

    std::string line;
    bool isUpperPart = true; // 用于区分上半部分和下半部分

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            // 遇到空行，表示切换到下半部分
            isUpperPart = false;
            continue;
        }

        if (isUpperPart)
        {
            // 处理上半部分，格式为 "key|value"
            std::istringstream ss(line);
            std::string keyStr, valueStr;

            if (std::getline(ss, keyStr, '|') && std::getline(ss, valueStr))
            {
                int key = std::stoi(keyStr);
                int value = std::stoi(valueStr);
                rules[key].push_back(value);
            }
        }
        else
        {
            // 处理下半部分，格式为 "value1,value2,..."
            std::vector<int> row;
            std::istringstream ss(line);
            std::string numStr;

            while (std::getline(ss, numStr, ','))
            {
                row.push_back(std::stoi(numStr));
            }

            updates.push_back(row);
        }
    }
    file.close();
    std::vector<std::vector<int>> correct_updates{};
    std::vector<std::vector<int>> incorrect_updates{};
    for (auto &update : updates)
    {
        bool correct = true;
        for (size_t i{}; i < update.size(); ++i)
        {
            for (size_t j{}; j < i; ++j)
            {
                if (std::find(rules[update[i]].begin(), rules[update[i]].end(), update[j]) != rules[update[i]].end())
                {
                    correct = false;
                    break;
                }
            }
            if (!correct)
            {
                break;
            }
        }
        if (correct)
        {
            correct_updates.push_back(update);
        }
        else
        {
            incorrect_updates.push_back(update);
        }
    }
    int answer{};
    for (const auto &update : correct_updates)
    {
        answer += update[update.size() / 2];
    }
    std::cout << "Question1: " << answer << std::endl;
    answer = 0;
    for (auto &update : incorrect_updates)
    {
        sortUpdate(update, rules);
    }
    for (const auto &update : incorrect_updates)
    {
        answer += update[update.size() / 2];
    }
    std::cout << "Question2: " << answer << std::endl;
    return 0;
}