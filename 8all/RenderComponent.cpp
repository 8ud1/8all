#include "RenderComponent.h"
#include "Renderer.h"

RenderComponent::RenderComponent(const std::string& textureId, const SDL_FRect& rect)
	: textureId(textureId), rect(rect){}

void RenderComponent::Render(Renderer& renderer, const SDL_FPoint& position)
{

	if (textureId.empty())
	{
		return;
	}
	SDL_FRect renderRect = rect;
	renderRect.x += position.x;
	renderRect.y += position.y;
	renderer.DrawTexture(textureId, renderRect);

	
}
