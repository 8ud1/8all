#pragma once

#include <SDL3/SDL.h>
#include <string>

#include "UIButton.h"


class UITextButton : public UIButton
{
private:
	std::string textBtn;

	SDL_Color defaultColor;
	SDL_Color hoveredColor;

public:
	UITextButton(SDL_FPoint position, SDL_FPoint size, std::function<void()> clickAction, std::string text, SDL_Color defaultColor, SDL_Color hoverColor);
	~UITextButton() = default;
	void Render(Renderer& renderer) override;
};

