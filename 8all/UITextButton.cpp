#include "UITextButton.h"

#include "Resources.h"
#include "Renderer.h"

UITextButton::UITextButton(SDL_FPoint position, SDL_FPoint size, std::function<void()> clickAction, std::string text, SDL_Color defaultColor, SDL_Color hoverColor)
	: UIButton(position, size, clickAction), textBtn(text), defaultColor(defaultColor), hoveredColor(hoverColor)
{

}

void UITextButton::Render(Renderer& renderer)
{
	renderer.DrawRect(*transform, isHovered ? hoveredColor : defaultColor);

	renderer.DrawText(
		textBtn,
		Resources::FONT,
		{ 255,255,255,255 },
		transform->position.x + transform->scale.x * 0.5f,
		transform->position.y + transform->scale.y * 0.5f
	);
}
