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

#include "CircleCollider.h"
#include "BoxCollider.h"
#include "CollisionInfo.h"

void InGameScreen::Physics()
{

	CollisionInfo info;
	if (ball->Collider()->CheckCollision(*wall->Collider(),info))
	{

		SDL_Log("Collision detected! %f", info.penetration);
		

		float dot = ball->rigidbody->velocity.x * info.normal.x + ball->rigidbody->velocity.y * info.normal.y;

		SDL_FPoint force = SDL_FPoint
		{
			ball->rigidbody->velocity.x * 0.5f,
			ball->rigidbody->velocity.y * 0.5f
		};

		ball->transform->position.x += info.normal.x * info.penetration;
		ball->transform->position.y += info.normal.y * info.penetration;

		ball->rigidbody->velocity.x -= 2.0f * dot * info.normal.x;
		ball->rigidbody->velocity.y -= 2.0f * dot * info.normal.y;

	}

	if (ball->Collider()->CheckCollision(*collider->Collider(), info))
	{

		SDL_Log("Collision detected! %f", info.penetration);


		float dot = ball->rigidbody->velocity.x * info.normal.x + ball->rigidbody->velocity.y * info.normal.y;

		SDL_FPoint force = SDL_FPoint
		{
			ball->rigidbody->velocity.x * 0.5f,
			ball->rigidbody->velocity.y * 0.5f
		};

		ball->transform->position.x -= info.normal.x * info.penetration;
		ball->transform->position.y -= info.normal.y * info.penetration;

		ball->rigidbody->velocity.x -= 2.0f * dot * info.normal.x;
		ball->rigidbody->velocity.y -= 2.0f * dot * info.normal.y;

	}
}

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

	wall = Instantiate<Wall>(
		"wall",
		SDL_FPoint{ 800.0f, 0.0f },
		SDL_FPoint{ 50.0f, Utilities::SCREEN_HEIGHT }
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
	Physics();
}


void InGameScreen::Render(Renderer& renderer)
{
	Scene::Render(renderer);
	renderer.DrawText("8ball", Resources::FONT_TITLE, Utilities::WHITE, Utilities::SCREEN_WIDTH * 0.5f, Utilities::SCREEN_HEIGHT * 0.1f);
	
	
}
