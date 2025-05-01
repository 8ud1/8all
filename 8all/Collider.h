#pragma once

#include <SDL3/SDL.h>

class Collider
{
public :
	SDL_FPoint center;
	float radius;

	bool Intersects(const Collider& other) const;
};

