#include "GameObject.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Rigidbody.h"


GameObject::GameObject(const std::string& name, GameObjectType type)
	:name(name), type(type), transform(std::make_unique<Transform>()) {}

