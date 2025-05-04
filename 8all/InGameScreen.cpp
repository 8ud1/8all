#include "InGameScreen.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <memory>
#include <cstdlib>
#include <string>

#include "Utilities.h"
#include "BillardRack.h"

#include "Game.h"

#include "UITextButton.h"
#include "UIButton.h"

#include "Ball.h"
#include "Wall.h"
#include "HoleTrigger.h"


// Draw the table walls
void InGameScreen::CreateWalls()
{
	//Top
	Instantiate<Wall>("topLeft", SDL_FPoint{ 265.0f,55.0f }, SDL_FPoint{ 340.0f,50.0f }, true);
	Instantiate<Wall>("topRight", SDL_FPoint{ 655.0f,55.0f }, SDL_FPoint{ 340.0f,50.0f }, true);
	//Bottom
	Instantiate<Wall>("bottomLeft", SDL_FPoint{ 265.0f,570.0f }, SDL_FPoint{ 340.0f,50.0f }, true);
	Instantiate<Wall>("bottomRight", SDL_FPoint{ 655.0f,570.0f }, SDL_FPoint{ 340.0f,50.0f }, true);
	//Left
	Instantiate<Wall>("left", SDL_FPoint{ 180.0f , 130.0f }, SDL_FPoint{ 50.0f,420.0f }, true);
	//Right
	Instantiate<Wall>("right", SDL_FPoint{ 1020.0f , 130.0f }, SDL_FPoint{ 50.0f,420.0f }, true);

}

// Draw the table holes
void InGameScreen::CreateHoles()
{
	float holeSize = 10.0f;

	/*UpperLeft*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ 234.0f,101.0f }, holeSize, [this](PhysicsObject* obj) {this->OnHoleTrigger(obj); });
	/*LowerLeft*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ 234.0f,573.0f }, holeSize, [this](PhysicsObject* obj) {this->OnHoleTrigger(obj); });
	/*LowerCenter*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ 628.0f,590.0f }, holeSize, [this](PhysicsObject* obj) {this->OnHoleTrigger(obj); });
	/*UpperCenter*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ 628.0f,90.0f }, holeSize, [this](PhysicsObject* obj) {this->OnHoleTrigger(obj); });
	/*LowerRight*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ 1022.0f,573.0f }, holeSize, [this](PhysicsObject* obj) {this->OnHoleTrigger(obj); });
	/*UpperRight*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ 1022.0f,101.0f }, holeSize, [this](PhysicsObject* obj) {this->OnHoleTrigger(obj); });

}

void InGameScreen::CreateBalls()
{
	whiteBall = Instantiate<Ball>(
		"white ball",
		15,
		SDL_FPoint{ 350.0f,Utilities::SCREEN_HEIGHT * 0.5f }
	);


	BillardRack rack;

	for (auto& placement : rack.GenerateRack())
	{
		float x = Utilities::SCREEN_WIDTH * 0.6f + placement.row * 25.0f;

		float y = Utilities::SCREEN_HEIGHT * 0.5f - (placement.row * 0.5f * 25.0f) + 25.0f * placement.column + 12.5f;

		SDL_Log("Creating ball %d ", placement.number);
		balls.push_back(Instantiate<Ball>(
			"ball_" + std::to_string(placement.number),
			placement.number,
			SDL_FPoint{ x, y }
		));
	}
}

void InGameScreen::OnHoleTrigger(PhysicsObject* obj)
{

	//white ball in hole 
	if (obj == whiteBall)
	{
		whiteBall->transform->position = SDL_FPoint{ 350.0f,Utilities::SCREEN_HEIGHT * 0.5f };
		whiteBall->RigidBody()->SetVelocity(SDL_FPoint{0.0f,0.0f});
		return;
	}


	// ball in hole
	auto it = std::find(balls.begin(), balls.end(), obj);
	if (it != balls.end()) {
		

		Ball* ball = *it;

		if (ball->GetId() == 7)
		{
			//ball 8 in Hole

			SDL_Log("YOU LOST -> 8 ball in hole");
		}

		ballCount++;
		obj->RigidBody()->SetStatic(true);
		obj->transform->position = SDL_FPoint{ 50.0f,50.0f + ballCount * 40.0f };
	}
}

InGameScreen::InGameScreen(Game& game)
	: game(game)
{
}

void InGameScreen::Enter()
{
	CreateWalls();
	CreateBalls();
	CreateHoles();
}

void InGameScreen::Exit()
{
	
}


void InGameScreen::LogicUpdate(float deltaTime)
{
	Scene::LogicUpdate(deltaTime);
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
			(whiteBall->transform->position.x - mousePos.x),
			(whiteBall->transform->position.y - mousePos.y),
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
				(whiteBall->transform->position.x - mousePos.x) ,
				(whiteBall->transform->position.y - mousePos.y) ,
			};


			whiteBall->RigidBody()->ApplyForce(shotVector);

			isCharging = false;

		}
		break;

	case SDL_EVENT_MOUSE_BUTTON_DOWN:

		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_FRect ballRect =
			{
				whiteBall->transform->position.x - whiteBall->transform->scale.x * 0.5f,
				whiteBall->transform->position.y - whiteBall->transform->scale.y * 0.5f,
				whiteBall->transform->scale.x,
				whiteBall->transform->scale.y
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


void InGameScreen::Render(Renderer& renderer)
{
	renderer.DrawTexture(Resources::TABLE, SDL_FRect{ 0.0f,0.0f, Utilities::SCREEN_WIDTH, Utilities::SCREEN_HEIGHT });
	Scene::Render(renderer);


	
	SDL_Point ballPos = SDL_Point
	{
		(int)whiteBall->transform->position.x,
		(int)whiteBall->transform->position.y
	};

	renderer.DrawCircle(ballPos, 50, SDL_Color{255,0,0,255});

	if (isCharging)
	{
		for (int i = 1; i < 10; ++i)
		{

			SDL_FRect rect = SDL_FRect{
			(whiteBall->transform->position.x + chargingVector.x * ( 0.1f * i )),
			(whiteBall->transform->position.y + chargingVector.y * ( 0.1f * i )),
			5.0f,5.0f
			};

			renderer.DrawRect(rect, SDL_Color{ 255,0,0,255 });
		}
	}
}
