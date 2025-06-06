#pragma once

#include "GameObject.h"
#include "Rigidbody.h"
#include "Collider.h"

class PhysicsObject : public GameObject
{

protected:
	std::unique_ptr<Collider> collider = nullptr;
	std::unique_ptr<Rigidbody> rigidbody = nullptr;

public:
	PhysicsObject(const std::string& name, GameObjectType type)
		: GameObject(name, type) {	}


	virtual ~PhysicsObject() = default;

	virtual void OnTrigger(PhysicsObject* obj) {};
	
	Collider* GetCollider() const { return collider.get(); }
	Rigidbody* RigidBody() const { return rigidbody.get(); }

};

