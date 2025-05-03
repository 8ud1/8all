#pragma once

#include <SDL3/SDL.h>
#include "Scene.h"
#include "Utilities.h"

class Ball;
class Game;

class InGameScreen : public Scene
{
private :
	Game& game;

	Ball* ball;
	Ball* collider;

public:
	InGameScreen(Game& game);
	void Enter() override;
	void Exit() override;
	void HandleInputs(const SDL_Event& event) override;
	void Update(float deltaTime) override;
	void Render(Renderer& renderer) override;

};

