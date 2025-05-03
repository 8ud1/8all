#include "CircleCollider.h"
#include <SDL3/SDL.h>
#include<cmath>

#include "BoxCollider.h"

bool CircleCollider::CheckCollision(const Collider& other) const
{
    return other.CheckCollisionWithCircle(*this);
}

bool CircleCollider::CheckCollisionWithCircle(const CircleCollider& other) const
{
    float dx = center.x  - other.center.x;
    float dy = center.y - other.center.y;

    float distSq = dx * dx + dy * dy;
    float radiusSum = radius + other.radius;

    return distSq <= (radiusSum * radiusSum);
}

bool CircleCollider::CheckCollisionWithBox(const BoxCollider& other) const
{
    const SDL_FRect& rect = other.rect;

    float closestX = std::max(rect.x, std::min(center.x, rect.x + rect.w));
    float closestY = std::max(rect.y, std::min(center.y, rect.y + rect.w));

    float dx = center.x - closestX;
    float dy = center.y - closestY;

    return (dx + dy) < radius;
}

void CircleCollider::DrawDebug(Renderer& renderer) const
{

    SDL_Point intCenter = { center.x, center.y };
    renderer.DrawCircle(intCenter, radius);
}
