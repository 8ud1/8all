#pragma once
#include <SDL3/SDL.h>

#include "Scene.h"
#include "Utilities.h"

class Game;
class Ball;

class MainMenu : public Scene
{
private :
	Game& game;
public:
	MainMenu(Game& game);
	void Enter() override;
	void Exit() override;
	void HandleInputs(const SDL_Event& event) override;	

	void Render(Renderer& renderer) override;
};

