#include "Renderer.h"

Renderer::Renderer(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, NULL);

	resourceManager = new ResourceManager(renderer);
}

Renderer::~Renderer()
{
	if (renderer) SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	delete(resourceManager);
	resourceManager = nullptr;
}

void Renderer::Clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Renderer::Present()
{
	SDL_RenderPresent(renderer);
}

bool Renderer::LoadTexture(const std::string& id, const std::string& path)
{
	return resourceManager->LoadTexture(id, path);
}

bool Renderer::LoadFont(const std::string& id, const std::string& path, int size)
{
	return resourceManager->LoadFont(id, path, size);
}


void Renderer::DrawRect(const SDL_FRect& rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Renderer::DrawTexture(const std::string& textureID, const SDL_FRect& rect)
{
	SDL_Texture* texture = resourceManager->GetTexture(textureID);

	if (texture)
	{
		SDL_RenderTexture(renderer, texture, nullptr, &rect);
	}
}

void Renderer::DrawText(const std::string& text, const std::string& fontId, SDL_Color color, float x, float y)
{
	TTF_Font* font = resourceManager->GetFont(fontId);

	if (!font) return;

	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, color);

	if (!surface) return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FRect rect = { x, y, surface->w, surface->h };

	SDL_DestroySurface(surface);

	if (texture)
	{
		SDL_RenderTexture(renderer, texture, nullptr, &rect);
		SDL_DestroyTexture(texture);
	}
}
