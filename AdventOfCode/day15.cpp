#include "aoc.h"

#include <set>

struct Pos2D
{
    int x{0};
    int y{0};

    Pos2D() = default;
    Pos2D(int _x, int _y) : x(_x), y(_y) {}
};

struct Pair
{
    Pos2D s;
    Pos2D b;
    int d{ 0 };
    
    Pos2D min;
    Pos2D max;
};

int ManhattanDistance(const Pos2D& a, const Pos2D& b)
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void parse(std::ifstream& file, std::vector<Pair>& pairs)
{
    std::string line;
    while (std::getline(file, line))
    {
        line.erase(0, std::string("Sensor at x=").size());
        std::string s1 = line.substr(0, line.find_first_of(','));
        line.erase(0, s1.size() + std::string(", y=").size());
        std::string s2 = line.substr(0, line.find_first_of(':'));
        line.erase(0, s2.size() + std::string(": closest beacon is at x=").size());
        std::string s3 = line.substr(0, line.find_first_of(','));
        line.erase(0, s3.size() + std::string(", y=").size());
        std::string s4 = line;

        Pair p;
        p.s = Pos2D(String::FromString<int>(s1), String::FromString<int>(s2));
        p.b = Pos2D(String::FromString<int>(s3), String::FromString<int>(s4));
        p.d = ManhattanDistance(p.s, p.b);
        p.min = Pos2D(p.s.x - p.d, p.s.y - p.d);
        p.max = Pos2D(p.s.x + p.d, p.s.y + p.d);

        pairs.push_back(p);
    }
}

struct Range
{
    int min;
    int max;
};

void rangesInLine(const std::vector<Pair>& pairs, int y, std::vector<Range>& ranges)
{
    for (const auto& p : pairs)
    {
        int bd = p.d;
        int rd = ManhattanDistance(p.s, Pos2D(p.s.x, y));

        int d = bd - rd;
        if (d > 0)
        {
            Range r;
            r.min = p.s.x - d;
            r.max = p.s.x + d;
            ranges.push_back(r);
        }
    }

    //std::sort(pairs.begin(), pairs.end(), [](const Range& a, const Range& b) { return a.min < b.min; });

    for (int i = 0; i < ranges.size() - 1; )
    {
        Range& currentRange = ranges[i];
        Range& nextRange = ranges[i + 1];
        if (currentRange.max >= nextRange.min && currentRange.max < nextRange.max)
        {
            currentRange.max = nextRange.max;
            ranges.erase(ranges.begin() + i + 1);
        }
        else
        {
            ++i;
        }
    }
}

int day15part1(std::ifstream& file)
{
    std::vector<Pair> pairs;
    parse(file, pairs);

    std::vector<Range> ranges;
    rangesInLine(pairs, 10, ranges);

    int result = 0;
    for (const auto& r : ranges)
        result += (r.max - r.min + 1);

    return result;
}

struct Region
{
    Pos2D min;
    Pos2D max;
    std::vector<int> overlaps;
    int cells;
}; 

template <typename T>
bool IsInBounds(const T& value, const T& low, const T& high) {
    return !(value < low) && (value < high);
}

bool regionOverlap(const Pos2D& min, const Pos2D& max, const Pair& pair)
{
    bool x1 = IsInBounds(pair.min.x, min.x, max.x);
    bool x2 = IsInBounds(pair.max.x, min.x, max.x);

    bool y1 = IsInBounds(pair.min.y, min.y, max.y);
    bool y2 = IsInBounds(pair.max.y, min.y, max.y);

    return (x1 || x2) && (y1 || y2);
}

int day15part2(std::ifstream& file)
{
    std::vector<Pair> pairs;
    parse(file, pairs);

    std::cout << "Pairs: " << pairs.size() << std::endl;
    std::sort(pairs.begin(), pairs.end(), [](const Pair& a, const Pair& b) { return a.d < b.d; });

    std::vector<Region> regions;
    for (int i = 0; i < pairs.size(); ++i)
    {
        for (int j = i + 1; j < pairs.size(); ++j)
        {
            if (regionOverlap(pairs[i].min, pairs[i].max, pairs[j]))
            {
                Region newSubRegion;
                newSubRegion.min = Pos2D(std::max(pairs[i].min.x, pairs[j].min.x), std::max(pairs[i].min.y, pairs[j].min.y));
                newSubRegion.max = Pos2D(std::min(pairs[i].max.x, pairs[j].max.x), std::min(pairs[i].max.y, pairs[j].max.y));
                newSubRegion.cells = (newSubRegion.max.x - newSubRegion.min.x + 1) * (newSubRegion.max.y - newSubRegion.min.y + 1);
                regions.push_back(std::move(newSubRegion));
                regions.back().overlaps.push_back(i);
                regions.back().overlaps.push_back(j);
            }
        }
    }

    for (int i = 0; i < regions.size(); ++i)
    {
        const Region& r = regions[i];
        for (int j = 0; j < pairs.size(); ++j)
        {
            bool hasPair = false;
            for (int k = 0; k < r.overlaps.size() && !hasPair; ++k)
            {
                if (j == r.overlaps[k])
                    hasPair = true;
            }
            if (!hasPair && regionOverlap(r.min, r.max, pairs[j]))
            {
                Region newSubRegion;
                newSubRegion.min = Pos2D(std::max(r.min.x, pairs[j].min.x), std::max(r.min.y, pairs[j].min.y));
                newSubRegion.max = Pos2D(std::min(r.max.x, pairs[j].max.x), std::min(r.max.y, pairs[j].max.y));
                newSubRegion.cells = (newSubRegion.max.x - newSubRegion.min.x + 1) * (newSubRegion.max.y - newSubRegion.min.y + 1);
                regions.push_back(std::move(newSubRegion));
                for (int p : r.overlaps)
                    regions.back().overlaps.push_back(p);
                regions.back().overlaps.push_back(j);
            }
        }
    }    

    std::cout << "Regions: " << regions.size() << std::endl;
    std::sort(regions.begin(), regions.end(), [](const Region& a, const Region& b) { return a.overlaps.size() > b.overlaps.size(); });

    Pos2D foundPos;
    for (const Region& r : regions)
    {
        if (r.cells == 1)
        {
            std::cout << r.min.x << " " << r.min.y << std::endl;
            foundPos = r.min;
        }
    }

    return foundPos.x * 4000000 + foundPos.y;
}
