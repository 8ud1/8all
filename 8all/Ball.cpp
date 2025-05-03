#include "Ball.h"

#include "Resources.h"
#include "Utilities.h"

#include "Transform.h"
#include "RenderComponent.h"
#include "Rigidbody.h"
#include "CircleCollider.h"

Ball::Ball(std::string name, const SDL_FPoint& startPos)
 :GameObject(name,GameObjectType::Ball)
{
	transform = std::make_unique<Transform>();
	transform->position = startPos;

	SDL_FRect rect = { 0.0f, 0.0f, 50.0f, 50.0f };
	renderComponent = std::make_unique<RenderComponent>(Resources::BALL, rect);

	//todo - passar por parametro el radio
	collider = std::make_unique<CircleCollider>(startPos,30.0f);

	rigidbody = std::make_unique < Rigidbody>();
	rigidbody->mass = 1.0f;


}

void Ball::Update(float deltaTime)
{
	rigidbody->Update(*transform, deltaTime);
	collider->center = transform->position;

}

void Ball::Render(Renderer& renderer)
{
	renderComponent->Render(renderer, transform->position);

	collider->DrawDebug(renderer);
}
