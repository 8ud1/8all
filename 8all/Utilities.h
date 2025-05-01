#pragma once

#include <SDL3/SDL.h>


enum class SceneType
{
	MAIN_MENU,
	GAME,
	RESULT
};

namespace Utilities
{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;


	const SDL_Color WHITE = { 255, 255, 255, 255 };
	const SDL_Color BLACK = { 0, 0, 0, 255 };

	
}