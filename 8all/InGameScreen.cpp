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

#include "CircleCollider.h"


InGameScreen::InGameScreen(Game& game)
	: game(game), ball(nullptr)
{
}

void InGameScreen::Enter()
{
	collider = Instantiate<Ball>(
		"ball",
			SDL_FPoint {Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.5f}
	);

	ball = Instantiate<Ball>(
		"ball 2",
		SDL_FPoint{ 200.0f,Utilities::SCREEN_HEIGHT * 0.5f }
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

	ball->rigidbody->ApplyForce(forceVector);

}

void InGameScreen::Update(float deltaTime)
{
	Scene::Update(deltaTime);


	if (ball->collider->CheckCollision(*collider->collider))
	{
		SDL_Log("Collision Success");

		SDL_FPoint normal =
		{
			collider->transform->position.x - ball->transform->position.x,
			collider->transform->position.y - ball->transform->position.y,
		};

		float lenght = sqrtf(normal.x * normal.x + normal.y * normal.y);

		if (lenght != 0.0f)
		{
			normal.x /= lenght;
			normal.y /= lenght;
		}

		float dot = ball->rigidbody->velocity.x * normal.x + ball->rigidbody->velocity.y * normal.y;

		SDL_FPoint force = SDL_FPoint
		{
			ball->rigidbody->velocity.x * 0.5f,
			ball->rigidbody->velocity.y * 0.5f
		};

		collider->rigidbody->ApplyForce(force);
			

		ball->rigidbody->velocity.x -= 2.0f * dot * normal.x;
		ball->rigidbody->velocity.y -= 2.0f * dot * normal.y;

	}
	else
	{
		SDL_Log("Collision Failed");
	}
	
}


void InGameScreen::Render(Renderer& renderer)
{
	Scene::Render(renderer);
	renderer.DrawText("8ball", Resources::FONT_TITLE, Utilities::WHITE, Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.1f);
	
	
}
