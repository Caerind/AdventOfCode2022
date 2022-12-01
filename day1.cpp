#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int partOne()
{
    std::ifstream file("day1.data");
    if (!file)
    {
        std::cerr << "Can't find data" << std::endl;
        return -1;
    }

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
            current += atoi(line.c_str());
        }
    }

    file.close();
    return result;
}

int partTwo()
{
    std::ifstream file("day1.data");
    if (!file)
    {
        std::cerr << "Can't find data" << std::endl;
        return -1;
    }

    int max[3] = {0,0,0};
    int current = 0;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.size() == 0)
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
        }
        else
        {
            current += atoi(line.c_str());
        }
    }

    file.close();
    return max[0] + max[1] + max[2];
}

int main()
{
    return partTwo();
}
