#include "Renderer.h"

#define _USE_MATH_DEFINES
#include <math.h>


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
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
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

void Renderer::DrawRect(Transform& transform, SDL_Color color)
{

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_FRect rect = { transform.position.x, transform.position.y, transform.scale.x, transform.scale.y };
	SDL_RenderFillRect(renderer, &rect);
}

void Renderer::DrawCircle(const SDL_Point& center, int radius, SDL_Color color)
{

	const int num_segments = 100;

	for (int i = 0; i < num_segments; ++i)
	{
		float theta = 2.0f * M_PI * float(i) / float(num_segments);

		int x = static_cast<int>(radius * cosf(theta));
		int y = static_cast<int>(radius * sinf(theta));

		SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
		SDL_RenderPoint(renderer,center.x + x,center.y + y);
	}
}



void Renderer::DrawTexture(const std::string& textureID, const SDL_FRect& rect)
{
	SDL_Texture* texture = resourceManager->GetTexture(textureID);

	if (texture)
	{
		SDL_RenderTexture(renderer, texture, nullptr, &rect);
	}
}

void Renderer::DrawTextures(const std::string& textureID, Transform* transform, int columns, int rows, int frame)
{

	SDL_Texture* texture = resourceManager->GetTexture(textureID);
	if (texture)
	{
		SDL_FRect dstRect = { transform->position.x - transform->scale.x * 0.5f, transform->position.y - transform->scale.y * 0.5f, transform->scale.x, transform->scale.y };


		int frameWidth = texture->w / columns; 
		int frameHeight = texture->h / rows;

		// Calcular fila y columna (suponiendo layout horizontal)
		SDL_FRect srcRect = { 0, 0,frameWidth ,frameWidth };

		srcRect.x = (frame % columns) * frameWidth;
		srcRect.y = (frame / rows) * frameHeight;


		SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);
	}
}

void Renderer::DrawText(const std::string& text, const std::string& fontId, SDL_Color color, float x, float y)
{
	TTF_Font* font = resourceManager->GetFont(fontId);

	if (!font) return;

	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, color);

	if (!surface) return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FRect rect = { x - surface->w * .5f, y -surface->h * 0.5f, surface->w, surface->h };

	SDL_DestroySurface(surface);

	if (texture)
	{
		SDL_RenderTexture(renderer, texture, nullptr, &rect);
		SDL_DestroyTexture(texture);
	}
}
