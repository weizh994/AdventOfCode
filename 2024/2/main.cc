#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>

bool safe_report_checking(const std::vector<int> &report)
{
    int sum = std::accumulate(report.begin(), report.end(), 0);
    double average = static_cast<double>(sum) / report.size();
    bool increasing{static_cast<double>(report[0]) < average};
    if (increasing)
    {
        for (size_t i{}; i < report.size() - 1; ++i)
        {
            if (report[i] >= report[i + 1])
            {
                return false;
            }
            else if (report[i + 1] - report[i] > 3)
            {
                return false;
            }
        }
    }
    else
    {
        for (size_t i{}; i < report.size() - 1; ++i)
        {
            if (report[i] <= report[i + 1])
            {
                return false;
            }
            else if (report[i] - report[i + 1] > 3)
            {
                return false;
            }
        }
    }
    return true;
}
bool is_safe(const std::vector<int> &report)
{
    // Check if the original report is safe
    if (safe_report_checking(report))
        return true;

    // Try removing each level and check if it makes the report safe
    for (size_t i = 0; i < report.size(); ++i)
    {
        std::vector<int> modifiedReport = report;
        modifiedReport.erase(modifiedReport.begin() + i); // Remove the level
        if (safe_report_checking(modifiedReport))
            return true;
    }

    return false; // Unsafe regardless of removals
}
int main()
{
    std::ifstream file("input");
    if (!file)
    {
        std::cerr << "No input file!" << std::endl;
        return 1;
    }
    std::vector<std::vector<int>> reports{};
    std::string line{};
    while (std::getline(file, line))
    {
        std::vector<int> report{};
        std::istringstream iss{line};
        int num{};
        while (iss >> num)
        {
            report.push_back(num);
        }
        reports.push_back(report);
    }
    file.close();
    int answer{};
    for (const auto &report : reports)
    {
        if (is_safe(report))
        {
            answer++;
        }
    }
    std::cout << answer << std::endl;
}