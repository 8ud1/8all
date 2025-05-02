#include "MainMenu.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <memory>
#include <cstdlib>

#include "Ball.h"
#include "Rigidbody.h"
#include "UITextButton.h"
#include "Game.h"
#include "Utilities.h"



MainMenu::MainMenu(Game& game)
	:game(game)
{

}

void MainMenu::Enter()
{
	Instantiate<UITextButton>(
		SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.5f - 100.0f, Utilities::SCREEN_HEIGHT * 0.5f},
		SDL_FPoint{ 200.0f,50.0f },
		[this]() {game.RequestChangeScene(SceneType::GAME); },
		("Start Game"),
		SDL_Color{ 170,170,170,255 },
		SDL_Color{ 0,170,0,255 }
	);

	Instantiate<UITextButton>(
		SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.5f - 100.0f, Utilities::SCREEN_HEIGHT * 0.5f + 75.0f },
		SDL_FPoint{ 200.0f,50.0f },
		[&]() {SDL_Log("Ranking"); },
		("Ranking"),
		SDL_Color{ 170,170,170,255 },
		SDL_Color{ 0,170,0,255 }
	);

	Instantiate<UITextButton>(
		SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.5f - 100.0f, Utilities::SCREEN_HEIGHT * 0.5f + 75.0f * 2.0f },
		SDL_FPoint{ 200.0f,50.0f },
		[&]() {SDL_Quit(); },
		("Quit"),
		SDL_Color{ 170,170,170,255 },
		SDL_Color{ 0,170,0,255 }
	);

}

void MainMenu::Exit()
{
	// Clean up resources, save state, etc.
	// This is where you would clean up the main menu scene.
	// For example, if you had loaded textures or fonts, you would unload them here.
	// renderer->UnloadFont(Resources::FONT_REGULAR);
	// renderer->UnloadFont(Resources::FONT_LITTLE);
	// renderer->UnloadFont(Resources::FONT_TITLE);
}

void MainMenu::HandleInputs(const SDL_Event& event)
{
	float force = 20.0f;
	SDL_FPoint forceVector = { 0.0f, 0.0f };

	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:

		switch (event.key.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			SDL_Log("Escape key pressed. Exiting...");
			break;
		case SDL_SCANCODE_W:

			forceVector.y = -force;
			break;
		case SDL_SCANCODE_A:

			forceVector.x = -force;

			break;
		case SDL_SCANCODE_S:
			forceVector.y = force;
			break;
		case SDL_SCANCODE_D:
			forceVector.x = force;
			break;
		}
		break;
	case SDL_EVENT_MOUSE_MOTION:
		//SDL_Log("Current mouse position is: (%f, %f)", event.motion.x, event.motion.y);
		break;
	default:
		break;
	}
}

void MainMenu::Render(Renderer& renderer)
{
	Scene::Render(renderer);


	renderer.DrawText(
		"8all",
		Resources::FONT_TITLE,
		SDL_Color{ 255,255,255,255 },
		Utilities::SCREEN_WIDTH * 0.5f,
		Utilities::SCREEN_HEIGHT * 0.25f
		);

}

