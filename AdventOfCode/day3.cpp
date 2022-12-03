#include "aoc.h"

int charValue(char c)
{
	if (c >= 97 && c <= 122)
	{
		return (int)(c)-96;
	}
	else
	{
		return (int)(c)-65 + 27;
	}
}

int day3part1(std::ifstream& file)
{
    int result = 0;

    std::string line;
    while (std::getline(file, line))
    {
        std::string first = line.substr(0, line.size() / 2);
		std::string second = line.substr(line.size() / 2);

        int count = 0;
        for (std::size_t i = 0; i < first.size(); ++i)
		{
			char c = first[i];
            if (std::find(second.begin(), second.end(), c) != second.end())
            {
                result += charValue(c);
                break;
            }
        }
    }

    return result;
}

int day3part2(std::ifstream& file)
{
	int result = 0; 
	
	int groupSize = 0;
	std::string group[3];
	std::string line;
	while (std::getline(file, line))
	{
		group[groupSize] = line;
		groupSize++;
		if (groupSize == 3)
		{
			groupSize = 0;
			for (std::size_t i = 0; i < group[0].size(); ++i)
			{
				char c = group[0][i];
				if (std::find(group[1].begin(), group[1].end(), c) != group[1].end() && std::find(group[2].begin(), group[2].end(), c) != group[2].end())
				{
					result += charValue(c);
					break;
				}
			}
		}
	}

    return result;
}
