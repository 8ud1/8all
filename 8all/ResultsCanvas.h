#pragma once
#include <SDL3/SDL.h>

#include <string>>
#include "Canvas.h"
#include "Game.h"

#include "Ranking.h"
#include "GameRules.h"

class ResultsCanvas: public Canvas
{

private:
	Game& game;
	std::string inputName;
	int winner = -1;
	PlayerInfo winnerInfo;
	bool ball8;
	int score;

	std::vector<RankingEntry> rankingEntries;
	

	int CalculateFinalScore();
	void SaveScore();

protected:
	void InitCanvas();
public:

	ResultsCanvas(Game& gameRef, bool startActive = false);

	void Update(float deltaTime) override;
	void Render(Renderer& renderer) override;
	void HandleInputs(const SDL_Event& event) override;
	void ShowResults(int winner,PlayerInfo playerInfo,bool ball8Fail);

	void GoToMainMenu();

};

