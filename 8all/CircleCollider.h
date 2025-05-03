#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:

	SDL_FPoint center;
	float radius;

	CircleCollider(SDL_FPoint center, float radius) : center(center) , radius(radius) {}

	bool CheckCollision(const Collider& other, CollisionInfo& info) const override;
	bool CheckCollisionWithCircle(const CircleCollider& other, CollisionInfo& info) const override;
	bool CheckCollisionWithBox(const BoxCollider& other, CollisionInfo& info) const override;

	void DrawDebug(Renderer& renderer) const override;
};

