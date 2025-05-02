#pragma once
#include <SDL3/SDL.h>
#include <functional>

#include "GameObject.h"

class UIButton : public GameObject
{

protected:
	bool isHovered;
	std::function<void()> OnClick;
	void CheckMouseInteraction();

public:

	UIButton(SDL_FPoint position, SDL_FPoint size, std::function<void()> clickAction);
	~UIButton() override = default;
	void Update(float deltaTime) override;
	void Render(Renderer& renderer) override;
};

	
