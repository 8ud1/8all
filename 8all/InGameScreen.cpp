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
#include "Rigidbody.h"
#include "Wall.h"

InGameScreen::InGameScreen(Game& game)
	: game(game)
{
}

void InGameScreen::Enter()
{

	for (int i = 0; i <= 5; i++)
	{
		float x = Utilities::SCREEN_WIDTH * 0.65f + i * 55 ;

		for (int j = 0; j < i; j++)
		{
			float y = Utilities::SCREEN_HEIGHT * 0.5f - (i * 0.5f * 55) + 55 * j + 25;

			Instantiate<Ball>(
				"ball_" + std::to_string(i),
				SDL_FPoint{ x, y }
			);
		}
	}

	ball = Instantiate<Ball>(
		"ball 2",
		SDL_FPoint{ 200.0f,Utilities::SCREEN_HEIGHT * 0.5f }
	);

	// environment

	 Instantiate<Wall>(
		"leftWall",
		SDL_FPoint{ 0.0f, 0.0f },
		SDL_FPoint{ 50.0f, Utilities::SCREEN_HEIGHT }
	);

	 Instantiate<Wall>(
		 "rightWall",
		 SDL_FPoint{ Utilities::SCREEN_WIDTH - 50.0f, 0.0f },
		 SDL_FPoint{ 50.0f, Utilities::SCREEN_HEIGHT }
	 );

	 Instantiate<Wall>(
		 "topWall",
		 SDL_FPoint{ 50.0f,0.0f },
		 SDL_FPoint{ Utilities::SCREEN_WIDTH -100.0f,50.0f }
	 );

	 Instantiate<Wall>(
		 "bottomWall",
		 SDL_FPoint{ 50.0f, Utilities::SCREEN_HEIGHT - 50.0f },
		 SDL_FPoint{ Utilities::SCREEN_WIDTH - 100.0f,50.0f }
	 );

}

void InGameScreen::Exit()
{
	
}

void InGameScreen::HandleInputs(const SDL_Event& event)
{

	float mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_FPoint mousePos = { mouseX, mouseY };

	if (isCharging)
	{
		chargingVector =
			SDL_FPoint
		{
			(ball->transform->position.x - mousePos.x),
			(ball->transform->position.y - mousePos.y),
		};
	}

	switch (event.type)
	{

	case SDL_EVENT_MOUSE_BUTTON_UP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{

			if (!isCharging) break;

			SDL_FPoint shotVector =
				SDL_FPoint
			{
				(ball->transform->position.x - mousePos.x) * 5.0f,
				(ball->transform->position.y - mousePos.y) * 5.0f,
			};


			ball->rigidbody->ApplyForce(shotVector);

			isCharging = false;

		}
		break;

	case SDL_EVENT_MOUSE_BUTTON_DOWN:

		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_FRect ballRect =
			{
				ball->transform->position.x - ball->transform->scale.x * 0.5f,
				ball->transform->position.y - ball->transform->scale.y * 0.5f,
				ball->transform->scale.x,
				ball->transform->scale.y
			};

			isCharging = SDL_PointInRectFloat(&mousePos, &ballRect);
		}
	

		break;
	case SDL_EVENT_KEY_DOWN:

		switch (event.key.scancode)
		{
		case SDL_SCANCODE_W:
			break;
		case SDL_SCANCODE_A:
			break;
		case SDL_SCANCODE_S:
			break;
		case SDL_SCANCODE_D:
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

void InGameScreen::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	//Physics();
}


void InGameScreen::Render(Renderer& renderer)
{
	Scene::Render(renderer);


	SDL_Point ballPos = SDL_Point
	{
		(int)ball->transform->position.x,
		(int)ball->transform->position.y
	};

	renderer.DrawCircle(ballPos, 50.0f, SDL_Color{255,0,0,255});
	if (isCharging)
	{
		for (int i = 1; i < 10; ++i)
		{

			SDL_FRect rect = SDL_FRect{
			(ball->transform->position.x + chargingVector.x * ( 0.1f * i )),
			(ball->transform->position.y + chargingVector.y * ( 0.1f * i )),
			5.0f,5.0f
			};

			renderer.DrawRect(rect, SDL_Color{ 255,0,0,255 });
		}
	}
}
