#pragma once
#include <SDL3/SDL.h>

#include "PhysicsObject.h"

class RenderComponent;
class Rigidbody;
class CircleCollider;

class Ball : public PhysicsObject
{
private:
	CircleCollider* circleCollider;
public:
	std::unique_ptr<RenderComponent> renderComponent;


	Ball(std::string name, const SDL_FPoint& startPos);
	void Update(float deltaTime) override;
	void Render(Renderer& renderer) override;

	CircleCollider* Collider() const { return circleCollider; }
};

