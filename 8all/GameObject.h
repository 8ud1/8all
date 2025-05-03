#pragma once

#include <string>
#include <memory>

#include "Utilities.h"

class Renderer;
class Transform;

class GameObject
{
public:
	std::string name;
	GameObjectType type = GameObjectType::None;

	std::unique_ptr<Transform> transform;

	GameObject(const std::string& name, GameObjectType type);
	virtual ~GameObject() = default;

	virtual void Update(float deltaTime) = 0;
	virtual void Render(Renderer& renderer) = 0;

};

