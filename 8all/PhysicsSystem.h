#pragma once

#include <vector>
#include "PhysicsObject.h"
#include "CollisionInfo.h"

class PhysicsSystem
{
private:
	std::vector<PhysicsObject*> bodies;

public: 
	void AddBody(PhysicsObject* body);
	void ClearBodies();
	bool AreAllObjectsStopped(float threshold = 1.0f) const;

	void Update(float deltaTime);	
	void ResolveCollision(PhysicsObject* bodyA, PhysicsObject* bodyB, CollisionInfo& info);
};

