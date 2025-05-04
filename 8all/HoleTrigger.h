#pragma once
#include "PhysicsSystem.h"
#include <functional>

class HoleTrigger :public PhysicsObject
{
private:
	std::function<void(PhysicsObject*)> OnTriggerAction = nullptr;
public :
	HoleTrigger(const std::string& name, const SDL_FPoint& pos, float radius, std::function<void(PhysicsObject*)> triggerAction);
	void OnTrigger(PhysicsObject* other) override;
	void Render(Renderer& renderer) override;
};
