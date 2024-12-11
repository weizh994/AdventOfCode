#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#define ll long long
struct stone
{
    ll num;
    stone *next;
    stone(ll num) : num(num), next(nullptr) {}
};
void handleStone(stone *curr)
{
    if (curr->num == 0)
        curr->num = 1;
    else if (std::to_string(curr->num).size() % 2 == 0)
    {
        std::string whole = std::to_string(curr->num);
        size_t mid = whole.size() / 2;
        std::string left = whole.substr(0, mid);
        curr->num = std::stoll(left);
        std::string right = whole.substr(mid, mid);
        stone *temp = new stone(std::stoll(right));
        temp->next = curr->next;
        curr->next = temp;
    }
    else
    {
        curr->num *= 2024;
    }
}
int main()
{
    std::string input{"2 54 992917 5270417 2514 28561 0 990"};
    // std::string input{"125 17"};
    std::istringstream iss{input};
    ll num{};
    stone *head{};
    stone *curr{};
    while (iss >> num)
    {
        stone *temp = new stone(num);
        if (!head)
        {
            head = temp;
            curr = temp;
        }
        curr->next = temp;
        curr = temp;
    }
    for (int i{}; i < 25; ++i)
    {
        stone *curr = head;
        while (curr)
        {
            stone *next = curr->next;
            handleStone(curr);
            curr = next;
        }
    }
    ll answer{};
    while (head)
    {
        answer++;
        head = head->next;
    }
    std::cout << "Question 1: " << answer << std::endl;
    std::istringstream iss2{input};
    std::unordered_map<ll, ll> stone_count;
    while (iss2 >> num)
    {
        stone_count[num] = 1;
    }
    for (int i{}; i < 75; ++i)
    {
        std::unordered_map<ll, ll> new_stone{};
        for (const auto &[val, num] : stone_count)
        {
            if (val == 0)
            {
                new_stone[1] += num;
            }
            else if (std::to_string(val).size() % 2 == 0)
            {
                std::string whole = std::to_string(val);
                size_t mid = whole.size() / 2;
                std::string left = whole.substr(0, mid);
                ll lval = std::stoll(left);
                std::string right = whole.substr(mid, mid);
                ll rval = std::stoll(right);
                new_stone[lval] += num;
                new_stone[rval] += num;
            }
            else
            {
                new_stone[val * 2024] += num;
            }
        }
        stone_count.swap(new_stone);
    }
    ll result{};
    for (const auto &[val, num] : stone_count)
    {
        result += num;
    }
    std::cout << "Question 2: " << result << std::endl;

    return 0;
}