#include "aoc.h"

struct Directory
{
    std::string name;
    int parent;
    std::vector<int> children;
    int filesSize{ 0 };

    int TotalSize(const std::vector<Directory>& dir) const
    {
        int t = filesSize;
        for (size_t i = 0; i < children.size(); i++)
        {
            t += dir[children[i]].TotalSize(dir);
        }
        return t;
    }
};

bool parse(std::ifstream& file, std::vector<Directory>& dir)
{
    int indexCurrent = 0;

    dir.push_back(Directory());
    dir.back().name = "/";
    dir.back().parent = -1;

    std::string line;
    while (std::getline(file, line))
    {
        if (String::Contains(line, "$ cd"))
        {
            if (line == "$ cd /")
            {
                indexCurrent = 0;
            }
            else if (line == "$ cd ..")
            {
                indexCurrent = dir[indexCurrent].parent;
            }
            else
            {
                line = line.substr(5);
                for (int child : dir[indexCurrent].children)
                {
                    if (dir[child].name == line)
                    {
                        indexCurrent = child;
                        break;
                    }
                }
            }
        }
        else if (String::Contains(line, "$ ls"))
        {
            // Do nothing
        }
        else
        {
            if (String::Contains(line, "dir "))
            {
                dir.push_back(Directory());
                dir.back().name = line.substr(4);
                dir.back().parent = indexCurrent;
                dir[indexCurrent].children.push_back((int)dir.size() - 1);
            }
            else
            {
                std::string sizeStr;
                String::Split(line, sizeStr, ' ');
                dir[indexCurrent].filesSize += String::FromString<int>(sizeStr);
            }
        }
    }
    return true;
}

int day7part1(std::ifstream& file)
{
    int result = 0;

    std::vector<Directory> dir;
    parse(file, dir);
    
    for (auto& d : dir)
    {
        if (d.parent != -1) // Exclude root ?
        {
            int t = d.TotalSize(dir);
            if (t <= 100000)
            {
                result += t;
            }
        }
    }

    return result;
}

int day7part2(std::ifstream& file)
{
    std::vector<Directory> dir;
    parse(file, dir);

    const int totalDiskSpace = 70000000;
    const int updateSpace = 30000000;
    int usedSpace = dir[0].TotalSize(dir);
    int freeSpace = totalDiskSpace - usedSpace;
    int needToCleanSpace = updateSpace - freeSpace;

    int minSpace = 999999999;
    for (auto& d : dir)
    {
        if (d.parent != -1) // Exclude root here
        {
            int t = d.TotalSize(dir);
            if (t >= needToCleanSpace && t < minSpace)
            {
                minSpace = t;
            }
        }
    }

    return minSpace;
}
