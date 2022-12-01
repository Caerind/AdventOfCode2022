#include "aoc.h"

int main(int argc, char** argv)
{
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    int day = ltm.tm_mday;

    bool hasTest1Value = false;
    int test1Value = 0;
    bool hasTest2Value = false;
    int test2Value = 0;

    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-day") == 0 && i + 1 < argc)
        {
            day = FromString<int>(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-test1") == 0 && i + 1 < argc)
        {
            hasTest1Value = true;
            test1Value = FromString<int>(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-test2") == 0 && i + 1 < argc)
        {
            hasTest2Value = true;
            test2Value = FromString<int>(argv[i + 1]);
        }
    }

    std::string filePath = StringFormat("day%d.data", day);
    std::string testFilePath = StringFormat("day%d-test.data", day);

    std::cout << "-------------------" << std::endl;
    std::cout << "Day: " << day << std::endl;
    std::cout << std::endl;

    bool testPassed = true;
    {
        std::cout << "-------------------" << std::endl;
        std::cout << "TestFile: " << testFilePath << std::endl;
        std::ifstream testFile(testFilePath.c_str());
        if (testFile)
        {
            int result1 = solve(day, 1, testFile);
            if (hasTest1Value)
            {
                bool result = (result1 == test1Value);
                testPassed = (testPassed && result);
                std::cout << "Part1: " << result1 << " => " << (result ? "PASSED" : "FAILED") << std::endl;
            }
            else
            {
                std::cout << "Part1: " << result1 << std::endl;
            }

            testFile.clear();
            testFile.seekg(0);

            int result2 = solve(day, 2, testFile);
            if (hasTest2Value)
            {
                bool result = (result2 == test2Value);
                testPassed = (testPassed && result);
                std::cout << "Part2: " << result2 << " => " << (result ? "PASSED" : "FAILED") << std::endl;
            }
            else
            {
                std::cout << "Part2: " << result2 << std::endl;
            }
        }
        else
        {
            std::cerr << "File not found" << std::endl;
        }
    }

    if (testPassed)
    {
        std::cout << std::endl;

        std::cout << "-------------------" << std::endl;
        std::cout << "File: " << filePath << std::endl;
        std::ifstream file(filePath.c_str());
        if (file)
        {
            std::cout << "Part1: " << solve(day, 1, file) << std::endl;
            file.clear();
            file.seekg(0);
            std::cout << "Part2: " << solve(day, 2, file) << std::endl;
        }
        else
        {
            std::cerr << "File not found" << std::endl;
        }
    }

    return 0;
}
