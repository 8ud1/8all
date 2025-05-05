#pragma once

#include <SDL3/SDL.h>
#include "Transform.h"
#include <cmath>

class Rigidbody
{
protected:

	Transform* transform;
	float mass;
	SDL_FPoint velocity{ 0.0f,0.0f };
	float angularVelocity = 0.0f;
	float spinForward = 0.0f;

	const float frictionFactor = 0.4f;
	const float angularFrictionFactor = 0.3f;
	const float angularImpuls = 0.0025f;


	const float spinForwardFrictionFactor = 0.5f;
	const float maxSpinForwardEffect = 200.0f;  
	const float maxSpinForwardChange = 70.0f;

	bool isStatic = false;
	
	
public :

	Rigidbody(Transform* transform, bool isStatic = false, float mass = 1.0f)
		: transform(transform), mass(mass), isStatic(isStatic), velocity(SDL_FPoint{ 0.0f, 0.0f }) {};

	Transform* GetTransform() const { return transform; }
	SDL_FPoint GetVelocity() const { return velocity; }
	float GetAngularVelocity() const { return angularVelocity; }
	float GetSpinForward() const { return spinForward; }
	float GetMass() const { return mass; }
	bool GetIsStatic() const { return isStatic; }
	float GetSpeed() const { return sqrt(velocity.x * velocity.x + velocity.y * velocity.y); }

	void SetVelocity(const SDL_FPoint& velocity) { this->velocity = velocity; }
	void SetAngularVelocity(const float angularVelocity) { this->angularVelocity = angularVelocity; }
	void SetSpinForward(const float spinForward) { this->spinForward = spinForward; }
	void SetPosition(const SDL_FPoint& position) { this->transform->position = position; }
	void SetStatic(const bool isStatic);


	void ResetStates();
	void ApplyForce(const SDL_FPoint& force);
	void ApplyTorqueFromImpulse(const SDL_FPoint& contactPoint, const SDL_FPoint& Impules);
	void AttractToPoint(SDL_FPoint& point, float force);
	
	void Update(float deltaTime);

};

