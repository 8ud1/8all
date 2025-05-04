#pragma once

#include <SDL3/SDL.h>
#include "Renderer.h"
#include "CollisionInfo.h"

class BoxCollider;
class CircleCollider;

class Collider
{
public :
	bool isTrigger = false;
	virtual ~Collider() = default;

	virtual bool CheckCollision(const Collider& other, CollisionInfo& info) const = 0;
	virtual bool CheckCollisionWithCircle(const CircleCollider& other, CollisionInfo& info) const = 0;
	virtual bool CheckCollisionWithBox(const BoxCollider& other, CollisionInfo& info) const = 0;

	virtual void DrawDebug(Renderer& renderer) const = 0;
};

