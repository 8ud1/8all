#pragma once

#include <string>
#include <memory>


class Renderer;
class Transform;
class RenderComponent;
class Rigidbody;


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

	//bool IsVisible() const;
};

