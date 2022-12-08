#include "aoc.h"

int day8part1(std::ifstream& file)
{
    int result = 0;

    std::vector<std::string> map;
    std::string line;
    std::size_t size = 0;
    while (std::getline(file, line))
    {
        map.push_back(line);
        if (size == 0)
            size = line.size();
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        for (std::size_t j = 0; j < map.size(); ++j)
        {
            if (i == 0 || j == 0 || i == size-1 || j == map.size()-1)
            {
                result++;
            }
            else
            {
                bool top = true;
                bool down = true;
                bool left = true;
                bool right = true;

                for (std::size_t x = 0; x < size; ++x)
                {
                    if (x != i && map[x][j] >= map[i][j])
                    {
                        if (x < i)
                        {
                            left = false;
                            x = i;
                        }
                        else
                        {
                            right = false;
                            break;
                        }
                    }
                }

                for (std::size_t y = 0; y < map.size(); ++y)
                {
                    if (y != j && map[i][y] >= map[i][j])
                    {
                        if (y < j)
                        {
                            top = false;
                            y = j;
                        }
                        else
                        {
                            down = false;
                            break;
                        }
                    }
                }

                if (top || down || left || right)
                    result++;
            }            
        }
    }

    return result;
}

int day8part2(std::ifstream& file)
{
    int result = 0;

    std::vector<std::string> map;
    std::string line;
    std::size_t size = 0;
    while (std::getline(file, line))
    {
        map.push_back(line);
        if (size == 0)
            size = line.size();
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < map.size(); ++j)
        {
            if (i == 0 || j == 0 || i == size - 1 || j == map.size() - 1)
            {
                // Nothing as 0 * anything is 0, it won't beat the high score
            }
            else
            {
                int scoreT = 0;
                int scoreD = 0;
                int scoreL = 0;
                int scoreR = 0;

                bool top = true;
                bool down = true;
                bool left = true;
                bool right = true;

                for (int n = 1; top || down || left || right; ++n)
                {
                    if (top)
                    {
                        if (j - n < 0)
                        {
                            top = false;
                            scoreT = n - 1;
                        }
                        else if (map[i][j - n] >= map[i][j])
                        {
                            top = false;
                            scoreT = n;
                        }
                    }
                    if (down)
                    {
                        if (j + n >= map.size())
                        {
                            down = false;
                            scoreD = n - 1;
                        }
                        else if (map[i][j + n] >= map[i][j])
                        {
                            down = false;
                            scoreD = n;
                        }
                    }
                    if (left)
                    {
                        if (i - n < 0)
                        {
                            left = false;
                            scoreL = n - 1;
                        }
                        else if (map[i - n][j] >= map[i][j])
                        {
                            left = false;
                            scoreL = n;
                        }
                    }
                    if (right)
                    {
                        if (i + n >= size)
                        {
                            right = false;
                            scoreR = n - 1;
                        }
                        else if (map[i + n][j] >= map[i][j])
                        {
                            right = false;
                            scoreR = n;
                        }
                    }                    
                }

                int score = scoreT * scoreD * scoreL * scoreR;
                if (score > result)
                {
                    result = score;
                }
            }
        }
    }

    return result;
}
