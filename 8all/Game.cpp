#include <iostream>
#include "Game.h"
 

#include "MainMenu.h"

void Game::HandleInputs()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		currentScene->HandleInputs(event);
	}
}


void Game::Update()
{
	if (currentScene) currentScene->Update(Time::DeltaTime());
}

void Game::Render()
{
	renderer->Clear();
	ShowStats();
	if (currentScene) currentScene->Render(*renderer);
	renderer->Present();
}

void Game::Test()
{
	
	SDL_FRect ballRect = { 100,100,256,256 };
	renderer->DrawTexture(Resources::BALL, ballRect);

	SDL_Color white = { 255,255,255,255 };
	renderer->DrawText("8all", Resources::FONT_TITLE, white, 720.0f, 450.0f);
	renderer->DrawText("billar Game", Resources::FONT_REGULAR,white, 720.0f, 500.0f);
}

void Game::ShowStats()
{

	SDL_FRect rect = { 0, 0, 1280, 25 };
	SDL_Color bgColor = { 0, 50, 0, 255 };
	SDL_Color color = { 0, 255, 0, 255 };

	renderer->DrawRect(rect, bgColor);
	std::string fpsText = "FPS: " + std::to_string(static_cast<int>(1.0f / Time::DeltaTime()));
	renderer->DrawText(fpsText,Resources::FONT_LITTLE, color, 10.0f, 5.0f);
	renderer->DrawText("Delta Time: " + std::to_string(Time::DeltaTime()), Resources::FONT_LITTLE, color, 50.0f, 5.0f);
}




Game::Game() : window(nullptr),renderer(nullptr), isRunning(false), deltaTime(0.0f) 
{
	activeSceneType = SceneType::MAIN_MENU;
	LoadScene(activeSceneType);
}

Game::~Game()
{
	delete(window);
	window = nullptr;
}

bool Game::Start(const char* title, int width, int height)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL_ttf: %s", SDL_GetError());
		return false;
	}


	window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return false;
	}

	renderer = new Renderer(window);


	//Todo - load resources on load Scene
	renderer->LoadFont(Resources::FONT_REGULAR,Resources::FONT_BASIC_PATH, Resources::FONT_REGULAR_SIZE);
	renderer->LoadFont(Resources::FONT_LITTLE,Resources::FONT_BASIC_PATH, Resources::FONT_LITTLE_SIZE);
	renderer->LoadFont(Resources::FONT_TITLE,Resources::FONT_BASIC_PATH, Resources::FONT_TITLE_SIZE);
	
	renderer->LoadTexture(Resources::BALL,Resources::TEXTURE_BALL_PATH);

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

		uint64_t frameEnd = SDL_GetTicks();   // ms
		float elapsedMs = static_cast<float>(frameEnd - frameStart);

		if (elapsedMs < targetFrameMs) {
			SDL_Delay(static_cast<uint32_t>(targetFrameMs - elapsedMs));
		}
	}
}

void Game::Cleanup()
{
	delete(renderer);
	renderer = nullptr;
	if (window) SDL_DestroyWindow(window);
	window = nullptr;
}

void Game::ChangeScene(SceneType type)
{
	if (type == activeSceneType) return;

	if (currentScene )
	{
		currentScene->Exit();
		delete(currentScene);
		currentScene = nullptr;
	}

	LoadScene(type);
}


void Game::LoadScene(SceneType type)
{

	switch (type)
	{
	case SceneType::MAIN_MENU:
		currentScene = new MainMenu();
		break;
	case SceneType::GAME:
		currentScene = new MainMenu();
		break;
	case SceneType::RESULT:
		currentScene = new MainMenu();
		break;
	default:
		return;
	}

	activeSceneType = type;
	currentScene->Enter();
}