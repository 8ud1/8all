#pragma once

#include <SDL3/SDL.h>

#include <memory>
#include <vector>

#include "GameObject.h"
#include "Renderer.h"

#include "PhysicsSystem.h"

class Scene
{

protected:
	PhysicsSystem physicsSystem;

	std::vector<std::unique_ptr<GameObject>> gameObjects;
	
	template <typename T, typename... Args>

	T* Instantiate(Args&&... args)
	{
		auto gameObject = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = gameObject.get();
		gameObjects.push_back(std::move(gameObject));

		if constexpr (std::is_base_of<PhysicsObject, T>::value)
		{
			physicsSystem.AddBody(ptr);
		}

		return ptr;
	}

	virtual void LogicUpdate(float deltaTime);
	virtual void PhysicsUpdate(float deltaTime);

public:

	virtual ~Scene() = default;

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void HandleInputs(const SDL_Event& event) = 0;
	void Update(float deltaTime);
	virtual void Render(Renderer& renderer);
};

