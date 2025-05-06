#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_audio.h>
#include <memory>

#include "Renderer.h"
#include "Time.h"
#include "Resources.h"

#include "Utilities.h"

class Scene;
class Renderer;

class Game
{
private:
	SDL_Window* window;
	std::unique_ptr<Renderer> renderer;

	bool isRunning;
	float deltaTime;

	SceneType activeSceneType;
	std::unique_ptr<Scene> currentScene;

	SceneType requestedSceneType;
	bool isSceneChangeRequested;

	void HandleInputs();
	void Update();
	void Render();

	void ShowStats();

	void LoadScene(SceneType type);
	void ChangeScene();

public:
	Game();
	~Game();

	bool Start(const char* title);
	void Run();
	void Cleanup();

	void RequestChangeScene(SceneType type);

	void RequestRestartScene(SceneType type);

	SDL_Window* GetWindow() const { return window; }
};

