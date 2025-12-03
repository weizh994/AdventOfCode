#include <iostream>
#include <string>

int main()
{
    std::string line{};
    unsigned long long joltage{};
    std::string jolts{};
    while (std::getline(std::cin, line))
    {
        jolts.clear();
        int first{-1};
        unsigned int max{0};
        // for (int i{2}; i > 0; --i)
        for (int i{12}; i > 0; --i)
        {
            max = 0;
            for (int j{first + 1}; j <= line.size() - i; ++j)
            {
                if (line[j] - '0' > max)
                {
                    max = line[j] - '0';
                    first = j;
                }
            }
            jolts += line[first];
        }
        joltage += std::stoull(jolts);
    }
    std::cout << joltage << std::endl;
    return 0;
}