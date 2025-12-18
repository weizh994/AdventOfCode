#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <jansson.h>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <set>
long distance(const std::array<long, 3>& a, const std::array<long,3>& b)
{
    return  std::pow(a.at(0)-b.at(0),2) +
    std::pow(a.at(1)-b.at(1),2) +
    std::pow(a.at(2)-b.at(2),2);
};
struct UnionFind{
    std::vector<size_t> parent,rank;
    size_t comp;
    UnionFind(size_t n):parent(n,0),rank(n,0),comp(n){}
    size_t find(size_t x)
    {
        return  parent[x]==x ? x : (parent[x] = find(parent[x]));
    }
    bool unite(size_t a, size_t b)
    {
        a = find(a);
        b = find(b);
        if(a!=b)
        {
            if(rank[a]<rank[b])std::swap(a,b);
            parent[b] = a;
            if(rank[a]==rank[b])++rank[a];
            --comp;
            return true;
        }
        return false;
    }
};
struct Edge { long d; size_t u, v; };
int main()
{
    std::string line{};
    std::vector<std::array<long,3>> boxes{};
    while(std::getline(std::cin,line))
    {
        std::istringstream ss{line};
        std::string a{};
        std::array<long,3> box{};
        size_t idx{};
        while(std::getline(ss,a,','))
        {
            box.at(idx++) = std::stol(a);    
        }
        boxes.push_back(std::move(box));
    }
    size_t count{};
    long long coor{};
    size_t result{};
    std::map<long long,std::vector<std::pair<size_t,size_t>>> edges{};
    for (size_t i = 0; i < boxes.size(); ++i)
    {
        for (size_t j = i + 1; j < boxes.size(); ++j)
        {
            edges[distance(boxes[i], boxes[j])].push_back({i, j});
        }
    }

    std::vector<std::set<size_t>> circuits(boxes.size());
    for (size_t i = 0; i < boxes.size(); ++i) {
        circuits[i].insert(i);
    }
    for(auto it= edges.begin();it!=edges.end();++it)
    {
        for(const auto& edge:it->second)
        {
            if(count == 10)
            {
                std::vector<std::set<size_t>> copy_circuits{circuits};
                std::sort(copy_circuits.begin(),copy_circuits.end(),[](const std::set<size_t>& a, const std::set<size_t>&b){return a.size()>b.size();});
                result = copy_circuits[0].size()*copy_circuits[1].size()*copy_circuits[2].size();
            }
            size_t u = edge.first;
            size_t v = edge.second;

            int idx_u = -1;
            int idx_v = -1;

            for (int i = 0; i < (int)circuits.size(); ++i) {
                if (circuits[i].contains(u)) idx_u = i;
                if (circuits[i].contains(v)) idx_v = i;
            }

            if(idx_u == idx_v)continue;
            else {
                int keep = idx_u;
                int erase = idx_v;
                if (erase < keep) std::swap(erase, keep);

                circuits[keep].insert(circuits[erase].begin(), circuits[erase].end());
                circuits.erase(circuits.begin() + erase);
                if(circuits.size()==1)
                {
                    coor = boxes[u][0] * boxes[v][0];
                }
            }
            ++count;
        }
    }
    /*
    std::vector<Edge> edges;
    for (size_t i = 0; i < boxes.size(); ++i) {
        for (size_t j = i+1; j < boxes.size(); ++j) {
            edges.push_back({distance(boxes[i], boxes[j]), i, j});
        }
    }
    std::sort(edges.begin(),edges.end(),[](const Edge& a, const Edge& b){return a.d<b.d;});
    UnionFind uf(edges.size());
    for(auto& e:edges)
    {
        if(count == 10)
        {
            std::vector<size_t> copy_rank{uf.rank};
            std::sort(copy_rank.begin(),copy_rank.end(),std::greater<size_t>{});
            result = copy_rank[0]*copy_rank[1]*copy_rank[2];
        }
        if(uf.unite(e.u, e.v))
        {
            if(uf.comp == 1)
            {
                coor = boxes[e.u][0] * boxes[e.v][0];
                break;
            }
        }
        ++count;
    }*/
    std::cout<<result<<std::endl;
    std::cout<<coor<<std::endl;
    return 0;
}
