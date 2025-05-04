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
    float centerAx = rect.x + rect.w * 0.5f;
    float centerAy = rect.y + rect.h * 0.5f;

    float centerBx = other.rect.x + other.rect.w * 0.5f;
    float centerBy = other.rect.y + other.rect.h * 0.5f;

    float dx = centerBx - centerAx;
    float dy = centerBy - centerAy;

    float halfWidthA = rect.w * 0.5f;
    float halfWidthB = other.rect.w * 0.5f;

    float halfHeightA = rect.h * 0.5f;
    float halfHeightB = other.rect.h * 0.5f;

    float overlapX = halfWidthA + halfWidthB - std::abs(dx);
    float overlapY = halfHeightA + halfHeightB - std::abs(dy);

    if (overlapX > 0 && overlapY > 0) {
        if (overlapX < overlapY) {
            info.normal = { dx < 0 ? -1.0f : 1.0f, 0.0f };
            info.penetration = overlapX;
        }
        else {
            info.normal = { 0.0f, dy < 0 ? -1.0f : 1.0f };
            info.penetration = overlapY;
        }
        return true;
    }

    return false;
}

void BoxCollider::DrawDebug(Renderer& renderer) const
{
    renderer.DrawRect(rect, SDL_Color{ 0,255,0,120 });
}
