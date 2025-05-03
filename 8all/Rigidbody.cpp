#include "Rigidbody.h"

#include <cmath>

void Rigidbody::ApplyForce(SDL_FPoint& force)
{
	if (!isStatic)
	{
		velocity.x += force.x / mass;
		velocity.y += force.y / mass;
	}
}

void Rigidbody::Update(Transform& transform, float deltaTime)
{
	if (!isStatic)
	{

		transform.position.x = transform.position.x + velocity.x * deltaTime;
		transform.position.y += velocity.y * deltaTime;
		

		const float frictionFactor = 0.6f;

		velocity.x -= velocity.x * frictionFactor * deltaTime; 
		velocity.y -= velocity.y * frictionFactor * deltaTime; 


		if (std::abs(velocity.x) < 0.01f) velocity.x = 0.0f;
		if (std::abs(velocity.y) < 0.01f) velocity.y = 0.0f;
	}
}
