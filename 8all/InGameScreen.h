#pragma once

#include <SDL3/SDL.h>
#include "Scene.h"
#include "Utilities.h"

class Ball;
class Game;
class Wall;
class PauseCanvas;

class InGameScreen : public Scene
{
private :
	
	//GameObjects
	Game& game;
	Ball* whiteBall = nullptr;

	std::vector<Ball*> balls;


	// Canvas
	std::unique_ptr<PauseCanvas> pauseCanvas;

	int ballCount = 0;

	bool isCharging = false;
	SDL_FPoint chargingVector = SDL_FPoint{ 0.0f,0.0f };

	void CreateBalls();

	void CreateHoles();
	void CreateWalls();

	void OnHoleTrigger(PhysicsObject* obj);

public:
	InGameScreen(Game& game);
	void Enter() override;
	void Exit() override;

	void LogicUpdate(float deltaTime) override;
	void HandleInputs(const SDL_Event& event) override;
	void Render(Renderer& renderer) override;

};

