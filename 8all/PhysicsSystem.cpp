#include "PhysicsSystem.h"

#include <SDL3/SDL.h>
#include <cmath>


#include "PhysicsObject.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Transform.h"



void PhysicsSystem::AddBody(PhysicsObject* body)
{
	bodies.push_back(body);
}

void PhysicsSystem::ClearBodies()
{
	bodies.clear();
}

bool PhysicsSystem::AreAllObjectsStopped(float threshold) const
{
	
	for (const auto& body : bodies)
	{
		Rigidbody* rb;
		rb = body->RigidBody();

		if (rb->GetIsStatic()) continue;

		float speed = rb->GetSpeed();

		if (speed > threshold )
		{
			return false;
		}

	}
	return true;
}

void PhysicsSystem::Update(float deltaTime)
{
	for (size_t i = 0; i < bodies.size(); ++i)
	{
		PhysicsObject* a = bodies[i];
		for (size_t j = i + 1; j < bodies.size(); ++j)
		{
			PhysicsObject* b = bodies[j];
			CollisionInfo info;
			if (a->GetCollider()->CheckCollision(*b->GetCollider(), info))
			{
				if (a->GetCollider()->isTrigger || b->GetCollider()->isTrigger)
				{
					a->OnTrigger(b);
					b->OnTrigger(a);
				}
				else
				{
					ResolveCollision(a, b, info);
				}
			}
		}
	}
}

void PhysicsSystem::ResolveCollision(PhysicsObject* bodyA, PhysicsObject* bodyB, CollisionInfo& info)
{

	Rigidbody* rbA = bodyA->RigidBody();
	Rigidbody* rbB = bodyB->RigidBody();


	float invMassA = rbA->GetIsStatic() ? 0.0f : 1.0f / rbA->GetMass();
	float invMassB = rbB->GetIsStatic() ? 0.0f : 1.0f / rbB->GetMass();


	float totalInvMass = invMassA + invMassB;

	// Skip if both rb are statics
	if (totalInvMass == 0.0f) return;

	// Penetration correction
	const float percent = 0.8f;  
	const float slop = 0.01f;    

	float correctionMagnitude = std::max(info.penetration - slop, 0.0f) / (invMassA + invMassB) * percent;

	SDL_FPoint correction = {
		correctionMagnitude * info.normal.x,
		correctionMagnitude * info.normal.y
	};

	// Apply the correction 
	if (!rbA->GetIsStatic()) {


		bodyA->transform->position.x -= correction.x * (invMassA / totalInvMass);
		bodyA->transform->position.y -= correction.y * (invMassA / totalInvMass);
	}

	if (!rbB->GetIsStatic()) 
	{

		bodyB->transform->position.x += correction.x * (invMassB/ totalInvMass);
		bodyB->transform->position.y += correction.y * (invMassB / totalInvMass);
	}

	
	// Calculate the relative velocity
	SDL_FPoint relativeVelocity
	{
		rbB->GetVelocity().x - rbA->GetVelocity().x,
		rbB->GetVelocity().y - rbA->GetVelocity().y
	};

	float velAlongNormal = relativeVelocity.x * info.normal.x + relativeVelocity.y * info.normal.y;

	if (velAlongNormal > 0) return;

	float bounciness = 0.90f;

	float j = -(1 + bounciness) * velAlongNormal;
	
	j /= invMassA + invMassB;


	SDL_FPoint impulse =
	{
		j * info.normal.x,
		j * info.normal.y
	};

	// Apply the impulse (linear)
	if (!rbA->GetIsStatic())
		rbA->SetVelocity(
			{
				rbA->GetVelocity().x - impulse.x * invMassA,
				rbA->GetVelocity().y - impulse.y * invMassA
			});
		

	if (!rbB->GetIsStatic())
		rbB->SetVelocity(
			{
				rbB->GetVelocity().x + impulse.x * invMassB,
				rbB->GetVelocity().y + impulse.y * invMassB
			});

	//ADd impulse by torque

	rbA->ApplyTorqueFromImpulse(info.contactPoint, impulse);
	rbB->ApplyTorqueFromImpulse(info.contactPoint, impulse);

}
