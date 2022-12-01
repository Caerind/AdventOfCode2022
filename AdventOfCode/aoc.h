#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <codecvt>
#include <locale>
#include <sstream>
#include <cctype>

#include "aoc_string.h"

int day1part1(std::ifstream& file);
int day1part2(std::ifstream& file);

int day2part1(std::ifstream& file);
int day2part2(std::ifstream& file);

int day3part1(std::ifstream& file);
int day3part2(std::ifstream& file);

int day4part1(std::ifstream& file);
int day4part2(std::ifstream& file);

int day5part1(std::ifstream& file);
int day5part2(std::ifstream& file);

int day6part1(std::ifstream& file);
int day6part2(std::ifstream& file);

int day7part1(std::ifstream& file);
int day7part2(std::ifstream& file);

int day8part1(std::ifstream& file);
int day8part2(std::ifstream& file);

int day9part1(std::ifstream& file);
int day9part2(std::ifstream& file);

int day10part1(std::ifstream& file);
int day10part2(std::ifstream& file);

int day11part1(std::ifstream& file);
int day11part2(std::ifstream& file);

int day12part1(std::ifstream& file);
int day12part2(std::ifstream& file);

int day13part1(std::ifstream& file);
int day13part2(std::ifstream& file);

int day14part1(std::ifstream& file);
int day14part2(std::ifstream& file);

int day15part1(std::ifstream& file);
int day15part2(std::ifstream& file);

int day16part1(std::ifstream& file);
int day16part2(std::ifstream& file);

int day17part1(std::ifstream& file);
int day17part2(std::ifstream& file);

int day18part1(std::ifstream& file);
int day18part2(std::ifstream& file);

int day19part1(std::ifstream& file);
int day19part2(std::ifstream& file);

int day20part1(std::ifstream& file);
int day20part2(std::ifstream& file);

int day21part1(std::ifstream& file);
int day21part2(std::ifstream& file);

int day22part1(std::ifstream& file);
int day22part2(std::ifstream& file);

int day23part1(std::ifstream& file);
int day23part2(std::ifstream& file);

int day24part1(std::ifstream& file);
int day24part2(std::ifstream& file);

int day25part1(std::ifstream& file);
int day25part2(std::ifstream& file);

inline int solve(int day, int part, std::ifstream& file)
{
    switch (day)
    {
    case 1:
    {
        if (part == 1) return day1part1(file);
        if (part == 2) return day1part2(file);
        break;
    }
    case 2:
    {
        if (part == 1) return day2part1(file);
        if (part == 2) return day2part2(file);
        break;
    }
    case 3:
    {
        if (part == 1) return day3part1(file);
        if (part == 2) return day3part2(file);
        break;
    }
    case 4:
    {
        if (part == 1) return day4part1(file);
        if (part == 2) return day4part2(file);
        break;
    }
    case 5:
    {
        if (part == 1) return day5part1(file);
        if (part == 2) return day5part2(file);
        break;
    }
    case 6:
    {
        if (part == 1) return day6part1(file);
        if (part == 2) return day6part2(file);
        break;
    }
    case 7:
    {
        if (part == 1) return day7part1(file);
        if (part == 2) return day7part2(file);
        break;
    }
    case 8:
    {
        if (part == 1) return day8part1(file);
        if (part == 2) return day8part2(file);
        break;
    }
    case 9:
    {
        if (part == 1) return day9part1(file);
        if (part == 2) return day9part2(file);
        break;
    }
    case 10:
    {
        if (part == 1) return day10part1(file);
        if (part == 2) return day10part2(file);
        break;
    }
    case 11:
    {
        if (part == 1) return day11part1(file);
        if (part == 2) return day11part2(file);
        break;
    }
    case 12:
    {
        if (part == 1) return day12part1(file);
        if (part == 2) return day12part2(file);
        break;
    }
    case 13:
    {
        if (part == 1) return day13part1(file);
        if (part == 2) return day13part2(file);
        break;
    }
    case 14:
    {
        if (part == 1) return day14part1(file);
        if (part == 2) return day14part2(file);
        break;
    }
    case 15:
    {
        if (part == 1) return day15part1(file);
        if (part == 2) return day15part2(file);
        break;
    }
    case 16:
    {
        if (part == 1) return day16part1(file);
        if (part == 2) return day16part2(file);
        break;
    }
    case 17:
    {
        if (part == 1) return day17part1(file);
        if (part == 2) return day17part2(file);
        break;
    }
    case 18:
    {
        if (part == 1) return day18part1(file);
        if (part == 2) return day18part2(file);
        break;
    }
    case 19:
    {
        if (part == 1) return day19part1(file);
        if (part == 2) return day19part2(file);
        break;
    }
    case 20:
    {
        if (part == 1) return day20part1(file);
        if (part == 2) return day20part2(file);
        break;
    }
    case 21:
    {
        if (part == 1) return day21part1(file);
        if (part == 2) return day21part2(file);
        break;
    }
    case 22:
    {
        if (part == 1) return day22part1(file);
        if (part == 2) return day22part2(file);
        break;
    }
    case 23:
    {
        if (part == 1) return day23part1(file);
        if (part == 2) return day23part2(file);
        break;
    }
    case 24:
    {
        if (part == 1) return day24part1(file);
        if (part == 2) return day24part2(file);
        break;
    }
    case 25:
    {
        if (part == 1) return day25part1(file);
        if (part == 2) return day25part2(file);
        break;
    }
    default:break;
    }
    assert(false);
    return -1;
}