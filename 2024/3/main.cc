#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

int mul(const std::string &match)
{
    // 从 match 中提取两个数字
    std::regex pattern(R"(\d+)");
    auto begin = std::sregex_iterator(match.begin(), match.end(), pattern);
    auto end = std::sregex_iterator();
    std::vector<int> numbers;
    for (auto it = begin; it != end; ++it)
    {
        numbers.push_back(std::stoi(it->str()));
    }
    return numbers[0] * numbers[1];
}

std::vector<std::string> splitAndKeepDelimiters(const std::string &input, const std::vector<std::string> &delimiters)
{
    // 构造正则表达式，将分隔符拼接为 alternation 模式
    std::string regexPattern = "(";
    for (size_t i = 0; i < delimiters.size(); ++i)
    {
        regexPattern += std::regex_replace(delimiters[i], std::regex(R"([\^$|()\[\]\{\}.*+?\\])"), R"(\$&)"); // 转义特殊字符
        if (i != delimiters.size() - 1)
        {
            regexPattern += "|";
        }
    }
    regexPattern += ")";
    // 创建正则表达式
    std::regex pattern(regexPattern);
    // 使用正则表达式分割字符串并保留分隔符
    std::sregex_token_iterator begin(input.begin(), input.end(), pattern, {-1, 0});
    std::sregex_token_iterator end;
    // 收集分割结果
    std::vector<std::string> result;
    for (auto it = begin; it != end; ++it)
    {
        result.push_back(it->str());
    }
    return result;
}

int main()
{
    std::ifstream file("input");
    if (!file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    // 读取文件内容
    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close(); // 关闭文件

    // 定义分隔符
    std::vector<std::string> delimiters = {"don't()", "do()"};

    // 分割字符串
    std::vector<std::string> parts = splitAndKeepDelimiters(input, delimiters);

    // 定义正则表达式，匹配 mul(X,Y) 格式，其中 X 和 Y 都是数字
    std::regex pattern(R"(mul\(\d+,\d+\))");
    // 创建结果容器
    std::vector<std::string> matches;
    bool flag{true};
    for (const auto &part : parts)
    {
        if (part == "don't()")
        {
            flag = false;
        }
        else if (part == "do()")
        {
            flag = true;
        }
        if (flag)
        {
            // 在 part 中查找匹配
            auto begin = std::sregex_iterator(part.begin(), part.end(), pattern);
            auto end = std::sregex_iterator();
            for (auto it = begin; it != end; ++it)
            {
                matches.push_back(it->str());
            }
        }
    }
    int answer{};
    for (const auto &match : matches)
    {
        answer += mul(match);
    }
    std::cout << "Answer: " << answer << std::endl;
    return 0;
}