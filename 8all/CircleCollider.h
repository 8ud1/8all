#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:

	SDL_FPoint center;
	float radius;

	CircleCollider(SDL_FPoint center, float radius) : center(center) , radius(radius) {}

	bool CheckCollision(const Collider& other) const override;
	bool CheckCollisionWithCircle(const CircleCollider& other) const override;
	bool CheckCollisionWithBox(const BoxCollider& other) const override;

	void DrawDebug(Renderer& renderer) const override;
};

