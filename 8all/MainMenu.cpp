#include "MainMenu.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include "Ball.h"

#include "Rigidbody.h"


#include <cstdlib>
#include <memory>

void MainMenu::MoveBalls(SDL_FPoint& force)
{
	SDL_FPoint forceVector = { force.x, force.y };
	for (auto& gameObject : gameObjects)
	{
		Ball* ball = dynamic_cast<Ball*>(gameObject.get());
		if (ball)
		{
			forceVector.x = force.x * static_cast<float>(rand()) / RAND_MAX * (1.8f - 0.2f);
			forceVector.y = force.y * static_cast<float>(rand()) / RAND_MAX * (1.8f - 0.2f);

			ball->rigidBody->ApplyForce(forceVector);
		}
	}
}

MainMenu::MainMenu()
{
}

void MainMenu::Enter()
{

	for (int i = 0; i < 5; i++)
	{
		SDL_FPoint pos = { 100 + i * 50, 100 + i * 50 };
		Instantiate<Ball>(pos);
	}

	SDL_FPoint position = { 500, 100 };
	Instantiate<Ball>(position);

}

void MainMenu::Exit()
{
	// Clean up resources, save state, etc.
	// This is where you would clean up the main menu scene.
	// For example, if you had loaded textures or fonts, you would unload them here.
	// renderer->UnloadFont(Resources::FONT_REGULAR);
	// renderer->UnloadFont(Resources::FONT_LITTLE);
	// renderer->UnloadFont(Resources::FONT_TITLE);
}

void MainMenu::HandleInputs(const SDL_Event& event)
{


	float force = 20.0f;
	SDL_FPoint forceVector = { 0.0f, 0.0f };

	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:

		switch (event.key.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			SDL_Log("Escape key pressed. Exiting...");
			break;
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

	MoveBalls(forceVector);
}




void MainMenu::Update(float deltaTime)
{

	for (auto& obj : gameObjects)
	{
		obj->Update(deltaTime);
	}
}

void MainMenu::Render(Renderer& renderer)
{
	for (auto& obj : gameObjects)
	{
		obj->Render(renderer);
	}

	// Render the main menu scene.
	// This could include drawing textures, fonts, etc.
	// For example, you might want to draw a background image, menu items, and other UI elements.
}
