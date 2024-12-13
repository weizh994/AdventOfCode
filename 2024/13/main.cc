#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define ll long long
struct Data
{
    std::pair<int, int> A;
    std::pair<int, int> B;
    std::pair<int, int> prize;
};
std::pair<ll, ll> calButton(const Data &data)
{
    ll base = data.A.first * data.B.second - data.A.second * data.B.first;
    ll A = data.prize.first * data.B.second - data.prize.second * data.B.first;
    ll B = data.prize.second * data.A.first - data.A.second * data.prize.first;
    if (A % base != 0 || B % base != 0)
        return {0, 0};
    else
        return {A / base, B / base};
}
std::pair<ll, ll> calButton2(const Data &data)
{
    std::pair<ll, ll> prize = {data.prize.first + 10000000000000, data.prize.second + 10000000000000};
    ll base = data.A.first * data.B.second - data.A.second * data.B.first;
    ll A = prize.first * data.B.second - prize.second * data.B.first;
    ll B = prize.second * data.A.first - data.A.second * prize.first;
    if (A % base != 0 || B % base != 0)
        return {0, 0};
    else
        return {A / base, B / base};
}
Data parseBlock(const std::vector<std::string> &block)
{
    Data data;

    int x, y;
    sscanf(block[0].c_str(), "Button A: X+%d, Y+%d", &x, &y);
    data.A = {x, y};

    sscanf(block[1].c_str(), "Button B: X+%d, Y+%d", &x, &y);
    data.B = {x, y};

    sscanf(block[2].c_str(), "Prize: X=%d, Y=%d", &x, &y);
    data.prize = {x, y};

    return data;
}

int main()
{
    std::ifstream file{"input"};
    while (!file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::vector<Data> dataset;
    std::vector<std::string> block;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            if (!block.empty())
            {
                dataset.push_back(parseBlock(block));
                block.clear();
            }
        }
        else
        {
            block.push_back(line);
        }
    }
    if (!block.empty())
    {
        dataset.push_back(parseBlock(block));
    }
    ll price{};
    for (const auto &data : dataset)
    {
        auto temp = calButton(data);
        price += 3 * temp.first + temp.second;
    }
    std::cout << "Question 1: " << price << std::endl;
    price = 0;
    for (const auto &data : dataset)
    {
        auto temp = calButton2(data);
        price += 3 * temp.first + temp.second;
    }
    std::cout << "Question 2: " << price << std::endl;
    return 0;
}