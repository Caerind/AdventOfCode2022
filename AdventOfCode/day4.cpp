#include "aoc.h"

int day4part1(std::ifstream& file)
{
    int result = 0;

    std::string line;
    while (std::getline(file, line))
    {
        std::string firstInput, secondInput, thirdInput, fourthInput;
		String::Split(line, firstInput, "-");
		String::Split(line, secondInput, ",");
		String::Split(line, thirdInput, "-");
        fourthInput = line;
        int a = String::FromString<int>(firstInput);
        int b = String::FromString<int>(secondInput);
        int c = String::FromString<int>(thirdInput);
        int d = String::FromString<int>(fourthInput);

        if (a <= c && d <= b) // cd is contained in ab
		{
			result++;
		}
        else if (c <= a && b <= d) // ab is contained in cd
		{
			result++;
		}
    }

    return result;
}

int day4part2(std::ifstream& file)
{
    int result = 0;

	std::string line;
	while (std::getline(file, line))
	{
		std::string firstInput, secondInput, thirdInput, fourthInput;
		String::Split(line, firstInput, "-");
		String::Split(line, secondInput, ",");
		String::Split(line, thirdInput, "-");
		fourthInput = line;
		int a = String::FromString<int>(firstInput);
		int b = String::FromString<int>(secondInput);
		int c = String::FromString<int>(thirdInput);
		int d = String::FromString<int>(fourthInput);

		if ((a <= c && b >= c) || (a <= d && b >= d)) // cd is overlapping ab
		{
			result++;
		}
		else if ((c <= a && d >= a) || (c <= b && d >= b)) // ab is overlapping cd
		{
			result++;
		}
	}

    return result;
}
