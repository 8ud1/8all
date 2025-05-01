#include "GameObject.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Rigidbody.h"


GameObject::GameObject(const std::string& name)
{
}

void GameObject::Update(float deltaTime)
{

	if (rigidBody && transform)
	{
		rigidBody->Update(transform.get(), deltaTime);
	}
}

void GameObject::Render(Renderer& renderer)
{
	if (renderComponent && transform)
	{
		renderComponent->Render(renderer, transform->position);
	}
}
