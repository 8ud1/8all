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

public:
	InGameScreen(Game& game);
	void Enter();
	void Exit();
	void HandleInputs(const SDL_Event& event);
	void Render(Renderer& renderer);
};

