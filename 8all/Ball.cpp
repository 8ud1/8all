#include "Ball.h"

#include "Resources.h"
#include "Utilities.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "CircleCollider.h"

#include "Renderer.h"

Ball::Ball(std::string name , int id,const SDL_FPoint& startPos)
 :PhysicsObject(name,GameObjectType::Ball) , id(id)
{
	transform = std::make_unique<Transform>();
	transform->position = startPos;
	transform->scale = SDL_FPoint{ 30.0f,30.0f };

	//todo - passar por parametro el radio
	collider = std::make_unique<CircleCollider>(startPos,15.0f);
	circleCollider = static_cast<CircleCollider*>(collider.get());

	rigidbody = std::make_unique < Rigidbody>(transform.get(),false,0.3f);
}

void Ball::PhysicsUpdate(float deltaTime)
{	
	rigidbody->Update(*transform, deltaTime);
	circleCollider->center = transform->position;
}

void Ball::Render(Renderer& renderer)
{

	SDL_FPoint position
	{
		transform->position.x - 15.0f,
		transform->position.y - 15.0f,
	};

	renderer.DrawTextures(Resources::TEXTURE_BALLS, transform.get(), Resources::BALLS_ROWS_COLUMNS,Resources::BALLS_ROWS_COLUMNS, id);

	//circleCollider->DrawDebug(renderer);
}
