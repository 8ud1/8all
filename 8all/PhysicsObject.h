#pragma once

#include "GameObject.h"
#include "Rigidbody.h"
#include "Collider.h"

class PhysicsObject : public GameObject
{

protected:
	std::unique_ptr<Collider> collider = nullptr;
public:
	std::unique_ptr<Rigidbody> rigidbody;
	

	PhysicsObject(const std::string& name, GameObjectType type)
		: GameObject(name, type) {
	}

	virtual ~PhysicsObject() = default;

	//Collider* Collider() const { return collider.get(); }
};

