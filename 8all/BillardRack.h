#pragma once
#include <vector>

struct BallPlacement
{
	int number;
	int row;
	int column;
};


class BillardRack
{
public:
	std::vector<BallPlacement> GenerateRack();
};

