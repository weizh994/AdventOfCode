// Advent of Code 2023 day 3
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

bool is_valid(char c)
{
    return c != '.' && (c < '0' || c > '9');
}

// check if the number adjacent to a symbol
bool valid(const std::vector<std::string> &lines, unsigned long row, unsigned long first, unsigned long last)
{
    if (row == 0) // first line
    {
        for (unsigned long i = first; i <= last; ++i)
        {
            if (is_valid(lines[row + 1][i]))
            {
                return true;
            }
        }
        if (first > 0 && (is_valid(lines[row][first - 1]) || is_valid(lines[row + 1][first - 1])))
        {
            return true;
        }
        if (last < lines[row].length() - 1 && (is_valid(lines[row][last + 1]) || is_valid(lines[row + 1][last + 1])))
        {
            return true;
        }
        return false;
    }
    else if (row == lines.size() - 1) // last line
    {
        for (unsigned long i = first; i <= last; ++i)
        {
            if (is_valid(lines[row - 1][i]))
            {
                return true;
            }
        }
        if (first > 0 && (is_valid(lines[row][first - 1]) || is_valid(lines[row - 1][first - 1])))
        {
            return true;
        }
        if (last < lines[row].length() - 1 && (is_valid(lines[row][last + 1]) || is_valid(lines[row - 1][last + 1])))
        {
            return true;
        }
        return false;
    }
    else // middle lines
    {
        for (unsigned long i = first; i <= last; ++i)
        {
            if (is_valid(lines[row - 1][i]) || is_valid(lines[row + 1][i]))
            {
                return true;
            }
        }
        if (first > 0 && ((is_valid(lines[row][first - 1]) || is_valid(lines[row - 1][first - 1]) || is_valid(lines[row + 1][first - 1]))))
        {
            return true;
        }
        if (last < lines[row].length() - 1 && ((is_valid(lines[row][last + 1]) || is_valid(lines[row - 1][last + 1]) || is_valid(lines[row + 1][last + 1]))))
        {
            return true;
        }
        return false;
    }
}

int main()
{
    int p1 = 0;
    int p2 = 0;
    std::vector<std::string> lines{};
    std::ifstream f("3.input");
    std::string line;
    if (f.is_open())
    {
        std::string line{};
        while (std::getline(f, line))
        {
            lines.push_back(line);
        }
    }
    else
    {
        std::cerr << "File not found\n";
    }
    f.close();
    unsigned long row{};
    for (auto &line : lines)
    {
        // remove char for input
        std::string copy_line{line};
        for (auto &c : copy_line)
        {
            if (c < '0' || c > '9')
            {
                c = ' ';
            }
        }
        std::istringstream input(copy_line);
        int num{};
        std::string::size_type first{};
        std::string::size_type last{};
        while (input >> num)
        {
            std::string snum{std::to_string(num)};
            first = line.find(snum, first);
            last = first + snum.length() - 1;
            // check if the number adjacent to a symbol
            if (valid(lines, row, first, last))
            {
                p1 += num;
            }
        }
        ++row; // next row
    }
    std::cout << "Part 1: " << p1 << std::endl;
    std::cout << "Part 2: " << p2 << std::endl;
}