#include "ResourceManager.h"

ResourceManager::ResourceManager(SDL_Renderer* renderer) : renderer(renderer) {}


ResourceManager::~ResourceManager()
{
	Cleanup();
}

bool ResourceManager::LoadTexture(const std::string& id, const std::string& path)
{
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());

	if (!surface)
		return false;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_DestroySurface(surface);

	if (!texture)
		return false;

	textures[id] = texture;

	return true;
}

SDL_Texture* ResourceManager::GetTexture(const std::string& id) const
{
	auto it = textures.find(id);
	return it != textures.end() ? it->second : nullptr;
}

bool ResourceManager::LoadFont(const std::string& id, const std::string& path, int size)
{
	TTF_Font* font = TTF_OpenFont(path.c_str(), size);
	if (!font)
		return false;


	fonts[id] = font;
	return true;
}

TTF_Font* ResourceManager::GetFont(const std::string& id) const
{
	auto it = fonts.find(id);
	return it != fonts.end() ? it->second : nullptr;
}

void ResourceManager::Cleanup()
{

	for (auto& tex : textures)
	{
		SDL_DestroyTexture(tex.second);
	}

	textures.clear();

	for (auto& font : fonts)
	{
		TTF_CloseFont(font.second);
	}

	fonts.clear();
}
