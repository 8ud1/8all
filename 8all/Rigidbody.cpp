#include "Rigidbody.h"

#include <cmath>

float Rigidbody::GetSpeed()
{
	return sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}

Rigidbody::Rigidbody(Transform* transform,bool isStatic,float mass)
	: transform(transform), mass(mass), isStatic(isStatic) 
{}

void Rigidbody::SetStatic(bool isStatic)
{
	this->isStatic = isStatic;
	SetVelocity(SDL_FPoint{ 0.0f, 0.0f });
}

void Rigidbody::ApplyForce(SDL_FPoint& force)
{
	if (!isStatic)
	{
		velocity.x += force.x / mass;
		velocity.y += force.y / mass;
	}
}

void Rigidbody::AttractToPoint(SDL_FPoint& point, float force)
{
	if (isStatic) return;

	SDL_FPoint desiredVector
	{
		point.x - transform->position.x,
		point.y - transform->position.y
	};

	float length = sqrt(desiredVector.x * desiredVector.x + desiredVector.y * desiredVector.y);
	float currentVelocity = GetSpeed();

	desiredVector.x /= length;
	desiredVector.y /= length;

	desiredVector.x *= currentVelocity;
	desiredVector.y *= currentVelocity;

	velocity.x += (desiredVector.x - velocity.x) * force;
	velocity.y += (desiredVector.y - velocity.y) * force;
}

void Rigidbody::Update(Transform& transform, float deltaTime)
{
	if (isStatic) return;

	transform.position.x = transform.position.x + velocity.x * deltaTime;
	transform.position.y += velocity.y * deltaTime;
		

	const float frictionFactor = 0.55f;

	velocity.x -= velocity.x * frictionFactor * deltaTime; 
	velocity.y -= velocity.y * frictionFactor * deltaTime; 


	if (std::abs(velocity.x) < 0.01f) velocity.x = 0.0f;
	if (std::abs(velocity.y) < 0.01f) velocity.y = 0.0f;
	
}
