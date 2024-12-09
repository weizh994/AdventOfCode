#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
long long calculate(const std::vector<int> &disk_maps)
{
    long long answer{};
    for (size_t i{}; i < disk_maps.size(); ++i)
    {
        if (disk_maps[i] != -1)
        {
            answer += disk_maps[i] * i;
        }
    }
    return answer;
}
bool moveFiles(std::vector<int> &disk)
{
    while (disk[disk.size() - 1] == -1)
    {
        disk.erase(disk.end() - 1);
    }
    size_t diskSize = disk.size();
    size_t left = 0;

    while (left < diskSize && disk[left] != -1)
    {
        left++;
    }
    if (left == diskSize || left == diskSize - 1)
        return false;

    for (int i = diskSize - 1; i >= 0; --i)
    {
        if (disk[i] != -1)
        {
            disk[left] = disk[i];
            disk[i] = -1;
            disk.erase(disk.end() - 1);
            return true;
        }
    }
    return false;
}
std::vector<std::pair<int, int>> getBlockMap(const std::vector<int> &disk)
{
    std::vector<std::pair<int, int>> block_map;
    size_t left = 0;
    while (left < disk.size())
    {
        // 寻找第一个 -1
        while (left < disk.size() && disk[left] != -1)
        {
            left++;
        }
        if (left == disk.size())
        {
            break;
        }
        size_t block_start = left;
        // 寻找连续的 -1 块
        while (left < disk.size() && disk[left] == -1)
        {
            left++;
        }
        size_t block_end = left;
        block_map.emplace_back(block_start, block_end - block_start);
    }
    return block_map;
}
std::vector<std::pair<int, int>> getFileMap(const std::vector<int> &disk)
{
    std::vector<std::pair<int, int>> file_map;
    if (disk.empty())
        return file_map;

    int right = disk.size() - 1;
    while (right >= 0)
    {
        while (right >= 0 && disk[right] == -1)
        {
            right--;
        }
        if (right < 0)
        {
            break;
        }
        int file_end = right;
        while (file_end >= 0 && disk[file_end] == disk[right])
        {
            file_end--;
        }
        int file_start = file_end + 1;
        int file_size = file_end < 0 ? right + 1 : right - file_end;
        file_map.emplace_back(file_start, file_size);
        right = file_end;
    }
    return file_map;
}
void moveWholeFiles(std::vector<int> &disk_maps)
{
    std::vector<std::pair<int, int>> block_map = getBlockMap(disk_maps);
    std::vector<std::pair<int, int>> file_map = getFileMap(disk_maps);

    for (size_t i{}; i < file_map.size(); ++i)
    {
        for (size_t j{}; j < block_map.size(); ++j)
        {
            int block_start = block_map[j].first;
            int block_size = block_map[j].second;
            int file_start = file_map[i].first;
            int file_size = file_map[i].second;
            if (block_size >= file_size && block_start < file_start)
            {
                for (int k{}; k < file_size; ++k)
                {
                    disk_maps[block_start + k] = disk_maps[file_start + k];
                    disk_maps[file_start + k] = -1;
                }
                block_map = getBlockMap(disk_maps);
                break;
            }
        }
    }
}
int main()
{
    std::ifstream file("input");
    while (!file)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::string line;
    std::getline(file, line);
    std::vector<int> disk_maps{};
    for (size_t i{}; i < line.size(); ++i)
    {
        size_t id{i / 2};
        if (i % 2 == 0)
        {
            int num_data = line[i] - '0';
            for (int j{}; j < num_data; ++j)
            {
                disk_maps.push_back(id);
            }
        }
        else
        {
            int num_blocks = line[i] - '0';
            for (int j{}; j < num_blocks; ++j)
            {
                disk_maps.push_back(-1);
            }
        }
    }
    std::vector<int> disk_maps_copy{disk_maps};
    while (moveFiles(disk_maps_copy))
    {
    }

    std::cout << "Question 1: " << calculate(disk_maps_copy) << std::endl;
    moveWholeFiles(disk_maps);
    std::cout << "Question 2: " << calculate(disk_maps) << std::endl;
}
