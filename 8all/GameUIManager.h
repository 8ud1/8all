#pragma once

#include <SDL3/SDL.h>


#include "Game.h"
#include "GameRules.h"

#include "Renderer.h"
#include "PauseCanvas.h"
#include "UIBallSpin.h"
#include "ShotController.h"
#include "ResultsCanvas.h"


class GameUIManager
{

private:
	Game& game;

	GameRules* gameRules;
	std::unique_ptr<PauseCanvas> pauseCanvas;
	std::unique_ptr<UIBallSpin> ballSpinUi;
	std::unique_ptr<ShotController> shotController;
	std::unique_ptr<ResultsCanvas> results;

	PlayerInfo playerInfo[2];

	int currentPlayer{ 0 };

public:

	GameUIManager(Game& game, GameRules* gameRules, Ball* whiteball);

	void Update(float deltaTime);
	void HandleInputs(const SDL_Event& event);
	void Render(Renderer& renderer);

	ShotController* GetShotController() const { return shotController.get(); }
	UIBallSpin* GetBallSpinUI() { return ballSpinUi.get(); }
	PauseCanvas* GetPauseCanvas() { return pauseCanvas.get(); }

	void ShowGameOver(int winner, bool ball8Fail = false);
	void TooglePause();

	void PrepareNextTurn(int nextPlayer, PlayerInfo& pi, PlayerInfo& pi2);
};

