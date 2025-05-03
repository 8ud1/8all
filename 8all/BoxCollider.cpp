#include "BoxCollider.h"

#include "CircleCollider.h"

bool BoxCollider::CheckCollision(const Collider& other, CollisionInfo& info) const
{
    return other.CheckCollisionWithBox(*this,info);
}

bool BoxCollider::CheckCollisionWithCircle(const CircleCollider& other, CollisionInfo& info) const
{
	return other.CheckCollisionWithBox(*this, info);
}

bool BoxCollider::CheckCollisionWithBox(const BoxCollider& other, CollisionInfo& info) const
{

	//Todo - something wrong
	bool overlapedX = (rect.x < other.rect.x + other.rect.w) && (rect.x + rect.w > other.rect.x);
	bool overlapedY = (rect.y < other.rect.y + other.rect.h) && (rect.y + rect.h > other.rect.y);


	if (overlapedX && overlapedY)
	{
		float dx = (rect.x + rect.w / 2) - (other.rect.x + other.rect.w / 2);
		float dy = (rect.y + rect.h / 2) - (other.rect.y + other.rect.h / 2);
		if (abs(dx) > abs(dy))
		{
			info.normal = { dx > 0 ? 1.0f : -1.0f, 0.0f };
			info.penetration = abs(dx);
		}
		else
		{
			info.normal = { 0.0f, dy > 0 ? 1.0f : -1.0f };
			info.penetration = abs(dy);
		}

		return true;
	}

	return false;
}

void BoxCollider::DrawDebug(Renderer& renderer) const
{
    renderer.DrawRect(rect, SDL_Color{ 0,255,0,120 });
}
