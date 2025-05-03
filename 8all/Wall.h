#pragma once

#include "PhysicsObject.h"

class Rigidbody;
class BoxCollider;

class Wall : public PhysicsObject
{

private:
	BoxCollider* boxCollider;

public:

	Wall(std::string name, const SDL_FPoint& startPos, const SDL_FPoint& size);
	void Update(float deltaTime) override;
	void Render(Renderer& renderer) override;

	BoxCollider* Collider() const { return boxCollider;}
};

