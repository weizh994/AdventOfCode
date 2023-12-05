#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

int main()
{
    int p1 = 0;
    int p2 = 0;
    int red_max{12}, green_max{13}, blue_max{14};
    std::ifstream f("2.input");
    std::string line;
    if (f.is_open())
    {
        while (std::getline(f, line))
        {
            auto colon{line.find(":")};
            auto game{std::stoi(line.substr(4, colon))};
            std::map<std::string, int> pockets{{"red", 0}, {"green", 0}, {"blue", 0}};
            std::string rest{};
            std::istringstream iss(line.substr(line.find(":") + 1));
            while (std::getline(iss, rest, ';'))
            {
                std::string pocket{};
                std::istringstream iss2(rest);
                while (std::getline(iss2, pocket, ','))
                {
                    int number{};
                    std::string color{};
                    std::istringstream iss3(pocket);
                    while (iss3 >> number >> color)
                    {
                        if (color.substr(0, 3) == "red")
                        {
                            if (number > pockets["red"])
                                pockets["red"] = number;
                        }
                        else if (color.substr(0, 5) == "green")
                        {
                            if (number > pockets["green"])
                                pockets["green"] = number;
                        }
                        else if (color.substr(0, 4) == "blue")
                        {
                            if (number > pockets["blue"])
                                pockets["blue"] = number;
                        }
                    }
                }
            }
            if (pockets["red"] <= red_max && pockets["green"] <= green_max && pockets["blue"] <= blue_max)
            {
                p1 += game;
            }
            p2 += (pockets["red"] * pockets["green"] * pockets["blue"]);
        }
    }
    else
    {
        std::cout << "File not found" << std::endl;
    }
    f.close();
    std::cout << "Part 1: " << p1 << std::endl;
    std::cout << "Part 2: " << p2 << std::endl;
}