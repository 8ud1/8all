#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <unordered_map>
#include <string>

class ResourceManager
{
private :
	SDL_Renderer* renderer;

	std::unordered_map < std::string, SDL_Texture*> textures;
	std::unordered_map < std::string, TTF_Font*> fonts;

public:
	ResourceManager(SDL_Renderer* renderer);
	~ResourceManager();

	bool LoadTexture(const std::string& id, const std::string& path);
	SDL_Texture* GetTexture(const std::string& id) const;

	bool LoadFont(const std::string& id, const std::string& path, int size);
	TTF_Font* GetFont(const std::string& id) const;

	void Cleanup();
};

