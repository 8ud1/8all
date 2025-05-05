#include "Rigidbody.h"
#include <algorithm>

void Rigidbody::SetStatic(bool isStatic)
{
	this->isStatic = isStatic;
	
	ResetStates();
}

void Rigidbody::ResetStates()
{
	SetVelocity(SDL_FPoint{ 0.0f, 0.0f });
	SetAngularVelocity(0.0f);
	SetSpinForward(0.0f);
}

void Rigidbody::ApplyForce(const SDL_FPoint& force)
{
	if (!isStatic)
	{
		velocity.x += force.x / mass;
		velocity.y += force.y / mass;
	}
}

void Rigidbody::ApplyTorqueFromImpulse(const SDL_FPoint& contactPoint, const SDL_FPoint& impulse)
{

	if (isStatic) return;

	SDL_FPoint r =
	{
		contactPoint.x - transform->position.x,
		contactPoint.y - transform->position.y
	};

	float rCrossImpulse = r.x * impulse.y - r.y * impulse.x;

	// I = 0.5f* massa * radi
	float inertia = 0.5f * mass * 1.0f;
	if (inertia == 0.0f) return;

	float torqueBoostFactor = 1.2; 
	float deltaAngularVel = (rCrossImpulse / inertia) * torqueBoostFactor;

	angularVelocity += deltaAngularVel;
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
	
	desiredVector.x /= length;
	desiredVector.y /= length;

	float attractorSpeed = std::max(GetSpeed(), 50.0f);

	desiredVector.x *= attractorSpeed;
	desiredVector.y *= attractorSpeed;


	velocity.x += (desiredVector.x - velocity.x) * force;
	velocity.y += (desiredVector.y - velocity.y) * force;
}

void Rigidbody::Update(float deltaTime)
{
	if (isStatic) return;

	float speed = GetSpeed();
	//Spin
	
	if (speed > 0.0f)
	{
		SDL_FPoint perpedicular{ -velocity.y/speed, velocity.x/speed };
		float spinStrength = angularImpuls * speed; 

		velocity.x += perpedicular.x * angularVelocity * spinStrength * deltaTime;
		velocity.y += perpedicular.y * angularVelocity * spinStrength * deltaTime;
	}

	//SpinForward	

	speed = GetSpeed();
	SDL_FPoint forward = { 0.0f,0.0f };
	if (speed > 0)
	{
		forward.x = velocity.x / speed;
		forward.y = velocity.y / speed;
	}

	float desiredSpinSpeed = spinForward * maxSpinForwardChange;
	float deltaSpeed = desiredSpinSpeed - speed;

	deltaSpeed = std::clamp(deltaSpeed, -maxSpinForwardChange * deltaTime, maxSpinForwardChange * deltaTime);

	velocity.x += forward.x * deltaSpeed;
	velocity.y += forward.y * deltaSpeed;

	//Update Position
	transform->position.x = transform->position.x + velocity.x * deltaTime;
	transform->position.y += velocity.y * deltaTime;

	//Update Rotation
	transform->rotation += angularVelocity * 2.0f * deltaTime;
	transform->rotation = fmod(transform->rotation, 360.0f);
	if (transform->rotation < 0.0f) transform->rotation += 360.0f;


	//Friction
	float linearDecay = std::exp(-frictionFactor * deltaTime);
	float angularDecay = std::exp(-angularFrictionFactor * deltaTime);
	float spinForwardDecay = std::exp(-spinForwardFrictionFactor * deltaTime);

	velocity.x *= linearDecay; 
	velocity.y *= linearDecay;
	angularVelocity *= angularDecay;
	spinForward *= spinForwardDecay;
	

	//Movemnet brake Threshold
	if (std::abs(velocity.x) < 0.01f) velocity.x = 0.0f;
	if (std::abs(velocity.y) < 0.01f) velocity.y = 0.0f;
	if (std::abs(angularVelocity) < 1.0f) angularVelocity = 0.0f;
	if (std::abs(spinForward) < 0.01f) spinForward = 0.0f;
	
}
