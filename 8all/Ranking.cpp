#include "Ranking.h"

#include <fstream>
#include <iostream>
#include <algorithm>

#include "Resources.h"

Ranking::Ranking(const std::string& fileName)
	:fileName(fileName)
{
	Load();
}

void Ranking::Load()
{
	entries.clear();

	std::ifstream inputFile(fileName);

	if (!inputFile.is_open())
	{
		std::ofstream createFile(fileName);
		createFile.close();
		std::cout << "Ranking file created: " << fileName << std::endl;
		return;
	}

	std::string playerName;
	int score;

	while (inputFile >> playerName >> score)
	{
		entries.emplace_back(playerName, score);
	}

	inputFile.close();
}

void Ranking::Save()
{
	std::ofstream outputFile(fileName);

	for (const auto& entry : entries)
	{
		outputFile << entry.playerName << " " << entry.score << std::endl;
	}

	outputFile.close();
}

bool Ranking::AddEntry(const std::string& playerName, int score)
{
	bool result = false;

	if (entries.empty() || score  > entries.front().score)
	{
		result = true;
	}
	entries.emplace_back(playerName, score);

	std::sort(entries.begin(), entries.end(), [](const RankingEntry& a, const RankingEntry& b) {
		return b.score < a.score;
		});


	Save();

	return result;
	
}

const std::vector<RankingEntry>& Ranking::GetEntries() const
{
	return entries;
}
