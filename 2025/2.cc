#include <iostream>
#include <string>

unsigned long isInvalid1(std::string &&line)
{
	if (line.size() % 2 != 0)
		return 0;
	if (line.substr(0, line.size() / 2) == line.substr(line.size() / 2))
	{
		//std::cout<<line<<std::endl;
		return 1;
	}
	return 0;
};
unsigned long isInvalid2(std::string &&line)
{
	for(size_t i{0}; i < line.size()/2 ; ++i)
	{
		std::string key{line.substr(0,i+1)};
		std::string cand;
		cand.reserve(line.size());
		while(cand.size()<line.size())
		{
			cand+=key;
		}
		cand.reserve(line.size());
		if(cand == line) return 1;
	}
	return 0;
};
int main()
{
	unsigned long long count{};
	for (std::string line{}; std::getline(std::cin, line, ',');)
	{
		std::string start{line.substr(0, line.find('-'))};
		std::string end{line.substr(line.find('-') + 1)};
		for (unsigned long i = std::stoul(start); i <= std::stoul(end); ++i)
		{
			//count += isInvalid1(std::to_string(i)) * i;
			count += isInvalid2(std::to_string(i))*i;
		}
	}
	std::cout << count << std::endl;
	return 0;
}
