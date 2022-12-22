#include "aoc.h"

#include <cassert>

enum class Direction
{
    Right = 0,
    Down,
    Left,
    Up
};

struct Instruction
{
    enum class Type
    {
        Move,
        Rotate
    };

    Instruction(Type _type, int _value)
        : type(_type)
        , value(_value)
    {
    }

    Type type;
    int value;
};

using Pos2D = en::Vector2i;
using Pos3D = en::Vector3i;

void Parse(std::ifstream& file, std::vector<std::string>& lines, int& width, int& height, std::vector<Instruction>& instructions)
{
    bool stopAdd = false;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.size() == 0)
            stopAdd = true;

        if (!stopAdd)
        {
            lines.push_back(line);
            width = std::max(width, (int)line.size());
            height++;
        }
    }

    int start = 0;
    for (int i = 0; i < (int)line.size(); ++i)
    {
        char c = line[i];
        if (!(c >= '0' && c <= '9'))
        {
            instructions.emplace_back(Instruction::Type::Move, String::FromString<int>(line.substr(start, i - start)));
            instructions.emplace_back(Instruction::Type::Rotate, (c == 'R') ? 1 : -1);
            start = i + 1;
        }
    }
    instructions.emplace_back(Instruction::Type::Move, String::FromString<int>(line.substr(start, (int)line.size() - start)));
}

char CharFromDirection(Direction dir)
{
    switch (dir)
    {
    case Direction::Right: return '>';
    case Direction::Down: return 'v';
    case Direction::Left: return '<';
    case Direction::Up: return '^';
    }
    return ' ';
}

int day22part1(std::ifstream& file)
{
    int width = 0;
    int height = 0;
    std::vector<Instruction> instructions;
    std::vector<std::string> lines;
    Parse(file, lines, width, height, instructions);

    // Map
    char** map = new char* [width];
    for (int i = 0; i < width; ++i)
    {
        map[i] = new char[height];
    }
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            if (i < (int)lines[j].size())
            {
                map[i][j] = lines[j][i];
            }
            else
            {
                map[i][j] = ' ';
            }
        }
    }
    
    // Find start
    Pos2D pos(-1, 0);
    Direction dir = Direction::Right;
    for (int i = 0; i < width && pos.x == -1; ++i)
    {
        if (map[i][0] == '.')
        {
            pos.x = i;
        }
    }

    // Compute next pos
    auto computeNextPos = [](Pos2D p, Direction d, int width, int height)
    {
        Pos2D nextPos = p;
        switch (d)
        {
        case Direction::Right:
            nextPos.x = (nextPos.x + 1) % width;
            break;
        case Direction::Down:
            nextPos.y = (nextPos.y + 1) % height;
            break;
        case Direction::Left:
            nextPos.x = (nextPos.x - 1 + width) % width;
            break;
        case Direction::Up:
            nextPos.y = (nextPos.y - 1 + height) % height;
            break;
        }
        return nextPos;
    };

    // Do instructions
    for (auto& instruction : instructions)
    {
        if (instruction.type == Instruction::Type::Rotate)
        {
            if (instruction.value == 1) dir = (Direction)(((int)dir + 1) % 4);
            if (instruction.value == -1) dir = (Direction)(((int)dir - 1 + 4) % 4);
        }
        else if (instruction.type == Instruction::Type::Move)
        {
            for (int count = 0; count < instruction.value; ++count)
            {
                Pos2D nextPos = computeNextPos(pos, dir, width, height);
                char c = map[nextPos.x][nextPos.y];
                if (c == '#')
                {
                    break;
                }
                else if (c == ' ')
                {
                    do
                    {
                        nextPos = computeNextPos(nextPos, dir, width, height);
                    } while (map[nextPos.x][nextPos.y] == ' ');
                    if (map[nextPos.x][nextPos.y] == '#')
                    {
                        break;
                    }
                }

                pos = nextPos;
            }
        }
    }

    return 1000 * (pos.y + 1) + 4 * (pos.x + 1) + (int)dir;
}

struct CubeFace
{
    int index;
    Pos2D mapCoords;
    Pos2D faceCoords;
    Pos3D faceNormal;
    en::Matrix3f matrix;
    
    bool IsOnFace(const Pos2D& pos, int faceSize) const { return (pos.x >= mapCoords.x && pos.x < mapCoords.x + faceSize && pos.y >= mapCoords.y && pos.y < mapCoords.y + faceSize); }
    bool IsNormalValid() const { return faceNormal != en::Vector3i::Zero(); }
    Pos2D Convert(const Pos2D& localPos) const { return localPos + mapCoords; }
};

void ComputeCube(std::vector<CubeFace>& cubeFaces)
{
    auto FaceNormalsFinished = [](std::vector<CubeFace>& cubeFaces)
    {
        for (const CubeFace& face : cubeFaces)
            if (!face.IsNormalValid())
                return false;
        return true;
    };

    cubeFaces[0].matrix = en::Matrix3f::Identity();
    cubeFaces[0].faceNormal = en::Vector3i(0, 0, 1);

    do
    {
        for (int i = 0; i < (int)cubeFaces.size(); ++i)
        {
            CubeFace& face = cubeFaces[i];
            if (face.IsNormalValid())
            {
                for (int j = 0; j < (int)cubeFaces.size(); ++j)
                {
                    CubeFace& otherFace = cubeFaces[j];
                    if (i != j && !otherFace.IsNormalValid())
                    {
                        int dx = otherFace.faceCoords.x - face.faceCoords.x;
                        int dy = otherFace.faceCoords.y - face.faceCoords.y;

                        if ((dx == 1 && dy == 0) || (dx == -1 && dy == 0) || (dx == 0 && dy == 1) || (dx == 0 && dy == -1))
                        {
                            auto localDir = en::Vector3i(dx, -dy, 0);
                            otherFace.faceNormal = face.matrix.TransformDirection(localDir);
                            auto cross = face.faceNormal.CrossProduct(otherFace.faceNormal);
                            otherFace.matrix = face.matrix * en::Matrix3f::RotationAxis(cross, 90);
                        }

                        /*
                        if (otherFace.IsNormalValid())
                        {
                            std::cout << face.index << " -> " << otherFace.index << ": " << otherFace.faceNormal.x << " " << otherFace.faceNormal.y << " " << otherFace.faceNormal.z << std::endl;
                        }
                        */
                    }
                }
            }            
        }
    } while (!FaceNormalsFinished(cubeFaces));
}

CubeFace* GetFaceFromNormal(std::vector<CubeFace>& cube, const en::Vector3i& normal)
{
    for (auto& f : cube)
    {
        if (f.faceNormal == normal)
        {
            return &f;
        }
    }
    assert(false);
    return nullptr;
}

int day22part2(std::ifstream& file)
{
    int width = 0;
    int height = 0;
    std::vector<Instruction> instructions;
    std::vector<std::string> lines;
    Parse(file, lines, width, height, instructions);

    // Map
    char** map = new char* [width];
    char** mapDebug = new char* [width];
    char** mapCube = new char* [width];
    for (int i = 0; i < width; ++i)
    {
        map[i] = new char[height];
        mapDebug[i] = new char[height];
        mapCube[i] = new char[height];
    }

    int faceSize = 4;
    int cubeCol = width / faceSize;
    int cubeRow = height / faceSize;

    std::vector<CubeFace> cubeFaces;

    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            mapCube[i][j] = ' ';
            mapDebug[i][j] = ' ';
            if (i < (int)lines[j].size())
            {
                map[i][j] = lines[j][i];
                if (lines[j][i] != ' ')
                {
                    Pos2D faceCoords(i / faceSize, j / faceSize);

                    bool found = false;
                    for (const CubeFace& face : cubeFaces)
                    {
                        if (face.faceCoords.x == faceCoords.x && face.faceCoords.y == faceCoords.y)
                        {
                            found = true;
                            mapCube[i][j] = '0' + face.index;
                        }
                    }
                    if (!found)
                    {
                        cubeFaces.push_back(CubeFace());
                        cubeFaces.back().index = (int)cubeFaces.size() - 1;
                        cubeFaces.back().mapCoords = Pos2D(i, j);
                        cubeFaces.back().faceCoords = faceCoords;
                        mapCube[i][j] = '0' + cubeFaces.back().index;
                    }

                }
            }
            else
            {
                map[i][j] = ' ';
            }
        }
    }

    /*
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            std::cout << mapCube[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    */

    ComputeCube(cubeFaces);

    // Find start
    Pos2D pos(-1, 0);
    Direction dir = Direction::Right;
    for (int i = 0; i < width && pos.x == -1; ++i)
    {
        if (map[i][0] == '.')
        {
            pos.x = i;
        }
    }
    mapDebug[pos.x][pos.y] = CharFromDirection(dir);

    CubeFace* currentFace = &cubeFaces[0];
    Pos2D facePos(pos.x % faceSize, pos.y % faceSize);

    auto computeNextPos = [](CubeFace* currentFace, Pos2D facePos, Direction dir, CubeFace*& nextFace, Pos2D& nextFacePos, Direction& nextDir, int faceSize, std::vector<CubeFace>& cube)
    {
        nextFace = currentFace;
        nextFacePos = facePos;
        nextDir = dir;

        switch (dir)
        {
        case Direction::Right:
            nextFacePos.x = (nextFacePos.x + 1);
            if (nextFacePos.x >= faceSize)
            {
                auto localDir = en::Vector3i(1, 0, 0);
                auto nextFaceNormal = currentFace->matrix.TransformDirection(localDir);
                nextFace = GetFaceFromNormal(cube, nextFaceNormal);
                assert(nextFace != nullptr);

                auto t = currentFace->matrix.Inverse() * nextFace->matrix;
                auto cross = currentFace->faceNormal.CrossProduct(nextFace->faceNormal);
                if (t == en::Matrix3f::RotationAxis(cross, 90))
                {
                    nextFacePos.x = 0;
                }
                else
                {
                    nextFacePos.x = 0;
                }

            }
            break;
        case Direction::Down:
            nextFacePos.y = (nextFacePos.y + 1);
            if (nextFacePos.y >= faceSize)
            {
                auto localDir = en::Vector3i(0, -1, 0);
                auto nextFaceNormal = currentFace->matrix.TransformDirection(localDir);
                nextFace = GetFaceFromNormal(cube, nextFaceNormal);
                assert(nextFace != nullptr);

                auto t = currentFace->matrix.Inverse() * nextFace->matrix;
                auto cross = currentFace->faceNormal.CrossProduct(nextFace->faceNormal);
                if (t == en::Matrix3f::RotationAxis(cross, 90))
                {
                    nextFacePos.y = 0;
                }
                else
                {
                    nextFacePos.y = 0; // debug
                }

            }
            break;
        case Direction::Left:
            nextFacePos.x = (nextFacePos.x - 1);
            if (nextFacePos.x < 0)
            {
                auto localDir = en::Vector3i(-1, 0, 0);
                auto nextFaceNormal = currentFace->matrix.TransformDirection(localDir);
                nextFace = GetFaceFromNormal(cube, nextFaceNormal);
                assert(nextFace != nullptr);

            }
            break;
        case Direction::Up:
            nextFacePos.y = (nextFacePos.y - 1);
            if (nextFacePos.y < 0)
            {
                auto localDir = en::Vector3i(0, 1, 0);
                auto nextFaceNormal = currentFace->matrix.TransformDirection(localDir);
                nextFace = GetFaceFromNormal(cube, nextFaceNormal);
                assert(nextFace != nullptr);

            }
            break;
        }
    };

    // Do instructions
    for (auto& instruction : instructions)
    {
        if (instruction.type == Instruction::Type::Rotate)
        {
            if (instruction.value == 1) dir = (Direction)(((int)dir + 1) % 4);
            if (instruction.value == -1) dir = (Direction)(((int)dir - 1 + 4) % 4);
        }
        else if (instruction.type == Instruction::Type::Move)
        {
            for (int count = 0; count < instruction.value; ++count)
            {
                CubeFace* nextFace;
                Pos2D nextFacePos;
                Direction nextDir;

                computeNextPos(currentFace, facePos, dir, nextFace, nextFacePos, nextDir, faceSize, cubeFaces);                
                Pos2D nextPos = nextFace->Convert(nextFacePos);

                char c = map[nextPos.x][nextPos.y];
                if (c == '#')
                {
                    break;
                }
                else if (c == ' ')
                {
                    do
                    {
                        computeNextPos(currentFace, facePos, dir, nextFace, nextFacePos, nextDir, faceSize, cubeFaces); 
                        nextPos = nextFace->Convert(nextFacePos);
                    } while (map[nextPos.x][nextPos.y] == ' ');
                    if (map[nextPos.x][nextPos.y] == '#')
                    {
                        break;
                    }
                }

                currentFace = nextFace;
                facePos = nextFacePos;
                dir = nextDir;

                pos = currentFace->Convert(facePos);
                mapDebug[pos.x][pos.y] = CharFromDirection(dir);
            }
        }

        /*
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                std::cout << (mapDebug[i][j] != ' ') ? mapDebug[i][j] : map[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        */
    }

    return 1000 * (pos.y + 1) + 4 * (pos.x + 1) + (int)dir;
}
