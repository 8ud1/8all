#include "HoleTrigger.h"
#include "CircleCollider.h"

HoleTrigger::HoleTrigger(const std::string& name, const SDL_FPoint& pos, float radius, std::function<void(PhysicsObject*)> triggerAction)
	:PhysicsObject(name, GameObjectType::Hole), OnTriggerAction(triggerAction)
{
	transform = std::make_unique<Transform>();

	transform->position = pos;
	transform->scale = SDL_FPoint{ radius,radius };

	collider = std::make_unique<CircleCollider>(pos, radius);
	collider->isTrigger = true;
}

void HoleTrigger::OnTrigger(PhysicsObject* other)
{
	other->RigidBody()->AttractToPoint(transform->position, 0.5f);


	SDL_FPoint a = transform->position;
	SDL_FPoint b = other->transform->position;

	float dx = b.x - a.x;
	float dy = b.y - a.y;

	float distance = sqrtf(dx * dx + dy * dy);

	if (distance < 5.0f) OnTriggerAction(other);
}

void HoleTrigger::Render(Renderer& renderer)
{
	return;

	SDL_Point intPos = SDL_Point
	{
		static_cast<int>(std::round(transform->position.x)),
		static_cast<int>(std::round(transform->position.y))
	};

	renderer.DrawCircle(intPos, static_cast<int>(std::round(transform->scale.x)), SDL_Color{ 0,0,255,255 });
}
