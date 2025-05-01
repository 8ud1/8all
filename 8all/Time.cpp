#include "Time.h"


uint64_t Time::lastCounter = SDL_GetPerformanceCounter();
uint64_t Time::frequency = SDL_GetPerformanceFrequency();
float Time::deltaTime = 0.0f;

void Time::Update()
{
	uint64_t current = SDL_GetPerformanceCounter();

	deltaTime = (static_cast<float>(current - lastCounter)) / static_cast<float>(frequency);

	lastCounter = current;
}

