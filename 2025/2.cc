#include <iostream>
#include <string>

unsigned long isInvalid(std::string &&line)
{
    if (line.size() % 2 != 0)
        return 0;
    if (line.substr(0, line.size() / 2) == line.substr(line.size() / 2))
        return 1;
    return 0;
};
int main()
{
    unsigned count{};
    for (std::string line{}; std::getline(std::cin, line, ',');)
    {
        std::string start{line.substr(0, line.find('-'))};
        std::string end{line.substr(line.find('-') + 1)};
        std::cout << start << '-' << end << std::endl;
        for (unsigned long i = std::stoul(start); i < std::stoul(end); ++i)
        {
            count += isInvalid(std::to_string(i)) * i;
        }
    }
    std::cout << count << std::endl;
    return 0;
}