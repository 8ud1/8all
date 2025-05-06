#include "ShotController.h"
#include <math.h>

#include "Ball.h"
#include "Renderer.h"
#include "UIBallSpin.h"
#include "GameRules.h"

void ShotController::HandleMouseDown(float mouseX, float mouseY)
{
	if (gameRules->IsTurnInProgress()) return;

	 
	SDL_FRect ballRect = {
		whiteBall->transform->position.x - whiteBall->transform->scale.x * 0.5f,
		whiteBall->transform->position.y - whiteBall->transform->scale.y * 0.5f,
		whiteBall->transform->scale.x,
		whiteBall->transform->scale.y
	};

	SDL_FPoint mousePos{ mouseX,mouseY };

	isCharging = SDL_PointInRectFloat(&mousePos, &ballRect);
}

void ShotController::HandleMouseUp(float mouseX, float mouseY)
{
	if (isCharging) ExecuteShot();
	isCharging = false;
	chargingVector = { 0.0f,0.0f };
}

void ShotController::Update(float mouseX, float mouseY)
{
	if (isCharging) {
		chargingVector.x = whiteBall->transform->position.x - mouseX;
		chargingVector.y = whiteBall->transform->position.y - mouseY;
	}
}

void ShotController::ExecuteShot()
{
	
	float length = chargingVector.x * chargingVector.x + chargingVector.y * chargingVector.y;
	if (length > 100.0f) {
		whiteBall->RigidBody()->ApplyForce(chargingVector);
		whiteBall->RigidBody()->SetAngularVelocity(ballSpinUi->GetX() * 100.f);
		whiteBall->RigidBody()->SetSpinForward(ballSpinUi->GetY());

		gameRules->OnPlayerShot();
	}
}

void ShotController::Disable()
{
	if (isCharging)
		isCharging = false;
}

void ShotController::Render(Renderer& renderer)
{
	if (isCharging)
	{
		for (int i = 1; i < 10; ++i)
		{

			SDL_FRect rect = SDL_FRect{
			(whiteBall->transform->position.x + chargingVector.x * (0.1f * i) - 2.5f),
			(whiteBall->transform->position.y + chargingVector.y * (0.1f * i) - 2.5f),
			5.0f,5.0f
			};

			renderer.DrawRect(rect, SDL_Color{ 255,0,0,255 });
		}
	}
}
