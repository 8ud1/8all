#pragma once

#include <SDL3/SDL.h>
#include "Transform.h"

class Rigidbody
{
protected:

	Transform* transform;
	float mass;
	SDL_FPoint velocity;
	
	bool isStatic = false;

	float GetSpeed();

public :

	Rigidbody(Transform* transform,	bool isStatic = false, float mass = 1.0f);

	Transform* GetTransform() const { return transform; }
	SDL_FPoint GetVelocity() const { return velocity; }
	float GetMass() const { return mass; }
	bool GetIsStatic() const { return isStatic; }

	void SetVelocity(const SDL_FPoint& velocity) { this->velocity = velocity; }
	void SetPosition(const SDL_FPoint& position) { this->transform->position = position; }
	void SetStatic(const bool isStatic);

	void ApplyForce(SDL_FPoint& force);
	void AttractToPoint(SDL_FPoint& point, float force);
	
	void Update(Transform& transform, float deltaTime);

};

