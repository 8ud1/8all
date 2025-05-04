#pragma once

#include "PhysicsObject.h"

class Rigidbody;
class BoxCollider;

class Wall : public PhysicsObject
{
private:
	BoxCollider* boxCollider;
	bool visible;
public:
	Wall(std::string name, const SDL_FPoint& startPos, const SDL_FPoint& size, bool visible);
	void Render(Renderer& renderer) override;

	BoxCollider* Collider() const { return boxCollider;}
};

