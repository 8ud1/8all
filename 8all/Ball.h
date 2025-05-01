#pragma once
#include <SDL3/SDL.h>

#include "GameObject.h"

class Ball : public GameObject
{

public:
	Ball(const SDL_FPoint& startPos);
	void Update(float deltaTime) override;
};

