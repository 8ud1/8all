#pragma once

#include <SDL3/SDL.h>
#include "Scene.h"
#include "Utilities.h"

#include "ShotController.h"
#include "PauseCanvas.h"
#include "GameRules.h"
#include "GameUIManager.h"

class Ball;
class Game;
class Wall;
class UIBallSpin;


class InGameScreen : public Scene
{
private :
	
	//GameObjects
	Game& game;
	Ball* whiteBall = nullptr;
	std::vector<Ball*> balls;

	// Canvas
	std::unique_ptr<GameRules> gameRules;
	std::unique_ptr<GameUIManager> uiManager;

	void SetupTable();
	void SetupBalls();
	void SetupUI();

public:
	InGameScreen(Game& game) : game(game) {};
	void Enter() override;
	void Exit() override;

	void LogicUpdate(float deltaTime) override;
	void HandleInputs(const SDL_Event& event) override;
	void Render(Renderer& renderer) override;

};

