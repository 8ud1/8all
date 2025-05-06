#include <iostream>
#include "Game.h"

#include "MainMenu.h"
#include "InGameScreen.h"

#include "Utilities.h"
#include "Renderer.h"

void Game::HandleInputs()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		currentScene->HandleInputs(event);

		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;
		}
	}
}


void Game::Update()
{
	if (currentScene) currentScene->Update(Time::DeltaTime());
}

void Game::Render()
{
	renderer->Clear();
	if (currentScene) currentScene->Render(*renderer);
	//ShowStats();
	renderer->Present();
}

void Game::ShowStats()
{
	SDL_FRect rect = { 0, 0, 1280, 25 };
	SDL_Color bgColor = { 0, 50, 0, 50 };
	SDL_Color color = { 0, 255, 0, 255 };

	renderer->DrawRect(rect, bgColor);
	std::string fpsText = "FPS: " + std::to_string(static_cast<int>(1.0f / Time::DeltaTime()));
	renderer->DrawText(fpsText,Resources::CONSOLE, color, 75.0f, 10.0f);
	renderer->DrawText("Delta Time: " + std::to_string(Time::DeltaTime()), Resources::CONSOLE, color,250.0f, 10.0f);
}


Game::Game() : window(nullptr),renderer(nullptr), isRunning(false), deltaTime(0.0f) 
{
	activeSceneType = SceneType::MAIN_MENU;
	LoadScene(activeSceneType);
}

Game::~Game()
{
	SDL_DestroyWindow(window);
}

bool Game::Start(const char* title)
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}

	int ttfResult = TTF_Init();
	if (ttfResult == -1)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL_ttf: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(title, Utilities::SCREEN_WIDTH, Utilities::SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return false;
	}

	renderer = std::make_unique<Renderer>(window);


	//Todo - load resources on load Scene	

	renderer->LoadFont(Resources::CONSOLE, Resources::FONT_PATH, 10.0f);
	renderer->LoadFont(Resources::FONT, Resources::FONT_PATH, Resources::FONT_LITTLE_SIZE);
	renderer->LoadFont(Resources::TITLE, Resources::FONT_TITLES_PATH, Resources::FONT_REGULAR_SIZE);
	renderer->LoadFont(Resources::TITLE_BIG, Resources::FONT_TITLES_PATH, Resources::FONT_TITLE_SIZE);

	renderer->LoadTexture(Resources::TABLE, Resources::TABLE_PATH);
	renderer->LoadTexture(Resources::TEXTURE_BALLS, Resources::TEXTURE_BALLS_PATH);

	isRunning = true;


	return true;
}

void Game::Run()
{
	const float targetFrameMs = 1000.0f / 60.0f;

	while (isRunning)
	{
		uint64_t frameStart = SDL_GetTicks();

		Time::Update();
		HandleInputs();
		Update();
		Render();

		ChangeScene();

		uint64_t frameEnd = SDL_GetTicks();   // ms
		float elapsedMs = static_cast<float>(frameEnd) - static_cast<float>(frameStart);

		if (elapsedMs < targetFrameMs) {
			SDL_Delay(static_cast<uint32_t>(targetFrameMs - elapsedMs));
		}
	}
}

void Game::Cleanup()
{
	if (window) SDL_DestroyWindow(window);
	window = nullptr;
}

void Game::RequestChangeScene(SceneType type)
{
	if (type == activeSceneType || isSceneChangeRequested) return;

	requestedSceneType = type;
	isSceneChangeRequested = true;
}

void Game::RequestRestartScene(SceneType type)
{
	isSceneChangeRequested = true;
	requestedSceneType = type;
}

void Game::ChangeScene()
{
	if (!isSceneChangeRequested) return;

	if (currentScene)
	{
		currentScene->Exit();
		currentScene.reset();
	}

	LoadScene(requestedSceneType);
	isSceneChangeRequested = false;
}


void Game::LoadScene(SceneType type)
{

	switch (type)
	{
	case SceneType::MAIN_MENU:
		currentScene = std::make_unique<MainMenu>(*this);
		break;
	case SceneType::GAME:
		currentScene = std::make_unique<InGameScreen>(*this);
		break;
	case SceneType::RESULT:
		currentScene = std::make_unique<MainMenu>(*this);
		break;
	default:
		return;
	}

	activeSceneType = type;
	currentScene->Enter();
}  