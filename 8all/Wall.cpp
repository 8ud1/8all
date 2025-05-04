#include "Wall.h"

#include "BoxCollider.h"

Wall::Wall(std::string name, const SDL_FPoint& startPos, const SDL_FPoint& size, bool visible)
	:PhysicsObject(name, GameObjectType::Wall), visible(visible)
{

	transform = std::make_unique<Transform>();
	transform->position = startPos;

	SDL_FRect rect = { startPos.x,startPos.y, size.x, size.y };

	collider = std::make_unique<BoxCollider>(rect);
	boxCollider = static_cast<BoxCollider*>(collider.get());

	rigidbody = std::make_unique<Rigidbody>(transform.get(),true);
}


void Wall::Render(Renderer& renderer)
{
	if (!visible) return;
	boxCollider->DrawDebug(renderer);
}
