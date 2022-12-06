#include "aoc.h"

int day6part1(std::ifstream& file)
{
    int result = 0;

    std::string line;
    std::getline(file, line);

    for (int i = 3; i < line.size(); ++i)
    {
        char a0 = line[i - 3];
        char a1 = line[i - 2];
        char a2 = line[i - 1];
        char a3 = line[i];

        if (!(a0 == a1 || a0 == a2 || a0 == a3 || a1 == a2 || a1 == a3 || a2 == a3))
        {
            return i + 1;
        }
    }

    return result;
}

int day6part2(std::ifstream& file)
{
    int result = 0;

    std::string line;
    std::getline(file, line);

    std::vector<char> v;
    for (int i = 0; i < 13; ++i)
    {
        v.push_back(line[i]);
    }
    for (int i = 13; i < line.size(); ++i)
    {
        v.push_back(line[i]);

        for (const auto a : v)
        {
            std::cout << a;
        }
        std::cout << std::endl;

        bool found = false;
        for (int j = 0; j < v.size() && !found; ++j)
        {
            for (int k = 0; k < v.size() - 1 && !found; ++k)
            {
                if (j != k)
                {
                    if (v[j] == v[k])
                    {
                        found = true;
                    }
                }
            }
        }
        if (!found)
        {
            return i + 1;
        }

        v.erase(v.begin());
    }

    return result;
}
