#include "aoc.h"

enum class RPC
{
    Rock = 1,
    Paper = 2,
    Scissors = 3
};

enum class Result
{
    Lost = 0,
    Draw = 3,
    Win = 6
};

Result match(RPC mainPlayer, RPC opponent)
{
    if (mainPlayer == opponent)
    {
        return Result::Draw;
    }
    else if ((mainPlayer == RPC::Rock && opponent == RPC::Scissors) || (mainPlayer == RPC::Paper && opponent == RPC::Rock) || (mainPlayer == RPC::Scissors && opponent == RPC::Paper))
    {
        return Result::Win;
    }
    else
	{
		return Result::Lost;
    }
}

RPC determine(Result expectedResult, RPC opponent)
{
	if (expectedResult == Result::Draw)
	{
        return opponent;
	}
    else if (expectedResult == Result::Win)
    {
        if (opponent == RPC::Rock) return RPC::Paper;
        else if (opponent == RPC::Paper) return RPC::Scissors;
        else return RPC::Rock;        
	}
	else
	{
		if (opponent == RPC::Rock) return RPC::Scissors;
		else if (opponent == RPC::Paper) return RPC::Rock;
		else return RPC::Paper;
	}
}

int day2part1(std::ifstream& file)
{
    int result = 0;

    std::string line;
    while (std::getline(file, line))
    {
        char opponent = line[0];
        RPC opponentRPC;
        if (opponent == 'A') opponentRPC = RPC::Rock;
        else if (opponent == 'B') opponentRPC = RPC::Paper;
        else opponentRPC = RPC::Scissors;

		char reco = line[2];
		RPC recoRPC;
		if (reco == 'X') recoRPC = RPC::Rock;
		else if (reco == 'Y') recoRPC = RPC::Paper;
		else recoRPC = RPC::Scissors;

		int a = (int)recoRPC;
		int b = (int)match(recoRPC, opponentRPC);
		result += (a + b);
    }

    return result;
}

int day2part2(std::ifstream& file)
{
    int result = 0;

	std::string line;
	while (std::getline(file, line))
	{
		char opponent = line[0];
		RPC opponentRPC;
		if (opponent == 'A') opponentRPC = RPC::Rock;
		else if (opponent == 'B') opponentRPC = RPC::Paper;
		else opponentRPC = RPC::Scissors;

		char reco = line[2];
        Result recoResult;
        if (reco == 'X') recoResult = Result::Lost;
        else if (reco == 'Y') recoResult = Result::Draw;
		else recoResult = Result::Win;

        int a = (int)recoResult;
        int b = (int)determine(recoResult, opponentRPC);
        result += (a + b);
	}

    return result;
}
