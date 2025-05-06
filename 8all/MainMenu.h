#pragma once
#include <SDL3/SDL.h>
#include <vector>

#include "Scene.h"
#include "Utilities.h"

#include "Ranking.h"
class Game;
class Ball;

class MainMenu : public Scene
{
private :
	Game& game;
	std::vector<RankingEntry> rankingEntries;

	void LoadRanking();
public:
	MainMenu(Game& game);
	void Enter() override;
	void Exit() override;
	void HandleInputs(const SDL_Event& event) override;	

	void ResetRanking();
	void Render(Renderer& renderer) override;
};

