#pragma once
#include <SDL3/SDL.h>
#include "PhysicsObject.h"

class Rigidbody;
class CircleCollider;

class Ball : public PhysicsObject
{
private:

	int id;
	CircleCollider* circleCollider;
public:
	Ball(std::string name, int id,  const SDL_FPoint& startPos);

	int GetId() const { return id; }
	CircleCollider* Collider() const { return circleCollider; }

	void PhysicsUpdate(float deltaTime) override;
	void Render(Renderer& renderer) override;
};

