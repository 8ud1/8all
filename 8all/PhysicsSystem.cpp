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
				ResolveCollision(a, b, info);
			}
		}
	}
}

void PhysicsSystem::ResolveCollision(PhysicsObject* bodyA, PhysicsObject* bodyB, CollisionInfo& info)
{
	Rigidbody* rbA = bodyA->RigidBody();
	Rigidbody* rbB = bodyB->RigidBody();

	float invMassA = rbA->isStatic ? 0.0f : 1.0f / rbA->mass;
	float invMassB = rbB->isStatic ? 0.0f : 1.0f / rbB->mass;


	// Skip if both rb are statics
	if (invMassA + invMassB == 0.0f) return;

	// Penetration correction (position separation)
	const float percent = 0.8f;  // 80% correction
	const float slop = 0.01f;    // tolerance
	float correctionMagnitude = std::max(info.penetration - slop, 0.0f) / (invMassA + invMassB) * percent;

	SDL_FPoint correction = {
		correctionMagnitude * info.normal.x,
		correctionMagnitude * info.normal.y
	};

	if (!rbA->isStatic) {
		bodyA->transform->position.x -= correction.x * invMassA;
		bodyA->transform->position.y -= correction.y * invMassA;
	}

	if (!rbB->isStatic) {
		bodyB->transform->position.x += correction.x * invMassB;
		bodyB->transform->position.y += correction.y * invMassB;
	}

	SDL_FPoint relativeVelocity
	{
		rbB->velocity.x - rbA->velocity.x,
		rbB->velocity.y - rbA->velocity.y
	};

	float velAlongNormal = relativeVelocity.x * info.normal.x + relativeVelocity.y * info.normal.y;

	if (velAlongNormal > 0) return;

	float bounciness = 0.8f;

	float j = -(1 + bounciness) * velAlongNormal;
	
	j /= invMassA + invMassB;


	SDL_FPoint impulse =
	{
		j * info.normal.x,
		j * info.normal.y
	};

	if (!rbA->isStatic) {
		rbA->velocity.x -= impulse.x * invMassA;
		rbA->velocity.y -= impulse.y * invMassA;
	}

	if (!rbB->isStatic) {
		rbB->velocity.x += impulse.x * invMassB;
		rbB->velocity.y += impulse.y * invMassB;
	}


}
