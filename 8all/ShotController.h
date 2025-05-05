#pragma once

#include<SDL3/SDL.h>


class Ball;
class Renderer;
class UIBallSpin;
class GameRules;

class ShotController
{
private:
	GameRules* gameRules;
	Ball* whiteBall;
	UIBallSpin* ballSpinUi;
	
	SDL_FPoint chargingVector{ 0.0f,0.0f };
	bool isCharging = false;


public:
	ShotController(GameRules* gameRules, Ball* whiteBall, UIBallSpin* ballSpinUi)
		:gameRules(gameRules), whiteBall(whiteBall), ballSpinUi(ballSpinUi) {};

	SDL_FPoint GetChargingVector() const { return chargingVector; }
	bool IsCharging() const { return isCharging; }
	
	void HandleMouseDown(float mouseX, float mouseY);
	void HandleMouseUp(float mouseX, float mouseY);
	void Update(float mouseX, float mouseY);
	void Render(Renderer& renderer);
	
	void ExecuteShot();
	void Disable();
};

