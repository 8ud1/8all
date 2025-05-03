#include "Ball.h"

#include "Resources.h"
#include "Utilities.h"

#include "Transform.h"
#include "RenderComponent.h"
#include "Rigidbody.h"
#include "CircleCollider.h"



Ball::Ball(std::string name , const SDL_FPoint& startPos)
 :PhysicsObject(name,GameObjectType::Ball)
{

	transform = std::make_unique<Transform>();
	transform->position = startPos;
	transform->scale = SDL_FPoint{ 50.0f,50.0f };

	SDL_FRect rect = { 0.0f, 0.0f, 50.0f, 50.0f };
	renderComponent = std::make_unique<RenderComponent>(Resources::BALL, rect);

	//todo - passar por parametro el radio
	collider = std::make_unique<CircleCollider>(startPos,25.0f);
	circleCollider = static_cast<CircleCollider*>(collider.get());

	rigidbody = std::make_unique < Rigidbody>();
	rigidbody->mass = 1.0f;
}

void Ball::Update(float deltaTime)
{
	rigidbody->Update(*transform, deltaTime);
	circleCollider->center = transform->position;
}

void Ball::Render(Renderer& renderer)
{

	SDL_FPoint position
	{
		transform->position.x - 25.0f,
		transform->position.y - 25.0f,
	};

	renderComponent->Render(renderer, position);
	circleCollider->DrawDebug(renderer);
}
