#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

std::map<std::string,std::vector<std::string>> adj{};
int count{};
void dfs(const std::string& curr,
    const std::string& end,
    std::set<std::string>& on_path)
{
    if(curr == end)
    {
        ++count;
        return;
    }
    if(!adj.contains(curr))return;
    for(const auto& nxt : adj[curr])
    {
        if(on_path.contains(nxt))continue;
        
        on_path.insert(nxt);

        dfs(nxt, end,on_path);

        on_path.erase(nxt);
    }
};
int main()
{
    std::string line{};
    while(std::getline(std::cin,line))
    {
        if(line.empty())break;
        std::istringstream ss{line.substr(line.find(':')+2)};
        std::string temp{};
        while (std::getline(ss,temp,' ')) {
            if(temp.empty())break;
            adj[line.substr(0,line.find(':'))].push_back(temp); 
        }
    }
    std::set<std::string> on_path = {"svr"};

    dfs("fft", "dac",  on_path);
    std::cout<<count<<std::endl;

    // part 2
    std::map<std::string, int> indeg;

    for (const auto& [u, vec] : adj) {
        if (!indeg.contains(u)) indeg[u] = 0;
        for (const auto& v : vec) {
            if (!indeg.contains(v)) indeg[v] = 0;
        }
    }

    for (const auto& [u, vec] : adj) {
        for (const auto& v : vec) {
            ++indeg[v];
        }
    }
    return 0;
}
