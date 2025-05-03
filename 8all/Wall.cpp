#include "Wall.h"

#include "BoxCollider.h"

Wall::Wall(std::string name, const SDL_FPoint& startPos, const SDL_FPoint& size)
	:PhysicsObject(name, GameObjectType::Wall)
{

	transform = std::make_unique<Transform>();
	transform->position = startPos;

	SDL_FRect rect = { startPos.x,startPos.y, size.x, size.y };

	collider = std::make_unique<BoxCollider>(rect);
	boxCollider = static_cast<BoxCollider*>(collider.get());

	rigidbody = std::make_unique<Rigidbody>();
	rigidbody->mass = 1.0f;
}

void Wall::Update(float deltaTime)
{
	rigidbody->Update(*transform, deltaTime);
	boxCollider->rect = { transform->position.x, transform->position.y, boxCollider->rect.w, boxCollider->rect.h };
}

void Wall::Render(Renderer& renderer)
{
	boxCollider->DrawDebug(renderer);
}
