#pragma once
#include "Collider.h"



class BoxCollider : public Collider
{
protected:

public:

	SDL_FRect rect;

	BoxCollider(const SDL_FRect& rect) : rect(rect) {}

	bool CheckCollision(const Collider& other, CollisionInfo& info) const override;
	bool CheckCollisionWithCircle(const CircleCollider& other, CollisionInfo& info) const override;
	bool CheckCollisionWithBox(const BoxCollider& other, CollisionInfo& info) const override;


	void DrawDebug(Renderer& renderer) const override;

};

