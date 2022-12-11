#include "aoc.h"

void EndOfCycle(int& cycles, int value, int& result)
{
    cycles++;
    if (cycles == 20)
    {
        result += value * cycles;
    }
    else if (cycles == 60)
    {
        result += value * cycles;
    }
    else if (cycles == 100)
    {
        result += value * cycles;
    }
    else if (cycles == 140)
    {
        result += value * cycles;
    }
    else if (cycles == 180)
    {
        result += value * cycles;
    }
    else if (cycles == 220)
    {
        result += value * cycles;
    }
}

int day10part1(std::ifstream& file)
{
    int result = 0;
    int cycles = 1;
    int value = 1;

    std::string line;
    while (std::getline(file, line))
    {
        if (line == "noop") EndOfCycle(cycles, value, result);
        if (String::Contains(line, "addx"))
        {
            EndOfCycle(cycles, value, result);
            line.erase(0, 4);
            value += String::FromString<int>(line);
            EndOfCycle(cycles, value, result);
        }
    }

    return result;
}

int day10part2(std::ifstream& file)
{
    constexpr int CRTwidth = 40;
    constexpr int CRTheight = 6;
    char CRT[CRTwidth][CRTheight];
    int crtCount = 0;
    int crtX = 0;
    int crtY = 0;

    int result = 0;
    int cycles = 1;
    int value = 1;

    auto endOfCycle2 = [&]()
    {
        cycles++;

        char c = '.';
        if (crtCount == value)
        {
            c = '#';
        }
        else if (crtCount == value - 1)
        {
            c = '#';
        }
        else if (crtCount == value + 1)
        {
            c = '#';
        }
        CRT[crtX][crtY] = c;

        crtCount++;
        crtX++;
        if (crtX == CRTwidth)
        {
            crtX = 0;
            crtY++;
            crtCount = 0;
        }
    };

    std::string line;
    while (std::getline(file, line))
    {
        if (line == "noop") endOfCycle2();
        if (String::Contains(line, "addx"))
        {
            endOfCycle2();
            line.erase(0, 4);
            endOfCycle2();
            value += String::FromString<int>(line);
        }
    }

    for (int j = 0; j < CRTheight; ++j)
    {
        for (int i = 0; i < CRTwidth; ++i)
        {
            std::cout << CRT[i][j];
        }
        std::cout << std::endl;
    }

    return result;
}
