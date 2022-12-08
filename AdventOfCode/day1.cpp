#include "aoc.h"

int day1part1(std::ifstream& file)
{
    int result = 0;
    int current = 0;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.size() == 0)
        {
            if (current > result)
                result = current;
            current = 0;
        }
        else
        {
            current += String::FromString<int>(line);
        }
    }

    return result;
}

int day1part2(std::ifstream& file)
{
    int max[3] = {0,0,0};
    int current = 0;

    const auto endOfBatch = [&current, &max]()
    {
        if (current > max[0])
        {
            max[2] = max[1];
            max[1] = max[0];
            max[0] = current;
        }
        else if (current > max[1])
        {
            max[2] = max[1];
            max[1] = current;
        }
        else if (current > max[2])
        {
            max[2] = current;
        }
        current = 0;
    };

    std::string line;
    while (std::getline(file, line))
    {
        if (line.size() == 0)
        {
            endOfBatch();
        }
        else
        {
            current += String::FromString<int>(line);
        }
    }
    endOfBatch();

    return max[0] + max[1] + max[2];
}
