#include "BoxCollider.h"

bool BoxCollider::CheckCollision(const Collider& other) const
{
    return other.CheckCollisionWithBox(*this);
}

bool BoxCollider::CheckCollisionWithCircle(const CircleCollider& other) const
{
    return false;
}

bool BoxCollider::CheckCollisionWithBox(const BoxCollider& other) const
{
    return false;
}

void BoxCollider::DrawDebug(Renderer& renderer) const
{

}
