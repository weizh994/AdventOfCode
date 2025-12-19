#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <vector>
#include <algorithm>
std::vector<std::pair<int, int>> tiles{};
std::unordered_map<int,std::pair<int,int>> H{};//(y,[x1,x2])
std::unordered_map<int,std::pair<int,int>> V{};//(x,[y1,y2])
long area(const std::pair<int, int>& a, const std::pair<int, int>&b)
{
    long x = std::max(a.first,b.first) - std::min(a.first,b.first) + 1;
    long y = std::max(a.second,b.second) - std::min(a.second,b.second) + 1;
    return  x*y;
}
bool dot_inside(int x, int y)
{
    auto itV = V.find(x);
    auto itH = H.find(y);
    if (itV == V.end() || itH == H.end()) return false;

    auto [ymin, ymax] = itV->second;
    auto [xmin, xmax] = itH->second;

    return (ymin <= y && y <= ymax) && (xmin <= x && x <= xmax);
}

bool v_line_cross(int x0, int y1,int y2)
{
    for(auto&[yh,xh]:H)
    {
        if(y1<=yh && yh<=y2)
        {
            int x_min = xh.first;
            int x_max = xh.second;
            if(x_min<=x0 && x0<=x_max) return true;
        }
    }
    return false;
}
bool h_line_cross(int y0, int x1, int x2)
{
    for(auto&[xv, yv]:V)
    {
        if(x1<=xv && xv<=x2)
        {
            int y_min = yv.first;
            int y_max = yv.second;
            if(y_min<=y0 && y0<=y_max) return true;
        }
    }
    return false;
}
bool inside(int i,int j,const std::vector<std::vector<int>>& adj)
{
    int x_left = std::min(tiles[i].first, tiles[j].first);
    int x_right = std::max(tiles[i].first, tiles[j].first);
    int y_top = std::min(tiles[i].second, tiles[j].second);
    int y_bottom = std::max(tiles[i].second, tiles[j].second);

    // check corners
    if(!dot_inside(x_left, y_top) ||
    !dot_inside(x_left, y_bottom) ||
    !dot_inside(x_right, y_top) ||
    !dot_inside(x_right, y_bottom)) return false;
    // check lines

    //Left Vertical Line
    if(v_line_cross(x_left, y_top, y_bottom)) return false;
    //Right Vertical Line
    if(v_line_cross(x_right, y_top, y_bottom)) return false;
    //Top Horizontal Line
    if(h_line_cross(y_top, x_left, x_right)) return false;
    //Bottom Horizontal Line
    if(h_line_cross(y_bottom, x_left, x_right)) return false;
    
    return true;
}
int main()
{
    std::string line{};
    while(std::getline(std::cin,line))
    {
        tiles.push_back({std::stoi(line.substr(0,line.find(','))),
                        std::stoi(line.substr(line.find(',')+1))}); 
    }
    long max_area{};
    for(auto it1=tiles.begin(); it1!=tiles.end();++it1)
    {
        for(auto it2=it1; it2!=tiles.end();++it2)
        {
            long curr_area = area(*it1,*it2);
            if(curr_area>max_area)max_area=curr_area;
        }
    }
    std::cout<<max_area<<std::endl;
    // Part 2
    max_area = 0;
    std::vector<std::vector<int>> adj(tiles.size());
    for(int i=0,j=1; j<tiles.size(); ++i,++j)
    {
        if(tiles[i].first==tiles[j].first || tiles[i].second==tiles[j].second)
        {
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
        // Just Check in case
        else {
            std::cout<<"Error"<<std::endl;
            return 1;
        }
    }
    adj[0].push_back(tiles.size()-1);
    adj[tiles.size()-1].push_back(0);
    // Just Check in case
    auto upd = [](auto& mp, int key, int v){
    auto it = mp.find(key);
    if(it == mp.end()) mp[key] = {v, v};
    else {
        it->second.first  = std::min(it->second.first,  v);
        it->second.second = std::max(it->second.second, v);
    }
};

    for(int i = 0;i<(int)adj.size();++i)
    {
        if(adj[i].size()!=2)
        {
            std::cout<<"Error"<<std::endl;
            return 1;
        }
        int x = tiles[i].first  ;
        int y = tiles[i].second ;   
        upd(H, y, x);
        upd(V, x, y);

    }

    for(int i = 0;i<tiles.size();++i)
    {
        for(int j = 1 ; j<tiles.size();++j)
        {
            if(inside(i,j,adj))
            {
                long curr_area = area(tiles[i], tiles[j]);
                if(curr_area>max_area)max_area=curr_area;
            }
        }
    }
    std::cout<<max_area<<std::endl;
    return 0;
}
