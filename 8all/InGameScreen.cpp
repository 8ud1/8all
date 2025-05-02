#include "InGameScreen.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <memory>
#include <cstdlib>
#include <string>


#include "Ball.h"
#include "UIButton.h"
#include "UITextButton.h"
#include "Game.h"
#include "Utilities.h"


InGameScreen::InGameScreen(Game& game)
	: game(game), ball(nullptr)
{
}

void InGameScreen::Enter()
{
	Instantiate<Ball>(
			SDL_FPoint {Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.5f}
	);

	ball = Instantiate<Ball>(
		SDL_FPoint{ 200.0f,300.0f }
	);

	Instantiate<UITextButton>(
		SDL_FPoint{ 0.0f , 0.0f },
		SDL_FPoint{ 200.0f, 50.0f },
		[this]() {game.RequestChangeScene(SceneType::MAIN_MENU); },
		std::string("Main Menu"),
		SDL_Color{ 170,170,170,170},
		SDL_Color{ 255,255,255,255 }
	);

}

void InGameScreen::Exit()
{
	ball = nullptr;
}

void InGameScreen::HandleInputs(const SDL_Event& event)
{

	float force = 100.0f;
	SDL_FPoint forceVector = { 0.0f, 0.0f };

	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:

		switch (event.key.scancode)
		{
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

	ball->rigidBody->ApplyForce(forceVector);
}


void InGameScreen::Render(Renderer& renderer)
{
	Scene::Render(renderer);
	renderer.DrawText("8ball", Resources::FONT_TITLE, Utilities::WHITE, Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.1f);
	
	
}
