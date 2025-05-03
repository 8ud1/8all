#pragma once

#include <string>
#include <memory>

#include "Utilities.h"

class Renderer;
struct Transform;

class GameObject
{
public:
	std::string name;
	GameObjectType type = GameObjectType::None;

	std::unique_ptr<Transform> transform;

	GameObject(const std::string& name, GameObjectType type)
		:name(name), type(type), transform(std::make_unique<Transform>()) {
	};

	virtual ~GameObject() = default;

	virtual void Update(float deltaTime) {};
	virtual void PhysicsUpdate(float deltaTime) {};
	virtual void Render(Renderer& renderer) = 0;

};

