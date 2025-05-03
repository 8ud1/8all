#pragma once
#include <SDL3/SDL.h>
#include "GameObject.h"

class RenderComponent;
class Rigidbody;
class CircleCollider;

class Ball : public GameObject
{	
public:
	std::unique_ptr<RenderComponent> renderComponent;
	std::unique_ptr<Rigidbody> rigidbody;
	std::unique_ptr<CircleCollider> collider;

	Ball(std::string name, const SDL_FPoint& startPos);
	void Update(float deltaTime) override;
	void Render(Renderer& renderer) override;
};

