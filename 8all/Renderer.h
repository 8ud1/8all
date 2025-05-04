#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>

#include "ResourceManager.h"
#include "Transform.h"

class Renderer
{

private:
	SDL_Renderer* renderer;
	ResourceManager* resourceManager;
public :

	Renderer(SDL_Window* window);
	~Renderer();

	//SDL_Renderer* GetRenderer() { return renderer; }
	
	void Clear();
	void Present();

	bool LoadTexture(const std::string& id, const std::string& path);
	bool LoadFont(const std::string& id, const std::string& path, int size);

	void DrawRect(const SDL_FRect& rect, SDL_Color color);
	void DrawRect(Transform& transform, SDL_Color color);

	void DrawCircle(const SDL_Point& center, int radius, SDL_Color color);

	void DrawTexture(const std::string& textureID, const SDL_FRect& rect);
	void DrawTexture(const std::string& textureID, const SDL_FRect& rect, float rotation);
	void DrawTextures(const std::string& textureID, Transform* transform, int columns, int rows, int frame);
	void DrawTextures(const std::string& textureID, Transform* transform, float columns, int rows, int frameHeight, int frame);

	void DrawText(const std::string& text, const std::string& fontId, SDL_Color color, float x, float y);
};

