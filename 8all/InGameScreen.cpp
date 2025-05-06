#include "InGameScreen.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <memory>
#include <cstdlib>
#include <string>

#include "Game.h"

#include "Utilities.h"
#include "BillardRack.h"

#include "Ball.h"
#include "Wall.h"
#include "HoleTrigger.h"

#include "UIBallSpin.h"


void InGameScreen::Enter()
{
	SetupTable();
	SetupBalls();
	gameRules = std::make_unique<GameRules>(whiteBall, balls);
	SetupUI();
}


void InGameScreen::Exit()
{

}

void InGameScreen::HandleInputs(const SDL_Event& event)
{
	float mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	switch (event.type)
	{
	case SDL_EVENT_MOUSE_MOTION:
		uiManager->GetShotController()->Update(mouseX, mouseY);
		break;
	case SDL_EVENT_MOUSE_BUTTON_UP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			uiManager->GetShotController()->HandleMouseUp(mouseX, mouseY);
		}
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			uiManager->GetShotController()->HandleMouseDown(mouseX, mouseY);
		}
		break;
	case SDL_EVENT_KEY_DOWN:
		switch (event.key.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			uiManager->TooglePause();
			break;
		}
		break;
	default:
		break;
	}

	uiManager->HandleInputs(event);
}

void InGameScreen::LogicUpdate(float deltaTime)
{
	uiManager->Update(deltaTime);

	if(gameRules->IsGameOver() || uiManager->GetPauseCanvas()->IsActive()) return;
	
	Scene::LogicUpdate(deltaTime);


	if (gameRules->IsTurnInProgress())
	{
		if (physicsSystem.AreAllObjectsStopped(0.05f))
		{
			gameRules->EvaluateTurn();

			if (gameRules->IsGameOver())
			{
				uiManager->ShowGameOver(gameRules->GetWinner());
				return;
			}

			gameRules->NextTurn();
			uiManager->PrepareNextTurn(gameRules->GetCurrentPlayer(),gameRules->GetPlayerInfo(0),gameRules->GetPlayerInfo(1));
		}
	}

}

void InGameScreen::PhysicsUpdate(float deltaTime)
{
	if (gameRules->IsGameOver() || uiManager->GetPauseCanvas()->IsActive()) return;
	Scene::PhysicsUpdate(deltaTime);
}

void InGameScreen::Render(Renderer& renderer)
{
	renderer.DrawTexture(Resources::TABLE, SDL_FRect{ 0.0f,0.0f, Utilities::SCREEN_WIDTH, Utilities::SCREEN_HEIGHT });
	Scene::Render(renderer);

	uiManager->Render(renderer);
}

void InGameScreen::SetupTable()
{
	//*Walls*
	//
	//Top
	Instantiate<Wall>("topLeft", SDL_FPoint{ 275.0f,55.0f }, SDL_FPoint{ 338.0f,50.0f }, false);
	Instantiate<Wall>("topRight", SDL_FPoint{ 668.0f,55.0f }, SDL_FPoint{ 338.0f,50.0f }, false);
	//Bottom
	Instantiate<Wall>("bottomLeft", SDL_FPoint{ 275.0f,575.0f }, SDL_FPoint{ 338.0f,50.0f }, false);
	Instantiate<Wall>("bottomRight", SDL_FPoint{ 668.0f,575.0f }, SDL_FPoint{ 338.0f,50.0f }, false);
	//Left
	Instantiate<Wall>("left", SDL_FPoint{ 200.0f , 138.0f }, SDL_FPoint{ 50.0f,410.0f }, false);
	//Right
	Instantiate<Wall>("right", SDL_FPoint{ 1030.0f , 138.0f }, SDL_FPoint{ 50.0f,410.0f }, false);

	//*Holes*
	//
	float holeSize = 20.0f;
	/*UpperLeft*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ 243.0f,105.0f }, holeSize, [this](PhysicsObject* obj) { gameRules->OnHoleTrigger(obj); });
	/*LowerLeft*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ 243.0f,580.0f }, holeSize, [this](PhysicsObject* obj) { gameRules->OnHoleTrigger(obj); });
	/*LowerCenter*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.5f,598.0f }, holeSize, [this](PhysicsObject* obj) { gameRules->OnHoleTrigger(obj); });
	/*UpperCenter*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ Utilities::SCREEN_WIDTH * 0.5f,88.0f }, holeSize, [this](PhysicsObject* obj) { gameRules->OnHoleTrigger(obj); });
	/*LowerRight*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ 1037.0f,580.0f }, holeSize, [this](PhysicsObject* obj) { gameRules->OnHoleTrigger(obj); });
	/*UpperRight*/Instantiate<HoleTrigger>("trigger", SDL_FPoint{ 1037.0f,105.0f }, holeSize, [this](PhysicsObject* obj) { gameRules->OnHoleTrigger(obj); });

}

void InGameScreen::SetupBalls()
{
	SDL_FPoint middleBoard{
		640.0f,
		340.0f
	};

	BillardRack rack;
	for (auto& placement : rack.GenerateRack())
	{
		float x = middleBoard.x + 100 + placement.row * 30.0f;
		float y = middleBoard.y - (placement.row * 0.5f * 30.0f) + 30.0f * placement.column ;
		balls.push_back(Instantiate<Ball>("ball_" + std::to_string(placement.number),placement.number,SDL_FPoint{ x, y }));
	}

	whiteBall = Instantiate<Ball>("white ball", 15, SDL_FPoint{ middleBoard.x - 200 ,middleBoard.y });
}


void InGameScreen::SetupUI()
{
	uiManager = std::make_unique<GameUIManager>(
		game, gameRules.get(), whiteBall);

	gameRules->SetUiManager(uiManager.get());
}





