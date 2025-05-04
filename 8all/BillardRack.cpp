#include "BillardRack.h"

#include <random>
#include <algorithm>

std::vector<BallPlacement> BillardRack::GenerateRack()
{
    std::vector<int> solids = { 1,2,3,4,5,6 };
	std::vector<int> stripes = {8,9,10,11,12,13,14 };

    std::vector<int> mixedBalls;

	int cornerLeft = solids.back(); solids.pop_back();
	int cornerRight = stripes.back(); stripes.pop_back();

	mixedBalls.insert(mixedBalls.end(), solids.begin(), solids.end());
	mixedBalls.insert(mixedBalls.end(), stripes.begin(), stripes.end());

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(mixedBalls.begin(), mixedBalls.end(), g);

	std::vector<BallPlacement> placements;


	int mixedIndex = 0;

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			BallPlacement placement;

			if (i == 0 && j == 0)
			{
				placement = { 0, i, j }; // ball 1 
			}
			else if (i == 2 && j == 1)
			{
				placement = { 7, i ,j }; // ball 8
			}
			else if (i == 1 && j == 0)
			{
				placement = {cornerLeft, i, j}; // corner left = solid balll
			}
			else if (i == 1 && j == 1)
			{
				placement = { cornerRight, i , j }; // corner right = stripe ball
			}
			else
			{
				placement = { mixedBalls[mixedIndex++], i, j };
			}

			placements.push_back(placement);
		}
	}


	return placements;
}
