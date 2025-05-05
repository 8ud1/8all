#include "UIBallSpin.h"

#include "Transform.h"
#include "Resources.h"
#include "Renderer.h"

UIBallSpin::UIBallSpin(SDL_FPoint position, SDL_FPoint size)
	:GameObject("UIBallSpin", GameObjectType::None)
{
	transform = std::make_unique<Transform>();
	transform->position = position;
	transform->scale = size;

	x = y = 0.0f;
}

void UIBallSpin::Update(float deltaTime)
{
	float mouseX, mouseY;

	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

	SDL_FPoint mousePos = { mouseX, mouseY };
	SDL_FRect absoluteBounds = { transform->position.x -transform->scale.x * 0.5f,
		transform->position.y - transform->scale.y * 0.5f,
		transform->scale.x, transform->scale.y };


	bool isHovered = SDL_PointInRectFloat(&mousePos, &absoluteBounds);

	if (isHovered && mouseState & SDL_BUTTON_LMASK)
	{
		x = (mousePos.x - transform->position.x)  / transform->scale.x;
		y = (mousePos.y - transform->position.y) / transform->scale.y;
	}
}

void UIBallSpin::Render(Renderer& renderer)
{
	SDL_Point position
	{
		transform->position.x,
		transform->position.y,
	};

	renderer.DrawTextures(Resources::TEXTURE_BALLS, transform.get(), Resources::BALLS_ROWS_COLUMNS, Resources::BALLS_ROWS_COLUMNS, 15);

	SDL_FRect
		rect
	{
		transform->position.x - 2.5f + (x * transform->scale.x),
		transform->position.y - 2.5f + (y * transform->scale.y),
		5.0f,
		5.0f
	};
	renderer.DrawRect(rect, SDL_Color{ 255,0,0,255 });

}
