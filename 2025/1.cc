#include <iostream>
#include <string>

int main()
{
    std::string line{};
    unsigned int idel{50};
    unsigned int pwd{};
    while (std::getline(std::cin, line))
    {
        unsigned int dist = std::stoi(line.substr(1)) % 100;
        pwd += std::stoi(line.substr(1)) / 100; // Part 2
        switch (line[0])
        {
        case 'L':
            if (dist > idel)
            {
                if (idel != 0)
                {
                    ++pwd;
                }
                idel += 100;
            }
            idel -= dist;
            break;
        case 'R':
            idel += dist;
            if (idel > 99)
            {
                idel -= 100;
                if (idel != 0)
                {
                    ++pwd;
                }
            }
            break;
        default:
            std::cout << "ERROR: Illegal input " << line << std::endl;
            return 1;
        }
        if (idel == 0)
        {
            ++pwd;
        }
        line.clear();
    }
    std::cout << pwd << std::endl;
    return 0;
}