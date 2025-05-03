#pragma once
#include "Collider.h"



class BoxCollider : public Collider
{

public:

	SDL_FRect rect;

	BoxCollider(const SDL_FRect& rect) : rect(rect) {}

	bool CheckCollision(const Collider& other) const override;
	bool CheckCollisionWithCircle(const CircleCollider& other) const override;
	bool CheckCollisionWithBox(const BoxCollider& other) const override;


	void DrawDebug(Renderer& renderer) const override;

};

