#include "PauseCanvas.h"

#include "UITextButton.h"
#include "Resources.h"
#include "Utilities.h"

PauseCanvas::PauseCanvas(
	std::function<void()> resumeAction, std::function<void()> rankingAction,
	std::function<void()> exitAction, std::function<void()> restartAction,
	bool startActive)
	: OnResume(resumeAction), ShowRanking(rankingAction),
	OnExit(exitAction), OnRestart(restartAction), Canvas(startActive)
{

	InitCanvas();
}

void PauseCanvas::InitCanvas()
{

	Instantiate<UITextButton>(
		SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.5f - 100.0f, Utilities::SCREEN_HEIGHT * 0.45f - 25.0f },
		SDL_FPoint{ 200.0f,50.0f},
		[&]() { OnResume(); },
		("Resume"),
		SDL_Color({ 170,170,170,255 }),
		SDL_Color({ 0,170,0,255 })
	);

	Instantiate<UITextButton>(
		SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.5f - 100.0f, Utilities::SCREEN_HEIGHT * 0.45f - 25.0f + 75 },
		SDL_FPoint{ 200.0f,50.0f },
		[&]() { OnRestart(); },
		("Retry"),
		SDL_Color({ 170,170,170,255 }),
		SDL_Color({ 0,170,0,255 })
	);

	Instantiate<UITextButton>(
		SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.5f - 100.0f, Utilities::SCREEN_HEIGHT * 0.45f - 25.0f + 150 },
		SDL_FPoint{ 200.0f,50.0f },
		[&]() { OnExit(); },
		("Main Menu"),
		SDL_Color({ 170,170,170,255 }),
		SDL_Color({ 0,170,0,255 })
	);
}

void PauseCanvas::Update(float deltaTime)
{
	if (!isActive) return;
	for (auto& uiElement : uiElements)
	{
		uiElement->Update(deltaTime);
	}
}

void PauseCanvas::Render(Renderer& renderer)
{
	if (!isActive) return;
	
	renderer.DrawRect(SDL_FRect{ 0.0f,0.0f, Utilities::SCREEN_WIDTH, Utilities::SCREEN_HEIGHT }, SDL_Color{ 0,0,0,150 });
	
	for (auto& uiElement : uiElements)
	{
		uiElement->Render(renderer);
	}

	renderer.DrawText("Pause", Resources::FONT_TITLE, SDL_Color{ 255,255,255,255 },
		Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.2f);

	
}

