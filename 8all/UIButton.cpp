#include "UIButton.h"
#include "Transform.h"
#include "Renderer.h"
#include "Resources.h"
#include "Utilities.h"


void UIButton::CheckMouseInteraction()
{
	float x, y = 0.0f;

	Uint32 mouseState = SDL_GetMouseState(&x, &y);

	SDL_FPoint mousePos = { x, y };
	SDL_FRect absoluteBounds = { transform->position.x, transform->position.y, transform->scale.x, transform->scale.y };

	bool nowHovered = SDL_PointInRectFloat(&mousePos, &absoluteBounds);

	isHovered = nowHovered;

	if (isHovered && (mouseState & SDL_BUTTON_LMASK))
	{
		if (OnClick)
			OnClick();
	}
	
}

UIButton::UIButton(SDL_FPoint position, SDL_FPoint size, std::function<void()> clickAction)
	: GameObject("button",GameObjectType::UIButton), OnClick(clickAction)
	
{
	isHovered = false;

	transform = std::make_unique<Transform>();

	transform->position = position;
	transform->scale = size;
}


void UIButton::Update(float deltaTime)
{
	CheckMouseInteraction();
}

void UIButton::Render(Renderer& renderer)
{
	SDL_Color color = isHovered ? SDL_Color{ 0, 255, 0, 255 } : SDL_Color{ 255, 0, 0, 255 };

	renderer.DrawRect(*transform, color);
	renderer.DrawText("Click Me", Resources::FONT_REGULAR, { 255,255,255,255 }, 
		transform->position.x + transform->scale.x *0.5f,
		transform->position.y + transform->scale.y * 0.5f);
}