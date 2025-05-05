#pragma once

#include <SDL3/SDL.h>


#include "Game.h"
#include "GameRules.h"

#include "Renderer.h"
#include "PauseCanvas.h"
#include "UIBallSpin.h"
#include "ShotController.h"


class GameUIManager
{

private:

	GameRules* gameRules;
	std::unique_ptr<PauseCanvas> pauseCanvas;
	std::unique_ptr<UIBallSpin> ballSpinUi;
	std::unique_ptr<ShotController> shotController;

	PlayerInfo playerInfo[2];

	int currentPlayer{ 0 };

public:

	GameUIManager(Game& game, GameRules* gameRules, Ball* whiteball);

	void Update(float deltaTime);
	void Render(Renderer& renderer);

	ShotController* GetShotController() const { return shotController.get(); }
	UIBallSpin* GetBallSpinUI() { return ballSpinUi.get(); }
	PauseCanvas* GetPauseCanvas() { return pauseCanvas.get(); }

	void ShowGameOver(int winner);
	void TooglePause();

	void PrepareNextTurn(int nextPlayer, PlayerInfo& pi, PlayerInfo& pi2);
};

