#include "CircleCollider.h"
#include <SDL3/SDL.h>
#include<cmath>

#include "BoxCollider.h"

bool CircleCollider::CheckCollision(const Collider& other, CollisionInfo& info) const
{

    return other.CheckCollisionWithCircle(*this, info);
}

bool CircleCollider::CheckCollisionWithCircle(const CircleCollider& other, CollisionInfo& info) const
{

    float dx = center.x  - other.center.x;
    float dy = center.y - other.center.y;

    float distSq = dx * dx + dy * dy;
    float radiusSum = radius + other.radius;


	if (distSq < (radiusSum * radiusSum))
	{

		float dist = sqrtf(distSq);
		info.penetration = radiusSum - dist;
		info.normal = dist != (0.0f) ? SDL_FPoint{ dx / dist, dy / dist } : SDL_FPoint{ 1.0f, 0.0f };
		
        return true;
	}
    return false;
}

bool CircleCollider::CheckCollisionWithBox(const BoxCollider& other, CollisionInfo& info) const
{

    const SDL_FRect& rect = other.rect;

    float closestX = std::max(rect.x, std::min(center.x, rect.x + rect.w));
    float closestY = std::max(rect.y, std::min(center.y, rect.y + rect.h));

    float dx = center.x - closestX;
    float dy = center.y - closestY;

	float distSQ = dx * dx + dy * dy;

	if (distSQ < (radius * radius))
	{
		float dist = sqrtf(distSQ);
		info.penetration = radius - dist;
		

        if (closestX == rect.x)
        {
			info.normal = { 1.0f, 0.0f };
        }
        else if (closestX == rect.x + rect.w)
        {
			info.normal = { -1.0f, 0.0f };
		}
		else if (closestY == rect.y)
		{
			info.normal = { 0.0f, 1.0f };
        }
        else if (closestY == rect.y + rect.h)
        {
			info.normal = { 0.0f, -1.0f };
        }
        else
        {
            info.normal = (dist != 0.0f) ? SDL_FPoint{ dx / dist, dy / dist } : SDL_FPoint{ 1.0f, 0.0f };

        }
        
        return true;
	}

    return false;
}

void CircleCollider::DrawDebug(Renderer& renderer) const
{

    SDL_Point intCenter = { center.x, center.y };
    renderer.DrawCircle(intCenter, radius, SDL_Color{0,255,0,255});
}
