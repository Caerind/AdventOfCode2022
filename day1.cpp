#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main()
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
