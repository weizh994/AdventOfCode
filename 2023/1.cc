#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string s{};
    int sum{};
    while (std::cin >> s)
    {
        // part 1
        /*
        int i{};
        std::find_if(s.begin(), s.end(), [&i](char c)
                     {
            if (c >= '0'&& c <= '9')
            {
                i = std::stoi(std::string{ c })*10;
                return true;
            }
            return false; });
        std::find_if(s.rbegin(), s.rend(), [&i](char c)
                     {
            if (c >= '0'&& c <= '9')
            {
                i += std::stoi(std::string{ c });return true;
            }
            return false; });
        sum += i;
        */

        // part 2
        }
    std::cout << sum << std::endl;
}