#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
int main()
{
    std::ifstream file("input");
    if (!file)
    {
        std::cerr << "No input file!" << std::endl;
        return 1;
    }
    std::vector<int> left_nums{}, right_nums{};
    int left_num{}, right_num{};
    while (file >> left_num >> right_num)
    {
        left_nums.push_back(left_num);
        right_nums.push_back(right_num);
    }
    file.close();

    /*Question 1*/
    // if (left_nums.size() != right_nums.size())
    // {
    //     std::cerr << "The number of left and right numbers are not equal!" << std::endl;
    //     return 1;
    // }
    // std::sort(left_nums.begin(), left_nums.end());
    // std::sort(right_nums.begin(), right_nums.end());

    // int answer{};
    // for(int i{}; i < left_nums.size(); ++i)
    // {
    //     answer += std::abs(left_nums[i] - right_nums[i]);
    // }
    // std::cout << answer << std::endl;

    /*Question 2*/
    std::map<int, int> freq{};

    for (int num : right_nums)
    {
        freq[num]++;
    }
    int answer{};
    for (int num : left_nums)
    {
        answer += (num * freq[num]);
    }
    std::cout << answer << std::endl;
}