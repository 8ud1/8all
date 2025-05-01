#pragma once

#include <SDL3/SDL.h>

class Time
{
private:
	static uint64_t lastCounter;
	static uint64_t frequency;
	static float deltaTime;

public:
	static void Update();
	static float DeltaTime() {return deltaTime;}
};

