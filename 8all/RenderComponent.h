#pragma once
#include <SDL3/SDL.h>
#include <string>

class Renderer;

class RenderComponent
{

private :
	std::string textureId;
	SDL_FRect rect;

public:
	RenderComponent(const std::string& textureId, const SDL_FRect& rect);
	void Render(Renderer& renderer, const SDL_FPoint& position);
};

