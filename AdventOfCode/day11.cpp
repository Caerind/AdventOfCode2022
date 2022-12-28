#include "aoc.h"

enum class Operation
{
    Multiply,
    Add
};

template <typename IntType>
struct Monkey
{
    int index;
    std::vector<IntType> items;
    Operation op;
    IntType opValue;
    bool opValueSelf;
    IntType divisibleBy;
    int monkeyTrue;
    int monkeyFalse;    

    IntType inspect = 0;
};

template <typename T>
void parse(std::vector<Monkey<T>>& monkeys, std::ifstream& file)
{
    std::string line;
    while (std::getline(file, line))
    {
        if (String::Contains(line, "Monkey"))
        {
            line.erase(0, 7);
            monkeys.push_back(Monkey<T>());
            monkeys.back().index = String::FromString<int>(line);
        }
        else if (String::Contains(line, "Starting items"))
        {
            line.erase(0, 2 + 8 + 1 + 5 + 1 + 1);
            line.erase(std::remove(line.begin(), line.end(), ','), line.end());
            std::istringstream iss(line);
            std::string token;
            while (std::getline(iss, token, ' '))
            {
                monkeys.back().items.push_back(String::FromString<T>(token));
            }
        }
        else if (String::Contains(line, "Operation"))
        {
            line.erase(0, 2 + 9 + 1 + 1 + 3 + 3 + 3 + 1);
            monkeys.back().op = (line[0] == '*') ? Operation::Multiply : Operation::Add;
            line.erase(0, 2);
            if (line == "old")
            {
                monkeys.back().opValueSelf = true;
                monkeys.back().opValue = 0;
            }
            else
            {
                monkeys.back().opValueSelf = false;
                monkeys.back().opValue = String::FromString<T>(line);
            }
        }
        else if (String::Contains(line, "Test"))
        {
            line.erase(0, 2 + 4 + 1 + 1 + 9 + 4);
            monkeys.back().divisibleBy = String::FromString<T>(line);
        }
        else if (String::Contains(line, "true"))
        {
            line.erase(0, 4 + 3 + 4 + 1 + 1 + 5 + 4 + 6 + 1);
            monkeys.back().monkeyTrue = String::FromString<int>(line);
        }
        else if (String::Contains(line, "false"))
        {
            line.erase(0, 4 + 3 + 5 + 1 + 1 + 5 + 4 + 6 + 1);
            monkeys.back().monkeyFalse = String::FromString<int>(line);
        }
    }
}

template <typename T>
T run(std::vector<Monkey<T>>& monkeys, int times, bool part1)
{
    T ppcm = 1;
    for (const Monkey<T>& m : monkeys)
    {
        ppcm *= m.divisibleBy;
    }

    for (int i = 0; i < times; ++i)
    {
        for (int j = 0; j < monkeys.size(); ++j)
        {
            Monkey<T>& m = monkeys[j];
            for (int k = 0; k < m.items.size(); ++k)
            {
                T& worry = m.items[k];                
                if (m.op == Operation::Add)
                {
                    if (m.opValueSelf)
                        worry += worry;
                    else
                        worry += m.opValue;
                }
                else
                {
                    if (m.opValueSelf)
                        worry *= worry;
                    else
                        worry *= m.opValue;
                }

                if (part1)
                {
                    worry /= 3;
                }

                worry = (worry % ppcm + ppcm) % ppcm;

                int newMonkey = ((worry % m.divisibleBy) == T(0)) ? m.monkeyTrue : m.monkeyFalse;

                monkeys[newMonkey].items.push_back(worry);
            }
            m.inspect += (int)m.items.size();
            m.items.clear();
        }
    }
    std::sort(monkeys.begin(), monkeys.end(), [](const Monkey<T>& a, const Monkey<T>& b) { return a.inspect > b.inspect; });
    return monkeys[0].inspect * monkeys[1].inspect;
}

int day11part1(std::ifstream& file)
{
    std::vector<Monkey<int>> monkeys;
    parse(monkeys, file);
    return run(monkeys, 20, true);
}

int day11part2(std::ifstream& file)
{
    std::vector<Monkey<long long int>> monkeys;
    parse(monkeys, file);
    std::cout << run(monkeys, 10000, false) << std::endl;
    return 0;
}
