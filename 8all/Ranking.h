#pragma once

#include <string>
#include <vector>

struct RankingEntry
{
	std::string playerName;
	int score;

	RankingEntry(const std::string& name, int score)
		: playerName(name), score(score) {
	}
};
class Ranking
{
private:
	std::vector<RankingEntry> entries;
	std::string fileName;

public:
	Ranking(const std::string& fileName);

	const std::vector<RankingEntry> GetEntries() const;

	void Load();
	void Save();
	void Clear();

	bool AddEntry(const std::string& playerName, int score);
};

