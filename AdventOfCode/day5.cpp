#include "aoc.h"

#include <stack>

int day5part1(std::ifstream& file)
{
    int result = 0;

    std::stack<char> stacks[9];

    bool readingStacks = true;
    std::vector<std::string> stackLines;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.size() == 0)
        {
            readingStacks = false;
            for (int i = stackLines.size() - 2; i >= 0; --i) // s-1 is 1 2 3 4... which is useless
            {
                char a0 = stackLines[i].size() > 1 ? stackLines[i][1] : ' ';
                char a1 = stackLines[i].size() > 5 ? stackLines[i][5] : ' ';
                char a2 = stackLines[i].size() > 9 ? stackLines[i][9] : ' ';
                char a3 = stackLines[i].size() > 13 ? stackLines[i][13] : ' ';
                char a4 = stackLines[i].size() > 17 ? stackLines[i][17] : ' ';
                char a5 = stackLines[i].size() > 21 ? stackLines[i][21] : ' ';
                char a6 = stackLines[i].size() > 25 ? stackLines[i][25] : ' ';
                char a7 = stackLines[i].size() > 29 ? stackLines[i][29] : ' ';
                char a8 = stackLines[i].size() > 33 ? stackLines[i][33] : ' ';
                if (a0 != ' ') stacks[0].push(a0); 
                if (a1 != ' ') stacks[1].push(a1); 
				if (a2 != ' ') stacks[2].push(a2);
				if (a3 != ' ') stacks[3].push(a3);
				if (a4 != ' ') stacks[4].push(a4);
				if (a5 != ' ') stacks[5].push(a5);
				if (a6 != ' ') stacks[6].push(a6);
				if (a7 != ' ') stacks[7].push(a7);
				if (a8 != ' ') stacks[8].push(a8);
            }
            stackLines.clear();
        }
        else if (readingStacks)
        {
            stackLines.push_back(line);
        }
        else
        {
            // Read instruction
            std::string countStr, indexStr, destStr;
            line.erase(line.begin(), line.begin() + 5);
            Split(line, countStr, " from ");
            Split(line, indexStr, " to ");
            destStr = line;
            int count = FromString<int>(countStr);
            int index = FromString<int>(indexStr) - 1;
            int dest = FromString<int>(destStr) - 1;

            for (int i = 0; i < count; ++i)
            {
                char moved = stacks[index].top();
				stacks[index].pop();
				stacks[dest].push(moved);
            }
        }
	}

	std::string output = "";
	for (int i = 0; i < 9; ++i)
	{
		if (!stacks[i].empty())
		{
			output += stacks[i].top();
		}
	}
	std::cout << output << std::endl;

    return result;
}

int day5part2(std::ifstream& file)
{
	int result = 0;

	std::vector<char> stacks[9];

	bool readingStacks = true;
	std::vector<std::string> stackLines;

	std::string line;
	while (std::getline(file, line))
	{
		if (line.size() == 0)
		{
			readingStacks = false;
			for (int i = stackLines.size() - 2; i >= 0; --i) // s-1 is 1 2 3 4... which is useless
			{
				char a0 = stackLines[i].size() > 1 ? stackLines[i][1] : ' ';
				char a1 = stackLines[i].size() > 5 ? stackLines[i][5] : ' ';
				char a2 = stackLines[i].size() > 9 ? stackLines[i][9] : ' ';
				char a3 = stackLines[i].size() > 13 ? stackLines[i][13] : ' ';
				char a4 = stackLines[i].size() > 17 ? stackLines[i][17] : ' ';
				char a5 = stackLines[i].size() > 21 ? stackLines[i][21] : ' ';
				char a6 = stackLines[i].size() > 25 ? stackLines[i][25] : ' ';
				char a7 = stackLines[i].size() > 29 ? stackLines[i][29] : ' ';
				char a8 = stackLines[i].size() > 33 ? stackLines[i][33] : ' ';
				if (a0 != ' ') stacks[0].push_back(a0);
				if (a1 != ' ') stacks[1].push_back(a1);
				if (a2 != ' ') stacks[2].push_back(a2);
				if (a3 != ' ') stacks[3].push_back(a3);
				if (a4 != ' ') stacks[4].push_back(a4);
				if (a5 != ' ') stacks[5].push_back(a5);
				if (a6 != ' ') stacks[6].push_back(a6);
				if (a7 != ' ') stacks[7].push_back(a7);
				if (a8 != ' ') stacks[8].push_back(a8);
			}
			stackLines.clear();
		}
		else if (readingStacks)
		{
			stackLines.push_back(line);
		}
		else
		{
			// Read instruction
			std::string countStr, indexStr, destStr;
			line.erase(line.begin(), line.begin() + 5);
			Split(line, countStr, " from ");
			Split(line, indexStr, " to ");
			destStr = line;
			int count = FromString<int>(countStr);
			int index = FromString<int>(indexStr) - 1;
			int dest = FromString<int>(destStr) - 1;

			for (int i = 0; i < count; ++i)
			{
				int j = stacks[index].size() - count + i;
				if (j >= 0)
				{
					stacks[dest].push_back(stacks[index][j]);
					stacks[index].erase(stacks[index].begin() + j);
				}
			}
		}
	}

	std::string output = "";
	for (int i = 0; i < 9; ++i)
	{
		if (!stacks[i].empty())
		{
			output += stacks[i][stacks[i].size() - 1];
		}
	}
	std::cout << output << std::endl;

	return result;
}
