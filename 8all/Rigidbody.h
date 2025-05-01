#pragma once

#include <SDL3/SDL.h>
#include "Transform.h"

class Rigidbody
{
public :

	Rigidbody() = default;
	SDL_FPoint velocity = { 0.0f, 0.0f };
	float mass = 1.0f;
	bool isStatic = false;

	void ApplyForce(SDL_FPoint& force);
	void Update(Transform* transform, float deltaTime);
};

