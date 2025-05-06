#pragma once

#include <vector>
#include <memory>

#include "Renderer.h"

class GameObject;

class Canvas
{
protected:

	std::vector<std::unique_ptr<GameObject>> uiElements;
	
	bool isActive;

	virtual void InitCanvas() = 0;

	template <typename T, typename... Args>

	T* Instantiate(Args&&... args)
	{
		auto uiElement = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = uiElement.get();
		uiElements.push_back(std::move(uiElement));

		return ptr;
	}

public:

	Canvas(bool startActive) : isActive(startActive){}
	~Canvas() = default;

	virtual void Show() { isActive = true; }
	virtual void Hide() { isActive = false; }

	bool IsActive() const { return isActive; }

	virtual void Update(float deltaTime) = 0;
	virtual void Render(Renderer& renderer) = 0;

	virtual void HandleInputs(const SDL_Event& event) {}

};

