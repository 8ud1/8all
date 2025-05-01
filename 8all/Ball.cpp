#include "Ball.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "RenderComponent.h"

#include "Resources.h"

Ball::Ball(const SDL_FPoint& startPos)
 :GameObject("ball")
{
	transform = std::make_unique<Transform>();
	transform->position = startPos;


	SDL_FRect rect = { 0.0f, 0.0f, 50.0f, 50.0f };
	renderComponent = std::make_unique<RenderComponent>(Resources::BALL, rect);

	rigidBody = std::make_unique < Rigidbody>();
	rigidBody->mass = 1.0f;


}

void Ball::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}
