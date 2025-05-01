#pragma once

#include <SDL3/SDL.h>

#include "Renderer.h"
#include "Time.h"
#include "Resources.h"

#include "Utilities.h"

class Scene;

class Game
{
private:
	SDL_Window* window;
	//Todo: use a smart pointer
	Renderer* renderer;

	bool isRunning;
	float deltaTime;

	//Todo: use a smart pointer
	Scene* currentScene;
	SceneType activeSceneType;

	void HandleInputs();
	void Update();
	void Render();

	void Test();
	void ShowStats();

	void LoadScene(SceneType type);

public:
	Game();
	~Game();

	bool Start(const char* title, int width, int height);
	void Run();
	void Cleanup();

	void ChangeScene(SceneType type);
};

