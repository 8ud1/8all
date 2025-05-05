#pragma once
#include <SDL3/SDL.h>
#include <functional>

#include "Canvas.h"



class PauseCanvas : public Canvas
{
private:

	std::function<void()> OnResume;
	std::function<void()> OnExit;
	std::function<void()> OnRestart;

protected:

	void InitCanvas() override;

public:

	PauseCanvas(		
		std::function<void()> resumeAction,
		std::function<void()> exitAction,
		std::function<void()> restartAction,
		bool startActive = false
	);

	void Update(float deltaTime) override;
	void Render(Renderer& renderer) override;
	
};

