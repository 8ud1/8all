#pragma once

#include <SDL3/SDL.h>
#include "Renderer.h"

class BoxCollider;
class CircleCollider;

class Collider
{
public :

	virtual ~Collider() = default;

	virtual bool CheckCollision(const Collider& other) const = 0;
	virtual bool CheckCollisionWithCircle(const CircleCollider& other) const = 0;
	virtual bool CheckCollisionWithBox(const BoxCollider& other) const = 0;

	virtual void DrawDebug(Renderer& renderer) const = 0;
};

