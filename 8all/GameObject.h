#pragma once

#include <string>
#include <memory>

#include "Transform.h",
#include "RenderComponent.h"
#include "Rigidbody.h"

class Renderer;

class GameObject
{
public:
	std::string name;

	std::unique_ptr<Transform> transform;
	std::unique_ptr<RenderComponent> renderComponent;
	std::unique_ptr<Rigidbody> rigidBody;

	GameObject(const std::string& name);

	virtual ~GameObject() = default;

	virtual void Update(float deltaTime);
	virtual void Render(Renderer& renderer);

};

