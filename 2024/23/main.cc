#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
using namespace std;
unordered_map<string, unordered_set<string>> graph{};
bool isClique(const vector<string> &nodes)
{
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        for (size_t j = i + 1; j < nodes.size(); ++j)
        {
            if (!graph.at(nodes[i]).contains(nodes[j]))
            {
                return false;
            }
        }
    }
    return true;
}
void findMaximumClique(vector<string> &currentClique, unordered_set<string> &remainingNodes,
                       vector<string> &maxClique)
{
    if (remainingNodes.empty())
    {
        // 如果剩余节点为空，检查当前团是否是最大团
        if (currentClique.size() > maxClique.size())
        {
            maxClique = currentClique;
        }
        return;
    }
    // 遍历剩余节点
    for (auto it = remainingNodes.begin(); it != remainingNodes.end();)
    {
        string node = *it;
        it = remainingNodes.erase(it); // 移除当前节点

        // 尝试加入当前节点到团
        currentClique.push_back(node);

        // 更新剩余节点集合：保留与当前团中的所有节点直接相连的节点
        unordered_set<string> nextNodes;
        for (const string &neighbor : remainingNodes)
        {
            if (isClique({neighbor, node}))
            {
                nextNodes.insert(neighbor);
            }
        }

        // 递归搜索更大的团
        findMaximumClique(currentClique, nextNodes, maxClique);

        // 回溯
        currentClique.pop_back();
    }
}

int main()
{
    ifstream file{"input"};
    if (!file)
        return 1;
    string line;
    vector<string> connections;
    while (getline(file, line))
        connections.push_back(line);
    for (const auto &connection : connections)
    {
        stringstream ss(connection);
        string a, b;
        getline(ss, a, '-');
        getline(ss, b, '-');
        graph[a].insert(b);
        graph[b].insert(a);
    }
    vector<vector<string>> triangles;
    for (const auto &[a, neighbors] : graph)
    {
        for (const auto &b : neighbors)
        {
            if (a >= b)
                continue;
            for (const auto &c : graph.at(b))
            {
                if (c > b && neighbors.contains(c))
                {
                    triangles.push_back({a, b, c});
                }
            }
        }
    }
    int result{};
    for (const auto &link : triangles)
    {
        if (link[0][0] == 't' || link[1][0] == 't' || link[2][0] == 't')
            result++;
    }
    cout << "Question 1: " << result << endl;
    vector<string> maxClique;
    unordered_set<string> remainingNodes;
    for (const auto &node : graph)
    {
        remainingNodes.insert(node.first);
    }

    vector<string> currentClique;
    findMaximumClique(currentClique, remainingNodes, maxClique);
    sort(maxClique.begin(), maxClique.end());
    for (size_t i{}; i < maxClique.size(); ++i)
    {
        if (i == 0)
            cout << "Question 2: " << maxClique[i];
        else
            cout << ',' << maxClique[i];
    }
    cout << endl;
    return 0;
}