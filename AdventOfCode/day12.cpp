#include "aoc.h"

#include <queue>
#include <unordered_map>

struct Pos2D
{
    int x{ 0 };
    int y{ 0 };

    Pos2D() = default;
    Pos2D(int _x, int _y) : x(_x), y(_y) {}
}; 

struct NodeLink
{
    int from{ 0 };
    int to{ 0 };
    float cost{ 0.0f };
    
    NodeLink() = default;
    NodeLink(int _from, int _to, float _cost)
        : from(_from)
        , to(_to)
        , cost(_cost)
    {
    }
};

struct Grid2D
{
    char* grid;
    int width;
    int height;

    static constexpr int hash = 10000;

    Grid2D(const std::vector<std::string>& map)
    {
        width = (int)map[0].size();
        height = (int)map.size();
        grid = (char*)malloc(width * height * sizeof(char));

        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                char m = map[j][i];
                if (m == 'S') m = 'a';
                if (m == 'E') m = 'z';
                SetValue(Pos2D(i, j), m);
            }
        }
    }

    Pos2D GetSize() const
    {
        return Pos2D(width, height);
    }

    bool IsValidCoords(const Pos2D& coords) const
    {
        const Pos2D size = GetSize();
        return coords.x >= 0 && coords.x < size.x&& coords.y >= 0 && coords.y < size.y;
    }

    void SetValue(const Pos2D& coords, char value)
    {
        if (IsValidCoords(coords))
        {
            grid[coords.x + coords.y * width] = value;
        }
    }

    char GetValue(const Pos2D& coords) const
    {
        return grid[coords.x + coords.y * width];
    }

    std::vector<NodeLink> GetNeighbors(int node) const
    {
        std::vector<NodeLink> links;
        links.reserve(4);

        const Pos2D coords = GetCoordsFromNode(node);
        char currentHeight = GetValue(coords);

        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                if (i == 0 && j == 0)
                    continue;

                // No diagonal moves
                if (i != 0 && j != 0)
                    continue;

                Pos2D neighbor(coords.x + i, coords.y + j);
                if (IsValidCoords(neighbor))
                {
                    char newHeight = GetValue(neighbor);

                    float cost = 0.0f;
                    if (newHeight > currentHeight + 1)
                        cost = 999999.9f;
                    else
                        cost = 1.0f;

                    links.push_back(NodeLink(node, GetNodeFromCoords(neighbor), cost));
                }
            }
        }

        return links;
    }

    bool IsValidNode(int node) const
    {
        return IsValidCoords(GetCoordsFromNode(node));
    }

    int GetNodeFromCoords(const Pos2D& coords) const
    {
        return coords.y * hash + coords.x;
    }

    Pos2D GetCoordsFromNode(int node) const
    {
        int x = node % hash;
        int y = node / hash;
        return Pos2D(x, y);
    }
};

struct PrioNodeCost
{
    int node;
    float cost;

    PrioNodeCost(int _node, float _cost)
        : node(_node)
        , cost(_cost)
    {
    }

    bool operator<(const PrioNodeCost& other) const
    {
        return cost > other.cost;
    }
};

struct AStar
{
    const Grid2D* graph{ nullptr };
    int startNode;
    int endNode;
    std::vector<Pos2D> path;
    bool finished{ false };

    std::unordered_map<int, int> cameFrom;
    std::unordered_map<int, float> costSoFar;
    std::priority_queue<PrioNodeCost> frontier;

    void Start(const Grid2D& grid, const Pos2D& start, const Pos2D& end)
    {
        graph = &grid;
        startNode = grid.GetNodeFromCoords(start);
        endNode = grid.GetNodeFromCoords(end);
        finished = false;

        // Check validity
        if (!graph->IsValidNode(startNode) || !graph->IsValidNode(endNode))
        {
            finished = true;
        }
        if (!finished && startNode == endNode)
        {
            finished = true;
        }
        if (finished)
        {
            return;
        }
        
        // Starting point
        cameFrom[startNode] = startNode;
        costSoFar[startNode] = 0.0f;
        frontier.push(PrioNodeCost(startNode, 0.0f));
    }

    void Iteration()
    {
        if (!finished && frontier.size() > 0)
        {
            PrioNodeCost current = frontier.top();
            frontier.pop();
            if (current.node == endNode)
            {
                FinalizePath();
                finished = true;
            }

            std::vector<NodeLink> links = graph->GetNeighbors(current.node);
            if (links.size() > 0)
            {
                for (const NodeLink& link : links)
                {
                    int nextNode = link.to;
                    float cost = link.cost;
                    float newCost = costSoFar[current.node] + cost;
                    if (costSoFar.find(nextNode) == costSoFar.end() || newCost < costSoFar[nextNode])
                    {
                        float priority = newCost;
                        cameFrom[nextNode] = current.node;
                        costSoFar[nextNode] = newCost;
                        frontier.push(PrioNodeCost(nextNode, priority));
                    }
                }
            }
        }
        else
        {
            finished = true;
        }
    }

    void FinalizePath()
    {
        int currentNode = endNode;

        std::vector<Pos2D> temp;
        while (currentNode != startNode)
        {
            temp.push_back(graph->GetCoordsFromNode(currentNode));
            currentNode = cameFrom[currentNode];
        }

        path.reserve(temp.size());
        for (int i = (int)temp.size() - 1; i >= 0; --i)
        {
            path.push_back(temp[i]);
        }

        finished = true;
    }
};


int day12part1(std::ifstream& file)
{
    std::string line;
    std::vector<std::string> map;
    while (std::getline(file, line))
        map.push_back(line);

    Pos2D start, end;
    for (int j = 0; j < map.size(); ++j)
    {
        for (int i = 0; i < map[j].size(); ++i)
        {
            char m = map[j][i];
            if (m == 'S') start = Pos2D(i, j);
            if (m == 'E') end = Pos2D(i, j);
        }
    }

    const Grid2D grid(map);
    AStar astar;
    astar.Start(grid, start, end);
    while (!astar.finished)
    {
        astar.Iteration();
    }
    return (int)astar.path.size();
}

int day12part2(std::ifstream& file)
{
    std::string line;
    std::vector<std::string> map;
    while (std::getline(file, line))
        map.push_back(line);

    Pos2D start;
    Pos2D end;
    for (int j = 0; j < map.size(); ++j)
    {
        for (int i = 0; i < map[j].size(); ++i)
        {
            char m = map[j][i];
            if (m == 'S') start = Pos2D(i, j);
            if (m == 'E') end = Pos2D(i, j);
        }
    }

    std::vector<int> paths;
    const Grid2D grid(map);

    for (int j = 0; j < map.size(); ++j)
    {
        //for (int i = 0; i < map[j].size(); ++i)
        int i = 0; // Reading the input show that only the first column can be used
        {
            char m = map[j][i];
            if (m == 'a' || m == 'S')
            {
                AStar astar;
                astar.Start(grid, Pos2D(i,j), end);
                while (!astar.finished)
                {
                    astar.Iteration();
                }
                if (astar.path.size() > 0)
                {
                    paths.push_back((int)astar.path.size());
                }
            }
        }
    }

    std::sort(paths.begin(), paths.end(), [](int a, int b) { return a < b; });

    return (int)paths[0];
}
