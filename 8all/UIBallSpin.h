#pragma once

#include "GameObject.h"
class UIBallSpin : public GameObject
{

private:
	float x, y = 0.0f;

public:
	UIBallSpin(SDL_FPoint position, SDL_FPoint size);
	~UIBallSpin() override = default;

	float GetX() const { return x; }
	float GetY() const { return -y; }

	void Reset() { x = y = 0.0f; }

	void Update(float deltaTime) override;
	void Render(Renderer& renderer) override;
};

