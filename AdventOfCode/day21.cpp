#include "aoc.h"

#include <unordered_map>
#include <cassert>

struct Operation;
using NumberType = long double;
using DicType = std::unordered_map<std::string, Operation>;

struct Operation
{
    std::string name;
    std::string a;
    std::string b;
    NumberType value{ 0 };
    bool isNumber{ false };
    char symbol;

    NumberType Compute(DicType& dic)
    {
        if (isNumber)
        {
            assert(value != NumberType(0));
            return value;
        }
        else
        {
            assert(dic.find(a) != dic.end());
            assert(dic.find(b) != dic.end());
            switch (symbol)
            {
            case '+': return dic[a].Compute(dic) + dic[b].Compute(dic);
            case '-': return dic[a].Compute(dic) - dic[b].Compute(dic);
            case '*': return dic[a].Compute(dic) * dic[b].Compute(dic);
            case '/': return dic[a].Compute(dic) / dic[b].Compute(dic);
            }
            assert(false);
            return NumberType(0);
        }
    }

    bool HasHumn(DicType& dic)
    {
        if (isNumber)
        {
            return false;
        }
        else
        {
            if (a == "humn" || b == "humn")
                return true;
            else
                return dic[a].HasHumn(dic) || dic[b].HasHumn(dic);
        }
    }

    void Reduce(DicType& dic)
    {
        if (!isNumber)
        {
            dic[a].Reduce(dic);
            dic[b].Reduce(dic);
            if (!HasHumn(dic))
            {

                value = Compute(dic);
                isNumber = true;
                dic.erase(a);
                dic.erase(b);
            }
        }
    }

    NumberType ReverseHumn(DicType& dic, NumberType expected)
    {
        if (name != "humn")
        {
            assert(!isNumber);

            assert(dic.find(a) != dic.end());
            assert(dic.find(b) != dic.end());

            Operation& opA = dic[a];
            Operation& opB = dic[b];

            if (opA.name == "humn" || opB.name == "humn")
                return expected;

            if (!opA.isNumber)
            {
                assert(opB.isNumber);
                switch (symbol) 
                {
                case '+': return opA.ReverseHumn(dic, expected - opB.value);
                case '-': return opA.ReverseHumn(dic, expected + opB.value);
                case '*': return opA.ReverseHumn(dic, expected / opB.value);
                case '/': return opA.ReverseHumn(dic, expected * opB.value);
                }
                assert(false);
                return NumberType(0);
            }
            else if (!opB.isNumber)
            {
                assert(opA.isNumber);
                switch (symbol)
                {
                case '+': return opB.ReverseHumn(dic, expected - opA.value);
                case '-': return opB.ReverseHumn(dic, opA.value - expected);
                case '*': return opB.ReverseHumn(dic, expected / opA.value);
                case '/': return opB.ReverseHumn(dic, opA.value / expected);
                }
                assert(false);
                return NumberType(0);
            }
            else
            {
                assert(false);
            }
        }
        return expected;
    }
};

void parse(std::ifstream& file, DicType& dic)
{
    std::string line;
    while (std::getline(file, line))
    {
        std::string name = line.substr(0, 4);

        assert(dic.find(name) == dic.end());

        dic[name] = Operation();
        line.erase(0, 6);

        Operation& op = dic[name];
        op.name = name;
        if (line.size() > 8)
        {
            op.isNumber = false;
            op.a = line.substr(0, 4);
            op.b = line.substr(7, 4);
            op.symbol = line[5];
        }
        else
        {
            op.isNumber = true;
            op.value = String::FromString<NumberType>(line);
        }
    }
}

int day21part1(std::ifstream& file)
{
    DicType dic;
    parse(file, dic);

    std::cout << dic["root"].Compute(dic) << std::endl;
    return 0;
}

int day21part2(std::ifstream& file)
{
    DicType dic;
    parse(file, dic);

    Operation& a = dic[dic["root"].a];
    Operation& b = dic[dic["root"].b];

    assert(a.HasHumn(dic));
    assert(!b.HasHumn(dic));

    dic["root"].Reduce(dic);

    Operation& humn = dic["humn"];
    assert(humn.isNumber);

    NumberType humnValue = a.ReverseHumn(dic, b.value);

    NumberType i = 0;
    while (true)
    {
        humn.value = humnValue + i;
        if (a.Compute(dic) == b.value)
        {
            std::cout << "root: humn(" << static_cast<long long>(humn.value) << ")" << a.Compute(dic) << " = " << b.value << std::endl;
            if (b.value == 150)
                return 0;
        }

        humn.value = humnValue - i;
        if (a.Compute(dic) == b.value)
        {
            std::cout << "root: humn(" << static_cast<long long>(humn.value) << ")" << a.Compute(dic) << " = " << b.value << std::endl;
            if (b.value == 150)
                return 0;
        }

        ++i;
    }

    return 0;
}
