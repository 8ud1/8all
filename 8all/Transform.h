#pragma once
#include <SDL3/SDL.h>

class Transform
{
public:

	Transform() = default;
	SDL_FPoint position = { 0.0f,0.0f };
	float rotation = 0.0f;
	SDL_FPoint scale = { 1.0f, 1.0f };
};

