#include "Rigidbody.h"

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
		
		// Apply damping
		velocity.x *= 0.98f; // Damping factor
		velocity.y *= 0.98f; // Damping factor
	}
}
