#include "aoc.h"

#include <unordered_set>

struct Pos2D
{
    int x{ 0 };
    int y{ 0 };

    Pos2D() = default;
    Pos2D(int _x, int _y) : x(_x), y(_y) {}

    Pos2D& operator=(const Pos2D& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }
    Pos2D operator+(const Pos2D& other) const
    {
        return Pos2D(x + other.x, y + other.y);
    }    
    Pos2D& operator+=(const Pos2D& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    bool operator==(const Pos2D& other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator<(const Pos2D& other)
    {
        return (x < other.y || (x == other.x && y == other.y));
    };
}; 

namespace std {
    template<> struct hash<Pos2D>
    {
        std::size_t operator()(const Pos2D& p) const noexcept
        {
            return p.x + 1234567 * p.y;
        }
    };
}

enum class Direction
{
    Right = 0,
    Up = 1,
    Left = 2,
    Down = 3
};

int day9part1(std::ifstream& file)
{
    std::unordered_set<Pos2D> visitedTailPositions;
    Pos2D headPos;
    Pos2D tailPos;

    visitedTailPositions.insert(tailPos);

    Pos2D directions[4]
    {
        Pos2D(1, 0),
        Pos2D(0, 1),
        Pos2D(-1, 0),
        Pos2D(0, -1)
    };

    std::string line;
    while (std::getline(file, line))
    {
        Pos2D dir;
        switch (line[0])
        {
        case 'R': dir = directions[(int)Direction::Right]; break;
        case 'U': dir = directions[(int)Direction::Up]; break;
        case 'L': dir = directions[(int)Direction::Left]; break;
        case 'D': dir = directions[(int)Direction::Down]; break;
        }
        line.erase(0, 2);
        int count = String::FromString<int>(line);

        for (int i = 0; i < count; ++i)
        {
            headPos += dir;

            int dx = headPos.x - tailPos.x;
            int dy = headPos.y - tailPos.y;
            if (dx >= 2)
            {
                tailPos += directions[(int)Direction::Right];
                if (dy > 0) tailPos += directions[(int)Direction::Up];
                if (dy < 0) tailPos += directions[(int)Direction::Down];
            }
            else if (dx <= -2)
            {
                tailPos += directions[(int)Direction::Left];
                if (dy > 0) tailPos += directions[(int)Direction::Up];
                if (dy < 0) tailPos += directions[(int)Direction::Down];
            }
            else if (dy >= 2)
            {
                tailPos += directions[(int)Direction::Up];
                if (dx > 0) tailPos += directions[(int)Direction::Right];
                if (dx < 0) tailPos += directions[(int)Direction::Left];
            }
            else if (dy <= -2)
            {
                tailPos += directions[(int)Direction::Down];
                if (dx > 0) tailPos += directions[(int)Direction::Right];
                if (dx < 0) tailPos += directions[(int)Direction::Left];
            }

            visitedTailPositions.insert(tailPos);
        }
    }

    return visitedTailPositions.size();
}

int day9part2(std::ifstream& file)
{
    std::unordered_set<Pos2D> visitedTailPositions;
    Pos2D headPos;
    Pos2D tailPos[9];

    visitedTailPositions.insert(Pos2D(0, 0));

    Pos2D directions[4]
    {
        Pos2D(1, 0),
        Pos2D(0, 1),
        Pos2D(-1, 0),
        Pos2D(0, -1)
    };

    std::string line;
    while (std::getline(file, line))
    {
        Pos2D dir;
        switch (line[0])
        {
        case 'R': dir = directions[(int)Direction::Right]; break;
        case 'U': dir = directions[(int)Direction::Up]; break;
        case 'L': dir = directions[(int)Direction::Left]; break;
        case 'D': dir = directions[(int)Direction::Down]; break;
        }
        line.erase(0, 2);
        int count = String::FromString<int>(line);

        for (int i = 0; i < count; ++i)
        {
            headPos += dir;

            Pos2D previousTrackingPos = headPos;
            for (int j = 0; j < 9; ++j)
            {
                int dx = previousTrackingPos.x - tailPos[j].x;
                int dy = previousTrackingPos.y - tailPos[j].y;
                if (dx >= 2)
                {
                    tailPos[j] += directions[(int)Direction::Right];
                    if (dy > 0) tailPos[j] += directions[(int)Direction::Up];
                    if (dy < 0) tailPos[j] += directions[(int)Direction::Down];
                }
                else if (dx <= -2)
                {
                    tailPos[j] += directions[(int)Direction::Left];
                    if (dy > 0) tailPos[j] += directions[(int)Direction::Up];
                    if (dy < 0) tailPos[j] += directions[(int)Direction::Down];
                }
                else if (dy >= 2)
                {
                    tailPos[j] += directions[(int)Direction::Up];
                    if (dx > 0) tailPos[j] += directions[(int)Direction::Right];
                    if (dx < 0) tailPos[j] += directions[(int)Direction::Left];
                }
                else if (dy <= -2)
                {
                    tailPos[j] += directions[(int)Direction::Down];
                    if (dx > 0) tailPos[j] += directions[(int)Direction::Right];
                    if (dx < 0) tailPos[j] += directions[(int)Direction::Left];
                }
                previousTrackingPos = tailPos[j];

                if (j == 8)
                {
                    visitedTailPositions.insert(tailPos[j]);
                }
            }
        }
    }

    return visitedTailPositions.size();
}
