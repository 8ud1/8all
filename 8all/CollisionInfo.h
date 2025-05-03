#pragma once

#include <SDL3/SDL.h>

class PhysicsObject;

struct CollisionInfo
{
	SDL_FPoint normal = { 0.0f, 0.0f };
	float penetration = 0.0f;
};
